#ifndef SOLARSYSTEMSIMULATION_H
#define SOLARSYSTEMSIMULATION_H

#include "model/solarsystem/solarsystem.h"
#include "visualization/heavenlybody/heavenlybody3d.h"
#include "visualization/heavenlybody/star3d.h"
#include "visualization/heavenlybody/planet3d.h"

class SolarSystemSimulation : public QObject
{
    Q_OBJECT

public:
    SolarSystemSimulation();

    void paintSolarSystem3d();
    void calculateSolarSystem3d();

    void setSolarSystem(SolarSystem *solarSystem);

    void setOrbitVisible(bool orbitVisible);
    void setCollisionDetection(bool collisionDetection);
    void setKeplersLawDefault(bool keplerDefault);

    float getMaxSemimajorAxis();

    bool isSolarSystemAvailable();

    QString getSolarSystemName();

private:
    QList<HeavenlyBody3d *> heavenlyBodies3d;

    QString name;
    float maxSemimajorAxis;
    bool collisionDetection;
    int calculationCount;

    void detectCollisions();

signals:
    void collisionDetected(HeavenlyBody3d *firstHeavenlyBody3d, HeavenlyBody3d *secondHeavenlyBody3d);

};

#endif // SOLARSYSTEMSIMULATION_H
