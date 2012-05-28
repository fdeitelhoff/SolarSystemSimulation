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

#include "solarsystemdetails.h"
#include "ui_solarsystemdetails.h"

/*!
 \brief Class to show the window for solar systems.

 \param parent Parent widget.
 \param solarSystemModel Model of the solar systems.
 \param isEdit Is edit or add.
*/
SolarSystemDetails::SolarSystemDetails(QWidget *parent, SolarSystemModel *solarSystemModel, bool isEdit) :
    QDialog(parent),
    ui(new Ui::SolarSystemDetails)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint);

    QObject::connect(ui->stars,
                     SIGNAL(currentIndexChanged(int)),
                     this,
                     SLOT(starSelected(int)),
                     Qt::DirectConnection);

    this->solarSystemModel = solarSystemModel;

    this->isEdit = isEdit;

    ui->planetsTableView->setModel(solarSystemModel->getSolarSystemHeavenlyBodyTableModel());
    ui->stars->setModel(solarSystemModel->getStarsComboBoxModel());
    ui->planets->setModel(solarSystemModel->getPlanetsComboBoxModel());

    solarSystemModel->setSolarSystemHeavenlyBodySelectionModel(ui->planetsTableView->selectionModel());

    connect(ui->planetsTableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this,
            SLOT(currentPlanetsRowChanged(QModelIndex,QModelIndex)),
            Qt::DirectConnection);

    if (solarSystemModel->getStarsComboBoxModel()->rowCount() > 0)
    {
        ui->stars->setCurrentIndex(0);
    }

    solarSystemModel->resetSolarSystemEntityData();

    if (isEdit)
    {
        ui->name->setText(solarSystemModel->getCurrentSolarSystem()->getName());

        solarSystemModel->loadEntityData();

        setPlanetManagementActive(true);

        setWindowTitle(QString("Edit Solar System '%1'").arg(solarSystemModel->getCurrentSolarSystem()->getName()));

        ui->stars->setCurrentIndex(solarSystemModel->getSelectedStarIndex());
    }

    QObject::connect(ui->planetsTableView->selectionModel(),
                     SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,
                     SLOT(selectionChanged(QItemSelection,QItemSelection)),
                     Qt::DirectConnection);

    if (solarSystemModel->getPlanetsComboBoxModel()->rowCount() > 0)
    {
        ui->planets->setCurrentIndex(0);
    }

    isExenctricityValueChangedActive = true;

    ui->planetsTableView->setItemDelegate(new SolarSystemItemDelegate(solarSystemModel));

    ui->planetsTableView->setColumnWidth(0, 50);
}

/*!
 \brief Delete the window.

*/
SolarSystemDetails::~SolarSystemDetails()
{
    delete ui;
}

/*!
 \brief Take over the data for the current heavenly body.

 \param current
 \param previous
*/
void SolarSystemDetails::currentPlanetsRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    SolarSystemHeavenlyBody *solarSystemHeavenlyBody = solarSystemModel->getCurrentSolarSystemHeavenlyBody();

    if (solarSystemHeavenlyBody)
    {
        ui->planets->setCurrentIndex(solarSystemModel->getSelectedHeavenlyBodyIndex());
        ui->excentricity->setValue(solarSystemHeavenlyBody->getNumericExcentricity() * 100);
        ui->excentricityEdit->setText(QString::number(solarSystemHeavenlyBody->getNumericExcentricity()));
        ui->semimajorAxis->setText(QString::number(solarSystemHeavenlyBody->getSemimajorAxis()));
        ui->angle->setText(QString::number(solarSystemHeavenlyBody->getAngle()));
        ui->orbitalPlaneAngle->setText(QString::number(solarSystemHeavenlyBody->getOrbitalPlaneAngle()));
    }
}

/*!
 \brief Enable or disable the buttons for delete and edit.

 \param selected
 \param deselected
*/
void SolarSystemDetails::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    ui->deletePlanet->setEnabled(selected.size() == 1);
    ui->editPlanet->setEnabled(selected.size() == 1);
}

/*!
 \brief Activate the planet management.

 \param isActive
*/
void SolarSystemDetails::setPlanetManagementActive(bool isActive)
{
    ui->planetsTableView->setEnabled(isActive);
    ui->planets->setEnabled(isActive);
    ui->excentricity->setEnabled(isActive);
    ui->excentricityEdit->setEnabled(isActive);
    ui->semimajorAxis->setEnabled(isActive);
    ui->angle->setEnabled(isActive);
    ui->orbitalPlaneAngle->setEnabled(isActive);
    ui->addPlanet->setEnabled(isActive);
}

/*!
 \brief Set the star and sho its diameter.

 \param index
*/
void SolarSystemDetails::starSelected(int index)
{
    HeavenlyBody *heavenlyBody = solarSystemModel->getStarsComboBoxModel()->getHeavenlyBody(index);

    if (heavenlyBody)
    {
        ui->diameterLabel->setText(QString("Diameter: %L1").arg(heavenlyBody->getDiameter()));

        QPalette palette = ui->colorLabel->palette();
        palette.setColor(QPalette::Background, heavenlyBody->getColor());
        ui->colorLabel->setPalette(palette);
    }
}

/*!
 \brief Connect text field and slider.

*/
void SolarSystemDetails::on_excentricityEdit_textChanged()
{
    isExenctricityValueChangedActive = false;

    bool ok = true;
    double currentExcentricity = ui->excentricityEdit->text().toDouble(&ok);

    if (ok)
    {
        ui->excentricity->setValue(currentExcentricity * 100);
    }

    isExenctricityValueChangedActive = true;
}

/*!
 \brief Connect slider and text field.

*/
void SolarSystemDetails::on_excentricity_valueChanged()
{
    if (isExenctricityValueChangedActive)
    {
        ui->excentricityEdit->setText(QString::number(ui->excentricity->value() / 100.0));
    }
}

/*!
 \brief Close the Window when cancel is clicked

*/
void SolarSystemDetails::on_cancel_clicked()
{
    close();
}

/*!
 \brief When accept clicked successfully enable planet management.

*/
void SolarSystemDetails::on_accept_clicked()
{
    if (updateOrCreateSolarSystem())
    {
        setPlanetManagementActive(true);

        isEdit = true;
    }
}

/*!
 \brief Save the data and close the window.

*/
void SolarSystemDetails::on_ok_clicked()
{
    if (updateOrCreateSolarSystem())
    {
        close();
    }
}

/*!
 \brief Take over the fields data to the model.

 \return bool
*/
bool SolarSystemDetails::updateOrCreateSolarSystem()
{
    bool ok = true;

    try
    {
        if (!isEdit)
        {
            solarSystemModel->createSolarSystem(ui->name->text(), ui->stars->currentIndex());
        }
        else
        {
            solarSystemModel->updateSolarSystem(ui->name->text(), ui->stars->currentIndex());
        }
    }
    catch (const PropertyNotValidException &notValidException)
    {
        ok = false;

        QMessageBox::critical(this,
                              QString("The field '%1' is not valid").arg(notValidException.getProperty()),
                              notValidException.getMessage(),
                              QMessageBox::Ok);
    }
    catch (const EntityNotUniqueException &notUniqueException)
    {
        ok = false;

        QMessageBox::critical(this,
                              "Not unique",
                              notUniqueException.getMessage(),
                              QMessageBox::Ok);
    }
    catch (const SqlQueryException &sqlQueryException)
    {
        ok = false;

        QMessageBox::critical(this,
                              "Database SQL error",
                              QString("There was an error with an SQL statement!\n\nError:\n\n%1").arg(sqlQueryException.getSqlError()),
                              QMessageBox::Ok);
    }

    return ok;
}

/*!
 \brief Take over the fields data to the model.

 \param isUpdate
*/
void SolarSystemDetails::updateOrCreatePlanet(bool isUpdate)
{
    bool ok = true;
    double currentExcentricity = ui->excentricityEdit->text().toDouble(&ok);

    if (!ok)
    {
        currentExcentricity = -1;
    }

    double angle = ui->angle->text().toDouble(&ok);

    if (!ok)
    {
        angle = 500;
    }

    double orbitalPlaneAngle = ui->orbitalPlaneAngle->text().toDouble(&ok);

    if (!ok)
    {
        orbitalPlaneAngle = 500;
    }

    try
    {
        if (isUpdate)
        {
            solarSystemModel->updatePlanet(ui->planets->currentIndex(),
                                           currentExcentricity,
                                           ui->semimajorAxis->text().toDouble(),
                                           angle,
                                           orbitalPlaneAngle);

            ui->planetsTableView->selectRow(solarSystemModel->getSelectedHeavenlyBodyIndex());
        }
        else
        {
            solarSystemModel->addPlanet(ui->planets->currentIndex(),
                                        currentExcentricity,
                                        ui->semimajorAxis->text().toDouble(),
                                        angle,
                                        orbitalPlaneAngle);

            ui->planetsTableView->selectRow(ui->planetsTableView->model()->rowCount() - 1);
        }
    }
    catch (const PropertyNotValidException &notValidException)
    {
        QMessageBox::critical(this,
                              QString("The field '%1' is not valid").arg(notValidException.getProperty()),
                              notValidException.getMessage() + "\n\nThe planet could not be added to the solar system!",
                              QMessageBox::Ok);
    }
    catch (const EntityNotUniqueException &notUniqueException)
    {
        QMessageBox::critical(this,
                              "Not unique",
                              notUniqueException.getMessage(),
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

/*!
 \brief Add the new planet to the model when add clicked.

*/
void SolarSystemDetails::on_addPlanet_clicked()
{
    updateOrCreatePlanet(false);
}

/*!
 \brief Take over the changed data of the planet when edit clicked.

*/
void SolarSystemDetails::on_editPlanet_clicked()
{
    updateOrCreatePlanet(true);
}

/*!
 \brief Delete the current planet, when delete is clicked.

*/
void SolarSystemDetails::on_deletePlanet_clicked()
{
    if (solarSystemModel->getCurrentSolarSystemHeavenlyBody())
    {
        QString name = solarSystemModel->getCurrentSolarSystemHeavenlyBody()->getHeavenlyBody()->getName();

        int result = QMessageBox::question(this,
                                           "Delete Heavenly Body",
                                           QString("Would you like to delete the Heavenly Body '%1'?").arg(name),
                                           QMessageBox::Yes | QMessageBox::No);

        if (result == QMessageBox::Yes)
        {
            solarSystemModel->deletePlanet();
        }
    }
}
