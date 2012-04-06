/***************************************************************************
 *   Copyright (C) 2008, 2011 by Walter Roth   *
 *   roth@fh-swf.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.              *
 ***************************************************************************/
#ifndef GLBODY_H
#define GLBODY_H
#include <QVector>
#include "glpoint.h"
#include "glcolorrgba.h"
/**
A 3d body that uses GL-arrays for drawing. Overwrite makeSurface() in subclasses
to create the points that form the surface. Overwrite draw() if you do not want
your body to be drawn with triangles.
       @author Walter Roth <roth@fh-swf.de>
*/
class GLBody{
public:
    /**Constructor does NOT create the surface.
      */
    GLBody();
    /** Destructor
      */
    virtual ~GLBody();

    /** Creates the surface. Should be called, when a GL engine is alreadyrunning.
       * To be overwritten by subclasses.
       * Is called automatically by draw, if required.
       * MUST NOT be called without a working GL engine.
       */
    virtual void makeSurface();
    /** Draws the surface and calls makeSurface if required.
     * Needs an active (made current) GL-Context.
     */
    virtual void draw();
    /** Set texture from file. Returns true on success
     */
    bool setTexture(const QString & textureFile);
    /** Set texture file.
     */
    bool setTextureFile(const QString & textureFile);
    /**Simple setters
     */
    void setColor(const GLColorRGBA & newVal){_color = newVal;}
    void setSpecularColor(const GLColorRGBA & newVal){_specularColor = newVal;}
    void setShininess(int newVal){_shininess = newVal;}
protected:
    /** The array of points defining the surface.
      */
    QVector <GLPoint> _points;
    /** The array with the indices. May be left empty.
    */
    QVector <GLint> _indices;
    /** The flag for a valid surface.
     */
    bool _surfaceValid;
    /** The texture to be used.
     */
    GLuint _texture;
    /** The tetxure file.
     */
    QString _textureFile;
    /** The diffuse and ambient color for the body.
    */
    GLColorRGBA _color;
    /**The specular color
    */
    GLColorRGBA _specularColor;
    /**Shoininess for specular color
  */
    int _shininess;
    // The factor for the vectors
    double _factor;
};
#endif

