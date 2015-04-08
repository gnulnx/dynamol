/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc                                     *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "addh.h" 
#include "forcefield.h"
#include "energy.h"

#include "xmodelview.h"
#include "molchangeevent.h"
#include "qsemaphore.h"
#include "atomtyper.h"
#include "linAlg.h"
#include "trashcan.h"
#include <qfile.h>
#include "molview.h"
#include "qapplication.h"

#include "atom.h"
#include "bond.h"
#include "molecule.h"
#include "fragment.h"
#include "chain.h"
#include "angle.h"
#include "torsion.h"

#include "moladapter.h"

//Dynamol Compuational Library Includes
#include "../dynacomp/forcefield.h"
#include "../dynacomp/energy.h"
#include "../dynacomp/molecule.h"
#include "../dynacomp/atom.h"
#include "../dynacomp/bond.h"
#include "../dynacomp/angle.h"
#include "../dynacomp/torsion.h"

addH::addH()
 : dynoThread(NULL)
{
   noOptimize = false;
   view = NULL;
   wait_sem = NULL;
}

void addH::setNoOptimze(bool opt) {noOptimize = opt;}

addH::~addH()
{
}

//void addH::setUp(molListView *listView, QString optimiztion, list<molecule *> &molList){
void addH::setUp(QSemaphore *wait_sem, XmodelView *view, QString optimiztion, list<molecule *> &molList){
   this->molList = molList;
   optimization = optimization;
   this->view = view;
   
   this->wait_sem = wait_sem;
   
}

void addH::stopThread() {stop = true;}
void addH::run() {
   //update->wait();
   QMutex mutex;
   QMutexLocker locker(&mutex);
   setName("addH"); 
   molecule *mol;
   
   list<molecule *>::iterator molIterator;
   for (molIterator = molList.begin(); molIterator != molList.end(); molIterator++) {
       mol=*molIterator;
       vector<atom *> newAtoms;
       addHydrogens(mol, newAtoms); 
       mol->updateValence();       
   }
   molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1002), wait_sem);
   e->postEvent();
   delete wait_sem;
   emit threadDone();
}   




void  addH::checkBondOrder(molecule *mol) {
    for (int i=0; i<mol->bonds.size(); i++) {
      bond *bd = mol->bonds[i];
      atom *atm1 = bd->from;
      atom *atm2 = bd->to;
      atom *tmp1, *tmp2;
      tmp1 = tmp2 = NULL;

      float length = distance(atm1->fCoords, atm2->fCoords);
      
      if (atm1->atoms.size() > 1)  {
          if (atm1->atoms[0] != atm2) tmp1 = atm1->atoms[0];
          else tmp1 = atm1->atoms[1];
      }
      
      if (atm2->atoms.size() > 1) {
          if (atm2->atoms[0] != atm1) tmp2 = atm2->atoms[0];
          else tmp2 = atm2->atoms[1];
      }

          
      float ang1, ang2;
      ang1 = ang2 = 400;

      if (tmp1 != NULL) ang1 = angleDegrees(tmp1->fCoords, atm1->fCoords, atm2->fCoords);
      if (tmp2 != NULL) ang2 = angleDegrees(tmp2->fCoords, atm2->fCoords, atm1->fCoords);
      
      if (atm1->getAtomicNum() == 6 && atm2->getAtomicNum() == 8 && bd->bondLength() < 1.32) {
      	int bdOrder = this->getTotalBondOrder(atm1);
	 if (bdOrder < 4) {
	    bd->setOrder(2); 
            bd->updateBond();
	 }
      }
      
      if (atm2->getAtomicNum() == 6 && atm1->getAtomicNum() == 8 && bd->bondLength() < 1.32) {
         //Hoping this little check will eliminate the O=C=O in carbonyl groups
	 int bdOrder = this->getTotalBondOrder(atm2);
	 if (bdOrder < 4) {
	    bd->setOrder(2); 
            bd->updateBond();
	 }
      }
      
      
    }
}

void addH::prepMolecule(molecule *mol) {
   //Remove single H's  1ZAP
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      if (atm->atoms.size() == 0 && atm->getAtomicNum() == 1) {
         TrashCan t(atm);
          t.empty();
      }
   }
}

void  addH::addHydrogens(molecule *mol, vector<atom *> &newAtoms) {
  QMutex mutex;
  QMutexLocker locker( &mutex );
 
  prepMolecule(mol);
  mol->ffTypes = "NONE";
  atomTyper typer;
  for (int i=0; i < mol->atoms.size(); i++) {
    atom *atm = mol->atoms[i];
    atm->setNum(i+1);
    atm->setFFType("*"); //reset the forcefield types
    
  }
  for (int i=0; i<mol->atoms.size(); i++) {
     atom *atm = mol->atoms[i];
     atm->atoms.clear();
     atm->angles.clear();
     atm->bonds.clear();
  }
  for (int i=0; i<mol->bonds.size(); i++) {
     bond *bd = mol->bonds[i];
     bd->fromAtom()->addAtom(bd->toAtom());
     bd->toAtom()->addAtom(bd->fromAtom());
  }
  vector<QString> tmp(2);
  tmp[0] = "Adding Hydrogens";
  tmp[1] = "";
  if (view)
    view->viewer->setInfoText(tmp);
  int totalAtoms = mol->atoms.size();
   for (int i=0; i<totalAtoms; i++) {
      atom *atm = mol->atoms[i];

      int totBdOrder = getTotalBondOrder(atm);
      if (atm->getAtomicNum() == 6) {
         if (atm->atoms.size() == 1 && totBdOrder == 1)  
            addTet_H(atm, mol, 3, newAtoms); 
         else if (atm->atoms.size() == 1 && totBdOrder == 2) 
            addTrig_H(atm, mol, 2, newAtoms);
         else if (atm->atoms.size() == 1 && totBdOrder == 3) 
            addOne(atm, mol, 1, newAtoms);
         else if (atm->atoms.size() == 2 && totBdOrder == 2) 
            addTet_H(atm, mol, 2, newAtoms);
         else if (atm->atoms.size() == 2 && totBdOrder == 3) 
            addOne(atm, mol, 1, newAtoms);
         else if (atm->atoms.size() == 3 && totBdOrder == 3) 
            addOne(atm, mol, 1, newAtoms);
      }
      else if(atm->getAtomicNum() == 7) {
         molecule *mol = dynamic_cast<molecule *>(atm->getParent());
         if (atm->atoms.size() == 0) {
            addOne(atm, mol, 1, newAtoms);
            addTet_H(atm, mol, 3, newAtoms);	
         }
         else if (atm->atoms.size() == 1 && totBdOrder == 1) {
            if (atm->getParent()->rtti() == 12) {  
               if (mol->getName() == "LYS" || atm->getSym() == "N  ") {
                  addTet_H(atm, mol, 3, newAtoms);
               }
               else addTrig_H(atm, mol, 2, newAtoms);
            } else {
	      addTrig_H(atm, mol, 2, newAtoms);
            }
         }
         else if (atm->atoms.size() == 1 && totBdOrder == 2) {
            if (atm->getParent()->rtti() == 12) {
               //fragment *frag = dynamic_cast<fragment *>(atm->getParent());
               if (mol->getName() == "ARG") 
                  addTrig_H(atm, mol, 2, newAtoms);
               else 
                  addTrig_H(atm, mol, 1, newAtoms);
            }
         }
         else if (atm->atoms.size() == 2 && totBdOrder == 2) {
            molecule *mol = dynamic_cast<molecule *>(atm->getParent());
	    if (atm->getParent()->rtti() == 12) {
               fragment *frag = dynamic_cast<fragment *>(atm->getParent());
               if (mol->getName() == "PRO" && frag->nTer) 
                  addTet_H(atm, mol, 2, newAtoms);
               else 
                  addOne(atm, mol, 1, newAtoms);
	    }
	    else {
	      addOne(atm, mol, 1, newAtoms);
	    }
	}
     }
     else if(atm->getAtomicNum() == 8) {
        //first case is for water
        if (atm->atoms.size() == 0) waterH(atm, mol, 2, newAtoms);
        else if (atm->atoms.size() == 1 && totBdOrder == 1) {
	   atom *tmp = atm->atoms[0];
	   int oCount = 0;
	   //check for carboxylic acids case...don't want to assign H to carboxylic acids
	   if (tmp->getAtomicNum() == 6)  {
	     for (int i=0; i<tmp->atoms.size(); i++) {
	        atom *tmp2 = tmp->atoms[i];
	        if (tmp2->getAtomicNum() == 8 && tmp2->atoms.size() == 1) oCount++;
	     }
	   }
           if (typer.isNitro_N(tmp)) {
              oCount = 2;
           }
           
	   if (oCount < 2) hydroxylH(atm, mol, 1, newAtoms, 108.161);
	}
     }
     else if(atm->getAtomicNum() == 16) { //Sulfer
        if (atm->atoms.size() == 1 && totBdOrder == 1) hydroxylH(atm, mol, 1, newAtoms, 96.591);
     }
  }
  if (stop == true) return;
  molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1001), wait_sem);
  e->setMolecule(mol, &newAtoms);
  
  if (view) 
     QApplication::postEvent(&view->jm, e);
  //this should block app until sem is released
  //The idea is to make sure that the molList view was updated with
  //The new hydrogens before releasing it.
  if (wait_sem)
     (*wait_sem)++; 
  
  tmp[0] = "Prepping molecule for H-Optimization";
  //Lets reset all the atoms numbers && then rebuild the atom::atoms vectors
  for (int i=0; i < mol->atoms.size(); i++) {
    mol->atoms[i]->setNum(i+1);
  }
  
  for (int i=0; i<mol->atoms.size(); i++) {
     atom *atm = mol->atoms[i];
     atm->atoms.clear();
     atm->angles.clear();
     atm->bonds.clear();
  }
  
  for (int i=0; i<mol->bonds.size(); i++) {
     bond *bd = mol->bonds[i];
     bd->fromAtom()->addAtom(bd->toAtom());
     bd->toAtom()->addAtom(bd->fromAtom());
  }
  
   string atomType;
   
   if (noOptimize) 
      return;
   
   QFile f("min.sdfx"); 
   f.remove();
   /** This section types the atoms */
   if (mol->rtti() < 13)
      atomType = "GAFF";
   else
      atomType = "AMBER_03";
 

   //Brand New dynacomp Stuff
   dynacomp::molecule *dcMol = new dynacomp::molecule();
   molAdapter::mol2dynacomp(dcMol, mol);

   dynacomp::forceField *fdc = new dynacomp::forceField();
   if (!fdc->setAtomTypes(dcMol, atomType)) {
      errorMsg = fdc->getErrorMsg();
      displayErrors();
      return;
   }

   vector<dynacomp::atom *> dcAtoms;
   for (int i=0; i<dcMol->atoms.size(); i++) {
        dynacomp::atom *atm = dcMol->atoms[i];
        if (atm->getAN() == 1) dcAtoms.push_back(atm);
   }
   vector<dynacomp::bond *> dcBonds;
   for (int i=0; i<dcMol->bonds.size(); i++) {
      dynacomp::bond *bd = dcMol->bonds[i];
      dynacomp::atom *atm1 = bd->fromAtom();
      dynacomp::atom *atm2 = bd->toAtom();
      if (atm1->getAN() == 1) dcBonds.push_back(bd);
      else if (atm2->getAN() == 1) dcBonds.push_back(bd);
   }
   vector<dynacomp::anglePtr> dcAngles, dcAngles2;
   vector<dynacomp::torPtr> dcTorsions;
   dcMol->setAngles();
   for (int i=0; i<dcMol->angles.size(); i++) {
      dynacomp::anglePtr ang = dcMol->angles[i];
      if (ang->front->getAN() == 1 || ang->back->getAN() == 1) {
         dcAngles.push_back(ang);
      }
   }
   dcMol->setTorsions();
   for (int i=0; i<dcMol->torsions.size(); i++) {
      dynacomp::torPtr tor = dcMol->torsions[i];
      if (tor->atm1->getAN() == 1 || tor->atm4->getAN() == 1) {
         dcTorsions.push_back(tor);
      }
   }
   int badIndex = -1;
   if (!fdc->setBonds(dcBonds, atomType, badIndex)) {
       errorMsg = fdc->getErrorMsg();
       displayErrors();
       return;
   }
   if (!fdc->setAngles(dcAngles, atomType, badIndex)) {
       errorMsg = fdc->getErrorMsg();
       displayErrors();
       return;
   }
   if (!fdc->setTorsions(dcTorsions, atomType, badIndex)) {
       errorMsg = fdc->getErrorMsg();
       displayErrors();
       return;
   }
   
   delete fdc;

   dynacomp::energy *dcEnergy = new dynacomp::energy();
   dcEnergy->setInfoText(view->viewer->infoText);
   dcEnergy->setMol(dcMol);

   dcEnergy->setAtoms(dcAtoms);
   if (stop == true) return;
   dcEnergy->setBonds(dcBonds);
   if (stop == true) return;
   dcEnergy->setAngles(dcAngles);
   if (stop == true) return;
   dcEnergy->setTorsions(dcTorsions);
   if (stop == true) return;   

   dcEnergy->setUp("CG", "NONE", "NONE", 1000, .0005, .001, .00000001);
   if (stop == true) return;

   dcEnergy->CG_minimize(200, 0.0, 0.0, 0.000000);
   if (stop == true) return;
   delete dcEnergy;
   
   mol->ffTypes = "NONE";
   mol->chargeType = "NONE";
   mol->angles.clear();
   mol->torsions.clear();
   mol->nonBonds.clear();
   tmp[0] = "";
   if (view)
     view->viewer->setInfoText(tmp);
}

void addH::hydroxylH(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms, float angle) {
      vector<float> dir(3);
      for (int i=0; i<3; i++) dir[i] = 0;
      for (int i=0; i<atm->atoms.size(); i++) {
         atom *tmp = atm->atoms[i];
	 for (int j=0; j<3; j++) dir[j] += tmp->fCoords[j] - atm->fCoords[j];
      }
     
      normalizef(dir);
      for (int i=0; i<3; i++) dir[i] = -dir[i];
      
         vector<float> prod(4), axis1(3);
         vector<float> a1(3), a2(3);
         for (int i=0; i<3; i++) {
           a1[i] = atm->atoms[0]->fCoords[i] - atm->fCoords[i];
         }
         crossProd(prod, a1, dir);
         crossProd(axis1, prod, dir);
         normalizef(axis1);
	 
	 float ang = angle - 90;
	 ang = -ang*3.145/180.0;
	 QUAT quat1(ang, &axis1[0]);
	 vector<float> mat1(16);
	 quat1.buildMatrix(&mat1[0]);
	 
	 vector<float> pos1(4);
      	 mulit_4X16(pos1, prod, mat1);
	 
	 normalizef(&pos1[0], 3);
	 for (int i=0; i<3; i++) pos1[i] += atm->fCoords[i];
	 if (atm->getParent()->rtti() == 11) {
           molecule *mol = dynamic_cast<molecule *>(atm->getParent());
	   for (int i=0; i<mol->atoms.size(); i++) {
	     mol->atoms[i]->setNum(i+1);
	   }
           atom *tmp1 = mol->addAtom(mol->atoms.size()+1, "H", pos1[0], pos1[1], pos1[2], 1);
           newAtoms.push_back(tmp1);
		      
           bond *bd = mol->addBond(mol->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
           bd->setParent(mol);
           bd->fromAtom()->addAtom(bd->toAtom());
           bd->toAtom()->addAtom(bd->fromAtom());
         }       
	 else if (atm->getParent()->rtti() == 12) {
	   fragment *frag = dynamic_cast<fragment *>(atm->getParent());
	   for (int i=0; i<frag->atoms.size(); i++) {
	    frag->atoms[i]->setNum(i+1);
	   }
           atom *tmp1 = frag->addAtom(frag->atoms.size()+1, "H", pos1[0], pos1[1], pos1[2], 1);
           newAtoms.push_back(tmp1);
		      
           bond *bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
           bd->setParent(frag);
           bd->fromAtom()->addAtom(bd->toAtom());
           bd->toAtom()->addAtom(bd->fromAtom());
      
           if (frag->getParent()->rtti() == 13) {
             chain *ch = dynamic_cast<chain *>(frag->getParent());
	     ch->atoms.push_back(tmp1);
	     ch->bonds.push_back(bd);
	  
	     if (ch->getParent()->rtti() == 14) {
	        protein *prot = dynamic_cast<protein *>(ch->getParent());
	        prot->atoms.push_back(tmp1);
	        prot->bonds.push_back(bd);
	     }
          }
	 }
}

void addH::waterH(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms) {
	
	vector<float> pos(3);
	for (int i=0; i<3; i++) pos[i] = atm->fCoords[i];
	//float inc = sqrt(2.0)/2.0;
	float inc = 1.543/2.0;

	if (atm->getParent()->rtti() == 11) {
           molecule *mol = dynamic_cast<molecule *>(atm->getParent());
	   for (int i=0; i<mol->atoms.size(); i++) {
	     mol->atoms[i]->setNum(i+1);
	   }
           atom *tmp1 = mol->addAtom(mol->atoms.size()+1, "H", pos[0], pos[1]+.5953, pos[2]-inc, 1);
           newAtoms.push_back(tmp1);
		      
           bond *bd = mol->addBond(mol->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
           bd->setParent(mol);
           bd->fromAtom()->addAtom(bd->toAtom());
           bd->toAtom()->addAtom(bd->fromAtom());
	   
	   for (int i=0; i<mol->atoms.size(); i++) {
	     mol->atoms[i]->setNum(i+1);
	   }
           tmp1 = mol->addAtom(mol->atoms.size()+1, "H", pos[0], pos[1]+.5953, pos[2]+inc, 1);
           newAtoms.push_back(tmp1);
		      
           bd = mol->addBond(mol->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
           bd->setParent(mol);
           bd->fromAtom()->addAtom(bd->toAtom());
           bd->toAtom()->addAtom(bd->fromAtom());
        }    
	else if (atm->getParent()->rtti() == 12) {
	   fragment *frag = dynamic_cast<fragment *>(atm->getParent());
	   for (int i=0; i<frag->atoms.size(); i++) {
	    frag->atoms[i]->setNum(i+1);
	   }
           atom *tmp1 = frag->addAtom(frag->atoms.size()+1, "H", pos[0], pos[1]+.5953, pos[2]-inc, 1);
           newAtoms.push_back(tmp1);
		      
           bond *bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
           bd->setParent(frag);
           bd->fromAtom()->addAtom(bd->toAtom());
           bd->toAtom()->addAtom(bd->fromAtom());
      
           if (frag->getParent()->rtti() == 13) {
             chain *ch = dynamic_cast<chain *>(frag->getParent());
	     ch->atoms.push_back(tmp1);
	     ch->bonds.push_back(bd);
	  
	     if (ch->getParent()->rtti() == 14) {
	        protein *prot = dynamic_cast<protein *>(ch->getParent());
	        prot->atoms.push_back(tmp1);
	        prot->bonds.push_back(bd);
	     }
          }
	  
	   tmp1 = frag->addAtom(frag->atoms.size()+1, "H", pos[0], pos[1]+.5953, pos[2]+inc, 1);
           newAtoms.push_back(tmp1);
		      
           bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
           bd->setParent(frag);
           bd->fromAtom()->addAtom(bd->toAtom());
           bd->toAtom()->addAtom(bd->fromAtom());
      
           if (frag->getParent()->rtti() == 13) {
             chain *ch = dynamic_cast<chain *>(frag->getParent());
	     ch->atoms.push_back(tmp1);
	     ch->bonds.push_back(bd);
	  
	     if (ch->getParent()->rtti() == 14) {
	        protein *prot = dynamic_cast<protein *>(ch->getParent());
	        prot->atoms.push_back(tmp1);
	        prot->bonds.push_back(bd);
	     }
          }
	 }   
}

void addH::addTrig_H(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms) {
      vector<float> dir(3);
      for (int i=0; i<3; i++) dir[i] = 0;
      for (int i=0; i<atm->atoms.size(); i++) {
         atom *tmp = atm->atoms[i];
	 for (int j=0; j<3; j++) dir[j] += tmp->fCoords[j] - atm->fCoords[j];
      }
      
      normalizef(dir);
      for (int i=0; i<3; i++) dir[i] = -dir[i];
      
         vector<float> prod(4), axis1(3);
         vector<float> a1(3), a2(3);
         for (int i=0; i<3; i++) {
           a1[i] = atm->atoms[0]->fCoords[i] - atm->fCoords[i];
         }
         crossProd(prod, a1, dir);
         crossProd(axis1, prod, dir);

         axisCheck(axis1);
         normalizef(axis1);
 
	 float ang = -30.0*3.145/180.0;
	 QUAT quat1(ang, &axis1[0]);
	 vector<float> mat1(16);
	 quat1.buildMatrix(&mat1[0]);
	 
	 vector<float> pos1(4);
      	 mulit_4X16(pos1, prod, mat1);

         axisCheck(pos1); //you using this routine correctly 
	 normalizef(&pos1[0], 3);

	 for (int i=0; i<3; i++) pos1[i] += atm->fCoords[i];
	 if (atm->getParent()->rtti() == 11) {
           molecule *mol = dynamic_cast<molecule *>(atm->getParent());
	   for (int i=0; i<mol->atoms.size(); i++) {
	     mol->atoms[i]->setNum(i+1);
	   }
           atom *tmp1 = mol->addAtom(mol->atoms.size()+1, "H", pos1[0], pos1[1], pos1[2], 1);
           newAtoms.push_back(tmp1);
		      
           bond *bd = mol->addBond(mol->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
           bd->setParent(mol);
           bd->fromAtom()->addAtom(bd->toAtom());
           bd->toAtom()->addAtom(bd->fromAtom());
         }       
	 else if (atm->getParent()->rtti() == 12) {
	   fragment *frag = dynamic_cast<fragment *>(atm->getParent());
	   for (int i=0; i<frag->atoms.size(); i++) {
	    frag->atoms[i]->setNum(i+1);
	   }
           atom *tmp1 = frag->addAtom(frag->atoms.size()+1, "H", pos1[0], pos1[1], pos1[2], 1);
           newAtoms.push_back(tmp1);
		      
           bond *bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
           bd->setParent(frag);
           bd->fromAtom()->addAtom(bd->toAtom());
           bd->toAtom()->addAtom(bd->fromAtom());
      
           if (frag->getParent()->rtti() == 13) {
             chain *ch = dynamic_cast<chain *>(frag->getParent());
	     ch->atoms.push_back(tmp1);
	     ch->bonds.push_back(bd);
	  
	     if (ch->getParent()->rtti() == 14) {
	        protein *prot = dynamic_cast<protein *>(ch->getParent());
	        prot->atoms.push_back(tmp1);
	        prot->bonds.push_back(bd);
	     }
          }
	 }
	 if (num == 2) {
	    vector<float> dir(3);
            for (int i=0; i<3; i++) dir[i] = 0;
            for (int i=0; i<atm->atoms.size(); i++) {
              atom *tmp = atm->atoms[i];
	      for (int j=0; j<3; j++) dir[j] += tmp->fCoords[j] - atm->fCoords[j];
            }
	    normalizef(dir);
      	    for (int i=0; i<3; i++) dir[i] = -dir[i];
	    for (int i=0; i<3; i++) dir[i] += atm->fCoords[i];
	    
	    if (atm->getParent()->rtti() == 11) {
                molecule *mol = dynamic_cast<molecule *>(atm->getParent());
	        for (int i=0; i<mol->atoms.size(); i++) {
	          mol->atoms[i]->setNum(i+1);
	        }
            	atom *tmp1 = mol->addAtom(mol->atoms.size()+1, "H", dir[0], dir[1], dir[2], 1);
            	newAtoms.push_back(tmp1);
		      
            	bond *bd = mol->addBond(mol->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
            	bd->setParent(mol);
            	bd->fromAtom()->addAtom(bd->toAtom());
            	bd->toAtom()->addAtom(bd->fromAtom());
           }  
	   else if (atm->getParent()->rtti() == 12) {
	   	fragment *frag = dynamic_cast<fragment *>(atm->getParent());
	   	for (int i=0; i<frag->atoms.size(); i++) {
	    		frag->atoms[i]->setNum(i+1);
	   	}
           	atom *tmp1 = frag->addAtom(frag->atoms.size()+1, "H", dir[0], dir[1], dir[2], 1);
           	newAtoms.push_back(tmp1);
		      
           	bond *bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
           	bd->setParent(frag);
           	bd->fromAtom()->addAtom(bd->toAtom());
           	bd->toAtom()->addAtom(bd->fromAtom());
      
           	if (frag->getParent()->rtti() == 13) {
           	  	chain *ch = dynamic_cast<chain *>(frag->getParent());
	     	  	ch->atoms.push_back(tmp1);
	          	ch->bonds.push_back(bd);
	  
	     		if (ch->getParent()->rtti() == 14) {
	        	   protein *prot = dynamic_cast<protein *>(ch->getParent());
	        	   prot->atoms.push_back(tmp1);
	        	   prot->bonds.push_back(bd);
	        	}
          	}
	 }
	       
	 }
}

void addH::addTet_H(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms) {
   vector<float> dir(3);
   for (int i=0; i<3; i++) dir[i] = 0;
   for (int i=0; i<atm->atoms.size(); i++) {
      atom *tmp = atm->atoms[i];
      for (int j=0; j<3; j++) dir[j] += tmp->fCoords[j] - atm->fCoords[j];
   }
   normalizef(dir);
   for (int i=0; i<3; i++) dir[i] = -dir[i];
   if (num == 2 && atm->atoms.size() == 2) {
      vector<float> prod(4), prod2(3);
      vector<float> a1(3), a2(3);
      for (int i=0; i<3; i++) {
        a1[i] = atm->atoms[0]->fCoords[i] - atm->fCoords[i];
	a2[i] = atm->atoms[1]->fCoords[i] - atm->fCoords[i];
      }
      crossProd(prod, a1, a2);
      crossProd(prod2, prod, dir);
      
      normalizef(prod2);
      
      vector<float> prod3 = prod2;
      vector<float> prod4 = prod2;
      
      float angle = -40.0*3.145/180.0;
      float angle2 = (-40.0-109.5)*3.145/180.0;
      QUAT quat1(angle, &prod2[0]);
      QUAT quat2(angle2, &prod3[0]);
      
      vector<float> mat1(16), mat2(16);
      quat1.buildMatrix(&mat1[0]);
      quat2.buildMatrix(&mat2[0]);
      prod[3] = 0;
      normalizef(prod);
      vector<float> pos1(4), pos2(4);
      mulit_4X16(pos1, prod, mat1);
      mulit_4X16(pos2, prod, mat2);
      normalizef(pos1);
      normalizef(pos2);
      
      for (int i=0; i<3; i++) pos1[i] += atm->fCoords[i];
      for (int i=0; i<3; i++) pos2[i] += atm->fCoords[i];
      for (int i=0; i<3; i++) prod[i] += atm->fCoords[i];
   
      if (atm->getParent()->rtti() == 11) {
          molecule *mol = dynamic_cast<molecule *>(atm->getParent());
	  for (int i=0; i<mol->atoms.size(); i++) {
	    mol->atoms[i]->setNum(i+1);
	  }
          atom *tmp1 = mol->addAtom(mol->atoms.size()+1, "H", pos1[0]+.005, pos1[1], pos1[2], 1);
          newAtoms.push_back(tmp1);
		      
          bond *bd = mol->addBond(mol->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
          bd->setParent(mol);
          bd->fromAtom()->addAtom(bd->toAtom());
          bd->toAtom()->addAtom(bd->fromAtom());
	  
	  for (int i=0; i<mol->atoms.size(); i++) {
	    mol->atoms[i]->setNum(i+1);
	  }
          tmp1 = mol->addAtom(mol->atoms.size()+1, "H", pos2[0]+.005, pos2[1], pos2[2], 1);
          newAtoms.push_back(tmp1);
		      
          bd = mol->addBond(mol->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
          bd->setParent(mol);
          bd->fromAtom()->addAtom(bd->toAtom());
          bd->toAtom()->addAtom(bd->fromAtom());
      } 
      else if (atm->getParent()->rtti() == 12) {
	  fragment *frag = dynamic_cast<fragment *>(atm->getParent());
	  for (int i=0; i<frag->atoms.size(); i++) {
	    frag->atoms[i]->setNum(i+1);
	  }
          atom *tmp1 = frag->addAtom(frag->atoms.size()+1, "H", pos1[0]+.005, pos1[1], pos1[2], 1);
          newAtoms.push_back(tmp1);
		      
          bond *bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
          bd->setParent(frag);
          bd->fromAtom()->addAtom(bd->toAtom());
          bd->toAtom()->addAtom(bd->fromAtom());
      
          if (frag->getParent()->rtti() == 13) {
             chain *ch = dynamic_cast<chain *>(frag->getParent());
	     ch->atoms.push_back(tmp1);
	     ch->bonds.push_back(bd);
	  
	     if (ch->getParent()->rtti() == 14) {
	        protein *prot = dynamic_cast<protein *>(ch->getParent());
	        prot->atoms.push_back(tmp1);
	        prot->bonds.push_back(bd);
	     }
         }
	 
	 for (int i=0; i<frag->atoms.size(); i++) {
	    frag->atoms[i]->setNum(i+1);
	  }
          tmp1 = frag->addAtom(frag->atoms.size()+1, "H", pos2[0]+.005, pos2[1], pos2[2], 1);
          newAtoms.push_back(tmp1);
		      
          bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
          bd->setParent(frag);
          bd->fromAtom()->addAtom(bd->toAtom());
          bd->toAtom()->addAtom(bd->fromAtom());
      
          if (frag->getParent()->rtti() == 13) {
             chain *ch = dynamic_cast<chain *>(frag->getParent());
	     ch->atoms.push_back(tmp1);
	     ch->bonds.push_back(bd);
	  
	     if (ch->getParent()->rtti() == 14) {
	        protein *prot = dynamic_cast<protein *>(ch->getParent());
	        prot->atoms.push_back(tmp1);
	        prot->bonds.push_back(bd);
	     }
         }
      }
   }
   
   
   //########### NOW WE TAKE CARE OF THE adding 3 hydrogens case
   else if (num == 3 && atm->atoms.size() == 1) {
      vector<float> axis1(4), prod2(3);
      vector<float> a1(3);
      for (int i=0; i<3; i++) {
        a1[i] = atm->atoms[0]->fCoords[i] - atm->fCoords[i];
      }
      
      crossProd(axis1, a1, dir);
     
      axisCheck(axis1);
      normalizef(axis1);

      float ang1 = 70.5*3.145/180.0;
      QUAT quat1(ang1, &axis1[0]);
      vector<float> mat1(16);
      
      quat1.buildMatrix(&mat1[0]);

      vector<float> pos1(4), pos2(4);
      pos1[3] = 0;
      mulit_4X16(pos1, dir, mat1);
      
      for (int i=0; i<3; i++) dir[i] += atm->fCoords[i];
      for (int i=0; i<3; i++) axis1[i] += atm->fCoords[i];
      
      //use this normalize becuase you need to anly normalize across the three positions..not 4
      //It took you a while to figure this all out.
      normalizef(&pos1[0], 3);
            
      for (int i=0; i<3; i++) pos1[i] += atm->fCoords[i];
      
      if (atm->getParent()->rtti() == 11) {
	  molecule *mol = dynamic_cast<molecule *>(atm->getParent());
	    
	  for (int i=0; i<mol->atoms.size(); i++) {
	    mol->atoms[i]->setNum(i+1);
	  }
          atom *tmp1 = mol->addAtom(mol->atoms.size()+1, "H", pos1[0], pos1[1], pos1[2], 1);
          newAtoms.push_back(tmp1);
		      
          bond *bd = mol->addBond(mol->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
          bd->setParent(mol);
          bd->fromAtom()->addAtom(bd->toAtom());
          bd->toAtom()->addAtom(bd->fromAtom());
	  
	  addTet_H(atm, mol, 2, newAtoms);  
      } 
      else if (atm->getParent()->rtti() == 12) {	  
	  fragment *frag = dynamic_cast<fragment *>(atm->getParent());
	  for (int i=0; i<frag->atoms.size(); i++) {
	    frag->atoms[i]->setNum(i+1);
	  }
          atom *tmp1 = frag->addAtom(frag->atoms.size()+1, "H", pos1[0], pos1[1], pos1[2], 1);
          newAtoms.push_back(tmp1);
		      
          bond *bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
          bd->setParent(frag);
          bd->fromAtom()->addAtom(bd->toAtom());
          bd->toAtom()->addAtom(bd->fromAtom());
      
          if (frag->getParent()->rtti() == 13) {
             chain *ch = dynamic_cast<chain *>(frag->getParent());
	     ch->atoms.push_back(tmp1);
	     ch->bonds.push_back(bd);
	  
	     if (ch->getParent()->rtti() == 14) {
	        protein *prot = dynamic_cast<protein *>(ch->getParent());
	        prot->atoms.push_back(tmp1);
	        prot->bonds.push_back(bd);
	     }
         }
	 addTet_H(atm, mol, 2, newAtoms);
      }
   
   }
}


void addH::addOne(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms) {
    //Since 1 is the simplest case we shall solve it first
    if (num == 1) {
      vector<float> dir(3);
      for (int i=0; i<3; i++) dir[i] = 0;
     
      if (atm->atoms.size() > 0) { 
         for (int i=0; i<atm->atoms.size(); i++) {
            atom *tmp = atm->atoms[i];
	    for (int j=0; j<3; j++) {
               dir[j] += tmp->fCoords[j] - atm->fCoords[j];
            }
         }
     
         axisCheck(dir);
 
         normalizef(dir);
      
         for (int i=0; i<3; i++) dir[i] = -dir[i];
         for (int i=0; i<3; i++) dir[i] += atm->fCoords[i];
      }
      else {
	      dir[0] = 1.0; dir[1] = 1.0; dir[2] = 1.0;
      }
      if (atm->getParent()->rtti() == 11) {
         molecule *mol = dynamic_cast<molecule *>(atm->getParent());
	 for (int i=0; i<mol->atoms.size(); i++) {
	    mol->atoms[i]->setNum(i+1);
	  }
          atom *tmp1 = mol->addAtom(mol->atoms.size()+1, "H", dir[0]+.005, dir[1], dir[2], 1);
          newAtoms.push_back(tmp1);
		      
          bond *bd = mol->addBond(mol->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
          bd->setParent(mol);
          bd->fromAtom()->addAtom(bd->toAtom());
          bd->toAtom()->addAtom(bd->fromAtom());
      } 
      else if (atm->getParent()->rtti() == 12) {
	  fragment *frag = dynamic_cast<fragment *>(atm->getParent());
	  for (int i=0; i<frag->atoms.size(); i++) {
	    frag->atoms[i]->setNum(i+1);
	  }
          atom *tmp1 = frag->addAtom(frag->atoms.size()+1, "H", dir[0]+.005, dir[1], dir[2], 1);
          newAtoms.push_back(tmp1);
		
          bond *bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);
          bd->setParent(frag);
          bd->fromAtom()->addAtom(bd->toAtom());
          bd->toAtom()->addAtom(bd->fromAtom());
          if (frag->getParent()->rtti() == 13) {
             chain *ch = dynamic_cast<chain *>(frag->getParent());
	     ch->atoms.push_back(tmp1);
	     ch->bonds.push_back(bd);
	     molecule *mol = dynamic_cast<molecule *>(ch->getParent());
	     if (mol && mol->rtti() == 14) {
	        protein *prot = dynamic_cast<protein *>(mol);
	        prot->atoms.push_back(tmp1);
	        prot->bonds.push_back(bd);
	     }
         }
      }
    }
}

void addH::bondHydrogen(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms) {
//First lets re-number the damned molecule/chain/protein

	float *cd = atm->fCoords;
	
	if (atm->getParent()->rtti() == 12) {
	   ////////////////cout <<"it is a fragment"<<endl;
	   fragment *frag = dynamic_cast<fragment *>(atm->getParent());
	   for (int i=0; i<frag->atoms.size(); i++) {
	     frag->atoms[i]->setNum(i+1);
	   }
	   atom *tmp1 = NULL;
	   bond *bd = NULL;
	   
	   
	   if (num == 1) {
	     //for (int k=0; k<num; k++) {
	     //First we want to determine the sum of the bonded atom vectors
	     //Step one translate to the origin
	     vector<float> center(3), dir(3);
	     center[0] = atm->fCoords[0];
	     center[1] = atm->fCoords[1];
	     center[2] = atm->fCoords[2];
	     
	     for (int i=0; i<3; i++) dir[i] = 0;
	
	     for (int i=0; i<atm->atoms.size(); i++) {
	        atom *tmp = atm->atoms[i];
		for (int j=0; j<3; j++) dir[j] += tmp->fCoords[j] - center[j];
	     }
	     
	
	     for(int j=0; j<3; j++) dir[j] /= atm->atoms.size();

             //////cout <<"probl 13"<<endl;	
	     normalizef(dir);
		
	     for (int j=0; j<3; j++) dir[j] = -dir[j] + center[j];
		  
	     //The .05 i here sothat it will minimize correctly???? I dunno man
	     tmp1 = frag->addAtom(frag->atoms.size()+1, "H", dir[0]+.05, dir[1], dir[2], 1);
	     newAtoms.push_back(tmp1);
		      
	      bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);

	      bd->setParent(frag);
	      bd->fromAtom()->addAtom(bd->toAtom());
  	      bd->toAtom()->addAtom(bd->fromAtom());

	      if (frag->getParent()->rtti() == 13) {
	      	chain *ch = dynamic_cast<chain *>(frag->getParent());
		ch->atoms.push_back(tmp1);
		ch->bonds.push_back(bd);
		
		if (ch->getParent()->rtti() == 14) {
		  protein *prot = dynamic_cast<protein *>(ch->getParent());
		  prot->atoms.push_back(tmp1);
		  prot->bonds.push_back(bd);
		}
	      }
	      
	   } else { 
	   for (int i=0; i<num; i++) {
	      if (i == 0) tmp1 = frag->addAtom(frag->atoms.size()+1, "H", cd[0]+1, cd[1]+1, cd[2]+1, 1);
	      if (i == 1) tmp1 = frag->addAtom(frag->atoms.size()+1, "H", cd[0]-1, cd[1]-1, cd[2]-1, 1);
	      if (i == 2) tmp1 = frag->addAtom(frag->atoms.size()+1, "H", cd[0]-1, cd[1]+1, cd[2]-1, 1);
	      
	      	
	      newAtoms.push_back(tmp1);
	      
	      
	      
	      bd = frag->addBond(frag->bonds.size(), tmp1->getNum(), atm->getNum(), 1);

	      bd->setParent(frag);
	      bd->fromAtom()->addAtom(bd->toAtom());
  	      bd->toAtom()->addAtom(bd->fromAtom());

	      if (frag->getParent()->rtti() == 13) {
	      	chain *ch = dynamic_cast<chain * >(frag->getParent());
		ch->atoms.push_back(tmp1);
		ch->bonds.push_back(bd);
		
		if (ch->getParent()->rtti() == 14) {
		  protein *prot = dynamic_cast<protein *>(ch->getParent());
		  prot->atoms.push_back(tmp1);
		  prot->bonds.push_back(bd);
		}
	      }
	   }
	   }
	} 
	else if (atm->getParent()->rtti() == 13) {
		//////////////cout <<"It is  a chain"<<endl;
	}
	else if (atm->getParent()->rtti() == 14) {
		//////////////cout <<"It is a  protein"<< endl;
	}

}


// ######################### DON"T LIKE THIESE BEING IN HERE ######################3
void addH::buildAngleVec(vector<bond *> &bonds, molecule *mol, vector<angle *> &angles) {
   //First step is to clear any current angles;
    angles.clear();
    
    for (int i=0; i<bonds.size(); i++) {
    	bond *bi = bonds[i];
	atom *aiFrom = bi->fromAtom();
	atom *aiTo = bi->toAtom();
    	for (int j=0; j<mol->bonds.size(); j++) {
		angle *ang = NULL;
      		bond *bj = mol->bonds[j];
		if (bj != bi) {
		  atom *ajFrom = bj->fromAtom();
		  atom *ajTo = bj->toAtom();
		
      		  if (aiFrom == ajFrom) ang = new angle(aiTo, aiFrom, ajTo);
      		  else if (aiTo == ajTo) ang = new angle(aiFrom, aiTo, ajFrom);
       		  else if (aiFrom == ajTo) ang = new angle(aiTo, aiFrom, ajFrom);
      	          else if (aiTo == ajFrom) ang = new angle(aiFrom, aiTo, ajTo);
      
		  if (ang != NULL) {
		    if (ang->front != ang->mid && ang->front != ang->back && ang->mid != ang->back) {
			angles.push_back(ang);	
		    }
		  }
		}
	}
    }
}



void addH::buildTorVec(vector<angle *> &angles, molecule *mol, vector<torsion *> &torsions) {
    if (angles.size() == 0) {
    	//////////////cout <<"You need to call setAngles before setTorsions"<<endl;
	return;
    }

    torsions.clear();
   
    
     for (int i=0; i<angles.size(); i++) {
        atom *atm1 = angles[i]->front;
	atom *atm2 = angles[i]->mid;
	atom *atm3 = angles[i]->back;   
	for (int j=0; j<mol->bonds.size(); j++) {
   	    atom *atm4 = mol->bonds[j]->toAtom();
	    atom *atm5 = mol->bonds[j]->fromAtom();
	    
	    if (atm4 == atm1 && atm5 != atm2) addTorsion(atm5, atm1, atm2, atm3, torsions);
	    else if (atm5 == atm1 && atm4 != atm2) addTorsion(atm4, atm1, atm2, atm3, torsions);
	    else if (atm4 == atm3 && atm5 != atm2) addTorsion(atm1, atm2, atm3, atm5, torsions);
	    else if (atm5 == atm3 && atm4 != atm2) addTorsion(atm1, atm2, atm3, atm4, torsions);	
	}
     }
     
}


void addH::addTorsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4, vector<torsion *> &torsions) {
	if (torsions.size() == 0) {
		torsion *tor = new torsion(atm1, atm2, atm3, atm4);
		torsions.push_back(tor);
		return;
	}
	
	for (int i=0; i<torsions.size(); i++) {
		atom *tor1 = torsions[i]->atm1;
		atom *tor2 = torsions[i]->atm2;
		atom *tor3 = torsions[i]->atm3;
		atom *tor4 = torsions[i]->atm4;
		int count = 0;
		if (tor1 == atm1 || tor1 == atm2 || tor1 == atm3 || tor1 == atm4) count++;
		if (tor2 == atm1 || tor2 == atm2 || tor2 == atm3 || tor2 == atm4) count++;
		if (tor3 == atm1 || tor3 == atm2 || tor3 == atm3 || tor3 == atm4) count++;
		if (tor4 == atm1 || tor4 == atm2 || tor4 == atm3 || tor4 == atm4) count++;
		
		if (count == 4) return;
	}
	////////////////cout <<"Adding new torsion"<<endl;
	torsion *tor = new torsion(atm1, atm2, atm3, atm4);
	torsions.push_back(tor);
}


int addH::getTotalBondOrder(atom *atm) {
   molecule *mol = dynamic_cast<molecule *>(atm->lastParent());
   
   int totalBondOrder = 0;
   for (int i=0; i<atm->atoms.size(); i++) {
      bond *bd = mol->getBond(atm, atm->atoms[i]);
      if (bd != NULL) { 
      	totalBondOrder += bd->getOrder();
      } else {
        ////////////////cout << atm->getNum() << setw(12) << atm->atoms[i]->getNum() << endl;
      }
   }
   return totalBondOrder;
}


void addH::axisCheck(vector<float> &axis) {
   while (axis[0] == 0 && axis[1] == 0 && axis[2] == 0) {
      for (int i=0; i<3; i++) {
         axis[i] = rand() % 10000000;
         axis[i] /= 10000000;
      }
   }
}

































