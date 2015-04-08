/***************************************************************************
                          mollistview.h  -  description
                             -------------------
    begin                : Wed Jan 21 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef MOLLISTVIEW_H
#define MOLLISTVIEW_H

//#include <qwidget.h>
#include <qlistview.h>
#include <qstring.h>

// application specific includes
//#include "mollistviewitem.h"


#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <set>
using namespace std;

namespace dynacomp {
	class molecule;
};

class molView;
class bond;
class atom;
class XmodelDoc;
class molListViewItem;
class molecule;
class protein;
class Object;
/**
  *@author John Furr
  */

/** This class is used to display the current molecules && their atoms.
    I would also like it to eventually support molecules && their surfaces.
*/
class molListView : public QListView  {
   Q_OBJECT
public: 
   molListView(QWidget *parent=0, const char *name=0, XmodelDoc* doc=0);
   ~molListView();

   /** This function is responsible for building a vector of objects 
   *   That need to be deleted.  This object vector is then passed
   *   to the TrahCan were it will be dealt with on an Object Type
   *   basis */
   void gatherObjectsToDelete(set<Object *> &setObjects);	
   
   void deleteItems();
   
   //This is purely to check the code for memory leaks
   void deleteC(string str);
   void emptySelQueue();
	
   void setMolView(molView *viewer);
   molView *viewer;
  
   stack<molListViewItem *> selStack;
   deque<molListViewItem *> selQueue;
   //queue<molListViewItem *> selQueue;
private:
   XmodelDoc             *doc;
   molecule                *mol;
   atom                    *at;
   bond                    *bd;
   QListViewItem          *bondElement, *protElement, *chainElement, *fragElement, *hetElement, *hetAtomElement;

   molListViewItem         *atomItem, *molItem, *fragItem, *chainItem, *protItem, *currSel;
   //QListViewItem *currSel;
   QString                 molName, atomName;
   list<molecule *>        molList; //This will probably be deleted???

   QKeyEvent *keyEvent;
   //This renderList is currently set to the same renderList as the molDB.renderList.
   // Is this really a good idea?  Try && remember your real motivations for doing it this way.
   //list<molecule *>        *renList;
   list<molecule *>        renList;

   molecule  *molMatchItem(QListViewItem *item);
   atom      *atomMatchItem(QListViewItem *item);

   map<QListViewItem *, molecule *>  molDisplayMap;
   map<QListViewItem *, atom *>      atomDisplayMap;


  
   enum button_state 				{DOWN, UP};  //Makes for easier to read c

   /**
     Variables of type button_state which are used to determine wether the buton in question is
     being pressed (DOWN) are has been released (UP).  The default position is UP.
   */
   button_state  leftButton, rightButton, midButton, shiftKey, controlKey, altKey;

protected:
  virtual void contentsMouseDoubleClickEvent (QMouseEvent *event);
  virtual void contentsMouseReleaseEvent (QMouseEvent *event);
 // virtual void contentsMousePressEvent(QMouseEvent *event);
  //void contentsMousePressEventEx( QMouseEvent * e );
 
public slots:
  /** This slot deletes all the molecules in the molView */
  void deleteAll();
  
  void keyPressSlot(QKeyEvent *event);
  void keyReleaseSlot(QKeyEvent *event);
  void updateView();
  void checkDoubleClick(QListViewItem *item);
  void optionsDialog(QListViewItem *, const QPoint &, int);
  void newRenderState(int, int);
  void molViewSlot();
  void addMolecule(molecule *mol, bool show = true);
  void addProtein(protein  *prot);
  void selectionChangedSlot();
  void clearSelectionSlot(); //simply calls QListViewItem->clearSelection
  void mouseButtonPressedSlot( int button, QListViewItem * item, const QPoint & pos, int c );
   
  /** These pair of function update the list view with the new atoms */
  void addNewAtom(atom *atm, molecule *parent);
  void addNewAtom(vector<atom *> &newAtoms, molecule *parent);
  
  /** This slot cathces the signal deleteAtoms from molView && begins the deletion process */
  void deleteAtomsSlot(vector<atom *> &Atoms);

  /** This function displays the atom "name".  If clear is true then the current molView is cleared first else the "name" molecule is displayed in addition to the current molView. */
  void displayMol(QString name, bool clear);

signals:
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void keyReleaseEvent(QKeyEvent *event);
  void doubleClicked();
  void renderMol(std::list<molecule *> *renderList);
};

#endif





































