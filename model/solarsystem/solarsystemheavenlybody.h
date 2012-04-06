#ifndef SOLARSYSTEMHEAVENLYBODY_H
#define SOLARSYSTEMHEAVENLYBODY_H

#include "model/heavenlybody/heavenlybody.h"

class SolarSystemHeavenlyBody
{

public:
    SolarSystemHeavenlyBody();
    SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double excentricity, double semimajorAxis);

    HeavenlyBody* getHeavenlyBody();
    double getExcentricity();
    double getSemimajorAxis();

private:
    HeavenlyBody *heavenlyBody;
    double excentricity;
    double semimajorAxis;

};

#endif // SOLARSYSTEMHEAVENLYBODY_H
