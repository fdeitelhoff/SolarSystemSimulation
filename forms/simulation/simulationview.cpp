#include "simulationview.h"
#include "ui_simulationview.h"

#include <QDebug>
#include <QWSKeyboardHandler>
#include <QKeyEvent>

#include "OpenGL/glcolorrgba.h"
#include "OpenGL/gllight.h"
#include "OpenGL/GL/glut.h"

SimulationView::SimulationView(QWidget *parent) :
    QGLWidget(parent)//,
  //   ui(new Ui::SimulationView)
{
    //ui->setupUi(this);
    _Perspective = new GLPerspective(25 * v_Z);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    solarSystemSimulation = new SolarSystemSimulation();

    //startTimer(20);
}

SimulationView::~SimulationView()
{
    stopSimulation();

    delete _Perspective;
    delete solarSystemSimulation;
}

void SimulationView::setOrbitVisible(bool orbitVisible)
{
    solarSystemSimulation->setOrbitVisible(orbitVisible);
}

void SimulationView::startSimulation()
{
    if (timerId != -1)
    {
        timerId = startTimer(20);
    }
}

void SimulationView::stopSimulation()
{
    killTimer(timerId);
    timerId = -1;
}

void SimulationView::setSolarSystem(SolarSystem *solarSystem)
{
    solarSystemSimulation->setSolarSystem(solarSystem);
    startSimulation();
}

void SimulationView::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
}

void SimulationView::timerEvent(QTimerEvent *event)
{
    updateGL();
}

void SimulationView::paintGL()
{
    GLLight light;
    //light.setPosition(GLVector(5, 5, 5));
    light.setShowLightSource(false);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _Perspective->apply();

    drawAxes();
    light.switchOn();

    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT, GL_SPECULAR, cl_White.fv());

    solarSystemSimulation->paintSolarSystem3d();

    light.switchOff();
    glDisable(GL_LIGHTING);

    glFlush();
}

void SimulationView::drawAxes()
{
    QVector <GLVector> points(6);

    points[0] = GLVector(-100.0,0.0,0.0);
    points[1] = GLVector(100.0,0.0,0.0);
    points[2] = GLVector(0.0,-100.0,0.0);
    points[3] = GLVector(0.0,100.0,0.0);
    points[4] = GLVector(0.0,0.0,-100.0);
    points[5] = GLVector(0.0,0.0,100.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, sizeof(GLVector), points[0].dv());

    QVector <GLColorRGBA> colors(6);

    // rot. GLfloat r, GLfloat g, GLfloat b, GLfloat a =1.0
    colors[0] = GLColorRGBA(1.0, 0.0, 0.0, 1.0);
    colors[1] = GLColorRGBA(1.0, 0.0, 0.0, 1.0);

    // gruen.
    colors[2] = GLColorRGBA(0.0, 1.0, 0.0, 1.0);
    colors[3] = GLColorRGBA(0.0, 1.0, 0.0, 1.0);

    // blau.
    colors[4] = GLColorRGBA(0.0, 0.0, 1.0, 1.0);
    colors[5] = GLColorRGBA(0.0, 0.0, 1.0, 1.0);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(GLColorRGBA), colors[0].fv());

    glDrawArrays(GL_LINES, 0, 6);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void SimulationView::keyPressEvent(QKeyEvent *ke)
{
    if (ke->modifiers() == Qt::ShiftModifier)
    {
        switch (ke->key())
        {
        case Qt::Key_Up:
            shiftSceneUpDown(0.1);
            break;
        case Qt::Key_Down:
            shiftSceneUpDown(-0.1);
            break;
        case Qt::Key_Left:
            shiftSceneLeftRight(0.1);
            break;
        case Qt::Key_Right:
            shiftSceneLeftRight(-0.1);
            break;
        case Qt::Key_PageDown:
            qDebug("Hier geht wa schief (down)");
            shiftSceneForwardBackward(-1.0);
            break;
        case Qt::Key_PageUp:
            qDebug("Hier geht wa schief (up)");
            shiftSceneForwardBackward(1.0);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (ke->key())
        {
        case Qt::Key_Up: turnCameraUpDown(1.0);
            break;
        case Qt::Key_Down: turnCameraUpDown(-1.0);
            break;
        case Qt::Key_Left: turnCameraLeftRight(1.0);
            break;
        case Qt::Key_Right: turnCameraLeftRight(-1.0);
            break;
        case Qt::Key_PageDown: stretchCameraDistance(0.99);
            break;
        case Qt::Key_PageUp: stretchCameraDistance(1.01);
            break;
        default:
            break;
        }
    }
}

void SimulationView::mouseMoveEvent(QMouseEvent *me)
{
    Qt::KeyboardModifiers modifiers = me->modifiers();

    // Ist CTRL gedrueckt?
    if (modifiers & Qt::ControlModifier)
    {
        // Ist ALT gedrueckt?
        if (modifiers & Qt::AltModifier)
        {
            if ((x - me->x()) < 0)
            {
                turnCameraLeftRight(-1.0);
            }
            else if (((x - me->x()) > 0))
            {
                turnCameraLeftRight(1.0);
            }

            if ((y - me->y()) > 0)
            {
                turnCameraUpDown(-1.0);
            }
            else if ((y - me->y()) < 0)
            {
                turnCameraUpDown(1.0);
            }
        }

        // Ist SHIFT gedrueckt?
        if (modifiers & Qt::ShiftModifier)
        {
            if ((x - me->x()) < 0)
            {
                shiftSceneLeftRight(-0.1);
            }
            else if ((x - me->x()) > 0)
            {
                shiftSceneLeftRight(0.1);
            }

            if ((y - me->y()) > 0)
            {
                shiftSceneUpDown(-0.1);
            }
            else if ((y - me->y()) < 0)
            {
                shiftSceneUpDown(0.1);
            }
        }
    }
    x = me->x();
    y = me->y();
    //updateGL();
}

void SimulationView::wheelEvent(QWheelEvent * wheelEvent)
{
    Qt::KeyboardModifiers modifiers = wheelEvent->modifiers();

    if (modifiers & Qt::ControlModifier)
    {
        int delta = wheelEvent->delta();
        qDebug() << delta;

        // Nach unten.
        if (delta < 0)
        {
            stretchCameraDistance(1.15);
        }
        // Nach oben.
        else
        {
            stretchCameraDistance(0.85);
        }
        //  updateGL();
    }
}

void SimulationView::resizeGL(int width, int height)
{
    _Perspective->setViewport(width, height);
}

void SimulationView::turnCameraUpDown(double angle)
{
    _Perspective->turnCameraUpDown(angle);
}

void SimulationView::turnCameraLeftRight(double angle)
{
    _Perspective->turnCameraLeftRight(angle);
}

void SimulationView::stretchCameraDistance(double factor)
{
    _Perspective->stretchCameraDistance(factor);
}

void SimulationView::shiftSceneUpDown(double distance)
{
    _Perspective->shiftSceneUpDown(distance);
}

void SimulationView::shiftSceneLeftRight(double distance)
{
    _Perspective->shiftSceneLeftRight(distance);
}

void SimulationView::shiftSceneForwardBackward(double distance)
{
    _Perspective->shiftSceneForwardBackward(distance);
}
