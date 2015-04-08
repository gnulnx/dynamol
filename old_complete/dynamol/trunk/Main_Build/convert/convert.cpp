/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                       
     john.furr@dynamol.com
 ***************************************************************************/
#include "convert.h"

//Dynamol Computational Library Includes
#include "../dynacomp/molecule.h"
#include "../dynacomp/atom.h"
#include "../dynacomp/bond.h"

//Dynamol Type Library Includes
#include "../dynatype/molecule.h"
#include "../dynatype/atom.h"
#include "../dynatype/bond.h"

namespace dt {

convert::convert()
{
}


convert::~convert()
{
}


void convert::toDynatype(dt::molPtr dtMol, dynacomp::molecule *dcMol) {
   // First renumber the molecule in ascending order
   // You will undo this at the end.
   vector<int> numHold;
   for (int i=0; i<dcMol->atoms.size(); i++) {
      numHold.push_back(dcMol->atoms[i]->getNum());
      dcMol->atoms[i]->setNum(i+1);
   }
   dtMol->atoms.clear();
   for (int i=0; i<dcMol->atoms.size(); i++) {
      int num = dcMol->atoms[i]->getNum();
      float *cd = dcMol->atoms[i]->fCoords;
      string sym = dcMol->atoms[i]->getSymbol();
      string newSym = "";
      for (int j=0; j<sym.size(); j++) {
         if (sym[j] != ' ')
            newSym += sym[j];
      }
 
      int AN = dcMol->atoms[i]->getAN();
      atomPtr atm = dtMol->addAtom(num, newSym, cd[0], cd[1], cd[2], AN);
      atm->fragName = dcMol->atoms[i]->fragName;
      atm->charge = dcMol->atoms[i]->getCharge();
   }

   dtMol->bonds.clear();
   for (int i=0; i<dcMol->bonds.size(); i++) {
      dynacomp::bond *bd = dcMol->bonds[i];
      int num = bd->getNum();
      int order = bd->getOrder();
      int fromNum = bd->fromNum();
      int toNum = bd->toNum();
      dtMol->addBond(num, fromNum, toNum, order);
   }
   //Undo the renumbering
   for (int i=0; i<dcMol->atoms.size(); i++) {
      dcMol->atoms[i]->setNum(numHold[i]);
   }
}

void convert::toDynacomp(dynacomp::molecule *dcMol, dt::molPtr dtMol) {
	dcMol->setName( dtMol->name );
	dcMol->atoms.clear();
	vector<int> numHold;
	for (int i=0; i < dtMol->atoms.size(); i++) {
		dt::atomPtr atm = dtMol->atoms[i];
		dynacomp::atom *dcAtom= dcMol->addAtom(dtMol->atoms[i]->getBase());
	    dcAtom->parity = atm->parity;
	}

	dcMol->bonds.clear();
	for (int i=0; i<dtMol->bonds.size(); i++) {
		dt::bondPtr bd = dtMol->bonds[i];
		int num = bd->num;
		int order = bd->order;
		dt::atomPtr frmAtm = bd->from.lock();
		int fromNum = frmAtm->getNum();
		dt::atomPtr toAtm = bd->to.lock();
		int toNum = toAtm->getNum();
		
		//int toNum = bd->toNum();
		dcMol->addBond(num, fromNum, toNum, order);
	}

}

bool convert::update(dynacomp::molecule *dcMol, dt::molPtr dtMol) {
   //Make sure that molecules are the same
   if (dcMol->atoms.size() != dtMol->atoms.size())
      return false;
   if (dcMol->bonds.size() != dtMol->bonds.size())
      return false;

   for (int i=0; i<dtMol->atoms.size(); i++) {
      atomPtr atm = dtMol->atoms[i];
      dynacomp::atom *dcAtm = dcMol->atoms[i];
      float *cd = atm->Coords;

      dcAtm->setFFType( atm->type );
      dcAtm->setCharge(atm->charge);
      dcAtm->fCoords[0] = cd[0];
      dcAtm->fCoords[1] = cd[1];
      dcAtm->fCoords[2] = cd[2];
   }
   return true;
}

};

