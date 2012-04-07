#include "simulationview.h"
#include "ui_simulationview.h"
#include <QDebug>
#include <QWSKeyboardHandler>
#include <QKeyEvent>
#include "OpenGL/glcolorrgba.h"
#include "OpenGL/gllight.h"
#include <GL/glut.h>


SimulationView::SimulationView(QWidget *parent) :
        QGLWidget(parent)//,
        //   ui(new Ui::SimulationView)
{
    //ui->setupUi(this);
    _Perspective = new GLPerspective(25 * v_Z);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    startTimer(20);
}

SimulationView::~SimulationView()
{
    //delete ui;
    delete _Perspective;
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
    //qDebug() << "Timer ID:" << event->timerId();
    updateGL();
}


void SimulationView::paintGL()

{
        // Inputvariablen
        static float a = 10; // Meter
        static float epsilon = 0.5;
        static float circumstance_time = 400; // Sekunden

        const float PI = 3.1415926535f;

        float b = a * sqrt(1 - epsilon * epsilon );
        float e = epsilon * a;

        // Umfang der Ellipse nach Ramanujan
        float lambda = ( a - b ) / ( a + b );
        float circumstance = ( a + b ) * PI * ( 1 + 3 * lambda * lambda / ( 10 + sqrt( 4 - 3 * lambda * lambda )));

        // Durchschnittsgeschwindigkeit bestimmen
        float average_speed = circumstance / circumstance_time;
        qDebug() << "Durchschnittsgeschwindigkeit: " << average_speed;

        // Mittlere Winkelgeschwindigkeit
        float omega_m = 2 * PI / circumstance_time;

        // Geschwindigkeit im Aphel
        float speed_aphel = omega_m * a * sqrt(( a - e ) / ( a + e ));
        qDebug() << "Geschwindigkeit Aphel: " << speed_aphel;

        // Geschwindigkeit im Perihel
        float speed_perihel = omega_m * a * sqrt(( a + e ) / ( a - e ));
        qDebug() << "Geschwindigkeit Perihel: " << speed_perihel;
        qDebug() << "\n";

        // My = Gravitationskonstante * Masse
        float my = speed_aphel * speed_aphel / ( 2 / ( a + e ) - 1 / a );





        static float phi = 0.0;
        static float step = 0.1;



    GLLight light;

    glColor3d(1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _Perspective->apply();

    drawScene();



    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cl_Red.fv());
    glMaterialfv(GL_FRONT, GL_SPECULAR, cl_White.fv());

    glPushMatrix();

    float x = cos(phi) * a + e;
    float y = sin(phi) * b;


    // Betrag des Vektors vom Brennpunk zum Planeten
    float r = sqrt( x * x + y * y);

    // Momentangeschwindigkeit des Planeten nach der Vis-Viva-Gleichung
    float instantaneous_velocity = sqrt( my * ( 2 / r - 1 / a ));
    qDebug() << "Phi: " << phi * 360 / ( 2 * PI );
    qDebug() << "x = " << x << "    y = " << y << "    r = " << r << "   my = " << my;
    qDebug() << "Momentangeschwindigkeit: " << instantaneous_velocity;

    glTranslated(x , y, 0.0);

    // Mit einem Dreisatz den zu überschreitenden Winkel bestimmen:
    // alpha / øalpha ~ v / øv
    float orbit_points_count = circumstance_time;
    float average_angle = 2 * PI / orbit_points_count;
    float alpha = average_angle * instantaneous_velocity / average_speed;

    phi += alpha;
    if (phi > 2 * PI)
        phi = 0;



    glMateriali(GL_FRONT, GL_SHININESS, 100);
    light.switchOn();
    glutSolidSphere(0.3,32,32);
    glPopMatrix();


    drawEllipse(a, b, e);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cl_Yellow.fv());
        glutSolidSphere(0.7,32,32);

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


void SimulationView::drawEllipse(float a, float b, float e)
{
        const float PI = 3.1415926535f;
        //Draws a ellpise made out of points.

            glColor3f(0,0,0);
                float x,y,z;
                float t;
            glBegin(GL_POINTS);
            for(t = 0; t <= 2 * PI; t += PI / 720)
                        {
                x = cos(t) * a + e;
                y = sin(t) * b;
                  z = 0;
                  glVertex3f(x,y,z);
                        }
            glEnd();

}

void SimulationView::drawScene()
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
