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
}
