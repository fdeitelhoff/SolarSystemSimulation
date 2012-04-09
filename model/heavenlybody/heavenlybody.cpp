#include "heavenlybody.h"

HeavenlyBody::HeavenlyBody(QString name, int diameter, QColor color, QString type)
{
    init(name, diameter, color, type);
}

HeavenlyBody::HeavenlyBody(qint64 id, QString name, int diameter, QColor color, QString type)
{
    this->setId(id);

    init(name, diameter, color, type);
}

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

void HeavenlyBody::init(QString name, int diameter, QColor color, QString type)
{
    this->setName(name);
    this->setDiameter(diameter);
    this->setColor(color);
    this->setType(type);
}

bool HeavenlyBody::operator==(const HeavenlyBody &heavenlyBody)
{
    return id == heavenlyBody.id &&
            name == heavenlyBody.name &&
            diameter == heavenlyBody.diameter &&
            type == heavenlyBody.type;
}

void HeavenlyBody::setId(qint64 id)
{
    if (id < 1)
    {
        throw PropertyNotValidException("ID", "The field '%1' has to be larger than 0!");
    }

    this->id = id;
}

void HeavenlyBody::setName(QString name)
{
    name = name.trimmed();

    if (name.length() <= 0 || name.length() > 255)
    {
        throw PropertyNotValidException("Name", "The field '%1' has to be between 0 and 255 characters long!");
    }

    this->name = name;
}

void HeavenlyBody::setDiameter(int diameter)
{
    if (diameter < 1)
    {
        throw PropertyNotValidException("Diameter", "The field '%1' has to be larger than 0!");
    }

    this->diameter = diameter;
}

void HeavenlyBody::setColor(QColor color)
{
    this->color = color;
}

void HeavenlyBody::setType(QString type)
{
    if (type != "S" && type != "P")
    {
        throw PropertyNotValidException("Type", "The field '%1' has to be 'P' (Planet) or 'S' (Star)!");
    }

    this->type = type;
}
