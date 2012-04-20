#include "solarsystem.h"

SolarSystem::SolarSystem(QString name, HeavenlyBody *centralStar)
{
    id = -1;

    init(name, centralStar);
}

SolarSystem::SolarSystem(qint64 id, QString name, HeavenlyBody *centralStar)
{
    setId(id);

    init(name, centralStar);
}

void SolarSystem::init(QString name, HeavenlyBody *centralStar)
{
    setName(name);
    setCentralStar(centralStar);
}

void SolarSystem::setId(qint64 id)
{
    if (id < 1)
    {
        throw PropertyNotValidException("ID", "The field '%1' has to be larger than 0!");
    }

    this->id = id;
}

void SolarSystem::setName(QString name)
{
    name = name.trimmed();

    if (name.length() <= 0 || name.length() > 255)
    {
        throw PropertyNotValidException("Name", "The field '%1' has to be between 1 and 255 characters long!");
    }

    this->name = name;
}

void SolarSystem::setCentralStar(HeavenlyBody *centralStar)
{
    if (!centralStar)
    {
        throw PropertyNotValidException("CentralStar", "The field '%1' must be a valid central star!");
    }

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
