#include "simulationview.h"
#include "ui_simulationview.h"

#include <QDebug>
#include <QWSKeyboardHandler>
#include <QKeyEvent>

#include "OpenGL/glcolorrgba.h"
#include "OpenGL/GL/glut.h"

SimulationView::SimulationView(QWidget *parent, SolarSystemSimulation *solarSystemSimulation) :
    QGLWidget(parent)
{
    perspective = new GLPerspective();

    light = new Light();

    environment = new Environment();

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

    // Some initial constants for the camera position and control.
    cameraZFactor = 3.5;
    axisLengthFactor = 2.0;
    backgroundColor = Qt::white;
    shiftSceneUpDownFactor = 0.5;
    shiftSceneLeftRightFactor = 0.5;
    shiftSceneForwardBackwardFactor = 1.0;
    turnCameraUpDownFactor = 1.0;
    turnCameraLeftRightFactor = 1.0;
    stretchCameraDistanceForwardFactor = 0.85;
    stretchCameraDistanceBackwardFactor = 1.15;
}

SimulationView::~SimulationView()
{
    stopSimulation();

    delete perspective;
    delete light;
    delete environment;
    delete timer;
}

bool SimulationView::isSimulationStarted()
{
    return timer->isActive();
}

void SimulationView::resetPerspective()
{
    perspective->setCamera(solarSystemSimulation->getMaxSemimajorAxis() * cameraZFactor * v_Z);
    perspective->setCenter(v_Zero);
    axisLength = perspective->distance() * axisLengthFactor;
}

void SimulationView::startSimulation()
{
    if (!timer->isActive())
    {
        timer->start(10);
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
    glClearColor(backgroundColor.red(), backgroundColor.green(),
                 backgroundColor.blue(), backgroundColor.alpha());
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
        solarSystemSimulation->setCollisionDetection(false);
        emit collisionDetectionDeactivated();
    }
}

void SimulationView::toggleCoordinateAxesVisibility()
{
    environment->toggleCoordinateAxesVisibility();

    update();
}

void SimulationView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply the current camera view.
    perspective->apply();

    // Draw the coordinate axis.
    environment->drawAxes(axisLength);

    // Enable the positional light source.
    light->enable();

    // Paint the solar system (planets and the star).
    solarSystemSimulation->paintSolarSystem3d();

    // Disable all lighting.
    light->disable();

    glFlush();
}

void SimulationView::updateOpenGL()
{
    axisLength = perspective->distance() * axisLengthFactor;

    updateGL();
}

void SimulationView::keyPressEvent(QKeyEvent *keyEvent)
{
    Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
    // Is the CTRL key pressed?
    if (modifiers & Qt::ControlModifier)
    {
        // Is the windows or the alt key pressed.
        if (modifiers & Qt::MetaModifier || modifiers & Qt::AltModifier)
        {
            switch (keyEvent->key())
            {
            case Qt::Key_Up:
                turnCameraUpDown(turnCameraUpDownFactor);
                break;
            case Qt::Key_Down:
                turnCameraUpDown(-turnCameraUpDownFactor);
                break;
            case Qt::Key_Left:
                turnCameraLeftRight(turnCameraLeftRightFactor);
                break;
            case Qt::Key_Right:
                turnCameraLeftRight(-turnCameraLeftRightFactor);
                break;
            case Qt::Key_PageDown:
                stretchCameraDistance(stretchCameraDistanceBackwardFactor);
                break;
            case Qt::Key_PageUp:
                stretchCameraDistance(stretchCameraDistanceForwardFactor);
                break;
            default:
                break;
            }
        }

        // Is the SHIFT key pressed?
        if (modifiers & Qt::ShiftModifier)
        {
            switch (keyEvent->key())
            {
            case Qt::Key_Up:
                shiftSceneUpDown(-shiftSceneUpDownFactor);
                break;
            case Qt::Key_Down:
                shiftSceneUpDown(shiftSceneUpDownFactor);
                break;
            case Qt::Key_Left:
                shiftSceneLeftRight(shiftSceneLeftRightFactor);
                break;
            case Qt::Key_Right:
                shiftSceneLeftRight(-shiftSceneLeftRightFactor);
                break;
            case Qt::Key_PageDown:
                stretchCameraDistance(stretchCameraDistanceBackwardFactor);
                break;
            case Qt::Key_PageUp:
                stretchCameraDistance(stretchCameraDistanceForwardFactor);
                break;
            default:
                break;
            }
        }
    }

    updateOpenGL();
}

void SimulationView::mouseMoveEvent(QMouseEvent *me)
{
    Qt::KeyboardModifiers modifiers = me->modifiers();

    // Is the CTRL key pressed?
    if (modifiers & Qt::ControlModifier)
    {
        // Is the windows or the alt key pressed.
        if (modifiers & Qt::MetaModifier || modifiers & Qt::AltModifier)
        {
            if ((x - me->x()) < 0)
            {
                turnCameraLeftRight(-turnCameraLeftRightFactor);
            }
            else if (((x - me->x()) > 0))
            {
                turnCameraLeftRight(turnCameraLeftRightFactor);
            }

            if ((y - me->y()) > 0)
            {
                turnCameraUpDown(-turnCameraUpDownFactor);
            }
            else if ((y - me->y()) < 0)
            {
                turnCameraUpDown(turnCameraUpDownFactor);
            }

            updateOpenGL();
        }

        // Is the SHIFT key pressed?
        if (modifiers & Qt::ShiftModifier)
        {
            if ((x - me->x()) < 0)
            {
                shiftSceneLeftRight(-shiftSceneLeftRightFactor);
            }
            else if ((x - me->x()) > 0)
            {
                shiftSceneLeftRight(shiftSceneLeftRightFactor);
            }

            if ((y - me->y()) > 0)
            {
                shiftSceneUpDown(-shiftSceneUpDownFactor);
            }
            else if ((y - me->y()) < 0)
            {
                shiftSceneUpDown(shiftSceneUpDownFactor);
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
            stretchCameraDistance(stretchCameraDistanceBackwardFactor);
        }
        // Nach oben.
        else
        {
            stretchCameraDistance(stretchCameraDistanceForwardFactor);
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
