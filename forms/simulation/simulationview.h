#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QWidget>
#include <QGLWidget>

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
    explicit SimulationView(QWidget *parent = 0);
    ~SimulationView();

    void setSolarSystem(SolarSystem *solarSystem);

    void startSimulation();
    void stopSimulation();

    void setOrbitVisible(bool orbitVisible);
    
protected:
    void keyPressEvent(QKeyEvent *ke);

private:
    Ui::SimulationView *ui;

    SolarSystemSimulation *solarSystemSimulation;
    int timerId;

    GLPerspective * _Perspective;
    GLLight * _light;
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
    void timerEvent(QTimerEvent *event);
};

#endif // SIMULATIONVIEW_H
