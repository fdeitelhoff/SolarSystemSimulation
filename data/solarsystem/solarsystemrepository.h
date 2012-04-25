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

    bool isEntityUnique(SolarSystem *solarSystem);
};

#endif // SOLARSYSTEMREPOSITORY_H
