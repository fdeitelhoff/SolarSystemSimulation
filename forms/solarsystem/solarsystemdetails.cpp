#include "solarsystemdetails.h"
#include "ui_solarsystemdetails.h"

SolarSystemDetails::SolarSystemDetails(QWidget *parent, SolarSystemModel *solarSystemModel, bool isEdit) :
    QDialog(parent),
    ui(new Ui::SolarSystemDetails)
{
    ui->setupUi(this);

    this->solarSystemModel = solarSystemModel;

    ui->planetsTableView->setModel(solarSystemModel->getSolarSystemHeavenlyBodyTableModel());
    ui->stars->setModel(solarSystemModel->getStarsComboBoxModel());
    ui->planets->setModel(solarSystemModel->getPlanetsComboBoxModel());

    solarSystemModel->loadOtherEntities();
}

SolarSystemDetails::~SolarSystemDetails()
{
    delete ui;
}

void SolarSystemDetails::on_cancel_clicked()
{
    close();
}

void SolarSystemDetails::on_ok_clicked()
{

}
