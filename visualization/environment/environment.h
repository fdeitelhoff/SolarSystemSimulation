#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QVector>

#include "OpenGL/glvector.h"
#include "OpenGL/glcolorrgba.h"

class Environment
{

public:
    Environment();

    void drawAxes(GLdouble axisLength);

    void toggleCoordinateAxesVisibility();

private:
    QVector<GLColorRGBA> colors;

    bool areCoordinateAxesVisible;

};

#endif // ENVIRONMENT_H
