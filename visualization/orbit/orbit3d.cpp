#include "orbit3d.h"

Orbit3d::Orbit3d(double angle, double orbitalPlaneAngle, GLColorRGBA color, float a, float b, float e)
{
    this->angle = angle;
    this->orbitalPlaneAngle = orbitalPlaneAngle;
    this->color = color;

    calculateEllipse(a, b, e);
}

void Orbit3d::paintOrbit3d()
{
    glPushMatrix();

    glRotatef(orbitalPlaneAngle, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);

    drawEllipse();

    glPopMatrix();
}

void Orbit3d::calculateEllipse(float a, float b, float e)
{
    // Pre calculate all ellipse points.
    float x, y;
    for(float t = 0; t <= 2 * M_PI; t += M_PI / 360)
    {
        x = cos(t) * a + e;
        y = sin(t) * b;

        ellipsePoints.append(GLVector(x, y, 0));
    }
}

void Orbit3d::drawEllipse()
{
    glDisable(GL_LIGHTING);

    glColor4f(color.red(), color.green(), color.blue(), color.alpha());

    glBegin(GL_LINE_LOOP);

    // Paint all precalculated ellipse points.
    foreach (GLVector vector, ellipsePoints)
    {
       glVertex3f(vector.x(), vector.y(), vector.z());
    }

    glEnd();

    glEnable(GL_LIGHTING);
}
