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

#include "heavenlybodyoverview.h"
#include "ui_heavenlybodyoverview.h"

/*!
 \brief Open the window of the heanenly body overview.

 \param parent Parent widget of this window.
 \param heavenlyBodyModel Model of the overview.
*/
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

    // Set the ItemDelegate for the custom background selection color.
    ui->heavenlyBodyTableView->setItemDelegate(new HeavenlyBodyItemDelegate(heavenlyBodyModel));

    ui->heavenlyBodyTableView->setColumnWidth(1, 300);

    ui->heavenlyBodyTableView->selectRow(0);
}

/*!
 \brief Delete the heavenly body overview window.

*/
HeavenlyBodyOverview::~HeavenlyBodyOverview()
{
    delete ui;
}

/*!
 \brief Enable double click to select a heavenly body.

 \param modelIndex Locate the data in the model
*/
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

/*!
 \brief Enable edit and delete buttom when row is selected.

 \param selected
 \param deselected
*/
void HeavenlyBodyOverview::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    ui->edit->setEnabled(selected.size() == 1);
    ui->deleteEntity->setEnabled(selected.size() == 1);
}

/*!
 \brief Add a new heavenly body to the model.

*/
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

/*!
 \brief Edit the selected heavenly body from the List.

*/
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

/*!
 \brief Delete the selected heavenly body

*/
void HeavenlyBodyOverview::on_deleteEntity_clicked()
{
    if (heavenlyBodyModel->getSelectedEntity())
    {
        try
        {
            int result = QMessageBox::question(this,
                                               "Delete a Heavenly Body",
                                               QString("Would you like to delete the Heavenly Body '%1'?").arg(heavenlyBodyModel->getSelectedEntity()->getName()),
                                               QMessageBox::Yes | QMessageBox::No,
                                               QMessageBox::No);

            if (result == QMessageBox::Yes)
            {
                heavenlyBodyModel->deleteEntity();
            }
        }
        catch (const DeleteEntityFailedException &exception)
        {
            QString message = exception.getMessage();

            if (exception.getSqlError() != "")
            {
                message += "\n\nSQL-Error:\n" + exception.getSqlError();
            }

            QMessageBox::critical(this,
                                  "Error while deleting",
                                  message,
                                  QMessageBox::Ok);
        }
    }
}
