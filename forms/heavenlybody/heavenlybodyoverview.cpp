#include "heavenlybodyoverview.h"
#include "ui_heavenlybodyoverview.h"

HeavenlyBodyOverview::HeavenlyBodyOverview(QWidget *parent, HeavenlyBodyModel *heavenlyBodyModel) :
    QDialog(parent),
    ui(new Ui::HeavenlyBodyOverview)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint);

    this->heavenlyBodyModel = heavenlyBodyModel;

    ui->heavenlyBodyTableView->setModel(heavenlyBodyModel->getHeavenlyBodyTableModel());
    heavenlyBodyModel->setSelectionModel(ui->heavenlyBodyTableView->selectionModel());

    heavenlyBodyModel->loadAllHeavenlyBodyEntities();

    ui->heavenlyBodyTableView->selectRow(0);

    QObject::connect(ui->heavenlyBodyTableView,
                     SIGNAL(doubleClicked(QModelIndex)),
                     this,
                     SLOT(doubleClicked(QModelIndex)),
                     Qt::DirectConnection);

    QObject::connect(ui->heavenlyBodyTableView->selectionModel(),
                     SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,
                     SLOT(selectionChanged(QItemSelection,QItemSelection)),
                     Qt::DirectConnection);

    ui->heavenlyBodyTableView->setColumnWidth(1, 300);
}

HeavenlyBodyOverview::~HeavenlyBodyOverview()
{
    delete ui;
}

void HeavenlyBodyOverview::doubleClicked(QModelIndex modelIndex)
{
    if (heavenlyBodyModel->isEntitySelected())
    {
        try
        {
            HeavenlyBodyDetails *heavenlyBodyDetails = new HeavenlyBodyDetails(this, heavenlyBodyModel, true);
            heavenlyBodyDetails->show();
        }
        catch (const SqlQueryException &sqlQueryException)
        {
            QMessageBox::critical(this,
                                  "Database SQL error",
                                  QString("There was an error with an SQL statement!\n\nError:\n\n%1").arg(sqlQueryException.getSqlError()),
                                  QMessageBox::Ok);
        }
    }
}

void HeavenlyBodyOverview::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    ui->edit->setEnabled(selected.size() == 1);
    ui->deleteEntity->setEnabled(selected.size() == 1);
}

void HeavenlyBodyOverview::on_add_clicked()
{
    try
    {
        HeavenlyBodyDetails *heavenlyBodyDetails = new HeavenlyBodyDetails(this, heavenlyBodyModel, false);
        heavenlyBodyDetails->show();
    }
    catch (const SqlQueryException &sqlQueryException)
    {
        QMessageBox::critical(this,
                              "Database SQL error",
                              QString("There was an error with an SQL statement!\n\nError:\n\n%1").arg(sqlQueryException.getSqlError()),
                              QMessageBox::Ok);
    }
}

void HeavenlyBodyOverview::on_edit_clicked()
{
    if (heavenlyBodyModel->isEntitySelected())
    {
        try
        {
            HeavenlyBodyDetails *heavenlyBodyDetails = new HeavenlyBodyDetails(this, heavenlyBodyModel, true);
            heavenlyBodyDetails->show();
        }
        catch (const SqlQueryException &sqlQueryException)
        {
            QMessageBox::critical(this,
                                  "Database SQL error",
                                  QString("There was an error with an SQL statement!\n\nError:\n\n%1").arg(sqlQueryException.getSqlError()),
                                  QMessageBox::Ok);
        }
    }
}

void HeavenlyBodyOverview::on_deleteEntity_clicked()
{
    if (heavenlyBodyModel->getSelectedEntity())
    {
        try
        {
            int result = QMessageBox::question(this,
                                               "Delete a Heavenly Body",
                                               QString("Would you like to delete the Heavenly Body '%1'?").arg(heavenlyBodyModel->getSelectedEntity()->getName()),
                                               QMessageBox::Yes | QMessageBox::No);

            if (result == QMessageBox::Yes)
            {
                heavenlyBodyModel->deleteEntity();
            }
        }
        catch (const DeleteEntityFailedException &exception)
        {
            QMessageBox::critical(this,
                                  "Error while deleting",
                                  exception.getMessage() + "\n\nSQL-Error:\n" + exception.getSqlError(),
                                  QMessageBox::Ok);
        }
    }
}
