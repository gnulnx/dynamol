/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "moladapter.h"

//dynamol includes
#include "molecule.h"
#include "fragment.h"
#include "atom.h"
#include "bond.h"

//dynatype includes
#include "../dynatype/molecule.h"
#include "../dynatype/atom.h"
#include "../dynatype/bond.h"

//Dynacomp Includes
#include "../dynacomp/molecule.h"
#include "../dynacomp/atom.h"
#include "../dynacomp/bond.h"

#include <iostream>
#include <map>
using namespace std;

molAdapter::molAdapter()
{
}

molAdapter::~molAdapter()
{ 
}

/** This is a simple function that converts a molecule to a dt::molecule */
void molAdapter::mol2molecule(dt::molPtr dtmol, molecule *mol) {
   //Define the molecule that will be returned
   dtmol->name = mol->getName();
   dtmol->atoms.clear();
   vector<int> atomNums;
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      atomNums.push_back(atm->getNum());
      atm->setNum(i+1);
   }   
   
   //copy the atom structure from molecule to molecule
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      int num = atm->getNum();
      float *cd = atm->get_fCoords();
      string sym;
      for (int i=0; i<atm->getSym().length(); i++) {
         if (atm->getSym()[i] != ' ') {
	    sym.push_back(atm->getSym()[i]);
	 }
      }

      int AN = atm->getAtomicNum();

      //Now lets add the new atom to dtmol
      dt::atomPtr dtatm = dtmol->addAtom(num, sym, cd[0], cd[1], cd[2], AN);

      dtatm->charge = atm->getCharge();
      
      if (mol->rtti() >= 12) {
         molecule *p1 = dynamic_cast<molecule *>(atm->getParent());
	 typeFrag(p1);
	 dtatm->fragName = p1->getName();
	 
	 molecule *p2 = dynamic_cast<molecule *>(p1->getParent());
	 if (p2) {
	   dtatm->chainName = p2->getName();
	 }
      }
   }
   dtmol->bonds.clear();
   //Copy the bond data from molecule to molecule
   for (int i=0; i<mol->bonds.size(); i++) {
      bond *bd = mol->bonds[i];
      int num = bd->getNum();
      int order = bd->getOrder();
      int fromNum = bd->fromNum();
      int toNum = bd->toNum();
      dtmol->addBond(num, fromNum, toNum, order);
   }

   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      atm->setNum(atomNums[i]);
   }
}

void molAdapter::molList2dynacompList(std::vector<dynacomp::molecule *> &dcVec, std::list<molecule *> &molList) {
   std::list<molecule *>::iterator it = molList.begin();
   for (it; it != molList.end(); it++) {
      molecule *mol = *it;
      dynacomp::molecule *dcMol = new dynacomp::molecule;
      mol2dynacomp(dcMol, mol);
      dcVec.push_back(dcMol);
   }
}


void molAdapter::mol2dynacomp(dynacomp::molecule *dcMol, molecule *mol) {
   typeFrag(mol);
   dynacomp::molecule testMol;
   dcMol->setName( mol->getName() );
   dcMol->atoms.clear();
   vector<int> numHold;
   for (int i=0; i < mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      numHold.push_back(atm->getNum());
      atm->setNum(i+1);
      dynacomp::atom *dcatm = dcMol->addAtom(mol->atoms[i]->getBase());
      if (mol->rtti() >= 12) {
         molecule *p1 = dynamic_cast<molecule *>(atm->getParent());
         typeFrag(p1);
         dcatm->fragName = p1->getName();
      }
   }

   dcMol->bonds.clear();
   for (int i=0; i<mol->bonds.size(); i++) {
      bond *bd = mol->bonds[i];
      int num = bd->getNum();
      int order = bd->getOrder();
      int fromNum = bd->fromNum();
      int toNum = bd->toNum();
      dcMol->addBond(num, fromNum, toNum, order);
   }

   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      atm->setNum(numHold[i]);
   }
   
   dcMol->chargeType = mol->chargeType;
   
}

void molAdapter::dynacomp2molecule(molecule *mol, dynacomp::molecule *dcMol)
{
	cout<<"molAdapter::dynacomp2molecule"<<endl;
	mol->setName( dcMol->getName() );
	for (int i=0; i<dcMol->atoms.size(); i++) {
		dynacomp::atom *dcAtm = dcMol->atoms[i];
		atom *tmp = mol->addAtom(dcAtm->getBase());
//		tmp->setCharge( dcAtm->getCharge() );
//		tmp->setFFType( dcAtm->getFFType );
	}

	for (int i=0; i<dcMol->bonds.size(); i++) {
		dynacomp::bond *dcBd = dcMol->bonds[i];
		mol->addBond(dcBd->getNum(), dcBd->fromNum(), dcBd->toNum(), dcBd->getOrder() );
	}
						

}

void molAdapter::dynacomp2mol(molecule *mol, dynacomp::molecule *dcMol)
{
   for (int i=0; i < dcMol->atoms.size(); i++) {
      float chg = dcMol->atoms[i]->getCharge();      
      mol->atoms[i]->setCharge(chg);
   }
   mol->chargeType = dcMol->chargeType;
}
    
/** This function converts a molecule to a mol */
//molecule *molAdapter::molecule2mol(dt::molecule *dtmol) {
molecule *molAdapter::molecule2mol(dt::molPtr dtmol) {
   molecule *mol = new molecule;
   for (int i=0; i< dtmol->atoms.size(); i++) {
      //dt::atom *dtatm = dtmol->atoms[i];
      dt::atomPtr dtatm = dtmol->atoms[i];
      int num = dtatm->getNum();
      float *cd = dtatm->Coords;
      int AN = dtatm->getAN();
      string sym = dtatm->getSymbol();
      atom *atm = mol->addAtom(num, sym, cd[0], cd[1], cd[2], AN);
      atm->setCharge( dtatm->charge );
      atm->setFFType( dtatm->type );
   } 
   return NULL;
}

//bool molAdapter::update(molecule *&mol, dt::molecule *dtmol) {
bool molAdapter::update(molecule *&mol, dt::molPtr dtmol) {
   if (!mol) {
      exit(0);
   }
   //Make sure that molecules are the same
   if (mol->atoms.size() != dtmol->atoms.size()) 
      return false;
   if (mol->bonds.size() != dtmol->bonds.size())
	return false;

   // First lets update the atoms
   //   I think this might be all that is required
   //

   for (int i=0; i<dtmol->atoms.size(); i++) {
      //dt::atom *dtatm = dtmol->atoms[i];
      dt::atomPtr dtatm = dtmol->atoms[i];
      atom *atm = mol->atoms[i];
      float *dcd = dtatm->Coords;    

      atm->setFFType( dtatm->type );
      //atm->setCharge( dtatm->charge );
      //atm->get_fCoords()[0] = dcd[0];
      //atm->get_fCoords()[1] = dcd[1];
      //atm->get_fCoords()[2] = dcd[2];
   }

   // This section copies the properties from the dtmol to the mol
   //   Both classes should always be using the map<QString, QString> propMap
   //
   map<string, string>::iterator mi = dtmol->propMap.begin();
   for (mi; mi != dtmol->propMap.end(); mi++) {
      mol->propMap[mi->first] = mi->second;
   }

}

void molAdapter::typeFrag(molecule *frag) { 
   string name = frag->getName();
   if (name == "ASP") {
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         if (atm->getAtomicNum() == 1) {
            if (atm->atoms[0]->getAtomicNum() == 8) {
               frag->setName("ASP_N");
               return;
            }
         }
      }
   }
   
   
   if (name == "GLU") {
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         if (atm->getAtomicNum() == 1) {
            if (atm->atoms[0]->getAtomicNum() == 8) {
               frag->setName("GLU_N");
               return;
            }
         }
      }
   }
   
   //Check for degenerate cases
   if (name == "ASN") {
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         if (atm->getSym() == "OD2") {
            frag->setName("ASP");
            typeFrag(frag);
         }
      }
   }
   
   if (name == "HIS" || name =="HIS_P" || name == "HIS_D" || name == "HIS_E") {
      bool delta = false;
      bool epsilon = false;
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         if (atm->getAtomicNum() ==1 && atm->atoms[0]->getSym() == "ND1") delta = true;
         if (atm->getAtomicNum() ==1 && atm->atoms[0]->getSym() == "NE2") epsilon = true;      
      }
      if (delta && epsilon) frag->setName("HIS_P");
      if (delta && !epsilon) frag->setName("HIS_D");
      if (!delta && epsilon) frag->setName("HIS_E");   

   }
   string name2 = frag->getName();
   if (name != name2 ) {
   }

   /** This section renames nTerminal and cTerminal amino acides
   */
   if (frag->rtti() == 12) {
      //fragment *f = dynamic_cast<fragment *>(frag);
      fragment *f = dynamic_cast<fragment *>(frag);
      if (f->nTer && name[0] != 'n') {
         string newName = "n" + name;
         frag->setName(newName);
      }
      if(f->cTer && name[0] != 'c') {
         string newName = "c" + name;
         frag->setName(newName);
      }
   }
}











