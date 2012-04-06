#include "glpoint.h"

GLPoint::GLPoint(const GLVector & vertex, const GLVector & normal, const GLVector & texCoord)
{
    _vertex = vertex;
    _normal = normal;
    _texCoord = texCoord;
}

GLPoint::~GLPoint()
{

}

GLdouble* GLPoint::normalPointer()
{
    return _normal.dv();
}

GLdouble* GLPoint::vertexPointer()
{
    return _vertex.dv();
}

GLdouble* GLPoint::texCoordPointer()
{
    return _texCoord.dv();
}
