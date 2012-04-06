/***************************************************************************
                          cglmatrix.cpp  -  description
                             -------------------
    begin                : Thu Apr 17 2003
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
#include <QString>
#include "glmatrix.h"

/** Standard constructor. Initializes a zero matrix.
    */
CGLMatrix::CGLMatrix(){
    for( int i =0; i < 16; i++)
        m_M[i] = 0.0;
}
/** Destructor. Does nothing.
   */
CGLMatrix::~CGLMatrix(){
}
/** Read property of GLfloat m_M[16]. */
GLfloat * CGLMatrix::getMatrix(){
    return &m_M[0];
}
/** Write property of GLfloat m_M[16]. */
void CGLMatrix::setMatrix( const GLfloat *_newVal){
    for( int i =0; i < 16; i++)
        m_M[i] = _newVal[i];
}
/** Loads the identity matrix.
 */
void CGLMatrix::loadIdentity(){
    m_M[0]=1.0;      //column 1
    m_M[1]=0.0;
    m_M[2]=0.0;
    m_M[3]=0.0;

    m_M[4]=0.0;     //column 2
    m_M[5]=1.0;
    m_M[6]=0.0;
    m_M[7]=0.0;

    m_M[8]=0.0;     // column 3
    m_M[9]=0.0;
    m_M[10]=1.0;
    m_M[11]=0.0;

    m_M[12]=0.0;   //  column 4
    m_M[13]=0.0;
    m_M[14]=0.0;
    m_M[15]=1.0;
}
/** Constructor that takes a full set of matrix coefficients. For column major order see top comment in header file. */
CGLMatrix::CGLMatrix(GLfloat M[16]){
    for (int i = 0; i < 16; i++)
        m_M[i]  = M[i];
}
/** Copy function for copy constructor and operator =. */
void CGLMatrix::copy(const CGLMatrix & toCopy){
    if(this != &toCopy){
        for(int i = 0; i <16; i++)
            m_M[i] = toCopy.m_M[i];
    }
}
/** Operator = copies m_M. */
const CGLMatrix  CGLMatrix::operator =(const CGLMatrix & toCopy){
    copy(toCopy);
    return * this;
}
/** Copy constructor. */
CGLMatrix::CGLMatrix(const CGLMatrix & toCopy){
    copy(toCopy);
}
/** Calculations run on main fpu. Use glMultMatrix for calculation on graphics processor.
    *  Matrix multiplication m_M * m2. !!!WARNING: ORDER OF MATRICES IS CRITICAL!!! (m_M*m2 != m2*m_M)
    *  The result element result[i,j] is obtained by multiplying all elements of row i  of matrix m_M with the elements
    *  of column j of matrix m2 and adding the products.  Mathematical row and column numbers usually start with a 1
    *  and not with a 0 as in C++.
    *  This has to be translated into the column major order of the OpenGL matrix, where the elements are held in m_M[16].
    *  A 1 based row i is addressed by: m_M[i-1], m_M [i+3], m_M[i+7], m_M[i+11].
    *  A 0 based row i is addressed by: m_M[i], m_M [i+4], m_M[i+8], m_M[i+12] = m_M[row + 4 * column].
    *  A 1 based column j is addressed by: m2[(j-1)*4], m_M[(j-1)*4 +1, m_M[(j-1)*4 +2, m_M[(j-1)*4 +3].
    *  A 0 based column j is addressed by: m2[j*4], m_M[j*4 +1], m_M[j*4 +2], m_M[j*4 +3] = m_M[4*column + row].
    *  The operator * runs through m_M[16] by zero based rows and columns, which is not the fastest, however a pretty
    *  obvious way of calculating the product. For top speed, use 16 separately hard coded sums.
    */
const CGLMatrix CGLMatrix::operator *(const CGLMatrix & m2) const{
    GLfloat result[16];
    int row, column, fourTimesColumn;
    for(row = 0; row<4; row++)            //rows 0 to 3, mathematical i = 1 to 4
        for (column =0; column <4; column ++){  //columns 0 to 3, mathematical j= 1 to 4
        fourTimesColumn = 4 * column;
        result[row + 4 * column] =
                m_M[row]       * m2.m_M[fourTimesColumn]
                +  m_M[row + 4]   * m2.m_M[fourTimesColumn + 1]
                +  m_M[row + 8]   * m2.m_M[fourTimesColumn + 2]
                +  m_M[row + 12]  * m2.m_M[fourTimesColumn + 3];
    }
    return CGLMatrix(result);
}
/** Writes matrix coefficients to stderr. */
void CGLMatrix::debug(QString caption){
    QString line, s;
    int row, column;
    qDebug("CGLMatrix debug output: " + caption.toLatin1());
    for (row = 0; row <4; row++){
        line= "row " + s.setNum(row+1) +": ";
        for(column = 0; column <4; column++){
            line += "  "+ s.setNum(m_M[column * 4 + row], 'g', 4);
        }
        qDebug(line.toLatin1());
    }
    qDebug("End of CGLMatrix debug output.\n");
}
/** Returns the transposed matrix m^T.
   */
CGLMatrix CGLMatrix::transpose()const{
    GLfloat t[16];
    int row, column;
    for (row = 0; row <4; row++){
        for(column = 0; column <4; column++){
            t[row*4 + column] = m_M[row + column *4];
        }//end for column
    }// end for row
    return CGLMatrix(t);
}
/** Returns the determinant.  Because it is rather probable, that the elements of the last row are 0, 0, 0 , 1,
   * the determinant is calculated based on the last row (row number 4).  The determinantes of the 3 by 3 matrices are
   * calculated using Sarrus' law.
   */
GLfloat CGLMatrix::determinant(){
    GLfloat result = 0.0;
    if(m(1, 4) != 0.0)
        result -= m(1,4) * calcSarrus(1);
    if(m(2, 4) != 0.0)
        result += m(2,4) * calcSarrus(2);
    if(m(3, 4) != 0.0)
        result -= m(3,4) * calcSarrus(3);
    if(m(4,4) != 0.0)
        result += m(4,4) * calcSarrus(4);

    QString s;
    qDebug("determinant value: " + s.setNum(result, 'g', 4).toLatin1());

    return result;
}
/** Calculates the determinant using Sarrus' law fo 3 by 3 matrices.
   * The 3 by 3 sub-matrix is obtained by deleting the last row (row 4) and the specified column.
   */
GLfloat CGLMatrix::calcSarrus(int deletedColumn){
    int sourceColumn = 0;
    int destColumn = 1;
    int row = 1;
    GLfloat result;
    CGLMatrix dest;   //zero init using standard constructor
    //create a 3 by 3 matrix from the top 3 rows, and delete specified column
    for(destColumn =1; destColumn <=3; destColumn++) {
        sourceColumn++;
        if(sourceColumn == deletedColumn)
            sourceColumn++;  //skip deleted column
        for(row = 1; row <=3; row ++){
            dest.setM(destColumn, row, m(sourceColumn, row));
        } //end for row
    }//end for sourceColumn

    result=
            dest.m(1,1) * dest.m(2,2) * dest.m(3,3)       //Sarrus law
            + dest.m(1,2) * dest.m(2,3) * dest.m(3,1)
            + dest.m(1,3) * dest.m(2,1) * dest.m(3,2)
            - dest.m(1,3) * dest.m(2,2) * dest.m(3,1)
            - dest.m(1,1) * dest.m(2,3) * dest.m(3,2)
            - dest.m(1,2) * dest.m(2,1) * dest.m(3,3);
    QString s;
    dest.debug("Sub matrix without column " + s.setNum(deletedColumn));
    qDebug("Sarrus value: " + s.setNum(result, 'g', 4).toLatin1());
    return result;
}
/** Returns matrix element row, column. For mathematical convenience, row and column numbers start with 1.
  *  Use getMatrix for direct access to single index zero based matrix element array, as required by OpenGL functions.
  */
GLfloat CGLMatrix::m(int row, int column){
    return m_M[row -1 + (column -1) *4];
}
/** Sets matrix element in row and column. Row and column numbers start with 1. */
void CGLMatrix::setM(int row, int column, GLfloat value){
    m_M[row -1 + (column -1) * 4] = value;
}
/** Loads the current modelview matrix.
 */
void CGLMatrix::loadModelview(){
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&m_M);
}
/** Multiplies the matrix onto the current matrix stack <b>without saving </b>the current matrix on that stack.
 */
void CGLMatrix::multToStack()const{
    glMultMatrixf((GLfloat*)&m_M);
}
