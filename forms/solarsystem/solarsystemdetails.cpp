#include "solarsystemdetails.h"
#include "ui_solarsystemdetails.h"

SolarSystemDetails::SolarSystemDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolarSystemDetails)
{
    ui->setupUi(this);
}

SolarSystemDetails::~SolarSystemDetails()
{
    delete ui;
}
