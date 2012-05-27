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

#ifndef HEAVENLYBODY3D_H
#define HEAVENLYBODY3D_H

#include <QDebug>

#include "model/heavenlybody/heavenlybody.h"
#include "OpenGL/glcolorrgba.h"
#include "OpenGL/GL/glut.h"
#include "OpenGL/glvector.h"

/**
    Class to calculate and paint the heavenly bodies.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class HeavenlyBody3d
{

public:
    HeavenlyBody3d(HeavenlyBody *heavenlyBody);

    virtual void paintHeavenlyBody3d();    
    virtual void calculateHeavenlyBody3d();

    void setOrbitVisisble(bool orbitVisisble);

    double getRadius();
    GLVector getCenter();
    QString getName();
    double calculateDistance(HeavenlyBody3d *heavenlyBody3d);

protected:
    GLColorRGBA color;

    float x;
    float y;

    GLVector heavenlyBodyCenter;

    bool isOrbitVisisble();

private:
    GLdouble radius;
    bool orbitVisisble;
    QString name;
};

#endif // HEAVENLYBODY3D_H
