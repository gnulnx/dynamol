/***************************************************************************
                          trackball.cpp  -  description
                             -------------------
    begin                : Sun Dec 28 2003
    copyright            : (C) 2003 by John Furr
    email                : jrflnx@yahoo.com
 ***************************************************************************/

#include "trackball.h"
#include "linAlg.h"

#include <fstream>
using namespace std;

TrackBall::TrackBall(){
  sphereRadius = 0.8;
}
TrackBall::~TrackBall(){
}

//Don't need to cann quat by  reference for performance as C++ already does this
void TrackBall::trackball (float quat[4], float px1, float py1, float px2, float py2) {
	float axis[3]; //axis of rotation
	float phi;  //How much to rotate
	float point1[3], point2[3], dist[3];   //coords of point 1 to && 2 && d is subtracted dest
	float temp; //A temporary variable

	if (px1 == px2 && py1 == py2) {
		//Might want to call vZero here.  I don't think so tho.
		quat[0] = 0.0;
		quat[1] = 0.0;
		quat[2] = 0.0;
		quat[3] = 1.0;
		return;
	}

	
	/*
	Determine the z coordinate by mapping scaled 2D mouse coords to Sphere.
	*/

	//sphereRadius =  (fabs(px1-px2)/fabs(py1*py2));
	//cout <<"sphereRadius: " << sphereRadius << endl;
	point1[0] = px1;
	point1[1] = py1;
	point1[2] = mapToSphere(sphereRadius, px1, py1);

	point2[0] = px2;
	point2[1] = py2;
	point2[2] = mapToSphere(sphereRadius, px2, py2);
	//cout <<"x: " << point2[0] <<"  y: " << point2[1]<<"  z: " << point2[2];

	/*
	Take the cross Product of point1 && point2 && store it
	as the axis of rotation.  THis will be the axis that we rotate around
	
	** NOte.  vCross returns the cross product of point1 and point2 as the axis.
	*/
	vCross(point1, point2, axis);

	/*
	Determine how much to rotate around the previously determined axis
	*/
	vSub(point1, point2, dist);
	temp = sqrt(dist[0]*dist[0] + dist[1]*dist[1] + dist[2]*dist[2]) / (2.0*sphereRadius);
	//ofstream outFile("test_data.txt", ios::app);
	
	//cout << fabs(px1-px2) / fabs(py2-py1) << endl;
	//outFile <<px1*px2<<", "<<py1*py2<<", "<< temp << endl;
	//cout <<"temp: " << temp << endl;
	if (temp > 1.0)
		temp = 1.0;
	if (temp < -1.0)
		temp = -1.0;

	phi =  5.0*asin(temp);
	axisToQuat(axis, phi, quat);
}
void TrackBall::axisToQuat(float axis[3], float phi, float quat[4]) {
  vNormal(axis);
  quat[0] = axis[0];
  quat[1] = axis[1];
  quat[2] = axis[2];
  vScale(quat, sin(phi/2.0));
  quat[3] = cos(phi/2.0);
}

float TrackBall::mapToSphere(float rad, float x, float y) {


  
  float dist, t, z;
  dist = sqrt(x*x + y*y);
  if (dist < rad*0.70710678118654752440) {
    z = sqrt(rad*rad-dist*dist);
  } else {
    // t is used here to speed up calculation.  Otherwise an extra division step would ber needed
    t = rad / 1.41421356237309504880;
    z = t*t/dist;
  }

  return z;

}

void TrackBall::addQuats(float quat1[4], float quat2[4], float dest[4]) {
	static int count = 0;  //uesd to determine if quat needs to be normalized
	float temp1[4], temp2[4], temp3[4];
	float tempFinal[4];

	vCopy(quat1, temp1);
	vScale(temp1, quat2[3]);

	vCopy(quat2, temp2);
	vScale(temp2, quat1[3]);

	vCross(quat2, quat1, temp3);
	vAdd(temp1, temp2, tempFinal);
	vAdd(temp3, tempFinal, tempFinal);
	tempFinal[3] = quat1[3]*quat2[3] - vDot(quat1, quat2);

	dest[0] = tempFinal[0];
	dest[1] = tempFinal[1];
	dest[2] = tempFinal[2];
	dest[3] = tempFinal[3];

	if (++count > 10) {
		count = 0;
		normalizeQuat(dest);
	}

}

void TrackBall::normalizeQuat(float quat[4]) {
  float mag;

  mag = (quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3]);
  for (int i=0; i<4; i++) {
    quat[i] /= mag;
  }

}

void TrackBall::buildRotMat(GLfloat m[4][4], float quat[4]) {

  m[0][0] = 1.0-(2.0*(quat[1]*quat[1] + quat[2]*quat[2]));
  m[0][1] = 2.0*(quat[0]*quat[1] - quat[2]*quat[3]);
  m[0][2] = 2.0*(quat[2]*quat[0] + quat[1]*quat[3]);
  m[0][3] = 0.0;

  m[1][0] = 2.0*(quat[0]*quat[1] + quat[2]*quat[3]);
  m[1][1] = 1.0-(2.0*(quat[2]*quat[2] + quat[0]*quat[0]));
  m[1][2] = 2.0*(quat[1]*quat[2] - quat[0]*quat[3]);
  m[1][3] = 0.0;

  m[2][0] = 2.0*(quat[2]*quat[0] - quat[1]*quat[3]);
  m[2][1] = 2.0*(quat[1]*quat[2] + quat[0]*quat[3]);
  m[2][2] = 1.0-(2.0*(quat[1]*quat[1] + quat[0]*quat[0]));
  m[2][3] = 0.0;

  m[3][0] = 0.0;
  m[3][1] = 0.0;
  m[3][2] = 0.0;
  m[3][3] = 1.0;
}






































