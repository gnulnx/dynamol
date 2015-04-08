/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef BUILDER_H
#define BUILDER_H

#include <qobject.h>
#include <vector>
#include <qstring.h>
using namespace std;
/**
@author jfurr
*/

class molView;
class builderDialog;
class bond;
class atom;
class molecule;

class builder : public QObject
{
Q_OBJECT
public:
    builder(QObject *parent = 0, const char *name = 0);
    ~builder();
     
    void setMolView(molView *viewer);  
    void setDialog(builderDialog *dialog); 
   
    molView *viewer;
    builderDialog *dialog;
    
    atom *prevAtom;
    
    vector<molecule *> frags;
    
    
    void drawMode();
    void sketchMode();
    void ringMode();
    void noMolecule();
    bool wasPrevAtom();
    void addToAtom(atom *atm);
    void addToBond(bond *bd);
    
    /** this function is called when the structure is cleaned.  It makes sure that
    *   Hydrogens have been added, that Carbons don't have 5 bonds, etc..
    */
    bool checkStructure(molecule *mol);
    /** this function check to see if the molecule has hydrogen or not */
    bool hCheck(molecule *mol);
    
    
    /** This function creates a new atom and bonds it to the previously
    *   selected atom.  It then points the prevAtom variable to the
    *   newly created atom
    */
    void createAndBondAtom(QString &sym, int AN, int bOrder);
    
    void reTypeMode();
    void reTypeBond(bond *);
    void reTypeAtom(atom *);
    
    void delMode();
    
    /** This function takes an atom and a bond pointer a arguments
    *   If an atom is selected the pointer will point to the selected
    *   atom.  Likewise for the bond
    *   If no atom or bond is selected then the pointers will be null respectively
    *   DO NOT PASS A POINTER TO A CURRENT ATOM OR BOND
    *   ONLY PASS A NULL POINTER
    */
    void currSelection(atom *&atm, bond *&bd);
    
    /** This function adds an atom in space.  
    *   It is added to the molecule but there is not bond present
    */
    void createLoneAtom(QString sym, int AN);
    
    /** this function bonds to two atoms */
    void bondAtoms(atom *prevAtom, atom *currAtom, int bOrder);
    
    
    /** This function display's an error message if PDB file based structures
    *   are modified
    */
    void pdbError();
    
    /** This function display's an error message when more than one molecule is
    *   present and you are trying to performa a createLoneAtom operation
    */
    void toManyMolError();
    
    /** This error is displayed if the user needs to add hydrogens */
    void hError();
    /** This error is displayed if the user tries to bond atoms between different 
    *   molecules
    */
    void diffMolError();
    
    /** This function maps the dilaog ringId to the position of the correct 
    *   frag as read from the frags/builderFrags.sdf file
    */
    int ringIdToVecPos(int ringId);
    
    /** this function is called when a ring is to be added to a bond */
    void addRingToBond(molecule *ring, bond *currBd);
    
    /** this function is called when a ring is to be added to an atom */
    void addRingToAtom(molecule *ring, atom *currAtom);
    
    /** This function deletes the hydrogens when you are adding a ring to an atom */
    void addToAtomHDel(molecule *ring);
    
    /** This function is used to renumber the ring starting at the highest
    *   number from the molecule it is bonding to
    */
    void renumberRing(molecule *ring, molecule *mol);
    
    /** This function bonds to molecules...atom-to-atom */
    void bondAtomToAtom(molecule *ring, molecule *mol);
    
    /** This function orients an sp2 ring with the new atom */
    void sp2Orient(molecule *ring, atom *currAtom);
    
    /** This function orients an sp3 ring with the new atom */
    void sp3Orient(molecule *ring, atom *currAtom);

    /** This function translates the mol so that it's atm1 is on top of atm2 
    *   This assumes that atm1 and atm2 are from different molecules
    */
    void translate(molecule *mol, atom *atm1, atom *atm2);
    
    /** This function is used to orient the molecule...it is called after the translate
    *   funtion to
    */
    void orient(molecule *mol, atom *atm1, atom *atm2, atom *ringAP);
    
    /** This function gets the ring attach point atom and the ring hydrogen atom
    *   The hydrogen is used to orient the ring
    */
    void getRingAtoms(molecule *ring, atom *&ra, atom *&rh);
    
    /** This function sets the attach point vector and the align point vector */
    void getAttachPoints(atom *currAtom,atom *&alignAtom, vector<float> &atp, vector<float> &alp);
    
    /** This function orients the ring such that ra istranslated to atp and
    *  rh is pointing in the same direction as alp
    */
    void orientRing(molecule *ring, atom *ra, atom *rh, 
                    vector<float> &atp, vector<float> &alp);
                    
    /** This function translates the ring so that ra is at the coords defined by atp */
    void translateRing(molecule *ring, atom *ra, vector<float> &atp);
    
    /** This function combines the two molecules */
    void combineMoleculesAtomAdd(molecule *ring, atom *ra, atom *rh, molecule *mol, atom *currAtom, atom *alignAtom);
    
    void combineMoleculesBondAdd(molecule *ring, atom *ra, atom *rh, molecule *mol, atom *currAtom, atom *alignAtom);
    
   /** this function returns to correct ring atoms for alignment to a bond
   *   The atoms are determined by the order of currBd
   */
   void getRingAtoms(molecule *ring, atom *&ra, atom *&rh, bond *currBd);
    
    /** This funciton is called when you need to dissallow user interaction with
    *   The interface...you implemented it like you did because dialog->setEabled(false)
    *   kept causing unpredictable crashes...probably a QT problem
    */
    void interfaceOff();
    
    /** This function gets the atoms needed to perform the final
    *   rotation for a ringToBond addition
    */
    void getLastRotAtoms(vector<atom *> &angAtoms, atom *rAttach, atom *rAlign, atom *&mid);
    
    /** This function performs the final rotation of ring to bond addition
    */
    void finalRot(molecule *ring, vector<atom *> &angAtoms, atom *rAttach, atom *rAlign, atom *mid);

    /** This function is used to flip a chiral center from R/S */
    void checkChirality();
public slots:
   void processRequest(double x, double y, double z);
   void addH();
   void delH();
   void clean();
   /** This slot is connected to the threadDone signal */
   void interfaceOn();
private:
   vector<float> prevSpot;
   vector<float> currSpot;
   
   bool ENABLE;
   
   void getType(const QString otherType, QString &sym, int &AN);
};

#endif
























