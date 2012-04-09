#include "solarsystem.h"

SolarSystem::SolarSystem()
{
}

SolarSystem::SolarSystem(qint64 id, QString name, HeavenlyBody *centralStar)
{
    this->id = id;
    this->name = name;
    this->centralStar = centralStar;
}

SolarSystem::SolarSystem(QString name, HeavenlyBody *centralStar)
{
    this->name = name;
    this->centralStar = centralStar;
}


void SolarSystem::addHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (solarSystemHeavenlyBody)
    {
        heavenlyBodies.append(solarSystemHeavenlyBody);
    }
}

void SolarSystem::removeHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (solarSystemHeavenlyBody)
    {
        heavenlyBodies.removeOne(solarSystemHeavenlyBody);
    }
}
