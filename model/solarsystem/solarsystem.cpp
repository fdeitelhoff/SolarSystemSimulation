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

#include "solarsystem.h"

/*!
 \brief Constructor for solar system with name and central star.

 \param name
 \param centralStar
*/
SolarSystem::SolarSystem(QString name, HeavenlyBody *centralStar)
{
    id = -1;

    init(name, centralStar);
}

/*!
 \brief Constructor for solar system with id, name and central star.

 \param id
 \param name
 \param centralStar
*/
SolarSystem::SolarSystem(qint64 id, QString name, HeavenlyBody *centralStar)
{
    setId(id);

    init(name, centralStar);
}

/*!
 \brief Method to init the solar system with a name and a central star.

 \param name
 \param centralStar
*/
void SolarSystem::init(QString name, HeavenlyBody *centralStar)
{
    setName(name);
    setCentralStar(centralStar);
}

/*!
 \brief Setter for the id.

 \param id
*/
void SolarSystem::setId(qint64 id)
{
    if (id < 1)
    {
        throw PropertyNotValidException("ID", "The field '%1' has to be larger than 0!");
    }

    this->id = id;
}

/*!
 \brief Setter for the name.

 \param name
*/
void SolarSystem::setName(QString name)
{
    name = name.trimmed();

    if (name.length() <= 0 || name.length() > 255)
    {
        throw PropertyNotValidException("Name", "The field '%1' has to be between 1 and 255 characters long!");
    }

    this->name = name;
}

/*!
 \brief Setter for the central star.

 \param centralStar
*/
void SolarSystem::setCentralStar(HeavenlyBody *centralStar)
{
    if (!centralStar)
    {
        throw PropertyNotValidException("CentralStar", "The field '%1' must be a valid central star!");
    }

    this->centralStar = centralStar;
}

/*!
 \brief Add a heavenly body to the solar system.

 \param solarSystemHeavenlyBody
*/
void SolarSystem::addHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (solarSystemHeavenlyBody)
    {
        heavenlyBodies.append(solarSystemHeavenlyBody);
    }
}

/*!
 \brief Remove a heavenly body from the solar system.

 \param solarSystemHeavenlyBody
*/
void SolarSystem::removeHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (solarSystemHeavenlyBody)
    {
        heavenlyBodies.removeOne(solarSystemHeavenlyBody);
    }
}
