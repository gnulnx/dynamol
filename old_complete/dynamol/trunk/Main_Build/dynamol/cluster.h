/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <deque>
#include "bsp.h"

using namespace std;

/**
@author jfurr
*/
class clusterPoint;
struct group {
   vector<clusterPoint *> Points;
   clusterPoint *centerPoint;
};

class clusterPoint : public point
{
public:
   clusterPoint(int num, group *parent, vector<float> &coords, float radius, float energy);
   ~clusterPoint();
   int num;
   vector<float> coords;
   float radius;
   float energy;
   group *parent;
};

class cluster{
public:
    cluster();

    ~cluster();
    
    /** This function is used to perform a hierachal clustering of data 
    *   It takes as input a vector< vector<float> > of curernt data, as well as a
    *   similar structure for the output.  In addition is also need to know how
    *   many clusters to form
    */
    void hierarchal(vector< vector<float> > &datMat, 
                    vector<float> &props, 
                    vector< vector< vector<float> > > &newClusters, 
                    int num
                    );
    
   /** This function reorganizes the data into a group vector */
   void datMat2Groups(vector< vector<float> > &datMat, 
                      vector<float> &props, 
                      vector<group *> &Groups
                      );
  
  /** This function determines the closests two groups.  The indeces are returned as
  *   index1, index 2
  */
  bool closestGroups(vector<group *> &Groups, 
                     BSP *bsp, 
                     int &index1, 
                     int &index2,
                     int sphereSize
                     );
                     
   void mergeGroups(vector<group *> &Groups, int index1, int index2);
   
   /** This function preps the newClusters for return */
   void groups2Clusters(vector<group *> &Groups, 
                        vector< vector< vector<float> > > &newClusters
                        );
                       
   float dist2(const vector<float> &p1, const vector<float> &p2) {
      float dist = 0;
      for (int i=0; i<p1.size(); i++) {
         dist += (p1[i]-p2[i])*(p1[i]-p2[i]);
      }
      return dist;
   }
};

#endif


























