#include "solarsystemheavenlybody.h"

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody()
{ }

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double excentricity, double semimajorAxis)
{
    this->heavenlyBody = heavenlyBody;
    this->excentricity = excentricity;
    this->semimajorAxis = semimajorAxis;
}

HeavenlyBody* SolarSystemHeavenlyBody::getHeavenlyBody()
{
    return heavenlyBody;
}

double SolarSystemHeavenlyBody::getExcentricity()
{
    return excentricity;
}

double SolarSystemHeavenlyBody::getSemimajorAxis()
{
    return semimajorAxis;
}
