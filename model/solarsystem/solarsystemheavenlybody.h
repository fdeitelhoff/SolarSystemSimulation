#ifndef SOLARSYSTEMHEAVENLYBODY_H
#define SOLARSYSTEMHEAVENLYBODY_H

#include "model/heavenlybody/heavenlybody.h"

class SolarSystemHeavenlyBody
{

public:
    SolarSystemHeavenlyBody();
    SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, int angle);

    HeavenlyBody* getHeavenlyBody();
    double getNumericExcentricity();
    double getSemimajorAxis();
    int getAngle();

private:
    HeavenlyBody *heavenlyBody;
    double numericExcentricity;
    double semimajorAxis;
    int angle;

};

#endif // SOLARSYSTEMHEAVENLYBODY_H
