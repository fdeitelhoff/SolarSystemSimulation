#ifndef HEAVENLYBODYREPOSITORY_H
#define HEAVENLYBODYREPOSITORY_H

#include <QList>
#include <QSqlQuery>
#include "heavenlybody.h"
#include "database/postgresqldatabase.h"

class HeavenlyBodyRepository
{

public:
    HeavenlyBodyRepository();

    QList<HeavenlyBody> fetchAllHeavenlyBodies();

private:
    PostgreSQLDatabase *database;
};

#endif // HEAVENLYBODYREPOSITORY_H
