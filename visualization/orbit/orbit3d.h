#ifndef ORBIT3D_H
#define ORBIT3D_H

#include <math.h>
#include <QDebug>

#include "OpenGL/glcolorrgba.h"
#include "OpenGL/glvector.h"

class Orbit3d
{

public:
    Orbit3d(int angle, GLColorRGBA color, float a, float b, float e);

    void paintOrbit3d();

    void drawEllipse();

private:
    int angle;
    GLColorRGBA color;
    QVector<GLVector> ellipsePoints;

    void calculateEllipse(float a, float b, float e);
};

#endif // ORBIT3D_H
