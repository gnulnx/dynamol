/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef SCRIPTSELECT_H
#define SCRIPTSELECT_H

#include <qobject.h>
#include "scriptobject.h"
#include <vector>
#include <list>
#include <string>
#include <iostream>

using namespace std;

class molView;
class scriptmolecule;
class XmodelView;
class scriptmollist;

/**DETAIL
@author jfurr

The select class provides a set of functions for selecting groups of atoms
in the molView window
*/
//class scriptselect : public QObject
class scriptselect : public scriptObject
{
Q_OBJECT
public:
    scriptselect(QObject *parent = 0, const char *name = 0);

    ~scriptselect();
    
    //void setmolView(molView *viewer);
    //void setXmodelView(XmodelView *viewer);
   
public slots:
    /**  \brief Clear selection
    *
    *   Clear the entire selection buffer
    *   
    *    typeical usage:
    *    <pre>
    *    select.clear();
    *    </pre>
    */
    void clear();
    
    /**  \brief Select all atoms.
    *
    *   Select all atoms in the molView
    *   
    *    typeical usage:
    *    <pre>
    *    select.clear();
    *    </pre>
    */
    void all();
    
    /**  \brief Select all atoms of a specific type
    *
    *   Select all atoms of a specific type in the molView
    *   
    *    typeical usage:
    *    <pre>
    *    select.all('C'); //selects all carbon atoms
    *    select.all('N'); //select all nitrogen atoms
    *    </pre>
    *
    *   see all select.atomType(string)
    */
    void all(QString type);
    
   /**  \brief Invert the current select
    *
    *   Selects all unselected atoms and deselects all selected atoms
    *   
    *    typeical usage:
    *    <pre>
    *    select.invert();
    *    </pre>
    */
    void invert();
    
    /**  \brief Select protein residue number
    *
    *   Only valid if a PDB file is loaded.
    *   
    *    typeical usage:
    *    <pre>
    *    select.resNum(198);
    *    </pre>
    */
    void resNum(int num);
    
    /**  \brief Like above funtion with chain option
    *
    *    Only valid if a PDB file is loaded.
    *   
    *    typeical usage:
    *    <pre>
    *    select.resNum(198, 1);  select residue number 198 in chain 1.
    *    </pre>
    */
    void resNum(int num, QString chainName);
    
    /** \brief Select all resides of a certain type
    *
    *    This function selects all residues of type 'resType'.  
    *    Restype should be one of the three letter residue identifeis 
    *    in all caps.  For instance "ARG", "LYS", "ALA" 
    *
    *   Typical usage:
    *   <pre>
    *   select.resType("ALA"); //select all alanine residues
    *   </pre>
    */
    void resType(QString resType);
    
    /** \brief Select all resides of a certain type with chain option
    *
    *    This function selects all residues of type 'resType'.  
    *    Restype should be one of the three letter residue identifeis 
    *    in all caps.  For instance "ARG", "LYS", "ALA" 
    *
    *   Typical usage:
    *   <pre>
    *   select.resType("ALA", 1); //select all alanine residues in chain 1
    *   </pre>
    */
    void resType(QString resType, QString chainName);
    
    /** \brief Select atom number <i> num </i>
    *
    *    Select the specified atom number
    *
    *   Typical usage:
    *   <pre>
    *   select.atomNum(10); //atom number 10 is now highlighted
    *   </pre>
    */
    void atomNum(int num);
    
    /**  \brief Select all atoms of a specific type
    *
    *   Select all atoms of a specific type in the molView.
    *   This function is justlike select.all(string)
    *   
    *    typeical usage:
    *    <pre>
    *    select.atomType('C'); //selects all carbon atoms
    *    select.atomType('N'); //select all nitrogen atoms
    *    </pre>
    *
    *   see all select.all(string)
    */
    void atomType(QString type);
    
    /**  \brief Select the molecule
    *
    *   Selects the molecule specified by <i> mol </i> if it is 
    *   present in the molView
    *   
    *    typeical usage:
    *    <pre>
    *    var mol = molList.getMol(0);
    *    select.mol( mol );  
    *    </pre>
    *
    *   see all select.all(string)
    */
    void mol(scriptmolecule *mol);
    
    /** \brief select atoms within a specied distance of those already selected
    *
    *    This function selects atoms with 'dist' angstroms of 
    *    the selected atoms 
    *  
    *    Typical usage:
    *    <pre>
    *    select.with(5.0); //select atoms within 5.0 angstrons of those currently selected
    *    </pre>
    */
    void within(float dist);
    
    /** \brief select atoms within a specied distance of those already selected
     *
     *    This function selects atoms with 'dist' angstroms of
     *    the molecule <i> mol </i>
     *
     *    Typical usage:
     *    <pre>
     *    select.with(5.0, mol); //select atoms within 5.0 angstrons of those currently selected
     *    </pre>
     */
    void within(float dist, scriptmolecule *mol);
    
    /** \brief Select and return the molecule defined by 'molname' 
     *
     *  Selects the molecule with name <i> name </i> if it is present in the molView.
     *  If it is present it returns the molecule.
     *
     *  Typical usage:
     *  <pre>
     *  select.mol("cyclosporin");
     *  </pre>
     */ 
    scriptmolecule *mol(QString molName);
    
     /** \brief Select and return all molecules in the molView
      *
      * This function is much like molView.getMols();
      *
      * Typical usage:
      * <pre>
      * var molList = select.current()
      * </pre>
      */
     scriptmollist *current();

private:
    //molView *molview;
    //XmodelView *viewer;

};

#endif





































