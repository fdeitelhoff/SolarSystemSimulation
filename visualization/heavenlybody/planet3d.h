#ifndef PLANET3D_H
#define PLANET3D_H

#include <math.h>
#include <QDebug>

#include "visualization/heavenlybody/heavenlybody3d.h"
#include "visualization/orbit/orbit3d.h"
#include "model/heavenlybody/heavenlybody.h"
#include "model/solarsystem/solarsystemheavenlybody.h"

class Planet3d : public HeavenlyBody3d
{

public:
    Planet3d(SolarSystemHeavenlyBody *solarSystemHeavenlyBody, const float keplerConstant);
    ~Planet3d();

    void paintHeavenlyBody3d();
    void calculateHeavenlyBody3d();

private:
    int orbitAngle;
    int pointsCounter;

    float a;
    float b;
    float epsilon;
    float e;
    double phi;
    float my;

    float averageSpeed;
    float circumstanceTime;

    Orbit3d *orbit3d;

    void init();

    void drawEllipse(float a, float b, float e);

    void setKeplerConstant(const float keplerConstant);

};

#endif // PLANET3D_H
