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

    ui->solarSystemTableView->setColumnWidth(1, 320);
}

SolarSystemOverview::~SolarSystemOverview()
{
    delete ui;
}

void SolarSystemOverview::doubleClicked(QModelIndex modelIndex)
{
    on_edit_clicked();
}

void SolarSystemOverview::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    ui->edit->setEnabled(selected.size() == 1);
    ui->deleteEntity->setEnabled(selected.size() == 1);
}

void SolarSystemOverview::on_add_clicked()
{
    showSolarSystemDetails(false);
}

void SolarSystemOverview::on_edit_clicked()
{
    if (solarSystemModel->isEntitySelected())
    {
        showSolarSystemDetails(true);
    }
}

void SolarSystemOverview::showSolarSystemDetails(bool isEdit)
{
    try
    {
        solarSystemModel->loadOtherEntities();

        if (solarSystemModel->getStarsComboBoxModel()->rowCount() <= 0)
        {
            QMessageBox::critical(this,
                                  "No star found",
                                  "There is at least one star needed to create a new solar system!\n\nPlease create one first.",
                                  QMessageBox::Ok);

        }
        else
        {
            SolarSystemDetails *solarSystemDetails = new SolarSystemDetails(this, solarSystemModel, isEdit);
            solarSystemDetails->show();
        }
    }
    catch (const SqlQueryException &sqlQueryException)
    {
        QMessageBox::critical(this,
                              "Database SQL error",
                              QString("There was an error with an SQL statement!\n\nError:\n\n%1").arg(sqlQueryException.getSqlError()),
                              QMessageBox::Ok);
    }
}

void SolarSystemOverview::on_deleteEntity_clicked()
{
    if (solarSystemModel->getCurrentSolarSystem())
    {
        int result = QMessageBox::question(this,
                                           "Delete a Solar System",
                                           QString("Would you like to delete the Solar System '%1'?").arg(solarSystemModel->getCurrentSolarSystem()->getName()),
                                           QMessageBox::Yes | QMessageBox::No);

        if (result == QMessageBox::Yes)
        {
            solarSystemModel->deleteSolarSystem();
        }
    }
}

void SolarSystemOverview::on_startSimulation_clicked()
{
    emit simulateSolarSystem(solarSystemModel->getCurrentSolarSystem());

    close();
}
