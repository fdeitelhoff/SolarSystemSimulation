/***************************************************************************
     gllight.h  -  A light for illuminating the scenes.
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

#ifndef GLLIGHT_H
#define GLLIGHT_H

#include "glcolorrgba.h"
#include "glvector.h"

/**A light for illuminating the scenes.
  *Encapsulates OpenGL light functionality. Call glEnable(GL_LIGHTING) before using a light.
  *Call  switchOn()  and switchOff() to switch the individual light on or off. 
  *OpenGl supports up to 8 lights. GLLight manages the light number automatically.
  *The bits from 0 to 7 of the static LightsInUse variable in gllight.cpp represent the respective lights. The constructor searches
  *for the first free light and takes its number as LightNumber. 
  *@author Walter Roth
  */

class GLLight{
public:
  /** Default constructor. A white directional light with direction (1,1,1).
   */
	GLLight();
  /** Constructor with a full set of parameters.
  */
  GLLight (const GLVector & Pos, const GLColorRGBA & Diffuse, const GLColorRGBA & Specular,
   const GLColorRGBA & Ambient);
  /** Destructor
  */
 virtual ~GLLight();
 /** Write property of GLVector Position.
 */
  virtual void setPosition( const GLVector& _newVal);
  /** Read property of GLVector Position.
  */
  virtual const GLVector& position();
  /** Write property of GLColorRGBA DiffuseColor.
  */
  virtual void setDiffuseColor( const GLColorRGBA& _newVal);
  /** Read property of GLColorRGBA DiffuseColor.
  */
  virtual const GLColorRGBA& diffuseColor();
  /** Write property of GLColorRGBA SpecularColor.
  */
  virtual void setSpecularColor( const GLColorRGBA& _newVal);
  /** Read property of GLColorRGBA SpecularColor.
  */
  virtual const GLColorRGBA& specularColor();
  /** Write property of GLColorRGBA AmbienCColor.
  */
  virtual void setAmbientColor( const GLColorRGBA& _newVal);
  /** Read property of GLColorRGBA AmbienCColor.
  */
  virtual const GLColorRGBA& ambientColor();
  /** Write property of double Brightness.
  */
  virtual void setBrightness( const double& _newVal);
  /** Read property of double Brightness.
  */
  virtual const double& brightness();
  /** Read property of int LightNumber.
  */
  virtual const int& lightNumber();
  /** Read property of static int LightsInUse.
  */
  virtual const int& activeLights();
  /** Read property of bool On.
  */
  virtual const bool& isOn();
  /** Turns off the light.
  */
  virtual void switchOff();
  /** Turns on the light.
  */
  virtual void switchOn();
  /** Write property of bool Directional.
  */
  virtual void setDirectional( const bool& _newVal);
  /** Read property of bool Directional.
  */
  virtual const bool& isDirectional();
  /** Write property of bool m_ShowLightSource.
  */
  static void setShowLightSource( const bool& _newVal);
protected: // Protected attributes
  /** The position of the light. Default: 1,1,1
  */
  GLVector _Position;
  /** The color to be used for the diffuse lighting model. Default: white
  */
  GLColorRGBA _DiffuseColor;
  /** The overall brightness of the light.
    * Values from 0 to 1 are multiplied with all color settings. Default: 1
    */
  double _Brightness;
  /** The color to be used for the specular lighting model. Default: white
  */
  GLColorRGBA _SpecularColor;
  /** The color to be used for the specular lighting model. Default: white
  */
  int _Shininess;
  /** The color to be used for the ambient lighting model. Default: black
  */
  GLColorRGBA _AmbientColor;
  /** State of the light. Use switchOn and switchOff to toggle.
  */
  bool On;
  /** Directional lights are indefinitely far away,
    * only the direction is evaluated. Much faster than positional lights. 
    * Positional lights are at a defined position.
    */
  bool _Directional;
  /** If this flag is on, a little red sphere and a ray is drawn in the
    * direction of the light.
    */
  static bool _ShowLightSource;
private: // Private methods
  /** Returns the first free light number.
  */
  int firstFreeNumber();
  /** The number of the light. OpenGL standard is from 0 to 7.
    * Maintained automatically.
    */
  int _LightNumber;
};

#endif
