#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    simulationView = new SimulationView(this);
    setCentralWidget(simulationView);

    heavenlyBodyModel = new HeavenlyBodyModel();
    heavenlyBodyModel->loadAllHeavenlyBodyEntities();

    solarSystemModel = new SolarSystemModel();
    solarSystemModel->loadAllSolarSystemEntities();
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
    solarSystemOverview->show();
}
