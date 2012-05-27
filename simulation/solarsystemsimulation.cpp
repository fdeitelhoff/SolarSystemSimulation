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

#include "solarsystemsimulation.h"

/*!
 \brief Constructor.

*/
SolarSystemSimulation::SolarSystemSimulation()
{
    heavenlyBodies3d = QList<HeavenlyBody3d *>();
}

/*!
 \brief Init the solar system simulation

 \param solarSystem Solar system to simulate.
*/
void SolarSystemSimulation::setSolarSystem(SolarSystem *solarSystem)
{
    name = solarSystem->getName();

    calculationCount = 0;

    heavenlyBodies3d.clear();

    const float keplerConstant = 160;

    maxSemimajorAxis = 0;

    // Add the star.
    heavenlyBodies3d.append(new Star3d(solarSystem->getCentralStar()));

    // Add the planet(s).
    SolarSystemHeavenlyBody *solarSystemHeavenlyBody;
    foreach (solarSystemHeavenlyBody, solarSystem->getHeavenlyBodies())
    {
        heavenlyBodies3d.append(new Planet3d(solarSystemHeavenlyBody, keplerConstant));

        if (solarSystemHeavenlyBody->getSemimajorAxis() > maxSemimajorAxis)
        {
            maxSemimajorAxis = solarSystemHeavenlyBody->getSemimajorAxis();
        }
    }

    if (maxSemimajorAxis < 1)
    {
        maxSemimajorAxis = 1;
    }
}

/*!
 \brief Getter for the name of the solar system.

 \return QString
*/
QString SolarSystemSimulation::getSolarSystemName()
{
    return name;
}

/*!
 \brief Is there at least one heavenly body ?

 \return bool
*/
bool SolarSystemSimulation::isSolarSystemAvailable()
{
    return heavenlyBodies3d.count() > 0;
}

/*!
 \brief Getter maximal semimajor axis. Required to calculate the perspective.

 \return float
*/
float SolarSystemSimulation::getMaxSemimajorAxis()
{
    return maxSemimajorAxis;
}

/*!
 \brief Calculate every heavenly body and detect collisions.

*/
void SolarSystemSimulation::calculateSolarSystem3d()
{
    // Loop through all 3D objects and calculate them.
    HeavenlyBody3d *heavenlyBody3d;
    foreach (heavenlyBody3d, heavenlyBodies3d)
    {
        heavenlyBody3d->calculateHeavenlyBody3d();
    }

    if (calculationCount < 10)
    {
        calculationCount++;
    }

    if (collisionDetection && calculationCount >= 10)
    {
        detectCollisions();
    }
}

/*!
 \brief Switch collision detection.

 \param collisionDetection
*/
void SolarSystemSimulation::setCollisionDetection(bool collisionDetection)
{
    this->collisionDetection = collisionDetection;
}

/*!
 \brief Detect collisions between all heavenly bodies.

*/
void SolarSystemSimulation::detectCollisions()
{
    HeavenlyBody3d *firstHeavenlyBody3d;
    HeavenlyBody3d *secondHeavenlyBody3d;
    double distance;
    foreach (firstHeavenlyBody3d, heavenlyBodies3d)
    {
        foreach (secondHeavenlyBody3d, heavenlyBodies3d)
        {
            if (firstHeavenlyBody3d != secondHeavenlyBody3d)
            {
                distance = firstHeavenlyBody3d->calculateDistance(secondHeavenlyBody3d);

                if (firstHeavenlyBody3d->getRadius() + secondHeavenlyBody3d->getRadius() >= distance)
                {
                    emit collisionDetected(firstHeavenlyBody3d, secondHeavenlyBody3d);
                    return;
                }
            }
        }
    }
}

/*!
 \brief Paint all heavenly bodies.

*/
void SolarSystemSimulation::paintSolarSystem3d()
{
    // Loop through all 3D objects and paint them.
    HeavenlyBody3d *heavenlyBody3d;
    foreach (heavenlyBody3d, heavenlyBodies3d)
    {
        heavenlyBody3d->paintHeavenlyBody3d();
    }
}

/*!
 \brief Set the state of 'orbit visible' to all heavenly body objects.

 \param orbitVisible
*/
void SolarSystemSimulation::setOrbitVisible(bool orbitVisible)
{
    HeavenlyBody3d *heavenlyBody3d;
    foreach (heavenlyBody3d, heavenlyBodies3d)
    {
        heavenlyBody3d->setOrbitVisisble(orbitVisible);
    }
}
