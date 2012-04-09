#ifndef SOLARSYSTEMREPOSITORY_H
#define SOLARSYSTEMREPOSITORY_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#include "database/postgresqldatabase.h"
#include "model/solarsystem/solarsystem.h"

class SolarSystemRepository
{

public:
    SolarSystemRepository();

    QList<SolarSystem *> fetchAllSolarSystemEntities();

    void addEntity(SolarSystem *solarSystem);
    void updateEntity(SolarSystem *solarSystem);
    void deleteEntity(SolarSystem *solarSystem);

    void addPlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody);
    void deletePlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

private:
    PostgreSQLDatabase *database;

};

#endif // SOLARSYSTEMREPOSITORY_H
