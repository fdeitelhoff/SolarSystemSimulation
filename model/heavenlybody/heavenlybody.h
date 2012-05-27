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

#ifndef HEAVENLYBODY_H
#define HEAVENLYBODY_H

#include <QString>
#include <QColor>

#include "model/exceptions/propertynotvalidexception.h"

/**
    Class to model heavebly bodies.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class HeavenlyBody
{

public:
    HeavenlyBody(QString name, int diameter, QColor color, QString type);
    HeavenlyBody(qint64 id, QString name, int diameter, QColor color, QString type);
    HeavenlyBody(qint64 id, QString name, int diameter, QString colorString, QString type);

    void init(QString name, int diameter, QColor color, QString type);

    /*!
     \brief Getter for id.

     \return qint64
    */
    qint64 getId() { return id; }

    /*!
     \brief Getter for the name.

     \return QString
    */
    QString getName() { return name; }

    /*!
     \brief Getter for the diameter.

     \return int
    */
    int getDiameter() { return diameter; }

    /*!
     \brief Getter for the color.

     \return QColor
    */
    QColor getColor() { return color; }

    /*!
     \brief Getter for the type.

     \return QString
    */
    QString getType() { return type; }

    void setId(qint64 id);
    void setName(QString name);
    void setDiameter(int diameter);
    void setColor(QColor color);
    void setType(QString type);

    bool operator==(const HeavenlyBody &heavenlyBody);

private:
    qint64 id;
    QString name;
    int diameter;
    QColor color;
    QString type;
};

#endif // HEAVENLYBODY_H
