/***************************************************************************
                          trackball.h  -  description
                             -------------------
    begin                : Sun Dec 28 2003
    copyright            : (C) 2003 by John Furr
    email                : jrflnx@yahoo.com
 ***************************************************************************/

#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <math.h>
#include <iostream>

typedef float   GLfloat;
typedef double  GLdouble;

using namespace std;

/**
	*@author John Furr

	This class contains the routines to generate quaternions.  It also contains functions to build the
	rotation matrix
*/

class TrackBall {
public: 
	TrackBall();
	~TrackBall();

	void trackball (float quat[4], float px1, float py1, float px2, float py2);
	void addQuats(float quat1[4], float quat2[4], float dest[4]);
	void buildRotMat(GLfloat m[4][4], float quat[4]);
	void axisToQuat(float a[3], float phi, float quat[4]);
	void normalizeQuat(float quat[4]);
	float mapToSphere(float rad, float x, float y);
  
private:
	float sphereRadius;

      
};

#endif





































