/*
    Copyright (C) 2012 by
    Fabian Deitelhoff (FH@FabianDeitelhoff.de) and
    Christof Geisler (christof.geisler@stud.fh-swf.de)

    This file is part of the project SolarSystemSimulation.

    SolarSystemSimulation is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SolarSystemSimulation is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SolarSystemSimulation.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "heavenlybodydetails.h"
#include "ui_heavenlybodydetails.h"

/*!
 \brief Open dialog window to add or edit a heavenly body.

 \param parent Parent of this dialog.
 \param heavenlyBodyModel Model of the heavenly body table.
 \param isEdit If TRUE edit, else add heavenlybody.
*/
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

/*!
 \brief Destructor to close dialog.

*/
HeavenlyBodyDetails::~HeavenlyBodyDetails()
{
    delete ui;
}

/*!
 \brief Close dialog by signal cancel clicked.

*/
void HeavenlyBodyDetails::on_cancel_clicked()
{
    close();
}

/*!
 \brief Open color chooser, when button clicked.

*/
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

/*!
 \brief Update the model when data is valid.

*/
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
