#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QWidget>
#include <QGLWidget>
#include <QTimer>
#include <QMessageBox>
#include <QAbstractButton>

#include "OpenGL/glperspective.h"
#include "OpenGL/gllight.h"
#include "OpenGL/glcube.h"
#include "simulation/solarsystemsimulation.h"

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
    
protected:
    void keyPressEvent(QKeyEvent *ke);

private:
    SolarSystemSimulation *solarSystemSimulation;

    QTimer *timer;

    GLPerspective * perspective;

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
    void drawAxes();
    void updateOpenGL();

private slots:
    void timerEvent();
    void collisionDetected(HeavenlyBody3d *firstHeavenlyBody3d, HeavenlyBody3d *secondHeavenlyBody3d);

signals:
    void simulationStopped();
    void collisionDetectionDeactivated();

};

#endif // SIMULATIONVIEW_H
