/***************************************************************************
                          GLVector.h  - description
                             -------------------
    begin                : Mon Feb 5 2001
    copyright            : (C) 2011 by Walter Roth
    email                : info@fh-swf.de
 ***************************************************************************/

/***************************************************************************
 *                                                                                   *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GLVECTOR_H
#define GLVECTOR_H

#define DEBUG_GLVECTOR   //comment this line for maximum performance
#define GLVECTOR_DEBUG_LEVEL 1

#include <GL/gl.h>
#include <math.h>
#include "glmatrix.h"

/** A vector with 3 dimensions in GLdouble numbers, especially designed for use with OpenGL.
  * Can be used easily with GL_xxx3dv functions. Use the dv() member function to obtain a
  * GLdouble * to the data. Alternatively, you may use vertex() for calls to glVertex and normal()
  * for calls to glNormal.
  * Contains the basic vector maths as memberfunctions and operators.
  * May be used with cartesian (x, y, z), geographic (radius, longitude angle counterclockwise
  * around y axis starting at z axis and latitude angle from equatorial xz plane up and down 90)
  * and polar coordinates ( radius, phi angle around z axis counterclockwise from x axis, theta angle
  * from positive z axis downwards). Radius is the length of the vector.
  * All angle functions work with 360 degree angles, unless you set GLVector::UseRadian or
  * GLVector::Use400NewDegree with the setAngleMode class function.
  * However, there is a constructor for geographic coordinates with a local AngleMode,
  * that accepts geographic coordinates and radian, 360 degree or 400 new degree angle
  * values. Pass Use360Degree or Use400NewDegree as first parameter, if you want to use degrees.
  * For polar coordinates, use the setRadiusPhiTheta function.
  * Data are kept as cartesian coordinates internally. Therefore, the geographic and polar values
  * may have rounding errors in the order of 10E-13.
  * All calculation functions except those operators, that include a = (=, +=, *= ...) are const functions.
  * This means, if you want to rotate a vector foo itself, you have to call: foo = foo.rotateVector().
  * For convenience, there are a couple of predefined vectors at the end of this header file (v_X, v_Y..).
  *
  * This class is designed for high performance and not for subclassing.
  * Undefine DEBUG_GLVECTOR for maximum performance (refer to top of header file).
  * There are no virtual functions, which would create a VMT.
  * This increases performance. Make functions virtual, if you want to subclass (NOT recommended).
  * The operators return references to members of the protected OpBufferVectors
  * array. This avoids permanent construction and destruction of temporary
  * GLVectors for calculation results.<b> The predefined maximum number of nested
  * calculations is 32. If you need more, increase the value of AvailableOpBuffers.
  * See the getNextBuffer function for details. Use debugOutputStatistics() to obtain
  * informations on buffer useage and call statistics. Operator buffer overflow is very likely,
  * if results of vector calculations are passed as reference parameters to functions that perform lots
  * of calculations. In these cases use "call by value" parameters or make an explicit copy of the
  * reference parameter. </b>
  * @author Walter Roth
  */

class GLVector {
public:
  /** Standard  constructor, creates a zero vector
  */
	GLVector();
  /**Destructor, presently it does nothing.
   */
  ~GLVector();
   /** Constructor for cartesian coordinates.
   */
	GLVector(GLdouble x, GLdouble y, GLdouble z);
  /** Constructor for geographic coordinates. Pass UseRadian, Use360Degree or Use400NewDegree as
    * value for angleMode.  Static AngleMode is NOT affected.
    * Alternatives: Construct a GLVector using the standard constructor. Then call
    * setRadiusPhiTheta for polar or setRadiusLongitudeLatitude for geographic coordinates.
    */
	GLVector(int angleMode,  GLdouble radius, GLdouble longitude, GLdouble latitude);
  /** Copy constructor. Calls copy() function.
  */
	GLVector(const GLVector&  toCopy);
  /** Read property  for x coordinate.
  */
  GLdouble x()const;
  /** Write property for x coordinate.
      */
  void setX(GLdouble _newVal);
  /** Read property  for y coordinate.
  */
  GLdouble y()const;
  /** Write property for y coordinate.
  */
  void setY(GLdouble _newVal);
  /** Read property  for z coordinate.
  */
  GLdouble z()const;
  /** Write property for z coordinate.
  */
  void setZ(GLdouble _newVal);
  /** Returns vector with length 1.0 and same direction as  *this.
  */
  const GLVector & unitVector()const;
  /** Scalar product.
   *  For vector product see function vectorMult.
   */
  GLdouble operator *(const GLVector& v2 )const;
  /** Vector product *this X v2.
  */
  const GLVector & vectorMult(const GLVector& v2)const;
  /** Normal vector with lenght 1.0 obtained by *this X v2.
  */
  const GLVector & normalVector(const GLVector& v2)const;
  /** Caculates the length.
  */
  GLdouble length()const;
  /** Returns a vector obtained by rotating *this around axis. Uses radian Angle.
  */
  const GLVector rotateVector(const GLVector& Axis, GLdouble Angle)const;
  /** Returns this - v2.
  */
  const GLVector & operator-(const GLVector& v2)const;
  /** Returns the vectorsum of v1 and v2.
  */
  const GLVector & operator+(const GLVector& v2)const;
  /** For use with glXXXX3dv functions. This function relies on the internal order of declaration.
  */
  GLdouble * dv()const;
  /** Returns  a vector  x*sx, y*sy, z*sz.
  */
  const GLVector & stretchVector(GLdouble sx, GLdouble sy, GLdouble sz)const;
  /** Multiplies vector with f.
  */
  const GLVector & operator *(GLdouble f)const;
  /** Returns true, if all coordinates are 0.
  */
  bool isNull()const;
 /** Compares two vectors.
   * Will only return true if ALL digits of the GLdouble coordinates are the same.
   */
  bool operator == (const GLVector& v2)const ;
  /** Compares two vectors. Uses !operator ==.
  */
  bool operator != (const GLVector& v2)const ;
  /** Copies toCopy and returns * this.
  */
  GLVector & operator = (const GLVector & toCopy);
  /** Multipies 3d Vector with 4*4 matrix. 4th coordinate of vector is assumed to be 1.0.
    * Calculations run on main fpu. Use glMultMatrix for calculation on graphics processor.
    */
  const GLVector & operator *(const CGLMatrix & m) const;
  /** Returns the debug output string.
  */
  QString debugString(const QString & caption)const;
  /** Writes list of coordinates to stderr.
  */
  void debugOutput(const QString &  caption)const;
  /** Produces a debug output of the number of operations, constructor calls etc.
  */
  static void debugOutputStatistics();
  /** Returns latitude angle from equatorial xz plane up and down.
  */
  GLdouble latitude()const;
  /** Returns theta angle from z axis downwards.
  */
  GLdouble theta()const;
  /** Returns length of vector, for convenience.
  */
  GLdouble radius()const;
  /** Returns degree value for angle. If angleMode is UseRadian, angle is returned unscaled.
  */
  GLdouble toDegree(GLdouble angle)const;
 /** Returns the longitude angle around y axis in radian, 360 degree or 400 new degree
   *according to angleMode.  Angle starts at z-axis.
   */
  GLdouble longitude()const;
 /** Returns phi angle around z axis in radian, 360 degree or 400 new degree
   *according to angleMode.
   */
  GLdouble phi()const;
  /** Multiplies vector with1/ f.
    */
  const GLVector & operator /(GLdouble f)const;
  /** Sets polar coordinates. Z is up, phi in xy plane, theta from z downwards.
    */
  void setRadiusPhiTheta(GLdouble radius, GLdouble phi, GLdouble theta);
 /** Sets geographic coordinates. Y is up, longitude in xz plane, latitude
   * from xz plane up- and downwards.
   */
  void setRadiusLongitudeLatitude(GLdouble radius, GLdouble longitude, GLdouble latitude);
  /** Write property of int _AngleMode.
  */
  static void setAngleMode( const int& _newVal);
  /** Read property of int _AngleMode.
  */
  static const int& angleMode();
  /** Returns radian value for angle.
  */
  GLdouble toRadian(GLdouble angle)const;
  /** Calls glVertex3dv.
 */
  void vertex()const;
  /** Sets debugging counters to 0.
 */
  static void debugResetCounters();
  /** Returns scalar product. May be used instead of operator *.
   *  For vector product see function vectorMult.
   */
  GLdouble scalarMult(const GLVector & v2)const;
  /**Limits coordinates to values between min and max. 
   */
  void limitTo(const GLVector & min, const GLVector & max);
protected: // Protected methods
  /** Copy function used by copy constructor and operator =.
  */
  void copy(const GLVector & toCopy);
/**Copies x, y and z to the next (and hopefully free) buffer vector
  *from the buffer ring OpBufferVectors and returns its address.
  *The number of available buffer vectors is controlled by AvailableOpBufferVectors.
  *<b>There is no verification,
  *whether a buffer position is no longer used. Therefore, if you are
  *performing very deeply nested calculations, you may have to set
  *AvailableOpBufferVectors to a higher value. Use debugOutputStatistics() for debugging.</b>
 */
 static const GLVector & nextBuffer(GLdouble x, GLdouble y, GLdouble z);
public: // Public attributes
  /** 360 degree mode for polar coordinates.
  */
   static const int Use360Degree = 1;
  /** 400 new degree mode for polar coordinates.
 */
  static const int Use400NewDegree = 2;
  /** Radian mode for polar coordinates.
  */
  static const int UseRadian = 3;
  /** Number of buffer vectors available for calculations using
    *the GLVector operators. See getNextBuffer.
    */
  static const int AvailableOpBuffers = 3;
protected: //Protected attributes
  //remove the dummy declaration, if your debugger works well without it.
 // char dummy; //neccessary for gdb 5.3 to show the correct formats of GLdoubles!
  //DO NOT CHANGE order of declaration for _X, _Y, _Z !! dv() and fv()will fail!!
  GLdouble _X ;
  GLdouble _Y;
  GLdouble _Z;
  //DO NOT CHANGE order of declaration!! dv() and fv()will fail!!
  /** Use radian, 360 degrees or 400 new degrees.
    * Set with GLVector::UseRadian, Use360Degree or Use400NewDegree.
    * Default: GLVector::Use360Degree
    */
  static int _AngleMode;
  /** Array with buffer vectors for return values of operators.
    */
  static GLVector OpBufferVectors[AvailableOpBuffers];
  /**Number of the presently used buffer for calculations.
  */
  static int n_Buffer;

  #ifdef DEBUG_GLVECTOR
  /**Maximum operator buffers used
  */ 
  static int n_MaxBuffers;
  /**Total number of operator calls
  */
  static int n_OperatorCalls;
  /**Total number of calls to function copy
  */
  static int n_CopyCalls;
  /**Total number of calls to constructors
  */
  static int n_ConstructorCalls;
  /**Total number of calls to dv, fv and vertex
  */
  static int n_VertexCalls;
private: // Private methods
  /** Counts the calls to operator functions.
  */
  static void debugOperators(const GLVector * v1 = NULL, const GLVector * v2 = NULL);
  #endif
};

  /** Returns f*v. For convenience.
    * Adds GLdouble * GLVector functionality as suppliment to GLVector operator *(GLdouble).
    */
const GLVector & operator *(GLdouble f, const GLVector& v);
  /** Returns v * (-1.0). For convenience.
    */
const GLVector & operator -(const GLVector& v);
 
/** Predefined global vectors for convenience.
*/
static GLVector v_Zero = GLVector(0,0,0);
static GLVector v_X    = GLVector(1,0,0);
static GLVector v_Y    = GLVector(0,1,0);
static GLVector v_Z    = GLVector(0,0,1);
static GLVector v_XY   = GLVector(1,1,0);
static GLVector v_YZ   = GLVector(0,1,1);
static GLVector v_XZ   = GLVector(1,0,1);
static GLVector v_XYZ  = GLVector(1,1,1);

static GLVector v_Min  = GLVector(-1e99,-1e99,-1e99);
static GLVector v_Max  = GLVector(1e99,1e99,1e99);

#endif
