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

#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <QString>
#include <QList>

#include "model/heavenlybody/heavenlybody.h"
#include "model/solarsystem/solarsystemheavenlybody.h"
#include "model/exceptions/propertynotvalidexception.h"

/**
    Class to model a solar system.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class SolarSystem
{

public:
    SolarSystem(QString name, HeavenlyBody *centralStar);
    SolarSystem(qint64 id, QString name, HeavenlyBody *centralStar);

    void init(QString name, HeavenlyBody *centralStar);

    /*!
     \brief Getter for the id.

     \return qint64
    */
    qint64 getId() { return id; }

    /*!
     \brief Getter for the name.

     \return QString
    */
    QString getName() { return name; }

    /*!
     \brief Getter for the central star.

     \return HeavenlyBody *
    */
    HeavenlyBody* getCentralStar() { return centralStar; }

    /*!
     \brief Getter for the number of heavenly bodies.

     \return int
    */
    int getPlanetCount() { return heavenlyBodies.size(); }

    /*!
     \brief Getter for the list of heavenly bodies.

     \return QList<SolarSystemHeavenlyBody *>
    */
    QList<SolarSystemHeavenlyBody *> getHeavenlyBodies() { return heavenlyBodies; }

    void setId(qint64 id);
    void setName(QString name);
    void setCentralStar(HeavenlyBody *centralStar);

    void addHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);
    void removeHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

private:
    qint64 id;
    QString name;
    HeavenlyBody *centralStar;
    QList<SolarSystemHeavenlyBody *> heavenlyBodies;
};

#endif // SOLARSYSTEM_H
