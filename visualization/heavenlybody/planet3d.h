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

#ifndef PLANET3D_H
#define PLANET3D_H

#include <math.h>
#include <QDebug>

#include "visualization/heavenlybody/heavenlybody3d.h"
#include "visualization/orbit/orbit3d.h"
#include "model/heavenlybody/heavenlybody.h"
#include "model/solarsystem/solarsystemheavenlybody.h"

/**
    Class to calculate and paint the planets.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class Planet3d : public HeavenlyBody3d
{

public:
    Planet3d(SolarSystemHeavenlyBody *solarSystemHeavenlyBody, const float keplerConstant);
    ~Planet3d();

    void paintHeavenlyBody3d();
    void calculateHeavenlyBody3d();

private:
    int orbitAngle;
    int orbitalPlaneAngle;
    int pointsCounter;

    float a;
    float b;
    float epsilon;
    float e;
    double phi;
    float mu;

    float averageSpeed;
    float timeOfCirculation;

    Orbit3d *orbit3d;

    void init();

    void drawEllipse(float a, float b, float e);

    void setKeplerConstant(const float keplerConstant);

};

#endif // PLANET3D_H
