#ifndef SOLARSYSTEMHEAVENLYBODY_H
#define SOLARSYSTEMHEAVENLYBODY_H

#include "model/heavenlybody/heavenlybody.h"

class SolarSystemHeavenlyBody
{

public:
    SolarSystemHeavenlyBody();
    SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis);

    HeavenlyBody* getHeavenlyBody();
    double getNumericExcentricity();
    double getSemimajorAxis();

private:
    HeavenlyBody *heavenlyBody;
    double numericExcentricity;
    double semimajorAxis;

};

#endif // SOLARSYSTEMHEAVENLYBODY_H
