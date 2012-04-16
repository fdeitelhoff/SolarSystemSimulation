#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    solarSystemSimulation = new SolarSystemSimulation();

    simulationView = new SimulationView(this, solarSystemSimulation);
    connect(simulationView,
            SIGNAL(simulationStopped()),
            this,
            SLOT(simulationStopped()));
    connect(simulationView,
            SIGNAL(collisionDetectionDeactivated()),
            this,
            SLOT(collisionDetectionDeactivated()));

    setCentralWidget(simulationView);

    try
    {
        // With the current architecture this should not be necessary here.
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStartSimulation_triggered()
{
    simulationView->startSimulation();

    setSimulationMenuState(false);
}

void MainWindow::on_actionStopSimulation_triggered()
{
    simulationView->stopSimulation();

    setSimulationMenuState(false);
}

void MainWindow::on_actionHeavenlyBodyOverview_triggered()
{
    HeavenlyBodyOverview *heavenlyBodyOverview = new HeavenlyBodyOverview(this, heavenlyBodyModel);
    heavenlyBodyOverview->show();
}

void MainWindow::on_actionSolarSystemOverview_triggered()
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
    simulationView->setSolarSystem(solarSystem);
    solarSystemSimulation->setOrbitVisible(ui->actionOrbitVisible->isChecked());

    on_actionStartSimulation_triggered();
}

void MainWindow::on_actionOrbitVisible_triggered()
{
    solarSystemSimulation->setOrbitVisible(ui->actionOrbitVisible->isChecked());
}

void MainWindow::on_actionResetPerspective_triggered()
{
    simulationView->resetPerspective();
}


//void MainWindow::on_actionKeplersLawDefault_triggered()
//{
//    simulationView->toggleKeplersLaw();
//}

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
}

void MainWindow::collisionDetectionDeactivated()
{
    ui->actionDetectCollisions->setChecked(false);
}

