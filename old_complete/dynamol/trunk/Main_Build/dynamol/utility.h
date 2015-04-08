/***************************************************************************
                          utility.h  -  description
                             -------------------
    begin                : Sun Oct 19 2003
    copyright            : (C) 2003 by 
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

struct ctrlPoint {
  float patch[2][2][3];
};


struct ctrlPoint_16 {
  float patch[4][4][3];
};

struct guidePoints {
  //vector<float> P1, P2, P3, P4;
  float P1[3], P2[3], P3[3], P4[3];
};






































