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

void SolarSystem::addHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (solarSystemHeavenlyBody)
    {
        heavenlyBodies.append(solarSystemHeavenlyBody);
    }
}
