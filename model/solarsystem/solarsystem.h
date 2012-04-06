#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <QString>

#include "model/heavenlybody/heavenlybody.h"

class SolarSystem
{

public:
    SolarSystem();
    //SolarSystem();

private:
    qint64 id;
    QString name;
    HeavenlyBody *centralStar;

};

#endif // SOLARSYSTEM_H
