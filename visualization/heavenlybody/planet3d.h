#ifndef PLANET3D_H
#define PLANET3D_H

#include <math.h>
#include <QDebug>

#include "visualization/heavenlybody/heavenlybody3d.h"
#include "model/heavenlybody/heavenlybody.h"
#include "model/solarsystem/solarsystemheavenlybody.h"

class Planet3d : public HeavenlyBody3d
{

public:
    Planet3d(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

    void paintHeavenlyBody3d();

    void setCircumstanceTime(float circumstanceTime);

private:
    float a;
    float b;
    float epsilon;
    float e;
    float phi;
    float my;

    float average_speed;
    float circumstance_time;

    void init();

    void drawEllipse(float a, float b, float e);
};

#endif // PLANET3D_H
