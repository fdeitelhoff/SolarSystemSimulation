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

#include "orbit3d.h"

/*!
 \brief Init the orbit with required components.

 \param angle
 \param orbitalPlaneAngle
 \param color
 \param a
 \param b
 \param e
*/
Orbit3d::Orbit3d(double angle, double orbitalPlaneAngle, GLColorRGBA color, float a, float b, float e)
{
    this->angle = angle;
    this->orbitalPlaneAngle = orbitalPlaneAngle;
    this->color = color;

    calculateEllipse(a, b, e);
}

/*!
 \brief Paint the orbit against the given angles.

*/
void Orbit3d::paintOrbit3d()
{
    glPushMatrix();

    glRotatef(orbitalPlaneAngle, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);

    drawEllipse();

    glPopMatrix();
}

/*!
 \brief Calculate the ellipse once,

 \param a
 \param b
 \param e
*/
void Orbit3d::calculateEllipse(float a, float b, float e)
{
    // Pre calculate all ellipse points.
    float x, y;
    for(float t = 0; t <= 2 * M_PI; t += M_PI / 360)
    {
        x = cos(t) * a + e;
        y = sin(t) * b;

        ellipsePoints.append(GLVector(x, y, 0));
    }
}

/*!
 \brief Paint the precalculated ellipse points in line modus.

*/
void Orbit3d::drawEllipse()
{
    glDisable(GL_LIGHTING);

    glColor4f(color.red(), color.green(), color.blue(), color.alpha());

    glBegin(GL_LINE_LOOP);

    // Paint all precalculated ellipse points.
    foreach (GLVector vector, ellipsePoints)
    {
       glVertex3f(vector.x(), vector.y(), vector.z());
    }

    glEnd();

    glEnable(GL_LIGHTING);
}
