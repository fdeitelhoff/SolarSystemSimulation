#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "forms/heavenlybody/heavenlybodyoverview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    simulationView = new SimulationView(this);
    setCentralWidget(simulationView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionHeavenlyBodyOverview_triggered()
{
    HeavenlyBodyOverview *heavenlyBodyOverview = new HeavenlyBodyOverview(this);
    heavenlyBodyOverview->show();
}
