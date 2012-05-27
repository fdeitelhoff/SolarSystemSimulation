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

#include "heavenlybody.h"

/*!
 \brief Constructor for heavenly body with name, diameter, color and type.

 \param name
 \param diameter
 \param color
 \param type
*/
HeavenlyBody::HeavenlyBody(QString name, int diameter, QColor color, QString type)
{
    id = -1;

    init(name, diameter, color, type);
}

/*!
 \brief Constructor for heavenly body with id, name, diameter, color and type.

 \param id
 \param name
 \param diameter
 \param color
 \param type
*/
HeavenlyBody::HeavenlyBody(qint64 id, QString name, int diameter, QColor color, QString type)
{
    setId(id);

    init(name, diameter, color, type);
}

/*!
 \brief Constructor for heavenly body with id, name, diameter, colorString and type.

 \param id
 \param name
 \param diameter
 \param colorString
 \param type
*/
HeavenlyBody::HeavenlyBody(qint64 id, QString name, int diameter, QString colorString, QString type)
{
    QStringList parts = colorString.split(":", QString::SkipEmptyParts);

    if (parts.size() != 4)
    {
        throw PropertyNotValidException("Color", "The field '%1' needs values for RGBA!");
    }

    QColor color;
    color.setRed(parts.at(0).toInt());
    color.setGreen(parts.at(1).toInt());
    color.setBlue(parts.at(2).toInt());
    color.setAlpha(parts.at(3).toInt());

    this->setId(id);

    init(name, diameter, color, type);
}

/*!
 \brief Init the object with name, diameter, color and type.

 \param name
 \param diameter
 \param color
 \param type
*/
void HeavenlyBody::init(QString name, int diameter, QColor color, QString type)
{
    this->setName(name);
    this->setDiameter(diameter);
    this->setColor(color);
    this->setType(type);
}

/*!
 \brief Overload == to compare two heavenly bodies.

 \param heavenlyBody
 \return bool HeavenlyBody::operator
*/
bool HeavenlyBody::operator==(const HeavenlyBody &heavenlyBody)
{
    return id == heavenlyBody.id &&
            name == heavenlyBody.name &&
            diameter == heavenlyBody.diameter &&
            type == heavenlyBody.type;
}

/*!
 \brief Setter for the id.

 \param id
*/
void HeavenlyBody::setId(qint64 id)
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
void HeavenlyBody::setName(QString name)
{
    name = name.trimmed();

    if (name.length() <= 0 || name.length() > 255)
    {
        throw PropertyNotValidException("Name", "The field '%1' has to be between 1 and 255 characters long!");
    }

    this->name = name;
}

/*!
 \brief Setter for the diameter.

 \param diameter
*/
void HeavenlyBody::setDiameter(int diameter)
{
    if (diameter < 1)
    {
        throw PropertyNotValidException("Diameter", "The field '%1' has to be larger than 0!");
    }

    this->diameter = diameter;
}

/*!
 \brief

 \param color Setter for the color.
*/
void HeavenlyBody::setColor(QColor color)
{
    this->color = color;
}

/*!
 \brief Setter for the type.

 \param type
*/
void HeavenlyBody::setType(QString type)
{
    if (type != "S" && type != "P")
    {
        throw PropertyNotValidException("Type", "The field '%1' has to be 'P' (Planet) or 'S' (Star)!");
    }

    this->type = type;
}
