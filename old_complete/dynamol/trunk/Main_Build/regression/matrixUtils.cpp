/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "matrixUtils.h"
#include <fstream>
#include <iostream>
using namespace std;

Matrix &readMatrix(string fileName) {
  ifstream inFile(fileName.c_str(), ios::in);
  if (!inFile) {
     cout <<fileName <<" was not opened"<<endl;
     cout <<"Default matrix is returned" << endl;
     return *(new Matrix());
  }     
  
  int rows, cols;
  inFile >> rows >> cols;
  Matrix *M = new Matrix(rows, cols);
  
  
  for (int i=0; i<rows; i++) {
     for (int j=0; j<cols; j++) {
        inFile >> M->Mat[i][j];
     }
  }
  return *M;
}