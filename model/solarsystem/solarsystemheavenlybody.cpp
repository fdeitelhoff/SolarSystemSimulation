#include "solarsystemheavenlybody.h"

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody()
{ }

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double excentricity, double semimajorAxis)
{
    this->heavenlyBody = heavenlyBody;
    this->excentricity = excentricity;
    this->semimajorAxis = semimajorAxis;
}
