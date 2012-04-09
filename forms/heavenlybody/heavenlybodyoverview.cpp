#include "heavenlybodyoverview.h"
#include "ui_heavenlybodyoverview.h"

HeavenlyBodyOverview::HeavenlyBodyOverview(QWidget *parent, HeavenlyBodyModel *heavenlyBodyModel) :
    QDialog(parent),
    ui(new Ui::HeavenlyBodyOverview)
{
    ui->setupUi(this);

    this->heavenlyBodyModel = heavenlyBodyModel;

    ui->heavenlyBodyTableView->setModel(heavenlyBodyModel->getHeavenlyBodyTableModel());
    heavenlyBodyModel->setSelectionModel(ui->heavenlyBodyTableView->selectionModel());

    ui->heavenlyBodyTableView->selectRow(0);
}

HeavenlyBodyOverview::~HeavenlyBodyOverview()
{
    delete ui;
}

void HeavenlyBodyOverview::on_add_clicked()
{
    HeavenlyBodyDetails *heavenlyBodyDetails = new HeavenlyBodyDetails(this, heavenlyBodyModel, false);
    heavenlyBodyDetails->show();
}

void HeavenlyBodyOverview::on_edit_clicked()
{
    HeavenlyBodyDetails *heavenlyBodyDetails = new HeavenlyBodyDetails(this, heavenlyBodyModel, true);
    heavenlyBodyDetails->show();
}

void HeavenlyBodyOverview::on_deleteEntity_clicked()
{
    try
    {
        heavenlyBodyModel->deleteEntity();
    }
    catch (const DeleteEntityFailedException &exception)
    {
        QMessageBox::information(this,
                                 "Error while deleting",
                                 exception.getMessage() + "\n\nSQL-Error:\n" + exception.getSqlError(),
                                 QMessageBox::Ok);
    }
}
