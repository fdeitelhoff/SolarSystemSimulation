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

#include "solarsystemtablemodel.h"

/*!
 \brief Default constructor.

*/
SolarSystemTableModel::SolarSystemTableModel()
    : QAbstractTableModel()
{
}

/*!
 \brief Returns the number of rows.

 \param
 \return int
*/
int SolarSystemTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return entities.size();
}

/*!
 \brief The column count is alway 4.

 \param
 \return int
*/
int SolarSystemTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

/*!
 \brief Returns the report of the index in case of the role.

 \param index
 \param role
 \return QVariant
*/
QVariant SolarSystemTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    SolarSystem *entity = entities.at(index.row());
    QVariant value;

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            value = QVariant(entity->getId());
            break;
        case 1:
            value = QVariant(entity->getName());
            break;
        case 2:
            value = QVariant(entity->getCentralStar()->getName());
            break;
        case 3:
            value = QVariant(entity->getPlanetCount());
            break;
        }
    }
    else if (role == Qt::TextAlignmentRole)
    {
        if (index.column() == 0 || index.column() == 3)
        {
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
        }
        else
        {
            value = QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    return value;
}

/*!
 \brief Returns the header of the given column.

 \param section
 \param orientation
 \param role
 \return QVariant
*/
QVariant SolarSystemTableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
    {
        return QVariant();
    }

    QString columnHeader;

    switch (section)
    {
    case 0:
        columnHeader = "ID";
        break;
    case 1:
        columnHeader = "Name";
        break;
    case 2:
        columnHeader = "Central Star";
        break;
    case 3:
        columnHeader = "Planet count";
        break;
    }

    return columnHeader;
}

/*!
 \brief Set the table data with the given entities.

 \param entities
*/
void SolarSystemTableModel::setData(QList<SolarSystem *> entities)
{
    this->entities.clear();
    this->entities.append(entities);

    reset();
}

/*!
 \brief Returns the entities at row.

 \param row
 \return SolarSystem *
*/
SolarSystem* SolarSystemTableModel::getSolarSystem(int row)
{
    if (row >= 0 && row < entities.size())
    {
        return entities.at(row);
    }

    return 0;
}

/*!
 \brief Add a solar system to the list.

 \param solarSystem
*/
void SolarSystemTableModel::addSolarSystem(SolarSystem *solarSystem)
{
    if (solarSystem)
    {
        int size = entities.size() + 1;

        beginInsertRows(QModelIndex(), size, size);
        entities.append(solarSystem);
        endInsertRows();
    }
}

/*!
 \brief Remove solar system from list.

 \param solarSystem
*/
void SolarSystemTableModel::deleteSolarSystem(SolarSystem *solarSystem)
{
    if (solarSystem)
    {
        int size = entities.size() - 1;

        beginRemoveRows(QModelIndex(), size, size);
        entities.removeOne(solarSystem);
        endRemoveRows();
    }
}

/*!
 \brief Returns number of solar systems in the list.

 \return int
*/
int SolarSystemTableModel::getEntityCount()
{
    return entities.size();
}
