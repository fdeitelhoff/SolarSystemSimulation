#include "heavenlybodydetails.h"
#include "ui_heavenlybodydetails.h"

HeavenlyBodyDetails::HeavenlyBodyDetails(QWidget *parent, HeavenlyBodyModel *heavenlyBodyModel, bool isEdit) :
    QDialog(parent),
    ui(new Ui::HeavenlyBodyDetails)
{
    ui->setupUi(this);

    this->isEdit = isEdit;

    this->heavenlyBodyModel = heavenlyBodyModel;

    tmpColor = Qt::green;

    colorDialog = new QColorDialog(this);

    if (isEdit)
    {
        currentEntity = heavenlyBodyModel->getSelectedEntity();

        setWindowTitle(QString("Edit Heavenly Body '%1'").arg(currentEntity->getName()));

        ui->name->setText(currentEntity->getName());
        ui->diameter->setText(QString::number(currentEntity->getDiameter()));

        tmpColor = currentEntity->getColor();

        if (currentEntity->getType() == "S")
        {
            ui->star->setChecked(true);
        }
    }

    // Maybe StyleSheets are a better solution here?
    QPalette palette = ui->colorLabel->palette();
    palette.setColor(ui->colorLabel->backgroundRole(), tmpColor);
    ui->colorLabel->setPalette(palette);
}

HeavenlyBodyDetails::~HeavenlyBodyDetails()
{
    delete ui;
}

void HeavenlyBodyDetails::on_cancel_clicked()
{
    close();
}

void HeavenlyBodyDetails::on_chooseColor_clicked()
{
    colorDialog->setCurrentColor(tmpColor);

    if (colorDialog->exec() == QDialog::Accepted)
    {
        tmpColor = colorDialog->currentColor();

        QPalette palette = ui->colorLabel->palette();
        palette.setColor(QPalette::Background, tmpColor);
        ui->colorLabel->setPalette(palette);
    }
}

void HeavenlyBodyDetails::on_ok_clicked()
{
    // Put this into a method of class HeavenlyBodyModel(?)
    if (!isEdit)
    {
        currentEntity = new HeavenlyBody();
    }

    currentEntity->setName(ui->name->text());
    currentEntity->setDiameter(ui->diameter->text().toInt());
    currentEntity->setColor(tmpColor);
    currentEntity->setType(ui->planet->isChecked() ? "P" : "S");

    if (isEdit)
    {
        heavenlyBodyModel->updateEntity(currentEntity);
    }
    else
    {
        heavenlyBodyModel->addEntity(currentEntity);
    }

    close();
}
