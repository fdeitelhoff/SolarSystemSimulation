/***************************************************************************
                          GLVector.cpp  -  for description see c3dvector.h
                             -------------------
    begin                : Mon Feb 5 2001
    copyright            : (C) 2001-2003 by Walter Roth
    email                : info@fh-swf.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software{} you can redistribute it and/or modi_Y  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation{} either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "glvector.h"
#include <stdio.h>
int GLVector::_AngleMode = GLVector::Use360Degree;
int GLVector::n_Buffer = 0;
GLVector GLVector::OpBufferVectors[AvailableOpBuffers];

//The following counters are activated in debugging mode only
#ifdef DEBUG_GLVECTOR
int GLVector::n_MaxBuffers = 0;
int GLVector::n_OperatorCalls = 0;
int GLVector::n_CopyCalls = 0;
int GLVector::n_ConstructorCalls = 0;
int GLVector::n_VertexCalls = 0;
#endif

/** Standard  constructor, creates a zero vector
    */
GLVector::GLVector(){
 #ifdef DEBUG_GLVECTOR
  n_ConstructorCalls ++;
 #endif 
 _X = 0;
 _Y = 0;
 _Z = 0; 
}

/**Destructor, presently it does nothing.
    */
GLVector::~GLVector(){
}

GLVector::GLVector(GLdouble x, GLdouble y, GLdouble z){
 #ifdef DEBUG_GLVECTOR
  n_ConstructorCalls ++;
 #endif
 _X = x;
 _Y = y;
 _Z = z;
}

/** Constructor for polar coordinates. Pass UseRadian, Use360Degree or Use400NewDegree as
    * value for angleMode.
    */
GLVector::GLVector(int angleMode, GLdouble radius, GLdouble longitude, GLdouble latitude){
 #ifdef DEBUG_GLVECTOR
  n_ConstructorCalls ++;
 #endif
  int oldAngleMode = GLVector::angleMode(); //prevent name clash
  setAngleMode(angleMode);
  setRadiusLongitudeLatitude(radius, longitude, latitude);
  setAngleMode(oldAngleMode);
}

/** Copy constructor. Calls copy() function.
    */
GLVector::GLVector(const GLVector& toCopy){
 #ifdef DEBUG_GLVECTOR
  n_ConstructorCalls ++;
 #endif
 copy(toCopy);
}


/** Read property for x coordinate.
    */
GLdouble GLVector::x()const{
  return _X;
}

/** Write property for x coordinate.
    */
void GLVector::setX(GLdouble _newVal){
 _X = _newVal;
}

/** Read property for y coordinate.
    */
GLdouble GLVector::y()const{
   return _Y;
}

/** Write property for y coordinate.
    */
void GLVector::setY(GLdouble _newVal){
 _Y = _newVal;
}

/** Read property for z coordinate.
    */
GLdouble GLVector::z()const{
  return _Z;
}

/** Write property for z coordinate.
    */
void GLVector::setZ(GLdouble _newVal){
 _Z = _newVal;
}

/** Returns vector with length 1.0 and same direction as  *this.
    */
const GLVector & GLVector::unitVector()const{
 GLVector v1;
 GLdouble aLength;
 aLength= length();
 if (aLength != 0.0)  
  return nextBuffer(_X / aLength,
                    _Y / aLength,
                    _Z / aLength);
  else {
   qDebug("GLVector::unitVector: Can not scale a zero vector to length 1.0");
   return nextBuffer(0.0, 0.0, 0.0);
  }
}

/** Scalar product.
   */
GLdouble GLVector::operator *( const GLVector& v2 )const{
 return  _X * v2._X + _Y * v2._Y + _Z * v2._Z;
}

/** Vector product *this X v2.
    */
const GLVector & GLVector::vectorMult( const GLVector& v2)const{
 return nextBuffer(
   _Y * v2._Z - _Z * v2._Y,
   _Z * v2._X - _X * v2._Z,
   _X * v2._Y - _Y * v2._X);
}

/** Normal vector with length 1.0 obtained by *this X v2.
   */
const GLVector & GLVector::normalVector(const GLVector& v2)const{
 /*GLVector v = vectorMult(v2);
 v = v.unitVector();
 return nextBuffer(v._X, v._Y, v._Z);*/
 return vectorMult(v2).unitVector();
}

/** Caculates the length.
   */
GLdouble GLVector::length()const{
 return sqrt(_X * _X + _Y * _Y + _Z * _Z);
}

//****************Function RotateVector************************************
//First get the projection of v1 on rotation axis. Then make a 2d axis
//system where Rotation.axis is normal to. xNew is the first axis of this
//system xNew = v1 - Av1(Projection of v1 on Rotation.Axis). The second axis
//yNew is obtained by vectormultiplication of Av1 and xNew divided by |Av1|.
//this has the same length as xNew and is normal to xNew and Rotation.Axis.
//Now xNew can easily be rotated in a 2d coordinate system made by xNew and
//yNew. The result is xRotated. The result of rotating v1 is Av1 + xRotated.

const GLVector GLVector::rotateVector(const GLVector& Axis, GLdouble Angle)const{
GLVector vAxis = Axis; //local copy
GLVector Av1     ; //Projection of v1 on Rotation Axis
GLVector xNew    ; //v1-Av1 first vector in plane of rotation
GLVector yNew    ; //second vector in plane of rotation
GLVector xRotated; //result of rotation of xnew by Rotation.Theta
GLVector xNewComp; //xNew component of xRotated in xNew, yNew plane
GLVector yNewComp; //yNew component of xRotated in xNew, yNew plane
GLdouble     AbsAxis;    // |Rotation Axis|
GLdouble     AbsAv1 ;    // |Av1|
GLdouble   radAngle = toRadian(Angle);
 // precalculate lengths
 AbsAxis = vAxis.length();  // precalculate length of Axis
 AbsAv1  = (*this * vAxis )/ AbsAxis ;   // precalculate length of Av1

 //get projection of v1 on Axis
 Av1     = vAxis * AbsAv1 ;

 // Make a cartesian xNew,yNew plane with equal xNew and yNew lengths.
 // Because xNew is normal to Axis, sin(Axis, xNew) is 1
 xNew    = * this - Av1; //keep length != 1 for speed
 yNew    = vAxis.vectorMult(xNew) * ( 1.0 / AbsAxis );

 // Rotate xNew in xNew, yNew plane by Theta
 xNewComp= xNew * cos( radAngle );
 yNewComp= yNew * sin( radAngle );
 xRotated= xNewComp + yNewComp;

 //Add Av1 and xRotated to get final result
 return Av1 + xRotated;
}

/** Returns the vectorsum of v1 and v2. */
const GLVector & GLVector::operator+(const GLVector& v2)const{
 #ifdef DEBUG_GLVECTOR
  debugOperators(this, &v2);
 #endif
 return nextBuffer (_X + v2._X,
                       _Y + v2._Y,
                       _Z + v2._Z);
}
/** Returns this - v2. */
const GLVector & GLVector::operator-(const GLVector& v2)const{
 #ifdef DEBUG_GLVECTOR
  debugOperators(this, &v2);
 #endif
 return nextBuffer (_X - v2._X,
                       _Y - v2._Y,
                       _Z - v2._Z);
}

/** For use with glXXXX3dv functions. */
GLdouble * GLVector::dv()const{
  #ifdef DEBUG_GLVECTOR
   n_VertexCalls ++;
  #endif
 return (GLdouble *)&_X;
}
/** Stretches a vector to x*sx, y*sy, z*sz. */
const GLVector & GLVector::stretchVector(GLdouble sx, GLdouble sy, GLdouble sz)const{
 #ifdef DEBUG_GLVECTOR
  debugOperators();
 #endif
 return nextBuffer( _X * sx, _Y * sy,_Z * sz);
}

/** Multiplies vector with f. */
const GLVector & GLVector::operator *(GLdouble f)const{
 #ifdef DEBUG_GLVECTOR
  debugOperators();
 #endif
 return nextBuffer(_X *f,
                      _Y *f,
                      _Z *f);
}
/** Returns true, if all coordinates are 0.
*/
bool GLVector::isNull()const{
 return ((_X == 0) & (_Y ==0) & (_Z==0));
}
/** Compares two vectors.
  * Will only return true if ALL digits of the GLdouble coordinates are the same.
  */
bool GLVector::operator == (const GLVector& v2) const{
 return ((v2._X == _X) & (v2._Y == _Y) & (v2._Z== _Z));
}
/** Compares two vectors. */
bool GLVector::operator != (const GLVector& v2) const{
 return ! (*this == v2);
}
/** Copy function used by copy constructor and operator =. */
void GLVector::copy(const GLVector & toCopy){
  if(this!= & toCopy){ //no self copy
     _X = toCopy._X;
     _Y = toCopy._Y;
     _Z = toCopy._Z;
  }
 #ifdef DEBUG_GLVECTOR
   n_CopyCalls ++;
 #endif
}
/** Copies toCopy and returns * this. */
GLVector & GLVector::operator = (const GLVector & toCopy){
  copy(toCopy);
  return *this;
}
/** Multipies 3d Vector with 4*4 matrix. 4th coordinate of vector is assumed to be 1.0.
   * Calculations run on main fpu. Use glMultMatrix for calculation on graphics processor.
   */
const GLVector & GLVector::operator *(const CGLMatrix & m) const{
 #ifdef DEBUG_GLVECTOR
  debugOperators();
 #endif
  CGLMatrix myM = m; //local copy
  GLfloat *pm = myM.getMatrix();  //call non - const member function for local copy
  return nextBuffer(
    pm[0] * _X + pm[4] * _Y + pm[8] * _Z + pm[12],   //use fast single index zero based addressing
    pm[1] * _X + pm[5] * _Y + pm[9] * _Z + pm[13],
    pm[2] * _X + pm[6] * _Y + pm[10] * _Z + pm[14]
  );
}
/** Writes list of coordinates to stderr. */
void GLVector::debugOutput(const QString & caption)const{
  qDebug(debugString(caption).toLatin1());
}
/** Returns the debug output string.
*/
QString GLVector::debugString(const QString & caption)const{
  QString sx,sy,sz, msg;
  return QString( caption + " GLVector  x: " + sx.setNum(_X, 'g', 4) +" y: " + sy.setNum(_Y, 'g', 4)+
  " z: " + sz.setNum(_Z, 'g', 4));  
}

/** Returns length of vector, for convenience.
 */
GLdouble GLVector::radius()const{
  return length();
}
/** Returns latitude angle form equatorial xz plane up and down.
 */
GLdouble GLVector::latitude()const{
  GLdouble lengthXZ = sqrt(_X * _X + _Z * _Z);

  GLdouble latitude;
  if (lengthXZ !=0.0)
   latitude= atan(_Y / lengthXZ);
  else{
     if( _Y > 0.0)
      latitude = M_PI /2.0;
     else latitude = - M_PI /2.0;
  }
  return toDegree(latitude);
}
/** Returns theta angle from z axis downwards.
 */
GLdouble GLVector::theta()const{
  GLdouble lengthXY = sqrt(_X * _X + _Y * _Y);

  GLdouble theta;
  if (lengthXY !=0.0)
   theta= atan(_Z / lengthXY) + M_PI /2.0;
  else{
     if( _Z > 0.0)
      theta = 0.0;
     else theta = - M_PI;
  }
  return toDegree(theta);
}
/** Returns radian value for angle.
 */
GLdouble GLVector::toRadian(GLdouble angle)const{
  if(_AngleMode == GLVector::Use360Degree)
    return angle * M_PI / 180.0;
  else {
    if(_AngleMode == GLVector::Use400NewDegree)
      return angle * M_PI / 200.0;
    else return angle;
  }
}
/** Returns degree value for angle. If _AngleMode is UseRadian, angle is returned unscaled.
*/
GLdouble GLVector::toDegree(GLdouble angle)const{
  if(_AngleMode == GLVector::Use360Degree)
    return angle / M_PI * 180.0;
  else {
    if(_AngleMode == GLVector::Use400NewDegree)
      return angle / M_PI * 200.0;
    else return angle;
  }
}
/** Returns the longitude angle around y axis in radian, 360 degree or 400 new degree
according to angleMode.  Angle starts at z-axis.*/
GLdouble GLVector::longitude()const{
  GLdouble longitude;
  if(_Z == 0.0){
      if(_X > 0.0)
         longitude = M_PI /2.0;
      else longitude = -M_PI /2.0;
    }
  else longitude = atan(_X / _Z);
  if((_Z < 0.0) & (_X > 0.0))
   longitude += M_PI;
  if((_X <0.0)&(_Z<0.0))
   longitude -= M_PI;
  return toDegree(longitude);
}

/** Returns phi angle around z axis in radian, 360 degree or 400 new degree
according to angleMode. */
GLdouble GLVector::phi()const{
  GLdouble phi;
  if(_X == 0.0){
      if(_Y >0.0)
         phi = M_PI /2.0;
      else phi = -M_PI /2.0;
    }
  else phi = atan(_Y / _X);
  if((_X < 0.0) & (_Y > 0.0) || (_Y <0.0)&(_X<0.0))
   phi += M_PI;
  return toDegree(phi);
}

/** Multiplies vector with1/ f.
 */
const GLVector & GLVector::operator /(GLdouble f)const{
 #ifdef DEBUG_GLVECTOR
  debugOperators();
 #endif
    if (f !=0.0){
       GLdouble f1= 1.0 / f; 
       return nextBuffer(_X * f1, _Y * f1, _Z * f1);
    }
    else{
      qDebug("Vector division by zero. Returning zero vector." );
      return nextBuffer(0.0,0.0,0.0);
    }
}
/** Sets polar coordinates. Z is up, phi in xy plane, theta from z downwards.
  */
void GLVector::setRadiusPhiTheta(GLdouble radius, GLdouble phi, GLdouble theta){
  phi = toRadian(phi);
  theta = toRadian(theta);
  _X = radius * sin(theta)* cos(phi);
  _Y = radius * sin(theta)*sin(phi);
  _Z = radius * cos(theta);
}

/** Sets geographic coordinates. Y is up, longitude in xz plane, latitude from xz plane up- and downwards.
  */
void GLVector::setRadiusLongitudeLatitude(GLdouble radius, GLdouble longitude, GLdouble latitude){
  GLdouble radLongitude = toRadian(longitude); // may be more than +-180 degree
  GLdouble radLatitude = toRadian(latitude);
  //Not more than +- 90 degree.
  if(radLatitude > M_PI / 2.0)
    radLatitude = M_PI/ 2.0;
  if(radLatitude < -M_PI / 2.0)
    radLatitude = -M_PI/ 2.0;
  _X = radius * sin(radLongitude)* cos(radLatitude);
  _Y = radius * sin(radLatitude);
  _Z = radius * cos(radLongitude)* cos(radLatitude);
}

/** Read property of int _AngleMode. */
const int& GLVector::angleMode(){
	return GLVector::_AngleMode;
}
/** Write property of int _AngleMode. */
void GLVector::setAngleMode( const int& _newVal){
	GLVector::_AngleMode = _newVal;
}
/** Calls glVertex3dv.
 */
void GLVector::vertex()const{
  #ifdef DEBUG_GLVECTOR
   n_VertexCalls ++;
  #endif
  glVertex3dv(& _X);
}
/**Limits coordinates to values between min and max. 
 */
void GLVector::limitTo(const GLVector & min, const GLVector & max){
  if(_X < min._X)
    _X = min._X;
  if(_Y < min._Y)
    _Y = min._Y;
  if(_Z < min._Z)
    _Z = min._Z;
  if(_X > max._X)
    _X = max._X;
  if(_Y > max._Y)
    _Y = max._Y;
  if(_Z > max._Z)
    _Z = max._Z;
}

/**Copies x, y and z to the next (and hopefully free) buffer vector
  *from the buffer ring OpBuffer and returns its address.
  *The number of available buffer vectors is controlled by AvailableOpBuffers.
  *<b>There is no verification,
  *whether a buffer position is no longer used. Therefore, if you are
  *performing very deeply nested calculations, you may have to set
  *_BufferVectors to a higher value.</b>
 */
const GLVector & GLVector::nextBuffer(GLdouble x, GLdouble y, GLdouble z){
  n_Buffer++;
  if(n_Buffer >= AvailableOpBuffers) //take the first after the last vector
   n_Buffer = 0;
  OpBufferVectors[n_Buffer]._X = x;
  OpBufferVectors[n_Buffer]._Y = y;
  OpBufferVectors[n_Buffer]._Z = z;
  #ifdef DEBUG_GLVECTOR
   if(GLVECTOR_DEBUG_LEVEL > 2){
     QString sNumber;
     sNumber.setNum(n_Buffer);
     GLVector v(x,y,z);
     v.debugOutput("GLVector buffer number:" + sNumber);
   }
  #endif
  return OpBufferVectors[n_Buffer];
}
/** Counts the calls to operator functions.
*/
#ifdef DEBUG_GLVECTOR
void GLVector::debugOperators(const GLVector * v1, const GLVector * v2){
  n_OperatorCalls ++;
  if(GLVECTOR_DEBUG_LEVEL >1
   && v1 >= &OpBufferVectors[0] && v1 < &OpBufferVectors[AvailableOpBuffers]
   && v2 >= &OpBufferVectors[0] && v2 < &OpBufferVectors[AvailableOpBuffers]){
     int depth = v2 - v1;
     if(depth < 0) depth = depth + n_MaxBuffers;
     depth ++; //one buffer is minimum
     if(depth < AvailableOpBuffers){ //address is within buffer range
      if(depth > n_MaxBuffers){
        n_MaxBuffers = depth;   //set debugging breakpoint here
        qDebug("GLVector::debugOperators: Maximum operator buffers used: %i", depth);
    }
   }
  }//end if debug level
}
#endif
/** Produces a debug output of the number of operations, constructoir calls etc.
 */
void GLVector::debugOutputStatistics(){
  #ifdef DEBUG_GLVECTOR
  char msg[255];
  if(GLVECTOR_DEBUG_LEVEL >1)
   sprintf(msg, "GLVector statistics: Constructor calls: %i Copy calls: %i Vertex calls: %i Operator calls: %i Maximum buffers used: %i",
   n_ConstructorCalls, n_CopyCalls, n_VertexCalls, n_OperatorCalls, n_MaxBuffers);
  else
   sprintf(msg, "GLVector statistics: Constructor calls: %i Copy calls: %i Vertex calls: %i Operator calls: %i",
   n_ConstructorCalls, n_CopyCalls, n_VertexCalls, n_OperatorCalls);
  qDebug(msg);
  #else
   qDebug("Debugging is switched off. Compile with -D DEBUG_GLVECTOR to switch on");
  #endif
}
/** Sets debugging counters to 0.
 */
void GLVector::debugResetCounters(){
  #ifdef DEBUG_GLVECTOR
   n_ConstructorCalls = 0;
   n_CopyCalls = 0;
   n_VertexCalls = 0;
   n_OperatorCalls = 0;
   n_MaxBuffers = 0;
   n_Buffer = 0;
   for (int i = 0; i < AvailableOpBuffers; i++){
     OpBufferVectors[i] = v_Zero;
   }  
  #else
   qDebug("Debugging is switched off. Compile with -D DEBUG_GLVECTOR to switch on");
  #endif
}
/** Returns scalar product.
 */
GLdouble GLVector::scalarMult(const GLVector & v2)const{
  //Source code copied from operator * for speed reasons.
 return  _X * v2._X
        +_Y * v2._Y
        +_Z * v2._Z;
}
/** Returns f*v. For convenience.  Adds GLdouble * GLVector functionality as suppliment to GLVector operator *(GLdouble).
 */
const GLVector & operator *(GLdouble f, const GLVector& v){
  return v * f;   //call operator * of GLVector class
}
/** Returns v * (-1.0). For convenience.
 */
const GLVector & operator -(const GLVector& v2){
  return v2 * (-1.0);
}

