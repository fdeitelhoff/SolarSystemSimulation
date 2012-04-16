#include "simulationview.h"
#include "ui_simulationview.h"

#include <QDebug>
#include <QWSKeyboardHandler>
#include <QKeyEvent>

#include "OpenGL/glcolorrgba.h"
#include "OpenGL/gllight.h"
#include "OpenGL/GL/glut.h"

SimulationView::SimulationView(QWidget *parent, SolarSystemSimulation *solarSystemSimulation) :
    QGLWidget(parent)
{
    perspective = new GLPerspective();
    perspective->setCamera(25 * v_Z);

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    this->solarSystemSimulation = solarSystemSimulation;
    connect(solarSystemSimulation,
            SIGNAL(collisionDetected(HeavenlyBody3d*,HeavenlyBody3d*)),
            this,
            SLOT(collisionDetected(HeavenlyBody3d*,HeavenlyBody3d*)));

    timer = new QTimer(this);
    connect(timer,
            SIGNAL(timeout()),
            this,
            SLOT(timerEvent()));
}

SimulationView::~SimulationView()
{
    stopSimulation();

    delete perspective;
    delete timer;
}

void SimulationView::resetPerspective()
{
    perspective->setCamera(solarSystemSimulation->getMaxSemimajorAxis() * 3.5 * v_Z);
    perspective->setCenter(v_Zero);
    axisLength = perspective->distance() * 2;
}

void SimulationView::startSimulation()
{
    if (!timer->isActive())
    {
        timer->start(20);
    }
}

void SimulationView::stopSimulation()
{
    if (timer->isActive())
    {
        timer->stop();
        emit simulationStopped();
    }
}

void SimulationView::setSolarSystem(SolarSystem *solarSystem)
{
    solarSystemSimulation->setSolarSystem(solarSystem);
    resetPerspective();
}

void SimulationView::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
}

void SimulationView::timerEvent()
{
    solarSystemSimulation->calculateSolarSystem3d();

    updateGL();
}

void SimulationView::collisionDetected(HeavenlyBody3d *firstHeavenlyBody3d, HeavenlyBody3d *secondHeavenlyBody3d)
{
    QMessageBox msgBox;

    QPushButton *stopSimulationButton = msgBox.addButton("Stop simulation", QMessageBox::ActionRole);
    QPushButton *ignoreCollisionsButton = msgBox.addButton("Ignore collisions", QMessageBox::ActionRole);

    msgBox.setWindowTitle("Collision detected");
    msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    msgBox.setText(QString("A collision was detected between the two objects '%1' and '%2'!\n\nWhat would you like to do?").arg(firstHeavenlyBody3d->getName(),
                                                                                                             secondHeavenlyBody3d->getName()));
    msgBox.setDefaultButton(stopSimulationButton);

    msgBox.exec();

    if (msgBox.clickedButton() == (QAbstractButton*)stopSimulationButton)
    {
        stopSimulation();
    }
    else if (msgBox.clickedButton() == (QAbstractButton*)ignoreCollisionsButton)
    {
        solarSystemSimulation->activateCollisionDetection(false);
        emit collisionDetectionDeactivated();
    }
}

void SimulationView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    perspective->apply();

    drawAxes();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat pos[4];
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;
    pos[3] = 1;

    GLfloat direc[4];
    direc[0] = 3;
    direc[1] = 3;
    direc[2] = 3;
    direc[3] = 1;

    glLightfv(GL_LIGHT0, GL_AMBIENT, GLColorRGBA(cl_White * 0.2).fv() );
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cl_White.fv() );
    glLightfv(GL_LIGHT0, GL_SPECULAR, cl_White.fv() );

    glLightfv(GL_LIGHT0, GL_POSITION, pos );
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direc );
    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180); // angle is 0 to 180
    //glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 180); // exponent is 0 to 128

    glMaterialfv(GL_FRONT, GL_SPECULAR, cl_White.fv());

    solarSystemSimulation->paintSolarSystem3d();

    glDisable(GL_LIGHTING);

    glFlush();
}

void SimulationView::drawAxes()
{
    QVector <GLVector> points(6);

    points[0] = GLVector(-axisLength,0.0,0.0);
    points[1] = GLVector(axisLength,0.0,0.0);
    points[2] = GLVector(0.0,-axisLength, 0.0);
    points[3] = GLVector(0.0,axisLength,0.0);
    points[4] = GLVector(0.0,0.0,-axisLength);
    points[5] = GLVector(0.0,0.0,axisLength);

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

void SimulationView::updateOpenGL()
{
    axisLength = perspective->distance() * 2; // / 10.0;

    updateGL();
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
            shiftSceneForwardBackward(-1.0);
            break;
        case Qt::Key_PageUp:
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

    updateOpenGL();
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

            updateOpenGL();
        }

        // Ist SHIFT gedrueckt?
        if (modifiers & Qt::ShiftModifier)
        {
            if ((x - me->x()) < 0)
            {
                shiftSceneLeftRight(-0.5);
            }
            else if ((x - me->x()) > 0)
            {
                shiftSceneLeftRight(0.5);
            }

            if ((y - me->y()) > 0)
            {
                shiftSceneUpDown(-0.5);
            }
            else if ((y - me->y()) < 0)
            {
                shiftSceneUpDown(0.5);
            }

            updateOpenGL();
        }
    }
    x = me->x();
    y = me->y();
}

void SimulationView::wheelEvent(QWheelEvent * wheelEvent)
{
    Qt::KeyboardModifiers modifiers = wheelEvent->modifiers();

    if (modifiers & Qt::ControlModifier)
    {
        int delta = wheelEvent->delta();

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

        updateOpenGL();
    }
}

void SimulationView::resizeGL(int width, int height)
{
    perspective->setViewport(width, height);
}

void SimulationView::turnCameraUpDown(double angle)
{
    perspective->turnCameraUpDown(angle);
}

void SimulationView::turnCameraLeftRight(double angle)
{
    perspective->turnCameraLeftRight(angle);
}

void SimulationView::stretchCameraDistance(double factor)
{
    perspective->stretchCameraDistance(factor);
}

void SimulationView::shiftSceneUpDown(double distance)
{
    perspective->shiftSceneUpDown(distance);
}

void SimulationView::shiftSceneLeftRight(double distance)
{
    perspective->shiftSceneLeftRight(distance);
}

void SimulationView::shiftSceneForwardBackward(double distance)
{
    perspective->shiftSceneForwardBackward(distance);
}
