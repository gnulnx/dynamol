/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SCRIPTMOLECULE_H
#define SCRIPTMOLECULE_H

#include <qobject.h>

#include "scriptobject.h"

#include <vector>
using namespace std;


class molView;
class molecule;
class XmodelView;
class scriptatom;
class scriptbond;
class energy;
class energyThread;

/**DETAIL
@author Dynamol Inc.

The molecule class is probably the most fundamental class in Dynamo scripting langauge.
This class provides many useful function for interacting with molecules
*/
class scriptmolecule : public scriptObject
{
friend class scriptatomtyper;
Q_OBJECT
public:
    scriptmolecule(QObject *parent = 0, const char *name = 0);
    scriptmolecule(molecule *, QObject *parent = 0, const char *name = 0);

    ~scriptmolecule();
    
    //void setMolecule(molecule *mol);
   	
    molecule *mol;
    bool fromMolView;

    /* this variable is used to determine if the molecule has been added to the list view || not */
    bool inListView;
public slots:
   
   /** \brief Prints the molecule name 
   *
   * This function simply prints the name of the molecule to the std output 
   */
   void printName();
   
   
   /** \brief Use this function to manipulate atoms in the molecule
   *
   *   This function returns atom number 'num'.  Typical usage would 
   *   be in conjunction with numOfAtoms() like:
   *   <pre>
   *   for (var i=0; i < mol.numOfAtoms(); i++) {
   *      var atm = mol.getAtom(i); 
   *      ...do something with atm 
   *   } 
   *  </pre>
   */ 
   scriptatom *getAtom(int num);
   
   /** \brief Use this function to manipulate bonds in the molecule
   *   
   *   This function returns bond number 'num'  Typical usage would 
   *   be in conjunction with numOfBonds() like:
   *   <pre>
   *   for (var i=0; i<mol.numOfBonds(); i++) {
   *      var bd = mol.getBond(i);
   *      ...do someting with bd
   *   }
   *   </pre>
   */
   scriptbond *getBond(int num);
   
   /** \brief Returns the number of atoms in the molecule 
   *
   *   This function returns the total number of atoms in the molecule 
   *   Usage might be in conjunction with getAtom() like:
   *   <pre>
   *   for (var i=0; i<mol.numOfAtoms(); i++) {
   *      var atm = mol.getAtom(i);
   *      ...do something with atm
   *   }
   *   </pre>
   */
   int numOfAtoms();
   
   /** \brief Returns the number of bonds in the molecule 
   *  
   *  This function return the total number of bonds in the molecule.   
   *  Typical Usage might be in conjunction with getBond() like:
   *   <pre>
   *   for (var i=0; i<mol.numOfBonds(); i++) {
   *      var bd = mol.getBond(i);
   *      ...do someting with bd
   *   }
   *   </pre>
   */
   int numOfBonds();
   
   /** \brief Add Charges to the molecule 
   *   
   *  This function adds charges to the molecule.  Currently the supported charge 'types' are:
   *  <ol>
   *  <li>AM1</li>
   *  <li>AM1-BCC</li>
   *  <li>MNDO</li>
   *  <li>AMBER</li>
   *  </ol> 
   *
   *  Example usage:  
   *  <pre>
   *  mol.addCharges("AM1-BCC");
   *  </pre>
   */    
    void addCharges(QString type);
    
    /** \brief Returns the molecular mechanics energy 
    *
    *    Small molecule energies are calculated with the gaff forcefield  and
    *    protein's are calculated with the Amber 2003 force field
    */
    double potE();
    
    /** \brief Store a property/value pair.  
    *
    *   Property/value pairs are used to store various properties about the molecule. 
    *   These property values will be written if you write an SD file.  Also if a property
    *   with the name 'name' already exists then the value 'value' will be over written.
    *   Typical usage woule include:
    *   <pre>
    *   var name = "logP";
    *   var value = 6.5;
    *   mol.addPropValuePair(name, value);
    *   </pre>
    *   See also getValue() and getProp()
    */
    void addPropValuePair(QString Name, QString Value, QString propType = "s");
    
    /** \brief Returns the value associated with the propery name
    *
    *    This function returns the value of  property 'name'.  If no such 
    *    property exists then 'none' is returned.  Usage:
    *    <pre>
    *    var logP = mol.getValue("logP");
    *    if (logP != "none") {
    *       do something cool
    *    }
    *    </pre>
    */
    QString getPropValue(QString propName);
    
    /**
    *
    */
    QString getPropType(QString propName);
   
    /** \brief Returns the number of properties associated with the molecule
    *   
    *   This function returns the number of property/value pairs that are 
    *   associated with this molecule
    */ 
    int numOfProperties();
    
    /** \brief Peform a quick minimization of the molecule. 
    *   
    *   This function performs a quick min on the molecule.  Usage is not recommended
    *   as this function will probably be replaced.
    */
    double quickMin();
    
    /** \brief Add hydrogens to the molecule
    *   
    *   This function adds hydrogens to the molecule. 
    *   Hydrogens positions are not optimized.  Typical usage:
    *   <pre>
    *   mol.addHyd();
    *   </pre>
    */    
    void addHyd();
    
    /** \brief Returns the name of the molecule as a string 
    * 
    *    Usage:
    *    <pre>
    *    var molName = mol.getName();
    *    </pre>
    */
    QString getName();
    
    /** \brief Used to Change the name of the molecule 
    *  
    *   This function sets the molecule name.  Use it if you would like to 
    *   change the molecules name.  Usage:
    *   <pre>
    *   var name = "MOL_ID_1290";
    *   mol.setName(name);
    *   mol.setName("MOL_ID");
    *   </pre>
    */
    void setName(QString name);
   
   /** \brief Make a copy of the molecule 
   * 
   *   This function makes a copy of the current molecule. Typical usage would be:
   *   <pre>
   *   var newMol = currMol.copy()
   *   <pre>
   */

   scriptmolecule *copy();
 
  /** \brief Returns the molecular weight 
  *
  *   Return the molecular weight
  */ 
  double molWeight();
private:
   energy *Energy;    
   energyThread *et;

protected:
   vector<scriptatom *> atoms;
   vector<scriptbond *> bonds;
};

#endif





































