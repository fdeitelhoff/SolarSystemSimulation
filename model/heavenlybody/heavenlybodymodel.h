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

#ifndef HEAVENLYBODYMODEL_H
#define HEAVENLYBODYMODEL_H

#include <QWidget>
#include <QList>
#include <QItemSelectionModel>
#include <QModelIndex>

#include "data/heavenlybody/heavenlybodyrepository.h"
#include "model/heavenlybody/heavenlybodytablemodel.h"
#include "model/heavenlybody/heavenlybody.h"

/**
    Class to model the list of heavenly bodies.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class HeavenlyBodyModel : public QWidget
{
    Q_OBJECT

public:
    HeavenlyBodyModel();

    void loadAllHeavenlyBodyEntities();

    HeavenlyBodyTableModel* getHeavenlyBodyTableModel();

    void setSelectionModel(QItemSelectionModel *selectionModel);

    HeavenlyBody* getSelectedEntity() { return selectedEntity; }
    bool isEntitySelected() { return selectedEntity != 0; }

    void addEntity(QString name, int diameter, QColor color, QString type);
    void updateEntity(QString name, int diameter, QColor color, QString type);
    void deleteEntity();

private slots:
    void currentRowChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    HeavenlyBodyRepository *heavenlyBodyRepository;
    HeavenlyBodyTableModel *heavenlyBodyTableModel;

    QItemSelectionModel *selectionModel;
    HeavenlyBody *selectedEntity;
};

#endif // HEAVENLYBODYMODEL_H
