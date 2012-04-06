#ifndef SOLARSYSTEMREPOSITORY_H
#define SOLARSYSTEMREPOSITORY_H

#include "database/postgresqldatabase.h"

class SolarSystemRepository
{

public:
    SolarSystemRepository();

private:
    PostgreSQLDatabase *database;

};

#endif // SOLARSYSTEMREPOSITORY_H
