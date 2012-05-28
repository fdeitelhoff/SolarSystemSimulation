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

#include "mainwindow.h"
#include "ui_mainwindow.h"

/*!
 \brief Open the main window and establish the database connection.

 \param parent
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    solarSystemSimulation = new SolarSystemSimulation();

    solarSystemSimulationView = new SimulationView(this, solarSystemSimulation);

    connect(solarSystemSimulationView,
            SIGNAL(simulationStopped()),
            this,
            SLOT(simulationStopped()));
    connect(solarSystemSimulationView,
            SIGNAL(collisionDetectionDeactivated()),
            this,
            SLOT(collisionDetectionDeactivated()));
    try
    {
        heavenlyBodyModel = new HeavenlyBodyModel();
        solarSystemModel = new SolarSystemModel();
    }
    catch (const DatabaseConnectionFailedException &dbConnectionFailed)
    {
        QMessageBox::critical(this,
                              "Database connection error",
                              QString("The database connection could not be opened!\n\nError:\n\n%1").arg(dbConnectionFailed.getSqlError()),
                              QMessageBox::Ok);

        exit(DatabaseConnectionError);
    }

    setCentralWidget(solarSystemSimulationView);
}

/*!
 \brief Destructor for the main window

*/
MainWindow::~MainWindow()
{
    delete ui;
    delete solarSystemSimulation;
    delete solarSystemSimulationView;
    delete heavenlyBodyModel;
    delete solarSystemModel;
}

/*!
 \brief Automatic connection

*/
void MainWindow::on_actionExit_triggered()
{
    close();
}

/*!
 \brief SLOT to close the application

*/
void MainWindow::closeApplication()
{
    solarSystemSimulationView->stopSimulation();
}

/*!
 \brief Open Solar System overview or restart paused simulation.

*/
void MainWindow::on_actionStartSimulation_triggered()
{
    if (!solarSystemSimulation->isSolarSystemAvailable())
    {
        ui->actionStartSimulation->setChecked(false);

        showSolarSystemOverview();
    }
    else
    {
        startSimulation();
    }
}

/*!
 \brief Automatic SLOT to stop simulation.

*/
void MainWindow::on_actionStopSimulation_triggered()
{
    stopSimulation();
}

/*!
 \brief Method to start the simulation.

*/
void MainWindow::startSimulation()
{
    solarSystemSimulationView->startSimulation();
    setWindowTitle(QString("Solar System Simulation - Solar System '%1' simulation running").arg(solarSystemSimulation->getSolarSystemName()));

    setSimulationMenuState(true);
}

/*!
 \brief Method to stop the simulation.

*/
void MainWindow::stopSimulation()
{
    solarSystemSimulationView->stopSimulation();
    setWindowTitle(QString("Solar System Simulation - Solar System '%1' simulation stopped").arg(solarSystemSimulation->getSolarSystemName()));

    setSimulationMenuState(false);
}

/*!
 \brief Automatic connection to show heavenly body overview.

*/
void MainWindow::on_actionHeavenlyBodyOverview_triggered()
{
    try
    {
        HeavenlyBodyOverview *heavenlyBodyOverview = new HeavenlyBodyOverview(this, heavenlyBodyModel);
        heavenlyBodyOverview->show();
    }
    catch (const SqlQueryException &sqlQueryException)
    {
        QMessageBox::critical(this,
                              "Database SQL error",
                              QString("There was an error with an SQL statement!\n\nError:\n\n%1").arg(sqlQueryException.getSqlError()),
                              QMessageBox::Ok);
    }
}

/*!
 \brief Automatic connection to show solar system overview.

*/
void MainWindow::on_actionSolarSystemOverview_triggered()
{
    showSolarSystemOverview();
}

/*!
 \brief Method to show solar system overview

*/
void MainWindow::showSolarSystemOverview()
{
    SolarSystemOverview *solarSystemOverview = new SolarSystemOverview(this, solarSystemModel);

    QObject::connect(solarSystemOverview,
                     SIGNAL(simulateSolarSystem(SolarSystem*)),
                     this,
                     SLOT(simulateSolarSystem(SolarSystem*)));

    solarSystemOverview->show();
}

/*!
 \brief

 \param solarSystem Set checkboxes foe simulation
*/
void MainWindow::simulateSolarSystem(SolarSystem *solarSystem)
{
    solarSystemSimulationView->setSolarSystem(solarSystem);
    solarSystemSimulation->setOrbitVisible(ui->actionOrbitVisible->isChecked());
    solarSystemSimulation->setCollisionDetection(ui->actionDetectCollisions->isChecked());

    on_actionStartSimulation_triggered();
}

/*!
 \brief Automatic connection to trigger orbit visible.

*/
void MainWindow::on_actionOrbitVisible_triggered()
{
    solarSystemSimulation->setOrbitVisible(ui->actionOrbitVisible->isChecked());
}

/*!
 \brief Automatic connection to reset the perspective

*/
void MainWindow::on_actionResetPerspective_triggered()
{
    solarSystemSimulationView->resetPerspective();
}

/*!
 \brief Set the simulation state to false.

*/
void MainWindow::simulationStopped()
{
    setSimulationMenuState(false);
}

/*!
 \brief Automatic connection to trigger collision detection

*/
void MainWindow::on_actionDetectCollisions_triggered()
{
    solarSystemSimulation->setCollisionDetection(ui->actionDetectCollisions->isChecked());
}

/*!
 \brief Set checkboxes for start and stop simulation.

 \param isSimulationStarted
*/
void MainWindow::setSimulationMenuState(bool isSimulationStarted)
{
    ui->actionStartSimulation->setChecked(isSimulationStarted);
    ui->actionStopSimulation->setChecked(!isSimulationStarted);

    if (!ui->actionStopSimulation->isEnabled())
    {
        ui->actionStopSimulation->setEnabled(isSimulationStarted);
    }
}

/*!
 \brief Deactivate checkbox for collision detection.

*/
void MainWindow::collisionDetectionDeactivated()
{
    ui->actionDetectCollisions->setChecked(false);
}

/*!
 \brief Automatic connection to show about window when menu clicked.

*/
void MainWindow::on_actionAboutThisApplication_triggered()
{
    About *about = new About(this);
    about->show();
    about->setFixedSize(about->size());
}

/*!
 \brief Automatic connections to trigger visibility coordinates.

*/
void MainWindow::on_actionCoordinatesVisible_triggered()
{
    solarSystemSimulationView->toggleCoordinateAxesVisibility();
}

/*!
 \brief Close the application directly when no simulation is active.

 \param event
*/
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (solarSystemSimulationView->isSimulationStarted())
    {
        int result = QMessageBox::question(this,
                                           "Exit application",
                                           "There is already a solar system simulation running. Would you like to close the application?",
                                           QMessageBox::Yes | QMessageBox::No,
                                           QMessageBox::No);

        if (result == QMessageBox::Yes)
        {
            closeApplication();
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        closeApplication();
        event->accept();
    }
}

/*!
 \brief Show the language depending manual (PDF) in the system default reader.

*/
void MainWindow::on_actionShowHelp_triggered()
{
    QString defaultLocale = QLocale::system().name();

    QString manualPath = QApplication::applicationDirPath();
    manualPath.append(QString("/documentation/%1/manual.pdf").arg(defaultLocale));

    QDesktopServices::openUrl(QUrl("file:///" + manualPath));
}
