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

#ifndef SOLARSYSTEMREPOSITORY_H
#define SOLARSYSTEMREPOSITORY_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#include "database/postgresqldatabase.h"
#include "model/solarsystem/solarsystem.h"
#include "data/exceptions/sqlqueryexception.h"
#include "data/exceptions/entitynotuniqueexception.h"

/**
    Class for solar system repository.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class SolarSystemRepository
{

public:
    SolarSystemRepository();

    QList<SolarSystem *> fetchAllSolarSystemEntities();

    void insertEntity(SolarSystem *solarSystem);
    void updateEntity(SolarSystem *solarSystem);
    void deleteEntity(SolarSystem *solarSystem);

    void insertPlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody);
    void updatePlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody, SolarSystemHeavenlyBody *oldSolarSystemHeavenlyBody);
    void deletePlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

private:
    PostgreSQLDatabase *database;

    bool isSolarSystemUnique(SolarSystem *solarSystem);
    bool isSolarSystemHeavenlyBodyUnique(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody);
};

#endif // SOLARSYSTEMREPOSITORY_H
