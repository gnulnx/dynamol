/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "buildsurface.h"
#include "molview.h"
#include "xmodelview.h"
#include "molchangeevent.h"
#include <qapplication.h>
#include <fstream>
#include <iomanip>
#include <map>
#include <stack>
#include <set>
#include "atom.h"
#include "nsc.h"
#include "linAlg.h"
#include "math.h"
#include "time.h"


//Triangle Strip Program Includes
//#include "StdAfx.h"

XYZ VertexInterp(double isolevel,XYZ p1, XYZ p2,double valp1,double valp2);

/*
   Given a grid cell and an isolevel, calculate the triangular
   facets required to represent the isosurface through the cell.
   Return the number of triangular facets, the array "triangles"
   will be loaded up with the vertices at most 5 triangular facets.
   0 will be returned if the grid cell is either totally above
   of totally below the isolevel.
*/
//int Polygonise(GRIDCELL grid,double isolevel, vector<TRIANGLE> &TRIS, surface *surf)
int Polygonise(GRIDCELL grid,double isolevel, vector<TRIANGLE> &TRIS, boost::shared_ptr<surface> &surf)
{
   int i,ntriang;
   int cubeindex;
   XYZ vertlist[12];

int edgeTable[256]={
0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0   };
int triTable[256][16] =
{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
{3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
{3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
{3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
{9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
{9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
{2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
{8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
{9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
{4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
{3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
{1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
{4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
{4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
{5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
{2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
{9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
{0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
{2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
{10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
{5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
{5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
{9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
{0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
{1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
{10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
{8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
{2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
{7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
{2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
{11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
{5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
{11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
{11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
{1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
{9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
{5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
{2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
{5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
{6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
{3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
{6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
{5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
{1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
{10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
{6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
{8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
{7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
{3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
{5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
{0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
{9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
{8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
{5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
{0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
{6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
{10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
{10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
{8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
{1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
{0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
{10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
{3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
{6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
{9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
{8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
{3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
{6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
{0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
{10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
{10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
{2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
{7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
{7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
{2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
{1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
{11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
{8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
{0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
{7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
{10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
{2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
{6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
{7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
{2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
{1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
{10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
{10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
{0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
{7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
{6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
{8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
{9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
{6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
{4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
{10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
{8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
{0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
{1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
{8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
{10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
{4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
{10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
{5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
{11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
{9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
{6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
{7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
{3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
{7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
{3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
{6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
{9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
{1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
{4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
{7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
{6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
{3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
{0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
{6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
{0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
{11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
{6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
{5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
{9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
{1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
{1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
{10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
{0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
{5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
{10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
{11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
{9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
{7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
{2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
{8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
{9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
{9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
{1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
{9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
{9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
{5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
{0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
{10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
{2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
{0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
{0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
{9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
{5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
{3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
{5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
{8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
{0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
{9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
{1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
{3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
{4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
{9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
{11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
{11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
{2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
{9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
{3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
{1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
{4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
{3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
{0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
{9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
{1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

   /*
      Determine the index into the edge table which
      tells us which vertices are inside of the surface
   */
   cubeindex = 0;
   if (grid.val[0] < isolevel) cubeindex |= 1;
   if (grid.val[1] < isolevel) cubeindex |= 2;
   if (grid.val[2] < isolevel) cubeindex |= 4;
   if (grid.val[3] < isolevel) cubeindex |= 8;
   if (grid.val[4] < isolevel) cubeindex |= 16;
   if (grid.val[5] < isolevel) cubeindex |= 32;
   if (grid.val[6] < isolevel) cubeindex |= 64;
   if (grid.val[7] < isolevel) cubeindex |= 128;

   /* Cube is entirely in/out of the surface */
   if (edgeTable[cubeindex] == 0) 
      return(0);

   /* Find the vertices where the surface intersects the cube */
   if (edgeTable[cubeindex] & 1)
      vertlist[0] =
         VertexInterp(isolevel,grid.p[0],grid.p[1],grid.val[0],grid.val[1]);
   if (edgeTable[cubeindex] & 2)
      vertlist[1] =
         VertexInterp(isolevel,grid.p[1],grid.p[2],grid.val[1],grid.val[2]);
   if (edgeTable[cubeindex] & 4)
      vertlist[2] =
         VertexInterp(isolevel,grid.p[2],grid.p[3],grid.val[2],grid.val[3]);
   if (edgeTable[cubeindex] & 8)
      vertlist[3] =
         VertexInterp(isolevel,grid.p[3],grid.p[0],grid.val[3],grid.val[0]);
   if (edgeTable[cubeindex] & 16)
      vertlist[4] =
         VertexInterp(isolevel,grid.p[4],grid.p[5],grid.val[4],grid.val[5]);
   if (edgeTable[cubeindex] & 32)
      vertlist[5] =
         VertexInterp(isolevel,grid.p[5],grid.p[6],grid.val[5],grid.val[6]);
   if (edgeTable[cubeindex] & 64)
      vertlist[6] =
         VertexInterp(isolevel,grid.p[6],grid.p[7],grid.val[6],grid.val[7]);
   if (edgeTable[cubeindex] & 128)
      vertlist[7] =
         VertexInterp(isolevel,grid.p[7],grid.p[4],grid.val[7],grid.val[4]);
   if (edgeTable[cubeindex] & 256)
      vertlist[8] =
         VertexInterp(isolevel,grid.p[0],grid.p[4],grid.val[0],grid.val[4]);
   if (edgeTable[cubeindex] & 512)
      vertlist[9] =
         VertexInterp(isolevel,grid.p[1],grid.p[5],grid.val[1],grid.val[5]);
   if (edgeTable[cubeindex] & 1024)
      vertlist[10] =
         VertexInterp(isolevel,grid.p[2],grid.p[6],grid.val[2],grid.val[6]);
   if (edgeTable[cubeindex] & 2048)
      vertlist[11] =
         VertexInterp(isolevel,grid.p[3],grid.p[7],grid.val[3],grid.val[7]);

   /* Create the triangle */
   ntriang = 0;
   XYZ xyz[3];
   for (i=0;triTable[cubeindex][i]!=-1;i+=3) {
      xyz[0] = vertlist[triTable[cubeindex][i  ]];
      xyz[1] = vertlist[triTable[cubeindex][i+1]];
      xyz[2] = vertlist[triTable[cubeindex][i+2]];
      for(int j=0; j<3; j++) {
         surf->verts.push_back(xyz[j].x);
         surf->verts.push_back(xyz[j].y);
         surf->verts.push_back(xyz[j].z);
      }
      ntriang++;
   }

   return(ntriang);
}

/*
   Linearly interpolate the position where an isosurface cuts
   an edge between two vertices, each with their own scalar value
*/
XYZ VertexInterp(double isolevel,XYZ p1, XYZ p2,double valp1,double valp2)
{
   double mu;
   XYZ p;

   if (fabs(isolevel-valp1) < 0.00001)
      return(p1);
   if (fabs(isolevel-valp2) < 0.00001)
      return(p2);
   if (fabs(valp1-valp2) < 0.00001)
      return(p1);
   mu = (isolevel - valp1) / (valp2 - valp1);
   p.x = p1.x + mu * (p2.x - p1.x);
   p.y = p1.y + mu * (p2.y - p1.y);
   p.z = p1.z + mu * (p2.z - p1.z);
  
   //Normal Section
   //p.norm[0] = p1.norm[0] + mu * (p2.norm[0] - p1.norm[0]);
   //p.norm[1] = p1.norm[1] + mu * (p2.norm[1] - p1.norm[1]);
   //p.norm[2] = p1.norm[2] + mu * (p2.norm[2] - p1.norm[2]);
   return(p);
}

// #######################################################################
// #################### NOW START REAL BUILD SURFACE FILE #################
//#########################################################################
buildSurface::buildSurface(molView *view, const char *name) 
: dynoThread(NULL) 
{
   acgs = false;
   elecColor = false;
   atomColor = false;
   smoothAtomColor = false;
   solidColor = false;

   this->view = view;
   view->infoText.push_back("Building Surface");
}

void buildSurface::setColor(float r, float g, float b) {
   Red = r;
   Green = g;
   Blue = b;
}

//void buildSurface::molSurfSetup(molStruct *ms, float res, float alpha, float trans, string color)
void buildSurface::molSurfSetup(boost::shared_ptr<molStruct> ms, boost::shared_ptr<surface> surf,
                                float res, float alpha, float trans, string color) 
{
  this->ms = ms;

  surf->show = false;
  s = surf;
  this->res = res;
  //cout <<"Res: " << res << endl;

  this->alpha = alpha;
  if (alpha > 3.4)
     bspWidth = 3.0;
  if (alpha <= 3.4)
     bspWidth = 4.5;

  this->color = color;
  if (color == "Electrostatic") {
     elecColor = true;
     atomColor = false;
     smoothAtomColor = false;
     solidColor = false; 
  }
  if (color == "Atom Color") {
    elecColor = false;
    atomColor = true;
    smoothAtomColor = false;
    solidColor = false;

  }
  if (color == "AC-GS") {
     elecColor = false;
     acgs = true;
     smoothAtomColor = false;
     solidColor = false;
  }
  if (color == "Solid") {
    elecColor = false;
    atomColor = false;
    smoothAtomColor = false;
    solidColor = true;
  }
  if (color == "Smooth Atom Color") {
     elecColor = false;
     atomColor = false;
     smoothAtomColor = true;
     solidColor = false;
  }
  this->trans = trans;

  this->view = view;
  gran = 0.001;
  igran = 1.0/gran;

  int count = 0;
  expLookup.resize(101.0/gran+1);
  for (float i=gran; i<100; i+=gran) {
     expLookup[count] = exp(-this->alpha*i);
     count++;
  }

  distLookup.resize(651.0/gran+1);
  count = 0;
  for (float i=gran; i<650; i+=gran) {
     distLookup[count] = exp(-.5*i); 
     count++;
  }
}


buildSurface::~buildSurface()
{
}

void buildSurface::bspSetup() {
   int size = ms->coords.size()/3;
   vector<dynacomp::point *> Points(size);
   int index = 0;
   for (int j=0; j<size; j++) {
      Points[j] = new dynacomp::point(j+1, &ms->coords[index], 0.0);
      index+=3;
   }

   bsp.reset( new BSP(3, Points) );

   int count = 0;
   for (int i=0; i<ms->coords.size(); i+=3) {
      float *center = &ms->coords[i];
      vector<dynacomp::point *> hits;
      bsp->getPoints(center, hits, bspWidth);
      vector<int> coordIndex(hits.size());
      float total = 0;
      for (int i=0; i<hits.size(); i++) {
         int num = hits[i]->num-1;
         float *cd = &ms->coords[num*3];
         float dist = distance(center, cd);
         if (!dist == 0) {
            total += exp(0.8*dist);
         }
      }

      if (total < 5000) {
         count++;
      }
   }

   
 
}

void buildSurface::bspSetup(vector<atom *> &ATOMS) {
   vector<dynacomp::point *> Points(ATOMS.size());
   //END BSP PLAY

   for (int j=0; j<ATOMS.size(); j++) {
      float size = 0.0;
      Points[j] = new dynacomp::point(j+1, ATOMS[j]->fCoords, size);  
   }

   bsp.reset( new BSP(3, Points) );
}

void buildSurface::buildGrid(double res) {
   double xMax, yMax, zMax;
   xMin = yMin = zMin = 10000000;
   xMax = yMax = zMax = -10000000;
   if (ms->coords.size() < 3)
      return;
   xMin = xMax = ms->coords[0];
   yMin = yMax = ms->coords[1];
   zMin = zMax = ms->coords[2];
   
   for (int i=0; i<ms->coords.size()-3; i+=3) {
     float *cd = &ms->coords[i];
     if (cd[0] < xMin) xMin = cd[0];
      if (cd[0] > xMax) xMax = cd[0];
      if (cd[1] < yMin) yMin = cd[1];
      if (cd[1] > yMax) yMax = cd[1];
      if (cd[2] < zMin) zMin = cd[2];
      if (cd[2] > zMax) zMax = cd[2];
   }

   xMin -= 4.0;  yMin -= 4.0; zMin -= 4.0;
   xMax += 4.0; yMax += 4.0; zMax += 4.0;

   this->res = res;
   this->ires = 1.0/res;
   for (double i=xMin; i<xMax; i+=res) {
     X.push_back(i);
   }

   for (double i=yMin; i<yMax; i+=res)
     Y.push_back(i);

   for (double i=zMin; i<zMax; i+=res)
     Z.push_back(i);
}
          
void buildSurface::buildGrid(vector<atom *> &ATOMS, double res) {
   // This is the X Y Z vector sertup
   // TURNS OUT YOU REALLY NEEDED THIS
   double xMax, yMax, zMax;
   xMin = yMin = zMin = 10000000;
   xMax = yMax = zMax = -10000000;
   for (int i=0; i<ATOMS.size(); i++) { 
      float *cd = ATOMS[i]->fCoords;
      if (cd[0] < xMin) xMin = cd[0];
      if (cd[0] > xMax) xMax = cd[0];
      if (cd[1] < yMin) yMin = cd[1];
      if (cd[1] > yMax) yMax = cd[1];
      if (cd[2] < zMin) zMin = cd[2];
      if (cd[2] > zMax) zMax = cd[2];
   }

   xMin -= 4.0;  yMin -= 4.0; zMin -= 4.0;
   xMax += 4.0; yMax += 4.0; zMax += 4.0;

   this->res = res;
   this->ires = 1.0/res;
   
   for (double i=xMin; i<xMax; i+=res) {
     X.push_back(i);
   }

   for (double i=yMin; i<yMax; i+=res) 
     Y.push_back(i);
   
   for (double i=zMin; i<zMax; i+=res) 
     Z.push_back(i);

}

void buildSurface::run5() {
	time_t total1 = time(NULL);
	time_t t1 = time(NULL);

	bspSetup();

	float xMin, yMin, zMin, xMax, yMax, zMax;
	xMin = yMin = zMin = 100000000;
	xMax = yMax = zMax = -100000000;
	cout <<"ms->coords.size(): " << ms->coords.size() << endl;
	for (unsigned int i=0; i<ms->coords.size(); i+=3) {
		if (ms->coords[i] >= xMax)
			xMax = ms->coords[i];
		if (ms->coords[i] < xMin)
			xMin = ms->coords[i];
		
		if (ms->coords[i+1] >= yMax)
			yMax = ms->coords[i+1];
		if (ms->coords[i+1] < yMin)
			yMin = ms->coords[i+1];
		
		if (ms->coords[i+2] >= zMax)
			zMax = ms->coords[i+2];
		if (ms->coords[i+2] < zMin)
			zMin = ms->coords[i+2];

	}

	float ires = 1.0/res;
	//cout <<"res: " << res << endl;
	//cout <<"ires: " << ires << endl;
	float n = 1.0;
	float in = 1.0/n;
	vector<float> xValues( (fabs(xMax-xMin)+10)*ires*n );
	vector<float> yValues( (fabs(yMax-yMin)+10)*ires*n );
	vector<float> zValues( (fabs(zMax-zMin)+10)*ires*n );

	float xNum = xMin-5.0;
	int ct = 0;
	for (int i=0; i<xValues.size(); i++) {
		xValues[i] = xNum;
		xNum += res*in;
	}
	float yNum = yMin-5.0;
	for (int i=0; i<yValues.size(); i++) {
		yValues[i] = yNum;
		yNum += res*in;
	}
	float zNum = zMin-5.0;
	for (int i=0; i<zValues.size(); i++) {
		zValues[i] = zNum;
		zNum += res*in;
		//cout <<"zNum: " << zNum << endl;
		//int test = 0;
		//cin >> test;
	}

	cout <<"xNum[max]: " << xValues[xValues.size()-1] << endl;
	cout <<"yNum[max]: " << yValues[yValues.size()-1] << endl;
	cout <<"zNum[max]: " << zValues[zValues.size()-1] << endl;
	
	cout <<"xValues.size(): " << xValues.size() << endl;
	cout <<"yValues.size(): " << yValues.size() << endl;
	cout <<"zValues.size(): " << zValues.size() << endl;

	vector< vector< vector<float> > > pointCheck(xValues.size());
	for (int i=0; i<pointCheck.size(); i++) {
		
		pointCheck[i].resize(yValues.size());
		for (int j=0; j<pointCheck[i].size(); j++) {
			
			pointCheck[i][j].resize(zValues.size());
			for (int k=0; k<pointCheck[i][j].size(); k++) {
				pointCheck[i][j][k] = -1000;
			}
		}
	}
	
//	long long int evalCount = 0;
   int radCount = 0;
	GRIDCELL g;
	vector<TRIANGLE> TRIS;
	int count = 0;
	vector<int> cellIndex;
	
	vector<float> coordValVec;
	coordValVec.reserve(5000000);
	float avgHits = 0;
	for (unsigned int i=0; i<ms->coords.size(); i+=3) {
		count++;
		float *cent = &ms->coords[i];	//Center coords
		
		vector<dynacomp::point *> hits;
		bsp->getPoints(&ms->coords[i], hits, 6.0);
//		vector<int> coordIndex(hits.size());
		vector<int> coordIndex;
		
		for (int j=0; j<hits.size(); j++) {
		    float *cd = &ms->coords[(hits[j]->num-1)*3];
			float a = cent[0] - cd[0];
			float b = cent[1] - cd[1];
			float c = cent[2] - cd[2];
			if (sqrt(a*a + b*b + c*c) <= 6.0)
				coordIndex.push_back( (hits[j]->num-1)*3 );
		}
		//cout <<hits.size() << "\t" << coordIndex.size() << endl;
		avgHits += coordIndex.size();

	   // if (coordIndex.size() < 38) {	
	
		float span = ms->radii[radCount] *1.65;
		float radii = ms->radii[radCount];
		//float span = radii + radii*1.
		span = 3.0;
		radCount++;
		float x1 = cent[0] - span;
		float x2 = cent[0] + span;
/*
		cout <<"x1-x2: " << x1 <<"\t" << x2 << endl;
		cout <<"new: " << xValues[(x1-xValues[0])*ires*n] <<"\t" << xValues[(x2-xValues[0])*ires*n] << endl;
		int gbh = 0; cin >> gbh;
	*/
		//x1 = xValues[(x1-xValues[0])*ires*n];
		//x2 = xValues[(x2-xValues[0])*ires*n];
		vector<float> center(3);
		for (x1; x1 < x2; x1 += res) {
			int xNum = (x1-xValues[0])*ires;
			xNum *= n;
			if (xNum > xValues.size())
				cout <<"xNum is bad: " << endl;
			center[0] = xValues[xNum];
			 
			float y1 = cent[1] - span;
			float y2 = cent[1] + span;
			//y1 = yValues[(y1-yValues[0])*ires*n];
      	//y2 = yValues[(y2-yValues[0])*ires*n];
			for (y1; y1 <y2 ; y1 += res) {
				int yNum = (y1-yValues[0])*ires;
				yNum *= n;
				if (yNum >= yValues.size())
					cout <<"Y is bad: " <<yNum <<"\t"<<yValues.size() <<"\t"<<y1<<"\t"<<y2<< endl;
					
				center[1] = yValues[yNum];
				
				float z1 = cent[2] - span;
				float z2 = cent[2] + span;
				//z1 = zValues[(z1-zValues[0])*ires*n];
		      //z2 = zValues[(z2-zValues[0])*ires*n];
				for (z1; z1 < z2; z1 += res) {
					int zNum = (z1-zValues[0])*ires;
					zNum *= n;
					if (zNum >= zValues.size())
						cout <<"Z is bad: " << endl;
		
					center[2] = zValues[zNum];
		
	//				cout <<zNum<<"\t"<< center[0]<<"\t"<<center[1]<<"\t"<<center[2] << endl;			
					if (pointCheck[xNum][yNum][zNum] == -1000) {
						pointCheck[xNum][yNum][zNum] = isoGaussianMs(coordIndex, center[0], center[1], center[2]);
						//cout << pointCheck[xNum][yNum][zNum]<< endl;
						cellIndex.push_back(xNum);
						cellIndex.push_back(yNum);
						cellIndex.push_back(zNum);
					}
					
				}
			//	int test = 0;
			//	cin >> test;
			}
		//}
		}	
		
	}
	//cout<<"And now you are here  "<< cellIndex.size() << endl;
	for (int i=0; i<cellIndex.size(); i+=3) {
		float x = cellIndex[i];
		float y = cellIndex[i+1];
		float z = cellIndex[i+2];

		float xVal = in*x/ires+xValues[0];
		float yVal = in*y/ires+yValues[0];
		float zVal = in*z/ires+zValues[0];

//		cout << xVal <<"   " << yVal <<"   " << zVal << endl;
		GRIDCELL g;
		g.val[0] = pointCheck[x][y][z];
		g.val[1] = pointCheck[x+n][y][z];
		g.val[2] = pointCheck[x+n][y][z+n];
		g.val[3] = pointCheck[x][y][z+n];
		g.val[4] = pointCheck[x][y+n][z];
		g.val[5] = pointCheck[x+n][y+n][z];
		g.val[6] = pointCheck[x+n][y+n][z+n];
		g.val[7] = pointCheck[x][y+n][z+n];

/*
		cout <<"Vals:  ";
		for (int j=0; j<8; j++) 
			cout << g.val[j] <<"  ";
		cout << endl;

		int test = 0; 
		cin >> test;
*/
		bool check = true;
		int underCount = 0;
		int overCount = 0;
		for (int i=0; i<8; i++) {
			if (g.val[i] == -1000)
				check = false;
			if (g.val[i] < 1.0) 
				underCount++;
			else 
				overCount++;
		}
			
		
		if (check && underCount != 8 & overCount != 8) {
		g.p[0].x = xVal;
		g.p[0].y = yVal;
		g.p[0].z = zVal;

		g.p[1].x = xVal+res;	
		g.p[1].y = yVal;
		g.p[1].z = zVal;
		
		g.p[2].x = xVal+res;
		g.p[2].y = yVal;
		g.p[2].z = zVal+res;
	
		g.p[3].x = xVal;
		g.p[3].y = yVal;
		g.p[3].z = zVal+res;
	
		g.p[4].x = xVal;
		g.p[4].y = yVal+res;
		g.p[4].z = zVal;
	
		g.p[5].x = xVal+res;
		g.p[5].y = yVal+res;
		g.p[5].z = zVal;

		g.p[6].x = xVal+res;
		g.p[6].y = yVal+res;
		g.p[6].z = zVal+res;
	
		g.p[7].x = xVal;
		g.p[7].y = yVal+res;
		g.p[7].z = zVal+res;
		 

		 Polygonise(g, 1.0, TRIS, s);	
		} 
	}
	cout <<"cellIndex.size(): " << cellIndex.size() << endl;	
	cout <<"count is: " << count << endl;
	cout <<"avgHits.size() = " << avgHits/count << endl;
	cout <<"max num is: " << xValues.size()*yValues.size()*zValues.size() << endl;
	cout <<"s->verts.size(): " << s->verts.size() << endl;
//	set< vector<float> >::iterator si = pointSet.begin();
/*
	map< vector<float>, vector<int> >::iterator mi = pointMap.begin();
	for (mi; mi != pointMap.end(); mi++) {
		vector<float> center = mi->first;
		vector<int> coordIndex = mi->second;
		buildCellMs(g, center[0], center[1], center[2], res, coordIndex );
		Polygonise(g, 1.0, TRIS, s);
	}
	*/
	invertVerts(s->verts);
 	isoNormalsMs();
	view->infoText.clear();
	s->show = true;
	
	/*&
	cout <<"PointSet.size(): " << pointSet.size() << endl;
	set< vector<float> >::iterator si = pointSet.begin();
	for (si; si != pointSet.end(); si++) {
		vector<float> tmp = *si;
		for (int i=0; i<tmp.size(); i++) {
			s->verts.push_back(tmp[i]);
		}
	}
*/		
	cout <<"s->verts.size(): " << s->verts.size() << endl;
	cout <<"Xs: " << xMin << "\t" << xMax << endl;
	cout <<"Ys: " << yMin << "\t" << yMax << endl;
	cout <<"Zs: " << zMin << "\t" << zMax << endl;

//	cout <<"evalCount: " << evalCount << evalCount << endl;
	time_t t2 = time(NULL);
	cout <<"total time: " << t2 - t1 << endl;
}

void buildSurface::run4() {
   time_t total1 = time(NULL);
   time_t t1 = time(NULL);

   bspSetup();
   buildGrid(res);
   double cd[3];// = new double[3];
   cd[0] = 0.0;
   cd[1] = 0.0;
   cd[2] = 0.0;
   //Find initial Cube
   GRIDCELL gs;
   vector<TRIANGLE> TRIS;
   double inc = res;
   vector<double> p(3);
   set< vector<double> > xyzSet;

   float startX, startY, startZ;
   startX = ms->coords[0];
   startY = ms->coords[1];
   startZ = ms->coords[2];

   while (s->verts.size() == 0) {
     //p[0] = getX(xMin+inc);
     //p[1] = getY(yMin+inc);
     //p[2] = getZ(zMin+inc);
     p[0] = getX(startX+inc);
     p[1] = getY(startY);
     p[2] = getZ(startZ);
     if ( buildCellMs(gs, p[0], p[1], p[2], res)) {
         Polygonise(gs, 1.0, TRIS, s);
      }
      inc += res;
   }
   
   p[0] = getX( gs.p[0].x );
   p[1] = getY( gs.p[0].y );
   p[2] = getZ( gs.p[0].z );
   xyzSet.insert(p);

   stack<GRIDCELL> cellStack;
   cellStack.push(gs);
   GRIDCELL g;

   float *center = new float[3];
   //t count = 0;
   while (!cellStack.empty()) {
     //f (count == 30) break;
      //unt++;
      GRIDCELL  stackTopCell = cellStack.top();
      center[0] = (stackTopCell.p[0].x + stackTopCell.p[0].x+res)*0.5;
      center[1] = (stackTopCell.p[0].y + stackTopCell.p[0].y+res)*0.5;
      center[2] = (stackTopCell.p[0].z + stackTopCell.p[0].z+res)*0.5;

      vector<int> coordIndex;//(hits.size());

      cellStack.pop();
      if (stackTopCell.checkTop(1.0) ) {
         XYZ tmp;
         tmp.x = getX( stackTopCell.p[4].x+.01 );
         tmp.y = getY( stackTopCell.p[4].y+.01 );
         tmp.z = getZ( stackTopCell.p[4].z+.01 );
         p[0] = tmp.x; p[1] = tmp.y; p[2] = tmp.z;
         if (xyzSet.find(p) == xyzSet.end()) {
               GRIDCELL g;
               buildTopCell(g, stackTopCell, coordIndex, tmp.x, tmp.y, tmp.z, res);
               Polygonise(g, 1.0, TRIS, s);
               cellStack.push(g);
            xyzSet.insert(p);
         }
      }

      if (stackTopCell.checkBottom(1.0) ) {
         XYZ tmp;
         tmp.x = getX( stackTopCell.p[0].x+.01 );
         tmp.y = getY( stackTopCell.p[0].y-res+.01 );
         tmp.z = getZ( stackTopCell.p[0].z+.01 );
         p[0] = tmp.x; p[1] = tmp.y; p[2] = tmp.z;
         if (xyzSet.find(p) == xyzSet.end()) {
            GRIDCELL g;
            buildBottomCell(g, stackTopCell, coordIndex, tmp.x, tmp.y, tmp.z, res);
            Polygonise(g, 1.0, TRIS, s);
            cellStack.push(g);
            xyzSet.insert(p);
         }
      }
      
      if (stackTopCell.checkFront(1.0)){
         XYZ tmp;
         tmp.x = getX( stackTopCell.p[3].x+.01 );
         tmp.y = getY( stackTopCell.p[3].y+.01 );
         tmp.z = getZ( stackTopCell.p[3].z+.01 );
         p[0] = tmp.x; p[1] = tmp.y; p[2] = tmp.z;
         if (xyzSet.find(p) == xyzSet.end()) {
            GRIDCELL g;
            buildFrontCell(g, stackTopCell, coordIndex, tmp.x, tmp.y, tmp.z, res);
            Polygonise(g, 1.0, TRIS, s);
            cellStack.push(g);
            xyzSet.insert(p);
         }
      }
      if (stackTopCell.checkBack(1.0)){
         XYZ tmp;
         tmp.x = getX( stackTopCell.p[0].x+.01 );
         tmp.y = getY( stackTopCell.p[0].y+.01 );
         tmp.z = getZ( stackTopCell.p[0].z-res+.01 );
         p[0] = tmp.x; p[1] = tmp.y; p[2] = tmp.z;
         if (xyzSet.find(p) == xyzSet.end()) {
            GRIDCELL g;
            buildBackCell(g, stackTopCell, coordIndex, tmp.x, tmp.y, tmp.z, res);
            Polygonise(g, 1.0, TRIS, s);
            cellStack.push(g);
            xyzSet.insert(p);
         }
      }

      if (stackTopCell.checkLeft(1.0)){
         XYZ tmp;
         tmp.x = getX( stackTopCell.p[0].x-res+.01 );
         tmp.y = getY( stackTopCell.p[0].y+.01 );
         tmp.z = getZ( stackTopCell.p[0].z+.01 );
         p[0] = tmp.x; p[1] = tmp.y; p[2] = tmp.z;
         if (xyzSet.find(p) == xyzSet.end()) {
            GRIDCELL g;
            buildLeftCell(g, stackTopCell, coordIndex, tmp.x, tmp.y, tmp.z, res);
            Polygonise(g, 1.0, TRIS, s);
            cellStack.push(g);
            xyzSet.insert(p);
         }
      }
      if (stackTopCell.checkRight(1.0)) {
         XYZ tmp;
         tmp.x = getX( stackTopCell.p[1].x+.01 );
         tmp.y = getY( stackTopCell.p[1].y+.01 );
         tmp.z = getZ( stackTopCell.p[1].z+.01 );
         p[0] = tmp.x; p[1] = tmp.y; p[2] = tmp.z;
         if (xyzSet.find(p) == xyzSet.end()) {
            GRIDCELL g;
            buildRightCell(g, stackTopCell, coordIndex, tmp.x, tmp.y, tmp.z, res);
            Polygonise(g, 1.0, TRIS, s);
            cellStack.push(g);
            xyzSet.insert(p);
         }
      }
   }

   //NORMAL SECTION
   //time_t t2 = time(NULL);
   //t1 = time(NULL);
   cout <<"verts.size(): " << s->verts.size() << endl;
   invertVerts(s->verts);

   //Need to sort the vertices
   //Determine the unique vertices and then specify the indices
   /*
   map<vector<float>, int > vertMap;
   vector<float> uniqVerts;
   int index = 0;
   for (int i=0; i < s->verts.size(); i+=3) {
      vector<float> a(3);
      a[0] = s->verts[i];
      a[1] = s->verts[i+1];
      a[2] = s->verts[i+2];

      if (vertMap.find(a) == vertMap.end()) {
         vertMap[a] = index;
         for (int j=0; j<3; j++)
            uniqVerts.push_back(a[j]);
         index++;
      }
   }


  // cout <<"Build vertMap: " << endl;

   vector<int> indexVec;
   for (int i=0; i<s->verts.size(); i+=3) {
      vector<float> a(3);
      a[0] = s->verts[i];
      a[1] = s->verts[i+1];
      a[2] = s->verts[i+2];
     
      if (vertMap.find(a) == vertMap.end()) {
          cout <<"vertex was not found!!!   "<< vertMap.size() << endl;
          cout << a[0] <<"\t" << a[1] << "\t" << a[2] << endl;
          int y = 0; cin >> y;
      } 
      int index = vertMap[a];
      //cout <<"index: " << index << endl;
      indexVec.push_back(index);
   }
    
   //cout <<"make indexVec: "<<endl;
   
   s->indices = indexVec;
   s->verts = uniqVerts;
   
   vector<int> strip;
   strip.push_back(s->indices[0]);
   strip.push_back(s->indices[1]);
   strip.push_back(s->indices[2]);
   list< vector<int> > tris;
   for (int i=0; i<s->indices.size(); i+=3) {
      vector<int> v(3);
      v[0] = s->indices[i];
      v[1] = s->indices[i+1];
      v[2] = s->indices[i+2]; 
      tris.push_back(v);
   }

   list< vector<int> >::iterator it = tris.begin();
//   for (int i=0; i<3; i++)
   it++;
   tris.erase(tris.begin(), it);

   for (int j=0; j<2; j++) {
      for(int i=0; i<10; i++) {
         int v1 = strip[strip.size()-1];
         int v2 = strip[strip.size()-2];     

         //Now find a triagle with similar vertices
         list< vector<int> >::iterator it, itTmp;
         it = tris.begin();
         for (it; it != tris.end(); it++) {
            vector<int> cds = *it;
            int index1 = -1;
            int index2 = -1;
            for (int i=0; i<3; i++) {
               if (cds[i] == v1) index1 = i;
               if (cds[i] == v2) index2 = i;
            }
            if (index1 != index2 && (index1 != -1 && index2 != -1) ) {
               cout<<"Using: "<<cds[0]<<" "<<cds[1]<<" "<<cds[2]<<endl;
               if (index1 == 0 && index2 == 1) strip.push_back(cds[2]);
               if (index1 == 1 && index2 == 0) strip.push_back(cds[2]);
               if (index1 == 0 && index2 == 2) strip.push_back(cds[1]);
               if (index1 == 2 && index2 == 0) strip.push_back(cds[1]);
               if (index1 == 1 && index2 == 2) strip.push_back(cds[0]);
               if (index1 == 2 && index2 == 1) strip.push_back(cds[0]);
               break;
            } 
         }
         itTmp = it; itTmp++;
         if (it != tris.end()) {
            tris.erase(it, itTmp);
         }
      }

      s->strips.push_back(strip);
      strip.clear();
      it = tris.begin();
      strip = *it;
      it++;
   }
   cout <<"srip.size(): " << strip.size() << endl;
   cout <<"Tris.size(): " << tris.size() <<"\t" << s->indices.size()<< endl;
   it = tris.begin();
   s->indices.clear();
   for (it; it != tris.end(); it++) {
      for (int j=0; j<3; j++) {
         vector<int> a = *it;
         s->indices.push_back(a[j]);
      }
   }
   cout <<"indices:  " << s->indices.size() << endl; 
   int test = 0;
   cin >> test;
   */  
  
/*
   cout <<"vertMap.size(): " << vertMap.size() << endl;
   cout <<"indexVec.size(): " << indexVec.size() << endl;
   cout <<"s->verts.size(): " << s->verts.size() << endl;
   cout <<"uniqVerts.size(): " << uniqVerts.size() << endl;
   int tpt = 0; cin >>tpt;

   int cnt = 0;
   for (int i=0; i<6; i++) {
      for (int j=0; j<3; j++) {
         cout << s->verts[cnt] << " ";
         cnt++;
      }
      cout << endl;
   }
   cout <<"Those were the first 3 s->verts: " << endl;
   while (true) {
      cout <<"enter triangle number to show: " << s->verts.size()/3 << endl;
      int num;
      cin >> num;
      for (int i=0; i<3; i++) 
         cout << s->verts[num*3+i] <<" ";
      cout << endl;

      //for (int i=0; i<3; i++) {
      int index = indexVec[num]*3;
      cout <<"Index is: " << index << endl; 
      cout << uniqVerts[index] <<" " << uniqVerts[index+1] <<" "<< uniqVerts[index+2] << endl;
      
   }
*/

   
  // s->verts = uniqVerts;
   //Calculate the Normals for each triangle vertice  
   time_t t2 = time(NULL);
   cout <<"first time: " << t2 - t1 << endl;
   isoNormalsMs();


/*
   set<float> aSet;
   for (int i=0; i<s->verts.size(); i+=3) {
      float *cd = &s->verts[i];
      float num = cd[0] + 100*cd[1] + 1000*cd[2];
      aSet.insert(num);
   }

   cout <<"aSet.size(): " << aSet.size() << "\t" << s->verts.size()/3 <<"\t" << s->verts.size() << endl;
*/
   //cout <<"s->verts.size(): " << s->verts.size() << endl;
   //cout <<"s->norms.size(): " << s->norms.size() << endl;
   //cout <<"s->color.size(): " << s->color.size() << endl;
   //cout <<"s->indices.size(): " << s->indices.size() << endl;



   view->infoText.clear();
   s->show = true;

   time_t t3 = time(NULL);
   cout <<"last time: "<< t3 - t2 << endl;
   cout <<"total time run4: " << t3 - t1 << endl;
}

void buildSurface::invertVerts(vector<float> &verts) {
   for (int i=0; i<verts.size(); i+=9) {
      float hold1 = verts[i];
      float hold2 = verts[i+1];
      float hold3 = verts[i+2];

      
      verts[i]   = verts[i+6];
      verts[i+1] = verts[i+7];
      verts[i+2] = verts[i+8];
      
      verts[i+6] = hold1;
      verts[i+7] = hold2;
      verts[i+8] = hold3;
   }  
}

bool buildSurface::buildTopCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &ci, 
                                double x, double y, double z, double res) 
{

   float center[3];
   center[0] = (x + x+res)*0.5;
   center[1] = (y + y+res)*0.5;
   center[2] = (z + z + res)*0.5;

   vector<dynacomp::point *> hits;
   bsp->getPoints(center, hits, bspWidth);
   vector<int> coordIndex(hits.size());

   for (int i=0; i<hits.size(); i++)
      coordIndex[i] = (hits[i]->num-1)*3;

   cell.p[0].x = curr.p[4].x;
   cell.p[0].y = curr.p[4].y;
   cell.p[0].z = curr.p[4].z;
   cell.val[0] = curr.val[4];

   cell.p[1].x = curr.p[5].x;
   cell.p[1].y = curr.p[5].y;
   cell.p[1].z = curr.p[5].z;
   cell.val[1] = curr.val[5];

   cell.p[2].x = curr.p[6].x;
   cell.p[2].y = curr.p[6].y;
   cell.p[2].z = curr.p[6].z;
   cell.val[2] = curr.val[6];

   cell.p[3].x = curr.p[7].x;
   cell.p[3].y = curr.p[7].y;
   cell.p[3].z = curr.p[7].z;
   cell.val[3] = curr.val[7];

   cell.p[4].x = x;
   cell.p[4].y = y+res;
   cell.p[4].z = z;
   cell.val[4] = isoGaussianMs(coordIndex, cell.p[4].norm, x, y+res, z);

   cell.p[5].x = x+res;
   cell.p[5].y = y+res;
   cell.p[5].z = z;
   cell.val[5] = isoGaussianMs(coordIndex, cell.p[5].norm, x+res, y+res, z);

   cell.p[6].x = x+res;
   cell.p[6].y = y+res;
   cell.p[6].z = z+res;
   cell.val[6] = isoGaussianMs(coordIndex, cell.p[6].norm, x+res, y+res, z+res);

   cell.p[7].x = x;
   cell.p[7].y = y+res;
   cell.p[7].z = z+res;
   cell.val[7] = isoGaussianMs(coordIndex, cell.p[7].norm, x, y+res, z+res);

   return true;
}

bool buildSurface::buildBottomCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &ci,
                                   double x, double y, double z, double res)
{

   float center[3];
   center[0] = (x + x+res)*0.5;
   center[1] = (y + y+res)*0.5;
   center[2] = (z + z + res)*0.5;

   vector<dynacomp::point *> hits;
   bsp->getPoints(center, hits, bspWidth);
   vector<int> coordIndex(hits.size());

   for (int i=0; i<hits.size(); i++)
      coordIndex[i] = (hits[i]->num-1)*3;

   //cout <<"buildBottomCell xyz: " << x <<"\t" << y <<"\t" << z << endl;

   cell.p[0].x = x;
   cell.p[0].y = y;
   cell.p[0].z = z;
   cell.val[0] = isoGaussianMs(coordIndex, cell.p[0].norm, x, y, z);

   cell.p[1].x = x+res;
   cell.p[1].y = y;
   cell.p[1].z = z;
   cell.val[1] = isoGaussianMs(coordIndex, cell.p[1].norm, x+res, y, z);

   cell.p[2].x = x+res;
   cell.p[2].y = y;
   cell.p[2].z = z+res;
   cell.val[2] = isoGaussianMs(coordIndex, cell.p[2].norm, x+res, y, z+res);

   cell.p[3].x = x;
   cell.p[3].y = y;
   cell.p[3].z = z+res;
   cell.val[3] = isoGaussianMs(coordIndex, cell.p[3].norm, x, y, z+res);


   cell.p[4].x = curr.p[0].x;
   cell.p[4].y = curr.p[0].y;
   cell.p[4].z = curr.p[0].z;
   cell.val[4] = curr.val[0];

   cell.p[5].x = curr.p[1].x;
   cell.p[5].y = curr.p[1].y;
   cell.p[5].z = curr.p[1].z;
   cell.val[5] = curr.val[1];

   cell.p[6].x = curr.p[2].x;
   cell.p[6].y = curr.p[2].y;
   cell.p[6].z = curr.p[2].z;
   cell.val[6] = curr.val[2];

   cell.p[7].x = curr.p[3].x;
   cell.p[7].y = curr.p[3].y;
   cell.p[7].z = curr.p[3].z;
   cell.val[7] = curr.val[3];

   return true;
}

bool buildSurface::buildFrontCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &ci,
                        double x, double y, double z, double res)
{

   float center[3];
   center[0] = (x + x+res)*0.5;
   center[1] = (y + y+res)*0.5;
   center[2] = (z + z + res)*0.5;

   vector<dynacomp::point *> hits;
   bsp->getPoints(center, hits, bspWidth);
   vector<int> coordIndex(hits.size());

   for (int i=0; i<hits.size(); i++)
      coordIndex[i] = (hits[i]->num-1)*3;

   cell.p[0].x = curr.p[3].x;
   cell.p[0].y = curr.p[3].y;
   cell.p[0].z = curr.p[3].z;
   cell.val[0] = curr.val[3];

   cell.p[1].x = curr.p[2].x;
   cell.p[1].y = curr.p[2].y;
   cell.p[1].z = curr.p[2].z;
   cell.val[1] = curr.val[2];

   cell.p[2].x = x+res;
   cell.p[2].y = y;
   cell.p[2].z = z+res;
   cell.val[2] = isoGaussianMs(coordIndex, cell.p[2].norm, x+res, y, z+res);

   cell.p[3].x = x;
   cell.p[3].y = y;
   cell.p[3].z = z+res;
   cell.val[3] = isoGaussianMs(coordIndex, cell.p[3].norm, x, y, z+res);

   cell.p[4].x = curr.p[7].x;
   cell.p[4].y = curr.p[7].y;
   cell.p[4].z = curr.p[7].z;
   cell.val[4] = curr.val[7];

   cell.p[5].x = curr.p[6].x;
   cell.p[5].y = curr.p[6].y;
   cell.p[5].z = curr.p[6].z;
   cell.val[5] = curr.val[6];

   cell.p[6].x = x+res;
   cell.p[6].y = y+res;
   cell.p[6].z = z+res;
   cell.val[6] = isoGaussianMs(coordIndex, cell.p[6].norm, x+res, y+res, z+res);

   cell.p[7].x = x;
   cell.p[7].y = y+res;
   cell.p[7].z = z+res;
   cell.val[7] = isoGaussianMs(coordIndex, cell.p[7].norm, x, y+res, z+res);

   return true;
}

bool buildSurface::buildBackCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &ci,
                        double x, double y, double z, double res)
{
   float center[3];
   center[0] = (x + x+res)*0.5;
   center[1] = (y + y+res)*0.5;
   center[2] = (z + z + res)*0.5;

   vector<dynacomp::point *> hits;
   bsp->getPoints(center, hits, bspWidth);
   vector<int> coordIndex(hits.size());

   for (int i=0; i<hits.size(); i++)
      coordIndex[i] = (hits[i]->num-1)*3;

   cell.p[0].x = x;
   cell.p[0].y = y;
   cell.p[0].z = z;
   cell.val[0] = isoGaussianMs(coordIndex, cell.p[0].norm, x, y, z);

   cell.p[1].x = x+res;
   cell.p[1].y = y;
   cell.p[1].z = z;
   cell.val[1] = isoGaussianMs(coordIndex, cell.p[1].norm, x+res, y, z);

   cell.p[2].x = curr.p[1].x;
   cell.p[2].y = curr.p[1].y;
   cell.p[2].z = curr.p[1].z;
   cell.val[2] = curr.val[1];
   
   cell.p[3].x = curr.p[0].x;
   cell.p[3].y = curr.p[0].y;
   cell.p[3].z = curr.p[0].z;
   cell.val[3] = curr.val[0];

   cell.p[4].x = x;
   cell.p[4].y = y+res;
   cell.p[4].z = z;
   cell.val[4] = isoGaussianMs(coordIndex, cell.p[4].norm, x, y+res, z);

   cell.p[5].x = x+res;
   cell.p[5].y = y+res;
   cell.p[5].z = z;
   cell.val[5] = isoGaussianMs(coordIndex, cell.p[5].norm, x+res, y+res, z);

   cell.p[6].x = curr.p[5].x;
   cell.p[6].y = curr.p[5].y;
   cell.p[6].z = curr.p[5].z;
   cell.val[6] = curr.val[5];

   cell.p[7].x = curr.p[4].x;
   cell.p[7].y = curr.p[4].y;
   cell.p[7].z = curr.p[4].z;
   cell.val[7] = curr.val[4];

   return true;
}

bool buildSurface::buildLeftCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &ci,
                        double x, double y, double z, double res)
{

   float center[3];
   center[0] = (x + x+res)*0.5;
   center[1] = (y + y+res)*0.5;
   center[2] = (z + z + res)*0.5;

   vector<dynacomp::point *> hits;
   bsp->getPoints(center, hits, bspWidth);
   vector<int> coordIndex(hits.size());

   for (int i=0; i<hits.size(); i++)
      coordIndex[i] = (hits[i]->num-1)*3;

   cell.p[0].x = x;
   cell.p[0].y = y;
   cell.p[0].z = z;
   cell.val[0] = isoGaussianMs(coordIndex, cell.p[0].norm, x, y, z);

   cell.p[1].x = curr.p[0].x;
   cell.p[1].y = curr.p[0].y;
   cell.p[1].z = curr.p[0].z;
   cell.val[1] = curr.val[0];

   cell.p[2].x = curr.p[3].x;
   cell.p[2].y = curr.p[3].y;
   cell.p[2].z = curr.p[3].z;
   cell.val[2] = curr.val[3];

   cell.p[3].x = x;
   cell.p[3].y = y;
   cell.p[3].z = z+res;
   cell.val[3] = isoGaussianMs(coordIndex, cell.p[3].norm, x, y, z+res);

   cell.p[4].x = x;
   cell.p[4].y = y+res;
   cell.p[4].z = z;
   cell.val[4] = isoGaussianMs(coordIndex, cell.p[4].norm, x, y+res, z);

   cell.p[5].x = curr.p[4].x;
   cell.p[5].y = curr.p[4].y;
   cell.p[5].z = curr.p[4].z;
   cell.val[5] = curr.val[4];

   cell.p[6].x = curr.p[7].x;
   cell.p[6].y = curr.p[7].y;
   cell.p[6].z = curr.p[7].z;
   cell.val[6] = curr.val[7];

   cell.p[7].x = x;
   cell.p[7].y = y+res;
   cell.p[7].z = z+res;
   cell.val[7] = isoGaussianMs(coordIndex, cell.p[7].norm, x, y+res, z+res);

   return true;
}

bool buildSurface::buildRightCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &ci,
                       double x, double y, double z, double res)
{

   float center[3];
   center[0] = (x + x+res)*0.5;
   center[1] = (y + y+res)*0.5;
   center[2] = (z + z + res)*0.5;

   vector<dynacomp::point *> hits;
   bsp->getPoints(center, hits, bspWidth);
   vector<int> coordIndex(hits.size());

   for (int i=0; i<hits.size(); i++)
      coordIndex[i] = (hits[i]->num-1)*3;

   cell.p[0].x = curr.p[1].x;
   cell.p[0].y = curr.p[1].y;
   cell.p[0].z = curr.p[1].z;
   cell.val[0] = curr.val[1];

   cell.p[1].x = x+res;
   cell.p[1].y = y;
   cell.p[1].z = z;
   cell.val[1] = isoGaussianMs(coordIndex, cell.p[1].norm, x+res, y, z);

   cell.p[2].x = x+res;
   cell.p[2].y = y;
   cell.p[2].z = z+res;
   cell.val[2] = isoGaussianMs(coordIndex, cell.p[2].norm, x+res, y, z+res);

   cell.p[3].x = curr.p[2].x;
   cell.p[3].y = curr.p[2].y;
   cell.p[3].z = curr.p[2].z;
   cell.val[3] = curr.val[2];

   cell.p[4].x = curr.p[5].x;
   cell.p[4].y = curr.p[5].y;
   cell.p[4].z = curr.p[5].z;
   cell.val[4] = curr.val[5];

   cell.p[5].x = x+res;
   cell.p[5].y = y+res;
   cell.p[5].z = z;
   cell.val[5] = isoGaussianMs(coordIndex, cell.p[5].norm, x+res, y+res, z);

   cell.p[6].x = x+res;
   cell.p[6].y = y+res;
   cell.p[6].z = z+res;
   cell.val[6] = isoGaussianMs(coordIndex, cell.p[6].norm, x+res, y+res, z+res);

   cell.p[7].x = curr.p[6].x;
   cell.p[7].y = curr.p[6].y;
   cell.p[7].z = curr.p[6].z;
   cell.val[7] = curr.val[6];

   return true;
}

bool buildSurface::buildCellMs(GRIDCELL &g, double x, double y, double z, double res, const vector<int> &coordIndex) 
{
	
	g.p[0].x = x;
	g.p[0].y = y;
	g.p[0].z = z;
	
	g.val[0] = isoGaussianMs(coordIndex, g.p[0].norm, x, y, z);
	
	g.p[1].x = x+res;
	g.p[1].y = y;
	g.p[1].z = z;
	g.val[1] = isoGaussianMs(coordIndex, g.p[1].norm, x+res, y, z);
	
	g.p[2].x = x+res;
	g.p[2].y = y;
	g.p[2].z = z+res;
	g.val[2] = isoGaussianMs(coordIndex, g.p[2].norm, x+res, y, z+res);
	
	g.p[3].x = x;
	g.p[3].y = y;
	g.p[3].z = z+res;
	g.val[3] = isoGaussianMs(coordIndex, g.p[3].norm, x, y, z+res);
	
	g.p[4].x = x;
	g.p[4].y = y+res;
	g.p[4].z = z;
	g.val[4] = isoGaussianMs(coordIndex, g.p[4].norm, x, y+res, z);
	
	g.p[5].x = x+res;
	g.p[5].y = y+res;
	g.p[5].z = z;
	g.val[5] = isoGaussianMs(coordIndex, g.p[5].norm, x+res, y+res, z);
	
	g.p[6].x = x+res;
	g.p[6].y = y+res;
	g.p[6].z = z+res;
	g.val[6] = isoGaussianMs(coordIndex, g.p[6].norm, x+res, y+res, z+res);
	
	g.p[7].x = x;
	g.p[7].y = y+res;
	g.p[7].z = z+res;
	g.val[7] = isoGaussianMs(coordIndex, g.p[7].norm, x, y+res, z+res);
	
	return true;
}

 
bool buildSurface::buildCellMs(GRIDCELL &g, double x, double y,double z, double res) {
   //static float *center = new float[3];
   float center[3];
   center[0] = (x + x+res)*0.5;
   center[1] = (y + y+res)*0.5;
   center[2] = (z + z + res)*0.5;

   vector<dynacomp::point *> hits;
   bsp->getPoints(center, hits, 3.0);
   vector<int> coordIndex(hits.size());

   for (int i=0; i<hits.size(); i++) 
      coordIndex[i] = (hits[i]->num-1)*3;

   g.p[0].x = x;
   g.p[0].y = y;
   g.p[0].z = z;
   g.val[0] = isoGaussianMs(coordIndex, g.p[0].norm, x, y, z);
 
   g.p[1].x = x+res;
   g.p[1].y = y;
   g.p[1].z = z;
   g.val[1] = isoGaussianMs(coordIndex, g.p[1].norm, x+res, y, z);

   g.p[2].x = x+res;
   g.p[2].y = y;
   g.p[2].z = z+res;
   g.val[2] = isoGaussianMs(coordIndex, g.p[2].norm, x+res, y, z+res);

   g.p[3].x = x;
   g.p[3].y = y;
   g.p[3].z = z+res;
   g.val[3] = isoGaussianMs(coordIndex, g.p[3].norm, x, y, z+res);

   g.p[4].x = x;
   g.p[4].y = y+res;
   g.p[4].z = z;
   g.val[4] = isoGaussianMs(coordIndex, g.p[4].norm, x, y+res, z);

   g.p[5].x = x+res;
   g.p[5].y = y+res;
   g.p[5].z = z;
   g.val[5] = isoGaussianMs(coordIndex, g.p[5].norm, x+res, y+res, z);

   g.p[6].x = x+res;
   g.p[6].y = y+res;
   g.p[6].z = z+res;
   g.val[6] = isoGaussianMs(coordIndex, g.p[6].norm, x+res, y+res, z+res);

   g.p[7].x = x;
   g.p[7].y = y+res;
   g.p[7].z = z+res;
   g.val[7] = isoGaussianMs(coordIndex, g.p[7].norm, x, y+res, z+res);

   return true;
}


bool buildSurface::buildCell(vector<atom *> &Atoms,  GRIDCELL &g, 
			     double x, double y, double z, double res) 
{

   float center[3];
   center[0] = (x + x+res)*0.5;
   center[1] = (y + y+res)*0.5;
   center[2] = (z + z + res)*0.5;
   vector<dynacomp::point *> hits;
   bsp->getPoints(center, hits, 3.0);
   vector<atom *> ATOMS(hits.size());
   for (int i=0; i<hits.size(); i++) 
      ATOMS[i] = Atoms[hits[i]->num-1];

   g.p[0].x = x; 
   g.p[0].y = y; 
   g.p[0].z = z;
   g.val[0] = isoGaussian(ATOMS, g.p[0].norm, x, y, z);
 
   g.p[1].x = x+res;
   g.p[1].y = y;
   g.p[1].z = z;
   g.val[1] = isoGaussian(ATOMS, g.p[1].norm, x+res, y, z);

   g.p[2].x = x+res;
   g.p[2].y = y;
   g.p[2].z = z+res;
   g.val[2] = isoGaussian(ATOMS, g.p[2].norm, x+res, y, z+res);

   g.p[3].x = x; 
   g.p[3].y = y; 
   g.p[3].z = z+res;
   g.val[3] = isoGaussian(ATOMS, g.p[3].norm, x, y, z+res);
   
   g.p[4].x = x; 
   g.p[4].y = y+res; 
   g.p[4].z = z; 
   g.val[4] = isoGaussian(ATOMS, g.p[4].norm, x, y+res, z);

   g.p[5].x = x+res; 
   g.p[5].y = y+res; 
   g.p[5].z = z;
   g.val[5] = isoGaussian(ATOMS, g.p[5].norm, x+res, y+res, z);
   
   g.p[6].x = x+res;
   g.p[6].y = y+res;
   g.p[6].z = z+res;
   g.val[6] = isoGaussian(ATOMS, g.p[6].norm, x+res, y+res, z+res);

   g.p[7].x = x;
   g.p[7].y = y+res;
   g.p[7].z = z+res;
   g.val[7] = isoGaussian(ATOMS, g.p[7].norm, x, y+res, z+res);

   return true;
}

void buildSurface::isoNormalsMs() {
   s->norms.resize(s->verts.size()); 
   s->color.resize(s->verts.size()/3*4);
   int colorIndex = 0;
   for (int i=0; i<s->verts.size(); i+=3) {
      for (int k=0; k<3; k++) 
         s->norms[i+k]  = 0.0;

      for (int k=0; k<4; k++) {
         s->color[colorIndex+k] = 0.0;
      }

      float elecPot = 0.0;
  
      float center[3];
      center[0] = s->verts[i];
      center[1] = s->verts[i+1];
      center[2] = s->verts[i+2];
   
      vector<dynacomp::point *> hits;
      bsp->getPoints(center, hits, 2.5);

      float minColorDist = 10000000;
      for (int j=0; j<hits.size(); j++) {
         float *cd = &ms->coords[(hits[j]->num-1)*3]; 
         float *color = &ms->color[(hits[j]->num-1)*4];
         float a1 = s->verts[i] - cd[0];
         float b1 = s->verts[i+1] - cd[1];
         float c1 = s->verts[i+2] - cd[2];

         float dist1 = a1*a1 + b1*b1 +c1*c1;   
         elecPot += ms->charge[hits[j]->num-1]/dist1;
         
         if (atomColor && dist1 < minColorDist) {
            minColorDist = dist1; 
            s->color[colorIndex]   = color[0];
            s->color[colorIndex+1] = color[1];
            s->color[colorIndex+2] = color[2];
            s->color[colorIndex+3] = trans;
         } 
         
         
	 if (acgs && dist1 < 10) {
	     s->color[colorIndex] += color[0];
	     s->color[colorIndex+1] += color[1];
	     s->color[colorIndex+2] += color[2];
	     s->color[colorIndex+3] = trans;
	 }
         
         float radii = ms->radii[hits[j]->num-1];
         if (dist1 < 10) {
            dist1 = sqrt(dist1);
            float tmpVal = dist1 - radii;
            float exp1;
            if (tmpVal > 0) {
               exp1 =  expLookup[int(tmpVal*igran)];
            } else
               exp1 = exp(-( dist1-radii )*alpha);

            if (smoothAtomColor) {
               s->color[colorIndex]   += color[0]*exp1;
               s->color[colorIndex+1] += color[1]*exp1;
               s->color[colorIndex+2] += color[2]*exp1;
               s->color[colorIndex+3] = trans; 
            }

            s->norms[i]   += alpha*a1/dist1*exp1;
            s->norms[i+1] += alpha*b1/dist1*exp1;
            s->norms[i+2] += alpha*c1/dist1*exp1;
         } 
      }
      if (elecColor) {
         if (elecPot < -.05) {
            s->color[colorIndex] = 1.0;
            s->color[colorIndex+1] = 0.0;
            s->color[colorIndex+2] = 0.0;
            s->color[colorIndex+3] = trans;
         } else if (elecPot > .05) {
            s->color[colorIndex] = 0.0;
            s->color[colorIndex+1] = 0.0;
            s->color[colorIndex+2] = 1.0;
            s->color[colorIndex+3] = trans;
         } else {
           s->color[colorIndex] = 1.0;
           s->color[colorIndex+1] = 1.0;
           s->color[colorIndex+2] = 1.0;
           s->color[colorIndex+3] = trans;
         }
      }
      if (solidColor) {
         s->color[colorIndex] = Red;
         s->color[colorIndex+1] = Green;
         s->color[colorIndex+2] = Blue;
         s->color[colorIndex+3] = trans;
      }

      if (acgs) {
      //Normalize the color
      float mag = 0;
      for (int i=0; i<3; i++) {
//	cout << s->color[colorIndex+i] << endl;
	mag += s->color[colorIndex+i]*s->color[colorIndex+i];
      }
      mag = sqrt(mag);
      for (int i=0; i<3; i++) {
        s->color[colorIndex+i] = s->color[colorIndex+i]/mag;
//	cout << s->color[colorIndex+i] << endl;
      }
      }
      colorIndex += 4;
   }
} 

void buildSurface::isoNormals(vector<triangle *> &tris, vector<atom *> &ATOMS) {

  for (int i=0; i<tris.size(); i++) {
    vector<double> nor1(3), nor2(3), nor3(3);
    for (int h=0; h<3; h++) {
      nor1[h] = nor2[h] = nor3[h] =0.0;
    }
    vector<double> cl1(3), cl2(3), cl3(3);
    for (int k=0; k<3; k++) {
      cl1[k] = 0.0;
      cl2[k] = 0.0;
      cl3[k] = 0.0;
    }
    tris[i]->trans = trans;
    float center[3];
    center[0] = tris[i]->v1[0];
    center[1] = tris[i]->v1[1];
    center[2] = tris[i]->v1[2];
    vector<dynacomp::point *> hits;
    bsp->getPoints(center, hits, 3.0);

    for (int j=0; j<hits.size(); j++) {
      	atom *atm = ATOMS[hits[j]->num-1];
       	float *cd = atm->fCoords;

       	float a1 = tris[i]->v1[0] - cd[0];
       	float b1 = tris[i]->v1[1] - cd[1];
       	float c1 = tris[i]->v1[2] - cd[2];

       	float dist1 = a1*a1 + b1*b1 +c1*c1;
       	if (dist1 < 10) {
               dist1 = sqrt(dist1);
	       float tmpVal = dist1-atm->getRadii();
               
               float exp1;
               if (tmpVal > 0) {
	          exp1 =  expLookup[int(tmpVal*igran)];
               } else
                  exp1 = exp(-(dist1-atm->getRadii())*alpha);
               cl1[0] += atm->COLOR[0]*exp1;
               cl1[1] += atm->COLOR[1]*exp1;
               cl1[2] += atm->COLOR[2]*exp1;
               nor1[0] += alpha*a1/dist1*exp1;
	       nor1[1] += alpha*b1/dist1*exp1;
	       nor1[2] += alpha*c1/dist1*exp1;
       	}


       	float a2 = tris[i]->v2[0] - cd[0];
       	float b2 = tris[i]->v2[1] - cd[1];
       	float c2 = tris[i]->v2[2] - cd[2];
       	float dist2 = a2*a2 + b2*b2 +c2*c2;

       	if (dist2 < 10) {
               dist2 = sqrt(dist2);
               float tmpVal = dist2-atm->getRadii();
	       float exp2;
               if (tmpVal > 0)  
                  exp2 =  expLookup[int(tmpVal*igran)];
               else
                  exp2 = exp(-(dist1-atm->getRadii())*alpha);

               cl2[0] += atm->COLOR[0]*exp2;
               cl2[1] += atm->COLOR[1]*exp2;
               cl2[2] += atm->COLOR[2]*exp2;
               nor2[0] += alpha*a2/dist2*exp2;
	       nor2[1] += alpha*b2/dist2*exp2;
	       nor2[2] += alpha*c2/dist2*exp2;
       	}

       	float a3 = tris[i]->v3[0] - cd[0];
       	float b3 = tris[i]->v3[1] - cd[1];
       	float c3 = tris[i]->v3[2] - cd[2];
       	float dist3 = a3*a3 + b3*b3 +c3*c3;

       	if (dist3 < 10) {
            dist3 = sqrt(dist3);
            float tmpVal = dist3-atm->getRadii();
	    float exp3;
            if (tmpVal > 0)  
               exp3 =  expLookup[int(tmpVal*igran)];
            else
            exp3 = exp(-(dist3-atm->getRadii())*alpha);   
	  
            cl3[0] += atm->COLOR[0]*exp3;
            cl3[1] += atm->COLOR[1]*exp3;
            cl3[2] += atm->COLOR[2]*exp3;
            nor3[0] += alpha*a3/dist3*exp3;
	    nor3[1] += alpha*b3/dist3*exp3;
	    nor3[2] += alpha*c3/dist3*exp3;
       }

    }
      
    for (int k=0; k<3; k++) {
        tris[i]->c1[k] = cl1[k];
	tris[i]->c2[k] = cl2[k];
	tris[i]->c3[k] = cl3[k];
    }
      

    for (int j=0; j<3; j++) {
         tris[i]->n1[j] = nor1[j];
     	 tris[i]->n2[j] = nor2[j];
   	 tris[i]->n3[j] = nor3[j];
    }
  }
  
}


float buildSurface::isoGaussianMs(const vector<int> &coordIndex, float x, float y, float z) {
	float isoValue = 0.0;
   	for (int i =0; i<coordIndex.size(); i++) {
		float *cd = &ms->coords[coordIndex[i]];
		float a = cd[0] - x;
		float b = cd[1] - y;
		float c = cd[2] - z;
		float d2 = a*a + b*b +c*c;
		float radii = ms->radii[coordIndex[i]*0.3333];
    
		float dist = sqrt(d2);
		float tmpVal = ( dist - radii );
        //float exp1 = expLookup[int(tmpVal*igran)];
		//float exp1 = exp(-alpha*tmpVal);
		//isoValue += exp1;    
		
		if (tmpVal < 10.0 && tmpVal > 0) {
			float exp1 = expLookup[int(tmpVal*igran)];
			isoValue += exp1; 
		} else if (tmpVal < 0 && isoValue > 1.0) {
			return isoValue;
		} else if (tmpVal < 0) {
			float exp1 = exp(-alpha*tmpVal);
			isoValue += exp1;
			if (isoValue > 1.0) return isoValue;
		}
		
	}
	return isoValue;
}

double buildSurface::isoGaussianMs(const vector<int> &coordIndex, double *norm,
                                 double x, double y, double z)
{
   double isoValue = 0.0;
   norm[0] = 0.0; norm[1] = 0.0; norm[2] = 0.0;
   for (int i =0; i<coordIndex.size(); i++) {
     float *cd = &ms->coords[coordIndex[i]];
     float a = cd[0] - x;
     float b = cd[1] - y;
     float c = cd[2] - z;
     float d2 = a*a + b*b +c*c;
     float radii = ms->radii[coordIndex[i]*0.3333];
    
     float dist = sqrt(d2);
     double tmpVal = ( dist - radii );
      
     if (tmpVal < 10.0 && tmpVal > 0) {
        double exp1 = expLookup[int(tmpVal*igran)];
        isoValue += exp1; 
     } else if (tmpVal < 0 && isoValue > 1.0) {
        return isoValue;
     } else if (tmpVal < 0) {
        double exp1 = exp(-alpha*tmpVal);
        isoValue += exp1;
        if (isoValue > 1.0) return isoValue;
     }
     
   }
   return isoValue;

}
double buildSurface::isoGaussian(vector<atom *> &ATOMS, double *norm,
				double x, double y, double z) 
{
   double isoValue = 0.0;
   norm[0] = 0.0; norm[1] = 0.0; norm[2] = 0.0;
   for (int i =0; i<ATOMS.size(); i++) {
     atom *atm = ATOMS[i];
     float *cd = atm->fCoords;
     float a = cd[0] - x;
     float b = cd[1] - y;
     float c = cd[2] - z;
     float dist = a*a + b*b +c*c;

     dist = sqrt(dist);
     double tmpVal = (dist-atm->getRadii());
     //isoValue += exp(-alpha*tmpVal);
     
     if (tmpVal < 10.0 && tmpVal > 0) {
        double exp1 = expLookup[int(tmpVal*igran)];
        isoValue += exp1;
     } else if (tmpVal < 0 && isoValue > 1.0) {
        return isoValue;
     } else if (tmpVal < 0) {
        double exp1 = exp(-alpha*tmpVal);
        isoValue += exp1;
        if (isoValue > 1.0) return isoValue;
     }
     
   }
   return isoValue;
}

void buildSurface::run() {
   //run4();
   run5();
   emit threadDone();
   molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1002));
   e->name = name;
   QApplication::postEvent(&view->modelView->jm, e);

   return;
}


