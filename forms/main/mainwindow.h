#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLayout>
#include <QCloseEvent>
#include <QLocale>
#include <QDesktopServices>
#include <QUrl>

#include "forms/heavenlybody/heavenlybodyoverview.h"
#include "forms/solarsystem/solarsystemoverview.h"
#include "forms/simulation/simulationview.h"
#include "forms/main/about.h"
/*
    Copyright (C) 2012 by
    Fabian Deitelhoff (FH@FabianDeitelhoff.de) and
    Christof Geisler (christof.geisler@stud.fh-swf.de)

    This file is part of the project SolarSystemSimulation.

    SolarSystemSimulation is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SolarSystemSimulation is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SolarSystemSimulation.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "simulation/solarsystemsimulation.h"
#include "data/exceptions/sqlqueryexception.h"

namespace Ui {
class MainWindow;
}

/**
    Class with components to show the main window.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

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
    void on_actionCoordinatesVisible_triggered();

    void on_actionAboutThisApplication_triggered();

    void on_actionShowHelp_triggered();

    void simulateSolarSystem(SolarSystem *solarSystem);

    void simulationStopped();
    void collisionDetectionDeactivated();
};

#endif // MAINWINDOW_H
