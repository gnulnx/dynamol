/***************************************************************************
                          mollistview.cpp  -  description
                             -------------------
    begin                : Wed Jan 21 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "mollistview.h"
#include "listViewRightClick.h"
#include "molview.h"
#include "trashcan.h"
#include <algorithm>
#include "xmodeldoc.h"
#include "mollistviewitem.h"
#include "atom.h"
#include "bond.h"
#include "molecule.h"
#include "protein.h"
#include "chain.h"
#include "fragment.h"
#include "object.h"
#include "qbuttongroup.h"
//#include "mollistviewdialog.h"
using namespace std;

molListView::molListView( QWidget *parent, const char *name, XmodelDoc *doc ) : QListView(parent,name) {
  addColumn("Molecule", -1);
  setSorting(-1);
  this->doc = doc;
  //Set the internal render list to the same as the molDB render list

  shiftKey = controlKey = altKey = UP;
  setRootIsDecorated(true);
  setSelectionMode(Extended);

  connect(this, SIGNAL(doubleClicked(QListViewItem *)), this, SLOT(checkDoubleClick(QListViewItem *)));

  //This will probably be used more so in future versions of qt. Otherwise the QDialog box will not pop up && act right forme.
  connect(this, SIGNAL(rightButtonClicked(QListViewItem *, const QPoint &, int)), this, SLOT(optionsDialog(QListViewItem *, const QPoint &, int)));
  connect(this, SIGNAL(selectionChanged()), this, SLOT(selectionChangedSlot()));
  connect(this, SIGNAL(mouseButtonPressed( int, QListViewItem *, const QPoint &, int )), this, SLOT(mouseButtonPressedSlot ( int , QListViewItem *, const QPoint &, int )));
  
  connect(this, SIGNAL(keyPressEvent( QKeyEvent * )), this, SLOT(keyPressSlot(QKeyEvent *)));
  connect(this, SIGNAL(keyReleaseEvent( QKeyEvent * )), this, SLOT(keyReleaseSlot(QKeyEvent *)));
}

molListView::~molListView(){
}

void molListView::setMolView(molView *viewer) {
   this->viewer = viewer;
}

void molListView::clearSelectionSlot() {
    triggerUpdate();
}

void molListView::molViewSlot() {
 
}

void    molListView::addMolecule(molecule *mol, bool show) {
   setMaximumWidth(1500);
   // First lets check to make sure that it is not 
   // already here..the pointer that is.
   QListViewItemIterator it(this);
   molListViewItem *listItem;
   molName = mol->getName().c_str();
   molItem = new molListViewItem(this, molName, mol);
   mol->setItem(molItem);   //Set the molListViewItem pointer in the molecule
   atom *tmpAtom;
   for (int i=0; i<mol->atoms.size(); i++) {
      tmpAtom = mol->atoms[i];
      atomName = tmpAtom->getSym().c_str();
      atomItem = new molListViewItem(molItem, atomName, tmpAtom);
      tmpAtom->setItem(atomItem);
   }
    // Now lets clear the render list && render the new molecule. 
    // I think that you should give
    // The user the option to clear the renderList || not.
    //  Perhaps you could append the new molecule
    // to the already rendered molecules???
   if (show) {
      renList.clear();
      renList.push_back(mol);
	  //viewer->setMolList(&renList);
      emit renderMol(&renList);
   }
};

void    molListView::addProtein(protein  *prot) {
  setMaximumWidth(1500);
  QString protName, chainName, fragName, atomName;
  chain *ch;
  fragment *frag;
  atom      *tmpAtom;
 
  protName = prot->getName().c_str();
  protItem = new molListViewItem(this, protName, prot);
  prot->setItem(protItem);   //Set the molecules->item to the molListViewItem...Not sure I like this.
  for (int i=0; i<prot->chains.size(); i++) {
    ch = prot->chains[i];
    chainName = ch->getName().c_str();
    chainItem = new molListViewItem(protItem, chainName, ch);
    ch->setItem(chainItem);
    
    if (ch->numOfFrags() != 0) {
      for (int j=0; j<ch->frags.size(); j++) {
        frag = ch->frags[j];
        fragName = frag->getName().c_str();
        QString tmp;
        tmp.setNum(frag->getNum());
        fragName.append("  ");
        fragName.append(tmp);
        fragItem = new molListViewItem(chainItem, fragName, frag);
        frag->setItem(fragItem);
	for (int k=0; k<frag->atoms.size(); k++) {
	  tmpAtom = frag->atoms[k];
          atomName = tmpAtom->getSym().c_str();
          atomItem = new molListViewItem(fragItem, atomName, tmpAtom);
          tmpAtom->setItem(atomItem);
        }
      }

    }
  }

  renList.clear();
  renList.push_back(prot);
  emit renderMol(&renList);
};

void molListView::updateView() {

}


void molListView::checkDoubleClick(QListViewItem *item) {
}

void molListView::optionsDialog(QListViewItem *, const QPoint &, int tmp) {
  
   listViewRightClick *dialog = new listViewRightClick(this);
   dialog->show();
   if ( dialog->exec() == listViewRightClick::Accepted ) {
      int style = dialog->group2->selectedId();
      int method = dialog->group1->selectedId();
      newRenderState(style, method);
   }
}

void molListView::contentsMouseDoubleClickEvent (QMouseEvent *event) {
  renList.clear();
  /*  Check for selected molecules && add them to the renList.
      Atoms will be selected && displayted along with their parent molecule
  */

  QListViewItemIterator it(this);
  molListViewItem *listItem;
  molecule *tmpMol;
  while ( it.current() ) {
    if (it.current()->isSelected()) {
      listItem = dynamic_cast<molListViewItem *>(it.current());
      if (listItem  == NULL) {
	//int test = 0;
	//cin >> test;
      }
      selQueue.push_back(listItem);
      if (listItem->getObject()->rtti() >= 11) {
        
        tmpMol = dynamic_cast<molecule *>(listItem->getObject());
        //This part is very impoartant....makes sure only one molecue is renderd
        QListViewItemIterator it2(it.current()->nextSibling());
        it = it2;
      } else if (listItem->getObject()->rtti() == 10) {   //it is an atom
      
        tmpMol = dynamic_cast<molecule *>(listItem->getObject()->getParent());
        
        QListViewItemIterator it2(it.current()->parent()->nextSibling());
        it = it2;
      }
      renList.push_back(tmpMol);
    }
    it++;
  }

  //This is statement is here to keep it from segFaulting when there is a double click but no molecule selected
  //I believe it is all being taken care of by render
  //if (renList.size() > 0) {
    emit renderMol(&renList);
    
  //}
}


void molListView::contentsMouseReleaseEvent (QMouseEvent *event) {
  //Determine the state of the mouse && the keyboard
  ButtonState button = event->button();
  ButtonState state  = event->state();
  //Make sure that it is the Left Mouse Button that is being pressed
  if (button & LeftButton ) {    
    
    molListViewItem *item;
    
    if (button & LeftButton || button & RightButton) {
      while (!selQueue.empty()) {
	item = selQueue[0]; //this is the front of the queue.
	if (item != NULL) {
	  if ( !item->isSelected() ) {
            if (item->getObject()->getParent()) {  
	    	item->getObject()->getParent()->getItem()->setSelected(false);
            }
            item->getObject()->setSelected(false, true);
           }
	} else {
	}
        selQueue.pop_front();  //remove the top element of the stack
      }
    }
    
  
    // Now add selected objects to th selQueue 
    QListViewItemIterator it( this );
    while ( it.current() ) {
        item = dynamic_cast<molListViewItem *>(it.current());
	if (item == currSel && controlKey == UP) {
	  item->setSelected(true);
	}
        if (item->getObject()->rtti() >=10) {
          if (item->isSelected()) {
            selQueue.push_back(item);
	    item->getObject()->setSelected(true, true);
	    it++;
          } else {  
              it++;
          }
        } else {
          it++;
        }
    } 
   }

   if (button & RightButton) {
      const QPoint p;
      QListViewItem *tmpItem;
      int tmp;
     optionsDialog(tmpItem, p, tmp);
   } 
 

   triggerUpdate();
   viewer->updateGL();
}


void molListView::selectionChangedSlot() {

  triggerUpdate();
}


void molListView::mouseButtonPressedSlot ( int button, QListViewItem *it, const QPoint & pos, int c ) {
  if (it != NULL) {
     
     molListViewItem *item = dynamic_cast<molListViewItem *>(it);
     currSel  = item;
     if (shiftKey == UP && controlKey == UP && altKey == UP && button == 1) {
        clearSelection();
        item->setSelected(true);
    }
    
    if (controlKey == DOWN) {
      //Lets check to see if the item is deselected && then ensure that the parent
      //is also deselected
      if ( !item->isSelected()) {
        if (item->getObject()->getParent() != NULL) 
	  item->getObject()->getParent()->getItem()->setSelected(false);
      }
    }
   }   
}

void molListView::keyPressSlot(QKeyEvent *event) {
  //Note that the QT manual says that this function cannot be truested???
  
  //It returns the value of the shift key after it was called
  int key = event->stateAfter();

   if (key & ShiftButton) {
	shiftKey = DOWN;
   }
   if (key & ControlButton) {
	controlKey = DOWN;
   }
   if (key & AltButton) {
	altKey = DOWN;
   }      
}


void molListView::keyReleaseSlot(QKeyEvent *event) {
  //Returns the value of the shit key that was set before being called
  int key = event->state();
  int key2 = event->key();

   if (key & ShiftButton) {
	shiftKey = UP;
   }
   if (key & ControlButton) {
	controlKey = UP;
   }
   if (key & AltButton) {
	altKey = UP;
   }   
   if (key2 == Key_Delete) {   
       deleteItems();    
       emptySelQueue();
   }
}
void molListView::deleteItems() {
   /** First gather the objects to delete into a set
   *   The set was chosen because it has fast insert 
   *   and delete opoerations.
   *   Only the highest level objects in the set are stored
   *   There is no reason to store an atom and it's parent */
   set<Object *> objectSet;
   gatherObjectsToDelete(objectSet);
   
   /** Now convert the set to a vector and then delete the 
   *   molListViewItem that belongs to the object
   *   This causes all the child objects to be dealt with as well
   */
   list<molecule *>::iterator lIter;
   vector<Object *> objectVector(objectSet.begin(),objectSet.end());
   for (int i=0; i<objectVector.size(); i++) {
      //delete objectVector[i]->getItem();
      
      //Now lets delete the selection from the renList
      /*
      lIter = std::find(renList.begin(), renList.end(), objectVector[i]);
      if (lIter != renList.end()) {
         renList.erase(lIter);
      }
      */
   }
   TrashCan t(objectVector);
   set<molecule *> renListSet(renList.begin(), renList.end());
   set<molecule *>::iterator si = renListSet.begin();
   for (si; si != renListSet.end(); si++) {
      molecule *mol = *si;
   }
   t.setCheck(renListSet);   
   t.empty(); 
   list<molecule *> newList(renListSet.begin(), renListSet.end());
   renList = newList;
   
   Object::updateRegistry();
   //viewer->renList->clear();
}


void molListView::gatherObjectsToDelete(set<Object *> &objectSet) {
   /** you are using a set to store the objects that
   *   That will need to be passed to the TrashCan.
   */
   
   molListViewItem *mItem;
   QListViewItemIterator it( this );
   while ( it.current() ) {
      QListViewItem *item = *it;
      
      if (item->isSelected() ) {
         if (!item->parent() ) {
            mItem = dynamic_cast<molListViewItem *>(it.current());
            objectSet.insert( mItem->getObject());
         } 
         else if ( !item->parent()->isSelected() ) {
            mItem = dynamic_cast<molListViewItem *>(it.current());
            objectSet.insert( mItem->getObject());
         }
      } 
      it++;
   } 
}
void molListView::emptySelQueue() {
    while (!selQueue.empty()) selQueue.pop_front();
    
    //////////cout <<"renList.size(): " << renList.size() << endl;
    emit renderMol(&renList);
}

//This function is for memory checking only
void molListView::deleteC(string str) {
  /*
  QListViewItemIterator it( this );
  while ( it.current() ) {
    molListViewItem *item = dynamic_cast<molListViewItem *>(it.current());
    Object *obj = item->getObject();
    molecule *mol = dynamic_cast<molecule *>(obj);
    if (mol && mol->getName() == str) {
      deleteItem(item);
    }
    
    it++;
  }	
  */  
}

void molListView::deleteAtomsSlot(vector<atom *> &Atoms) {
   TrashCan t(Atoms);
   set<molecule *> renListSet(renList.begin(), renList.end());
   t.setCheck(renListSet);
   t.empty();
   list<molecule *> newList(renListSet.begin(), renListSet.end());
   renList = newList;
   emit renderMol(&renList);
}




void molListView::newRenderState(int rs, int rm) {
 //////////////cout <<"molListView::newRenderState  "<<rs << setw(12) << rm << setw(12) << renList.size() << endl;
   molListViewItem *item; 
 //renList.clear();
   if (rm == 1) {
      renList.clear();
   }
   QListViewItemIterator it( this );
   molecule *tmpMol;
   atom *tmpAtom;

   vector<molecule *> molsToRender;
   while ( it.current() ) {

      item = dynamic_cast<molListViewItem *>(it.current());
      if (item->getObject()->rtti() > 10 && item->isSelected()) {
         //QListViewItem *qi = new QListViewItem(this);
         //qi->parent();
         //item->parent();
         
         while (item->parent && item->parent->isSelected()) {
           item = item->parent;
         }
         
         tmpMol = dynamic_cast<molecule *>(item->getObject());
         for (int i=0; i<tmpMol->atoms.size(); i++) {
            //at = tmpMol->getCurrentAtom();
            at = tmpMol->atoms[i];
            if (rs == 3) {
                at->setRenderType(CPK);
            } else if (rs == 2 || rs == 1) {
                 at->setRenderType(BALL);
            } else if (rs == 0) {
                 at->setRenderType(PNT);
            }
            if (!tmpMol->nextAtom()) {
	       break;
	    }
         }

      if (tmpMol->getNumOfBonds() > 0) {
         tmpMol->setBondToBegin();
         for (;;) {
            bd = tmpMol->getCurrentBond();
            
            if (rs == 3) {
               bd->setRenderType(NOBOND);
            } else if (rs == 1) {
              bd->setRenderType(STICK);
            } else if (rs == 0 || rs == 2) {
             bd->setRenderType(WIRE);
            }
            
            if (!tmpMol->nextBond())
               break;
         }
      }
           
      bool inList = false;
      for (int i=0; i<molsToRender.size(); i++) {
         if (tmpMol == molsToRender[i]) {
            inList = true;
            break;
         }
      }
      if (!inList)
         molsToRender.push_back(tmpMol);
      //renList.push_back(tmpMol);
        
   } else {
     tmpAtom = dynamic_cast<atom *>(item->getObject());
   }

   //selQueue.pop_front();
   it++;
 }  
  
   list<molecule *>::iterator lIter = renList.begin();
   for (int i=0; i<molsToRender.size(); i++) {
      bool alreadyInList = false;
      lIter = renList.begin();
      for (lIter; lIter != renList.end(); lIter++) {
         molecule *mol = *lIter;
	 if (mol->getObjectNum() == molsToRender[i]->getObjectNum()) {
	    //////////////cout <<"Nope"<<endl;
	    alreadyInList = true;
	 }
      }
      if (!alreadyInList) 
         renList.push_back(molsToRender[i]);
   }
   emit renderMol(&renList);
    
}


void molListView::addNewAtom(atom *atm, molecule *parent) {
   vector<atom *> newAtoms; 
   newAtoms.push_back(atm);
   addNewAtom(newAtoms, parent);
}
void molListView::addNewAtom(vector<atom *> &newAtoms, molecule *parent) {
   //////////////cout <<"molListView::addNewAtom "<< newAtoms.size() << endl;
   
   for (int i=0; i<newAtoms.size(); i++) {
   	atom *tmpAtm = newAtoms[i];
	molListViewItem *item = tmpAtm->getParent()->getItem();
	QString atomName = tmpAtm->getSym().c_str();
	atomItem = new molListViewItem(item, atomName, tmpAtm);
	tmpAtm->setItem(atomItem);
   }
   //////////////cout <<"Leaving molListView::addNewAtom"<<endl;
}

void molListView::displayMol(QString name, bool clear) {
   QListViewItemIterator it( this );
   
   if (clear == true) renList.clear();
   
   while ( it.current() ) {
      molListViewItem *item = dynamic_cast<molListViewItem *>(it.current());
      Object *obj = item->getObject();
      if (item->text(0) == name && obj->rtti() >= 11) {
         molecule *mol = dynamic_cast<molecule *>(obj);
         renList.push_back(mol);
         emit renderMol(&renList);
      }
      it++;
   }	
}

void molListView::deleteAll() {
  //////////cout <<"molListView::deleteAll()"<<endl;
  QListViewItemIterator it( this );
  while ( it.current() ) {
     it.current()->setSelected(true);  
     it++;
  }
  deleteItems();
}


































