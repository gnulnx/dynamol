/***************************************************************************
                          linalg.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include "quat.h"

using namespace std;

class QUAT;

///////////////////////////////////////////////////////
#define always_inline inline __attribute__( ( always) )
///////////////////////////////////////////////////////

/** function to normalize a vector of arbitrary size
*/

void  normalizef( vector< float > &vec);

//This should be a faster normalizing routine for 3D vectors.
void  normalize_3f( vector< float > &vec);

/** this performs the cross product of two vectors
*/
void crossProd(float *prod, const float *a, const float *b);
void  crossProd(vector<float> &prod, const vector<float> &a, const vector<float> &b);

/** This function translates the vector by x, y, z
*/
void  translate(vector<float> &coords, float x, float y, float z);

/** This function takes two points on a line && returns the direction cosines
*/
//vector<float> &dirCosines(const vector<float> &coords1, const vector<float> &coords2);

/** Return a pointer to a 3D array which is contains the direction cosines for two points
*/
vector<double> dirCosines(float *coords1, float *coords2);

/** calculates the direction cosines from two 3D array && puts the result in retVec
*/
void  dirCosines(vector<double> &retVec, float *coords1, float *coords2);

/** multiply to matrices vector<16>
*/
vector<float> multTransMatrix(const vector<float> &mat1, const vector<float> &mat2);

/** multiply two vector<16> matrices && store result in retMat
    This method works similar to the above function
*/
void  multTransMatrix_16(vector<float> &retMat, const vector<float> &mat1, const vector<float> &mat2);

/** like the above function but for a vector fo size 4
*/
void  multTransMatrix_4(float retMat[4], const float mat1[4], const float mat2[16]);
/*always_inline*/ void  multTransMatrix_4(vector<float> &retMat, const vector<float> &mat1, const vector<float> &mat2);/*  {
 retMat[0] = mat1[0]*mat2[0] + mat1[1]*mat2[4] + mat1[2]*mat2[8] + mat1[3]*mat2[12];
 retMat[1] = mat1[0]*mat2[1] + mat1[1]*mat2[5] + mat1[2]*mat2[9] + mat1[3]*mat2[13];
 retMat[2] = mat1[0]*mat2[2] + mat1[1]*mat2[6] + mat1[2]*mat2[10] + mat1[3]*mat2[14];
 retMat[3] = mat1[0]*mat2[3] + mat1[1]*mat2[7] + mat1[2]*mat2[11] + mat1[3]*mat2[15];
};
*/

void  multTransMatrix_4(vector<float> &retMat, const float *, const vector<float> &mat2);


/** Multiply two matrices || arbitrary size
*/
vector<float>  multiMatrix(const vector<float> &vec, const vector<float> &mat);

/** This method is like the one above but it is overloaded so that the ret matrix is passed by
    reference instead of returned by value...DUH
*/
void  multiMatrix(vector<float> &retMat, const vector<float> &mat1, const vector<float> &mat2);

/**initializes a vector
*/
vector<float> initMat(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);

/** set to identity
*/

void  identity(vector<float> &mat);


/** Set rotX matrix
*/
void  setRotX(vector<float> &mat, float p1, float p2);

/** Overlaoded for.  This guy takes an angle as the operator..
 
*/
void  setRotX(vector<float> &mat, float angle);

/**Set rotY matrix
*/
void  setRotY(vector<float> &mat, float p1, float p2);


/** overloaded to take an angle
*/
void setRotY(vector<float> &mat, float angle);

/**Set rotZ matrix
*/
void  setRotZ(vector<float> &mat, float p1, float p2);

/**Overloaded  so that the rotation matrix can take an arbitraru rotation angle
*/
void setRotZ(vector<float> &mat, float angle);

/** Set translation amtrix
*/
void  setTransMat(vector<float> &mat, float x, float y, float z);

/** print the matrix in matrix like format
*/
void  printMatrix(const vector<float> &mat);


/** void invert a 4x4 matrix
*/
void invertMatrix(vector<float> &mat, vector<float> &des);

/** Calculate the distance between two 3D-Arrays
*/
float dist(const vector<float> &p1, const vector<float> &p2);

/** calculate the distance between to 3 point array
*/
float distance(float *p1, float *p2);

double distance(vector<double> &p1, vector<double> &p2);

/** This makes a quat a rotation matrix in collumn major format...like openGL */
void quatToMatrix(vector<float> &mat, vector<float> &quat);



/** This makes the quat a rotation matrix in row major format */
void quatToMatrix_row(vector<float> &mat, vector<float> &quat);

/*Given an axis && an angle computer quaternion */
void axis_to_quat(vector<float> &axis, float phi, vector<float> &quat);

void axis_to_quat(float axis[], float phi, float quat[]);

/** Multiplies to quats */
void  multQuats(vector<float> &res, const vector<float> &q1, const vector<float> &q2);

/** This converts from a row major matrix to a collumn major format */
void rowToColumn(float *ret, const float *row);

void rowToColumn(vector<float> &col, const vector<float> &row);


//THis is the new stuff...what you should be using
void quatToMatrix(float mat[], float quat[]);

void quatToMatrix(vector<float> &mat, vector<float> &quat);

void mulit_4X16(float retVec[], float vec[], float mat[]);

void mulit_4X16(vector<float> &retVec, vector<float> &vec, vector<float> &mat);

//routine to normlize a vector
void  normalizef(float vec[], const int size);

void normalized(double vec[], const int size);

void buildRotMat(float m[4][4], float quat[4]);

/** this performs the cross product of two vectors
*/
void  vCross(const float vec1[3], const float vec2[3], float prod[3]) ;

/** This is the dot product of two vectors
 */
float vDot(const float vect1[3], const float vect2[3]);

/** This function subtracts two vectors
*/
void vSub(const float point1[3], const float point2[3], float dest[3]);

/** THis function adds two vectors
*/
void vAdd(const float vect1[3], const float vect2[3], float dest[3]);

/** This zeros out a vector
*/
void vZero(float vect[]);

/* This copies two vectors
*/
void vCopy(float vect1[], float vect2[]); //Might remove this && hard code it were it needs to go

/* This noramlizes a vector
*/
void vNormal(float vect[3]);

/* This scales a vector by an arbitrary constant
*/
void vScale(float vect[3], float divisor);

/** This function returns the angle in degrees between three points in spaces */

float angleDegrees(const float cd1[3], const float mid[3], const float cd2[3]);
float angleRadians(const float cd1[3], const float mid[3], const float cd2[3]);

void quatToMatrix(QUAT q, float mat[16]);

float vLength(float vec[3]);


/** This function uses quaternions to overlay two lines l1 & l2
*   The function will translate the l2_p1 to l1_p1.  It will then 
*   rotate l2 such that l2_p2 is pointing in the same direction as l1_p2
*/
void alignLines(const float *l1_p1, const float *l1_p2, float *l2_p1, float *l2_p2);

void alignLines(const vector<float> &l1_p1, const vector<float> &l1_p2,
	              vector<float> &l2_p1, vector<float> &l2_p2);






































