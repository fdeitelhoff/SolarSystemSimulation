#ifndef SOLARSYSTEMHEAVENLYBODY_H
#define SOLARSYSTEMHEAVENLYBODY_H

#include "model/heavenlybody/heavenlybody.h"
#include "model/exceptions/propertynotvalidexception.h"

class SolarSystemHeavenlyBody
{

public:
    SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, int angle);

    HeavenlyBody* getHeavenlyBody();
    double getNumericExcentricity();
    double getSemimajorAxis();
    int getAngle();

    void setHeavenlyBody(HeavenlyBody *heavenlyBody);
    void setNumericExcentricity(double numericExcentricity);
    void setSemimajorAxis(double semimajorAxis);
    void setAngle(int angle);

private:
    HeavenlyBody *heavenlyBody;
    double numericExcentricity;
    double semimajorAxis;
    int angle;

    void init(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, int angle);
};

#endif // SOLARSYSTEMHEAVENLYBODY_H
