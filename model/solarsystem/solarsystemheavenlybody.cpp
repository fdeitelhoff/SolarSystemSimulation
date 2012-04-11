#include "solarsystemheavenlybody.h"

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody()
{ }

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double excentricity, double semimajorAxis)
{
    this->heavenlyBody = heavenlyBody;
    this->numericExcentricity = excentricity;
    this->semimajorAxis = semimajorAxis;
}

HeavenlyBody* SolarSystemHeavenlyBody::getHeavenlyBody()
{
    return heavenlyBody;
}

double SolarSystemHeavenlyBody::getNumericExcentricity()
{
    return numericExcentricity;
}

double SolarSystemHeavenlyBody::getSemimajorAxis()
{
    return semimajorAxis;
}
