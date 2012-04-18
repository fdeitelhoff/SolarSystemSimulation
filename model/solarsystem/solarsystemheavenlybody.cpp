#include "solarsystemheavenlybody.h"

SolarSystemHeavenlyBody::SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double excentricity, double semimajorAxis, int angle)
{
    init(heavenlyBody, excentricity, semimajorAxis, angle);
}

void SolarSystemHeavenlyBody::init(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, int angle)
{
    setHeavenlyBody(heavenlyBody);
    setNumericExcentricity(numericExcentricity);
    setSemimajorAxis(semimajorAxis);
    setAngle(angle);
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

void SolarSystemHeavenlyBody::setAngle(int angle)
{
    if (angle < 0 || angle > 360)
    {
        throw PropertyNotValidException("Angle", "The field '%1' has to be between 0 and 360 degrees!");
    }

    this->angle = angle;
}
