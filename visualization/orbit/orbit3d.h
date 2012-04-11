#ifndef ORBIT3D_H
#define ORBIT3D_H

#include "OpenGL/glcolorrgba.h"
#include <math.h>

class Orbit3d
{

public:
    Orbit3d(GLColorRGBA color);

    void paintOrbit3d(float a, float b, float e);

    void drawEllipse(float a, float b, float e);

private:
    GLColorRGBA color;

};

#endif // ORBIT3D_H
