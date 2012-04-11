#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    simulationView = new SimulationView(this);
    setCentralWidget(simulationView);

    // With the current architecture this should not be necessary here.
    heavenlyBodyModel = new HeavenlyBodyModel();
    solarSystemModel = new SolarSystemModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStartSimulation_triggered()
{
    simulationView->startSimulation();
    ui->actionStartSimulation->setChecked(true);
    ui->actionStopSimulation->setChecked(false);
}

void MainWindow::on_actionStopSimulation_triggered()
{
    simulationView->stopSimulation();
    ui->actionStartSimulation->setChecked(false);
    ui->actionStopSimulation->setChecked(true);
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
                     SLOT(on_simulateSolarSystem(SolarSystem*)));

    solarSystemOverview->show();
}

void MainWindow::on_simulateSolarSystem(SolarSystem *solarSystem)
{
    simulationView->setSolarSystem(solarSystem);
    simulationView->setOrbitVisible(ui->actionOrbitVisible->isChecked());

    on_actionStartSimulation_triggered();
}

void MainWindow::on_actionOrbitVisible_triggered()
{
    simulationView->setOrbitVisible(ui->actionOrbitVisible->isChecked());
}

void MainWindow::on_actionResetPerspective_triggered()
{
    simulationView->resetPerspective();
}
