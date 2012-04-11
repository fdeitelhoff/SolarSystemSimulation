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

protected:
    GLColorRGBA color;

    bool isOrbitVisisble();

private:
    GLdouble radius;
    bool orbitVisisble;
};

#endif // HEAVENLYBODY3D_H
