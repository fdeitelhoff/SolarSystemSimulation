#include "light.h"

Light::Light()
{
    lightNumber = GL_LIGHT0;

    // The first three are the coordinates (x, y, z).
    // The second one is w (w=1 positional light, w=0 directional light).
    lightPosition[0] = 0;
    lightPosition[1] = 0;
    lightPosition[2] = 0;
    lightPosition[3] = 1;
}

void Light::enable()
{
    glEnable(GL_LIGHTING);
    glEnable(lightNumber);

    glLightfv(lightNumber, GL_AMBIENT, GLColorRGBA(cl_White * 0.4).fv());
    glLightfv(lightNumber, GL_DIFFUSE, cl_White.fv());
    glLightfv(lightNumber, GL_SPECULAR, cl_White.fv());

    glLightfv(lightNumber, GL_POSITION, lightPosition);
    glLightf(lightNumber, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(lightNumber, GL_LINEAR_ATTENUATION, 0.00001);
    glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, 0.00004);

    glMaterialfv(GL_FRONT, GL_SPECULAR, cl_White.fv());
}

void Light::disable()
{
    glDisable(GL_LIGHTING);
}
