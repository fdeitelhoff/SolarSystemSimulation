#ifndef HEAVENLYBODY_H
#define HEAVENLYBODY_H

#include <QString>
#include <QColor>

class HeavenlyBody
{

public:
    HeavenlyBody();
    HeavenlyBody(qint64 id, QString name, int diameter, QColor color, QString type);
    HeavenlyBody(qint64 id, QString name, int diameter, QString colorString, QString type);

    qint64 getId() { return id; }
    QString getName() { return name; }
    int getDiameter() { return diameter; }
    QColor getColor() { return color; }
    QString getType() { return type; }

    void setId(qint64 id) { this->id = id; }
    void setName(QString name) { this->name = name; }
    void setDiameter(int diameter) { this->diameter = diameter; }
    void setColor(QColor color) { this->color = color; }
    void setType(QString type) { this->type = type; }

private:
    qint64 id;
    QString name;
    int diameter;
    QColor color;
    QString type;
};

#endif // HEAVENLYBODY_H
