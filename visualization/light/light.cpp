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

#include "light.h"

/*!
 \brief Set the light to the position of the central star.

*/
Light::Light()
{
    lightNumber = GL_LIGHT0;

    // The first three are the coordinates (x, y, z).
    // The fourth one is w (w=1 positional light, w=0 directional light).
    lightPosition[0] = 0;
    lightPosition[1] = 0;
    lightPosition[2] = 0;
    lightPosition[3] = 1;
}

/*!
 \brief Enable lighting scene.

*/
void Light::enable()
{
    glEnable(GL_LIGHTING);
    glEnable(lightNumber);

    glLightfv(lightNumber, GL_AMBIENT, GLColorRGBA(cl_White * 0.4).fv());
    glLightfv(lightNumber, GL_DIFFUSE, cl_White.fv());
    glLightfv(lightNumber, GL_SPECULAR, cl_White.fv());

    glLightfv(lightNumber, GL_POSITION, lightPosition);
    glLightf(lightNumber, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(lightNumber, GL_LINEAR_ATTENUATION, 0.00001);
    glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, 0.00004);

    glMaterialfv(GL_FRONT, GL_SPECULAR, cl_White.fv());
}

/*!
 \brief Disable lighting.

*/
void Light::disable()
{
    glDisable(GL_LIGHTING);
}
