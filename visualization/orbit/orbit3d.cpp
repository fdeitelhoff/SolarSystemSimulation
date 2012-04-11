#include "orbit3d.h"

Orbit3d::Orbit3d(GLColorRGBA color)
{
    this->color = color;
}

void Orbit3d::paintOrbit3d(float a, float b, float e)
{
    glPushMatrix();
    glRotatef(45.0, 0.0, 0.0, 1.0);
    drawEllipse(a, b, e);
    glPopMatrix();
}

void Orbit3d::drawEllipse(float a, float b, float e)
{
    glDisable(GL_LIGHTING);

    glColor3f(color.red(), color.green(), color.blue());
    float x,y,z;

    glBegin(GL_LINE_LOOP);
    for(float t = 0; t <= 2 * M_PI; t += M_PI / 720)
    {
        x = cos(t) * a + e;
        y = sin(t) * b;
        z = 0;

        glRotatef(45.0, 1.0, 1.0, 1.0);

        glVertex3f(x,y,z);
    }
    glEnd();

    glEnable(GL_LIGHTING);
}
