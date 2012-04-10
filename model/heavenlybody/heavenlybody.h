#ifndef HEAVENLYBODY_H
#define HEAVENLYBODY_H

#include <QString>
#include <QColor>

#include "model/exceptions/propertynotvalidexception.h"

class HeavenlyBody
{

public:
    HeavenlyBody(QString name, int diameter, QColor color, QString type);
    HeavenlyBody(qint64 id, QString name, int diameter, QColor color, QString type);
    HeavenlyBody(qint64 id, QString name, int diameter, QString colorString, QString type);

    void init(QString name, int diameter, QColor color, QString type);

    qint64 getId() { return id; }
    QString getName() { return name; }
    int getDiameter() { return diameter; }
    QColor getColor() { return color; }
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
