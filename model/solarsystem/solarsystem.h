#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <QString>
#include <QList>

#include "model/heavenlybody/heavenlybody.h"
#include "model/solarsystem/solarsystemheavenlybody.h"

class SolarSystem
{

public:
    SolarSystem();
    SolarSystem(QString name, HeavenlyBody *centralStar);
    SolarSystem(qint64 id, QString name, HeavenlyBody *centralStar);

    qint64 getId() { return id; }
    QString getName() { return name; }
    HeavenlyBody* getCentralStar() { return centralStar; }
    int getPlanetCount() { return heavenlyBodies.size(); }
    QList<SolarSystemHeavenlyBody *> getHeavenlyBodies() { return heavenlyBodies; }

    void setId(qint64 id) { this->id = id; }
    void setName(QString name) { this->name = name; }
    void setCentralStar(HeavenlyBody *centralStar) { this->centralStar = centralStar; }

    void addHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);
    void removeHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

private:
    qint64 id;
    QString name;
    HeavenlyBody *centralStar;
    QList<SolarSystemHeavenlyBody *> heavenlyBodies;
};

#endif // SOLARSYSTEM_H
