#include "solarsystemsimulation.h"

SolarSystemSimulation::SolarSystemSimulation()
{
    heavenlyBodies3d = QList<HeavenlyBody3d *>();
}

void SolarSystemSimulation::setSolarSystem(SolarSystem *solarSystem)
{
    heavenlyBodies3d.clear();

    // Add the star.
    heavenlyBodies3d.append(new Star3d(solarSystem->getCentralStar()));

    SolarSystemHeavenlyBody *solarSystemHeavenlyBody;
    foreach (solarSystemHeavenlyBody, solarSystem->getHeavenlyBodies())
    {
        heavenlyBodies3d.append(new Planet3d(solarSystemHeavenlyBody));
    }
}

void SolarSystemSimulation::paintSolarSystem3d()
{
    HeavenlyBody3d *heavenlyBody3d;
    foreach (heavenlyBody3d, heavenlyBodies3d)
    {
        heavenlyBody3d->paintHeavenlyBody3d();
    }
}
