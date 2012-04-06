/***************************************************************************
                          glcolorrgba.cpp  -  description
                             -------------------
    begin                : Tue Feb 6 2001
    copyright            : (C) 2001, 2008 by Walter Roth
    email                : info@fh-swf.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "glcolorrgba.h"

/** Constructs a black color.
*/
GLColorRGBA::GLColorRGBA(){
 _Red = 0.0;
 _Green = 0.0;
 _Blue = 0.0;
 _Alpha = 1.0;
}
/** Constructs the specified color.
*/
GLColorRGBA::GLColorRGBA(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
 _Red = r;
 _Green = g;
 _Blue = b;
 _Alpha = a;
}
/** Copy constructor.
 */
GLColorRGBA::GLColorRGBA (const GLColorRGBA & toCopy){
   copy(toCopy);
}

/** Destructor, does nothing.
*/
GLColorRGBA::~GLColorRGBA(){
}

GLfloat * GLColorRGBA::fv(){
 return &_Red;
}

/** For brightness adjustment. "a" value is not multipiled.
*/
GLColorRGBA GLColorRGBA::operator *(double f){
 return GLColorRGBA(_Red * f,
                   _Green * f,
                   _Blue * f,
                   _Alpha);
}
/** Returns Red value. */
double GLColorRGBA::red(){
  return _Red;
}
/** Returns Green value. */
double GLColorRGBA::green(){
  return _Green;
}
/** Returns Blue value. */
double GLColorRGBA::blue(){
  return _Blue;
}
/** Returns A (transparency) value. */
double GLColorRGBA::alpha(){
  return _Alpha;
}
/** Copy operator.
 */
GLColorRGBA GLColorRGBA::operator = (const GLColorRGBA & toCopy){
  copy(toCopy);
  return * this;
}
/** Copy function. For internal use only.
 */
void GLColorRGBA::copy(const GLColorRGBA & toCopy){
  _Red = toCopy._Red;
  _Green = toCopy._Green;
  _Blue = toCopy._Blue;
  _Alpha = toCopy._Alpha;
}
