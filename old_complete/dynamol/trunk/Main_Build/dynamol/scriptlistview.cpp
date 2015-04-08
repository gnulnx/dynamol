/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "scriptlistview.h"
#include "moldb.h"
#include "scriptmolecule.h"

#include "molecule.h"

#include "mollistview.h"

scriptlistview::scriptlistview(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
}


scriptlistview::~scriptlistview()
{
}


void scriptlistview::addMol(scriptmolecule *mol) {
  //molDB db;
  //connect(&db, SIGNAL(newMolecule(molecule *)), view->listView, SLOT(addMolecule(molecule *)));
  if (mol != NULL) {
    listView->addMolecule(mol->mol);
    mol->inListView = true;
  } else {
    ////////////cout <<"No molecule to add to molList"<<endl;
  }
  //////////////cout <<"Here you are in addMol"<<endl;
}

void scriptlistview::displayMol(QString name, bool clear) {
   listView->displayMol(name, clear);
}

void scriptlistview::displayMol(QString name) {
   listView->displayMol(name, true);
}


QVariant scriptlistview::getListNames() {
   //////////cout <<"getListNames "<< listView << endl;
    QValueList<QVariant> list;
   QListViewItemIterator it( listView );
    //////////cout <<"Made it here"<<endl;
    //////////cout << it.current() << endl;
    //////////cout <<it.current()->text(0) << endl;
    while ( it.current() ) {
	////////////cout << it.current()->text(0);
//        //////////cout << it.current()->parent() << endl;      
        if ( it.current()->parent() == NULL ) {
            //////////cout << it.current()->text(0) << endl;
	    list.push_back(it.current()->text(0));
	}
	
        it++;
    }
    //////////cout <<"You are here"<<endl;

//   QValueList<QVariant> list;
//   list.push_back(QVariant(obj1));
//   list.push_back(QVariant(obj2));
   QVariant arr(list);
   return arr;   

}


































