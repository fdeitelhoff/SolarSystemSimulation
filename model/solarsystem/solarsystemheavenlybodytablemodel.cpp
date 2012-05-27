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

#include "solarsystemheavenlybodytablemodel.h"

/*!
 \brief Class to image the solar system table with all heavenly body entities.

*/
SolarSystemHeavenlyBodyTableModel::SolarSystemHeavenlyBodyTableModel()
    : QAbstractTableModel()
{
}

/*!
 \brief Returns the number of rows.

 \param
 \return int
*/
int SolarSystemHeavenlyBodyTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return entities.size();
}

/*!
 \brief The number of columns is alway 8.

 \param
 \return int
*/
int SolarSystemHeavenlyBodyTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 8;
}

/*!
 \brief Reset the model to its original state.

*/
void SolarSystemHeavenlyBodyTableModel::reset()
{
    QAbstractTableModel::reset();
}

/*!
 \brief Clear data and reset.

*/
void SolarSystemHeavenlyBodyTableModel::resetData()
{
    entities.clear();

    reset();
}

/*!
 \brief Set the content, the color and the alignment of the data in the model.

 \param index
 \param role
 \return QVariant
*/
QVariant SolarSystemHeavenlyBodyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    SolarSystemHeavenlyBody *entity = entities.at(index.row());

    if (role == Qt::DisplayRole)
    {
        QVariant value;

        switch (index.column())
        {
        case 0:
            value = QVariant(entity->getHeavenlyBody()->getId());
            break;
        case 1:
            value = QVariant(entity->getHeavenlyBody()->getName());
            break;
        case 2:
            value = QVariant(QString("%L1").arg(entity->getHeavenlyBody()->getDiameter()));
            break;
        case 4:
            value = QVariant(entity->getNumericExcentricity());
            break;
        case 5:
            value = QVariant(entity->getSemimajorAxis());
            break;
        case 6:
            value = QVariant(entity->getAngle());
            break;
        case 7:
            value = QVariant(entity->getOrbitalPlaneAngle());
            break;
        }

        return value;
    }
    else if (role == Qt::TextAlignmentRole)
    {
        QVariant value;

        switch (index.column())
        {
        case 0:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 2:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 4:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 5:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 6:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 7:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        default:
            value = QVariant(Qt::AlignLeft | Qt::AlignVCenter);
            break;
        }

        return value;
    }
    else if (role == Qt::BackgroundRole)
    {
        if (index.column() == 3)
        {
            return QVariant(entity->getHeavenlyBody()->getColor());
        }
        else
        {
            return QVariant(QColor(Qt::white));
        }
    }
    else
    {
        return QVariant();
    }
}

/*!
 \brief Get the Header of the given section.

 \param section
 \param orientation
 \param role
 \return QVariant
*/
QVariant SolarSystemHeavenlyBodyTableModel::headerData(int section, Qt::Orientation orientation,
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
        columnHeader = "Diameter";
        break;
    case 3:
        columnHeader = "Color";
        break;
    case 4:
        columnHeader = "Excentricity";
        break;
    case 5:
        columnHeader = "Semimajor Axis";
        break;
    case 6:
        columnHeader = "Angle";
        break;
    case 7:
        columnHeader = "Orbital Plane Angle";
        break;
    }

    return columnHeader;
}

/*!
 \brief Set the data to the model.

 \param entities
*/
void SolarSystemHeavenlyBodyTableModel::setData(QList<SolarSystemHeavenlyBody *> entities)
{
    this->entities.clear();
    this->entities.append(entities);

    reset();
}

/*!
 \brief Return the data of the given row.

 \param row
 \return SolarSystemHeavenlyBody *
*/
SolarSystemHeavenlyBody* SolarSystemHeavenlyBodyTableModel::getSolarSystemHeavenlyBody(int row)
{
    if (row >= 0 && row < entities.size())
    {
        return entities.at(row);
    }

    return 0;
}

/*!
 \brief Add a heavenly body with corresponding data to the solar system.

 \param solarSystemHeavenlyBody
*/
void SolarSystemHeavenlyBodyTableModel::addSolarSystemHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (solarSystemHeavenlyBody)
    {
        int size = entities.size() + 1;

        beginInsertRows(QModelIndex(), size, size);
        entities.append(solarSystemHeavenlyBody);
        endInsertRows();
    }
}

/*!
 \brief Delete heavenly body and its data from solar system.

 \param solarSystemHeavenlyBody
*/
void SolarSystemHeavenlyBodyTableModel::deleteSolarSystemHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (solarSystemHeavenlyBody)
    {
        int size = entities.size() - 1;

        beginRemoveRows(QModelIndex(), size, size);
        entities.removeOne(solarSystemHeavenlyBody);
        endRemoveRows();
    }
}

/*!
 \brief Get the index of the given heavenly body.

 \param solarSystemHeavenlyBody
 \return int
*/
int SolarSystemHeavenlyBodyTableModel::getSolarSystemHeavenlyBodyIndex(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (!solarSystemHeavenlyBody)
    {
        return -1;
    }

    int row = -1;
    foreach(SolarSystemHeavenlyBody *entity, entities)
    {
        row++;
        if ((*entity) == (*solarSystemHeavenlyBody))
        {
            break;
        }
    }

    return row;
}
