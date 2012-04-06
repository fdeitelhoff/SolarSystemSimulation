/***************************************************************************
 *    Copyright (C) 2008, 2011 by Walter Roth   *
 *    roth@fh-swf.de   *
 *                                                                          *
 *    This program is free software; you can redistribute it and/or modify *
 *    it under the terms of the GNU General Public License as published by *
 *    the Free Software Foundation; either version 2 of the License, or     *
 *    (at your option) any later version.                                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program; if not, write to the                         *
 *    Free Software Foundation, Inc.,                                       *
 *    59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.              *
 ***************************************************************************/
#ifndef GLPOINT_H
#define GLPOINT_H
#include "glvector.h"
/**
A 3d-point to be used with GL-arrays. It encapsulates vertex, normal and texture
coordinates. For maximum memory efficiency it does not contain ANY virtual
function. This means, it should NOT be subclassed.
Useage with Qt: QVector<GLPoint> Geometry;
Useage with STL: Vector <GLPoint> Geometry;
Do always use sizeof(GLPoint) for the stride parameter in glXXXXArray functions.
       @author Walter Roth <roth@fh-swf.de>
*/
class GLPoint{
public:
     /**Constructor
     */
     GLPoint(const GLVector & vertex = v_Zero, const GLVector & normal = v_X,
const GLVector & texCoord =v_Zero);
     /**Destructor
     */
     ~GLPoint();
    /** Returns address of _X coordinate of _Vertex
    */
   GLdouble * vertexPointer();
   /** Returns address of _X coordinate of _Normal
    */
   GLdouble * normalPointer();
   /** Returns address of _X coordinate of _TexCoord
    */
   GLdouble * texCoordPointer();
   /** For debugging.
    */
   void debugOutput(const QString & prefix);
private:
 GLVector _vertex;
 GLVector _normal;
 GLVector _texCoord;
};
#endif
