/***************************************************************************
                          ccolorrgba.h  - description
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

#ifndef GLCOLORRGBA_H
#define GLCOLORRGBA_H


/** A color class that supports RGBA colors. Color is saved as 4 GLfloat values
  * 0.0 = black, 1.0 = full intensity.
  * The "A" value is for transparency (very practical for window panes).
  * 0.0 = transparent, 1.0 = opaque
  *@author Walter Roth
  */
# include <GL/gl.h>

class GLColorRGBA {
 GLfloat _Red, _Green, _Blue, _Alpha;  //DO NOT CHANGE order of declaration! Is used as GLdouble *!
public:
  /** Constructs a black color.
  */
  GLColorRGBA();
  /** Constructs the specified color.
   */
  GLColorRGBA(GLfloat r, GLfloat g, GLfloat b, GLfloat a =1.0);
  /** Destructor, does nothing.
  */
  virtual ~GLColorRGBA();
  /**Returns a pointer to fR. To be used with GLColorXXXfv functions.
    */
  GLfloat * fv(); 
  /** For brightness adjustment. "a" value is not multiplied.
    */
  GLColorRGBA operator *(double f);
  /** Returns Red value.
    */
  double red();
  /** Copy operator.
  */
  GLColorRGBA operator=(const GLColorRGBA & toCopy);
  /** Returns Green value.
  */
  double green();
  /** Copy constructor.
 */
   GLColorRGBA (const GLColorRGBA & toCopy);
  /** Returns Blue value.
  */
  double blue();
  /** Returns A (transparency) value.
  */
  double alpha();
protected: // Protected methods
 /** Copy function. For internal use only. MUST be called by subclassed copy functions.
 */
  void copy(const GLColorRGBA & toCopy);
};

/** Predefined global colors for convenience.
  */
static GLColorRGBA cl_White      = GLColorRGBA(1.0,1.0,1.0);
static GLColorRGBA cl_Black      = GLColorRGBA(0.0,0.0,0.0);
static GLColorRGBA cl_Red        = GLColorRGBA(1.0,0.0,0.0);
static GLColorRGBA cl_Green      = GLColorRGBA(0.0,1.0,0.0);
static GLColorRGBA cl_Blue       = GLColorRGBA(0.0,0.0,1.0);
static GLColorRGBA cl_LightBlue  = GLColorRGBA(0.5,0.5,1.0);
static GLColorRGBA cl_Gray       = GLColorRGBA(0.5,0.5,0.5);
static GLColorRGBA cl_Yellow     = GLColorRGBA(1.0,1.0,0.0);
static GLColorRGBA cl_Magenta    = GLColorRGBA(1.0,0.0,1.0);
static GLColorRGBA cl_Cyan       = GLColorRGBA(0.0,1.0,1.0);

#endif
