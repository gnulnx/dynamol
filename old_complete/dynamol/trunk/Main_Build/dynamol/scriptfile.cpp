/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "scriptfile.h"
#include "molecule.h"
#include "xmodelview.h"
#include "scriptmollist.h"
#include "scriptmolecule.h"

#include "mollistview.h"

sdReader scriptfile::sdRead;

scriptfile::scriptfile(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
}


scriptfile::~scriptfile()
{
}
int scriptfile::numOfRecords(QString fileName) {
	molDB *db = new molDB;
	int num = db->read_sd(fileName.latin1(), false);
	delete db;
	return num;	
}
 
scriptmollist *scriptfile::readMol(QString fileName) {
   molDB db;
   if (view != NULL) {
     //connect(&db, SIGNAL(newMolecule(molecule *)), view->listView, SLOT(addMolecule(molecule *)));
   }
   
   if (fileName.contains(".sdf") > 0) {
      int num = db.read_sd(fileName.latin1(), false);
      scriptmollist *molList = new scriptmollist;
      vector<molecule *> mols;
      db.getSdRange(0, num, mols);
      for (int i=0; i<mols.size(); i++) {
         scriptmolecule *smol = new scriptmolecule(mols[i]);
         molList->push_back(smol);
      }
      return molList;
   } 
   
   if (fileName.contains(".mol2") > 0) {
   }
      
   return new scriptmollist;
   
}

void scriptfile::openMol(QString fileName) {
   scriptmollist *list = readMol(fileName);
   for (int i=0; i<list->size(); i++) {
      scriptmolecule *mol = list->getMol(i);
      listView->addMolecule(mol->mol);
   }
}

scriptmollist *scriptfile::readMol(QString fileName, int start, int end) {
  molDB db;
   //////////////cout <<"in scriptmolLIst read(QString fileName, int start, int end)"<<endl;
   if (view != NULL) {
     //connect(&db, SIGNAL(newMolecule(molecule *)), view->listView, SLOT(addMolecule(molecule *)));
   }
   //int num = db->read_sd(fileName.latin1(), false);
   int num = db.read_sd(fileName.latin1(), false);
   if (num-1 < end) end = num-1;
   scriptmollist *molList = new scriptmollist;
   vector<molecule *> mols;
   db.getSdRange(start, end, mols);
   //////////////cout <<"YOu are here: " << mols.size() << endl;
   for (int i=0; i<mols.size(); i++) {
      scriptmolecule *smol = new scriptmolecule(mols[i]);
      //smol->setXmodelView(view);
      //smol->setMolecule(mols[i]);
      //////////////cout << "mols[i]->getName(): " << mols[i]->getName() << setw(12) << mols[i]->atoms.size() << endl;
      molList->push_back(smol);
   }
 
   return molList;
}

bool scriptfile::writeMol(scriptmolecule *mol, QString fileName, bool append) {
  if (mol == NULL) {
    //////////////cout <<"No mol to write!"<<endl;
    return false;
  }
  
  molDB db;
  int a = 0;
  if (append) a = 1;
  else a = 0;
  if (fileName.contains(".sdf") || fileName.contains(".SDF") ) {
    //////////////cout <<"it is an sdf file"<<endl;
    db.writeSDF(fileName.latin1(), mol->mol, a);
    return true;
  }
  
  if (fileName.contains(".mol2") || fileName.contains(".MOL2") ) {
    //////////////cout <<"it is a mol2 file"<<endl;
    db.writeMol2(fileName.latin1(), mol->mol, a);
    return true;
  }   
}


int scriptfile::scanSDFile(QString fileName) {
  return sdRead.scanSDFile( fileName );

}

scriptmolecule *scriptfile::getMol(int position) {
   molecule *mol = sdRead.getMolPos( position );
   return new scriptmolecule(mol);
}


















































