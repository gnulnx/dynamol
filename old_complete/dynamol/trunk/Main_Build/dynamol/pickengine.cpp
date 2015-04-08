/***************************************************************************
                          pickengine.cpp  -  description
                             -------------------
    begin                : Mon Mar 8 2004 Dynamol 
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "pickengine.h"
#include "molview.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"

pickEngine::pickEngine(molView *viewer){
  this->viewer = viewer;
  atm1 = atm2 = atm3 = atm4;
}
pickEngine::~pickEngine(){
}

void  pickEngine::getHitObjectNumbers(vector<int> &nums, GLint hits, GLuint buffer[]) {
  nums.clear();
  atom *tmpAtm;
  int tester = 0;
  int bufferInt = 0;
  for (int i=0; i<hits; i++) {
    int numOfHits = buffer[ bufferInt ];
    bufferInt++; //zMin
    bufferInt++; //zMax
    if (numOfHits > 0) {
      for (int j=0; j<numOfHits; j++) {
        bufferInt++;
        nums.push_back( buffer[bufferInt] );
      }
      bufferInt++;
    } else bufferInt++;
  }
}


//void pickEngine::processHits(GLint hits, GLuint buffer[], mouseSensor::button_state shiftState, mouseSensor::button_state ctrlState) {
void pickEngine::processHits(GLint hits, GLuint buffer[], int shiftState, int ctrlState) {
  //First get alist of the object numbers from the hit list.
  //All atoms. bond. && molecules have a unique object number
  //cout <<"pickEngine::processHits"<<endl;
  list<molecule *>::iterator molIterator;
  molecule *mol = NULL;
  vector<int> objectNums;

  getHitObjectNumbers(objectNums, hits, buffer);
  //cout <<"After getHitObjectNums"<<endl;
 //Now check to see if we can deselect everything && return
 //This is done if no atoms are selected && both the control && shift keys are up
  bool returnCond = false;
  
  
  /*     
  if (objectNums.size() == 0 && shiftState == mouseSensor::UP && ctrlState == mouseSensor::UP) {
    for (molIterator = viewer->renList->begin(); molIterator != viewer->renList->end(); molIterator++) {
        mol=*molIterator;
        mol->setSelected(false, true);
        for (int i=0; i<mol->bonds.size(); i++) {
           mol->bonds[i]->setSelected(false);
        }
        ////////////cout <<"HERE 1"<<endl;
        returnCond = true;
	viewer->selFullMol = false;
    }
  } 
  */
  //cout <<"pick A"<<endl;
  if (objectNums.size() == 0) {
    for (molIterator = viewer->renList->begin(); molIterator != viewer->renList->end(); molIterator++) {
        mol=*molIterator;
        mol->setSelected(false, true);
        for (int i=0; i<mol->bonds.size(); i++) {
           mol->bonds[i]->setSelected(false);
        }
	viewer->selFullMol = false;
    } 
    viewer->updateGL();
    return;
  }
  //cout <<"Pick B"<<endl;
  if (shiftState == mouseSensor::UP && ctrlState == mouseSensor::UP) {
   for (molIterator = viewer->renList->begin(); molIterator != viewer->renList->end(); molIterator++) {
        mol=*molIterator;
        //mol->setSelected(false, true);
        for (int i=0; i<mol->bonds.size(); i++) {
           mol->bonds[i]->setSelected(false);
        }
        //////////////cout <<"HERE 2"<<endl;
        //returnCond = true;
	//viewer->selFullMol = false;
    }
  }
  //cout <<"Pick C"<<endl;

  /*
  for (molIterator = viewer->renList->begin(); molIterator != viewer->renList->end(); molIterator++) {
        mol=*molIterator;
        mol->setSelected(false, true);
        for (int i=0; i<mol->bonds.size(); i++) {
           mol->bonds[i]->setSelected(false);
        }
        //returnCond = true;
	viewer->selFullMol = false;
   }
    */
  if (returnCond) {
      viewer->updateGL();
      return;
  }
  //cout <<"Pick D"<<endl;
  //Now lets get a list of all the atoms in the hit list.
  //This list will then be further processed based on shift, control, double click state combinations
  vector<atom *> selectAtoms, deSelectAtoms;
  vector<bond *> selectBonds, deSelectBonds;
  atom *atm = NULL;
  //////////////cout <<"objectNums.size(): " << objectNums.size() << endl;
  for (int i=0; i<objectNums.size(); i++) {
    //cout <<objectNums[i] << endl;
    //cout <<"Before Object::registry  " << endl;
    //cout <<"Before with num: " << objectNums[i] << endl;
   
    Object *tmp = Object::registry[ objectNums[ i ] ];
    //cout <<"After Object::registry  "<< tmp << "\t"<<Object::registry.size() << endl;
    //cout <<"tmp->rtti(): " << tmp->rtti() << endl;
    atom *atm = NULL;
    bond *bd = NULL;
    if (tmp->rtti() == 10) atm = dynamic_cast<atom *>(tmp);
    if (tmp->rtti() == 9) bd = dynamic_cast<bond *>(tmp);
    //////////////cout <<"atm  --  bd " << atm <<setw(12) << bd << endl;
    if (atm != NULL) {
      selectAtoms.push_back(atm);
      //////////////cout <<atm->bonds.size() <<"  <----------atm->bonds.size() "<<endl;
      //for (int i=0; i<atm->bonds.size(); i++) atm->bonds[i]->setSelected(false, false);
      //bd = NULL;
    }
      
    if (bd != NULL) selectBonds.push_back(bd);
    //}
  }
  //cout <<"Pick E"<<endl;
  //This should preserve atom selection
  if (selectAtoms.size() > 0) selectBonds.clear();
  
  //if double click with no shift || control  then select the atoms first parent
  if (viewer->selFullMol == true && shiftState == mouseSensor::UP && ctrlState == mouseSensor::UP) {
    //////////////cout <<"a)  shiftState == UP   &&  ctrlState == UP"<<endl;
    
    viewer->selFullMol = false;
    //Deslect all molecules first
    for (molIterator = viewer->renList->begin(); molIterator !=viewer->renList->end(); molIterator++) {
      molecule *mol = *molIterator;
      mol->setSelected(false, true);
    }
    //////////////cout <<"a) part 2: " << endl;
    for (int i=0; i<selectAtoms.size(); i++) {
      molecule *molToSelect = dynamic_cast<molecule *>(selectAtoms[i]->getParent());
      molToSelect->setSelected(true, true);
      molToSelect->item->listView()->ensureItemVisible(molToSelect->getItem());
    }
    //////////////cout <<"a) part 3: " << endl;
  }
 else //Now do a chain select by depressing the shift key && double clicking
 if (viewer->selFullMol == true && shiftState == mouseSensor::DOWN && ctrlState == mouseSensor::UP) {
    //////////////cout <<"a)  shiftState == DONW    && ctrlState == UP " << endl;
    viewer->selFullMol = false;
    //Deslect all molecules first
    for (molIterator = viewer->renList->begin(); molIterator != viewer->renList->end(); molIterator++) {
      molecule *mol = *molIterator;
      mol->setSelected(false, true);
    }
    for (int i=0; i<selectAtoms.size(); i++) {
      molecule *molToSelect = dynamic_cast<molecule *>(selectAtoms[i]->getParent());
      molecule *chainMol = dynamic_cast<molecule *>(molToSelect->getParent());
      if (chainMol != NULL) {
        chainMol->setSelected(true, true);
        chainMol->item->setSelected(true);
        chainMol->item->listView()->ensureItemVisible(chainMol->getItem());
      }
    }
  }
 else    //Now do a protein select if the control key is depressed
 if (viewer->selFullMol == true && shiftState == mouseSensor::UP && ctrlState == mouseSensor::DOWN) {
    //////////////cout <<"a)  shiftState == UP   &&   ctrlState == DOWN"<<endl;
    viewer->selFullMol = false;
    //Deslect all molecules first
    for (molIterator = viewer->renList->begin(); molIterator != viewer->renList->end(); molIterator++) {
      molecule *mol = *molIterator;
      mol->setSelected(false, true);
    }
    for (int i=0; i<selectAtoms.size(); i++) {
      molecule *molToSelect = dynamic_cast<molecule *>(selectAtoms[i]->getParent());
      molecule *chainMol = dynamic_cast<molecule *>(molToSelect->getParent());
      if (chainMol != NULL) {
        molecule *protMol = dynamic_cast<molecule *>(chainMol->getParent());
        if (protMol != NULL) {
          protMol->setSelected(true, true);
          protMol->item->listView()->ensureItemVisible(protMol->getItem());
        }
      }
    }
  }
 else
  if (shiftState == mouseSensor::DOWN && ctrlState == mouseSensor::UP) {
    //////////////cout <<"b)  shiftState == DONW    && ctrlState == UP " << endl;
    for (int i=0; i<selectAtoms.size(); i++)
      selectAtoms[i]->setSelected(true);
  }
  else
  if (shiftState == mouseSensor::UP && ctrlState == mouseSensor::DOWN) {
    //////////////cout <<"b)  shiftState == UP   &&   ctrlState == DOWN"<<endl;
    for (int i=0; i<selectAtoms.size(); i++) {
      if (selectAtoms[i]->isSelected() == false) selectAtoms[i]->setSelected(true);
      else  selectAtoms[i]->setSelected(false);
    }
  }
  else
  if (shiftState == mouseSensor::UP && ctrlState == mouseSensor::UP) {
    //////////////cout <<"b)  shiftState == UP   &&  ctrlState == UP"<<endl;
    for (molIterator = viewer->renList->begin(); molIterator != viewer->renList->end(); molIterator++) {
      molecule *mol = *molIterator;
      mol->setSelected(false, true);
    }
    for (int i=0; i<selectAtoms.size(); i++) {
      selectAtoms[ i ]->setSelected(true);
      viewer->currentSelection = selectAtoms;
    }
  }
  
  for (int i=0; i<selectBonds.size(); i++) {
     selectBonds[i]->setSelected(true);
     /*
     atom *from, *to;
     from = selectBonds[i]->fromAtom();
     to = selectBonds[i]->toAtom();
     from->setSelected(true, true);
     to->setSelected(true, true);
     */
  }

   //cout <<"Before updateRegistry"<<endl;
   Object::updateRegistry();
   //cout <<"After update Registry"<<endl;
   //////////////cout <<"Registry.size() "<< Object::registry.size() << endl;
   //////////////cout <<"Objects created: " << Object::objectCreate << endl;
   //////////////cout <<"Objects destroy: " << Object::objectDestroy << endl;
   /*
   ////////////cout <<"angles created:" << angle::angCreate << endl;
   ////////////cout <<"angles destroy: " << angle::angDelete << endl;
   ////////////cout << endl;
   ////////////cout <<"nb create: " << nonBond::nbCreate << endl;
   ////////////cout <<"nb delete: " << nonBond::nbDelete << endl;
   ////////////cout << endl;
   ////////////cout <<"tor create: " << torsion::torCreate << endl;
   ////////////cout <<"tor delete: " << torsion::torDelete << endl;
   ////////////cout << endl;
   ////////////cout << endl;
   */
   //////////////cout <<"Diff: " << Object::objectCreate - Object::registry.size() << endl;
  
}



void pickEngine::distPicks(GLint hits, GLuint buffer[] ) {
  //////////////cout <<"pickEngine::distPicks"<<endl;
  list<molecule *> *renList = viewer->renList;
 // int *angSelCounter = &viewer->angSelCounter;
  
  //initialize an iterator to the begging of the render list...
  list<molecule *>::iterator iter = viewer->renList->begin();

  //Get a list of all the object numbers from the selection buffer.
  //There must only be one number
  vector<int> objectNums;
  ////////////cout <<"hits: " << hits << setw(12) << viewer->renList->size() << endl;
  getHitObjectNumbers(objectNums, hits, buffer);
  int OBJECTNUM;
  atom *atm = NULL;
  for (int i=0; i<objectNums.size(); i++) {
    Object *tmp = Object::registry[ objectNums[ i ] ];
    atom *atm = NULL;
    bond *bd = NULL;
    if (tmp->rtti() == 10) {  
       atm = dynamic_cast<atom *>(tmp);
       OBJECTNUM = objectNums[i];
    }
  }
  //if (objectNums.size() != 1) return;
  
    //############### UNSELECT SECTION #################
  //This section
  while (iter != viewer->renList->end()) {
        molecule *tmpMol = *iter;
        for (unsigned int i=0; i<tmpMol->atoms.size(); i++) {
          atom *tmpAtom = tmpMol->atoms[i];
          if (tmpAtom->getObjectNum() == OBJECTNUM) atm = tmpAtom;
          if (tmpAtom->getItem() != NULL) tmpAtom->setSelected(false);
        }

        tmpMol->getItem()->setSelected(false);
		  iter++;
  }

  //////////////cout <<"atm: " << atm << endl;
  if (atm == NULL) return;

  if ( viewer->distSelCounter == 0) {
      atm1 = atm;
      viewer->distSelCounter++;
      atm->setSelected(true);
  } else {
      atm2 = atm;
      viewer->distSelCounter++;
  }


  if (viewer->distSelCounter == 2) {

      if ( !viewer->delDistMode ) {  //If we are in distance define mode
          //First check for intro-molecular distances
          if ( (atm1->getParent() == atm2->getParent() ) && atm1->getParent()->rtti() == 11 ) {
            molecule *mol = dynamic_cast<molecule *>(atm1->getParent());
            mol->addDistance(atm1, atm2);
            atm2->setSelected(false);
            atm1 = atm2 = NULL;
          }   else {  //It must be an inter-molecular distance
            //////////////cout <<"Adding interMolDistance"<<endl;
            vector<atom *> tmp;
            tmp.push_back(atm1);
            tmp.push_back(atm2);
            viewer->interMolDist.push_back(tmp);
            atm2->setSelected(false);
            atm1 = atm2 = atm3 = atm4 = NULL;
          }
      }  else {  //now were are in distance delete mode
            if ( (atm1->getParent() == atm2->getParent() ) && atm1->getParent()->rtti() == 11 ) {   //intraMolDist deeletion
                molecule *mol = dynamic_cast<molecule *>(atm1->getParent());
                mol->delDistance(atm1, atm2);
                atm2->setSelected(false);
                atm1 = atm2 = atm3 = atm4 = NULL;
            } else {//interMolDist deleteion
               viewer->delInterMolDist(atm1, atm2);
               atm2->setSelected(false);
               atm1 = atm2 = atm3 = atm4 = NULL;
            }
      }
      viewer->setCursor(QCursor(Qt::ArrowCursor) );
      viewer->distMode = false;
      viewer->delDistMode = false;
      viewer->angMode = false;
      viewer->delAngMode = false;
      viewer->torsionMode = false;
      viewer->delTorsionMode = false;

      viewer->distSelCounter = 0;
      viewer->angSelCounter = 0;
      viewer->torsionSelCounter = 0;

      viewer->atm1 = viewer->atm2  = viewer->atm3 = viewer->atm4 = NULL;
  }
  //glInitNames();
}

void pickEngine::angPicks(GLint hits, GLuint buffer[]) {
  list<molecule *> *renList = viewer->renList;
  //int *angSelCounter = &viewer->angSelCounter;
  
  list<molecule *>::iterator iter = renList->begin();

  atom *atm = NULL;
  vector<int> objectNums;
  getHitObjectNumbers(objectNums, hits, buffer);
  int OBJECTNUM;
  for (int i=0; i<objectNums.size(); i++) {
    Object *tmp = Object::registry[ objectNums[ i ] ];
    atom *atm = NULL;
    if (tmp->rtti() == 10) {  
       atm = dynamic_cast<atom *>(tmp);
       OBJECTNUM = objectNums[i];
    }
  }
  //////////////cout <<"The number of Hits is: " << hits <<  endl;

  if (hits == 0) return; //once you add the distance line...it shows up as 2 hits...messed up...don't like it not one little bit.

    //############### UNSELECT SECTION #################
  while (iter != viewer->renList->end()) {
        molecule *tmpMol = *iter;
        for (unsigned int i=0; i<tmpMol->atoms.size(); i++) {
          atom *tmpAtom = tmpMol->atoms[i];
          if (tmpAtom->getObjectNum() == OBJECTNUM) atm = tmpAtom;
          if (viewer->angSelCounter == 2)
            if (tmpAtom->getItem() != NULL) tmpAtom->setSelected(false);
        }

        tmpMol->getItem()->setSelected(false);
		  iter++;
  }

  //////////////cout <<"You are here in angPicks && angSelCounter is currently " <<viewer->angSelCounter<< endl;
  //atom *atm = getHit(hits, buffer);
  if (atm != NULL) {
      if ( viewer->angSelCounter == 0) {atm1 = atm;  viewer->angSelCounter++;  atm->setSelected(true);}
      else if (viewer->angSelCounter == 1) { atm2 = atm; viewer->angSelCounter++; atm->setSelected(true);}
      else if (viewer->angSelCounter == 2) { atm3 = atm; viewer->angSelCounter++; atm->setSelected(true);}

  }

    if (viewer->angSelCounter == 3) {

        if ( !viewer->delAngMode ) {  //If we are in angle define mode
             //First check for intra-molecular angle
            if ( (atm1->getParent() == atm2->getParent() && atm1->getParent() == atm3->getParent()) && atm1->getParent()->rtti() == 11 ) {
              molecule *mol = dynamic_cast<molecule *>(atm1->getParent());
              mol->addAngle(atm1, atm2, atm3);
              atm3->setSelected(false);
              atm1 = atm2 = atm3 = atm4 = NULL;
            }   else {  // It must be an inter-molecular angle
              vector<atom *> tmp(3);
              tmp[0] = atm1;  tmp[1] = atm2;  tmp[2] = atm3;
              viewer->interMolAng.push_back(tmp);
              atm3->setSelected(false);
              atm1 = atm2 = atm3 = atm4 = NULL;
            }
        }  else {  //now were are in angle delete mode
              ////////////////cout <<"You are in angle delete mode: " << viewer->angSelCounter << endl;
              if ( (atm1->getParent() == atm2->getParent() && atm1->getParent() == atm3->getParent()) && atm1->getParent()->rtti() == 11 ) {   //intraMolDist deeletion
                  molecule *mol = dynamic_cast<molecule *>(atm1->getParent());
                  mol->delAngle(atm1, atm2, atm3);
                  atm3->setSelected(false);
                  atm1 = atm2 = atm3 = atm4 = NULL;
              } else {//interMolDist deleteion
                //Need to make this function work
                viewer->delInterMolAng(atm1, atm2, atm3);
                atm3->setSelected(false);
                atm1 = atm2 = atm3 = atm4 = NULL;
              }
        }
        viewer->setCursor(QCursor(Qt::ArrowCursor) );
        viewer->distMode = false;
        viewer->delDistMode = false;
        viewer->angMode = false;
        viewer->delAngMode = false;
        viewer->torsionMode = false;
        viewer->delTorsionMode = false;

        viewer->distSelCounter = 0;
        viewer->angSelCounter = 0;
        viewer->torsionSelCounter = 0;

        viewer->atm1 = viewer->atm2  = viewer->atm3 = viewer->atm4 = NULL;
    }
    //viewer->glInitNames();
}


void pickEngine::torsionPicks(GLint hits, GLuint buffer[]) {
  //////////////cout <<"pickEnging::torsionPicks()"<<endl;
  list<molecule *> *renList = viewer->renList;
  //int *angSelCounter = &viewer->angSelCounter;

  list<molecule *>::iterator iter = renList->begin();

  atom *atm = NULL;
  vector<int> objectNums;
  getHitObjectNumbers(objectNums, hits, buffer);
  int OBJECTNUM;
  for (int i=0; i<objectNums.size(); i++) {
    Object *tmp = Object::registry[ objectNums[ i ] ];
    if (tmp->rtti() == 10) {  
       atm = dynamic_cast<atom *>(tmp);
       OBJECTNUM = objectNums[i];
    }
  }

  if (hits == 0) return; //once you add the distance line...it shows up as 2 hits...messed up...don't like it not one little bit.

    //############### UNSELECT SECTION #################
  while (iter != viewer->renList->end()) {
        molecule *tmpMol = *iter;
        for (unsigned int i=0; i<tmpMol->atoms.size(); i++) {
          atom *tmpAtom = tmpMol->atoms[i];
          if (tmpAtom->getObjectNum() == OBJECTNUM) atm = tmpAtom;
          if (viewer->torsionSelCounter == 3)
            if (tmpAtom->getItem() != NULL) tmpAtom->setSelected(false);
        }

        tmpMol->getItem()->setSelected(false);
		  iter++;
  }

  //atom *atm = getHit(hits, buffer);
  if (atm != NULL) {
      if ( viewer->torsionSelCounter == 0) {atm1 = atm;  viewer->torsionSelCounter++;  atm->setSelected(true);}
      else if (viewer->torsionSelCounter == 1) { atm2 = atm; viewer->torsionSelCounter++; atm->setSelected(true);}
      else if (viewer->torsionSelCounter == 2) { atm3 = atm; viewer->torsionSelCounter++; atm->setSelected(true);}
      else if (viewer->torsionSelCounter == 3) { atm4 = atm; viewer->torsionSelCounter++; atm->setSelected(true);}

  }


    if (viewer->torsionSelCounter == 4) {

        if ( !viewer->delTorsionMode ) {  //If we are in angle define mode
             //First check for intra-molecular angle
            if ( (atm1->getParent() == atm2->getParent() && atm1->getParent() == atm3->getParent() && atm1->getParent() == atm4->getParent()) && atm1->getParent()->rtti() == 11 ) {
              molecule *mol = dynamic_cast<molecule *>(atm1->getParent());
              mol->addTorsion(atm1, atm2, atm3, atm4);
              atm4->setSelected(false);
              atm1 = atm2 = atm3 = atm4 = NULL;
            }   else {  // It must be an inter-molecular angle
              vector<atom *> tmp(4);
              tmp[0] = atm1;  tmp[1] = atm2;  tmp[2] = atm3;  tmp[3] = atm4;
              viewer->interMolTor.push_back(tmp);
              atm4->setSelected(false);
              atm1 = atm2 = atm3 = atm4 = NULL;
            }
        }  else {  //now were are in angle delete mode
              ////////////////cout <<"You are in angle delete mode: " << viewer->angSelCounter << endl;
              if ( (atm1->getParent() == atm2->getParent() && atm1->getParent() == atm3->getParent() && atm1->getParent() == atm4->getParent()) && atm1->getParent()->rtti() == 11 ) {   //intraMolDist deeletion
                  molecule *mol = dynamic_cast<molecule *>(atm1->getParent());
                  mol->delTorsion(atm1, atm2, atm3, atm4);
                  atm4->setSelected(false);
                  atm1 = atm2 = atm3 = atm4 = NULL;
              } else {//interMolDist deleteion
                //Need to make this function work
                viewer->delInterMolTorsion(atm1, atm2, atm3, atm4);
                atm4->setSelected(false);
                atm1 = atm2 = atm3 = atm4 = NULL;
              }
        }
        viewer->setCursor(QCursor(Qt::ArrowCursor) );
        viewer->distMode = false;
        viewer->delDistMode = false;
        viewer->angMode = false;
        viewer->delAngMode = false;
        viewer->torsionMode = false;
        viewer->delTorsionMode = false;

        viewer->distSelCounter = 0;
        viewer->angSelCounter = 0;
        viewer->torsionSelCounter = 0;

        viewer->atm1 = viewer->atm2  = viewer->atm3 = viewer->atm4 = NULL;
    }
}


atom *pickEngine::getHit(GLint hits, GLuint buffer[])  {
  list<molecule *>::iterator  molIterator;
  atom *tmpAtm;
 //There is a problem here because you are only searching over one molecule.
 for (molIterator = viewer->renList->begin(); molIterator != viewer->renList->end(); molIterator++) {
       molecule *mol=*molIterator;
       for (int i=0; i<mol->atoms.size(); i++) {
          atom *atm = mol->atoms[ i ];
          if (atm->getObjectNum() == buffer[3] ) return atm;
       }
 }

  /** This code sorta works
  Object *tmpObj = mol->getObject(buffer[3]);
  if (tmpObj->rtti() != 10)  {//////////////cout <<"returning null: " << endl; return NULL;}
  atom *tmpAtm = dynamic_cast<atom *>(tmpObj);

  */
  return tmpAtm;
}







































