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

private:
    QVector<GLColorRGBA> colors;

};

#endif // ENVIRONMENT_H
