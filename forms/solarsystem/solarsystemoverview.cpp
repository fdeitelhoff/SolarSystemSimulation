#include "solarsystemoverview.h"
#include "ui_solarsystemoverview.h"

SolarSystemOverview::SolarSystemOverview(QWidget *parent, SolarSystemModel *solarSystemModel) :
    QDialog(parent),
    ui(new Ui::SolarSystemOverview)
{
    ui->setupUi(this);

    this->solarSystemModel = solarSystemModel;

    ui->solarSystemTableView->setModel(solarSystemModel->getSolarSystemTableModel());
    solarSystemModel->setSolarSystemSelectionModel(ui->solarSystemTableView->selectionModel());

    solarSystemModel->loadAllSolarSystemEntities();

    ui->solarSystemTableView->selectRow(0);

    QObject::connect(ui->solarSystemTableView,
                     SIGNAL(doubleClicked(QModelIndex)),
                     this,
                     SLOT(doubleClicked(QModelIndex)),
                     Qt::DirectConnection);

    QObject::connect(ui->solarSystemTableView->selectionModel(),
                     SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,
                     SLOT(selectionChanged(QItemSelection,QItemSelection)),
                     Qt::DirectConnection);
}

SolarSystemOverview::~SolarSystemOverview()
{
    delete ui;
}

void SolarSystemOverview::doubleClicked(QModelIndex modelIndex)
{
    if (solarSystemModel->isEntitySelected())
    {
        SolarSystemDetails *solarSystemDetails = new SolarSystemDetails(this, solarSystemModel, true);
        solarSystemDetails->show();
    }
}

void SolarSystemOverview::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    ui->edit->setEnabled(selected.size() == 1);
    ui->deleteEntity->setEnabled(selected.size() == 1);
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

void SolarSystemOverview::on_startSimulation_clicked()
{
    emit simulateSolarSystem(solarSystemModel->getCurrentSolarSystem());

    close();
}
