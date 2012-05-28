/*
    Copyright (C) 2012 by
    Fabian Deitelhoff (FH@FabianDeitelhoff.de) and
    Christof Geisler (christof.geisler@stud.fh-swf.de)

    This file is part of the project SolarSystemSimulation.

    SolarSystemSimulation is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SolarSystemSimulation is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SolarSystemSimulation.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "solarsystemheavenlybody.h"

/*!
 \brief Constructor for a heavenly body in the solar system.

 \param heavenlyBody
 \param excentricity
 \param semimajorAxis
 \param angle
 \param orbitalPlaneAngle
*/
SolarSystemHeavenlyBody::SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double excentricity, double semimajorAxis, double angle, double orbitalPlaneAngle)
{
    init(heavenlyBody, excentricity, semimajorAxis, angle, orbitalPlaneAngle);
}

/*!
 \brief Init a heavenly body in the solar system.

 \param heavenlyBody
 \param numericExcentricity
 \param semimajorAxis
 \param angle
 \param orbitalPlaneAngle
*/
void SolarSystemHeavenlyBody::init(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, int angle, double orbitalPlaneAngle)
{
    setHeavenlyBody(heavenlyBody);
    setNumericExcentricity(numericExcentricity);
    setSemimajorAxis(semimajorAxis);
    setAngle(angle);
    setOrbitalPlaneAngle(orbitalPlaneAngle);
}

/*!
 \brief Setter for heavenly body in solar system.

 \param heavenlyBody
*/
void SolarSystemHeavenlyBody::setHeavenlyBody(HeavenlyBody *heavenlyBody)
{
    if (!heavenlyBody)
    {
        throw PropertyNotValidException("HeavenlyBody", "The field '%1' must be a valid HeavenlyBody!");
    }

    this->heavenlyBody = heavenlyBody;
}

/*!
 \brief Set the numeric excentricity of the heavenly body in the solar system.

 \param numericExcentricity
*/
void SolarSystemHeavenlyBody::setNumericExcentricity(double numericExcentricity)
{
    if (numericExcentricity < 0 || numericExcentricity > 0.7)
    {
        throw PropertyNotValidException("Excentricity", "The field '%1' has to be between 0 and 0.7!");
    }

    this->numericExcentricity = numericExcentricity;
}

/*!
 \brief Set the semimajor axis of the heavenly body in the solar system.

 \param semimajorAxis
*/
void SolarSystemHeavenlyBody::setSemimajorAxis(double semimajorAxis)
{
    if (semimajorAxis <= 0 || semimajorAxis > 10000)
    {
        throw PropertyNotValidException("Semimajor Axis", "The field '%1' has to be between 0 and 10.000!");
    }

    this->semimajorAxis = semimajorAxis;
}

/*!
 \brief Set the angle of the heavenly body in the solar system.

 \param angle
*/
void SolarSystemHeavenlyBody::setAngle(double angle)
{
    if (angle < -360 || angle > 360)
    {
        throw PropertyNotValidException("Angle", "The field '%1' has to be between -360 and +360 degrees!");
    }

    this->angle = angle;
}

/*!
 \brief Set the orbital plane angle of the heavenly body in the solar system.

 \param orbitalPlaneAngle
*/
void SolarSystemHeavenlyBody::setOrbitalPlaneAngle(double orbitalPlaneAngle)
{
    if (orbitalPlaneAngle < -360 || orbitalPlaneAngle > 360)
    {
        throw PropertyNotValidException("OrbitalPlaneAngle", "The field '%1' has to be between -360 and +360 degrees!");
    }

    this->orbitalPlaneAngle = orbitalPlaneAngle;
}

/*!
 \brief Overload the == operator to compare two heavenly bodies in a solar system.

 \param solarSystemHeavenlyBody
 \return bool SolarSystemHeavenlyBody::operator
*/
bool SolarSystemHeavenlyBody::operator==(const SolarSystemHeavenlyBody &solarSystemHeavenlyBody)
{
    return solarSystemHeavenlyBody.heavenlyBody == getHeavenlyBody()
            && solarSystemHeavenlyBody.numericExcentricity == getNumericExcentricity()
            && solarSystemHeavenlyBody.semimajorAxis == getSemimajorAxis()
            && solarSystemHeavenlyBody.angle == getAngle()
            && solarSystemHeavenlyBody.orbitalPlaneAngle == getOrbitalPlaneAngle();
}
