/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "jobmanager.h"
#include "xmodelview.h"

#include "molchangeevent.h"

#include <qmessagebox.h>
#include "mollistview.h"
#include "molview.h"

#include "atom.h"
#include "bond.h"
#include "angle.h"
#include "torsion.h"

jobManager::jobManager(QObject *parent, const char *name)
 : QObject(parent, name)
{
  
}


jobManager::~jobManager()
{
}

bool jobManager::eventFilter(QObject *obj, QEvent *e) {
   // QEVent::User+1 this make sure that you have waited long 
   // enough in the add H It uses a semaphore to do the timing work
   if (e->type() == 1001) {
     molChangeEvent *event = dynamic_cast<molChangeEvent *>(e);   
     view->listView->addNewAtom(*event->newAtoms, event->mol);
     
     if (!event->wait_sem->available()) {     
        (*event->wait_sem)--;
	view->update->wakeAll();
     }
     view->startAllGUI();
          
     return TRUE;
   }
   
   //QEvent::User+2 is used to stop the molView->autoUpdate() function.
   else if (e->type() == 1002) {
     ////////////////cout <<"Stopping the Auto Update"<<endl;
     molChangeEvent *event = dynamic_cast<molChangeEvent *>(e);
     emit jobDone(event->name);
     view->viewer->endAutoUpdate(NULL);
     return TRUE;
   }
   else if (e->type() == 1003) {
      molChangeEvent *event = dynamic_cast<molChangeEvent *>(e);
      QMessageBox::critical( 0, "Dynamol", event->Msg);
      emit jobDone(event->name);
      return TRUE;
   }
   else if (e->type() == 1004) { //could not type bond
      molChangeEvent *event = dynamic_cast<molChangeEvent *>(e);
      QString error = "Could Not Type Bond\n";
      QString tmp;
      tmp.setNum(event->bd->from->getNum() );
      error += tmp;
      error += " (";
      error += event->bd->from->getFFType();
      error += ")--";
      tmp.setNum(event->bd->to->getNum() );
      error += tmp;
      error += " (";
      error += event->bd->to->getFFType();
      error += ")";
      QMessageBox::critical( 0, "Dynamol",error);
      emit jobDone(event->name);
      return TRUE;
   }
   else if (e->type() == 1005) { //could not type angle
      molChangeEvent *event = dynamic_cast<molChangeEvent *>(e);
      QString error = "Could Not Type Angle\n";
      QString tmp;
      tmp.setNum(event->ang->front->getNum() );
      error += tmp;
      error += " (";
      error += event->ang->front->getFFType();
      error += ")--";
      tmp.setNum(event->ang->mid->getNum() );
      
      error += tmp;
      error += " (";
      error += event->ang->mid->getFFType();
      error += ")--";
      tmp.setNum(event->ang->back->getNum() );
      error += tmp;
      error += " (";
      error += event->ang->back->getFFType();
      error += ")\n";
      
      error += "Job has been aborted";
      QMessageBox::critical( 0, "Dynamol",error);
      emit jobDone(event->name);
      return TRUE;
   }
   else if (e->type() == 1006) { //could not type torsion
      molChangeEvent *event = dynamic_cast<molChangeEvent *>(e);
      QString error = "Could Not Type Torsion\n";
      QString tmp;
      
      tmp.setNum(event->tor->atm1->getNum() );
      error += tmp;
      error += " (";
      error += event->tor->atm1->getFFType();
      error += ")--";
      
      tmp.setNum(event->tor->atm2->getNum() );
      error += tmp;
      error += " (";
      error += event->tor->atm2->getFFType();
      error += ")--";
      
      tmp.setNum(event->tor->atm3->getNum() );
      error += tmp;
      error += " (";
      error += event->tor->atm3->getFFType();
      error += ")\n"; 
      
      tmp.setNum(event->tor->atm4->getNum() );
      error += tmp;
      error += " (";
      error += event->tor->atm4->getFFType();
      error += ")\n"; 
      
      error += "Job has been aborted";
      QMessageBox::critical( 0, "Dynamol",error);
      emit jobDone(event->name);
      return TRUE;
   }
   else if (e->type() == 1007) { //could not type nonBOnd
      ////////////////cout <<"nonbond was not typed"<<endl;
   }

   else if (e->type() == 1008) { //Dynatype not found
      QString error = "Atom type procedure failed.\n";
      error += "This most likely results from the dynatype ";
      error += "program not being in the correct place";
      QMessageBox::critical( 0, "Dynamol",error);
   }
   else if (e->type() == 1009) {
      QString error = "Make sure that MOPAC is in your path\nJob Not run";
      QMessageBox::critical( 0, "Dynamol",error);  
   }
   else if (e->type() == 1010) {
      //This section is used to display a new peice of information to the user
      molChangeEvent *event = dynamic_cast<molChangeEvent *>(e);
      view->viewer->setInfoText( event->displayText );
   }
   else if (e->type() == 1011) { //Add molecule to listView 
      //cout <<"molChangeEvent: 1011" << endl;
      molChangeEvent *event = dynamic_cast<molChangeEvent *>(e);
      //cout <<"HERE 1"<<endl;
      view->listView->addMolecule(event->mol, true);
      //cout <<"HERE 2"<<endl;
      view->viewer->renderMols(event->molVec); 
      //cout <<"Done with jobmanager"<<endl;
   }


   return FALSE;
}

void jobManager::setXmodelView(XmodelView *view) {this->view = view;}


bool jobManager::registerJob(dynoThread *thread) {
   //////////////cout <<"registerJob " << endl;
   QString name = thread->getName();
   QString nameHold = name;
   int count = 0;
   for (int i=0; i<jobNames.size(); i++) {
      if (jobNames[i] == name) {
         count++;
         QString num;
         num.setNum(count);
         name += "-";
         name += num;
         
      }
   }
   if (count != 0) {
      QString Num;
      Num.setNum(count);
      nameHold += "-";
      nameHold += Num;
      thread->setName(nameHold);
   }
   jobNames.push_back(nameHold);
   threads.push_back(thread);
   return true;
}

bool jobManager::removeJob(QString name) {
   int index = 0;
   for (int i=0; i<jobNames.size(); i++) {
      if (name == jobNames[i]) {
         threads[i]->stopThread();    
         threadTrash.push_back(threads[i]);
         jobNames.erase(jobNames.begin() + i );
         threads.erase(threads.begin() + i );
	 return true;
      }       
   }

   return false;
}







































