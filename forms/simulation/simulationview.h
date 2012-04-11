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
    
protected:
    void keyPressEvent(QKeyEvent *ke);

private:
    Ui::SimulationView *ui;

    SolarSystemSimulation *solarSystemSimulation;

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
    void loopToPaintOrbit();
    int x;
    int y;
    void wheelEvent(QWheelEvent * wheelEvent);
    void drawScene();
    void timerEvent(QTimerEvent *event);
    void drawEllipse(float a, float b, float e);
};

#endif // SIMULATIONVIEW_H
