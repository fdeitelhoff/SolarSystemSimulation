#include "heavenlybodydetails.h"
#include "ui_heavenlybodydetails.h"

HeavenlyBodyDetails::HeavenlyBodyDetails(QWidget *parent, HeavenlyBodyModel *heavenlyBodyModel, bool isEdit) :
    QDialog(parent),
    ui(new Ui::HeavenlyBodyDetails)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);

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
    try
    {
        if (isEdit)
        {
            heavenlyBodyModel->updateEntity(ui->name->text(),
                                            ui->diameter->text().toInt(),
                                            tmpColor,
                                            ui->planet->isChecked() ? "P" : "S");
        }
        else
        {
            heavenlyBodyModel->addEntity(ui->name->text(),
                                         ui->diameter->text().toInt(),
                                         tmpColor,
                                         ui->planet->isChecked() ? "P" : "S");
        }

        close();
    }
    catch (const PropertyNotValidException &notValidException)
    {
        QMessageBox::critical(this,
                              QString("The field '%1' is not valid").arg(notValidException.getProperty()),
                              notValidException.getMessage(),
                              QMessageBox::Ok);
    }
    catch (const EntityNotUniqueException &notUniqueException)
    {
        QMessageBox::critical(this,
                              "Not unique",
                              notUniqueException.getMessage(),
                              QMessageBox::Ok);
    }
    catch (const HeavenlyBodyTypeException &typeException)
    {
        QMessageBox::critical(this,
                              "Type could not changed",
                              typeException.getMessage(),
                              QMessageBox::Ok);
    }
    catch (const SqlQueryException &sqlQueryException)
    {
        QMessageBox::critical(this,
                              "Database SQL error",
                              QString("There was an error with an SQL statement!\n\nError:\n\n%1").arg(sqlQueryException.getSqlError()),
                              QMessageBox::Ok);
    }
}
