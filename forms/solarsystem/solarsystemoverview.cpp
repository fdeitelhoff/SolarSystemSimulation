#include "solarsystemoverview.h"
#include "ui_solarsystemoverview.h"

SolarSystemOverview::SolarSystemOverview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolarSystemOverview)
{
    ui->setupUi(this);

    solarSystemModel = new SolarSystemModel();

    ui->solarSystemTableView->setModel(solarSystemModel->getSolarSystemTableModel());
    solarSystemModel->setSolarSystemSelectionModel(ui->solarSystemTableView->selectionModel());

    solarSystemModel->loadAllSolarSystemEntities();
}

SolarSystemOverview::~SolarSystemOverview()
{
    delete ui;
}

void SolarSystemOverview::on_add_clicked()
{
    SolarSystemDetails *solarSystemDetails = new SolarSystemDetails(this, solarSystemModel, false);
    solarSystemDetails->show();
}

void SolarSystemOverview::on_edit_clicked()
{
    SolarSystemDetails *solarSystemDetails = new SolarSystemDetails(this, solarSystemModel, true);
    solarSystemDetails->show();
}

void SolarSystemOverview::on_deleteEntity_clicked()
{
    solarSystemModel->deleteSolarSystem();
}
