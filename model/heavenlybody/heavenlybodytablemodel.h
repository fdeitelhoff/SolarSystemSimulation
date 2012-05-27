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

#ifndef HEAVENLYBODYTABLEMODEL_H
#define HEAVENLYBODYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVariant>
#include <QList>
#include <QDebug>

#include "model/heavenlybody/heavenlybody.h"

/**
    Class to model the table of heavenly bodies.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class HeavenlyBodyTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    HeavenlyBodyTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void setData(QList<HeavenlyBody *> entities);

    HeavenlyBody* getHeavenlyBody(int row);

    void addHeavenlyBody(HeavenlyBody *heavenlyBody);

    void removeHeavenlyBody(HeavenlyBody *heavenlyBody);

    /*!
     \brief Getter for entity count.

     \return int
    */
    int getEntityCount() { return entities.size(); }

private:
    QList<HeavenlyBody *> entities;
};

#endif // HEAVENLYBODYTABLEMODEL_H
