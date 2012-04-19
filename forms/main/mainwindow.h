#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLayout>
#include <QCloseEvent>

#include "forms/heavenlybody/heavenlybodyoverview.h"
#include "forms/solarsystem/solarsystemoverview.h"
#include "forms/simulation/simulationview.h"
#include "forms/main/about.h"
#include "simulation/solarsystemsimulation.h"
#include "data/exceptions/sqlqueryexception.h"

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

    SimulationView *solarSystemSimulationView;
    SolarSystemSimulation *solarSystemSimulation;

    HeavenlyBodyModel *heavenlyBodyModel;
    SolarSystemModel *solarSystemModel;

    void setSimulationMenuState(bool isSimulationStarted);

    void showSolarSystemOverview();
    void closeApplication();
    void startSimulation();
    void stopSimulation();

    void closeEvent(QCloseEvent *event);

    enum ErrorCodes { DatabaseConnectionError = 1 };

private slots:
    void on_actionExit_triggered();
    void on_actionHeavenlyBodyOverview_triggered();
    void on_actionSolarSystemOverview_triggered();
    void on_actionStartSimulation_triggered();
    void on_actionStopSimulation_triggered();
    void on_actionOrbitVisible_triggered();
    void on_actionResetPerspective_triggered();
    void on_actionDetectCollisions_triggered();

    void on_actionAboutThisApplication_triggered();

    void simulateSolarSystem(SolarSystem *solarSystem);

    void simulationStopped();
    void collisionDetectionDeactivated();
};

#endif // MAINWINDOW_H
