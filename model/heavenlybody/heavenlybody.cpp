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
