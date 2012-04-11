#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "forms/heavenlybody/heavenlybodyoverview.h"
#include "forms/solarsystem/solarsystemoverview.h"
#include "forms/simulation/simulationview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    SimulationView *simulationView;

    HeavenlyBodyModel *heavenlyBodyModel;
    SolarSystemModel *solarSystemModel;

private slots:
    void on_actionHeavenlyBodyOverview_triggered();
    void on_actionSolarSystemOverview_triggered();
    void on_actionStartSimulation_triggered();
    void on_actionStopSimulation_triggered();
    void on_actionOrbitVisible_triggered();
    void on_actionResetPerspective_triggered();

    void on_simulateSolarSystem(SolarSystem *solarSystem);
};

#endif // MAINWINDOW_H
