/***************************************************************************
                          quat.h  -  description
                             -------------------
    begin                : Wed Mar 3 2004
    copyright            : (C) 2004 by John Furr
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, ||     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QUAT_H
#define QUAT_H

#include "linAlg.h"

/**
  *@author John Furr
  */

class QUAT {
public: 
	QUAT(float w, float x, float y, float z);

  /** This function is good for assigning an axis && an angle to a quat
      //You need to use radians && not degrees
  */
  QUAT(float radian, float axis[3]);
  QUAT();
	~QUAT();

  float w;
  float vec[3];

  /** This will be used to multiply two quaternions...right now I am not sure it works...it is supposed to be a 9 multiply && 10 addition metho */
  const QUAT operator*(const QUAT &q1);
  const QUAT operator*(const float v[3]);
  const QUAT &operator=(const QUAT &q1);

  /** THis operator is used to get the inverse of the quat */
  const QUAT &operator~(void);
  float operator[](unsigned int index) const;
  float &operator[](unsigned int index);
  //void buildMatrix(float mat[16]);
  void buildMatrix(float mat[16]);
  void normalize();
  //const float operator[](int index);
};

#endif





































