#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QWidget>
#include <QGLWidget>
#include <QTimer>
#include <QMessageBox>
#include <QAbstractButton>

#include "OpenGL/glperspective.h"
#include "simulation/solarsystemsimulation.h"
#include "visualization/light/light.h"
#include "visualization/environment/environment.h"

namespace Ui {
class SimulationView;
}

class SimulationView : public QGLWidget
{
    Q_OBJECT
    
public:
    explicit SimulationView(QWidget *parent = 0, SolarSystemSimulation *solarSystemSimulation = 0);
    ~SimulationView();

    void setSolarSystem(SolarSystem *solarSystem);

    void startSimulation();
    void stopSimulation();

    void resetPerspective();
    bool isSimulationStarted();

    void toggleCoordinateAxesVisibility();
    
protected:
    void keyPressEvent(QKeyEvent *keyEvent);

private:
    SolarSystemSimulation *solarSystemSimulation;

    QTimer *timer;

    GLPerspective *perspective;
    Light *light;
    Environment *environment;

    GLdouble axisLength;

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void turnCameraUpDown(double angle);
    void turnCameraLeftRight(double angle);
    void stretchCameraDistance(double factor);
    void shiftSceneUpDown(double distance);
    void shiftSceneLeftRight(double distance);
    void shiftSceneForwardBackward(double distance);
    void mouseMoveEvent(QMouseEvent *me);
    int x;
    int y;
    void wheelEvent(QWheelEvent * wheelEvent);
    void updateOpenGL();

    double cameraZFactor;
    int axisLengthFactor;
    QColor backgroundColor;
    float shiftSceneUpDownFactor;
    float shiftSceneLeftRightFactor;
    float shiftSceneForwardBackwardFactor;
    float turnCameraUpDownFactor;
    float turnCameraLeftRightFactor;
    float stretchCameraDistanceForwardFactor;
    float stretchCameraDistanceBackwardFactor;

private slots:
    void timerEvent();
    void collisionDetected(HeavenlyBody3d *firstHeavenlyBody3d, HeavenlyBody3d *secondHeavenlyBody3d);

signals:
    void simulationStopped();
    void collisionDetectionDeactivated();

};

#endif // SIMULATIONVIEW_H
