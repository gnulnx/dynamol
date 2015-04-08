/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SURFSTRUCT_H
#define SURFSTRUCT_H

#include <vector>
using std::vector;
class surface {
public:
   vector<float> verts;
   vector<float> uniqVerts;
   vector< vector<float> > simpleStrips;
   vector< vector<int> > strips;

   vector<int> indices;
   vector<float> color;
   vector<float> norms;
   bool singleColor;
   bool show;
   surface::surface() {
      //verts.reserve(2000000);
      //color.reserve(2000000);
      //norms.reserve(2000000);
      singleColor = false;
      show = false;
   }
   surface::~surface() {
   //   cout <<"Killing the surface"<<endl;
   }
};

#endif
