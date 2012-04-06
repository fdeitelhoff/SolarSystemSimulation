#ifndef SOLARSYSTEMREPOSITORY_H
#define SOLARSYSTEMREPOSITORY_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "database/postgresqldatabase.h"
#include "model/solarsystem/solarsystem.h"

class SolarSystemRepository
{

public:
    SolarSystemRepository();

    QList<SolarSystem *> fetchAllSolarSystemEntities();

private:
    PostgreSQLDatabase *database;

};

#endif // SOLARSYSTEMREPOSITORY_H
