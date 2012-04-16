#ifndef HEAVENLYBODY3D_H
#define HEAVENLYBODY3D_H

#include <QDebug>

#include "model/heavenlybody/heavenlybody.h"
#include "OpenGL/glcolorrgba.h"
#include "OpenGL/gllight.h"
#include "OpenGL/GL/glut.h"

class HeavenlyBody3d
{

public:
    HeavenlyBody3d(HeavenlyBody *heavenlyBody);

    virtual void paintHeavenlyBody3d();    
    virtual void calculateHeavenlyBody3d();

    void setOrbitVisisble(bool orbitVisisble);
    void setKeplerDefault(bool keplerDefault);
    bool isKeplerDefault();
    bool keplerDefault;


    double getRadius();
    GLVector getCenter();
    QString getName();
    double calculateDistance(HeavenlyBody3d *heavenlyBody3d);

protected:
    GLColorRGBA color;

    float x;
    float y;

    bool isOrbitVisisble();

private:
    GLdouble radius;
    bool orbitVisisble;
    QString name;
};

#endif // HEAVENLYBODY3D_H
