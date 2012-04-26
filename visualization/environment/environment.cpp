#include "environment.h"

Environment::Environment()
{
    colors.resize(6);

    // red. GLfloat r, GLfloat g, GLfloat b, GLfloat a =1.0
    colors[0] = GLColorRGBA(1.0, 0.0, 0.0, 1.0);
    colors[1] = GLColorRGBA(1.0, 0.0, 0.0, 1.0);

    // green.
    colors[2] = GLColorRGBA(0.0, 1.0, 0.0, 1.0);
    colors[3] = GLColorRGBA(0.0, 1.0, 0.0, 1.0);

    // blue.
    colors[4] = GLColorRGBA(0.0, 0.0, 1.0, 1.0);
    colors[5] = GLColorRGBA(0.0, 0.0, 1.0, 1.0);

    areCoordinateAxesVisible = false;
}

void Environment::drawAxes(GLdouble axisLength)
{
    if (areCoordinateAxesVisible)
    {
        QVector <GLVector> points(6);

        points[0] = GLVector(-axisLength,0.0,0.0);
        points[1] = GLVector(axisLength,0.0,0.0);
        points[2] = GLVector(0.0,-axisLength, 0.0);
        points[3] = GLVector(0.0,axisLength,0.0);
        points[4] = GLVector(0.0,0.0,-axisLength);
        points[5] = GLVector(0.0,0.0,axisLength);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, sizeof(GLVector), points[0].dv());

        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, sizeof(GLColorRGBA), colors[0].fv());

        glDrawArrays(GL_LINES, 0, 6);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void Environment::toggleCoordinateAxesVisibility()
{
    areCoordinateAxesVisible = !areCoordinateAxesVisible;
}
