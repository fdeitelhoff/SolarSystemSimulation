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

#include "solarsystemoverview.h"
#include "ui_solarsystemoverview.h"

/*!
 \brief Class to show the window with the table of the solar systems.

 \param parent
 \param solarSystemModel
*/
SolarSystemOverview::SolarSystemOverview(QWidget *parent, SolarSystemModel *solarSystemModel) :
    QDialog(parent),
    ui(new Ui::SolarSystemOverview)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint);

    this->solarSystemModel = solarSystemModel;

    ui->solarSystemTableView->setModel(solarSystemModel->getSolarSystemTableModel());
    solarSystemModel->setSolarSystemSelectionModel(ui->solarSystemTableView->selectionModel());

    solarSystemModel->loadAllSolarSystemEntities();

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

    ui->solarSystemTableView->selectRow(0);
}

/*!
 \brief Delete the window.

*/
SolarSystemOverview::~SolarSystemOverview()
{
    delete ui;
}

/*!
 \brief Make double click the same action than edit clicked.

 \param modelIndex
*/
void SolarSystemOverview::doubleClicked(QModelIndex modelIndex)
{
    on_edit_clicked();
}

/*!
 \brief Set the status of the buttons delete, edit, start simulation

 \param selected
 \param deselected
*/
void SolarSystemOverview::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    ui->edit->setEnabled(selected.size() == 1);
    ui->deleteEntity->setEnabled(selected.size() == 1);
    ui->startSimulation->setEnabled(selected.size() == 1);
}

/*!
 \brief Open solar systems details when add is clicked.

*/
void SolarSystemOverview::on_add_clicked()
{
    showSolarSystemDetails(false);
}

/*!
 \brief Open solar system details with data when edit is clicked.

*/
void SolarSystemOverview::on_edit_clicked()
{
    if (solarSystemModel->isEntitySelected())
    {
        showSolarSystemDetails(true);
    }
}

/*!
 \brief Open the window solar system details.

 \param isEdit
*/
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

/*!
 \brief Delete solar system when delete button is clicked.

*/
void SolarSystemOverview::on_deleteEntity_clicked()
{
    if (solarSystemModel->getCurrentSolarSystem())
    {
        int result = QMessageBox::question(this,
                                           "Delete a Solar System",
                                           QString("Would you like to delete the Solar System '%1'?").arg(solarSystemModel->getCurrentSolarSystem()->getName()),
                                           QMessageBox::Yes | QMessageBox::No,
                                           QMessageBox::No);

        if (result == QMessageBox::Yes)
        {
            solarSystemModel->deleteSolarSystem();
        }
    }
}

/*!
 \brief Close the window solar system overview and start the simulation.

*/
void SolarSystemOverview::on_startSimulation_clicked()
{
    emit simulateSolarSystem(solarSystemModel->getCurrentSolarSystem());

    close();
}
