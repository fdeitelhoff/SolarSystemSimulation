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

#ifndef SOLARSYSTEMHEAVENLYBODYTABLEMODEL_H
#define SOLARSYSTEMHEAVENLYBODYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVariant>
#include <QList>

#include "model/solarsystem/solarsystemheavenlybody.h"

/**
    Class to model a list of heavenly bodies in a solar system.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/


class SolarSystemHeavenlyBodyTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    SolarSystemHeavenlyBodyTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void setData(QList<SolarSystemHeavenlyBody *> entities);

    void addSolarSystemHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);
    void deleteSolarSystemHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

    SolarSystemHeavenlyBody* getSolarSystemHeavenlyBody(int row);

    /*!
     \brief Getter for the number of entities.

     \return int
    */
    int getEntityCount() { return entities.size(); }

    int getSolarSystemHeavenlyBodyIndex(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

    void reset();

    void resetData();

private:
    QList<SolarSystemHeavenlyBody *> entities;
};

#endif // SOLARSYSTEMHEAVENLYBODYTABLEMODEL_H
