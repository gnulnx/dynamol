/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef SCRIPTATOM_H
#define SCRIPTATOM_H

#include <qobject.h>
#include "scriptobject.h"
#include <qvariant.h>
#include <vector>
using namespace std;

class atom;
/**DETAIL
@author jfurr

The atom classes provides funtion to manipulate the individual atoms in a molecule
*/
class scriptatom : public scriptObject
{
friend  class scriptmolecule;
Q_OBJECT
Q_PROPERTY( double x WRITE setX READ getX )
Q_PROPERTY( double y WRITE setY READ getY )
Q_PROPERTY( double z WRITE setZ READ getZ )

public:
    scriptatom(QObject *parent = 0, const char *name = 0);
    ~scriptatom();
    
    void setAtom(atom *atm);
    
    /** These atoms are actually set when new bonds are added to the molecule 
    *   See the scriptbond  
    */
    vector<scriptatom *> atoms;
      
public slots:
  
   /** \brief Prints the atom name
   *
   *   This function simply prints the name of the atom 
   */
   void printName();

   /** \brief Returns the coords of the atom (by value)
   *   
   *   This function returns the coords by value. It is usually used in conjunction with
   *   setCoords() like:
   *  <pre>
   *  var cd = mol.getCoords();
   *  for (var i=0; i<3; i++) {
   *     cd[i] += {some value}
   *  }
   *  mol.setCoords(cd);
   *  </pre>
   */
   QVariant/*Array*/ getCoords();

   /** \brief Sets the coordinates of the atom
   *
   *   This function sets the coords of the atom.  It is usually used in conjunction
   *   with getCoords() like:
   *   <pre>
   *   var cd = mol.getCoords();
   *   for (var i=0; i<3; i++) {
   *      cd[i] += {some value}
   *   }
   *   mol.setCoords(cd);
   *   </pre>
   */
   void setCoords(QVariant/*Array*/ array);

   /** \brief Set the atoms X coordinate
   * 
   *   This function sets the atoms X coordinate.  X is also a parameter of atom.
   *   Typical usage is:
   *   <pre>
   *   atm.x += 2.0; //add 2 angstroms to the x coordinate 
   *   </pre> 
   */
   void setX( const double &x );
   
   /**  \brief Return the atoms X coordinate 
   *
   *   This function returns the X coorinate.  X is also a parameter of atom.
   *   Typical usage is:
   *   <pre>
   *   var xCoord = atm.x;  
   *   </pre>
   */
   double getX() const;
   
   /** \brief Set the atoms Y coordinate
   * 
   *   This function sets the atoms Y coordinate.  Y is also a parameter of atom.
   *   Typical usage is:
   *   <pre>
   *   atm.y += 2.0; //add 2 angstroms to the Y coordinate 
   *   </pre> 
   */
   void setY( const double &x );
   
   /**  \brief Return the atoms Y coordinate 
   *
   *   This function returns the Y coorinate.  Y is also a parameter of atom.
   *   Typical usage is:
   *   <pre>
   *   var yCoord = atm.y;  
   *   </pre>
   */
   double getY() const;
   
   /** \brief Set the atoms Z coordinate
   * 
   *   This function sets the atoms Z coordinate.  Z is also a parameter of atom.
   *   Typical usage is:
   *   <pre>
   *   atm.z += 2.0; //add 2 angstroms to the Z coordinate 
   *   </pre> 
   */
   void setZ( const double &x );
   
   /**  \brief Return the atoms Z coordinate 
   *
   *   This function returns the Z coorinate.  Z is also a parameter of atom.
   *   Typical usage is:
   *   <pre>
   *   var zCoord = atm.z;  
   *   </pre>
   */
   double getZ() const;
  
    /** \brief Returns the atomic number 
    *
    *   This function return the atomic number of the atom 
    */
   int atomicNum();
 
   /**  \brief Returns the atomic symbol 
   *   
   *   This function returns the atomic symbol.  Not the force field type. 
   */
   QString getSym();
   
   /** \brief returns the force field atom type
   *  
   *   This function returns the ff_type.  Not the atomic symbol 
   */
   QString getType();
   
   /** \brief This function returns the atoms atomic mass 
   *
   *   This function returns the atoms atomic mass
   */
   double getMass();
  
   /** \brief Set the atoms charge
   *
   *   This function sets the atoms partial charge
   */
   void setCharge(double charge);

   /** \brief  Returns true if the atom is selected 
   *
   *   True is returned is atom is selected and false otherwise.
   */
   bool isSelected();
 
   /** \brief Returns the atoms partial charge
   *
   *   This function returns the atoms parial charge.  Note you must set the partial 
   *   charges. This is usually done with molecule::setCharges() like:
   *   <pre>
   *   mol.setCharges("AM1-BCC");
   *   </pre> 
   */
   double getPartialCharge();
   
   /** \brief Returns the formal charge 
   *   
   *   This function returns the atoms formal charge 
   */
   int getFormalCharge();
   
   /** \brief Sets the atoms formal charge
   *
   *   This function sets the atoms formal charge 
   */
   void setFormalCharge(int formalCharge);
   
   /** Depricated function.  Use numOfAtoms()
   *  
   *   This function returns the number of bonded atoms.  The function is desprecated 
   *   and you should only use numOfAtoms(). 
   */
   int getAtomsSize();

   /** \brief Returns the number of bonded atoms 
   * 
   *   This function returns the number of bonded atoms.  Typical usage is:
   *   <pre>
   *   var atm = mol.getAtom(0); //or some other number in the range 0 to mol.numOfAtoms()
   *   for (var i=0; i<atm.numOfAtoms(); i++) {
   *      var bondedAtm = atm.getAtom(i);
   *      do something cool with th ebonded atom 
   *   }
   *   </pre>
   *  You should use this one function as opposed to the getAtoms.size()
   */
   int numOfAtoms();
   
   /** \brief Returns the bonded atom specified by index
   *
   *   This function returns the bonded atom number specified by index. Typdal usage is
   *   in conjunction with numOfAtoms() like:
   *   <pre>
   *   var atm = mol.getAtom(0); //or some other number in the range 0 to mol.numOfAtoms()
   *   for (var i=0; i<atm.numOfAtoms(); i++) {
   *      var bondedAtm = atm.getAtom(i);
   *      do something cool with th ebonded atom 
   *   }
   *   </pre>
   */
   scriptatom *getAtom(int index);
   
   /** \brief Returns the atoms number
   *
   *   This function returns the atom number (Not the atomic number) 
   */
   int getNum();
   
   /** \brief Returns the vertex degree of the atom
   *
   *    This funtion returns the vertex degree of the atom.  The vertex
   *    degree is defined as number of sigma electrons minus the 
   *    number of hydrogens in the atom.  Basically it is a count of
   *    the number of heavy atoms bonded to the the atom.  Hydrogen atoms
   *    will return a vertex degree of 0
   */
   int vertexDegree();
   
   /** \brief Returns the valence vertex degree of the atom
   *
   *    This function returns the valence vertex degree (vvd) of the atom.
   *    The vvd is defined as
   *    <pre>
   *    vvd = (Zv - H) / (Z - Zv - 1)
   *     
   *     Z  = Atomic Number
   *     Zv = Number of valence electrons
   *     H  = Number of hydrogens
   *     </pre>
   */
   int valenceVertexDegree();
   
   /** \brief Returns the number of valence electrons
   *
   *    This function returns the number of valence electrons on the atom
   */
   int valenceCount();
   
   /** \brief Returns the number of bonded hydrogen atoms
   * 
   *    Simply returns a count of the bonded hydrogen atoms
   */
   int hydrogenCount();
   
   /** \brief Returns the principle quantum number of the atom
   *
   *   This function returns the principle quantum number of the atom
   */
   int pQN();

   /** \brief Return the Partial Charge 
   *
   *   This function returns the partial charge of the atom
   */
   double getCharge();
   
protected:
   atom *atm;
   QString code;
};

#endif





































