#include "glcube.h"
#include <stdio.h>
#include <QDebug>


GLCube::GLCube()
{
}

void GLCube::makeSurface()
{
    GLVector vertex[8];
    GLVector textCoord;
    _points.resize(36);

                                           //                          |y
                                           //                          |
                                           //                          |
                                           //                         3|_______ 2
                                           //                        / |      /|
    vertex[0] = GLVector(0.0, 0.0, 0.0);   //                       /  |     / |
    vertex[1] = GLVector(1.0, 0.0, 0.0);   //                      /  0|___ /__|1____________x
    vertex[2] = GLVector(1.0, 1.0, 0.0);   //                     /______  /   /
    vertex[3] = GLVector(0.0, 1.0, 0.0);   //                    |7  /     |6 /
    vertex[4] = GLVector(0.0, 0.0, 1.0);   //                    |         | /
    vertex[5] = GLVector(1.0, 0.0, 1.0);   //                    | /       |/
    vertex[6] = GLVector(1.0, 1.0, 1.0);   //                   4|_________|5
    vertex[7] = GLVector(0.0, 1.0, 1.0);   //                    /
                                           //                   /
                                           //                  /
                                           //                 /z

    if(_factor != 1)
    {
        for( int i=0 ; i<8 ; i++ )
        {
            vertex[i] = vertex[i] * _factor;
        }
    }

    GLVector normal_x = GLVector(1.0, 0.0, 0.0);
    GLVector normal_y = GLVector(0.0, 1.0, 0.0);
    GLVector normal_z = GLVector(0.0, 0.0, 1.0);

    // Back
    textCoord   = vertex[1];
    _points[0]  = GLPoint(vertex[0], - normal_z, textCoord);
    _points[1]  = GLPoint(vertex[2], - normal_z, textCoord);
    _points[2]  = GLPoint(vertex[1], - normal_z, textCoord);
    _points[3]  = _points[0];
    _points[4]  = GLPoint(vertex[3], - normal_z, textCoord);
    _points[5]  = _points[1];

    // Front
    textCoord   = vertex[4];
    _points[6]  = GLPoint(vertex[4],  normal_z, textCoord);
    _points[7]  = GLPoint(vertex[5],  normal_z, textCoord);
    _points[8]  = GLPoint(vertex[6],  normal_z, textCoord);
    _points[9]  = _points[6];
    _points[10] = _points[8];
    _points[11] = GLPoint(vertex[7],  normal_z, textCoord);

    // Left
    textCoord   = vertex[0];
    _points[12] = GLPoint(vertex[0], - normal_x, textCoord);
    _points[13] = GLPoint(vertex[4], - normal_x, textCoord);
    _points[14] = GLPoint(vertex[7], - normal_x, textCoord);
    _points[15] = _points[12];
    _points[16] = _points[14];
    _points[17] = GLPoint(vertex[3], - normal_x, textCoord);

    // Right
    textCoord = vertex[5];
    _points[18] = GLPoint(vertex[1],  normal_x, textCoord);
    _points[19] = GLPoint(vertex[2],  normal_x, textCoord);
    _points[20] = GLPoint(vertex[6],  normal_x, textCoord);
    _points[21] = _points[18];
    _points[22] = _points[20];
    _points[23] = GLPoint(vertex[5],  normal_x, textCoord);

    // Top
    textCoord   = vertex[7];
    _points[24] = GLPoint(vertex[7],  normal_y, textCoord);
    _points[25] = GLPoint(vertex[2],  normal_y, textCoord);
    _points[26] = GLPoint(vertex[3],  normal_y, textCoord);
    _points[27] = _points[24];
    _points[28] = GLPoint(vertex[6],  normal_y, textCoord);
    _points[29] = _points[25];

    // Bottom
    textCoord   = vertex[0];
    _points[30] = GLPoint(vertex[0], - normal_y, textCoord);
    _points[31] = GLPoint(vertex[1], - normal_y, textCoord);
    _points[32] = GLPoint(vertex[5], - normal_y, textCoord);
    _points[33] = _points[30];
    _points[34] = _points[32];
    _points[35] = GLPoint(vertex[4], - normal_y, textCoord);

    GLBody::makeSurface();
}

void GLCube::draw()
{
    this->draw( cl_Black );
}

void GLCube::draw(GLColorRGBA color)
{
    this->draw(color, 1.0);
}

void GLCube::draw( double factor )
{
    this->draw( cl_Black, factor);
}

void GLCube::draw(GLColorRGBA color, double factor)
{
    if (_factor != factor)
    {
        _factor = factor;           // Format changed
        _surfaceValid = false;
    }

    if (!_surfaceValid)
    {
        makeSurface();
    }

    _color = color;

    if (glIsEnabled(GL_LIGHTING))
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT, (_color * 0.1).fv());
        glMaterialfv(GL_FRONT, GL_SPECULAR, _specularColor.fv());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, _color.fv());
        glMateriali(GL_FRONT, GL_SHININESS, _shininess);
    }
    else
    {
        glColor3fv(_color.fv());
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, sizeof(GLPoint), _points[0].vertexPointer());

    if (glIsEnabled(GL_LIGHTING))
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_DOUBLE, sizeof(GLPoint), _points[0].normalPointer());
    }

    glDrawArrays(GL_TRIANGLES, 0, _points.size());

    glDisableClientState(GL_VERTEX_ARRAY);
}
