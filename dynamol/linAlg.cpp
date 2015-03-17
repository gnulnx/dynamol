/***************************************************************************
                          linalg.ccp  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "linAlg.h"


#define M_PI 3.14159265



void  normalize_3f( vector< float > &vec) {
  float mag = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
  vec[0] /= mag;
  vec[1] /= mag;
  vec[2] /= mag;
}

void crossProd(float *prod, const float *a, const float *b) {
   prod[0] = (a[1]*b[2] - a[2]*b[1]);
   prod[1] = -(a[0]*b[2] - a[2]*b[0]);
   prod[2] = (a[0]*b[1] - a[1]*b[0]);
}

void  crossProd(vector<float> &prod, const vector<float> &a, const vector<float> &b) {
  prod[0] = (a[1]*b[2] - a[2]*b[1]);
  prod[1] = -(a[0]*b[2] - a[2]*b[0]);
  prod[2] = (a[0]*b[1] - a[1]*b[0]);
 // ////cout <<"prod: " << endl;
 // for (int i=0; i<3; i++) {
 //    ////cout << prod[i] << endl;
 // }
 // ////cout << prod.size() <<"  prod done"<<endl;
}

void  translate(vector<float> &coords, float x, float y, float z) {
  coords[0] += x; //translate the x component
  coords[1] += y; //translate the y component
  coords[2] += z; //translate the z component
}


vector<double> dirCosines(float *coords1, float *coords2) {
 vector<double> dc(3);// = new float[3];
 double sum = 0;
 //double one = 1;

 /*
 double a = (coords1[0]-coords2[0]);
 double b = (coords1[1]-coords2[1]);
 double c = (coords1[2]-coords2[2]);
 sum += a*a;
 sum += b*b;
 sum += c*c;
 */
 sum += (coords1[0]-coords2[0])*(coords1[0]-coords2[0]);
 sum += (coords1[1]-coords2[1])*(coords1[1]-coords2[1]);
 sum += (coords1[2]-coords2[2])*(coords1[2]-coords2[2]);
 double mag = sqrt(sum);

 //dc[0] = a/mag;
 //dc[1] = b/mag;
 //dc[2] = c/mag;

 dc[0] = (coords1[0]-coords2[0])/mag;
 dc[1] = (coords1[1]-coords2[1])/mag;
 dc[2] = (coords1[2]-coords2[2])/mag;
 
 return dc;

}

void  dirCosines(vector<double> &retVec, float *coords1, float *coords2) {
 //retVec.resize(3);
 double sum = 0;

 double a = (coords1[0]-coords2[0]);
 double b = (coords1[1]-coords2[1]);
 double c = (coords1[2]-coords2[2]);
 sum += a*a;
 sum += b*b;
 sum += c*c;
 double mag = sqrt(sum);

 retVec[0] = a/mag;
 retVec[1] = b/mag;
 retVec[2] = c/mag;
}

vector<float> multTransMatrix(const vector<float> &mat1, const vector<float> &mat2) {
 vector<float> retMat;
 if (mat1.size() == 16) {
  retMat.resize(16);
 } else if (mat1.size() == 4) {
   retMat.resize(4);
 }
 //determine row 1
 retMat[0] = mat1[0]*mat2[0] + mat1[1]*mat2[4] + mat1[2]*mat2[8] + mat1[3]*mat2[12];
 retMat[1] = mat1[0]*mat2[1] + mat1[1]*mat2[5] + mat1[2]*mat2[9] + mat1[3]*mat2[13];
 retMat[2] = mat1[0]*mat2[2] + mat1[1]*mat2[6] + mat1[2]*mat2[10] + mat1[3]*mat2[14];
 retMat[3] = mat1[0]*mat2[3] + mat1[1]*mat2[7] + mat1[2]*mat2[11] + mat1[3]*mat2[15];

 if (retMat.size() == 4) {
   return retMat;
 }
 
 //determine row 2
 retMat[4] = mat1[4]*mat2[0] + mat1[5]*mat2[4] + mat1[6]*mat2[8] + mat1[7]*mat2[12];
 retMat[5] = mat1[4]*mat2[1] + mat1[5]*mat2[5] + mat1[6]*mat2[9] + mat1[7]*mat2[13];
 retMat[6] = mat1[4]*mat2[2] + mat1[5]*mat2[6] + mat1[6]*mat2[10] + mat1[7]*mat2[14];
 retMat[7] = mat1[4]*mat2[3] + mat1[5]*mat2[7] + mat1[6]*mat2[11] + mat1[7]*mat2[15];

 //determine row 3
 retMat[8] = mat1[8]*mat2[0] + mat1[9]*mat2[4] + mat1[10]*mat2[8] + mat1[11]*mat2[12];
 retMat[9] = mat1[8]*mat2[1] + mat1[9]*mat2[5] + mat1[10]*mat2[9] + mat1[11]*mat2[13];
 retMat[10] = mat1[8]*mat2[2] + mat1[9]*mat2[6] + mat1[10]*mat2[10] + mat1[11]*mat2[14];
 retMat[11] = mat1[8]*mat2[3] + mat1[9]*mat2[7] + mat1[10]*mat2[11] + mat1[11]*mat2[15];

 //determine row 4
 retMat[12] = mat1[12]*mat2[0] + mat1[13]*mat2[4] + mat1[14]*mat2[8] + mat1[15]*mat2[12];
 retMat[13] = mat1[12]*mat2[1] + mat1[13]*mat2[5] + mat1[14]*mat2[9] + mat1[15]*mat2[13];
 retMat[14] = mat1[12]*mat2[2] + mat1[13]*mat2[6] + mat1[14]*mat2[10] + mat1[15]*mat2[14];
 retMat[15] = mat1[12]*mat2[3] + mat1[13]*mat2[7] + mat1[14]*mat2[11] + mat1[15]*mat2[15];
 
 return retMat;
}


void  multTransMatrix_4(vector<float> &retMat, const vector<float> &mat1, const vector<float> &mat2) {
 retMat[0] = mat1[0]*mat2[0] + mat1[1]*mat2[4] + mat1[2]*mat2[8] + mat1[3]*mat2[12];
 retMat[1] = mat1[0]*mat2[1] + mat1[1]*mat2[5] + mat1[2]*mat2[9] + mat1[3]*mat2[13];
 retMat[2] = mat1[0]*mat2[2] + mat1[1]*mat2[6] + mat1[2]*mat2[10] + mat1[3]*mat2[14];
 retMat[3] = mat1[0]*mat2[3] + mat1[1]*mat2[7] + mat1[2]*mat2[11] + mat1[3]*mat2[15];
}

void  multTransMatrix_4(vector<float> &retMat, const float *mat1, const vector<float> &mat2) {
 retMat[0] = mat1[0]*mat2[0] + mat1[1]*mat2[4] + mat1[2]*mat2[8] + mat1[3]*mat2[12];
 retMat[1] = mat1[0]*mat2[1] + mat1[1]*mat2[5] + mat1[2]*mat2[9] + mat1[3]*mat2[13];
 retMat[2] = mat1[0]*mat2[2] + mat1[1]*mat2[6] + mat1[2]*mat2[10] + mat1[3]*mat2[14];
 retMat[3] = mat1[0]*mat2[3] + mat1[1]*mat2[7] + mat1[2]*mat2[11] + mat1[3]*mat2[15];
}

void  multTransMatrix_4(float retMat[4], const float mat1[4], const float mat2[16]) {
  retMat[0] = mat1[0]*mat2[0] + mat1[1]*mat2[4] + mat1[2]*mat2[8] + mat1[3]*mat2[12];
  retMat[1] = mat1[0]*mat2[1] + mat1[1]*mat2[5] + mat1[2]*mat2[9] + mat1[3]*mat2[13];
  retMat[2] = mat1[0]*mat2[2] + mat1[1]*mat2[6] + mat1[2]*mat2[10] + mat1[3]*mat2[14];
  retMat[3] = mat1[0]*mat2[3] + mat1[1]*mat2[7] + mat1[2]*mat2[11] + mat1[3]*mat2[15];
}

void  multTransMatrix_16(vector<float> &retMat, const vector<float> &mat1, const vector<float> &mat2) {
  //if (retMat.size() != 16) {
  //  retMat.resize(16);
  //}
 //determine row 1
 retMat[0] = mat1[0]*mat2[0] + mat1[1]*mat2[4] + mat1[2]*mat2[8]  + mat1[3]*mat2[12];
 retMat[1] = mat1[0]*mat2[1] + mat1[1]*mat2[5] + mat1[2]*mat2[9]  + mat1[3]*mat2[13];
 retMat[2] = mat1[0]*mat2[2] + mat1[1]*mat2[6] + mat1[2]*mat2[10] + mat1[3]*mat2[14];
 retMat[3] = mat1[0]*mat2[3] + mat1[1]*mat2[7] + mat1[2]*mat2[11] + mat1[3]*mat2[15];

 //if (retMat.size() == 4) {
 //  return;
 //}

 //determine row 2
 retMat[4] = mat1[4]*mat2[0] + mat1[5]*mat2[4] + mat1[6]*mat2[8] + mat1[7]*mat2[12];
 retMat[5] = mat1[4]*mat2[1] + mat1[5]*mat2[5] + mat1[6]*mat2[9] + mat1[7]*mat2[13];
 retMat[6] = mat1[4]*mat2[2] + mat1[5]*mat2[6] + mat1[6]*mat2[10] + mat1[7]*mat2[14];
 retMat[7] = mat1[4]*mat2[3] + mat1[5]*mat2[7] + mat1[6]*mat2[11] + mat1[7]*mat2[15];

 //determine row 3
 retMat[8] = mat1[8]*mat2[0] + mat1[9]*mat2[4] + mat1[10]*mat2[8] + mat1[11]*mat2[12];
 retMat[9] = mat1[8]*mat2[1] + mat1[9]*mat2[5] + mat1[10]*mat2[9] + mat1[11]*mat2[13];
 retMat[10] = mat1[8]*mat2[2] + mat1[9]*mat2[6] + mat1[10]*mat2[10] + mat1[11]*mat2[14];
 retMat[11] = mat1[8]*mat2[3] + mat1[9]*mat2[7] + mat1[10]*mat2[11] + mat1[11]*mat2[15];

 //determine row 4
 retMat[12] = mat1[12]*mat2[0] + mat1[13]*mat2[4] + mat1[14]*mat2[8] + mat1[15]*mat2[12];
 retMat[13] = mat1[12]*mat2[1] + mat1[13]*mat2[5] + mat1[14]*mat2[9] + mat1[15]*mat2[13];
 retMat[14] = mat1[12]*mat2[2] + mat1[13]*mat2[6] + mat1[14]*mat2[10] + mat1[15]*mat2[14];
 retMat[15] = mat1[12]*mat2[3] + mat1[13]*mat2[7] + mat1[14]*mat2[11] + mat1[15]*mat2[15];

}


vector<float> initMat(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) {
 vector<float> tmp(16);
 tmp[0] = a; tmp[1] = b; tmp[2] = c; tmp[3] = d;
 tmp[4] = e; tmp[5] = f; tmp[6] = g; tmp[7] = h;
 tmp[8] = i; tmp[9] = j; tmp[10] = k; tmp[11] = l;
 tmp[12] = m; tmp[13] = n; tmp[14] = o; tmp[15] = p;

 return tmp;
}

void  identity(vector<float> &mat) {
 if (mat.size() != 16) {
   ////////////cout <<"Wrong size vec in identity"<<endl;
   return;
 }
  mat[0] = 1;  mat[1] = 0;   mat[2] = 0;   mat[3] = 0;
  mat[4] = 0;  mat[5] = 1;  mat[6] = 0;  mat[7] = 0;
  mat[8] = 0;  mat[9] = 0; mat[10] = 1; mat[11] = 0;
  mat[12] = 0; mat[13] = 0;  mat[14] = 0;  mat[15] =1;  
}

void  setRotX(vector<float> &mat, float p1, float p2) {
  if (mat.size() != 16) {
    ////////////cout <<"Wrong size vec in setRotX"<<endl;
    return;
  }

  //p1 = cz/d
  //p2 = cy/d
  mat[0] = 1;  mat[1] = 0;   mat[2] = 0;   mat[3] = 0;
  mat[4] = 0;  mat[5] = p1;  mat[6] = p2;  mat[7] = 0;
  mat[8] = 0;  mat[9] = -p2; mat[10] = p1; mat[11] = 0;
  mat[12] = 0; mat[13] = 0;  mat[14] = 0;  mat[15] = 1;
}

void  setRotX(vector<float> &mat, float angle) {
  if (mat.size() != 16) {
    ////////////cout <<"Wrong size vec in setRotX"<<endl;
    return;
  }

  float p1 = cos( angle*M_PI/180.000);
  float p2 = sin( angle*M_PI/180.000);
  //p2 = cy/d
  mat[0] = 1;  mat[1] = 0;   mat[2] = 0;   mat[3] = 0;
  mat[4] = 0;  mat[5] = p1;  mat[6] = p2;  mat[7] = 0;
  mat[8] = 0;  mat[9] = -p2; mat[10] = p1; mat[11] = 0;
  mat[12] = 0; mat[13] = 0;  mat[14] = 0;  mat[15] = 1;
}

void  setRotY(vector<float> &mat, float p1, float p2) {
  if (mat.size() != 16) {
    ////////////cout <<"Wrong size vec in setRotY"<<endl;
    return;
  }

  //p1 = d
  //p2 = cx
  mat[0] = p1;  mat[1] = 0;  mat[2] = p2;  mat[3] = 0;
  mat[4] = 0;   mat[5] = 1;  mat[6] = 0;   mat[7] = 0;
  mat[8] = -p2; mat[9] = 0;  mat[10] = p1; mat[11] = 0;
  mat[12] = 0;  mat[13] =0;  mat[14] = 0;  mat[15] = 1;
}

void setRotY(vector<float> &mat, float angle) {
  if (mat.size() != 16) {
    ////////////cout <<"Wrong size vec in setRotY"<<endl;
    return;
  }

  float p1 = cos( angle*M_PI/180.000);
  float p2 = sin( angle*M_PI/180.000);
  mat[0] = p1;  mat[1] = 0;  mat[2] = -p2;  mat[3] = 0;
  mat[4] = 0;   mat[5] = 1;  mat[6] = 0;   mat[7] = 0;
  mat[8] = p2; mat[9] = 0;  mat[10] = p1; mat[11] = 0;
  mat[12] = 0;  mat[13] =0;  mat[14] = 0;  mat[15] = 1;

}

void  setRotZ(vector<float> &mat, float p1, float p2) {
  if (mat.size() != 16) {
    ////////////cout <<"Wrong size vec in setRotZ"<<endl;
    return;
  }

  //p1 = cos(delta)
  //p2 = sin(delta)
  mat[0] = p1;  mat[1] = p2;  mat[2] = 0;   mat[3] = 0;
  mat[4] = -p2; mat[5] = p1;  mat[6] = 0;   mat[7] = 0;
  mat[8] = 0;   mat[9] = 0;   mat[10] = 1;  mat[11] = 0;
  mat[12] = 0;  mat[13] = 0;  mat[14] = 0;  mat[15] = 1;
}

void setRotZ(vector<float> &mat, float angle) {
  if (mat.size() != 16) {
    ////////////cout <<"Wrong size vec in setRotZ"<<endl;
    return;
  }

  float p1 = cos( angle*M_PI/180.000);
  float p2 = sin( angle*M_PI/180.000);
  mat[0] = p1;  mat[1] = p2;  mat[2] = 0;   mat[3] = 0;
  mat[4] = -p2; mat[5] = p1;  mat[6] = 0;   mat[7] = 0;
  mat[8] = 0;   mat[9] = 0;   mat[10] = 1;  mat[11] = 0;
  mat[12] = 0;  mat[13] = 0;  mat[14] = 0;  mat[15] = 1;
}

void  setTransMat(vector<float> &mat, float x, float y, float z) {
  if (mat.size() != 16) {
    ////////////cout <<"Wrong size vec in setRotZ"<<endl;
    return;
  }

  mat[0] = 1;   mat[1] = 0;   mat[2] = 0;   mat[3] = 0;
  mat[4] = 0;   mat[5] = 1;   mat[6] = 0;   mat[7] = 0;
  mat[8] = 0;   mat[9] = 0;   mat[10] = 1;  mat[11] = 0;
  mat[12] = -x; mat[13] = -y; mat[14] = -z; mat[15] = 1;
}

void  printMatrix(const vector<float> &mat) {
  if (mat.size() != 16) {
    ////////////cout <<"Wrong size vec in setRotZ"<<endl;
    return;
  }

  ////////////cout.setf(ios::fixed);
  for (int i=0; i<4; i++) {
     ////////////cout <<setprecision(2)<<setw(7)<<mat[i];
  }
  ////////////cout << endl;

  for (int i=4; i<8; i++) {
     ////////////cout <<setprecision(2)<<setw(7)<<mat[i];
  }
  ////////////cout << endl;

  for (int i=8; i<12; i++) {
     ////////////cout <<setprecision(2)<<setw(7)<<mat[i];
  }
  ////////////cout << endl;

  for (int i=12; i<16; i++) {
     ////////////cout <<setprecision(2)<<setw(7)<<mat[i];
  }
  ////////////cout << endl;

  ////////////cout << endl;
}


vector<float>  multiMatrix(const vector<float> &vec, const vector<float> &mat) {
 vector<float> res(3);

 res[0] = vec[0]*mat[0] + vec[1]*mat[4] + vec[2]*mat[8];
 res[1] = vec[0]*mat[1] + vec[1]*mat[5] + vec[2]*mat[9];
 res[2] = vec[0]*mat[2] + vec[1]*mat[6] + vec[2]*mat[10];


 return res;
}

void  multiMatrix(vector<float> &retMat, const vector<float> &mat1, const vector<float> &mat2) {
  retMat[0] = mat1[0]*mat2[0] + mat1[1]*mat2[4] + mat1[2]*mat2[8];
  retMat[1] = mat1[0]*mat2[1] + mat1[1]*mat2[5] + mat1[2]*mat2[9];
  retMat[2] = mat1[0]*mat2[2] + mat1[1]*mat2[6] + mat1[2]*mat2[10];
}


void invertMatrix(vector<float> &mat, vector<float> &dst) {
  float tmp[12]; /*temp array for pairs*/
  float src[16]; /*array of transpose source matrix*/
  float det;

  /* transpose matrix */
  for (int i=0; i<4; i++) {
    src[i]      = mat[i*4];
    src[i+4]    = mat[i*4+1];
    src[i+8]    = mat[i*4+2];
    src[i+12]    = mat[i*4+3];
  }

  /* calculate pairs for first 8 elements (cofactors) */
  tmp[0] =  src[10] * src[15];
  tmp[1] =  src[11] * src[14];
  tmp[2] =  src[9]  * src[15];
  tmp[3] =  src[11] * src[13];
  tmp[4] =  src[9]  * src[14];
  tmp[5] =  src[10] * src[13];
  tmp[6] =  src[8]  * src[15];
  tmp[7] =  src[11] * src[12];
  tmp[8] =  src[8]  * src[14];
  tmp[9] =  src[10] * src[12];
  tmp[10] = src[8]  * src[13];
  tmp[11] = src[9]  * src[12];

  /* calculate first 8 elements (cofactors) */
  dst[0]  = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
  dst[0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];

  dst[1]  = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
  dst[1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
  
  dst[2]  = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
  dst[2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];

  dst[3]  = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
  dst[3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];

  dst[4]  = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
  dst[4] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];

  dst[5]  = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
  dst[5] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];

  dst[6]  = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
  dst[6] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];

  dst[7]  = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
  dst[7] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];

  /* calculate paris for second 8 elements (cofactors) */
  tmp[0]  = src[2]*src[7];
  tmp[1]  = src[3]*src[6];
  tmp[2]  = src[1]*src[7];
  tmp[3]  = src[3]*src[5];
  tmp[4]  = src[1]*src[6];
  tmp[5]  = src[2]*src[5];
  tmp[6]  = src[0]*src[7];
  tmp[7]  = src[3]*src[4];
  tmp[8]  = src[0]*src[6];
  tmp[9]  = src[2]*src[4];
  tmp[10] = src[0]*src[5];
  tmp[11] = src[1]*src[4];

   /* calculate second 8 elements (cofactors) */
  dst[8]  = tmp[0]*src[13]    + tmp[3]*src[14] + tmp[4]*src[15];
  dst[8] -= tmp[1]*src[13]    + tmp[2]*src[14] + tmp[5]*src[15];

  dst[9]  = tmp[1]*src[12]    + tmp[6]*src[14] + tmp[9]*src[15];
  dst[9] -= tmp[0]*src[12]    + tmp[7]*src[14] + tmp[8]*src[15];

  dst[10]  = tmp[2]*src[12]   + tmp[7]*src[13] + tmp[10]*src[15];
  dst[10] -= tmp[3]*src[12]   + tmp[6]*src[13] + tmp[11]*src[15];

  dst[11]  = tmp[5]*src[12]   + tmp[8]*src[13] + tmp[11]*src[14];
  dst[11] -= tmp[4]*src[12]   + tmp[9]*src[13] + tmp[10]*src[14];

  dst[12]  = tmp[2]*src[10]   + tmp[5]*src[11] + tmp[1]*src[9];
  dst[12] -= tmp[4]*src[11]   + tmp[0]*src[9] + tmp[3]*src[10];

  dst[13]  = tmp[8]*src[11]   + tmp[0]*src[8] + tmp[7]*src[10];
  dst[13] -= tmp[6]*src[10]   + tmp[9]*src[11] + tmp[1]*src[8];

  dst[14]  = tmp[6]*src[9]    + tmp[11]*src[11] + tmp[3]*src[8];
  dst[14] -= tmp[10]*src[11]  + tmp[2]*src[8] + tmp[7]*src[9];

  dst[15]  = tmp[10]*src[10]  + tmp[4]*src[8] + tmp[9]*src[9];
  dst[15] -= tmp[8]*src[9]    + tmp[11]*src[10] + tmp[5]*src[8];

  det = src[0]*dst[0]+src[1]*dst[1]+src[2]*dst[2]+src[3]*dst[3];

  /*calcluate matrix inverse*/
  det = 1/det;
  for (int j=0; j<16; j++) 
    dst[j] *= det;
}


float dist(const vector<float> &p1, const vector<float> &p2) {
  /*
  float dist = 0;
  //float a = (p1[0]-p2[0]);
  //float b = (p1[1]-p2[1]);
  //float c = (p1[2]-p2[2]);
  //dist = a*a + b*b + c*c;
  dist += (p1[0]-p2[0]) * (p1[0]-p2[0]);
  dist += (p1[1]-p2[1]) * (p1[1]-p2[1]);
  dist += (p1[2]-p2[2]) * (p1[2]-p2[2]);

  return sqrt(dist);
  */
  if (p1.size() != p2.size()) {
    ////////////cout <<"vectors are not same size"<<endl;
    return 0.0;
  }
  float total = 0;
  for (int i=0; i<p1.size(); i++) {
     total += (p1[i] - p2[i]) * (p1[i] - p2[i]);
  }
  if (total == 0) return 0.0;
  return sqrt(total);
  //return 1000;
}


float distance(float *p1, float *p2) {
 //////////////cout <<"distance from linAlg"<<endl;
 float a = p1[0]-p2[0];
 float b = p1[1]-p2[1];
 float c = p1[2]-p2[2];

 return sqrt(a*a + b*b + c*c);
}

double distance(vector<double> &p1, vector<double> &p2) {
 double a = p1[0]-p2[0];
 double b = p1[1]-p2[1];
 double c = p1[2]-p2[2];

 return sqrt(a*a + b*b + c*c);
}

void quatToMatrix( vector<float> &mat, vector<float> &q) {
  //////////////cout <<"quatToMatrix"<<endl;
  //This code was taken from openGL programming fo the X-windos system
  /*
  if (mat.size() != 16 || q.size() != 4) {
    ////////////cout <<"size error in quatToMatrix"<<endl;
    return;
  }   */

  float xx = q[0]*q[0];
  float xy = q[0]*q[1];
  float xz = q[0]*q[2];
  float xw = q[0]*q[3];

  float yy = q[1]*q[1];
  float yz = q[1]*q[2];
  float yw = q[1]*q[3];

  float zz = q[2]*q[2];
  float zw = q[2]*q[3];


  mat[0] = 1-2 * (yy+zz);
  mat[1] = 2*(xy-zw);
  mat[2] = 2*(xz+yw);
  mat[3] = 0;

  mat[4] = 2 * (xy+zw);
  mat[5] = 1-2 * (xx + zz);
  mat[6] = 2 * (yz - xw);
  mat[7] = 0;

  mat[8] = 2 * (xz - yw);
  mat[9] = 2 * (yz + xw);
  mat[10] = 1 - 2 * (xx + yy);
  mat[11] = 0;

  mat[12] = 0;
  mat[13] = 0;
  mat[14] = 0;
  mat[15] = 1;
}

void quatToMatrix_row(vector<float> &mat, vector<float> &q) {
  float xx = q[0]*q[0];
  float xy = q[0]*q[1];
  float xz = q[0]*q[2];
  float xw = q[0]*q[3];
  
  float yy = q[1]*q[1];
  float yz = q[1]*q[2];
  float yw = q[1]*q[3];

  float zz = q[2]*q[2];
  float zw = q[2]*q[3];
   
  
  mat[0] = 1-2 * (yy+zz);
  mat[1] = 2*(xy-zw);
  mat[2] = 2*(xz+yw);
  mat[3] = 0;

  mat[4] = 2 * (xy+zw);
  mat[5] = 1-2 * (xx + zz);
  mat[6] = 2 * (yz - xw);
  mat[7] = 0;

  mat[8] = 2 * (xz - yw);
  mat[9] = 2 * (yz + xw);
  mat[10] = 1 - 2 * (xx + yy);
  mat[11] = 0;

  mat[12] = 0;
  mat[13] = 0;
  mat[14] = 0;
  mat[15] = 1;
}


void quatToMatrix(float mat[], float q[]) {
  //This code was taken from openGL programming fo the X-windos system
  /*
  if (mat.size() != 16 || q.size() != 4) {
    ////////////cout <<"size error in quatToMatrix"<<endl;
    return;
  }   */

  float xx = q[0]*q[0];
  float xy = q[0]*q[1];
  float xz = q[0]*q[2];
  float xw = q[0]*q[3];

  float yy = q[1]*q[1];
  float yz = q[1]*q[2];
  float yw = q[1]*q[3];

  float zz = q[2]*q[2];
  float zw = q[2]*q[3];

  float ww = q[3]*q[3];

  mat[0] = 1-2 * (yy+zz);
  mat[1] = 2*(xy-zw);
  mat[2] = 2*(xz+yw);
  mat[3] = 0;

  mat[4] = 2 * (xy+zw);
  mat[5] = 1-2 * (xx + zz);
  mat[6] = 2 * (yz - xw);
  mat[7] = 0;

  mat[8] = 2 * (xz - yw);
  mat[9] = 2 * (yz + xw);
  mat[10] = 1 - 2 * (xx + yy);
  mat[11] = 0;

  mat[12] = 0;
  mat[13] = 0;
  mat[14] = 0;
  mat[15] = 1;

}

void axis_to_quat(vector<float> &axis, float phi, vector<float> &quat) {
  quat.resize(4);    //wuat in format  (x, y, z, angle)

  float sin_a = sin(phi/2.0);
  float cos_a = cos(phi/2.0);
  
  quat[0] = axis[0]*sin_a;
  quat[1] = axis[1]*sin_a;
  quat[2] = axis[2]*sin_a;
  quat[3] = cos_a;

  

  normalizef(quat);
}


void  multQuats(vector<float> &res, const vector<float> &q1, const vector<float> &q2) {

 /* Quaternion multiplication is represented as follows

   q1 = (V1, s1);
   q2 = (V2, s2);

   q1*q2 = (V1 X V1 + V1*s2 + V2*s1 , s1*s2 - V1*V2);

   **note (V1 X V1 + V1*s2 + V2*s1) is x, y, z.  cross product is a vector
   while the V1*V2 is a scaler...dot product
 */
  
 vector<float> cross(3);
 vector<float> q1s2(3), q2s1(3);
 // The cross product works as follows
 //          i   j   k
 //  A X B = a0  a1  a2 = ( a1*b2 - a2*b1 )i - ( a0*b2 - a2*b0 )j + ( a0*b1 - a1*b0 )k
 //          b0  b1  b2
 
 cross[0] = (q1[1]*q2[2] - q1[2]*q2[1]);
 cross[1] = (q1[0]*q2[2] - q1[2]*q2[0]);
 cross[2] = (q1[0]*q2[1] - q1[1]*q2[0]);

 q1s2[0] = q1[0]*q2[3];
 q1s2[1] = q1[1]*q2[3];
 q1s2[2] = q1[2]*q2[3];

 q2s1[0] = q2[0]*q1[3];
 q2s1[1] = q2[1]*q1[3];
 q2s1[2] = q2[2]*q1[3];

 
 float dot = q1[0]*q2[0] + q1[1]*q2[1] + q1[2]*q2[2];
 float ss  = q1[3]*q2[3];

 res[0] = cross[0] + q1s2[0] + q2s1[0];
 res[1] = cross[1] + q1s2[1] + q2s1[1];
 res[2] = cross[2] + q1s2[2] + q2s1[2];
 res[3] = ss-dot;
 
}


void mulit_4X16(float retVec[], float vec[], float mat[]) {
  retVec[0] = vec[0]*mat[0] + vec[1]*mat[4] + vec[2]*mat[8] + vec[3]*mat[12];
 retVec[1] = vec[0]*mat[1] + vec[1]*mat[5] + vec[2]*mat[9] + vec[3]*mat[13];
  retVec[2] = vec[0]*mat[2] + vec[1]*mat[6] + vec[2]*mat[10] + vec[3]*mat[14];
  retVec[3] = vec[0]*mat[3] + vec[1]*mat[7] + vec[2]*mat[11] + vec[3]*mat[15];
}

void mulit_4X16(vector<float> &retVec, vector<float> &vec, vector<float> &mat) {
  retVec[0] = vec[0]*mat[0] + vec[1]*mat[4] + vec[2]*mat[8] + vec[3]*mat[12];
  retVec[1] = vec[0]*mat[1] + vec[1]*mat[5] + vec[2]*mat[9] + vec[3]*mat[13];
  retVec[2] = vec[0]*mat[2] + vec[1]*mat[6] + vec[2]*mat[10] + vec[3]*mat[14];
  retVec[3] = vec[0]*mat[3] + vec[1]*mat[7] + vec[2]*mat[11] + vec[3]*mat[15];
}


void axis_to_quat(float axis[], float phi, float quat[]) {
  //////////////cout <<"You are in axis_to_quat "<< phi << endl;
  normalizef(axis, 3);
  float sin_a = sin(phi/2.0);
  float cos_a = cos(phi/2.0);

  quat[0] = axis[0]*sin_a;
  quat[1] = axis[1]*sin_a;
  quat[2] = axis[2]*sin_a;
  quat[3] = cos_a;

  normalizef(quat, 4);
}

void  normalizef(float vec[], const int size) {
  float mag =0;
  for (unsigned int i=0; i<size; i++) mag += vec[i]*vec[i];

  mag = sqrt(mag);
  for (unsigned int i=0; i<size; i++) vec[i] /= mag;
  
}

void normalizef( vector< float > &vec) {
  float mag =0;
  for (unsigned int i=0; i<vec.size(); i++) mag += vec[i]*vec[i];
  mag = sqrt(mag);
  for (unsigned int i=0; i<vec.size(); i++)vec[i] /= mag;
}


void  normalized(double vec[], const int size) {
  float mag =0;
  for (unsigned int i=0; i<size; i++) mag += vec[i]*vec[i];

  mag = sqrt(mag);
  for (unsigned int i=0; i<size; i++) vec[i] /= mag;
  
}



void buildRotMat(float m[4][4], float quat[4]) {

  m[0][0] = 1.0-(2.0*(quat[1]*quat[1] + quat[2]*quat[2]));
  m[0][1] = 2.0*(quat[0]*quat[1] - quat[2]*quat[3]);
  m[0][2] = 2.0*(quat[2]*quat[0] + quat[1]*quat[3]);
  m[0][3] = 0.0;

  m[1][0] = 2.0*(quat[0]*quat[1] + quat[2]*quat[3]);
  m[1][1] = 1.0-(2.0*(quat[2]*quat[2] + quat[0]*quat[0]));
  m[1][2] = 2.0*(quat[1]*quat[2] - quat[0]*quat[3]);
  m[1][3] = 0.0;

  m[2][0] = 2.0*(quat[2]*quat[0] - quat[1]*quat[3]);
  m[2][1] = 2.0*(quat[1]*quat[2] + quat[0]*quat[3]);
  m[2][2] = 1.0-(2.0*(quat[1]*quat[1] + quat[0]*quat[0]));
  m[2][3] = 0.0;

  m[3][0] = 0.0;
  m[3][1] = 0.0;
  m[3][2] = 0.0;
  m[3][3] = 1.0;
}

void  vCross(const float vec1[3], const float vec2[3], float prod[3]) {
  prod[0] = (vec1[1]*vec2[2] - vec1[2]*vec2[1]);
  prod[1] = -(vec1[0]*vec2[2] - vec1[2]*vec2[0]);
  prod[2] = (vec1[0]*vec2[1] - vec1[1]*vec2[0]);
}

void vAdd(const float vect1[3], const float vect2[3], float dest[3]) {
  dest[0] = vect1[0] + vect2[0];
  dest[1] = vect1[1] + vect2[1];
  dest[2] = vect1[2] + vect2[2];
}

void vSub(const float point1[3], const float point2[3], float dest[3]) {
  dest[0] = point1[0] - point2[0];
  dest[1] = point1[1] - point2[1];
  dest[2] = point1[2] - point2[2];
}

void vZero(float vect[3]) {
  vect[0] = 0;
  vect[1] = 0;
  vect[2] = 0;
}

float vDot(const float vect1[3], const float vect2[3]) {;
  return (vect1[0]*vect2[0] + vect1[1]*vect2[1] + vect1[2]*vect2[2]);
}

void vCopy(float vect1[], float vect2[]) {
  vect2[0] = vect1[0];
  vect2[1] = vect1[1];
  vect2[2] = vect1[2];
}

void vNormal(float vect[3]) {
  float length = sqrt(vect[0]*vect[0] + vect[1]*vect[1] + vect[2]*vect[2]);
  vScale(vect, 1.0/length);
}
void vScale(float vect[3], float divisor) {
  vect[0] *= divisor;
  vect[1] *= divisor;
  vect[2] *= divisor;
}

void quatToMatrix(QUAT q, float mat[16]) {
  float xx = q[0]*q[0];
  float xy = q[0]*q[1];
  float xz = q[0]*q[2];
  float xw = q[0]*q[3];

  float yy = q[1]*q[1];
  float yz = q[1]*q[2];
  float yw = q[1]*q[3];

  float zz = q[2]*q[2];
  float zw = q[2]*q[3];

  float ww = q[3]*q[3];

  mat[0] = 1-2 * (yy+zz);
  mat[1] = 2*(xy-zw);
  mat[2] = 2*(xz+yw);
  mat[3] = 0;

  mat[4] = 2 * (xy+zw);
  mat[5] = 1-2 * (xx + zz);
  mat[6] = 2 * (yz - xw);
  mat[7] = 0;

  mat[8] = 2 * (xz - yw);
  mat[9] = 2 * (yz + xw);
  mat[10] = 1 - 2 * (xx + yy);
  mat[11] = 0;

  mat[12] = 0;
  mat[13] = 0;
  mat[14] = 0;
  mat[15] = 1;
}

float vLength(float vec[3]) {
 return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}

float angleDegrees(const float cd1[3], const float mid[3], const float cd2[3]) {
  return angleRadians(cd1, mid, cd2)*57.2958;
}

float angleRadians(const float cd1[3], const float mid[3], const float cd2[3]) {
   float p1[3], p2[3];

  float dp, mag1, mag2; //doProduct mag1, mag2t
  mag1 = mag2 = dp = 0;

  for (int i=0; i<3; i++) {
    p1[ i ] = cd1[ i ] - mid[ i ];
    p2[ i ] = cd2[ i ] - mid[ i ];

    dp += p1[ i ] * p2[ i ];
    mag1 += p1[ i ] * p1[ i ];
    mag2 += p2[ i ] * p2[ i ];
  }
  
  if (mag1 == 0.0) return 0.0;
  else mag1 = sqrt(mag1);
  
  if (mag2 == 0.0) return 0.0;
  else mag2 = sqrt(mag2);

  float tmp = dp / (mag1*mag2);
  if (tmp > 1) tmp = 1;
  if ( tmp < -1) tmp = -1;
  return acos( tmp ); 
}

void rowToColumn(float *col, const float *row) {
   col[0] = row[0];
   col[1] = row[4];
   col[2] = row[8];
   col[3] = row[12];
   
   col[4] = row[1];
   col[5] = row[5];
   col[6] = row[9];
   col[7] = row[13];
   
   col[8] = row[2];
   col[9] = row[6];
   col[10] = row[10];
   col[11] = row[14];
   
   col[12] = row[3];
   col[13] = row[7];
   col[14] = row[11];
   col[15] = row[15];
}

void rowToColumn(vector<float> &col, const vector<float> &row) {
   if (col.size() != 16 || row.size() != 16) {
      ////////////cout <<"Wrong size vectors: " << endl;
      return;
   }
   col[0] = row[0];
   col[1] = row[4];
   col[2] = row[8];
   col[3] = row[12];
   
   col[4] = row[1];
   col[5] = row[5];
   col[6] = row[9];
   col[7] = row[13];
   
   col[8] = row[2];
   col[9] = row[6];
   col[10] = row[10];
   col[11] = row[14];
   
   col[12] = row[3];
   col[13] = row[7];
   col[14] = row[11];
   col[15] = row[15];
}

void alignLines(const float *l1_p1, const float *l1_p2, float *l2_p1, float *l2_p2)
{
    for (int i=0; i<3; i++) {
	l2_p1[i] -= l1_p1[i];
	l2_p2[i] -= l1_p1[i];
    }
/*
    float lp11[3], lp12[3];
    for (int i=0; i<3; i++) {
	lp11[i] = l1_p1[i];
	lp12[i] = l1_p2[i];
    }

    float xTrans = -lp11[0];
    float yTrans = -lp11[1];
    float zTrans = -lp11[2];
    /** first lets translate all points such that l1_p1 is at the origin and such
   
   for (int i=0; i<3; i++) {
	l2_p1[i] -= lp11[i];
        l2_p2[i] -= lp11[i];
	lp11[i] -= lp11[i];
	lp12[i] -= lp11[i];
    }

    float axis[3];
    crossProd(axis, lp12, l2_p1);  

    float angle = angleRadians(lp12, l2_p2, l2_p1);
    ////////////cout <<"angle is: " << angle << endl;
    QUAT q(angle, axis); 
    float rotM[16];
    q.buildMatrix(rotM);

    multTransMatrix_4(l2_p1, l2_p1, rotM);
    multTransMatrix_4(l2_p2, l1_p2, rotM);
   
    for (int i=0; i<3; i++) {
	l2_p1[i] += l1_p1[i];
	l2_p2[i] += l1_p1[i];
    } 
*/
    ////////////cout <<"Leaving alignLines"<<endl;  
}

void alignLines(const vector<float> &l1_p1, const vector<float> &l1_p2, vector<float> &l2_p1, vector<float> &l2_p2) 
{
   alignLines(&l1_p1[0], &l1_p2[0], &l2_p1[0], &l2_p2[0]);
}



































