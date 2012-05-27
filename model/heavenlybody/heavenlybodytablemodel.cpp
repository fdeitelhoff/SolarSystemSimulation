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

#include "heavenlybodytablemodel.h"

/*!
 \brief Class to image the table of heavenly bodies.

*/
HeavenlyBodyTableModel::HeavenlyBodyTableModel()
    : QAbstractTableModel()
{
}

/*!
 \brief Get the number of rows.

 \param
 \return int
*/
int HeavenlyBodyTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return entities.size();
}

/*!
 \brief The number of columns is alway 5.

 \param
 \return int
*/
int HeavenlyBodyTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 5;
}

/*!
 \brief Get the data for the heavenly table model.

 \param index
 \param role
 \return QVariant
*/
QVariant HeavenlyBodyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    HeavenlyBody *entity = entities.at(index.row());

    if (role == Qt::DisplayRole)
    {
        QVariant value;

        switch (index.column())
        {
        case 0:
            value = QVariant(entity->getId());
            break;
        case 1:
            value = QVariant(entity->getName());
            break;
        case 2:
            value = QVariant(QString("%L1").arg(entity->getDiameter()));
            break;
        case 4:
            value = QVariant(entity->getType());
            break;
        }

        return value;
    }
    else if (role == Qt::BackgroundRole)
    {
        if (index.column() == 3)
        {
            return QVariant(entity->getColor());
        }
        else
        {
            return QVariant(QColor(Qt::white));
        }
    }
    else if (role == Qt::TextAlignmentRole)
    {
        QVariant value;

        switch(index.column())
        {
        case 0:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 2:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 4:
            value = QVariant(Qt::AlignCenter);
            break;
        default:
            value = QVariant(Qt::AlignLeft | Qt::AlignVCenter);
            break;
        }

        return value;
    }
    else
    {
        return QVariant();
    }
}

/*!
 \brief Return header data of the specified column of the table.

 \param section
 \param orientation
 \param role
 \return QVariant
*/
QVariant HeavenlyBodyTableModel::headerData(int section, Qt::Orientation orientation,
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
        columnHeader = "Type";
        break;
    }

    return columnHeader;
}

/*!
 \brief Set the data of the entities.

 \param entities
*/
void HeavenlyBodyTableModel::setData(QList<HeavenlyBody*> entities)
{
    this->entities.clear();
    this->entities.append(entities);

    reset();
}

/*!
 \brief Get heavenly boda of row row.

 \param row
 \return HeavenlyBody *
*/
HeavenlyBody* HeavenlyBodyTableModel::getHeavenlyBody(int row)
{
    if (row >= 0 && row < entities.size())
    {
        return entities.at(row);
    }

    return 0;
}


/*!
 \brief Append heavebly body to the entities.

 \param heavenlyBody
*/
void HeavenlyBodyTableModel::addHeavenlyBody(HeavenlyBody *heavenlyBody)
{
    if (heavenlyBody)
    {
        int size = entities.size() + 1;

        beginInsertRows(QModelIndex(), size, size);
        entities.append(heavenlyBody);
        endInsertRows();
    }
}

/*!
 \brief Remove heavenly body from the entities.

 \param heavenlyBody
*/
void HeavenlyBodyTableModel::removeHeavenlyBody(HeavenlyBody *heavenlyBody)
{
    if (heavenlyBody)
    {
        int size = entities.size() - 1;

        beginRemoveRows(QModelIndex(), size, size);
        entities.removeOne(heavenlyBody);
        endRemoveRows();
    }
}
