/***************************************************************************
                          quat.cpp  -  description
                             -------------------
    begin                : Wed Mar 3 2004
    copyright            : (C) 2004 by John Furr
    email                : 
 ***************************************************************************/


#include "quat.h"

namespace dynacomp {

QUAT::QUAT(float w, float x, float y, float z){
  this->w = w;
  vec[0]  = x;
  vec[1] = y;
  vec[2] = z;
}

//Note the angle should be in radians
QUAT::QUAT(float radian, float axis[3]) {
  vNormal(axis);  //get unit vector vor axis

  float *q = &w;
  float sin_a = sin(radian/2.0);
  
  q[0] = cos(radian/2.0);
  q[1] = axis[0]*sin_a;
  q[2] = axis[1]*sin_a;
  q[3] = axis[2]*sin_a;
  normalize();  //make sure that quat is normalized
}

QUAT::QUAT() {};

QUAT::~QUAT(){
}

const QUAT QUAT::operator*(const QUAT &q1) {

  float *q = &w;
  float t0 = (q[3]-q[2]) * (q1[2]+q1[3]);
  float t1 = (q[0]+q[1]) * (q1[0]+q1[1]);  //  (r+i)*(b.r + b.i);
  float t2 = (q[0]-q[1]) *  (q1[2]+q1[3]);
  float t3 = (q[3]+q[2]) * (q1[0]-q1[1]);
  float t4 = (q[3]-q[1]) * (q1[1]-q1[2]);
  float t5 = (q[3]+q[1]) * (q1[1]+q1[2]);
  float t6 = (q[0]+q[2]) * (q1[0]-q1[3]);
  float t7 = (q[0]-q[2]) * (q1[0]+q1[3]);
  float t8 = t5+t6+t7;
  float t9 = (t4+t8)*0.5;
  QUAT retQuat;
  retQuat.w = t0+t9-t5;
  retQuat.vec[0] = t1+t9-t8;
  retQuat.vec[1] = t2+t9-t7;
  retQuat.vec[2] = t2+t9-t6;
  retQuat.vec[3] = t3+t9-t6;
  return retQuat;
  //return *this;
}

const QUAT QUAT::operator*(const float v[3]) {
  QUAT retQuat;

  retQuat.w = 0;

  float vec1[3], cross[3];
  vec1[0] = v[0]*w;
  vec1[1] = v[1]*w;
  vec1[2] = v[2]*w;

  vCross(vec, v,  cross);
  vAdd(vec1, cross, retQuat.vec);

  return retQuat;
}

const QUAT &QUAT::operator=(const QUAT &q1) {
  w = q1.w;
  vec[0] = q1.vec[0];
  vec[1] = q1.vec[1];
  vec[2] = q1.vec[2];
  return *this;
}

const QUAT &QUAT::operator~(void) {
  vec[0] = -vec[0];
  vec[1] = -vec[1];
  vec[2] = -vec[2];

  return *this;
}

float QUAT::operator[](unsigned int index) const {
  return *(&w+index);
}

float &QUAT::operator[](unsigned int index)  {
  return *(&w+index);
}

/*
const float QUAT::operator[](int index) {

  return *(&w+index);
}
*/
/*
void QUAT::buildMatrix(float mat[16]) {
  //############# NOTE ABOUT NOTATION ###############
  //############# IMPORTANT  READ  ####################
  //The notation in this function is set backwards...when you went from openGL for X-Windows book to QUAT class you reversed the
  //way that you think about quaternions...this however should still work
  float *q = &w;
  float xx = q[0]*q[0];
  float xy = q[0]*q[1];
  float xz = q[0]*q[2];
  float xw = q[0]*q[3];

  float yy = q[1]*q[1];
  float yz = q[1]*q[2];
  float yw = q[1]*q[3];

  float zz = q[2]*q[2];
  float zw = q[2]*q[3];

  float ww = q[3]*q[3];

  mat[0] = 1-2 * (yy+zz);
  mat[1] = 2*(xy-zw);
  mat[2] = 2*(xz+yw);
  mat[3] = 0;

  mat[4] = 2 * (xy+zw);
  mat[5] = 1-2 * (xx + zz);
  mat[6] = 2 * (yz - xw);
  mat[7] = 0;

  mat[8] = 2 * (xz - yw);
  mat[9] = 2 * (yz + xw);
  mat[10] = 1 - 2 * (xx + yy);
  mat[11] = 0;

  mat[12] = 0;
  mat[13] = 0;
  mat[14] = 0;
  mat[15] = 1;
}
*/
void QUAT::buildMatrix(float mat[16]) {
   //############# NOTE ABOUT NOTATION ###############
  //############# IMPORTANT  READ  ####################
  //The notation in this function is set backwards...when you went from openGL for X-Windows book to QUAT class you reversed the
  //way that you think about quaternions...this however should still work
  float *q = &w;

  float xw = q[1]*q[0];
  float xx = q[1]*q[1];
  float xy = q[1]*q[2];
  float xz = q[1]*q[3];
 
  float yw = q[2]*q[0];
  float yy = q[2]*q[2];
  float yz = q[2]*q[3];
  
  float zw = q[3]*q[0];
  float zz = q[3]*q[3];


  //float ww = q[0]*q[0];

  mat[0] = 1-2 * (yy+zz);
  mat[1] = 2*(xy-zw);
  mat[2] = 2*(xz+yw);
  mat[3] = 0;

  mat[4] = 2 * (xy+zw);
  mat[5] = 1-2 * (xx + zz);
  mat[6] = 2 * (yz - xw);
  mat[7] = 0;

  mat[8] = 2 * (xz - yw);
  mat[9] = 2 * (yz + xw);
  mat[10] = 1 - 2 * (xx + yy);
  mat[11] = 0;

  mat[12] = 0;
  mat[13] = 0;
  mat[14] = 0;
  mat[15] = 1;

}

void QUAT::normalize() {
  float *q = &w;
  float mag = 0;
  for (int i=0; i<4; i++) mag += q[i]*q[i];
  mag = 1.0/sqrt(mag);
  for (int i=0; i<4; i++) q[i] *= mag;
}

}//End Namespace



































