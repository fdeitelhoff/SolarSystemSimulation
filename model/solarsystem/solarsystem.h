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
    SolarSystem(qint64 id, QString name, HeavenlyBody *centralStar);

    qint64 getId() { return id; }
    QString getName() { return name; }
    HeavenlyBody* getCentralStar() { return centralStar; }
    int getPlanetCount() { return heavenlyBodies.size(); }

    void addHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

private:
    qint64 id;
    QString name;
    HeavenlyBody *centralStar;
    QList<SolarSystemHeavenlyBody *> heavenlyBodies;
};

#endif // SOLARSYSTEM_H
