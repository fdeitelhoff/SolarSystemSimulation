#include "solarsystemsimulation.h"

SolarSystemSimulation::SolarSystemSimulation()
{
    heavenlyBodies3d = QList<HeavenlyBody3d *>();
}

void SolarSystemSimulation::setSolarSystem(SolarSystem *solarSystem)
{
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
}

float SolarSystemSimulation::getMaxSemimajorAxis()
{
    return maxSemimajorAxis;
}

void SolarSystemSimulation::calculateSolarSystem3d()
{
    // Loop through all 3D objects and calculate them.
    HeavenlyBody3d *heavenlyBody3d;
    foreach (heavenlyBody3d, heavenlyBodies3d)
    {
        heavenlyBody3d->calculateHeavenlyBody3d();
    }

    if (collisionDectection)
    {
        detectCollisions();
    }
}

void SolarSystemSimulation::activateCollisionDetection(bool active)
{
    collisionDectection = active;
}

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

void SolarSystemSimulation::paintSolarSystem3d()
{
    // Loop through all 3D objects and paint them.
    HeavenlyBody3d *heavenlyBody3d;
    foreach (heavenlyBody3d, heavenlyBodies3d)
    {
        heavenlyBody3d->paintHeavenlyBody3d();
    }
}

void SolarSystemSimulation::setOrbitVisible(bool orbitVisible)
{
    HeavenlyBody3d *heavenlyBody3d;
    foreach (heavenlyBody3d, heavenlyBodies3d)
    {
        heavenlyBody3d->setOrbitVisisble(orbitVisible);
    }
}
