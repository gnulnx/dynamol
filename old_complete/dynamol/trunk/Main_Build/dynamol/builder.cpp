/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "builder.h"
#include "buildDialog.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "buildDialog.h"
#include "molview.h"
#include "mollistview.h"
#include <iomanip>
#include <list>
#include "molchangeevent.h"
#include "qmessagebox.h"
#include "atom.h"
#include "bond.h"
#include "xmodelview.h"
#include "linAlg.h"
#include "quat.h"
#include "dynothread.h"
#include "atomtyper.h"
#include "trashcan.h"
#include "moldb.h"

#include <qfile.h>
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qstring.h>

using namespace std;


builder::builder(QObject *parent, const char *name)
 : QObject(parent, name)
{
   
   prevAtom = NULL;
   ENABLE = true;
   QString fragFile = "";

   #ifdef LINUX
      fragFile = getenv("DYNAMOL");
      fragFile += "/frags/builderFrags.sdf";
   #endif

   #ifdef WINDOWS
      fragFile = "..\\frags\\builderFrags.sdf";
   #endif 

   if (!QFile::exists(fragFile)) {
      QString error = "Fragment file not found\n";
      error += "Builder will crash if you try to use rings";
      QMessageBox::critical(0, "Dynamol", error);
   }

   molDB::readSDToMolVec(fragFile.latin1(), frags);
}
void builder::setMolView(molView *viewer) {
   this->viewer = viewer;
  
}
void builder::setDialog(builderDialog *dialog) {
   this->dialog = dialog;
   connect(dialog->addH, SIGNAL(clicked()), this, SLOT(addH()));
   connect(dialog->remH, SIGNAL(clicked()), this, SLOT(delH()));
   connect(dialog->clean, SIGNAL(clicked()), this, SLOT(clean()));
}

builder::~builder()
{
}

void builder::processRequest(double x, double y, double z) {
   #ifdef BUILDER_COMMENT
      cout <<"\nbuilder::processRequest"<<endl;
   #endif
   viewer->renderOff();
   if (!ENABLE) return;
   currSpot.clear();
   currSpot.push_back(x);
   currSpot.push_back(y);
   currSpot.push_back(z);
   
   if (dialog->draw->isChecked()) {
      drawMode();
   } else if (dialog->retype->isChecked()) {
      reTypeMode();
   } else if (dialog->Delete->isChecked()) {
      delMode();
   }

      
   viewer->renderOn();
   viewer->updateGL();
   #ifdef BUILDER_COMMENT
      cout <<"Leaving builder::processRequest"<<endl;
   #endif
}


void builder::checkChirality() {
   atom *atm = NULL;
   bond *bd = NULL;
   
   currSelection(atm, bd);
   if (atm == NULL) return;
   
   atomTyper typer;
   string cType = typer.chirality(atm);
}

void builder::reTypeMode() {
   viewer->SPHERES.clear();
   prevSpot.clear();

   atom *atm = NULL;
   bond *bd = NULL;
   
   currSelection(atm, bd);
   
   if (atm) reTypeAtom(atm);
   if (bd) reTypeBond(bd);
}

void builder::delMode() {
   atom *atm = NULL;
   bond *bd = NULL;
   
   currSelection(atm, bd);
   
   if (atm != NULL) {
      TrashCan t(atm);
      t.empty();
   }
   
   if (bd != NULL) {
      vector<atom *> atomsToDel;
      atomsToDel.push_back(bd->from);
      atomsToDel.push_back(bd->to);
      TrashCan t(atomsToDel);
      t.empty();
   }
}

void builder::reTypeBond(bond *bd) {
   if (bd->getOrder() == 3)
      bd->setOrder(1);
   else 
      bd->setOrder( bd->getOrder() + 1 );

   //bd->setOrder(dialog->bondGroup->selectedId()+1);
}

void builder::currSelection(atom *&atm, bond *&bd) {
   list<molecule *>::iterator molIter = viewer->renList->begin();               
   for (molIter; molIter != viewer->renList->end(); molIter++) {
      molecule *mol = *molIter;
      for (int i=0; i<mol->atoms.size(); i++) {
         atom *tmpAtm = mol->atoms[i];
         if (tmpAtm->isSelected()) {
            atm = tmpAtm;
            return;
         }
      }
      
      for (int i=0; i<mol->bonds.size(); i++) {
         bond *tmpBd = mol->bonds[i];
         if (tmpBd->selected) {
            bd = tmpBd;
            break;
         }
      }
   }              
}


void builder::reTypeAtom(atom *atm) {
   QString aType = dialog->otherAtom->currentText();
   QString sym;
   int AN;
   getType(aType, sym, AN);
   atm->changeType(sym.latin1(), AN);
}

void builder::drawMode() {
   #ifdef BUILDER_COMMENT
      cout <<"builder::drawMode"<<endl;
   #endif
   //Make sure all the spheres are cleared in the molView
   viewer->SPHERES.clear();
  
   
   if ( dialog->ringGroup->selectedId() == -1) {
      sketchMode();
   } else { 
      ringMode();
   }
   #ifdef BUILDER_COMMENT
      cout <<"Leaving builder::drawMode"<<endl;
   #endif   
}

void builder::sketchMode() {
   //First check for the case of no current molecule     
   if (viewer->renList->size() == 0) {
      noMolecule();
      for (int i=0; i<3; i++) currSpot[i] = 0.0;
      prevSpot = currSpot;
      return;
   }
   //Determine the bond order
   int bOrder = dialog->bondGroup->selectedId()+1;
   
   //Now lets figure out what sort of atom we are drawing
   QString aType = dialog->otherAtom->currentText();
   QString sym;
   int AN;
   getType(aType, sym, AN);
   
   atom *currAtom = NULL;
   bond *currBd = NULL;
   currSelection(currAtom, currBd);
   if (currBd) {
      if (currBd->getOrder() == 3) currBd->setOrder(1);
      else currBd->setOrder(currBd->getOrder()+1);
      prevAtom = NULL;
   }
   
   else if ( (prevAtom && currAtom) && (prevAtom != currAtom) ) {
      bondAtoms(prevAtom, currAtom, bOrder);
      prevAtom = NULL;
   }
   
   //Clear the builder
   else if ( (prevAtom && currAtom) && (prevAtom == currAtom) ) {
      prevAtom = NULL;
   }
   
   else if (!prevAtom && currAtom) {
      prevAtom = currAtom;
      viewer->addSphere(currSpot[0], currSpot[1], currSpot[2],
                     0.75, wire, 0.0, 1.0, 0.2);
   }
   
   //create new atom and select it.
   else if (!prevAtom && !currAtom) {
      createLoneAtom(sym, AN);   
   }
   
   else if (prevAtom && !currAtom) {
      //create new atom and bond it to prev atom
      createAndBondAtom(sym, AN, bOrder);
   }
  
   prevSpot = currSpot;
}

void builder::ringMode() {
   #ifdef BUILDER_COMMENT
      cout <<"builder::ringMode"<<endl;
   #endif
 
   molecule *mol;
   int molCount = 0;
   list<molecule *>::iterator molIter = viewer->renList->begin();               
   for (molIter; molIter != viewer->renList->end(); molIter++) {
      mol = *molIter;
      molCount++;
      if (mol->rtti() > 11) {
         pdbError();
         return;
      }
      if (molCount > 1) {
         toManyMolError();
         return;
      }
   }   
   int ringId = dialog->ringGroup->selectedId();
   /** Ring_is Info
   *  sp3_8 = 0;
   *  sp3_7 = 1;
   *  sp3_6 = 4
   *  sp3_5 = 6
   
   *  sp2_8 = 3
   *  sp2_7 = 2
   *  sp2_6 = 5
   *  sp2_5 = 7
   */
    
   int ringIndex = ringIdToVecPos(ringId);
   //First check for the case of no current molecule     
   molecule *ring = new molecule;
   *ring = *frags[ringIndex];
   //perturb the atoms slightly so that the stick model works
   float perturb = .001;
   for (int i=0; i<ring->atoms.size(); i++) {
      float *cd = ring->atoms[i]->fCoords;
      int num = rand() % 2;
      cd[2] += perturb;
      perturb += .001;
    }
    
    //Check for the default case of no molecule currently present
    if (viewer->renList->size() == 0) {
      viewer->listView->addMolecule(ring);
      return;
    }  
    
   atom *currAtom = NULL;
   bond *currBd = NULL;
   currSelection(currAtom, currBd);
   
   if (currBd) {
      int order = currBd->getOrder();
      addRingToBond(ring, currBd);
   }
   else if (currAtom) {
      addRingToAtom(ring, currAtom);
   }

   #ifdef BUILDER_COMMENT
      cout <<"Leaving builder::ringMode"<<endl;
   #endif
}

void builder::addRingToBond(molecule *ring, bond *currBd) {
   #ifdef BUILDER_COMMENT
      cout <<"builder::addRingToBond  "<< ring->atoms.size() << endl;
   #endif

   atom *rAttach, *rAlign, *alignAtom;
   rAttach = rAlign = alignAtom = NULL;
   
   vector<float> atp(3), alp(3); //atp = atatch point...... alp = align point
   
   getRingAtoms(ring, rAttach, rAlign);
   getAttachPoints(currBd->fromAtom(), alignAtom, atp, alp);
   orientRing(ring, rAttach, rAlign, atp, alp);
   
   getRingAtoms(ring, rAttach, rAlign, currBd);

   //This section sets the attach points;
   for (int i=0; i<3; i++) {
      atp[i] = currBd->from->fCoords[i];
      alp[i] = currBd->to->fCoords[i];
   }

   orientRing(ring, rAttach, rAlign, atp, alp);

   molecule *mol = dynamic_cast<molecule *>(currBd->getParent());

   combineMoleculesBondAdd(ring, rAttach, rAlign, mol, currBd->from, currBd->to);


   vector<atom *> angAtoms;
   atom *mid = NULL;
   getLastRotAtoms(angAtoms, rAttach, rAlign, mid);
   finalRot(ring, angAtoms, rAttach, rAlign, mid);
   #ifdef BUILDER_COMMENT
      cout <<"Leaving builder::addRingToBond"<<endl;
   #endif
}


void builder::finalRot(molecule *ring, vector<atom *> &angAtoms, atom *rAttach, atom *rAlign, atom *mid) 
{
   #ifdef BUILDER_COMMENT
      cout <<"builder::finalRot"<<endl;
      cout <<"rAlign->getNum(): " << rAlign->getNum() << endl;
      cout <<"rAttach->getNum(): " << rAttach->getNum() << endl;
   #endif
   //First we need our axis of rotation;  
   vector<float> axis(3);
   for (int i=0; i<3; i++) {
      axis[i] = rAlign->fCoords[i] - rAttach->fCoords[i];
   }
   
     
   vector<float> Angles;
   for (int i=0; i<angAtoms.size(); i++) {
      for (int j=i+1; j<angAtoms.size(); j++) {
         float angle = angleDegrees(angAtoms[i]->fCoords, mid->fCoords, angAtoms[j]->fCoords);
         Angles.push_back(angle);
      }
   }
   float rotInc = .05;
   float best = -100000;
   
   if (Angles.size() == 1) {
      best = Angles[0];
   }
   
   rotInc = 0.0174532925;
   for (float i=0; i<370; i++) {
      
      vector<float> rotM(16);
    
      QUAT q(rotInc, &axis[0]);
      q.buildMatrix(&rotM[0]);
      for (int k=0; k<ring->atoms.size(); k++) {
         atom *atm = ring->atoms[k]; 
	 vector<float> coords(4);
	 for (int j=0; j<3; j++) {
            coords[j] = atm->fCoords[j]-rAttach->fCoords[j];
         }
         
	 coords[3] = 1.0;
	 vector<float> newCoords(4);
         
   	 multTransMatrix_4(newCoords, coords, rotM); 
	 
	 for (int j=0; j<3; j++) {
	    atm->fCoords[j] = newCoords[j]+rAttach->fCoords[j];
	 }
         
      }
  
      float minAngle = 1000;
      for (int i=0; i<angAtoms.size(); i++) {
         for (int j=i+1; j<angAtoms.size(); j++) {
            float angle = angleDegrees(angAtoms[i]->fCoords, mid->fCoords, angAtoms[j]->fCoords);

            if (angle < minAngle) {
            minAngle = angle;
            }
         }
      }
      
      if (minAngle >= best) {
         best = minAngle;
      } else {
         rotInc = -rotInc;
      }
   }

   #ifdef BUILDER_COMMENT
      cout <<"Leaving builder::finalRot"<<endl;
   #endif
}

void builder::getLastRotAtoms(vector<atom *> &angAtoms, atom *rAttach, atom *rAlign, atom *&mid) {
      
   atom *finRot1, *finRot2;
   finRot1 = finRot2 = NULL;
   
   vector<atom *> nonH1, nonH2;
   for (int i=0; i<rAttach->atoms.size(); i++) {
      atom *atm = rAttach->atoms[i];
      if (atm->getAtomicNum() != 1 && atm != rAlign) {
         nonH1.push_back(atm);
      }
   }   
   for (int i=0; i<rAlign->atoms.size(); i++) {
      atom *atm = rAlign->atoms[i];
      if (atm->getAtomicNum() != 1 && atm != rAttach) {
         nonH2.push_back(atm);
      }
   }
   if (nonH1.size() >= nonH2.size()) {
      angAtoms = nonH1;
      mid = rAttach;
   } else {
      angAtoms = nonH2;   
      mid = rAlign;
   }
}


void builder::combineMoleculesBondAdd(molecule *ring, atom *ra, atom *rl, molecule *mol, atom *currAtom, atom *alignAtom) 
{
   #ifdef BUILDER_COMMENT
      cout <<"builder::combineMoleculesBondAdd"<<endl;
      for (int i=0; i<ring->atoms.size(); i++)
         cout << ring->atoms[i]->getBase() <<"\t"<<ring->atoms[i]->getSymbol()<< endl;
      cout <<"Do those make sense?"<<endl;
      //int tst = 0; cin >> tst;
   #endif

   vector<atom *> HToDel2;
   for (int i=0; i<ra->atoms.size(); i++) {
      atom *atm = ra->atoms[i];
      if (atm->getAtomicNum() == 1)
         HToDel2.push_back(atm);
   }

   for (int i=0; i<rl->atoms.size(); i++) {
      atom *atm = rl->atoms[i];
      if (atm->getAtomicNum() == 1)
         HToDel2.push_back(atm);
   }
   TrashCan t32(HToDel2);
   t32.empty();
   HToDel2.clear();

   renumberRing(ring, mol);

   for (int i=0; i<ring->atoms.size(); i++) {
      atom *atm = ring->atoms[i];
      atm->setParent(mol);
      mol->atoms.push_back(atm);
   }
   
   viewer->listView->addNewAtom(ring->atoms, mol);
   for (int i=0; i<ring->bonds.size(); i++) {
      bond *bd = ring->bonds[i];
      bd->setParent(mol);
      mol->bonds.push_back(bd);
   }
   
   for (int i=0; i<currAtom->atoms.size(); i++) {
      atom *atm = currAtom->atoms[i];
      bond *bd = mol->getBond(currAtom, atm);
      mol->addBond(mol->bonds.size()+1, atm->getNum(), ra->getNum(), bd->getOrder());
   }
   
   for (int i=0; i<alignAtom->atoms.size(); i++) {
      atom *atm = alignAtom->atoms[i];
      bond *bd = mol->getBond(alignAtom, atm);
      mol->addBond(mol->bonds.size()+1, atm->getNum(), rl->getNum(), bd->getOrder());
   }
   
   bool alignIsH = false;
   bool currIsH = false;
   if (alignAtom->getAtomicNum() == 1)
   	alignIsH = true;
   if (currAtom->getAtomicNum() == 1) 
   	currIsH = true;
	
   vector<atom *> HToDel;
   vector<atom *> atomToKeep;
   for (int i=0; i<ra->atoms.size(); i++) {
      atom *atm = ra->atoms[i];
      if (atm->getAtomicNum() == 1) 
         HToDel.push_back(atm);
   }

   for (int i=0; i<rl->atoms.size(); i++) {
      atom *atm = rl->atoms[i];
      if (atm->getAtomicNum() == 1) 
         HToDel.push_back(atm);
   }
   TrashCan t(HToDel);
   t.empty();
   HToDel.clear();
  

   if (currAtom && !currIsH) {
        HToDel.push_back(currAtom);
   }
   if (alignAtom && !alignIsH) {
        HToDel.push_back(alignAtom);
   }
   TrashCan t2(HToDel);
   t2.empty();


   bond *bd = mol->getBond(ra, rl);
   bd->setOrder(1);


   //Really need to perform on last final rotation to maximize the angle
   vector<atom *> newRingAtoms;
   for (int i=0; i<ring->atoms.size(); i++) {
      newRingAtoms.push_back(ring->atoms[i]);
   }
   ring->atoms = newRingAtoms;
   #ifdef BUILDER_COMMENT
      cout <<"Leaving builder::combineMoleculesBondAdd"<<endl;
   #endif
}

void builder::getRingAtoms(molecule *ring, atom *&ra, atom *&rl, bond *currBd) {
   #ifdef BUILDER_COMMENT
      cout <<"builder::addRingAtoms"<<endl;
   #endif
   string name = ring->getName();
   if (currBd->getOrder() == 1) {
      if (name == "sp2_5_ring") {
         ra = ring->atoms[0];
         rl = ring->atoms[2];
      } else if (name == "sp2_6_ring")  {
         ra = ring->atoms[2];
         rl = ring->atoms[4];
      } else if (name == "sp2_7_ring") {
         ra = ring->atoms[2];
         rl = ring->atoms[4];
      } else if (name == "sp2_8_ring") {
         ra = ring->atoms[0];
         rl = ring->atoms[2];
      } 
   } else  {
      if (name == "sp2_5_ring") {
         ra = ring->atoms[0];
         rl = ring->atoms[8];
      } else if (name == "sp2_6_ring")  {
         ra = ring->atoms[0];
         rl = ring->atoms[2];
      } else if (name == "sp2_7_ring") {
         ra = ring->atoms[0];
         rl = ring->atoms[2];
      } else if (name == "sp2_8_ring") {
         ra = ring->atoms[2];
         rl = ring->atoms[4];
      }
   }
   
   if (name == "sp3_5_ring") {
         ra = ring->atoms[0];
         rl = ring->atoms[3];
   } else if (name == "sp3_6_ring") {
         ra = ring->atoms[0];
         rl = ring->atoms[3];
   } else if (name == "sp3_7_ring") {
         ra = ring->atoms[0];
         rl = ring->atoms[3];
   } else if (name == "sp3_8_ring") {
         ra = ring->atoms[0];
         rl = ring->atoms[3];
  }
}

void builder::addRingToAtom(molecule *ring, atom *currAtom) {
   //ra = ring atatch.   rh = ring hydrogen
   atom *ra, *rh, *alignAtom;  
   ra = rh = alignAtom = NULL;
   
   vector<float> atp, alp; //atp = atatch point...... alp = align point
   
   getRingAtoms(ring, ra, rh);
   getAttachPoints(currAtom, alignAtom, atp, alp);
   orientRing(ring, ra, rh, atp, alp);
   
   molecule *mol = dynamic_cast<molecule *>(currAtom->getParent());
   combineMoleculesAtomAdd(ring, ra, rh, mol, currAtom, alignAtom);
}

void builder::combineMoleculesAtomAdd(molecule *ring, atom *ra, atom *rh, molecule *mol, atom *currAtom, atom *alignAtom) 
{
   vector<atom *> atomsToDel;
   /** First we renumber the ring */
   renumberRing(ring, mol);

   /** Then we add the ring atoms to mol */
   for (int i=0; i<ring->atoms.size(); i++) {
      ring->atoms[i]->setParent(mol);
      mol->atoms.push_back(ring->atoms[i]);           
   }
   
  /** Next we add the ring bonds to the mol */
   viewer->listView->addNewAtom(ring->atoms, mol);
   for (int i=0; i<ring->bonds.size(); i++) {
      ring->bonds[i]->setParent(mol);
      mol->bonds.push_back(ring->bonds[i]);
   }
 
   currAtom->setRenderType(BALL);
   //return;
   if (alignAtom) {
      mol->addBond(mol->bonds.size()+1, ra->getNum(), alignAtom->getNum(), 1);
      //delete rh;
      TrashCan t(rh);
      t.empty();
      //return;
      //delete currAtom;
   }
   else {
      vector<atom *> HToDel;
      for (int i=0; i<currAtom->atoms.size(); i++) {
         atom *atm = currAtom->atoms[i];
         bond *bd = mol->getBond(currAtom, atm);
         if (!bd) {
         }
         mol->addBond(mol->bonds.size()+1, atm->getNum(), ra->getNum(), bd->getOrder());
      }

      for (int i=0; i<ra->atoms.size(); i++) {
         atom *atm = ra->atoms[i];
         if (atm->getAtomicNum() == 1) 
		HToDel.push_back(atm);
      }
      
      for (int i=0; i<HToDel.size(); i++) {
         //delete HToDel[i];
         //atomsToDel.push_back(HToDel[i]);
      }
      TrashCan t(HToDel);
      t.empty();
      HToDel.clear();      
   }
   
   //delete currAtom;
   atomsToDel.push_back(currAtom); 
   TrashCan t(atomsToDel);
   t.empty();
}

void builder::orientRing(molecule *ring, atom *ra, atom *rh, vector<float> &atp, vector<float> &alp) 
{
   #ifdef BUILDER_COMMENT
      cout <<"builder::orientRing"<<endl;
   #endif
   /** This section translates the ring such that ra is at the atp */
   translateRing(ring, ra, atp); //bond to 3
   
   /** Now lets determine our axis of rotation */
   vector<float> axis(3);
   vector<float> cd1(3), cd2(3);
   for (int i=0; i<3; i++) {
      cd1[i] = rh->fCoords[i]-atp[i];
      cd2[i] = alp[i] - atp[i];
   }
   
   crossProd(axis, cd2, cd1);
   
   /** Now lets get our angle of rotation */
   float angle = angleRadians(rh->fCoords, ra->fCoords, &alp[0]);
   
   vector<float> rotM(16);
   
   QUAT q(angle, &axis[0]);
   q.buildMatrix(&rotM[0]);
   for (int i=0; i<ring->atoms.size(); i++) {
   	atom *atm = ring->atoms[i];
	vector<float> coords(4);
	for (int i=0; i<3; i++) {
		coords[i] = atm->fCoords[i]-ra->fCoords[i];
        }
	coords[3] = 1.0;
	vector<float> newCoords(4);
   	multTransMatrix_4(newCoords, coords, rotM); 
	
	for (int i=0; i<3; i++) {
		atm->fCoords[i] = newCoords[i]+ra->fCoords[i];
	}
   }
}

void builder::getAttachPoints(atom *currAtom, atom *&alignAtom, vector<float> &atp, vector<float> &alp) {
   #ifdef BUILDER_COMMENT
      cout <<"builder::getAttachPoints"<<endl;
   #endif
   atp.resize(3);
   alp.resize(3);
   if (currAtom->atoms.size() == 1) {
      atom *alpA = currAtom->atoms[0];
      alignAtom = alpA;
      for (int i=0; i<3; i++) {
         atp[i] = currAtom->fCoords[i];
         alp[i] = alpA->fCoords[i];
      }
      return;
   }
   
   for (int i=0; i<alp.size(); i++) {
      alp[i] = 0.0;
      atp[i] = currAtom->fCoords[i];
   }
   
   if (currAtom->atoms.size() > 1) {
      for (int i=0; i<currAtom->atoms.size(); i++) {
         atom *atm = currAtom->atoms[i];
         alp[0] += atm->fCoords[0];
         alp[1] += atm->fCoords[1];
         alp[2] += atm->fCoords[2];
      }
      
      for (int i=0; i<3; i++) 
         alp[i] /= currAtom->atoms.size();
   }
}

void builder::getRingAtoms(molecule *ring, atom *&ra, atom *&rh) {
   string name = ring->getName();
   if (name == "sp2_5_ring") {
      ra = ring->atoms[2];
      rh = ring->atoms[3];
   } else if (name == "sp2_6_ring")  {
      ra = ring->atoms[0];
      rh = ring->atoms[1];
   } else if (name == "sp2_7_ring") {
      ra = ring->atoms[0];
      rh = ring->atoms[1];
   } else if (name == "sp2_8_ring") {
      ra = ring->atoms[0];
      rh = ring->atoms[1];
   } else if (name == "sp3_5_ring") {
      ra = ring->atoms[0];
      rh = ring->atoms[1];
   } else if (name == "sp3_6_ring") {
      ra = ring->atoms[0];
      rh = ring->atoms[1];
   } else if (name == "sp3_7_ring") {
      ra = ring->atoms[0];
      rh = ring->atoms[1];
   } else if (name == "sp3_8_ring") {
      ra = ring->atoms[0];
      rh = ring->atoms[1];
   }
}
/*
void builder::addRingToAtom(molecule *ring, atom *currAtom) {
   string name = ring->getName();
   int index = -1;
   
   molecule *mol = dynamic_cast<molecule *>(currAtom->getParent());
   renumberRing(ring, mol); 
   int numOfAtoms = currAtom->atoms.size();
   QString qName = ring->getName();
   if (qName.contains("sp2") ) {
      sp2Orient(ring, currAtom);
   } else
   if (qName.contains("sp3") ) {
      sp3Orient(ring, currAtom);
   }
   
   bondAtomToAtom(ring, mol);
}

*/

void builder::sp2Orient(molecule *ring, atom *currAtom) {
   string name = ring->getName();
    
   atom *ringAtomToDel = NULL;
   atom *molAtomToDel = NULL; 
   /** This section takes care of translation */
   if (name == "sp2_5_ring") {
      translate(ring, ring->atoms[2], currAtom); //bond to 3
      orient(ring, ring->atoms[3], currAtom, ring->atoms[2]);
   } else if (name == "sp2_6_ring")  {
      translate(ring, ring->atoms[0], currAtom);
      orient(ring, ring->atoms[1], currAtom, ring->atoms[0]);
   } else if (name == "sp2_7_ring") {
      translate(ring, ring->atoms[0], currAtom);
      orient(ring, ring->atoms[1], currAtom, ring->atoms[0]);
   } else if (name == "sp2_8_ring") {
      translate(ring, ring->atoms[0], currAtom);
      orient(ring, ring->atoms[1], currAtom, ring->atoms[0]);
   }
   /** Now for the much harder part...reorienting molecule */
}
void builder::orient(molecule *mol, atom *delAtom, atom *currAtom, atom *ringAP) {
   int test = 0; cin >> test;
   //we are going to orient 'mol' so that it's delAtom points at or overlays
   // with the bondAtom
   if (currAtom->atoms.size() == 0) return;
   atom *currHold = currAtom;
   currAtom = currAtom->atoms[0];
   vector<float> axis(3);
   vector<float> cd1(3), cd2(3);
   vector<float> rotM(16);
   for (int i=0; i<3; i++) {
      cd1[i] = delAtom->fCoords[i] - ringAP->fCoords[i];
      cd2[i] = currAtom->fCoords[i] - ringAP->fCoords[i];
   }
   crossProd(axis, cd2, cd1);
   float angle = angleRadians(currAtom->fCoords, ringAP->fCoords, delAtom->fCoords);
   
   QUAT q(angle, &axis[0]);
   q.buildMatrix(&rotM[0]);
   for (int i=0; i<mol->atoms.size(); i++) {
   	atom *atm = mol->atoms[i];
	vector<float> coords(4);
	for (int i=0; i<3; i++) {
		coords[i] = atm->fCoords[i]-ringAP->fCoords[i];
        }
	coords[3] = 1.0;
	vector<float> newCoords(4);
   	multTransMatrix_4(newCoords, coords, rotM); 
	
	for (int i=0; i<3; i++) {
		atm->fCoords[i] = newCoords[i]+ringAP->fCoords[i];
	}
   }

   //Now lets reassign the currAtom and then add the ring atoms
   currAtom = currHold;
   int size = ringAP->atoms.size();
   int tt = 0; cin >> tt;
   delete delAtom;
   
   for (int i=0; i<ringAP->atoms.size(); i++) {
	currAtom->atoms.push_back(ringAP->atoms[i]);
	ringAP->atoms[i]->atoms.push_back(currAtom);
	mol->addBond(mol->bonds.size()+1, currAtom->getNum(), ringAP->atoms[i]->getNum(), 1);
   }
   delete ringAP;
}

void builder::translateRing(molecule *ring, atom *ra, vector<float> &atp) {
   float xTrans = atp[0] - ra->fCoords[0];
   float yTrans = atp[1] - ra->fCoords[1];
   float zTrans = atp[2] - ra->fCoords[2];
   
   for (int i=0; i<ring->atoms.size(); i++) {
      atom *tmpAtm = ring->atoms[i];
      tmpAtm->fCoords[0] += xTrans;
      tmpAtm->fCoords[1] += yTrans;
      tmpAtm->fCoords[2] += zTrans;
   }
}

void builder::translate(molecule *mol, atom *atm1, atom *atm2) {
   float *cd1 = atm1->fCoords;
   float *cd2 = atm2->fCoords;
   float xTrans = cd2[0] - cd1[0];
   float yTrans = cd2[1] - cd1[1];
   float zTrans = cd2[2] - cd1[2];
   
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *tmpAtm = mol->atoms[i];
      float *cd3 = tmpAtm->fCoords;
      cd3[0] += xTrans;
      cd3[1] += yTrans;
      cd3[2] += zTrans; 
   }

}

void builder::sp3Orient(molecule *ring, atom *currAtom) {
}

void builder::renumberRing(molecule *ring, molecule *mol) {
  int atomNum = mol->atoms.size()+1;
  for (int i=0; i<ring->atoms.size(); i++) {
      ring->atoms[i]->setNum(atomNum);
      atomNum++;
  }
}

void builder::bondAtomToAtom(molecule *ring, molecule *mol) {
   for (int i=0; i<ring->atoms.size(); i++) {
      ring->atoms[i]->setParent(mol);
      mol->atoms.push_back(ring->atoms[i]);
   }
   
   //Now lets tell the list view all about it.
   viewer->listView->addNewAtom(ring->atoms, mol);
   
   for (int i=0; i<ring->bonds.size(); i++) {
      mol->bonds.push_back(ring->bonds[i]);
   }
}

void builder::addToAtomHDel(molecule *ring) {
   string name = ring->getName();
   /** This first section deletes all the hydrogens */
// TrashCan *t;
   if (name == "sp2_5_ring")
      delete ring->atoms[3]; //bond to 3
   else if (name == "sp2_6_ring") 
      delete ring->atoms[1]; //bond to 1
   else if (name == "sp2_7_ring")
      delete ring->atoms[1]; //bond to 1
   else if (name == "sp2_8_ring")
      delete ring->atoms[1]; //bond to 1
   else if (name == "sp3_5_ring")
      delete ring->atoms[1]; //bond to 1
   else if (name == "sp3_6_ring")
      delete ring->atoms[1]; //bond to 1
   else if (name == "sp3_7_ring")
      delete ring->atoms[1]; //bond to 1
   else if (name == "sp3_8_ring")
      delete ring->atoms[1]; //bond to 1
   
}  

int builder::ringIdToVecPos(int ringId) {
   if (ringId == 0) return 7;
   if (ringId == 1) return 6;
   if (ringId == 2) return 2;
   if (ringId == 3) return 3;
   if (ringId == 4) return 5;
   if (ringId == 5) return 1;
   if (ringId == 6) return 4;
   if (ringId == 7) return 0;
}

void builder::createLoneAtom(QString sym, int AN) {
   int molCount = 0;
   molecule *mol;
   list<molecule *>::iterator molIter = viewer->renList->begin();               
   for (molIter; molIter != viewer->renList->end(); molIter++) {
      mol = *molIter;
      molCount++;
      if (mol->rtti() > 11) {
         pdbError();
         return;
      }
      if (molCount > 1) {
         toManyMolError();
         return;
      }
   }
 
   
   int atomNum = mol->atoms.size()+1;
   atom *atm = mol->addAtom(atomNum, sym, currSpot[0], currSpot[1], currSpot[2], AN);
   viewer->addSphere(currSpot[0], currSpot[1], currSpot[2],
                     0.75, wire, 0.0, 1.0, 0.2);
   viewer->listView->addNewAtom(atm, mol);
   prevAtom = atm;
}

void builder::noMolecule() {
   //now lets figure out what sort of atom we are drawing
   QString aType = dialog->otherAtom->currentText();
   QString sym;
   int AN;
   getType(aType, sym, AN);
   molecule *mol = new molecule;
   prevAtom = mol->addAtom(1, sym, 0.01, -0.01, -25.0, AN);
   viewer->addSphere(0.0, 0.0, -25.0,
                     0.75, wire, 0.0, 1.0, 0.2);
   viewer->listView->addMolecule(mol);
}

bool builder::wasPrevAtom() {
   if (!prevAtom) return false;
   float *cd = prevAtom->fCoords;
   if (cd[0] == currSpot[0] && cd[1] == currSpot[1] && cd[2] == currSpot[2]) {
      return true;
   }
   
   return false;
    
}

void builder::createAndBondAtom(QString &sym, int AN, int bOrder) {
   if (!prevAtom) return; 
   
   
   molecule *mol = dynamic_cast<molecule *>(prevAtom->lastParent());
   if (mol->rtti() > 11) {
      pdbError();
      prevAtom = NULL;
      return;
   }
   int atomNum = mol->atoms.size()+1;
   float z = prevAtom->fCoords[2];
   int ran = rand() %2;
   float num;
   if (ran == 1) num = .01;
   if (ran == 0) num = -0.01;
   //atom *atm = mol->addAtom(atomNum, sym, currSpot[0], currSpot[1], z+num, AN);
   atom *atm = mol->addAtom(atomNum, sym, currSpot[0], currSpot[1], currSpot[2]+num, AN);
   mol->addBond(mol->bonds.size()+1, prevAtom->getNum(), atomNum, bOrder);
   //viewer->addSphere(currSpot[0], currSpot[1], z,
                    // 0.25, wire, 0.0, 1.0, 0.2);
                    
   viewer->addSphere(currSpot[0], currSpot[1], currSpot[2]+num,
                     0.75, wire, 0.0, 1.0, 0.2);
   viewer->listView->addNewAtom(atm, mol);
   prevAtom = atm;
}

void builder::bondAtoms(atom *prevAtom, atom *currAtom, int bOrder) {
   if (!prevAtom || !currAtom) return;
   molecule *mol = dynamic_cast<molecule *>(prevAtom->lastParent());
   molecule *mol2 = dynamic_cast<molecule *>(currAtom->lastParent());
   if (mol != mol2) {
      diffMolError();
      return;
   }
   
   if (mol->rtti() > 11) {
      pdbError();
      prevAtom = NULL;
      return;
   }
   
  
   mol->addBond(mol->bonds.size()+1, prevAtom->getNum(), currAtom->getNum(), bOrder);
}

void builder::addToAtom(atom *atm) {
    
}

void builder::addToBond(bond *bd) {

}

void builder::addH() {
   if (!ENABLE) return;
   interfaceOff();
   
   list<molecule *>::iterator molIter = viewer->renList->begin();               
   for (molIter; molIter != viewer->renList->end(); molIter++) {
      molecule *mol = *molIter;
      if (mol->rtti() > 11) {
         pdbError();
         return;
      }
   }
   
   viewer->SPHERES.clear();
   prevAtom = NULL;
   dynoThread *thread = viewer->modelView->addHydrogens("PARTIAL");
   
   connect(thread, SIGNAL(threadDone()), this, SLOT(interfaceOn()));
}

void builder::delH() {
   if (!ENABLE) return;
   vector<atom *> atomsToDel;
   list<molecule *>::iterator molIter = viewer->renList->begin();               
   for (molIter; molIter != viewer->renList->end(); molIter++) {
      molecule *mol = *molIter;
      if (mol->rtti() > 11) {
         pdbError();
         return;
      }
      for(int i=0; i<mol->atoms.size(); i++) {
         atom *atm = mol->atoms[i];
         if (atm->getAtomicNum() == 1)
            atomsToDel.push_back(atm);
      }
   }
  
   TrashCan t(atomsToDel);
   t.empty();
   /* 
   for (int i=0; i<atomsToDel.size(); i++) { 
      delete atomsToDel[i];
   }
   */
   viewer->SPHERES.clear();
   prevAtom = NULL;
   viewer->updateGL();
}

void builder::clean() {
   if (!ENABLE) return;
   interfaceOff();
   list<molecule *>::iterator molIter = viewer->renList->begin();               
   for (molIter; molIter != viewer->renList->end(); molIter++) {
      molecule *mol = *molIter;
      if (mol->rtti() > 11) {
         pdbError();
         return;
      }
      if (!checkStructure(mol) ) return;
      
      //Now reset all the forcefield and charge stuff
      mol->chargeType = "NONE";
      mol->ffTypes    = "NONE";
      for (int i=0; i<mol->atoms.size(); i++) {
         atom *atm = mol->atoms[i];
         atm->setFFType("*");
      }
   }
   
   prevAtom = NULL;
   viewer->SPHERES.clear();
  
   QString jobName = "Clean";
   QString minMethod = "CG";
   QString ffType = "GAFF";
   QString chargeType = "Current";
   QString dielectric = "Constant";
   float dieValue = 80.0;
   float maxForce = 0.0;
   float rmsef = 0.0;
   float minEDiff = 0.0;
   viewer->molEditMode = false;
   dynoThread *thread = viewer->modelView->MMmin(jobName, minMethod, ffType, chargeType, dielectric, dieValue, 500, rmsef, maxForce, minEDiff);
   
   viewer->molEditMode = true;
   connect(thread, SIGNAL(threadDone()), this, SLOT(interfaceOn()));
}

void builder::interfaceOn() {
   ENABLE = true;   
}

void builder::interfaceOff() {
   ENABLE = false;
}

bool builder::checkStructure(molecule *mol) {
   if (!hCheck(mol)) return false;
   return true;
}
bool builder::hCheck(molecule *mol) {
   //real quick pass to see if there are any H's
   bool someH = false;
   for (int i=0; i<mol->atoms.size(); i++) {
      if (mol->atoms[i]->getAtomicNum() == 1) {
         someH = true;
         break;
      }
   }
   if (!someH) {
      hError();
      return false;
   }
   return true;
}
void builder::hError() {
   QString error = "You must add H's before you clean the structure";
   QMessageBox::critical( 0, "Dynamol",error);
}

void builder::pdbError() {
   QString error = "When working with PDB file's you may only change bond\n";
   error += "orders and delete atoms.  Adding new atoms or bonds is not supported.\n";
   error += "If you must make these changes then you should save the current\n";
   error += "structures as a mol2 file and then reload it. Sorry for the\n";
   error += "inconvenience";
   QMessageBox::critical( 0, "Dynamol",error);
}

void builder::toManyMolError() {
   QString error = "When more than one molecule is present you must begin\n";
   error += "your sketch from another atom.\n";
   QMessageBox::critical( 0, "Dynamol",error);
}

void builder::diffMolError() {
   QString error = "Bonds may only be formed between atoms in the same moelcule";
   QMessageBox::critical( 0, "Dynamol",error);
}













































void builder::getType(const QString aType, QString &sym, int &AN) 
{
if (aType == "Actinium") {
sym = "Ac";
}
else
if (aType == "Silver") {
sym = "Ag";
}
else
if (aType == "Aluminum") {
sym = "Al";
}
else
if (aType == "Americium") {
sym = "Am";
}
else
if (aType == "Argon") {
sym = "Ar";
}
else
if (aType == "Arsenic") {
sym = "As";
}
else
if (aType == "Astatine") {
sym = "At";
}
else
if (aType == "Gold") {
sym = "Au";
}
else
if (aType == "Boron") {
sym = "B";
}
else
if (aType == "Barium") {
sym = "Ba";
}
else
if (aType == "Beryllium") {
sym = "Be";
}
else
if (aType == "Bohrium") {
sym = "Bh";
}
else
if (aType == "Bismuth") {
sym = "Bi";
}
else
if (aType == "Berkelium") {
sym = "Bk";
}
else
if (aType == "Bromine") {
sym = "Br";
}
else
if (aType == "Carbon") {
sym = "C";
}
else
if (aType == "Calcium") {
sym = "Ca";
}
else
if (aType == "Cadmium") {
sym = "Cd";
}
else
if (aType == "Cerium") {
sym = "Ce";
}
else
if (aType == "Californium") {
sym = "Cf";
}
else
if (aType == "Chlorine") {
sym = "Cl";
}
else
if (aType == "Curium") {
sym = "Cm";
}
else
if (aType == "Cobalt") {
sym = "Co";
}
else
if (aType == "Chromium") {
sym = "Cr";
}
else
if (aType == "Cesium") {
sym = "Cs";
}
else
if (aType == "Copper") {
sym = "Cu";
}
else
if (aType == "Dubnium") {
sym = "Db";
}
else
if (aType == "Darmstadtium") {
sym = "Ds";
}
else
if (aType == "Dysprosium") {
sym = "Dy";
}
else
if (aType == "Erbium") {
sym = "Er";
}
else
if (aType == "Einsteinium") {
sym = "Es";
}
else
if (aType == "Europium") {
sym = "Eu";
}
else
if (aType == "Fluorine") {
sym = "F";
}
else
if (aType == "Iron") {
sym = "Fe";
}
else
if (aType == "Fermium") {
sym = "Fm";
}
else
if (aType == "Francium") {
sym = "Fr";
}
else
if (aType == "Gallium") {
sym = "Ga";
}
else
if (aType == "Gadolinium") {
sym = "Gd";
}
else
if (aType == "Germanium") {
sym = "Ge";
}
else
if (aType == "Hydrogen") {
sym = "H";
}
else
if (aType == "Helium") {
sym = "He";
}
else
if (aType == "Hafnium") {
sym = "Hf";
}
else
if (aType == "Mercury") {
sym = "Hg";
}
else
if (aType == "Holmium") {
sym = "Ho";
}
else
if (aType == "Hassium") {
sym = "Hs";
}
else
if (aType == "Iodine") {
sym = "I";
}
else
if (aType == "Indium") {
sym = "In";
}
else
if (aType == "Iridium") {
sym = "Ir";
}
else
if (aType == "Potassium") {
sym = "K";
}
else
if (aType == "Krypton") {
sym = "Kr";
}
else
if (aType == "Lanthanum") {
sym = "La";
}
else
if (aType == "Lithium") {
sym = "Li";
}
else
if (aType == "Lawrencium") {
sym = "Lr";
}
else
if (aType == "Lutetium") {
sym = "Lu";
}
else
if (aType == "Mendelevium") {
sym = "Md";
}
else
if (aType == "Magnesium") {
sym = "Mg";
}
else
if (aType == "Manganese") {
sym = "Mn";
}
else
if (aType == "Molybdenum") {
sym = "Mo";
}
else
if (aType == "Meitnerium") {
sym = "Mt";
}
else
if (aType == "Nitrogen") {
sym = "N";
}
else
if (aType == "Sodium") {
sym = "Na";
}
else
if (aType == "Neon") {
sym = "Ne";
}
else
if (aType == "Niobium") {
sym = "Nb";
}
else
if (aType == "Neodymium") {
sym = "Nd";
}
else
if (aType == "Nickel") {
sym = "Ni";
}
else
if (aType == "Nobelium") {
sym = "No";
}
else
if (aType == "Neptunium") {
sym = "Np";
}
else
if (aType == "Oxygen") {
sym = "O";
}
else
if (aType == "Osmium") {
sym = "Os";
}
else
if (aType == "Phosphorus") {
sym = "P";
}
else
if (aType == "Palladium") {
sym = "Pd";
}
else
if (aType == "Polonium") {
sym = "Po";
}
else
if (aType == "Lead") {
sym = "Pb";
}
else
if (aType == "Platinum") {
sym = "Pt";
}
else
if (aType == "Praseodymium") {
sym = "Pr";
}
else
if (aType == "Promethium") {
sym = "Pm";
}
else
if (aType == "Plutonium") {
sym = "Pu";
}
else
if (aType == "Protactinium") {
sym = "Pa";
}
else
if (aType == "Radium") {
sym = "Ra";
}
else
if (aType == "Rubidium") {
sym = "Rb";
}
else
if (aType == "Rhenium") {
sym = "Re";
}
else
if (aType == "Rutherfordium") {
sym = "Rf";
}
else
if (aType == "Rhodium") {
sym = "Rh";
}
else
if (aType == "Radon") {
sym = "Rn";
}
else
if (aType == "Ruthenium") {
sym = "Ru";
}
else
if (aType == "Sulfur") {
sym = "S";
}
else
if (aType == "Antimony") {
sym = "Sb";
}
else
if (aType == "Scandium") {
sym = "Sc";
}
else
if (aType == "Selenium") {
sym = "Se";
}
else
if (aType == "Seaborgium") {
sym = "Sg";
}
else
if (aType == "Silicon") {
sym = "Si";
}
else
if (aType == "Samarium") {
sym = "Sm";
}
else
if (aType == "Tin") {
sym = "Sn";
}
else
if (aType == "Strontium") {
sym = "Sr";
}
else
if (aType == "Tantalum") {
sym = "Ta";
}
else
if (aType == "Terbium") {
sym = "Tb";
}
else
if (aType == "Technetium") {
sym = "Tc";
}
else
if (aType == "Tellurium") {
sym = "Te";
}
else
if (aType == "Thorium") {
sym = "Th";
}
else
if (aType == "Titanium") {
sym = "Ti";
}
else
if (aType == "Thallium") {
sym = "Tl";
}
else
if (aType == "Thulium") {
sym = "Tm";
}
else
if (aType == "Uranium") {
sym = "U";
}
else
if (aType == "Ununbium") {
sym = "Uub";
}
else
if (aType == "Ununnilium") {
sym = "Uun";
}
else
if (aType == "Ununumium") {
sym = "Uuu";
}
else
if (aType == "Vanadium") {
sym = "V";
}
else
if (aType == "Tungsten") {
sym = "W";
}
else
if (aType == "Xenon") {
sym = "Xe";
}
else
if (aType == "Yttrium") {
sym = "Y";
}
else
if (aType == "Ytterbium") {
sym = "Yb";
}
else
if (aType == "Zinc") {
sym = "Zn";
}
else
if (aType == "Zirconium") {
sym = "Zr";
}
   AN = molDB::SYM2AN(sym); 
}

























