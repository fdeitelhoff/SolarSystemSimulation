#ifndef SOLARSYSTEMSIMULATION_H
#define SOLARSYSTEMSIMULATION_H

#include "model/solarsystem/solarsystem.h"
#include "visualization/heavenlybody/heavenlybody3d.h"
#include "visualization/heavenlybody/star3d.h"
#include "visualization/heavenlybody/planet3d.h"

class SolarSystemSimulation
{

public:
    SolarSystemSimulation();

    void paintSolarSystem3d();

    void setSolarSystem(SolarSystem *solarSystem);

private:
    QList<HeavenlyBody3d *> heavenlyBodies3d;
};

#endif // SOLARSYSTEMSIMULATION_H