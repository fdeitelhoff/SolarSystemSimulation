#include "mainwindow.h"
#include "ui_mainwindow.h"

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

MainWindow::~MainWindow()
{
    delete ui;
    delete solarSystemSimulation;
    delete solarSystemSimulationView;
    delete heavenlyBodyModel;
    delete solarSystemModel;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::closeApplication()
{
    solarSystemSimulationView->stopSimulation();
}

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

void MainWindow::on_actionStopSimulation_triggered()
{
    stopSimulation();
}

void MainWindow::startSimulation()
{
    solarSystemSimulationView->startSimulation();
    setWindowTitle(QString("Solar System Simulation - Solar System '%1' simulation running").arg(solarSystemSimulation->getSolarSystemName()));

    setSimulationMenuState(true);
}

void MainWindow::stopSimulation()
{
    solarSystemSimulationView->stopSimulation();
    setWindowTitle(QString("Solar System Simulation - Solar System '%1' simulation stopped").arg(solarSystemSimulation->getSolarSystemName()));

    setSimulationMenuState(false);
}

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

void MainWindow::on_actionSolarSystemOverview_triggered()
{
    showSolarSystemOverview();
}

void MainWindow::showSolarSystemOverview()
{
    SolarSystemOverview *solarSystemOverview = new SolarSystemOverview(this, solarSystemModel);

    QObject::connect(solarSystemOverview,
                     SIGNAL(simulateSolarSystem(SolarSystem*)),
                     this,
                     SLOT(simulateSolarSystem(SolarSystem*)));

    solarSystemOverview->show();
}

void MainWindow::simulateSolarSystem(SolarSystem *solarSystem)
{
    solarSystemSimulationView->setSolarSystem(solarSystem);
    solarSystemSimulation->setOrbitVisible(ui->actionOrbitVisible->isChecked());

    on_actionStartSimulation_triggered();
}

void MainWindow::on_actionOrbitVisible_triggered()
{
    solarSystemSimulation->setOrbitVisible(ui->actionOrbitVisible->isChecked());
}

void MainWindow::on_actionResetPerspective_triggered()
{
    solarSystemSimulationView->resetPerspective();
}

void MainWindow::simulationStopped()
{
    setSimulationMenuState(false);
}

void MainWindow::on_actionDetectCollisions_triggered()
{
    solarSystemSimulation->activateCollisionDetection(ui->actionDetectCollisions->isChecked());
}

void MainWindow::setSimulationMenuState(bool isSimulationStarted)
{
    ui->actionStartSimulation->setChecked(isSimulationStarted);
    ui->actionStopSimulation->setChecked(!isSimulationStarted);

    if (!ui->actionStopSimulation->isEnabled())
    {
        ui->actionStopSimulation->setEnabled(isSimulationStarted);
    }
}

void MainWindow::collisionDetectionDeactivated()
{
    ui->actionDetectCollisions->setChecked(false);
}

void MainWindow::on_actionAboutThisApplication_triggered()
{
    About *about = new About(this);
    about->show();
    about->setFixedSize(about->size());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (solarSystemSimulationView->isSimulationStarted())
    {
        int result = QMessageBox::question(this,
                                           "Exit application",
                                           "There is already a solar system simulation running. Would you like to close the application?",
                                           QMessageBox::Yes | QMessageBox::No);

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
