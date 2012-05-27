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

#include "heavenlybody3d.h"

/*!
 \brief Init the 3d objects.

 \param heavenlyBody
*/
HeavenlyBody3d::HeavenlyBody3d(HeavenlyBody *heavenlyBody)
{
    name = heavenlyBody->getName();

    color = GLColorRGBA(heavenlyBody->getColor().redF(),
                        heavenlyBody->getColor().greenF(),
                        heavenlyBody->getColor().blueF(),
                        heavenlyBody->getColor().alphaF());

    radius = GLdouble((heavenlyBody->getDiameter() / 2.0) / 3000.0);

    x = 0;
    y = 0;
}

/*!
 \brief Paint the heavebly bodies.

*/
void HeavenlyBody3d::paintHeavenlyBody3d()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color.fv());
    glMateriali(GL_FRONT, GL_SHININESS, 100);

    glutSolidSphere(radius, 32, 32);
}

/*!
 \brief Calculate the heavenly bodies.

*/
void HeavenlyBody3d::calculateHeavenlyBody3d()
{ }

/*!
 \brief Set or unset orbit visible.

 \param orbitVisisble
*/
void HeavenlyBody3d::setOrbitVisisble(bool orbitVisisble)
{
    this->orbitVisisble = orbitVisisble;
}

/*!
 \brief Get state of orbit visible.

 \return bool
*/
bool HeavenlyBody3d::isOrbitVisisble()
{
    return orbitVisisble;
}

/*!
 \brief Get the radius of the heavenly body 3d.

 \return double
*/
double HeavenlyBody3d::getRadius()
{
    return radius;
}

/*!
 \brief get the center of the heavenly body 3d.

 \return GLVector
*/
GLVector HeavenlyBody3d::getCenter()
{
    return heavenlyBodyCenter;
}

/*!
 \brief Get the name of the heavenly body 3d

 \return QString
*/
QString HeavenlyBody3d::getName()
{
    return name;
}

/*!
 \brief Calculate the distance between the given heavenly body 3d and the current.

 \param heavenlyBody3d
 \return double
*/
double HeavenlyBody3d::calculateDistance(HeavenlyBody3d *heavenlyBody3d)
{
    double x = pow(heavenlyBody3d->getCenter().x() - getCenter().x(), 2);
    double y = pow(heavenlyBody3d->getCenter().y() - getCenter().y(), 2);
    double z = pow(heavenlyBody3d->getCenter().z() - getCenter().z(), 2);

    return sqrt(x + y + z);
}
