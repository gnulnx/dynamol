/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef REGRESS_H
#define REGRESS_H

#include "matrix.h"
/**
@author John Furr
*/

/** \brief This class performs a multiple linear regression
*/
class Regress{
public:
    Regress();

    ~Regress();

    /** \brief Multiple Linear Regress
    *
    *    This function performs a multi linear regression
    */
    void MR(Matrix &Y, Matrix &X);

    /** \brief PLS Perform a partial least squares regression
    *
    *    This function performs a PLS regression
    */
    void PLS(Matrix &Y, Matrix &X);    
public:

   /** \brief The Y predictions
   *    
   *    These are the Y predictions for the Model
   *    Ypred is calculated by:
   *    <pre>
   *    Ypred = Xb;
   *    </pre>
   */
   Matrix Ypred;
   
   /** \brief The Y collums averages
   *
   *   These are the Y collum averages.  For a single Y variable
   *   The Matrix will be 1 X 1.  For two Y variables
   *   the matrix will be 1 X 2
   */
   Matrix Yavg;
   
   /** \brief The Y collumn Totals
   *
   *   These are the Y collum totals
   */
   Matrix Ytotal;
   
   /** \brief The model residuals
   *
   *    These are the model residuals
   *    Residuals are calculate by:
   *    <pre>
   *    residuals = Ypred - Y;
   *    </pre>
   */
   Matrix residuals;
   
   /** \brief The predicted Beta's
   *
   *    These are the predicted Beta's from a MR run
   */
   Matrix b;

   /** \brief Squared Sum of Errors
   *
   *   This is the squared sum of the errors
   */
   Matrix SSE;

   /** \brief Square of the Multiple Correlation Coefficient
   *
   *    This is the r^2 value
   */
   Matrix R2;
};

#endif
