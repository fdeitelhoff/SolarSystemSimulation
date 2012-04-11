#ifndef ORBIT3D_H
#define ORBIT3D_H

#include "OpenGL/glcolorrgba.h"
#include <math.h>
#include <QDebug>

class Orbit3d
{

public:
    Orbit3d(int angle, GLColorRGBA color);

    void paintOrbit3d(float a, float b, float e);

    void drawEllipse(float a, float b, float e);

private:
    int angle;
    GLColorRGBA color;

};

#endif // ORBIT3D_H
