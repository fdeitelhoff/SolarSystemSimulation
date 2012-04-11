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

protected:
    GLColorRGBA color;

private:
    GLdouble radius;
};

#endif // HEAVENLYBODY3D_H
