/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "cluster.h"
#include "linAlg.h"
#include <iomanip>

namespace dynacomp {

clusterPoint::clusterPoint(int num, group *parent, vector<float> &coords, float radius, float energy) 
: point(num, coords, radius)
{
   this->num = num;
   this->coords = coords;
   this->radius = radius;
   this->energy = energy;
   this->parent = parent;
}

clusterPoint::~clusterPoint() {}

cluster::cluster()
{
}


cluster::~cluster()
{
}

void cluster::hierarchal(vector< vector<float> > &datMat, vector<float> &props, vector< vector< vector<float> > > &newClusters, int num) 
{
   /** This section organizes the data into groups of points */
   vector<group *> Groups;
   datMat2Groups(datMat, props, Groups);
   
   /** This section forms a vector of points for use with the bsp */
   vector<point *> Points;
   //vector<clusterPoint *> Points;
   for (unsigned int i=0; i<Groups.size(); i++) {
      Points.push_back(Groups[i]->Points[0]);
   }
   
   BSP *bsp = new BSP(3, Points);
   ////////////cout <<"Groups.size():  " << Groups.size() << endl;
   ////////////cout <<"Points.size(): " << Points.size() << endl;
   ////////////cout <<"bsp->count: " << bsp->count << endl;
   ////////////cout <<"bsp->avg: " << bsp->avg << endl;
   
   //closestPoints(bsp, point *p1, point *p2);
   int index1, index2;
   int sphereSize = 1;
   while ((int)Groups.size() > num) {
      
      while (!closestGroups(Groups, bsp, index1, index2, sphereSize))
         sphereSize++;
      
      mergeGroups(Groups, index1, index2);
      ////////////cout <<"Groups " << Groups.size() << setw(12) << sphereSize << endl;
   }
   
   groups2Clusters(Groups, newClusters);
   
}

void cluster::groups2Clusters(vector<group *> &Groups, vector< vector< vector<float> > > &newClusters) 
{
   newClusters.resize(Groups.size());
   for (unsigned int i=0; i<Groups.size(); i++) {
      ////////////cout <<"Points: " << Groups[i]->Points.size() << endl;
      group *g = Groups[i];
      newClusters[i].resize(g->Points.size());
      for (unsigned int j=0; j<g->Points.size(); j++) {
         newClusters[i][j] = g->Points[j]->coords;
      }
   }
}

void cluster::mergeGroups(vector<group *> &Groups, int index1, int index2) {
   ////////////cout <<"Welcome to mergeGroups "<<index1 << setw(12) << index2 << setw(12) <<Groups.size() << endl;
   group *g1 = Groups[index1];
   group *g2 = Groups[index2];

   if (g1->Points[0]->energy < g2->Points[0]->energy) {
      for (unsigned int i=0; i<g2->Points.size(); i++) {
         g1->Points.push_back(g2->Points[i]);
         g2->Points[i]->parent = g1;
      }
      Groups.erase(Groups.begin()+index2);
   } else {
      for (unsigned int i=0; i<g1->Points.size(); i++) {
         g2->Points.push_back(g1->Points[i]);
         g1->Points[i]->parent = g2;
      }   
      Groups.erase(Groups.begin()+index1);
   }
      
}

bool cluster::closestGroups(vector<group *> &Groups, BSP *bsp, int &index1, int &index2, int sphereSize) {
      
   float DIST = 1000000.0;
   float EDIFF = 10000000.0;
   int groupIndex = -1;
   int hitIndex = -1;
   //group *hitGroup;
   vector<point *> hits;
   for (unsigned int i=0; i < Groups.size(); i++) {
      hits.clear();
      group *g = Groups[i];
      
      //The first point is the one we compare to; 
      point *centerPoint = g->centerPoint;
      clusterPoint *groupPoint = g->centerPoint;
      
      bsp->getPoints(centerPoint, hits, sphereSize);
      for (unsigned int j=0; j<hits.size(); j++) {
         float dist = bsp->distance(centerPoint->coords, hits[j]->coords);
         //float dist = dist2(centerPoint->coords, hits[j]->coords);
         
         if (dist <= DIST) {
            clusterPoint *tmp = reinterpret_cast<clusterPoint *>(hits[j]);
            float eDiff = fabs(groupPoint->energy - tmp->energy);
            if (eDiff < EDIFF && tmp->parent != g) {
               groupIndex = i;
               hitIndex = j;
               DIST = dist;
               EDIFF = eDiff;  
            }
         }
      }
   }
   
   if (groupIndex == -1) {
      //////////cout <<"Retuning false: " << sphereSize << endl;
      return false;
   }
   
   
   index1 = groupIndex;
   
   point *p = Groups[groupIndex]->centerPoint;
   hits.clear();
   bsp->getPoints(p, hits, sphereSize);
   point *p2 = hits[hitIndex];
   clusterPoint *cp2 = reinterpret_cast<clusterPoint *>(p2);
   group *closestGroup = cp2->parent;
   
   for (unsigned int i=0; i<Groups.size(); i++) {
      if (closestGroup == Groups[i]) {
         index2 = i;
         break;
      }
   }
   
   if (Groups[index1] == Groups[index2]) {
      //////////cout <<"Major Problemo!"<<endl;
      //int test = 0;
      //cin >> test;
   }
   
   return true;
}

void cluster::datMat2Groups(vector< vector<float> > &datMat, vector<float> &props, vector<group *> &Groups) {
   for (unsigned int i=0; i<datMat.size(); i++) {
      //determine the effect of changing the size value...currently 1
      group *g = new group;
      clusterPoint *p = new clusterPoint(i, g, datMat[i], 1, props[i]); 
      g->Points.push_back(p);
      g->centerPoint = p;
      Groups.push_back(g);      
   }
}



};//END NAMESPACE


