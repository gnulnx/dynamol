/***************************************************************************
                          quat.h  -  description
                             -------------------
    begin                : Wed Mar 3 2004
    copyright            : (C) 2004 by John Furr
    email                : 
 ***************************************************************************/


#ifndef DYNACOMPQUAT_H
#define DYNACOMPQUAT_H

#include "linAlg.h"

namespace dynacomp {
/** \brief A Quaternion class.  
*
*  Mainly used in the Dynamol Molecular Viewer, but it will probably 
*  prove quite useful in numerous future computational algorithms
*  <pre>
*  The Documentation is Horrible.
*  Horrible I say.  
*  You will need to look at quat.h and quat.cpp to get a feel for what this class
*  is doing
*  </pre>
*  @author John Furr
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

  /** This will be used to multiply two quaternions...right now I am not sure it works...it is supposed to be a 9 multiply && 10 addition metho */
  const QUAT operator*(const QUAT &q1);
  const QUAT operator*(const float v[3]);
  const QUAT &operator=(const QUAT &q1);

  /** THis operator is used to get the inverse of the quat */
  const QUAT &operator~(void);
  float operator[](unsigned int index) const;
  float &operator[](unsigned int index);
  void buildMatrix(float mat[16]);
  void normalize();
  
  
  float w;
  float vec[3];

};

};// End Namespace
#endif





































