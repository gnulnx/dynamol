/***************************************
 *   Copyright (C) 2004 by Dynamol Inc.*
 *   john.furr@dynamol.com             *
 ***************************************/
#ifndef DYNACOMPCOMPUTE_H
#define DYNACOMPCOMPUTE_H

#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;

/** \defgroup Computational
*/

/** \brief 
*
*  \ingroup Computational
*
*  The dynacomp namespace provides a namespace for algorithms of a
*  computational nature.  You will primarily interact with the 
*  Computational module throught the Compute class which will act
*  as a facade for the underlaying algorithms such as Minimization,
*  charges, Flexible alignment, etc.
*/
namespace dynacomp {
class molecule;
/** \brief The Gateway to various computational alorithm
*
*  The compute class acts as a facade for the various computationl
*  algorithms.  Algoithms will inlude Energy elated funtions, and
*  charge related functions.
*  @author john furr.
*/
class Compute{
public:
   Compute();

   ~Compute();

   /** \brief Add charges to the molecule
   *
   *    This function will add charges to a single molecule
   *    If you will be adding charges to more than molecule
   *    you should use the setCharges(vector<molecule *> &mols, string chargeType)
   *    function instread.  It will be faster because you only read the
   *    charge properties from disk one time
   */
   static bool charges(molecule *mol, string chargType);

   /** \brief Compute Charges for molecule
   *
   *   Calculate {chargType} for molecule {mol
   */
   bool Charges(molecule *mol, string chargType);

   /** brief Minimize a molecule 
   *
   *   This function Minimizes a molecule
   */
   bool Minimize(dynacomp::molecule *mol, //Minimize a Molecule
              string method,         //SD=Steepest Descent CG=Conjugate Gradients
              string ffType,         //GAFF or AMBER03
              string chargeType,     //Current, AM1, AM1-BCC, MNDO, PM3, ForceField
              int maxIter=5000,         //The maximum Iterations for minimiation
              float rmsef=0.005,           //The minimum RMSE of the atomic forces before termination
              float maxForce=0.01,        //The maximum allowable atomic force
              float minEDiff=0.01);       //The min chage in energy before termination

  /** Set up the dielectric constant for the calculation */
  int dieSetup(string method, float die);

   /** Add charges to a set of molecules
   *
   *   Like the above function except it adds charges to a groupd of molecules
   */
   static bool charges(vector<molecule *> &mols, vector<string> &chargType);

   /** \brief Compute Potential Energy 
   *
   *   This function computes the potential energy of a molecule
   */
   bool potEnergy(molecule *mol);

   /** \brief Return the error messages 
   *
   *   Each message is seperated by a :
   */
   string getErrorMsg();
private:
   void readChargeFile(string fileName);


   /** \brief Error Message String
   *
   *  each message is seperated by a :
   */
   static string errorMsg;

   float die;
};

}

#endif

