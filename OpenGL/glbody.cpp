#include "glbody.h"

GLBody::GLBody()
{
    _surfaceValid = false;
}

GLBody::~GLBody()
{

}



// Ist es notwendig, diese Methoden hier zu implementieren ?
// Es müsste doch auch gehen, diese Klasse (GLBody) als ab-
// strakte Klasse anzulegen.
void GLBody::makeSurface()
{
    setTexture(_textureFile);
    _surfaceValid = true;
}


// Warum wird das hier implementiert, wenn es für die Funktion doch
// wieder überschrieben wird ?

void GLBody::draw()
{
    if (!_surfaceValid)
    {
        makeSurface();
    }
    if (_points.size() == 0 )
    {
        return;
    }

    glEnableClientState(GL_INDEX_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3,GL_DOUBLE,sizeof(GLPoint),_points[0].vertexPointer());
    glNormalPointer(GL_DOUBLE,sizeof(GLPoint),_points[0].normalPointer());
    glTexCoordPointer(3,GL_DOUBLE,sizeof(GLPoint),_points[0].texCoordPointer());

    if ( _indices.size() > 0)
    {
        glIndexPointer(GL_INT,sizeof(GLuint),_indices.data());
    }
    else
    {
        glDisableClientState(GL_INDEX_ARRAY);
    }

    glDrawElements(GL_TRIANGLES,_indices.count(),GL_UNSIGNED_INT,_indices.data());

    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}


bool GLBody::setTexture(const QString &textureFile)
{
    // Next time in this theatre
    return false;
}

bool GLBody::setTextureFile(const QString &textureFile)
{
    // Next time in this theatre
    return false;
}
