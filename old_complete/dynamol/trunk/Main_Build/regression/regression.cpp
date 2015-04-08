/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
 
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>
#include <matrix.h>
#include "matrixUtils.h"
#include "regress.h"
using namespace std;

int main(int argc, char *argv[])
{
  cout << "Hello, world!" << endl;

  Matrix X = readMatrix("X.txt");   
  Matrix Y = readMatrix("Y.txt");
 
  Regress R;
  //R.MR(Y, X);
  R.PLS(Y, X);
  //R.Ypred.print();
  //R.residuals.print();
  //cout << endl;
  //R.Ytotal.print();
  //R.SSE.print();
  cout <<"SSE: " <<R.SSE[0][0] << endl;
  cout <<"R2: " <<R.R2[0][0] << endl;
  return EXIT_SUCCESS;
}
