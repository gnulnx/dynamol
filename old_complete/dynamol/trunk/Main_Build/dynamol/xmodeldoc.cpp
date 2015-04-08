/***************************************************************************
                          chemtestdoc.cpp  -  description
                             -------------------
    begin                : Tue Dec 30 21:35:06 EST 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "xmodeldoc.h"
#include <fstream>
#include <iostream>
using namespace std;
//#include "pdbreader.h"
//#include "export.h"

XmodelDoc::XmodelDoc()
{
  modified = false;
}

XmodelDoc::~XmodelDoc()
{
}

void XmodelDoc::newDoc()
{
}

bool XmodelDoc::save()
{
  //////////////cout <<"Hey man this is were all the save action is going on!"<<endl;
  /*  
  QFileDialog* fd = new QFileDialog(this, "file dialog" );
  fd->setMode( QFileDialog::AnyFile );
  string fileName = fd->selectedFile();
  fd->show();
  ////////////cout <<"FileName is: " << fileName << endl;
  */
  return true;
}

bool XmodelDoc::saveAs(QString &filename, list<molecule *> &renList)
{
  if (renList.size() == 0) {
    //////////////cout <<"There is nothing in the molView to save"<<endl;
    return false;
  }
  
  if (filename.contains(".sdf")) {
    //////////////cout <<"Saving as an sdf file"<<endl;
    list<molecule *>::iterator molIter = renList.begin();
    int count = 0;
    for (molIter; molIter != renList.end(); molIter++) {
      molecule *mol = *molIter;
      if (count == 0)
         db.writeSDF(filename.latin1(), mol, 0); 
      else
         db.writeSDF(filename.latin1(), mol, 1);

      count++;
    }
  }
  else if (filename.contains(".mol2") ) {
    //////////////cout <<"Saving as a mol2 file"<<endl;
     
    list<molecule *>::iterator molIter = renList.begin();
    for (molIter; molIter != renList.end(); molIter++) {
      molecule *mol = *molIter;
      db.writeMol2(filename.latin1(), mol, 0); 
    }
    
  }
  else if (filename.contains(".sdfx") ){
     //////////////cout <<"Saving as a dynamol extended sdf format"<<endl;
     list<molecule *>::iterator molIter = renList.begin();
    for (molIter; molIter != renList.end(); molIter++) {
      molecule *mol = *molIter;
      db.writeSDFX(filename.latin1(), mol, 1); 
    }
  
  } else if (filename.contains(".ddb") ) {
    list<molecule *>::iterator molIter = renList.begin();
    for (molIter; molIter != renList.end(); molIter++) {
      molecule *mol = *molIter;
      ////cout <<"Trying to write a DDB file"<<endl;
      db.writeDDB(filename.latin1(), mol, 1);
    }  
  } else {
    filename.append(".sdf");
    //////////////cout <<"could not descern file type saving as:  " <<  filename << endl;
  }
  
  
  //////////////cout <<"Saving file: "<< filename << endl;
  return true;
}

bool XmodelDoc::load(QString &filename)
{

  
  //Read in mol2 file
  if (filename.contains(".mol2")) {
    db.read_mol2(filename.latin1());
    emit documentChanged();
    return true;
  }

  //UNCOMMENT HERE TO TEST A READ IN OFF ALL PDB STRUCTURES
  if (filename.contains(".list") ) {
      ifstream inFile;
      inFile.open(filename.latin1(), ios::in);
      //////////////cout <<"You did get hereL " << filename << endl;
      vector<string> pdbs;
      string tmp;
      while (inFile >> tmp) pdbs.push_back(tmp);
  
      for (int i=0; i<pdbs.size(); i++) {
        //////////////cout <<"Reading: " << pdbs[i] <<endl;
        db.read_pdb(pdbs[i]);
        //////////////cout <<"And now we are here: " << endl;
        emit documentChanged();
        //return true;
      }
  }
  
  //Read in pdb
  if (filename.contains(".ent") || filename.contains(".pdb")) {
    //////////////cout <<filename.latin1()<<endl;
    //exit(0);
    db.read_pdb(filename.latin1());
    //db.read_pdb2(filename.latin1());
    //////////////cout <<"Getting ready to emit the damned signal: " << endl;
    emit documentChanged();
    //////////////cout <<"you have emitted documentChagned(): " << endl;
    return true;
  }

  //////////////cout <<"You are here in doc "<< filename << endl;
  if (filename.contains(".sdf") || filename.contains(".SDF")
     ||filename.contains(".mol")) 
  {
    //string a = filename.latin1();
    if (db.read_sd(filename.latin1(), true)) {
    
    	emit documentChanged();
	return true;
    } else {
        return false;
    }
  }
  
  if (filename.contains(".ddb") ) {
     db.readDDB(filename);
	emit documentChanged();
        return true;
  } 
 
  if (filename.contains(".mae") ) {
     if (db.readMAE(filename)) {
        emit documentChanged();
        return true;
     }
     return false;
  }
  
  //This is were you will add the code to read the sdfx file type

}

bool XmodelDoc::isModified() const
{
  return modified;
}






































