#ifndef LIGHT_H
#define LIGHT_H

#include "OpenGL/glcolorrgba.h"
#include "OpenGL/GL/glut.h"

class Light
{

private:
    int lightNumber;
    GLfloat lightPosition[4];

public:
    Light();

    void enable();
    void disable();
};

#endif // LIGHT_H
