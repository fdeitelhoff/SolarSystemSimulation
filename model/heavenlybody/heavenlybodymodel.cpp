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

#include "heavenlybodymodel.h"

/*!
 \brief Class to image the list of heavenly bodies.

*/
HeavenlyBodyModel::HeavenlyBodyModel()
{
    heavenlyBodyRepository = new HeavenlyBodyRepository();

    heavenlyBodyTableModel = 0;
    selectedEntity = 0;
}

/*!
 \brief Load heavenly bodies from repository

*/
void HeavenlyBodyModel::loadAllHeavenlyBodyEntities()
{
    HeavenlyBodyTableModel *heavenlyBodyTableModel = getHeavenlyBodyTableModel();

    QList<HeavenlyBody *> entities = heavenlyBodyRepository->fetchAllHeavenlyBodyEntities();

    heavenlyBodyTableModel->setData(entities);
}

/*!
 \brief Setter for the selection model.

 \param selectionModel
*/
void HeavenlyBodyModel::setSelectionModel(QItemSelectionModel *selectionModel)
{
    this->selectionModel = selectionModel;
    QObject::connect(this->selectionModel,
                     SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                     this,
                     SLOT(currentRowChanged(QModelIndex,QModelIndex)),
                     Qt::DirectConnection);
}

/*!
 \brief Set the entity to the selected row

 \param current
 \param previous
*/
void HeavenlyBodyModel::currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.row() >= 0)
    {
        selectedEntity = heavenlyBodyTableModel->getHeavenlyBody(current.row());
    }
}

/*!
 \brief Getter for the heavenly body table model.

 \return HeavenlyBodyTableModel *
*/
HeavenlyBodyTableModel* HeavenlyBodyModel::getHeavenlyBodyTableModel()
{
    if (!heavenlyBodyTableModel)
    {
        heavenlyBodyTableModel = new HeavenlyBodyTableModel();
    }

    return heavenlyBodyTableModel;
}

/*!
 \brief Update entity in model and repository.

 \param name
 \param diameter
 \param color
 \param type
*/
void HeavenlyBodyModel::updateEntity(QString name, int diameter, QColor color, QString type)
{
    // Create a temporary object first.
    HeavenlyBody *heavenlyBody = new HeavenlyBody(selectedEntity->getId(), name, diameter, color, type);

    heavenlyBodyRepository->updateEntity(heavenlyBody);

    // Update the "real" object when there was no error during the update!
    selectedEntity->setName(name);
    selectedEntity->setDiameter(diameter);
    selectedEntity->setColor(color);
    selectedEntity->setType(type);
}

/*!
 \brief Add entity in model and repository.

 \param name
 \param diameter
 \param color
 \param type
*/
void HeavenlyBodyModel::addEntity(QString name, int diameter, QColor color, QString type)
{
    HeavenlyBody *heavenlyBody = new HeavenlyBody(name, diameter, color, type);

    heavenlyBodyRepository->insertEntity(heavenlyBody);

    heavenlyBodyTableModel->addHeavenlyBody(heavenlyBody);
}

/*!
 \brief Delete entity in model and repository, selected next row.

*/
void HeavenlyBodyModel::deleteEntity()
{
    if (isEntitySelected())
    {
        heavenlyBodyRepository->deleteEntity(selectedEntity);
        heavenlyBodyTableModel->removeHeavenlyBody(selectedEntity);

        if (heavenlyBodyTableModel->getEntityCount() > 0)
        {
            selectedEntity = heavenlyBodyTableModel->getHeavenlyBody(selectionModel->currentIndex().row());
        }
        else
        {
            selectedEntity = 0;
        }
    }
}
