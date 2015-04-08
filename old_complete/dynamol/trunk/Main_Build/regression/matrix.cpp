/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "matrix.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace std;
Matrix::Matrix()
{
   Mat.resize(1);
   for (int i=0; i<Mat.size(); i++) {
      Mat[i].resize(1);
      for (int j=0; j< Mat[i].size(); j++) {
         Mat[i][j] = 1.0;
      }
   }
}

Matrix::Matrix(int rows, int cols) {
   Mat.resize(rows);
   for (int i=0; i<Mat.size(); i++) {
      Mat[i].resize(cols);
      for (int j=0; j< Mat[i].size(); j++) {
         Mat[i][j] = 1.0;
      }
   }
}

Matrix::~Matrix()
{
}

Matrix &Matrix::operator=( const Matrix &M ) {
   this->Mat = M.Mat;
   return *this;
}


vector<double> &Matrix::operator[]( int i ) {
   return Mat[i];
}

bool Matrix::operator&( Matrix &M ) {
   if (M.numRows() == this->numRows() && M.numCols() == this->numCols())
      return true;
      
   return false;
}

Matrix &Matrix::operator+( Matrix &M ) {
   if ( !(M & *this)) {
      cout <<"Matrix addition cannot be peformed on different size Matrices"<<endl;
      cout <<"Returning default Matrix"<<endl;
      Matrix *C = new Matrix();
      return *C;
   }
   
   Matrix *C = new Matrix(M.numRows(), M.numCols());
   for (int i=0; i<M.numRows(); i++) {
      for (int j=0; j<M.numCols(); j++) {
         C->Mat[i][j] = M[i][j] + Mat[i][j];
      }
   }
   //I Think this is wrong
   return *C;
}

bool Matrix::operator+=( Matrix &M ) {
   if ( !(M & *this)) {
      cout <<"Matrix addition cannot be peformed on different size Matrices"<<endl;
      cout <<"Nothing will be done"<<endl;
      return false;
   }
   
   for (int i=0; i<M.numRows(); i++) {
      for (int j=0; j<M.numCols(); j++) {
         Mat[i][j] = Mat[i][j] + M[i][j];
      }
   }
   return true;
}

Matrix &Matrix::operator-( Matrix &M ) {
   if ( !(M & *this)) {
      cout <<"Matrix subtraction cannot be peformed on different size Matrices"<<endl;
      cout <<"Returning default Matrix"<<endl;
      Matrix *C = new Matrix();
      return *C;
   }
   
   Matrix *C = new Matrix(M.numRows(), M.numCols());
   for (int i=0; i<M.numRows(); i++) {
      for (int j=0; j<M.numCols(); j++) {
         C->Mat[i][j] = M[i][j] - Mat[i][j];
      }
   }

   return *C;
}

bool Matrix::operator-=( Matrix &M ) {
   if ( !(M & *this)) {
      cout <<"Matrix subtraction cannot be peformed on different size Matrices"<<endl;
      cout <<"Nothing will be done"<<endl;
      return false;
   }
   
   for (int i=0; i<M.numRows(); i++) {
      for (int j=0; j<M.numCols(); j++) {
         Mat[i][j] = Mat[i][j] - M[i][j];
      }
   }
   return true;
}

Matrix &Matrix::operator*( Matrix &B ) {
  if ( !(this->numCols() == B.numRows()) ) {
     cout <<"Cols in A are not equal to rows in B:  ";
     cout <<"Matrices will not be multiplied.  A 1X1 matrix ";
     cout <<"Will be returned with element value = 1"<<endl;
     cout <<this->numCols() <<setw(12) << B.numRows() << endl;
     //cout <<this->numRows() << setw(12) << B.numCols() << endl;
     return *(new Matrix());
  }
  int p = this->numCols();
  Matrix *C = new Matrix(this->numRows(), B.numCols());
  for (int i=0; i<C->numRows(); i++) {

     for (int j=0; j<C->numCols(); j++) {
        double sum = 0;
        for (int k=0; k<p; k++) {
            sum += Mat[i][k] * B.Mat[k][j];
        } 
        C->Mat[i][j] = sum;
     }
  }
  
  return *C;
}

bool Matrix::operator*=( Matrix &B ) {
   if ( !(this->numCols() == B.numRows()) ) {
     cout <<"Cols in A are not equal to rows in B:  ";
     cout <<"Matrices will not be multiplied. "<<endl;
     return false;
  }
  Matrix C = *this * B;
  this->Mat = C.Mat;
}

bool Matrix::resize( int i, int j ) {
  if (i <= 0 || j <= 0) {
     cout <<"Matrix cannot be initialized to size 0"<<endl;
     return false;
  }
  Mat.resize(i);
  for (int i=0; i<Mat.size(); i++) {
     Mat[i].resize(j);
     for (int j=0; j<Mat[i].size(); j++) {
        Mat[i][j] = 1.0;
     }
  }
  return true;
}

Matrix &Matrix::transpose() {
   Matrix *M = new Matrix(this->numCols(), this->numRows());

   for (int i=0; i<numRows(); i++) {
      for (int j=0; j<numCols(); j++) {
         M->Mat[j][i] = this->Mat[i][j];
      }
   }
   return *M;
}

int Matrix::numRows() {
  return Mat.size();
}
 
int Matrix::numCols() {
  return Mat[0].size();
}
    
void Matrix::print() {
   //cout <<"Matrix: " << Mat.size() <<setw(12) << Mat[0].size() << endl;
   for (int i=0; i<Mat.size(); i++) {
      for (int j=0; j<Mat[i].size(); j++) {
         if (j != Mat[i].size() -1) {
            cout << Mat[i][j] << setw(15);
         }  else {
            cout << Mat[i][j];
         }
      }
      cout << endl;
   }
   cout << endl;
}

bool Matrix::swapRows(int i, int j) {
  if (i < numRows() && j < numRows()) {
     vector<double> hold = Mat[j];
     Mat[j] = Mat[i];
     Mat[i] = hold;
     
     return true;
  }
  
  cout <<"Either Index i or j wsa greater than the number of rows in the matrix ";
  cout <<"Row swap is simply not possible"<<endl;
  return false;
}

bool Matrix::rowMult( int row, double value ) {
   if (row >= numRows() ) {
      cout <<"Row out of range.  Unable to perforn row multiplication"<<endl;
      return false;
   }
   
   if (value == 0.0) {
      cout <<"May  not multiply a row by zero."<<endl;
      return false;
   }
   
   for (int j=0; j<Mat[row].size(); j++) {
      Mat[row][j] *= value;
   }
   
   return true;
}

bool Matrix::addRow(int i, int j) {
   if (i >= numRows() || j >= numRows() ) {
      cout <<"either row i or row j is out of range"<<endl;
      cout <<"Row add not performed"<<endl;
      return false;
   }
   
   for (int k=0; k<Mat[i].size(); k++) {
      Mat[j][k] += Mat[i][k];
   } 
   
   return true;
}

bool Matrix::subRow(int i, int j) {
   if (i >= numRows() || j >= numRows() ) {
      cout <<"either row i or row j is out of range"<<endl;
      cout <<"Row add not performed"<<endl;
      return false;
   }
   
   for (int k=0; k<Mat[i].size(); k++) {
      Mat[j][k] -= Mat[i][k];
   } 
   
   return true;
}

bool Matrix::elimination(vector<double> &multipliers) {
multipliers.clear();
int i=0;
int j= 0;
while (i < numRows() && j < numCols()) {
   double maxVal = Mat[i][j];
   int maxIndex = i;
   
   for (int k=i+1; k < numRows(); k++) {
      double val = Mat[k][j];
      if (fabs(val) > fabs(maxVal) ) {
         maxVal = val;
         maxIndex = k;
      }
   }  
   
   
   if (maxVal != 0) {
      swapRows(i, maxIndex);
      double multiply = 1.0/maxVal;
      multipliers.push_back(multiply);
      rowMult(i, multiply);
      
      vector<double> row = Mat[i];
      for (int k=0; k<row.size(); k++) {
          row[k] *= multiply;
      }
      
      for (int u=0; u<numRows(); u++) {
         if (u != i) {
         vector<double> row = Mat[i];
         for (int k=0; k<row.size(); k++) {
            row[k] *= Mat[u][j];
         }
         for (int k=0; k<Mat[u].size(); k++) {
            Mat[u][k] -= row[k];
         }
         }
      }
      
      i++;
   }   
   j++;
}

}

Matrix &Matrix::invert() {
   Matrix M(this->numRows(), this->numCols()*2);
   for (int i=0; i<this->numRows(); i++) {
      for (int j=0; j<this->numCols(); j++) {
          M[i][j] = this->Mat[i][j];
      }
   }

   for (int i=0; i<this->numCols(); i++) {
      for (int j=this->numCols(); j<M.numCols(); j++) {
          if (j-this->numCols() == i) {
             M[i][j] = 1.0;
          } else {
             M[i][j] = 0.0;
          }
      }
   }

   vector<double> d;
   M.elimination(d);

   Matrix *F = new Matrix(this->numRows(), this->numCols());
   for (int i=0; i<this->numRows(); i++) {
      for (int j=this->numCols(); j<M.numCols(); j++) {
          F->Mat[i][j-this->numCols()] = M[i][j];
      }
   }

 //  cout <<"f is; " << endl;
 //  F->print();

   return *F;
}

bool Matrix::colCenter() {
   //cout <<"Hello column man:  BEFORE"<<endl;
   //print();
   vector<double> colVector(Mat[0].size());
   for (int i=0; i<colVector.size(); i++) {
      colVector[i] = 0.0;
   }

   for (int i=0; i<Mat.size(); i++) {
      for (int j=0; j<Mat[i].size(); j++) {
         colVector[j] += Mat[i][j];
      }
   }

   for (int i=0; i<colVector.size(); i++) {
      colVector[i] /= Mat[0].size();
   }


   for (int i=0; i<Mat.size(); i++) {
      for (int j=0; j<Mat[i].size(); j++) {
         Mat[i][j] /= (colVector[j]);
      }
   }
   //cout <<"After: " << endl;
   //print();
   return true;
}

bool Matrix::colNormalize() {
   vector<double> mag(Mat[0].size());
   //print();
   for (int i=0; i<mag.size(); i++) {
      mag[i] = 0.0;
   }

   for (int i=0; i<Mat.size(); i++) {
      for (int j=0; j<Mat[i].size(); j++) {
         mag[j] += Mat[i][j]*Mat[i][j];
      }
   }

   for (int i=0; i<mag.size(); i++) {
      mag[i] = sqrt(mag[i]);//Mat[0].size();
   }


   for (int i=0; i<Mat.size(); i++) {
      for (int j=0; j<Mat[i].size(); j++) {
         Mat[i][j] /= (mag[j]);
      }
   }
   //print();
return true;
}


