/***************************************************************************
                          ribbon.cpp  -  description
                             -------------------
    begin                : Tue Nov 18 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "ribbon.h"
#include "chain.h"
#include "fragment.h"
#include "atom.h"

#include <math.h>
//#include "enumTypes.h"

ribbon::ribbon(chain *ch, RIBBON_TYPE ribType)
: Object()
{
      if (ch->frags.size() == 0) {
      return;
    }
    //First section will grab all of the CA && carbonyl O atoms from the molecule
    CAatoms.clear();
    Oatoms.clear();
    type.clear(); //0=HELIX 1=SHEET, 2= LOOP

    //find our oxygen && CA atoms here
    //For now you are also going to get the colors from here as well
    for (int i=0; i<ch->frags.size(); i++) {
      fragment *frag = ch->frags[i];

      int test = 0;
      int caPos, oPos;
      for (int j=0; j<frag->atoms.size(); j++) {
        atom *atm = frag->atoms[j];
        if (atm->getSym() == "CA" || atm->getSym() =="CA "/*this part for wierd amino acids..BMT*/) {
          caPos = j;
          test++;
        } else if (atm->getSym() == "O" || atm->getSym() == "O  ") {
          oPos = j;
          test++;
        }

        if (test == 2) {
          CAatoms.push_back(frag->atoms[caPos]->get_fCoords() );
          Oatoms.push_back(frag->atoms[oPos]->get_fCoords() );
          type.push_back(frag->type);
          break;
        }
      }
    }

    if (CAatoms.size() < 2) {
      ch->rib = NULL;
      return;
    }


    //determine were to send the data for ribbon build up
  if (ribType == FLAT) {
    flat(ch);
  } else if (ribType == CARTOON) {
    cartoon(ch);
  }

}

/* ################################ FLAT RIBBON ###########################
  This section is done.  It would be possible to do some optimzation work in here.  
  Should probably be done at some point Currently you are using a vOrder of 2.  
  This significantly improves performance.   However I think that there are certain 
  effects that I would be able to get if I used all four v control points....
  (that is all four control points on each peptide plane.  As it is you are only 
  going to use two of them.  I am leaving the code in that actually calulates all 
  four just incase you ever want to get back down && dirty with it
###########################################################################*/
void ribbon::flat(chain *ch) {

    //Assign the order to the uOrder && vOrder variables.
    vOrder = 2;
    uOrder = 4;
    
    vKnots.resize(4);
    for (int i=0; i<2; i++) {
      vKnots[i] = 0.0;
      vKnots[i+2] = 1.0;
    }

    //Set the multiplicity of the uKnot vector to 4.
    int order = 4;
    for (int i=0; i<order; i++) {
      uKnots.push_back(0);
    }

    int uKnotCount = 1;

    //THIS SECTION IS ALL FROM THE PAPER ALGORITHMS FOR RIBBON MODELS OF PROTEINS
    //First lets form vector A which is Cai - Ca
    //Lets also go ahead && form vector B which is Oi - Cai
    //Might as well get the vector C ( the cross product of A && B as well
    //Oh && lets not forget vector D which is crossprocudt of C && A
    vector<float> A(3), B(3), C(3), D(3), D_prev(3), P(3), P_1(3), P_2(3), P_3(3), P_4(3), DOT(3);
    float angle, prevAngle;
    angle = prevAngle = 0;
    static int flipped = 0;
    for (int i=0; i<CAatoms.size()-1; i++) {

      A[0] = CAatoms[i+1][0] - CAatoms[i][0];
      A[1] = CAatoms[i+1][1] - CAatoms[i][1];
      A[2] = CAatoms[i+1][2] - CAatoms[i][2];

      B[0] = Oatoms[i][0] - CAatoms[i][0];
      B[1] = Oatoms[i][1] - CAatoms[i][1];
      B[2] = Oatoms[i][2] - CAatoms[i][2];

      //Cross products for vector C.  This was copied from the Trackball vCross routine
      C[0] = (A[1]*B[2])-(A[2]*B[1]);
      C[1] = (A[2]*B[0])-(A[0]*B[2]);
      C[2] = (A[0]*B[1])-(A[1]*B[0]);

      //Now get the cross product of C && A && save as vector D
      D[0] = (C[1]*A[2])-(C[2]*A[1]);
      D[1] = (C[2]*A[0])-(C[0]*A[2]);
      D[2] = (C[0]*A[1])-(C[1]*A[0]);

      //Now normalize both vector C && vector D
      float cMag = 0; float dMag = 0;
      cMag = sqrt(C[0]*C[0] + C[1]*C[1] + C[2]*C[2]);      //Not sure if you need to add the square root here || not
       dMag = sqrt(D[0]*D[0] + D[1]*D[1] + D[2]*D[2]);     //Not sure if you need to add the square root here || not

      C[0] /= cMag;    C[1] /= cMag;     C[2] /= cMag;
      D[0] /= dMag;    D[1] /= dMag;     D[2] /= dMag;

      //Form point P as the midpoint between Ca && Ca+1
      P[0] = (CAatoms[i+1][0] + CAatoms[i][0])/2;
      P[1] = (CAatoms[i+1][1] + CAatoms[i][1])/2;
      P[2] = (CAatoms[i+1][2] + CAatoms[i][2])/2;

      //Translate in the direction of vector C if part of a helix
      if (type[i] == HELIX) {
        P[0] -= C[0]*1.5;
        P[1] -= C[1]*1.5;
        P[2] -= C[2]*1.5;
      }

      //Now we scale vector D by 1/2 the desired ribbon width
      //D[0] *=1.5; D[1] *= 1.5; D[2] *= 1.5;
      //Checking the angle beteen the two peptide planes
      if (i > 1) {
        DOT[0] = D[0] * D_prev[0];
        DOT[1] = D[1] * D_prev[1];
        DOT[2] = D[2] * D_prev[2];
        angle = DOT[0] +DOT[1] +DOT[2];
        angle =ARCFIX*acos(angle);
      }

      //Keep track of the previous D vectors so that we can assign correct P for Beta-Sheets && other atoms
      D_prev[0] = D[0];
      D_prev[1] = D[1];
      D_prev[2] = D[2];
      prevAngle = angle;

      //if ( angle > 90 && flipped == 0 ) {

      //This makes it skinnier for the loop regions...er turn regions
      if (type[i] == TURN) {
        D[0] /=2; D[1] /= 2; D[2] /= 2;
      }

      P_1[0] = P[0] - D[0];
      P_1[1] = P[1] - D[1];
      P_1[2] = P[2] - D[2];

      P_4[0] = P[0] + D[0];
      P_4[1] = P[1] + D[1];
      P_4[2] = P[2] + D[2];

      /* Scale it agin ...this should get us the inner two points...of the four
        *** NOTE *** This is were you assign the other 2 control points for each 
         peptide plane.  If you should ever need them you know were to find them
      */
      D[0] /=2; D[1] /= 2; D[2] /= 2;
      P_2[0] = P[0] - D[0];
      P_2[1] = P[1] - D[1];
      P_2[2] = P[2] - D[2];

      P_3[0] = P[0] + D[0];
      P_3[1] = P[1] + D[1];
      P_3[2] = P[2] + D[2];

	  //for (int i=0; i<3; i++) {
	  //	  P_2[i] = (P_1[i]+P_4[i])/2 + 2;
	  //	  P_3[i] = (P_1[i]+P_4[i])/2 - 2;
	  //}

     // SET THE COLOR FOR THE SEGEMENT.  THis goes first becuase you are going to 
     // evetually use this code to do the cartoon segments
      float a, b, c, d;
      if (type[i] == HELIX) {
         a= 1.0; b=0.0; c=0.0; d=1.00;
      } else if (type[i] == SHEET) {
       a = 1.0; b=1.0; c= 0.5; d=1.0;
      } else {
        a = 0.0; b=0.0; c=1.0; d=1.0;
      }
      
      //BUILD THE CONTROL PNTS... REMEMBER TO FLIP IF 90      
      if (angle > 90 && flipped == 0) {
        seg.push_back(P_1[0]);    seg.push_back(P_1[1]);    seg.push_back(P_1[2]);
        //seg.push_back(P_2[0]);    seg.push_back(P_2[1]);    seg.push_back(P_2[2]);
        //seg.push_back(P_3[0]);    seg.push_back(P_3[1]);    seg.push_back(P_3[2]);
        seg.push_back(P_4[0]);    seg.push_back(P_4[1]);    seg.push_back(P_4[2]); 

        for (int i=0; i<2; i++) {
          colors.push_back(a); colors.push_back(b); colors.push_back(c); colors.push_back(d);
          //colors.push_back(0.0); colors.push_back(0.0); colors.push_back(0.0); colors.push_back(d);
        }

       uKnots.push_back(uKnotCount);
       uKnotCount++;
        
        flipped = 1;
      } else {
        seg.push_back(P_4[0]);    seg.push_back(P_4[1]);    seg.push_back(P_4[2]);
        //seg.push_back(P_3[0]);    seg.push_back(P_3[1]);    seg.push_back(P_3[2]);
        //seg.push_back(P_2[0]);    seg.push_back(P_2[1]);    seg.push_back(P_2[2]);
        seg.push_back(P_1[0]);    seg.push_back(P_1[1]);    seg.push_back(P_1[2]);

        for (int i=0; i<2; i++) {
          colors.push_back(a); colors.push_back(b); colors.push_back(c); colors.push_back(d);
        }

        uKnots.push_back(uKnotCount);
        uKnotCount++;
      
        flipped = 0;
        
      }
    }

  //Make adjustment to the end of knot vector so that the multiplicity is equal to the order
  int tmpSize = uKnots.size()-1; 
  for (int i=0; i<order; i++) {
    uKnots[tmpSize-i] = uKnotCount-order;
  }
  
  // ADD THE RIBBON TO THE CHAIN MOLECULE
  ch->setRibbon(this);
}


/* ########################## CARTOON SECTION #####################################
This is were you attempt to do the cartoon rendering with arrow heads && such

  ############################################################################### */
 
void ribbon::cartoon(chain *ch) {

      // Set the know vector for the v parameteric direction.  For the flat ribbon this knot vector is simply this

      //Assign the order to the uORder && vOrder variables.
    vOrder = 2;
    uOrder = 4;

    vKnots.resize(4);
    for (int i=0; i<2; i++) {
      vKnots[i] = 0.0;
      vKnots[i+2] = 1.0;
    }

    //Set the multiplicity of the uKnot vector to 4.
    int order = 4;
    for (int i=0; i<order; i++) {
      uKnots.push_back(0);
    }

    int uKnotCount = 1;

    //////////////cout <<CAatoms.size()<<"\tOatoms.size(): " << Oatoms.size()<< endl;
    //THIS SECTION IS ALL FROM THE PAPER ALGORITHMS FOR RIBBON MODELS OF PROTEINS
    //First lets form vector A which is Cai - Ca
    //Lets also go ahead && form vector B which is Oi - Cai
    //Might as well ge the vector C ( the cross product of A && B as well
    //Oh && lets not forget vector D which is crossprocudt of C && A
    vector<float> A(3), B(3), C(3), D(3), D_prev(3), P(3), P_1(3), P_2(3), P_3(3), P_4(3), DOT(3);
    float angle, prevAngle;
    angle = prevAngle = 0;
    static int flipped = 0;
    for (int i=0; i<CAatoms.size()-1; i++) {

      A[0] = CAatoms[i+1][0] - CAatoms[i][0];
      A[1] = CAatoms[i+1][1] - CAatoms[i][1];
      A[2] = CAatoms[i+1][2] - CAatoms[i][2];

      B[0] = Oatoms[i][0] - CAatoms[i][0];
      B[1] = Oatoms[i][1] - CAatoms[i][1];
      B[2] = Oatoms[i][2] - CAatoms[i][2];

      //Cross products for vector C.  This was copied from the Trackball vCross routine
      C[0] = (A[1]*B[2])-(A[2]*B[1]);
      C[1] = (A[2]*B[0])-(A[0]*B[2]);
      C[2] = (A[0]*B[1])-(A[1]*B[0]);

      //Now get the cross product of C && A && save as vector D
      D[0] = (C[1]*A[2])-(C[2]*A[1]);
      D[1] = (C[2]*A[0])-(C[0]*A[2]);
      D[2] = (C[0]*A[1])-(C[1]*A[0]);

      //Now normalize both vector C && vector D
      float cMag = 0; float dMag = 0;
      cMag = sqrt(C[0]*C[0] + C[1]*C[1] + C[2]*C[2]);      //Not sure if you need to add the square root here || not
       dMag = sqrt(D[0]*D[0] + D[1]*D[1] + D[2]*D[2]);     //Not sure if you need to add the square root here || not

      C[0] /= cMag;    C[1] /= cMag;     C[2] /= cMag;
      D[0] /= dMag;    D[1] /= dMag;     D[2] /= dMag;

      //Form point P as the midpoint between Ca && Ca+1

      P[0] = (CAatoms[i+1][0] + CAatoms[i][0])/2;
      P[1] = (CAatoms[i+1][1] + CAatoms[i][1])/2;
      P[2] = (CAatoms[i+1][2] + CAatoms[i][2])/2;

      //Translate in the direction of vector C if part of a helix
      if (type[i] == HELIX) {
        P[0] -= C[0]*1.5;
        P[1] -= C[1]*1.5;
        P[2] -= C[2]*1.5;
      }

      //Now we scale vector D by 1/2 the desired ribbon width
      //D[0] *=1.5; D[1] *= 1.5; D[2] *= 1.5;
      //Checking the angle beteen the two peptide planes
      if (i > 1) {
        DOT[0] = D[0] * D_prev[0];
        DOT[1] = D[1] * D_prev[1];
        DOT[2] = D[2] * D_prev[2];
        angle = DOT[0] +DOT[1] +DOT[2];
        angle =ARCFIX*acos(angle);
      }

      //Keep track of the previous D vectors so that we can assign correct P for Beat-Sheets && other atoms
      D_prev[0] = D[0];
      D_prev[1] = D[1];
      D_prev[2] = D[2];
      prevAngle = angle;

      //if ( angle > 90 && flipped == 0 ) {

      //This makes it skinnier for the loop regions...er turn regions
      if (type[i] == TURN) {
        D[0] /=2; D[1] /= 2; D[2] /= 2;
      }

      P_1[0] = P[0] - D[0];
      P_1[1] = P[1] - D[1];
      P_1[2] = P[2] - D[2];

      P_4[0] = P[0] + D[0];
      P_4[1] = P[1] + D[1];
      P_4[2] = P[2] + D[2];

      /* Scale it agin ...this should get us the inner two points...of the four
        *** NOTE *** This is were you assign the other 2 control points for each peptide plane.  If you should ever need them you know
        were to find them
      */
      D[0] /=2; D[1] /= 2; D[2] /= 2;
      P_2[0] = P[0] - D[0];
      P_2[1] = P[1] - D[1];
      P_2[2] = P[2] - D[2];

      P_3[0] = P[0] + D[0];
      P_3[1] = P[1] + D[1];
      P_3[2] = P[2] + D[2];

     // SET THE COLOR FOR THE SEGEMENT.  THis goes first becuase you are going to evetually use this code to do the cartton segments
      float a, b, c, d;
      if (type[i] == HELIX) {
         a= 1.0; b=0.0; c=0.0; d=1.0;
      } else if (type[i] == SHEET) {
       a = 1.0; b=1.0; c= 0.5; d=1.0;
      } else {
        a = 0.0; b=0.0; c=1.0; d=1.0;
      }

      int vertexCount = 1;
      //BUILD THE CONTROL PNTS... REMEMBER TO FLIP IF 90
      if (angle > 90 && flipped == 0) {
        
       if (type[i+1] == TURN && type[i] != TURN) {
        for (int i=0; i<3; i++) {
          seg.push_back(P_1[0]);    seg.push_back(P_1[1]);    seg.push_back(P_1[2]);
          seg.push_back(P_4[0]);    seg.push_back(P_4[1]);    seg.push_back(P_4[2]); 
          for (int i=0; i<2; i++) {
            colors.push_back(a); colors.push_back(b); colors.push_back(c); colors.push_back(1);
          }
          uKnots.push_back(uKnotCount);
          uKnotCount++;
        }
        D[0] *=4; D[1] *= 4; D[2] *= 4;
        P_1[0] = P[0] - D[0];
        P_1[1] = P[1] - D[1];
        P_1[2] = P[2] - D[2];

        P_4[0] = P[0] + D[0];
        P_4[1] = P[1] + D[1];
        P_4[2] = P[2] + D[2];
        for (int i=0; i<3; i++) {
          seg.push_back(P_1[0]);    seg.push_back(P_1[1]);    seg.push_back(P_1[2]);
          seg.push_back(P_4[0]);    seg.push_back(P_4[1]);    seg.push_back(P_4[2]);
          for (int i=0; i<2; i++) {
            colors.push_back(a); colors.push_back(b); colors.push_back(c); colors.push_back(1);
          }
          uKnots.push_back(uKnotCount);
          uKnotCount++;
        }
       } else {
        seg.push_back(P_1[0]);    seg.push_back(P_1[1]);    seg.push_back(P_1[2]);
        seg.push_back(P_4[0]);    seg.push_back(P_4[1]);    seg.push_back(P_4[2]);
        for (int i=0; i<2; i++) {
          colors.push_back(a); colors.push_back(b); colors.push_back(c); colors.push_back(d);
        }

        uKnots.push_back(uKnotCount);
        uKnotCount++;

       }
        
        flipped = 1;
      } else {
        if (type[i+1] == TURN && type[i] != TURN) {
        for (int i=0; i<3; i++) {
          seg.push_back(P_4[0]);    seg.push_back(P_4[1]);    seg.push_back(P_4[2]);
          seg.push_back(P_1[0]);    seg.push_back(P_1[1]);    seg.push_back(P_1[2]);
          for (int i=0; i<2; i++) {
            colors.push_back(a); colors.push_back(b); colors.push_back(c); colors.push_back(1);
          }
          uKnots.push_back(uKnotCount);
          uKnotCount++;
        }
        D[0] *=4; D[1] *= 4; D[2] *= 4;
        P_1[0] = P[0] - D[0];
        P_1[1] = P[1] - D[1];
        P_1[2] = P[2] - D[2];

        P_4[0] = P[0] + D[0];
        P_4[1] = P[1] + D[1];
        P_4[2] = P[2] + D[2];
        for (int i=0; i<3; i++) {
          seg.push_back(P_4[0]);    seg.push_back(P_4[1]);    seg.push_back(P_4[2]);
          seg.push_back(P_1[0]);    seg.push_back(P_1[1]);    seg.push_back(P_1[2]);
          for (int i=0; i<2; i++) {
            colors.push_back(a); colors.push_back(b); colors.push_back(c); colors.push_back(1);
          }
          uKnots.push_back(uKnotCount);
          uKnotCount++;
        }
       } else {
          seg.push_back(P_4[0]);    seg.push_back(P_4[1]);    seg.push_back(P_4[2]);
          seg.push_back(P_1[0]);    seg.push_back(P_1[1]);    seg.push_back(P_1[2]);
          for (int i=0; i<2; i++) {
            colors.push_back(a); colors.push_back(b); colors.push_back(c); colors.push_back(d);
          }

        uKnots.push_back(uKnotCount);
        uKnotCount++;
        flipped = 0;
       }
        

      }


    }


  //Make adjustment to the end of knot vector so that the multiplicity is equal to the order
  int tmpSize = uKnots.size()-1;
  for (int i=0; i<order; i++) {
    uKnots[tmpSize-i] = uKnotCount-order;
  }

  // ADD THE RIBBON TO THE CHAIN MOLECULE
  ch->setRibbon(this);
}



ribbon::~ribbon(){
  //delete the vector of guidePoint pointers
  for (int i=0; i<allGuidePoints.size(); i++) {
    delete allGuidePoints[i];
  }

  //delete the alocated array of floats;
  seg.clear();
}





































