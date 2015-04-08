/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "regress.h"
#include <iostream>

Regress::Regress()
{
}


Regress::~Regress()
{
}

void Regress::PLS(Matrix &Y, Matrix &X) {
   X.colCenter();
   X.colNormalize();
   Y.colCenter();
   Y.colNormalize();

   Matrix E = X;
   Matrix F = Y;
   Matrix ET = E.transpose();
   Matrix Ft = F.transpose();

   Matrix u = Y;

   Matrix w = ET*u;
   w.colNormalize();
   Matrix t = E*w;
   t.colNormalize();
   Matrix c = Ft*t;
   c.colNormalize();
   u = F*c;

   Matrix test = t.transpose()*t;
   test.print();
}

void Regress::MR(Matrix &Y, Matrix &X) {
#if 0
  X.colCenter();
  X.colNormalize();
  Y.colCenter();
  Y.colNormalize();
#endif
  Matrix XT = X.transpose();
  Matrix XX = XT*X;
  Matrix XXI = XX.invert();

  Matrix XTY = XT*Y;

  Matrix YT = Y.transpose();
  Matrix YTY = YT*Y;
 

  Matrix b = XXI*XT*Y;
  
  // calculate Ypred
  Ypred = X*b;
  
  //Calculate the residuals
  residuals = Ypred - Y;
  
  //Calculate Yavg
  //Calculate Ytotal
  Yavg.resize(Y.numCols(), 1);
  Ytotal.resize(Y.numCols(), 1);
  for (int i=0; i<Y.numCols(); i++) {
     double sum = 0;
     for (int j=0; j<Y.numRows(); j++) {
       sum += Y[j][i];
     }
     Ytotal[i][0] = sum;
     double average = sum / Y.numRows();
     Yavg[i][0] = average;
  }

  //Calculate SSE
  SSE.resize(Y.numCols(), 1);
  R2.resize(Y.numCols(), 1);
  for (int i=0; i<Ypred.numCols(); i++) {
     double sse = 0;
     double R2top = 0;
     double R2bottom = 0;
     for (int j=0; j<Ypred.numRows(); j++) {
        double tmp1 = Y[j][i] - Ypred[j][i];
        //double tmp2 = Ypred[j][i] - Yavg[i][0];
        double top    = Ypred[j][i] - Yavg[i][0];
        double bottom = Y[j][i] - Yavg[i][0];
	sse += tmp1*tmp1;
        R2top += top*top;
        R2bottom += bottom*bottom;
     }
     SSE[i][0] = sse;
     //TSS[i][0] = tss;
     R2[i][0] = R2top/R2bottom;
  }
     
  

}

