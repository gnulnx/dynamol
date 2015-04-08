/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;
/**
@author John Furr
*/

/** \brief A Matrix class
*
*   The matrix class is a row oriented matrix class.
*   By row oriented I mean a Matrix defined as A[i][j] would
*   have i row and j collums.  This definition was most compatible 
*   with linear algebra methods.
*/
class Matrix{
public:
   /** \brief Default Matrix Constructor
   *
   *    Matrix will be initialized with 1 row and 1 col.  The value
   *    will be initialized to 1
   */
   Matrix();
    
    /** \brief Constructer that initializes Matrix size
    *
    *    Use the constructor when you want to initialize the size
    *    of the Matrix.  All Matrix elements will be initialized to 
    *    a value of 1.
    */
    Matrix(int rows, int cols);

    /** \brief Matrix Destructor
    *
    *    Not much to say about the destructor at this time
    */
    ~Matrix();
    
    /** \brief Matrix Copy
    *
    *   Set 1 matrix equal to another
    *   <pre>
    *   Mat A;
    *   Mat B = A;
    *   </pre>
    */
    Matrix &operator=(const Matrix &M);
    
    
    /**  \brief Access element (i,j) 
    *
    *    Random access of Matrix element 
    *    (i, j) where i is the row
    *    number and j is the col number 
    *    Use this function to set/get
    *    individual Matrix elemets
    *    <pre>
    *    Matrix A(4, 4); //Initalize a 4X4 matrix
    *    for (int i=0; i<4; i++) {
    *       for(int j=0; j<4; j++) {
    *           A[i][j] = i*j;
    *       }
    *    }
    *    </pre>
    */
    vector<double> &operator[](int i);
    
    
    /**  \brief Matrix Size test
    *
    *     Returns true if the number of rows and colums 
    *     are the same for both matrices
    */
    bool operator&( Matrix &M );
    
    /** \brief Add two Matrices and store result in C
    *
    *   Assuming two Matrices <i> A </i> and <i> B </i>
    *   are the same size this function will return the
    *   sum of the two matrices as C
    *   <pre>
    *   Matrix A, B;
    *   ...some matrix code
    *   Matrix C = A + B;
    *   </pre>
    */
    Matrix &operator+( Matrix &M );
    
    /** \brief Increment Matrix A be Matrix B
    *
    *    Assuming two Matrices <i> A </i> and <i> B </i>
    *    are the same size this function will store result
    *    of the Matrix addition in Matrix A.  Function returns false 
    *    if operation cannot be performed.  True otherwise
    *    <pre>
    *    Matrix A, B;
    *    ...some matrix code
    *    A += B;
    *    </pre>
    *    Matrix A is now equal to A(orig) + B
    */
    bool operator+=( Matrix &M );
    
    /** \brief Subtract two Matrices and store result in C
    *
    *   Assuming two Matrices <i> A </i> and <i> B </i>
    *   are the same size this function will return the
    *   subtraction of the two matrices as C
    *   <pre>
    *   Matrix A, B;
    *   ...some matrix code
    *   Matrix C = A - B;
    *   </pre>
    */
    Matrix &operator-( Matrix &M );
    
    /** \brief Increment Matrix A be Matrix B
    *
    *    Assuming two Matrices <i> A </i> and <i> B </i>
    *    are the same size this function will store result
    *    of the Matrix subtraction in Matrix A.  Function returns false 
    *    if operation cannot be performed.  True otherwise
    *    <pre>
    *    Matrix A, B;
    *    ...some matrix code
    *    A -= B;
    *    </pre>
    *    Matrix A is now equal to A(orig) + B
    */
    bool operator-=( Matrix &M );
    
    
    /** \brief Multiply two Matrices (A X B) and store result in C
    *
    *   Assuming that matrix A has the same number of collums
    *   as Matrix B has rows then Matrix multiplication is caried
    *   out like:  C = A X B
    *   
    *   In the event that the matrices cannot be multiplied a matrix
    *   of size (1,1) with element value equal to 1 is returned
    *
    *   <pre>
    *   Matrix A, B;
    *   ...some matrix code
    *   Matrix C = A * B;
    *   </pre>
    */
    Matrix &operator*( Matrix &M );
    
    /** \brief Multiply two Matrices (A X B) and store result in A
    *
    *   Assuming that matrix A has the same number of collums
    *   as Matrix B has rows then Matrix multiplication is caried
    *   out like:  A = A X B
    *   
    *   In the event that the matrices cannot be multiplied false is returned
    *   If the operation is succeful then true is returned
    *   <pre>
    *   Matrix A, B;
    *   ...some matrix code
    *   A *= B;
    *   </pre>
    */
    bool operator*=( Matrix &M );
     
    /** \brief Transpose the Matrix
    *
    *    To transpose a mtrix means to make the rows cols and 
    *    the cols rows. 
    */
    Matrix &transpose();
   
    /** \brief Swap row i with row j
    *
    *    This is one of the three basic matrix operations
    *    It is used during Matrix elimination.  If either 
    *    i or j is greater than the number of rows false
    *    will be returned and now swap will be performed.
    *    if the swap is performed then true is returned.
    */
    bool swapRows(int i, int j);
    
    /** \brief Row multiplication
    *
    *    This is one of the three basic matrix operations.
    *    It is used during matrix elimination.  Value must be non
    *    zero in order to be a valid row multiplication.
    *    The function returns true on success and false otherwise
    */
    bool rowMult( int row, double value );
    
    /** \brief Add row i to row j
    *
    *    his is one of the three basic matrix operations.
    *    It is used during matrix elimination.  i and j must
    *    be valid matrix rows.  Row i is added to row j.  True
    *    is returned on success and false otherwise
    */
    bool addRow(int i, int j);
    
    /** \brief Subtract row i to row j
    *
    *    This is one of the three basic matrix operations.
    *    It is used during matrix elimination.  i and j must
    *    be valid matrix rows.  Row i is added to row j.  True
    *    is returned on success and false otherwise
    */
    bool subRow(int i, int j);
    
    /** \brief Return the number of rows
    * 
    *    Returns the number of rows in the matrix
    */
    int numRows();
    
    /** \brief Return the number of Columns
    * 
    *    Returns the number of Colums in the matrix
    */
    int numCols();
    
    /** \brief Print the Matrix to Standard Out
    * 
    *    Print the Matrix to Standard Outx
    */
    void print();
    
    /** \brief Resize the Matrix
    *
    *    This function resizes the Matrix to i rows and j colums
    *    All new elemets are initialized to 1.0.  You are not allowed
    *    to resize a Matrices row or collums to a size of 0 or less.
    *    This function returns true if the matrix was correctly resized 
    *    and false otherwise.
    */
    bool resize(int i, int j);
    
    /** \brief Matrix Elimination
    *
    *    Perform Matrix elimination.
    *    Takes a vector of doubles as an argument.  The values
    *    will be filled with the multipliers used while 
    *    eliminating the matrix.  The multipliers are used
    *    during the LU decomposition for matrix inversion
    */
    bool elimination(vector<double> &multipliers);
    
    /** \brief Invert the Matrix
    *
    *    This functions uses the LU decomposition method
    *    to invert the Matrix.  The inverted Matrix is returned 
    *    and the current Matrix is unchanged
    */
    Matrix &invert(); 
   
   /** \brief Column Center the Matrix
   *
   *   This function Column Centers the matrix by subracting the mean of eac columns
   *   from that columns elements
   */
   bool colCenter(); 

   /** \brief Normalize the Matrix
   *
   *    This function normalizes the matrix columns
   */
   bool colNormalize();
public:
   /** \brief Matrix is represented as a vector of vectors 
   *
   *   By using vectors many tasks were made trivial.
   *   All matrix values are treated as double precision
   *   floating point numbers
   */
   vector< vector< double > > Mat;

};

#endif
