/***************************************************************************
                          cglmatrix.h  -  description
                             -------------------
    begin                : Thu Apr 17 2003
    last modified        : Sun Apr 4 2004
    copyright            : (C) 2003 by Walter Roth
    email                : roth@fh-swf.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CGLMATRIX_H
#define CGLMATRIX_H


/**A 4 *4 matrix for use with OpenGl functions and C3dVectors declared as m[16].
  * The standard column-major order of an OpenGL matrix is:
  *
  *              m[0]  m[4] m[8]   m[12]             m11 m12 m13 m14
  *              m[1]  m[5] m[9]   m[13]             m21 m22 m23 m24
  *              m[2]  m[6] m[10]  m[14]             m31 m32 m33 m34
  *              m[3]  m[7] m[11]  m[15]             m41 m42 m43 m44
  *             
  * Note that m11 is the top left coefficient m[0], m41 = m[3], m12 = m[4] and m44 = m[15].
  *<p><b>If you read this in an html file, refer to the cglmatrix.h file for correct formatting.</b></p>
  *@author Walter Roth
  */
#include<GL/gl.h>

#include <QString>


class CGLMatrix {
public:
    /** Standard constructor. Initializes a zero matrix.
    */
    CGLMatrix();
    /** Constructor that takes a full set of matrix coefficients.
    * For column major order see top comment in header file.
    */
    CGLMatrix(GLfloat M[16]);
    /** Destructor. Does nothing.
   */
    virtual ~CGLMatrix();
    /** Write property of GLfloat m[16].
     */
    virtual void setMatrix( const GLfloat * _newVal);
    /** Read property of GLfloat m[16]. Returns the address of m[0].
     */
    virtual GLfloat * getMatrix();
    /** Loads the identity matrix.
 */
    virtual void loadIdentity();
    /** Copy constructor.
  */
    CGLMatrix(const CGLMatrix & toCopy);
    /** Operator = copies m.
    */
    const CGLMatrix  operator =(const CGLMatrix & toCopy);
    /** Matrix multiplication m * m2. !!!WARNING: ORDER OF MATRICES IS CRITICAL!!! (m*m2 != m2*m)
    * Calculations run on main fpu. Use glMultMatrix for calculation on graphics processor.
    */
    const CGLMatrix  operator *(const CGLMatrix & m2) const;
    /** Writes matrix coefficients to stderr.
   */
    void debug(QString caption = "");
    /** Returns matrix element row, column. For mathematical convenience, row and column numbers start with 1.
    * Use getMatrix for direct access to single index zero based matrix element array, as required by OpenGL functions.
    */
    GLfloat m(int row, int column);
    /** Returns the transposed matrix m^T.
  */
    CGLMatrix transpose()const;
    /** Returns the determinant.
  */
    GLfloat determinant();
    /** Calculates the determinant using Sarrus' law fo 3 by 3 matrices.
    * The 3 by 3 matrix is obtained by deleting the last row (row 4) and the specified column.
    */
    GLfloat calcSarrus(int deletedColumn);
    /** Sets matrix element in row and column. Row and column numbers start with 1.
  */
    void setM(int row, int column, GLfloat value);
    /** Loads the current modelview matrix.
 */
    void loadModelview();
    /** Multiplies the matrix onto the current matrix stack <b>without saving </b>the current matrix on that stack.
 */
    void multToStack()const;
protected: // Protected attributes
    /** A vector that contains the 16 matrix coefficients. The order of coefficients is compatible to OpenGL matrices.
     */
private: // Private methods
    /** Copy function for copy constructor and operator =.
  */
    void copy(const CGLMatrix & toCopy);
    /** The 16 matrix coeficients.
  */
    GLfloat m_M[16];
};

#endif
