#include "solarsystemrepository.h"

SolarSystemRepository::SolarSystemRepository()
{
    database = PostgreSQLDatabase::getInstance();
}
