#ifndef SOLARSYSTEMMODEL_H
#define SOLARSYSTEMMODEL_H

#include <QWidget>
#include <QItemSelectionModel>

#include "data/solarsystem/solarsystemrepository.h"
#include "model/solarsystem/solarsystemtablemodel.h"
#include "model/heavenlybody/heavenlybodycomboboxmodel.h"
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

#include "data/heavenlybody/heavenlybodyrepository.h"
#include "model/solarsystem/solarsystemheavenlybodytablemodel.h"

/**
    Class to model solarsystems.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class SolarSystemModel : public QWidget
{
    Q_OBJECT

public:
    SolarSystemModel();

    void loadAllSolarSystemEntities();

    void loadOtherEntities();
    void loadEntityData();

    void setSolarSystemSelectionModel(QItemSelectionModel *selectionModel);
    void setSolarSystemHeavenlyBodySelectionModel(QItemSelectionModel *selectionModel);

    SolarSystemTableModel* getSolarSystemTableModel();
    SolarSystemHeavenlyBodyTableModel* getSolarSystemHeavenlyBodyTableModel();

    HeavenlyBodyComboBoxModel* getStarsComboBoxModel();
    HeavenlyBodyComboBoxModel* getPlanetsComboBoxModel();

    SolarSystem* getCurrentSolarSystem() { return currentSolarSystem; }
    SolarSystemHeavenlyBody* getCurrentSolarSystemHeavenlyBody() { return currentSolarSystemHeavenlyBody; }

    void createSolarSystem(QString name, int centralStarIndex);
    void updateSolarSystem(QString name, int centralStarIndex);
    void deleteSolarSystem();

    void addPlanet(int planetIndex, double excentricity, double semimajorAxis, double angle, double orbitalPlaneAngle);
    void updatePlanet(int planetIndex, double excentricity, double semimajorAxis, double angle, double orbitalPlaneAngle);
    void deletePlanet();

    bool isEntitySelected();

    int getSelectedStarIndex();
    int getSelectedHeavenlyBodyIndex();

    void resetSolarSystemEntityData();

private slots:
    void currentSolarSystemRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void currentPlanetsRowChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    SolarSystemRepository *solarSystemRepository;
    HeavenlyBodyRepository *heavenlyBodyRepository;

    SolarSystemTableModel *solarSystemTableModel;
    SolarSystemHeavenlyBodyTableModel *solarSystemHeavenlyBodyTableModel;
    HeavenlyBodyComboBoxModel *starsComboBoxModel;
    HeavenlyBodyComboBoxModel *planetsComboBoxModel;

    QItemSelectionModel *solarSystemSelectionModel;
    QItemSelectionModel *solarSystemHeavenlyBodySelectionModel;

    SolarSystem *currentSolarSystem;
    SolarSystemHeavenlyBody *currentSolarSystemHeavenlyBody;
};

#endif // SOLARSYSTEMMODEL_H
