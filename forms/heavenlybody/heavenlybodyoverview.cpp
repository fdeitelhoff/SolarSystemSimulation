#include "heavenlybodyoverview.h"
#include "ui_heavenlybodyoverview.h"

HeavenlyBodyOverview::HeavenlyBodyOverview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HeavenlyBodyOverview)
{
    ui->setupUi(this);

    heavenlyBodyModel = new HeavenlyBodyModel();
    heavenlyBodyModel->loadAllHeavenlyBodies();
}

HeavenlyBodyOverview::~HeavenlyBodyOverview()
{
    delete ui;
}
