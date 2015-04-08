/***************************************************************************
                          trackball.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@gmail.com


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

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





































