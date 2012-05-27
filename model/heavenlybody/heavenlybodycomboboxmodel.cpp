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

#include "heavenlybodycomboboxmodel.h"

/*!
 \brief Default constructor for the heavenly body combo box, inherit from QAbstractItemModel.

*/
HeavenlyBodyComboBoxModel::HeavenlyBodyComboBoxModel()
    : QAbstractItemModel()
{
}

/*!
 \brief Create index and return it when possible.

 \param row
 \param column
 \param parent
 \return QModelIndex
*/
QModelIndex HeavenlyBodyComboBoxModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( column < 0 || row < 0 )
    {
        return QModelIndex();
    }

    return createIndex(row, column); //, entities.at(row));
}

/*!
 \brief Get complete QModelIndex for index.

 \param index
 \return QModelIndex
*/
QModelIndex HeavenlyBodyComboBoxModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

/*!
 \brief Get the row count of index.

 \param index
 \return int
*/
int HeavenlyBodyComboBoxModel::rowCount(const QModelIndex &index) const
{
    return entities.size();
}

/*!
 \brief Column count is always 1 for index.

 \param index
 \return int
*/
int HeavenlyBodyComboBoxModel::columnCount(const QModelIndex &index) const
{
    return 1;
}

/*!
 \brief Get the name of the heavenly body at the marked row.

 \param index
 \param role
 \return QVariant
*/
QVariant HeavenlyBodyComboBoxModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    return entities.at(index.row())->getName();
}

/*!
 \brief Set entities to combo box.

 \param entities
*/
void HeavenlyBodyComboBoxModel::setData(QList<HeavenlyBody *> entities)
{
    this->entities.clear();
    this->entities.append(entities);

    reset();
}

/*!
 \brief Getter for heavenly body.

 \param index
 \return HeavenlyBody *
*/
HeavenlyBody* HeavenlyBodyComboBoxModel::getHeavenlyBody(int index)
{
    if (index < 0 || index >= entities.size())
    {
        return 0;
    }

    return entities.at(index);
}

/*!
 \brief Get the index of the given heavenly body.

 \param heavenlyBody
 \return int
*/
int HeavenlyBodyComboBoxModel::getHeavenlyBodyIndex(HeavenlyBody *heavenlyBody)
{
    if (!heavenlyBody)
    {
        return -1;
    }

    int row = -1;
    foreach(HeavenlyBody *entity, entities)
    {
        row++;
        if ((*entity) == (*heavenlyBody))
        {
            break;
        }
    }

    return row;
}
