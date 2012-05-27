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

#ifndef HEAVENLYBODYCOMBOBOXMODEL_H
#define HEAVENLYBODYCOMBOBOXMODEL_H

#include <QDebug>
#include <QAbstractItemModel>

#include "model/heavenlybody/heavenlybody.h"

/**
    Class for the model of heavenly body combo box.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class HeavenlyBodyComboBoxModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    HeavenlyBodyComboBoxModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &index = QModelIndex()) const;
    int columnCount(const QModelIndex &index = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setData(QList<HeavenlyBody *> entities);

    HeavenlyBody* getHeavenlyBody(int index);
    int getHeavenlyBodyIndex(HeavenlyBody *heavenlyBody);

private:
    QList<HeavenlyBody *> entities;
};

#endif // HEAVENLYBODYCOMBOBOXMODEL_H
