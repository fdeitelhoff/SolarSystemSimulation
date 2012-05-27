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

#include "environment.h"

/*!
 \brief Default constructor set the color matrix for the coordinate axes.

*/
Environment::Environment()
{
    colors.resize(6);

    // red. GLfloat r, GLfloat g, GLfloat b, GLfloat a =1.0
    colors[0] = GLColorRGBA(1.0, 0.0, 0.0, 1.0);
    colors[1] = GLColorRGBA(1.0, 0.0, 0.0, 1.0);

    // green.
    colors[2] = GLColorRGBA(0.0, 1.0, 0.0, 1.0);
    colors[3] = GLColorRGBA(0.0, 1.0, 0.0, 1.0);

    // blue.
    colors[4] = GLColorRGBA(0.0, 0.0, 1.0, 1.0);
    colors[5] = GLColorRGBA(0.0, 0.0, 1.0, 1.0);

    areCoordinateAxesVisible = false;
}

/*!
 \brief Draw axes if requested.

 \param axisLength
*/
void Environment::drawAxes(GLdouble axisLength)
{
    if (areCoordinateAxesVisible)
    {
        QVector <GLVector> points(6);

        points[0] = GLVector(-axisLength,0.0,0.0);
        points[1] = GLVector(axisLength,0.0,0.0);
        points[2] = GLVector(0.0,-axisLength, 0.0);
        points[3] = GLVector(0.0,axisLength,0.0);
        points[4] = GLVector(0.0,0.0,-axisLength);
        points[5] = GLVector(0.0,0.0,axisLength);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, sizeof(GLVector), points[0].dv());

        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, sizeof(GLColorRGBA), colors[0].fv());

        glDrawArrays(GL_LINES, 0, 6);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

/*!
 \brief Toggel visability of coordinate axes.

*/
void Environment::toggleCoordinateAxesVisibility()
{
    areCoordinateAxesVisible = !areCoordinateAxesVisible;
}
