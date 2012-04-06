/***************************************************************************
                          gllight.cpp  -  description
                             -------------------
    begin                : Mon Jun 3 2002
    copyright            : (C) 2002, 2008 by Walter Roth
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

#include "gllight.h"
#include "GL/glut.h"

/** OpenGl supports up to 8 lights. GLLight manages the light number automatically.
The bits from 0 to 7 of LightsInUse represent the respective lights. The constructor searches
for the first free light and takes its number as _LightNumber. */
static int LightsInUse = 0; //initialize once.
bool GLLight::_ShowLightSource = true;     //show a red ball and a ray for debugging

/** Default Constructor
*/
GLLight::GLLight(){
 _Position = v_XYZ;
 _DiffuseColor = cl_White;
 _SpecularColor= cl_White;
 _Shininess = 80;
 _AmbientColor= cl_White *0.2;
 _Brightness = 1.0;
 _LightNumber = firstFreeNumber();
 _Directional = true;
}
  /** Constructor with a full set of parameters.
  */
 GLLight::GLLight(const GLVector & Pos, const GLColorRGBA & Diffuse, const GLColorRGBA & Specular,
  const GLColorRGBA & Ambient){
 _Position = Pos;
 _DiffuseColor = Diffuse;
 _SpecularColor= Specular;
 _AmbientColor= Ambient;
 _Brightness =1.0;
 _LightNumber = firstFreeNumber();
 _Directional = true;
}

GLLight::~GLLight(){
 switchOff();
 char test =1;
 for (int i = 0; i < _LightNumber; i++)
  test = test *2;
 test = !test;
 LightsInUse = LightsInUse & test; // mark as free
}

/** Read property of GLVector _Position. */
const GLVector& GLLight::position(){
	return _Position;
}
/** Write property of GLVector _Position. */
void GLLight::setPosition( const GLVector& _newVal){
	_Position = _newVal;
	if(isOn())
   {switchOff(); switchOn();}
}
/** Read property of GLColorRGBA _DiffuseColor. */
const GLColorRGBA& GLLight::diffuseColor(){
	return _DiffuseColor;
}
/** Write property of GLColorRGBA _DiffuseColor. */
void GLLight::setDiffuseColor( const GLColorRGBA& _newVal){
 _DiffuseColor = _newVal;
	if(isOn())
   {switchOff(); switchOn();}
}
/** Read property of GLColorRGBA _SpecularColor. */
const GLColorRGBA& GLLight::specularColor(){
	return _SpecularColor;
}
/** Write property of GLColorRGBA _SpecularColor. */
void GLLight::setSpecularColor( const GLColorRGBA& _newVal){
	_SpecularColor = _newVal;
	if(isOn())
   {switchOff(); switchOn();}
}
/** Read property of GLColorRGBA _AmbientColor. */
const GLColorRGBA& GLLight::ambientColor(){
	return _AmbientColor;
}
/** Write property of GLColorRGBA _AmbientColor. */
void GLLight::setAmbientColor( const GLColorRGBA& _newVal){
	_AmbientColor = _newVal;
	if(isOn())
   {switchOff(); switchOn();}
}
/** Read property of double _Brightness. */
const double& GLLight::brightness(){
	return _Brightness;
}
/** Write property of double _Brightness. */
void GLLight::setBrightness( const double& _newVal){
	_Brightness = _newVal;
	if(isOn())
   {switchOff(); switchOn();}
}
/** Read property of int Number. */
const int& GLLight::lightNumber(){
	return _LightNumber;
}
/** Read property of static int LightsInUse. */
const int& GLLight::activeLights(){
	return LightsInUse;
}
/** Returns the first free light number. */
int GLLight::firstFreeNumber(){
 char Lights = LightsInUse;
 char test = 1;
  for(int i = 0; i < 8; i++)
  {
   if((Lights & test) == 0)
    {
      LightsInUse = LightsInUse | test; // mark as used
      return i;
    }
   test = test * 2; //next bit
  }
  qDebug("GLLight::firstFreeNumber: Too many lights in use! (More than 8)");
  return -1; //no more lights available
}
/** Read property of bool On. */
const bool& GLLight::isOn(){
	return On;
}
/** Turns on the light. */
   void GLLight::switchOn(){
  GLColorRGBA color;
  GLfloat pos[4];
  bool lightingIsOn = glIsEnabled(GL_LIGHTING);
  pos[0] = _Position.x(); pos[1] = _Position.y(); pos[2] = _Position.z(); //copy position
  if(isDirectional())
   pos[3] = 0.0;  // 0 is a flag for directional light (as the sun)
  else pos[3] =1.0; // 1 is a positional light (as a lamp)
  glLightfv(GL_LIGHT0 + _LightNumber,  GL_POSITION, pos);
  color = _DiffuseColor * _Brightness;
  glLightfv(GL_LIGHT0 + _LightNumber,  GL_DIFFUSE, color.fv());
  color = _SpecularColor * _Brightness;
  glLightfv(GL_LIGHT0 + _LightNumber,  GL_SPECULAR, color.fv());
  color = _AmbientColor * _Brightness;
  glLightfv(GL_LIGHT0 + _LightNumber,  GL_AMBIENT, color.fv());

  glEnable(GL_LIGHT0 + _LightNumber);
  
  if(_ShowLightSource){
     if(lightingIsOn)
      glDisable(GL_LIGHTING); //make shure that a red line is shown     
     glPushMatrix();
     glColor3fv(cl_Red.fv());
     glBegin(GL_LINES);     // draw a ray
       glVertex3d(0.0,0.0,0.0);
       glVertex3d(pos[0], pos[1],pos[2]);
     glEnd(); 
     glTranslated(pos[0], pos[1],pos[2]);
     glutWireSphere(0.05, 4,4); //draw a light source
     glPopMatrix();
     if(lightingIsOn)
      glEnable(GL_LIGHTING); //re-enable lighting, if it was on
  }
  On = true;
}
/** Turns off the light. */
void GLLight::switchOff(){
 glDisable(GL_LIGHT0 + _LightNumber);
}
/** Read property of bool _Directional. */
const bool& GLLight::isDirectional(){
	return _Directional;
}
/** Write property of bool _Directional. */
void GLLight::setDirectional( const bool& _newVal){
	_Directional = _newVal;
}
/** Write property of bool _ShowLightSource. */
void GLLight::setShowLightSource( const bool& _newVal){
	GLLight::_ShowLightSource = _newVal;
}
