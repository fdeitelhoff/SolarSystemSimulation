#include "heavenlybody.h"

HeavenlyBody::HeavenlyBody()
{ }

HeavenlyBody::HeavenlyBody(qint64 id, QString name, int diameter, QColor color, QString type)
{
    this->id = id;
    this->name = name;
    this->diameter = diameter;
    this->color = color;
    this->type = type;
}

HeavenlyBody::HeavenlyBody(qint64 id, QString name, int diameter, QString colorString, QString type)
{
    this->id = id;
    this->name = name;
    this->diameter = diameter;
    this->type = type;

    QColor color;

    QStringList parts = colorString.split(":", QString::SkipEmptyParts);

    color.setRed(parts.at(0).toInt());
    color.setGreen(parts.at(1).toInt());
    color.setBlue(parts.at(2).toInt());
    color.setAlpha(parts.at(3).toInt());

    this->color = color;
}
