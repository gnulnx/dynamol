/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "bsp.h"
//#include "leaf.h"
//#include "point.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

namespace dynacomp {

point::point(int num, vector<float> &coords, float radius) {
   this->num = num;
   this->coords = &coords[0];
   this->radius = radius;
}
point::point(int num, float *coords, float radius) {
      this->num = num;
      this->coords = coords;
      this->radius = radius;
};
point::~point() {
};

BSP::BSP(int gran, vector<point *> &Points)
{
  this->gran = gran;
  count = 0;
  avg = 0;
  root = 0;
  pointToExclude = NULL;
  //First lets determine the largest axis and then determine the orthoganal axis for splitting
  int axis = 0;
  float split = 0;
  getAxis(Points, axis, split);
  
  root = new leaf(axis, split);
  leafVec.push_back(root);
  root->Points = Points;

  buildSubTree(root);
  
  avg = avg/count;
}

float BSP::distance(const vector<float> &p1, const vector<float> &p2) {
   float dist = 0;
   for (unsigned int i=0; i<p1.size(); i++) {
      dist += (p1[i] - p2[i])*(p1[i] - p2[i]);
   }   
   return sqrt(dist);
}

void BSP::getPoints(float *p, vector<point *> &hits, float dist) {
   hits.reserve(100);
   point *P = new point(0, p, 0.0);
   getPoints(P, hits, dist);
}

void BSP::getPoints(point *p, vector<point *> &hits, float dist) {
   pointToExclude = p;
   
   //Ranges.resize(p->coords.size());
   Ranges.resize(3);
   for (unsigned int i=0; i<Ranges.size(); i++) {
      Ranges[i].resize(2);
      Ranges[i][0] = p->coords[i]-dist;
      Ranges[i][1] = p->coords[i]+dist;
   }
   
   checkRange(root, hits);
}


int BSP::checkRange(leaf *node, vector<point *> &hits) {
   if ((int)node->Points.size() <= gran) {
      addPoints(node, hits);
      return node->Points.size();
   }
   
   int axis = node->axis;
   float value = node->value;
   int num = 0;

   if (Ranges[axis][0] > value && Ranges[axis][1] > value) {
      num = checkRange(node->right, hits);
      return num;
   }
   else 
   if (Ranges[axis][0] < value && Ranges[axis][1] < value) {
      num = checkRange(node->left, hits);
      return num;
   }
   else {
      num = checkRange(node->right, hits);
      num = checkRange(node->left, hits);
      return num;
   }
   
}


void BSP::addPoints(leaf *node, vector<point *> &hits) {
  for (unsigned int i=0; i<node->Points.size(); i++) {
     if (pointToExclude != node->Points[i]) 
  	  hits.push_back(node->Points[i]);
  }
}

void BSP::buildSubTree(leaf *node) {
   if ((int)node->Points.size() <= gran) {
	count++;
	avg += node->Points.size();
	return;
   }
   else splitPoints(node, node->Points);
}

BSP::~BSP()
{
   for (unsigned int i=0; i<leafVec.size(); i++) 
      delete leafVec[i];
}

void BSP::getAxis(const vector<point *> &Points, int &axis, float &split) {
   //vector<int> axisSizes(Points[0]->coords.size());
   vector<int> axisSizes(3);
   
   for (unsigned int i=0; i<axisSizes.size(); i++) {
      axisSizes[i] = (int)getRange(Points, i);
   }
   
   int maxSize = -1;
   for (unsigned int i=0; i<axisSizes.size(); i++) {
      if (axisSizes[i] > maxSize) {
         axis = i;
         maxSize = axisSizes[i];
      }
   }
   
   split = getMean(Points, axis);
   return;
}

float BSP::getMean(const vector<point *> &Points, int axis) {
   float mean = 0;
   for (unsigned int i=0; i<Points.size(); i++) 
     mean +=Points[i]->coords[axis];
     
   return mean / Points.size();
}
float BSP::getRange(const vector<point *> &Points, int axis) {
   float min = 10000000;
   float max = -10000000;
   for (unsigned int i=0; i<Points.size(); i++) {
   
     float value = Points[i]->coords[axis];
     if (value > max) max = value;
     else if (value < min) min = value;
   }
   float a = min-max;
     return sqrt(a*a);
     if (a < 0) return -1*a;
     else return a;
}



float BSP::getMedian(const vector<point *> &Points, int axis) {
   int size = Points.size();
   int median = size % 2;
   if(median == 0) 
     return Points[size/2 -1]->coords[axis];
   else 
     return Points[(size+1)/2]->coords[axis];
}

void BSP::splitPoints(leaf *node, vector<point *> &Points) {
    vector<point *> left;
    vector<point *> right;
    int axis = node->axis;
    for (unsigned int i=0; i<Points.size(); i++) {
      point *p = Points[i];
      if (p->coords[axis] < node->value) left.push_back(p);
      else (right.push_back(p));
    }
    
    float split = 0;
    if (right.size() > 0) {
      getAxis(right, axis, split);
      node->right = new leaf(axis, split);
      leafVec.push_back(node->right);
      node->right->Points = right;
      buildSubTree(node->right);
    }
    
    if (left.size() > 0) {
      getAxis(left, axis, split);
      node->left = new leaf(axis, split);
      leafVec.push_back(node->left);
      node->left->Points = left;
      buildSubTree(node->left);
    }
}


}; // END NAMESPACE























