#include "solarsystemheavenlybody.h"

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody()
{ }

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double excentricity, double semimajorAxis, int angle)
{
    this->heavenlyBody = heavenlyBody;
    this->numericExcentricity = excentricity;
    this->semimajorAxis = semimajorAxis;
    this->angle = angle;
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

int SolarSystemHeavenlyBody::getAngle()
{
    return angle;
}
