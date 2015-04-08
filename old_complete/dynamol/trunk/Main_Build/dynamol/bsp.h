/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef BSP_H
#define BSP_H
#include <vector>


using namespace std;
/**
@author jfurr
*/

class point {
public:
   point(int num, vector<float> &coords, float radius);
   ~point();

   int num;
   vector<float> coords;
   float radius;
};

class leaf{
public:
   leaf(float axis, float value) {
      this->axis = axis;
      this->value = value;  
      right = 0;
      left = 0;
   }

   ~leaf();

   int axis;  
   float value;      
   vector<point *> Points;
    
   leaf *right, *left;
};


class BSP {
public:
   BSP(int gran, vector<point *> &Points);

   ~BSP();

   /**the granularity of the tree....
   *  aka how minimum elements per leaf
   */
   int gran; 
   
   /** The root node */
   leaf *root;
   
   /** This should replace the above range functions once you port this
   *   to the full multi deminsional space
   */
   vector< vector<float> > Ranges;
   
   /** Total leaf node count */
   int count; 
   
   /** Avg number of points in the leaf nodes */
   float avg;
   
   /** When you search the tree this is you center point..you wouldn't want
   *   to return this point
   */
   point *pointToExclude; 
   
   /** this function will return either the median value or the left (smallest) most value f the middle two */
   float getMedian(const vector<point *> &Points, int axis);
    
   /** Split points and add them to the current leaf node */
   void splitPoints(leaf *node, vector<point *> &Points);
    
   /** this function gets the largest axis and the median value of that axis */
   void getAxis(const vector<point *> &Points, int &axis, float &value);
   
   /** Get range */
   float getRange(const vector<point *> &Points, int axis);
   
   /** get the mean */
   float getMean(const vector<point *> &Points, int axis);
   
   /** This build the range tree */
   void buildSubTree(leaf *node);
    
   
   /** Like the above function but for use in mutli deminsional space 
   */
   void getPoints(point *p, vector<point *> &hits, float dist); 
   int checkRange(leaf *node, vector<point *> &hits); 
   
   void addPoints(leaf *node, vector<point *> &hits);
    
   float distance(const vector<float> &p1, const vector<float> &p2);
};

#endif


























