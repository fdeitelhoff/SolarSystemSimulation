#include "solarsystemsimulation.h"

SolarSystemSimulation::SolarSystemSimulation()
{
    heavenlyBodies3d = QList<HeavenlyBody3d *>();
}

void SolarSystemSimulation::setSolarSystem(SolarSystem *solarSystem)
{
    heavenlyBodies3d.clear();

    const float keplerConstant = 160;

    // Add the star.
    heavenlyBodies3d.append(new Star3d(solarSystem->getCentralStar()));

    // Add the planet(s).
    SolarSystemHeavenlyBody *solarSystemHeavenlyBody;
    foreach (solarSystemHeavenlyBody, solarSystem->getHeavenlyBodies())
    {
        heavenlyBodies3d.append(new Planet3d(solarSystemHeavenlyBody, keplerConstant));
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
