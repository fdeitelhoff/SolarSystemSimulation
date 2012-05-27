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

#ifndef SOLARSYSTEMHEAVENLYBODY_H
#define SOLARSYSTEMHEAVENLYBODY_H

#include "model/heavenlybody/heavenlybody.h"
#include "model/exceptions/propertynotvalidexception.h"

/**
    Class to model a heavenly body in a solar system.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/


class SolarSystemHeavenlyBody
{

public:
    SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, double angle, double orbitalPlaneAngle);

    /*!
     \brief Getter for the heavenly body.

     \return HeavenlyBody *
    */
    HeavenlyBody* getHeavenlyBody() { return heavenlyBody; }

    /*!
     \brief Getter for the numeric excentricity.

     \return double
    */
    double getNumericExcentricity() { return numericExcentricity; }

    /*!
     \brief Getter for the semimajor axis.

     \return double
    */
    double getSemimajorAxis() { return semimajorAxis; }

    /*!
     \brief Getter for the angle.

     \return double
    */
    double getAngle() { return angle; }

    /*!
     \brief Getter for the orbital plane angle.

     \return double
    */
    double getOrbitalPlaneAngle() { return orbitalPlaneAngle; }

    void setHeavenlyBody(HeavenlyBody *heavenlyBody);
    void setNumericExcentricity(double numericExcentricity);
    void setSemimajorAxis(double semimajorAxis);
    void setAngle(double angle);
    void setOrbitalPlaneAngle(double orbitalPlaneAngle);

    bool operator==(const SolarSystemHeavenlyBody &solarSystemHeavenlyBody);

private:
    HeavenlyBody *heavenlyBody;
    double numericExcentricity;
    double semimajorAxis;
    int angle;
    double orbitalPlaneAngle;

    void init(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, int angle, double orbitalPlaneAngle);
};

#endif // SOLARSYSTEMHEAVENLYBODY_H
