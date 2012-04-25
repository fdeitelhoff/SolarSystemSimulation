#include "solarsystemheavenlybody.h"

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double excentricity, double semimajorAxis, double angle, double orbitalPlaneAngle)
{
    init(heavenlyBody, excentricity, semimajorAxis, angle, orbitalPlaneAngle);
}

void SolarSystemHeavenlyBody::init(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, int angle, double orbitalPlaneAngle)
{
    setHeavenlyBody(heavenlyBody);
    setNumericExcentricity(numericExcentricity);
    setSemimajorAxis(semimajorAxis);
    setAngle(angle);
    setOrbitalPlaneAngle(orbitalPlaneAngle);
}

void SolarSystemHeavenlyBody::setHeavenlyBody(HeavenlyBody *heavenlyBody)
{
    if (!heavenlyBody)
    {
        throw PropertyNotValidException("HeavenlyBody", "The field '%1' must be a valid HeavenlyBody!");
    }

    this->heavenlyBody = heavenlyBody;
}

void SolarSystemHeavenlyBody::setNumericExcentricity(double numericExcentricity)
{
    if (numericExcentricity < 0 || numericExcentricity > 0.7)
    {
        throw PropertyNotValidException("Excentricity", "The field '%1' has to be between 0 and 0.7!");
    }

    this->numericExcentricity = numericExcentricity;
}

void SolarSystemHeavenlyBody::setSemimajorAxis(double semimajorAxis)
{
    if (semimajorAxis <= 0)
    {
        throw PropertyNotValidException("Semimajor Axis", "The field '%1' has to be larger than 0!");
    }

    this->semimajorAxis = semimajorAxis;
}

void SolarSystemHeavenlyBody::setAngle(double angle)
{
    if (angle < -360 || angle > 360)
    {
        throw PropertyNotValidException("Angle", "The field '%1' has to be between -360 and +360 degrees!");
    }

    this->angle = angle;
}

void SolarSystemHeavenlyBody::setOrbitalPlaneAngle(double orbitalPlaneAngle)
{
    if (orbitalPlaneAngle < -360 || orbitalPlaneAngle > 360)
    {
        throw PropertyNotValidException("OrbitalPlaneAngle", "The field '%1' has to be between -360 and +360 degrees!");
    }

    this->orbitalPlaneAngle = orbitalPlaneAngle;
}
