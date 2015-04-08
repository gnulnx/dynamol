/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef BUILDSURFACE_H
#define BUILDSURFACE_H

#include "dynothread.h"
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>

using namespace std;

#include "surfstruct.h"

//BOOST Includes
#include <boost/shared_ptr.hpp>

//Dynamol Computational Includes
#include "../dynacomp/bsp.h"
using dynacomp::BSP;

class molView;
//class XmodelView;
class molecule;
class atom;
class triangle;
/**
@author jfurr
*/
//#include "stdlib.h"
//#include "stdio.h"
//#include "string.h"
//void ZeroMemory(void *, unsigned int size);
/*
inline void ZeroMemory(void *addr, unsigned int size) {
   memset(addr, 0, size);
}
*/
/** \brief This is your basic surface class
*
*  You should simply pass these vectors to the appropriate vertex Array's
*/
/*
struct surface { 
   vector<float> verts;
   vector<float> color;
   vector<float> norms;
   bool singleColor;
   surface::surface() {
      verts.reserve(2000000);
      color.reserve(2000000);
      norms.reserve(2000000);
      singleColor = false;
   }
};
*/
/** \brief A molecule structure
*
*   Copy the relavent molecule information here
*/
struct molStruct {
   vector<float> coords;
   vector<float> radii;
   vector<float> color;
   vector<float> charge;
};

typedef struct XYZ { 
  double value;
  double x, y, z;
  double norm[3];

  XYZ::XYZ() {
    x = y = z = 0.0;
    norm[0] = norm[1] = norm[2] = 0.0;
  }
 
  XYZ& XYZ::operator= (const XYZ& xyz)
  {
    if (this == &xyz) return *this;   // Gracefully handle self assignment
    x = xyz.x;
    y = xyz.y;
    z = xyz.z;
    value = xyz.value;
    norm[0] = xyz.norm[0];
    norm[1] = xyz.norm[1];
    norm[2] = xyz.norm[2];
    // Put the normal assignment duties here...
    
    return *this;
  }
  /*
  inline bool operator==(const XYZ &xyz) const
  {
    cout <<"Using == "<<endl;
    if (xyz.x != x) return false;
    if (xyz.y != y) return false;
    if (xyz.z != z) return false;
    return true;
  };
 */ 
  inline bool operator!=(const XYZ &xyz)
  {
    
    if (xyz.x != x) return true;
    if (xyz.y != y) return true;
    if (xyz.z != z) return true;
    return false;
  };

  inline bool operator<(const XYZ &xyz) const
  {
    //cout <<"Using less Than "<< endl;
    if (x != xyz.x && x < xyz.x) return true;
    if (y != xyz.y && y < xyz.y) return true;
    if (z != xyz.z && z < xyz.z) return true;
    return false;
  };
  void print() 
  {
     cout << x << setw(12) << y << setw(12) << z << setw(12) << value<< endl;
  }

};

typedef struct TRIANGLE {
   TRIANGLE::TRIANGLE() {
      cp.resize(3);
      cp[0] = 0.0;
      cp[1] = 0.0;
      cp[2] = 0.0;
   }
   XYZ p[3];
   vector<double> cp; //GRIDCELL lower point
} ;

typedef struct GRIDCELL {
  XYZ p[8];
  double val[8];
  GRIDCELL::GRIDCELL() {
    for (int i=0; i<8; i++)
      val[i] = 0.0;
  }

  inline bool checkTop(float iso) {
    int count = 0;
    if ( val[4] < iso ) count++;
    if ( val[5] < iso ) count++;
    if ( val[6] < iso ) count++;
    if ( val[7] < iso ) count++;
    if ( count < 4 && count != 0 ) return true;
    return false;
  }
  inline bool checkBottom(float iso) {
    int count = 0;
    if ( val[0] < iso ) count++;
    if ( val[1] < iso ) count++;
    if ( val[2] < iso ) count++;
    if ( val[3] < iso ) count++;
    if ( count < 4 && count != 0) return true;
    return false;
  }
  inline bool checkLeft(float iso) {
    int count = 0;
    if ( val[0] < iso ) count++;
    if ( val[3] < iso ) count++;
    if ( val[7] < iso ) count++;
    if ( val[4] < iso ) count++;
    if (count < 4 && count != 0) return true;
    return false;
  }
  inline bool checkRight(float iso) {
    int count = 0;
    if ( val[1] < iso ) count++;
    if ( val[2] < iso ) count++;
    if ( val[6] < iso ) count++;
    if ( val[5] < iso ) count++;
    if (count < 4 && count != 0) return true;
    return false;
  }
  inline bool checkFront(float iso) {
    int count = 0;
    if ( val[3] < iso ) count++;
    if ( val[7] < iso ) count++;
    if ( val[6] < iso ) count++;
    if ( val[2] < iso ) count++;
    if (count < 4 && count != 0) return true;
    return false;
  }
  inline bool checkBack(float iso) {
    int count = 0;
    if ( val[0] < iso ) count++;
    if ( val[4] < iso ) count++;
    if ( val[5] < iso ) count++;
    if ( val[1] < iso ) count++;
    if (count < 4 && count != 0) return true;
    return false;
  }
};

class buildSurface : public dynoThread
{
public:
    buildSurface(molView *view = 0, const char *name = 0);

    ~buildSurface();

   /** \brief This function is used to set guassian parameters
   *
   *   <pre> 
   *   res = grid resolution in Angstrons
   *   alpha = 1.0/alpha in the exp(-alpha term)
   *   trans = translucency
   *   color = color mode {solid, atomType, electrostatic}
   */
   //void molSurfSetup(molStruct *mol, float res, float alpha, float trans, string color);
   void molSurfSetup(boost::shared_ptr<molStruct> mol, boost::shared_ptr<surface> surf, 
                     float res, float alpha, float trans, string color);
 
   /** \brief The main run function 
   *  
   *   Threads call start which in turn calls this function
   */
   virtual void run();

   /** Trying to do it atom-atom wise */
   void run5();

	/** \brief A point value map
	 *
	 */
	map<int, float> valMap;
	
   /** This is the gaussian marching cubes  way */
   void run4();

   /** \brief Calculate the isoGaussian molecular surface 
   */
   double isoGaussian(vector<atom *> &ATOMS, double *norm,  
		     double x, double y, double z);

   /** \breif The new isoGaussian function */
   double isoGaussianMs(const vector<int> &index, double *norm,
                      double x, double y, double z);\

	/** This one is for the all atom approach */	   
	float isoGaussianMs(const vector<int> &coordIndex, float x, float y, float z);
   
   /** \brief calculate the normals for the gaussian surface
   */
   void isoNormals(vector<triangle *>  &tris, vector<atom *> &ATOMS);

   /** \brief Possibly the new isoNormal routine */
   void isoNormalsMs();

  
   /** \brief Invert Triangles
   *
   *   This function will change the facing side of a triangle.
   *   It basically operates by swapping the v1 and v3 vertices
   */
   void invertVerts(vector<float> &verts);

   /** \brief Build a cell.
   *
   *  The xyz coordinates should specify the minimum x, y, and z
   *  coords of the box.  The res is the grid resolution
   */
   bool buildCell(vector<atom *> &ATOMS, GRIDCELL &cell, 
		   double x, double y, double z, double res);

   /** \brief Current slow way of doing things 
   *
   *   Will be replacing this method with a quicker method that requires
   *   have the calls to isoGaussiaMs
   */
   bool buildCellMs(GRIDCELL &cell, double x, double y, double z, double res);
   bool buildCellMs(GRIDCELL &cell, double x, double y, double z, double res, const vector<int> &coordIndex);

   bool buildTopCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &hits, 
                     double x, double y, double z, double res);

   bool buildBottomCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &hits,
                        double x, double y, double z, double res);

   bool buildFrontCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &hits,
                        double x, double y, double z, double res);

   bool buildBackCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &hits,
                        double x, double y, double z, double res);

   bool buildLeftCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &hits,
                        double x, double y, double z, double res);

   bool buildRightCell(GRIDCELL &cell, const GRIDCELL &curr, const vector<int> &hits,
                        double x, double y, double z, double res);

   /** \brief Build the grid
    *  construct the X, Y, Z vectors of possible grid values
   */  
   void buildGrid(vector<atom *> &ATOMS, double res);

   /** \brief New Build Grid */
   void buildGrid(double res);

   /** \brief Lookup Vectors
   *
   *    X, Y, Z provide lookup values for possible grid points 
   */
   vector<double> X;
   vector<double> Y;
   vector<double> Z;

   double xMin, yMin, zMin;
   double res;
   double ires;
   inline double getX(double val) {
      if (val < X[0]) {
         //cout <<"X range "<<val <<"\t"<<X[X.size()-1] <<"\t"<<X[0]<< endl;
         return X[0];
      }
      else if (val > X[X.size()-1]) {
         cout <<"X BIG "<<val <<"\t"<<X[X.size()-1] <<"\t"<<X[0]<< endl;
         return X[X.size()-1];
      }
      return X[(val-xMin)*ires];
   }

   inline double getY(double val) {
      if (val < Y[0])
         return Y[0];
      else if (val > Y[Y.size()-1]) {
         cout <<"Y  BIG "<<val<<"\t"<<Y[Y.size()-1]<<"\t"<<Y[0]<< endl;	
         return Y[Y.size()-1];
      }
      return Y[(val-yMin)*ires];
   }

   inline double getZ(double val) {
      if (val < Z[0])
         return Z[0];
      else if (val > Z[Z.size()-1]) {
         cout <<"Z BIG"<< val <<"\t"<<Z[Z.size()-1]<<"\t"<<Z[0]<<endl;
         return Y[Y.size()-1];
      }
      return Z[(val-zMin)*ires];
   }


   /** \brief In the case of a flat color 
   */
   void setColor(float r, float g, float b);
   float Red, Green, Blue;

   /** \brief Function to build the Binary Spacial Division Tree for fast lookup 
   */
   void bspSetup(vector<atom *> &ATOMS);

   /** \brief This should be the correct one to use */
   void bspSetup();

   //BSP *bsp;
   boost::shared_ptr<BSP> bsp;

   /** \brief exp lookup table
   *
   *   This vector provides a lookup table for the exponential guassian function
   */
   vector<double> expLookup;

   vector<double> distLookup;

   /** \brief...bad idea...doubled the time */
   map<float, vector<double> > expDistLookup;


   /** \brief trying to provide a lookup table for negative gaussian values 
   *
   *   This is not really used at this point in time 
   */   
   vector<float> expNeg;

   /** \brief gran is the lookup table granularity. 
   */
   float gran;

   /** \brief the inverse granularity */
   float igran;

   /** \brief alpha is the exp(-alpha) value
   */
   float alpha;

   /** \brief Controls the width of the BSP search
   *
   *   For looser surfaces you have to search wider
   */
   float bspWidth;

   /** \brief Trans is the translucency..should this be moved?
   */
   float trans;

   /** \brief Color is the color model */
   string color;

   /** \brief surface face direction if CULL_FACE is on 
   */
   bool direction;
   float indexOffSet;
  

   /** \brief A molStruct Pointer
   *
   *   This should be auto deleted at the end of the calculation
   */
   //molStruct *ms;
   boost::shared_ptr<molStruct> ms;

   /** \brief a temporary surface */ 
   //surface *s;
   boost::shared_ptr<surface> s;
 
   molView *view;

   /** \brief atom color variables */
   bool elecColor;
   bool atomColor;
   bool smoothAtomColor;
   bool solidColor;
   bool acgs;
//   molecule *mol;

};

#endif


