#ifndef GLCUBE_H
#define GLCUBE_H
#include "glbody.h"

class GLCube : public GLBody
{
public:
    GLCube();
    void draw();
    void draw( GLColorRGBA color );
    void draw( double factor );
    void draw( GLColorRGBA color, double factor );
    void makeSurface();
   // void makeSurface();
    double _factor;
};

#endif // GLCUBE_H
