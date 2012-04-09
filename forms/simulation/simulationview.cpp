#include "simulationview.h"
#include "ui_simulationview.h"
#include <QDebug>
#include <QWSKeyboardHandler>
#include <QKeyEvent>
#include "OpenGL/glcolorrgba.h"
#include "OpenGL/gllight.h"
#include "OpenGL/GL/glut.h"

SimulationView::SimulationView(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::SimulationView)
{
    ui->setupUi(this);

    //ui->setupUi(this);
    _Perspective = new GLPerspective();
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);


//        glutIdleFunc(main_loop_function);
//        glutMainLoop();
        startTimer(20);
}

SimulationView::~SimulationView()
{
    delete ui;
    delete _Perspective;
}


// Main loop
void main_loop_function() {
//// Z angle
//	static float angle;
//// Clear color (screen)
//// And depth (used internally to block obstructed objects)
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//// Load identity matrix
//	glLoadIdentity();
//// Multiply in translation matrix
//	glTranslatef(0, 0, -4);
//// Multiply in rotation matrix
//	glRotatef(angle, 0, 0, 1);
//// Render colored quad
//	glBegin(GL_QUADS);
//
//		glColor3ub(255, 000, 000);
//		glVertex2f(-1, 0);
//
//		glColor3ub(000, 255, 000);
//		glVertex2f(0, 1);
//
//		glColor3ub(000, 000, 255);
//		glVertex2f(1, 0);
//
//		glColor3ub(255, 255, 255);
//		glVertex2f(0, -1);
//
//	glEnd();
//// Swap buffers (color buffers, makes previous render visible)
//	glutSwapBuffers();
//// Increase angle to rotate
//	angle += 0.5;

    while(TRUE)

       qDebug("What happens");

}

//WorldView3d::WorldView3d(QWidget *parent) :
//        QGLWidget(parent)//,
//        //   ui(new Ui::WorldView3d)
//{
//    //ui->setupUi(this);
//    _Perspective = new GLPerspective();
//    setFocusPolicy(Qt::StrongFocus);
//    setMouseTracking(true);


////        glutIdleFunc(main_loop_function);
////        glutMainLoop();
//        startTimer(20);
//}

//WorldView3d::~WorldView3d()
//{
//    //delete ui;
//    delete _Perspective;
//}





void SimulationView::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);


}

void SimulationView::timerEvent(QTimerEvent *event)
{
    qDebug() << "Timer ID:" << event->timerId();
    updateGL();
}


void SimulationView::paintGL()

{
    static float pos = 0.0;
    static float step = .1;
    static float radius = 10;


    GLLight light;

    glColor3d(1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _Perspective->apply();

     drawScene();



    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cl_Red.fv());
    glMaterialfv(GL_FRONT, GL_SPECULAR, cl_White.fv());

    glPushMatrix();

    float a = cos(pos) * radius;
    float b = sin(pos) * radius;

    glTranslated(a , b, 0.0);
    pos += step;
    if (pos > 360)
        pos = 0;


    qDebug("pos: ");
    qDebug() << pos;

    glMateriali(GL_FRONT, GL_SHININESS, 100);
    light.switchOn();
    glutSolidSphere(0.7,32,32);
    glPopMatrix();



//
//    // 1. Sicherung der Matrix
//    glPushMatrix();
//
//    glTranslated(1.0, 0.0, 0.0);
//
//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cl_Green.fv());
//    glutSolidSphere(0.2,32,32);
//
//    // Matrix wieder herstellen
//    glPopMatrix();
//
//    glPushMatrix();
//
//    glTranslated(2.0, 2.0, 0.0);
//
//    //cube.draw( cl_Cyan );
//
//    glPopMatrix();
//
//    glPushMatrix();
//
//    glTranslated(-2.0, -2.0, 0.0);
//
//    //cube.draw( cl_Red );
//
//    glPopMatrix();
//
//    glPushMatrix();
//
//    glTranslated(0.0, 0.0, 0.0);
//
//    //cube.draw( cl_Yellow, 0.5 );
//
//    glPopMatrix();

    light.switchOff();
    glDisable(GL_LIGHTING);

    glFlush();
}

void SimulationView::drawScene()
{
    QVector <GLVector> points(6);

    points[0] = GLVector(0.0,0.0,0.0);
    points[1] = GLVector(1.0,0.0,0.0);
    points[2] = GLVector(0.0,0.0,0.0);
    points[3] = GLVector(0.0,1.0,0.0);
    points[4] = GLVector(0.0,0.0,0.0);
    points[5] = GLVector(0.0,0.0,1.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, sizeof(GLVector), points[0].dv());


    QVector <GLColorRGBA> colors(6);

    // rot. GLfloat r, GLfloat g, GLfloat b, GLfloat a =1.0
    colors[0] = GLColorRGBA(1.0, 0.0, 0.0, 1.0);
    colors[1] = GLColorRGBA(1.0, 0.0, 0.0, 1.0);

    // grün.
    colors[2] = GLColorRGBA(0.0, 1.0, 0.0, 1.0);
    colors[3] = GLColorRGBA(0.0, 1.0, 0.0, 1.0);

    // blau.
    colors[4] = GLColorRGBA(0.0, 0.0, 1.0, 1.0);
    colors[5] = GLColorRGBA(0.0, 0.0, 1.0, 1.0);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(GLColorRGBA), colors[0].fv());

    glDrawArrays(GL_LINES, 0, 6);


}

void SimulationView::loopToPaintOrbit()
{
    while(TRUE)
        updateGL();
}


void SimulationView::keyPressEvent(QKeyEvent *ke)
{
    qDebug("KeyboardEvent");
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
            shiftSceneForwardBackward(0.99);
            break;
            case Qt::Key_PageUp:
            qDebug("Hier geht wa schief (up)");
            shiftSceneForwardBackward(1.01);
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
  //  loopToPaintOrbit();
  //  updateGL();
}

void SimulationView::mouseMoveEvent(QMouseEvent *me)
{

    qDebug("mouseEvent");

    Qt::KeyboardModifiers modifiers = me->modifiers();

    // Ist CTRL gedrückt?
    if (modifiers & Qt::ControlModifier)
        {
        // Ist ALT gedrückt?
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

        // Ist SHIFT gedrückt?
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

    //    glViewport(0,0,width,height);
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
