#ifndef SOLARSYSTEMHEAVENLYBODY_H
#define SOLARSYSTEMHEAVENLYBODY_H

#include "model/heavenlybody/heavenlybody.h"
#include "model/exceptions/propertynotvalidexception.h"

class SolarSystemHeavenlyBody
{

public:
    SolarSystemHeavenlyBody(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, double angle, double orbitalPlaneAngle);

    HeavenlyBody* getHeavenlyBody() { return heavenlyBody; }
    double getNumericExcentricity() { return numericExcentricity; }
    double getSemimajorAxis() { return semimajorAxis; }
    double getAngle() { return angle; }
    double getOrbitalPlaneAngle() { return orbitalPlaneAngle; }

    void setHeavenlyBody(HeavenlyBody *heavenlyBody);
    void setNumericExcentricity(double numericExcentricity);
    void setSemimajorAxis(double semimajorAxis);
    void setAngle(double angle);
    void setOrbitalPlaneAngle(double orbitalPlaneAngle);

    bool operator==(const SolarSystemHeavenlyBody &solarSystemHeavenlyBody);

private:
    HeavenlyBody *heavenlyBody;
    double numericExcentricity;
    double semimajorAxis;
    int angle;
    double orbitalPlaneAngle;

    void init(HeavenlyBody *heavenlyBody, double numericExcentricity, double semimajorAxis, int angle, double orbitalPlaneAngle);
};

#endif // SOLARSYSTEMHEAVENLYBODY_H
