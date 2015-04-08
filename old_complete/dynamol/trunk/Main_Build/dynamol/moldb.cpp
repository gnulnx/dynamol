/***************************************************************************
                          moldb.cpp  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "moldb.h"
#include "sddialog.h"
#include "atomtyper.h"
#include <qerrormessage.h>
#include <qmessagebox.h>
#include <qprogressbar.h>
#include <qprogressdialog.h>
#include <qdatastream.h>
#include <qfile.h>
#include "energy.h"
#include "fragfactory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "pdbreader.h"

#include "protein.h"
#include "chain.h"
#include "fragment.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"

//Dynatype Include
#include "../dynatype/molecule.h"
#include "../dynatype/dtype.h"
#include "moladapter.h"

void fixBondOrder(bond *bd);

molDB::molDB(){
   signalBlock = false;
   setMolToBegin();
   currentMol = mols.begin();
  
   molecule *mol;
   renList = new list<molecule *>;

   fragGen = new fragFactory();
}
molDB::~molDB(){
}

list<molecule *>  molDB::getAllMols()             {return mols;};
list<protein *>   molDB::getALLProts()            {return prots;};
int               molDB::numOfMols()              {return mols.size();};
int               molDB::numOfProts()             {return prots.size();};
void              molDB::setProtToBegin()         {this->currentProt = prots.begin();};
protein           *molDB::getCurrentProt()        {return *currentProt;};
void              molDB::setFragToBegin()         {this->currentFrag = frags.begin();};
fragment          *molDB::getCurrentFrag()        {return *currentFrag;};
list<molecule *>  *molDB::getRenderList()         {return renList;};
molecule          *molDB::getCurrentRen()         {return *currentRen;};
void              molDB::setRenListToBegin()      {this->currentRen = renList->begin();};
int               molDB::renSize()                {return this->renList->size();};


void molDB::read_pdb(string file) { //try to read it all in at once
  /*
    Call the pdbReader::readPDB
    This returns a temporary list of protein strucutres....what about changing this to
    have support for DNA && just other plain molecules.
  */
  pdbReader reader;
  list<protein *> tmpProts;
  reader.readPDB(file, tmpProts);
  list<protein *>::iterator it;
  it = tmpProts.begin();
  //Now lets renumber the atoms in the protein
  for (it; it != tmpProts.end(); it++) {
     protein *prot = *it;
     for (int i=0; i<prot->atoms.size(); i++) {
     	prot->atoms[i]->setNum(i+1);
	prot->atoms[i]->atoms.clear();
     }
     for (int i=0; i<prot->bonds.size(); i++) {
     	
	bond *bd = prot->bonds[i];
	bd->setNum(i+1);
	atom *atm1 = bd->toAtom();
	atom *atm2 = bd->fromAtom();
	
	atm1->addAtom(atm2);
	atm2->addAtom(atm1);
	
     }
     //Now lets assign n-Terminal and c-Terminal
     //This is Dynamol specific
     for (int i=0; i<prot->chains.size(); i++) {
        fragment *fragStart = prot->chains[i]->frags[0];
	fragment *fragEnd = prot->chains[i]->frags[prot->chains[i]->frags.size()-1];
	fragStart->cTer = true;
	fragEnd->nTer = true;
     }
  }
  
  /*
    Now we add the new proteins to the list<protein *> prots
    We also emit the signal newProtein(protein *) which is recieved by
    molListView::addProtein(protein *);
  */
  it = tmpProts.begin();
  while (it != tmpProts.end() ) {
    prots.push_back(*it);
    
    protein *prot = *it;
    prot->metalCheck();
    
    emit newProtein(*it);   
    it++;
  }
  tmpProts.clear();
  
  
}


void molDB::read_mol2(string file, vector<molecule *> *currMols) {
  ifstream inFile;
//  vector<molecule *> currMols;
  string holdStr;
  inFile.open(file.c_str(), ios::in);
  
  if (!inFile) {
    return;
  }
  
  int count =0; 
  while (!inFile.eof() ) { 
     molecule *holdMol = new molecule();
     holdStr = ""; 
     bool fileEnd = false;
     //while (getline(inFile, holdStr)) {
     while (!inFile.eof()) {
       getline(inFile, holdStr);
       if (inFile.eof()) {
           fileEnd = true;
           break;
       }

       if (holdStr == "@<TRIPOS>MOLECULE") {
         break;
       }
     }
     if (fileEnd) {
	break;
     }
     getline(inFile, holdStr);
     QString qName = holdStr;
     qName.replace(' ', "_");
     if (holdStr != "") {
        holdMol->setName(qName.latin1()); //set the molecule name
     } else {
        holdMol->setName("mol");
     }
  int num, numOfAtoms, numOfBonds, from , to, test, atomicNum;
  string name, type;
  double x, y, z;
  char buffer[80];
  
  inFile >> numOfAtoms >> numOfBonds;
  while (inFile >> holdStr) {
    if (holdStr == "@<TRIPOS>ATOM") {
      break;
    }
  }
  string line;
  getline(inFile, line); //get the rest of the @<TRIPOS>ATOM line
  atomicNum = 0;
  float charge = 0;
  string subName;
  int subId;
  for (int i=0; i<numOfAtoms; i++) {
    string line;
    getline(inFile, line);
    
    istringstream ss(line, ios::in);
    ss >> num >> name >> x >> y >> z >> type >> subId >> subName >> charge;
    atomicNum = SYM2AN(name);
    atom *atm = holdMol->addAtom(num, name, x, y, z, atomicNum);
    atm->setCharge(charge);
  }
  inFile >> holdStr;

  //Reading in Bonds
  string tmpOrder; //need string because of ar in mol2 files
  /*  112   110   111    2
      113   110   120    1
      114   112   113    1
      115   113   114   ar
      116   113   115   ar
  */
  for (int i=0; i<numOfBonds; i++) {
    inFile >> num >> from >> to >> tmpOrder;
    if (tmpOrder == "1" || tmpOrder == "am")
      holdMol->addBond(num, from, to, 1);
    else if (tmpOrder == "2")
      holdMol->addBond(num, from, to, 2);
    else if (tmpOrder == "3")
      holdMol->addBond(num, from, to, 3);
    else if (tmpOrder == "ar")
      holdMol->addBond(num, from, to, 4);
    else
      holdMol->addBond(num, from, to, 1);
  }

  //This section will reassign singel && double bonds to the tripos aromatic
   
  for (int i=0; i<holdMol->bonds.size(); i++) {
      bond *bd = holdMol->bonds[i];
      if (bd->order == 4) {
         bd->order = 2;
         fixBondOrder(bd);
      }
   }

  //inFile.close();dd
  for (int i=0; i<holdMol->atoms.size(); i++) {
    float *cd = holdMol->atoms[i]->fCoords;
  }
  for (int i=0; i<holdMol->bonds.size(); i++) {
    bond *bd = holdMol->bonds[i];
  }
  holdMol->updateValence();
  if (currMols)
     currMols->push_back(holdMol);

  emit newMolecule(holdMol);
  }
  inFile.close();
  return;
}

void fixBondOrder(bond *bd) {
   molecule *mol = dynamic_cast<molecule *>(bd->getParent());   

   if (bd->order == 2) {
      for (int i=0; i<bd->from->atoms.size(); i++) {
         bond *tmpBD = mol->getBond(bd->from, bd->from->atoms[i]);
         if (tmpBD->order == 4) {
            tmpBD->order = 1;
            fixBondOrder(tmpBD);
         }
      }
      
      for (int i=0; i<bd->to->atoms.size(); i++) {
         bond *tmpBD = mol->getBond(bd->to, bd->to->atoms[i]);
         if (tmpBD->order == 4) {
            tmpBD->order = 1;
            fixBondOrder(tmpBD);
         }
      }
   } else
   if (bd->order == 1) {
      for (int i=0; i<bd->from->atoms.size(); i++) {
         bond *tmpBD = mol->getBond(bd->from, bd->from->atoms[i]);
         if (tmpBD->order == 4) {
            tmpBD->order = 2;
            fixBondOrder(tmpBD);
         }
      }
      
      for (int i=0; i<bd->to->atoms.size(); i++) {
         bond *tmpBD = mol->getBond(bd->to, bd->to->atoms[i]);
         if (tmpBD->order == 4) {
            tmpBD->order = 2;
            fixBondOrder(tmpBD);
         }
      }
   } else {
   }
   
}

int molDB::read_sd(string file, bool prompt) {
  //This section is simply to estimate how many records there are to be read
  long int l, m;
  ifstream f(file.c_str(), ios::in);
  l = f.tellg();
  f.seekg (0, ios::end);
  m = f.tellg();
  f.close();

  long int size = m-l;
  long int estRecordNum = size/4854;
 
  ifstream inFile(file.c_str(), ios::in);
  if (!inFile) {
    return 0;
  }

  sdFile = file;
  

  //First thing we do is scan the file for the $$$$ to determine the number of molecules
  string tmpString;
  int molCount = 0;
  QString label;
  label.setNum(estRecordNum);
  QString LABEL = "Estimated Structures to Scan: ";
  LABEL += label;
  QProgressDialog fileCheck( LABEL, "Cancel", estRecordNum,
                          0, "SDF Scan", TRUE );

  fileCheck.show();
  fileCheck.setProgress(0);
  while (inFile >> tmpString) {
    if (tmpString == "$$$$") molCount++;
    fileCheck.setProgress(molCount);
    if (fileCheck.wasCancelled()) return 0;
  }
  fileCheck.hide();
  
  if (molCount == 0) {
	molCount = 1;
  }

  if (molCount == 1) {
     vector<molecule *> mols;
     getSdRange(0, 1, mols);
  } else {
  if (prompt) {
     dialog = new sdDialog(0, "sdDialog", true, molCount);
     if ( dialog->exec() == sdDialog::Accepted ) {
       int from = dialog->fromEdit->text().toInt()-1;
       int to = dialog->toEdit->text().toInt()-1;
       vector<molecule *> mols;
       getSdRange(from, to-from, mols);
     }
     delete dialog;
  }
  }
  return molCount;
}

bool molDB::readMAE(QString fileName) {
   ifstream inFile(fileName.latin1(), ios::in);
   if (!inFile) {
      return false;
   }
   //scan the file to determine how many records mae records there are.
   
   string line;
   int count = 0;
   while ( !inFile.eof() ) {
      getline(inFile, line);
      QString qLine = line;
      if (qLine.contains("f_m_ct {") ) {
         count++;
      }
   }
   inFile.close();
   inFile.clear();
   
   if (count == 0) {
	count = 1;
  }

  int from = 1;
  int to = 2;
  if (count == 1) {
     vector<molecule *> mols;
     getSdRange(0, 1, mols);
     from = 1;
     to = 2;
  } else {
     dialog = new sdDialog(0, "Mae Dialog", true, count);
     if ( dialog->exec() == sdDialog::Accepted ) {
       from = dialog->fromEdit->text().toInt();
       to = dialog->toEdit->text().toInt();
       vector<molecule *> mols;
       //getSdRange(from, to-from, mols);
     }
     delete dialog;
  }
  
  inFile.open(fileName.latin1(), ios::in);
  count = 0;
  while ( count <= from ) {
     getline(inFile, line);
     QString qLine = line;
     if (qLine.contains("f_m_ct {")) count++;
     if (inFile.eof()) break;
  }
  //int check = 0;
  //cin >> check; 
  //Start Reading records
  //int count = from;
   int total = to-from;
   int molCount = count;

   QString LABEL = "Structures to Read:  ";
   QString label; label.setNum(total);
   LABEL += label;
   QProgressDialog fileCheck( LABEL, "Cancel", total,
                          0, "SDF Scan", FALSE );

   fileCheck.show();


  //while ( molCount < to ) {
   for (int i=0; i<total; i++) {
      fileCheck.setProgress(i+1);
      molecule *mol = new molecule;
      //Read property section section
      vector<QString> props;
      while (true) {
         getline(inFile, line);
         QString qLine = line;
         if (qLine.contains(":::")) break;
         props.push_back(qLine);
      }  
      
      //Read values for properties
      vector<QString> values;
      for (int i=0; i<props.size(); i++) {
         getline(inFile, line);
         QString qLine = line;
         values.push_back(qLine);
      }  
      
      getline(inFile, line);
      QString qLine = line;
      qLine.stripWhiteSpace();
      if (!qLine.contains("m_atom") ) {
         return false;
      }
      
      int a, b;
      for (int i=0; i<line.size(); i++) {
         if (line[i] == '[') a = i;
         if (line[i] == ']') {b = i; break;}
      }
      QString qAtomNum = line.substr(a+1, b-(a+1));
      
      getline(inFile, line); // # First column is atom index #
      vector<QString> Defines;
      int xIndex, yIndex, zIndex, chrgIndex, forChgIndes, atomicNumIndex;
      count = 0;
      while (true) {
        getline(inFile, line);
        QString qLine = line;
        if (qLine.contains(":::")) break;
        Defines.push_back(qLine);
        if (qLine.contains("r_m_x_coord")) xIndex = count;
        else if (qLine.contains("r_m_y_coord")) yIndex = count;
        else if (qLine.contains("r_m_z_coord")) zIndex = count;
        else if (qLine.contains("r_m_charge1")) chrgIndex = count;
        else if (qLine.contains("i_m_atomic_number")) atomicNumIndex = count;
        count++;
      }
           
      string tmp;
      while (true) {
         float x, y, z, charge;
         x = y = z = charge = 0;
         int AN, index;
         AN = index = -1;
         inFile >> tmp; //atom index
         QString qIndex = tmp;
         if (qIndex.contains(":::"))  break;
         else index = qIndex.toInt();
         for (int i=0; i<Defines.size(); i++) {
            inFile >> tmp;
            QString qTmp = tmp;
            int quoteCount = qTmp.contains("\"");
            if (quoteCount == 1) {
               while (true) {
                 inFile >> tmp;
                 qTmp = tmp;
                 if (qTmp.contains("\"")) break;
              }  
            }
            qTmp = tmp;
            if (i == xIndex) x = qTmp.toFloat();
            if (i == yIndex) y = qTmp.toFloat();
            if (i == zIndex) z = qTmp.toFloat();
            if (i == chrgIndex) charge = qTmp.toFloat();
            if (i == atomicNumIndex) AN = qTmp.toInt();
         }
         string sym = AN2SYM(AN);
         mol->addAtom(index, sym, x, y, z, AN);
         
      }
      
      getline(inFile, line);
      getline(inFile, line);
      getline(inFile, line);
      getline(inFile, line); //# First column is bond index #
      
      vector<QString> bondParams;
      count = 0;
      int fIndex, tIndex, orderIndex;
      fIndex = tIndex = orderIndex = -1;
      //read in the param section down to :::
      while (true) {
         getline(inFile, line);
         QString qLine = line;
         if( qLine.contains(":::") ) break;
         bondParams.push_back(qLine);
         if (qLine.contains("i_m_from") && !qLine.contains("i_m_from_rep")) fIndex = count;
         else if (qLine.contains("i_m_to") && !qLine.contains("i_m_to_rep")) tIndex = count;
         else if (qLine.contains("i_m_order")) orderIndex = count;
         count++;
      }
      getline(inFile, line);
     // ////////////cout <<"fIndex: " << fIndex << endl;
     // ////////////cout <<"tIndex: " << tIndex << endl;
     // ////////////cout <<"orderIndex: " << orderIndex << endl;
     // ////////////cout <<line<<endl;

      //now read in the bond section
      while (true) {
          inFile >> tmp;
	  QString qTmp = tmp;
 	  int bondNum = -1;
          int fromNum, toNum, orderNum;
          fromNum = toNum = orderNum = -1;
	  if (qTmp.contains(":::") ) break;
	  else bondNum = qTmp.toInt();
          for (int i=0; i<bondParams.size(); i++) {
             inFile >> tmp;
             qTmp = tmp;
             if (i == fIndex) fromNum = qTmp.toInt();
             if (i == tIndex) toNum = qTmp.toInt();
             if (i == orderIndex) orderNum = qTmp.toInt();
          }
          mol->addBond(bondNum, fromNum, toNum, orderNum);
      }
     
      //////////////cout <<"mol->bonds.size(): " << mol->bonds.size() << endl; 
       mol->updateValence();

       mols.push_back(mol);
       emit newMolecule(mol);
       while ( true ) {
          getline(inFile, line);
          QString qLine = line;
          //////////////cout <<"qLine: " << qLine << endl;
          if (qLine.contains("f_m_ct {")) {
	 //    ////////////cout <<"BREAKING"<<endl; 
             break;
          }
          if (inFile.eof()) return true;
       }
       molCount++;
      // ////////////cout <<"molCount: " << molCount << endl;
       //////////////cout <<"to: " << to << endl;
       //return true;
       //int test = 0;
       //cin >> test;
   }
  
  
}

void molDB::setMolToBegin() {
  //////////////cout <<"you are in setMolToBegin(): " << endl;
  currentMol = mols.begin();
}



molecule *molDB::getMol() {
  //////////////cout <<"You are in the getMol: " << &currentMol << endl;
  return *currentMol;
}

int molDB::nextMol() {
  currentMol++;
  if (currentMol != mols.end()) {
    return 1;
  } else {
    return 0;
  }
}

int   molDB::nextRen() {
  currentRen++;
  if (currentRen != renList->end()) {
    return 1;
  } else {
    return 0;
  }
}
 

int molDB::prevMol() {
  currentMol--;
  if (currentMol != mols.begin()) {
    return 1;
  } else {
    return 0;
  }
}
int   molDB::prevRen() {
  currentRen--;
  if (currentRen != renList->begin()) {
    return 1;
  } else {
    return 0;
  }
}


int   molDB::nextProt() {
  currentProt++;
  if (currentProt != prots.end()) {
    return 1;
  } else {
    return 0;
  }
};
int   molDB::prevProt() {
  currentProt--;
  if (currentProt != prots.begin()) {
    return 1;
  } else {
    return 0;
  }
};

int molDB::nextFrag() {
  currentFrag++;
  if (currentFrag != frags.end()) {
    return 1;
  } else {
    return 0;
  }
};
int molDB::prevFrag() {
   currentFrag--;
  if (currentFrag != frags.begin()) {
    return 1;
  } else {
    return 0;
  }
};
  


int molDB::SYM2AN(string type) {
  QString qType = type;
   //  //////////cout <<"type size: " << type.size() << endl;
   if (qType.contains("Cl") || qType.contains("CL"))
      return 17;
  
   int atomicNum = 0;
   if (type[0] == 'H' && type.size() == 1) {
      atomicNum = 1;
   } else if (type[0] == 'H' && type[1] == 'e') {
      atomicNum = 2;
   } else if (type[0] == 'l' && type[1] == 'i') {
      atomicNum = 3;
   } else if (type[0] == 'B' && type[1] == 'e') {
      atomicNum = 4;
   } else if (type[0] == 'B' && type.size() == 1) {
      atomicNum = 5;
   } else if (type[0] == 'C' && type.size() == 1) {
      atomicNum = 6;
   } else if (type[0] == 'N' && type.size() == 1) {
      atomicNum = 7;
   } else if (type[0] == 'O' && type.size() == 1) {
      atomicNum = 8;
   } else if (type[0] == 'F') {
      atomicNum = 9;
   } else if (type[0] == 'N' && type[1] == 'e') {
      atomicNum = 10;
   } else if (type[0] == 'N' && type[1] == 'a') {
      atomicNum = 11;
   } else if (type[0] == 'M' && type[1] == 'g') {
      atomicNum = 12;
   } else if (type[0] == 'A' && type[1] == 'l') {
      atomicNum = 13;
   } else if (type[0] == 'S' && type[1] == 'i') {
      atomicNum = 14;
   } else if (type[0] == 'P' && type.size() == 1) {
      atomicNum = 15;
   } else if (type[0] == 'S' && type.size() == 1) {
      atomicNum = 16;
   } else if (type[0] == 'C' && type[1] == 'l') {
      atomicNum = 17;
   } else if (type[0] == 'A' && type[1] == 'r') {
      atomicNum = 18;
   } else if (type[0] == 'K') {
      atomicNum = 19;
   } else if (type[0] == 'C' && type[1] == 'a') {
      atomicNum = 20;
   } else if (type[0] == 'S' && type[1] == 'c') {
      atomicNum = 21;
   } else if (type[0] == 'T' && type[1] == 'i') {
      atomicNum = 22;
   } else if (type[0] == 'V') {
      atomicNum = 23;
   } else if (type[0] == 'C' && type[1] == 'r') {
      atomicNum = 24;
   } else if (type[0] == 'M' && type[1] == 'n') {
      atomicNum = 25;
   } else if (type[0] == 'F' && type[1] == 'e') {
      atomicNum = 26;
   } else if (type[0] == 'C' && type[1] == 'o') {
      atomicNum = 27;
   } else if (type[0] == 'N' && type[1] == 'i') {
      atomicNum = 28;
   } else if (type[0] == 'C' && type[1] == 'u') {
      atomicNum = 29;
   } else if (type[0] == 'Z' && (type[1] == 'n' || type[1] == 'N' )) {
      atomicNum = 30;
   } else if (type[0] == 'G' && type[1] == 'a') {
      atomicNum = 31;
   } else if (type[0] == 'G' && type[1] == 'e') {
      atomicNum = 32;
   } else if (type[0] == 'A' && type[1] == 's') {
      atomicNum = 33;
   } else if (type[0] == 'S' && type[1] == 'e') {
      atomicNum = 34;
   } else if (type[0] == 'B' && type[1] == 'r') {
      atomicNum = 35;
   } else if (type[0] == 'K' && type[1] == 'r') {
      atomicNum = 36;
   } else if (type[0] == 'R' && type[1] == 'b') {
      atomicNum = 37;
   } else if (type[0] == 'S' && type[1] == 'r') {
      atomicNum = 38;
   } else if (type[0] == 'Y') {
      atomicNum = 39;
   } else if (type[0] == 'Z' && type[1] == 'r') {
      atomicNum = 40;
   } else if (type[0] == 'M' && type[1] == 'o') {
      atomicNum = 42;
   } else if (type[0] == 'T' && type[1] == 'c') {
      atomicNum = 43;
   } else if (type[0] == 'R' && type[1] == 'u') {
      atomicNum = 44;
   } else if (type[0] == 'R' && type[1] == 'h') {
      atomicNum = 45;
   } else if (type[0] == 'P' && type[1] == 'd') {
      atomicNum = 46;
   } else if (type[0] == 'A' && type[1] == 'g') {
      atomicNum = 47;
   } else if (type[0] == 'C' && type[1] == 'd') {
      atomicNum = 48;
   } else if (type[0] == 'I' && type[1] == 'n') {
      atomicNum = 49;
   } else if (type[0] == 'S' && type[1] == 'n') {
      atomicNum = 50;
   } else if (type[0] == 'S' && type[1] == 'b') {
      atomicNum = 51;
   } else if (type[0] == 'T' && type[1] == 'e') {
      atomicNum = 52;
   } else if (type[0] == 'I') {
      atomicNum = 53;
   } else if (type[0] == 'X' && type[1] == 'e') {
      atomicNum = 54;
   } else if (type[0] == 'C' && type[1] == 's') {
      atomicNum = 55;
   } else if (type[0] == 'B' && type[1] == 'a') {
      atomicNum = 56;
   } else if (type[0] == 'L' && type[1] == 'a') {
      atomicNum = 57;
   } else if (type[0] == 'H' && type[1] == 'f') {
      atomicNum = 58;
   } else if (type[0] == 'P' && type[1] == 'r') {
      atomicNum = 59;
   } else if (type[0] == 'N' && type[1] == 'd') {
      atomicNum = 60;
   } else if (type[0] == 'P' && type[1] == 'm') {
      atomicNum = 61;
   } else if (type[0] == 'S' && type[1] == 'm') {
      atomicNum = 62;
   } else if (type[0] == 'E' && type[1] == 'u') {
      atomicNum = 63;
   } else if (type[0] == 'G' && type[1] == 'd') {
      atomicNum = 64;
   } else if (type[0] == 'T' && type[1] == 'b') {
      atomicNum = 65;
   } else if (type[0] == 'D' && type[1] == 'y') {
      atomicNum = 66;
   } else if (type[0] == 'H' && type[1] == 'o') {
      atomicNum = 67;
   } else if (type[0] == 'E' && type[1] == 'r') {
      atomicNum = 68;
   } else if (type[0] == 'T' && type[1] == 'm') {
      atomicNum = 69;
   } else if (type[0] == 'Y' && type[1] == 'b') {
      atomicNum = 70;
   } else if (type[0] == 'L' && type[1] == 'u') {
      atomicNum = 71;
   } else if (type[0] == 'H' && type[1] == 'f') {
      atomicNum = 72;
   } else if (type[0] == 'T' && type[1] == 'a') {
      atomicNum = 73;
   } else if (type[0] == 'W') {
      atomicNum = 74;
   } else if (type[0] == 'R' && type[1] == 'e') {
      atomicNum = 75;
   } else if (type[0] == 'O' && type[1] == 's') {
      atomicNum = 76;
   } else if (type[0] == 'I' && type[1] == 'r') {
      atomicNum = 77;
   } else if (type[0] == 'P' && type[1] == 't') {
      atomicNum = 78;
   } else if (type[0] == 'A' && type[1] == 'u') {
      atomicNum = 79;
   } else if (type[0] == 'H' && type[1] == 'g') {
      atomicNum = 80;
   } else if (type[0] == 'T' && type[1] == 'i') {
      atomicNum = 81;
   } else if (type[0] == 'P' && type[1] == 'b') {
      atomicNum = 82;
   } else if (type[0] == 'B' && type[1] == 'i') {
      atomicNum = 83;
   } else if (type[0] == 'P' && type[1] == 'o') {
      atomicNum = 84;
   } else if (type[0] == 'A' && type[1] == 't') {
      atomicNum = 85;
   } else if (type[0] == 'R' && type[1] == 'n') {
      atomicNum = 86;
   } else if (type[0] == 'F' && type[1] == 'r') {
      atomicNum = 87;
   } else if (type[0] == 'R' && type[1] == 'a') {
      atomicNum = 88;
   } else if (type[0] == 'A' && type[1] == 'c') {
      atomicNum = 89;
   } else if (type[0] == 'T' && type[1] == 'h') {
      atomicNum = 90;
   } else if (type[0] == 'P' && type[1] == 'a') {
      atomicNum = 91;
   } else if (type[0] == 'U') {
      atomicNum = 92;
   } else if (type[0] == 'N' && type[1] == 'p') {
      atomicNum = 93;
   } else if (type[0] == 'P' && type[1] == 'u') {
      atomicNum = 94;
   } else if (type[0] == 'A' && type[1] == 'm') {
      atomicNum = 95;
   } else if (type[0] == 'C' && type[1] == 'm') {
      atomicNum = 96;
   } else if (type[0] == 'B' && type[1] == 'k') {
      atomicNum = 97;
   } else if (type[0] == 'C' && type[1] == 'f') {
      atomicNum = 98;
   } else if (type[0] == 'E' && type[1] == 's') {
      atomicNum = 99;
   } else if (type[0] == 'F' && type[1] == 'm') {
      atomicNum = 100;
   } else if (type[0] == 'M' && type[1] == 'd') {
      atomicNum = 101;
   } else if (type[0] == 'N' && type[1] == 'o') {
      atomicNum = 102;
   } else if (type[0] == 'L' && type[1] == 'r') {
      atomicNum = 103;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'q') {
      atomicNum = 104;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'p') {
      atomicNum = 105;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'h') {
      atomicNum = 106;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 's') {
      atomicNum = 107;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'o') {
      atomicNum = 108;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'e') {
      atomicNum = 109;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'n') {
      atomicNum = 110;
   }
  
   if (atomicNum == 0) {
  
  if (type[0] == 'H') {
      atomicNum = 1;
  } else if (type[0] == 'C' && type[1] != 'l') {
      atomicNum = 6;
  } else if (type[0] == 'N')  {
      atomicNum = 7;
  } else if (type[0] == 'O') {
      atomicNum = 8;
  } else if (type[0] == 'S' && type[1] != 'i') {
      atomicNum = 16;
  } else if (type[0] == 'P') {
      atomicNum = 15;
  } else if (type[0] == 'F') {
      atomicNum = 9;
  } else if (type[0] == 'C' && type[1] == 'l') {
      atomicNum = 17;
  } else if (type[0] == 's' && type[1] == 'i') {
      atomicNum = 41;
  } else if (type[0] == 'B' && type[1] == 'r') {
      atomicNum = 35;
  } else if (type[0] == 'I') {
      atomicNum = 53;
  } else if (type[0] == 'N' && type[1] == 'a') {
      atomicNum = 11;
  } else if (type[0] == 'K') {
      atomicNum = 19;
  } else if (type[0] == 'C' && type[1] == 'a') {
      atomicNum = 20;
  } else if (type[0] == 'L' && type[1] == 'i') {
      atomicNum = 3;
  } else if (type[0] == 'A' && type[1] == 'l') {
      atomicNum = 13;
  } else if (type[0] == 'A' && type[1] == 'u') {
      atomicNum = 79;
  } else {
      atomicNum = 0;
      //////////cout <<"Atom type not found!!!!!!!"<<endl;
  }
  }
    return atomicNum;
}

string molDB::AN2SYM(int an) {
   if (an == 1) return "H";
   else if (an == 2) return "He";
   else if (an == 3) return "li";
   else if (an == 4) return "Be";
   else if (an == 5) return "B";
   else if (an == 6) return "C";
   else if (an == 7) return "N";
   else if (an == 8) return "O";
   else if (an == 9) return "F";
   else if (an == 10) return "Ne";
   else if (an == 11) return "Na";
   else if (an == 12) return "Mg";
   else if (an == 13) return "Al";
   else if (an == 14) return "Si";
   else if (an == 15) return "P";
   else if (an == 16) return "S";
   else if (an == 17) return "Cl";
   else if (an == 18) return "Ar";
   else if (an == 19) return "K";
   else if (an == 20) return "Ca";
   else if (an == 21) return "Sc";
   else if (an == 22) return "Ti";
   else if (an == 23) return "V";
   else if (an == 24) return "Cr";
   else if (an == 25) return "Mn";
   else if (an == 26) return "Fe";
   else if (an == 27) return "Co";
   else if (an == 28) return "Ni";
   else if (an == 29) return "Cu";
   else if (an == 30) return "Zn";
   else if (an == 31) return "Ga";
   else if (an == 32) return "Ge";
   else if (an == 33) return "As";
   else if (an == 34) return "Se";
   else if (an == 35) return "Br";
   else if (an == 36) return "Kr";
   else if (an == 37) return "Rb";
   else if (an == 38) return "Sr";
   else if (an == 39) return "Y";
   else if (an == 40) return "Zr";
   else if (an == 42) return "Mo";
   else if (an == 43) return "Tc";
   else if (an == 44) return "Ru";
   else if (an == 45) return "Rh";
   else if (an == 46) return "Pd";
   else if (an == 47) return "Ag";
   else if (an == 48) return "Cd";
   else if (an == 49) return "In";
   else if (an == 50) return "Sn";
   else if (an == 51) return "Sb";
   else if (an == 52) return "Te";
   else if (an == 53) return "I";
   else if (an == 54) return "Xe";
   else if (an == 55) return "Cs";
   else if (an == 56) return "Ba";
   else if (an == 57) return "La";
   else if (an == 58) return "Hf";
   else if (an == 59) return "Pr";
   else if (an == 60) return "Nd";
   else if (an == 61) return "Pm";
   else if (an == 62) return "Sm";
   else if (an == 63) return "Eu";
   else if (an == 64) return "Gd";
   else if (an == 65) return "Tb";
   else if (an == 66) return "Dy";
   else if (an == 67) return "Ho";
   else if (an == 68) return "Er";
   else if (an == 69) return "Tm";
   else if (an == 70) return "Yb";
   else if (an == 71) return "Lu";
   else if (an == 72) return "Hf";
   else if (an == 73) return "Ta";
   else if (an == 74) return "W";
   else if (an == 75) return "Re";
   else if (an == 76) return "Os";
   else if (an == 77) return "Ir";
   else if (an == 78) return "Pt";
   else if (an == 79) return "Au";
   else if (an == 80) return "Hg";
   else if (an == 81) return "Ti";
   else if (an == 82) return "Pb";
   else if (an == 83) return "Bi";
   else if (an == 84) return "Po";
   else if (an == 85) return "At";
   else if (an == 86) return "Rn";
   else if (an == 87) return "Fr";
   else if (an == 88) return "Ra";
   else if (an == 89) return "Ac";
   else if (an == 90) return "Th";
   else if (an == 91) return "Pa";
   else if (an == 92) return "U";
   else if (an == 93) return "Np";
   else if (an == 94) return "Pu";
   else if (an == 95) return "Am";
   else if (an == 96) return "Cm";
   else if (an == 97) return "Bk";
   else if (an == 98) return "Cf";
   else if (an == 99) return "Es";
   else if (an == 100) return "Fm";
   else if (an == 101) return "Md";
   else if (an == 102) return "No";
   else if (an == 103) return "Lr";
   else if (an == 104) return "Unq";
   else if (an == 105) return "Unp";
   else if (an == 106) return "Unh";
   else if (an == 107) return "Uns";
   else if (an == 108) return "Uno";
   else if (an == 109) return "Une";
   else if (an == 110) return "Unn";
   else {
   	////////////cout <<"Could not convert atomic number: " << an << " to symbol...please fix me!"<<endl;
   }
}

bool molDB::checkIntNum(string &str) {
  bool bad = true;
  for (int i=0; i<str.size(); i++) {
     bool bad = true;
     if (str[i] == '0') bad = false;
     else if(str[i] == '1') bad = false;
     else if (str[i] == '2') bad = false;
     else if (str[i] == '3') bad = false;
     else if (str[i] == '4') bad = false;
     else if (str[i] == '5') bad = false;
     else if (str[i] == '6') bad = false;
     else if (str[i] == '7') bad = false;
     else if (str[i] == '8') bad = false;
     else if (str[i] == '9') bad = false;
     else if (str[i] == '+') bad = false;
     else if (str[i] == '-') bad = false;
     else if (str[i] == ' ') bad = false;
     
     if (bad) return false;
  }
  return true;
}
 
bool molDB::checkFloatNum(string &str) {
bool bad = true;
  for (int i=0; i<str.size(); i++) {
     bool bad = true;
     if (str[i] == '0') bad = false;
     else if (str[i] == '1') bad = false;
     else if (str[i] == '2') bad = false;
     else if (str[i] == '3') bad = false;
     else if (str[i] == '4') bad = false;
     else if (str[i] == '5') bad = false;
     else if (str[i] == '6') bad = false;
     else if (str[i] == '7') bad = false;
     else if (str[i] == '8') bad = false;
     else if (str[i] == '9') bad = false;
     else if (str[i] == '+') bad = false;
     else if (str[i] == '-') bad = false;
     else if (str[i] == '.') bad = false;
     else if (str[i] == ' ') bad = false;
     
     if (bad) return false;
  }
  return true;
}
 
void molDB::getSdRange(int start, int num, vector<molecule *> &molVec) {
  ifstream inFile;
  //mols.clear();
  
  inFile.open(sdFile.c_str(), ios::in);
  if (!inFile) {
    return;
  }

  //start = 1;
  //Move down to the correct sd Record
  string tmpString;
  if (start > 1) {
    int count = 1;
    while (inFile >> tmpString) {
      if (tmpString == "$$$$") {
        count++;
        if (count == start) {
	   getline(inFile, tmpString); //get the rest of the line
	   break;
	}
      }
    }
  }


  QString LABEL = "Structures to Read:  ";
  QString label; label.setNum(num);
  LABEL += label;
  QProgressDialog fileCheck( LABEL, "Cancel", num,
                          0, "SDF Scan", FALSE );

  fileCheck.show();
  
  for (int i=0; i<num; i++) {
    fileCheck.setProgress(i);
    bool hasSulfer = false;
    molecule *mol = new molecule();

    string Name, tmp, atmNumString, bdNumString;
    getline(inFile, Name);
    QString qName = Name;
    qName.replace(' ', "_");
    if (Name != "") mol->setName(qName.latin1());
    else {
	    QString qName = sdFile;
	    int num = qName.contains('/');
	    QString qName2;
	    if (num == 0) qName2 = " ";
	    else qName2 = qName.section( '/', num, num );
	    ////////////cout <<"Setting name here"<<endl;
	    mol->setName(qName2.latin1());
    }
    getline(inFile, tmp);
    getline(inFile, tmp);
    getline(inFile, tmp);


    if (tmp.size() == 0) {
      QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"This error is likely due to an extra line in the SD header");
      delete mol;
      
      return;
    }
    
 
    if (tmp.size() < 6) {
      QMessageBox::critical( 0, "Dynamol", "Error in Sd File.  Read Aborted");
      delete mol;
      return;
    }
    atmNumString = tmp.substr(0,3);
    if (!checkFloatNum(atmNumString)) {
       QMessageBox::critical( 0, "Dynamol",
    	 "An error was encountered in the sd file.  Molecule read has been aborted\n"
    	 "Did not find an integer value for number of atoms");
	    delete mol;
	    return;
    }
    

    bdNumString =  tmp.substr(3,3);
    if (!checkIntNum(bdNumString)) {
    	 QMessageBox::critical( 0, "Dynamol",
    	 "An error was encountered in the sd file.  Molecule read has been aborted\n"
    	 "Did not find an integer value for number of bonds");
	    delete mol;
	    return;
    }
    
    int atmNum = atoi(atmNumString.c_str() );
    int bdNum = atoi(bdNumString.c_str() );
    for (int j=0; j<atmNum; j++) {
       float x, y, z;
       string sym;
      
       inFile >> x >> y >> z >> sym;
       if (sym == "P") hasSulfer = true;
       if (!inFile) {
          QMessageBox::critical( 0, "Dynamol",
          "An error was encountered in the sd file.  Molecule read has been aborted\n"
    	    "Line read failed!");
	       delete mol;
	       return;
      }
     
      getline(inFile, tmp);    //There is other information that you can read from the sd 
      int atomicNum = SYM2AN(sym);
      mol->addAtom(j+1, sym, x, y, z, atomicNum);
    }
   
    string line;
    for (int j=0; j<bdNum; j++) {
      int num, from, to, order;
      getline(inFile, line);
      QString qFrom = line.substr(0,3);
      QString qTo = line.substr(3,3);
      QString qOrder = line.substr(8,1);
      from =  qFrom.toInt();
      to = qTo.toInt();
      order = qOrder.toInt();
      
      mol->addBond(j+1, from, to, order); 
    }

    while (inFile >> tmp) {
      if (tmp == ">") {
        inFile >> tmp;
      	string name = tmp.substr(1,tmp.size()-2);
	getline(inFile, tmp);
	string data;
	getline(inFile, data);
        mol->addPropValuePair(name, data);
      }
      if (tmp.substr(0,4) == "$$$$") {
         break;
	 delete mol;
      }
    }
   getline(inFile, tmp); //just to get that last little bit
   int input = 0;

   mol->updateValence();
   molVec.push_back(mol);
   static int counter = 0;
   counter++;
   if (!signalBlock)
      emit newMolecule(mol);
      
   if (fileCheck.wasCancelled()) break;
  } 

  return;

}

void molDB::writeDDB(const char *fileName, molecule *mol, int append) {
  //ofstream outFile(file, ios::out);
  QFile file( fileName );
  if (append == 1) {
	file.open(IO_WriteOnly);//| IO_Append);
  } else {
     file.open( IO_WriteOnly );
  }
  QDataStream stream( &file ); // we will serialize the data into the file
  stream << mol->getName();   // serialize a string
  stream << (Q_INT32)mol->atoms.size() << mol->bonds.size();
  for (int i=0; i<mol->atoms.size(); i++) {
	atom *atm = mol->atoms[i];
	float *cd = atm->fCoords;
       	stream << atm->getSym() <<cd[0] << cd[1]<<cd[2] << atm->getCharge();
  }

  for (int i=0; i<mol->bonds.size(); i++) {
	bond *bd = mol->bonds[i];
	stream << bd->from->getNum() << bd->to->getNum() << bd->order;
  }   
}

void molDB::readDDB(const char *fileName) {
   QFile file( fileName );
   file.open( IO_ReadOnly );
   QDataStream stream( &file );
   QString qName; 
   int atomNum, bdNum;
   stream >> qName >> atomNum >> bdNum;
   string name = qName.latin1();
   molecule *mol = new molecule;
   mol->setName(name);
   QString qSym;
   float x, y, z, chg;
   for (int i=0; i<atomNum; i++) {
      stream >> qSym >> x >> y >> z >> chg;
      string sym = qSym.latin1();
      int atomicNum = SYM2AN(sym);
      mol->addAtom(i+1, sym, x, y, z, atomicNum);
   }

   int from, to, order;
   for (int i=0; i<bdNum; i++) {
     stream >> from >> to >> order;
     mol->addBond(i+1, from, to, order); 
   }
   
   emit newMolecule(mol); 
   
}

void molDB::writeMol2(const char *file, molecule *mol, int append) {
  //This provides default...aka bad types
  
  
  //dt::molecule *dMol = new dt::molecule;
  dt::molPtr dMol( new dt::molecule );
  molAdapter::mol2molecule(dMol, mol);
  dt::dType t;
  t.setGaffTypes(dMol);
  molAdapter::update(mol, dMol);
  
  //atomTyper *typer = new atomTyper;
  boost::shared_ptr<atomTyper> typer( new atomTyper );

  typer->type_mol2(mol);
  typer->gaff2Mol2(mol);
  
   ofstream outFile;
   if (append == 1) outFile.open(file, ios::app);
   else outFile.open(file, ios::out);
   //outFile.open(file, ios::out);

    
    //I think that the next thing that we want to do is actually copy the current molecule into another molecule so that
    // we can be sure that the atom numbering && stuff is right
   
   vector<int> oldNums;
    for (int i=0; i<mol->atoms.size(); i++) {
      atom *tmp = mol->atoms[ i ];
      oldNums.push_back( tmp->getNum() );
      tmp->setNum(i+1);
    }

    outFile <<"@<TRIPOS>MOLECULE"<<endl;
    outFile <<mol->getName() << endl;
    outFile << mol->getNumOfAtoms() << setw(10) << mol->getNumOfBonds() <<setw(10)<<"0  0  0"<< endl;
    outFile <<"SMALL"<<endl;
    outFile <<"NO_CHARGES"<<endl;
    outFile <<endl; //two blank lines


    outFile <<"@<TRIPOS>ATOM" <<endl;
    for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      //atm->setNum(i+1);
      float *cd = atm->fCoords;
      QString scd0; scd0.setNum(cd[0]).truncate(6); //Makes sure the number is truncated
      QString scd1; scd1.setNum(cd[1]).truncate(6); //Makes sure the number is truncated
      QString scd2; scd2.setNum(cd[2]).truncate(6); //Makes sure the number is truncated 
      //string sym =  typer->atomicNumToString(atm->getAN());
      string sym = AN2SYM(atm->getAN());	
      molecule *m = dynamic_cast<molecule *>(atm->parent);
      QString molName =  m->getName();
      molName.replace(' ', "_");
      m->setName(molName.latin1());
      outFile <<right<< setw(7) << i+1 <<" "<<left<< setw(7) << sym <<  setw(15) << scd0 << setw(15) << scd1 << setw(15) << scd2 << setw(15) << atm->getFFType() << setw(15) << m->getNum() << setw(16) << m->getName() << setw(16)<<atm->getCharge() << endl;    
    }

   outFile << "@<TRIPOS>BOND" << endl;
   for (int i=0; i<mol->bonds.size(); i++) {
     bond *bd = mol->bonds[ i ];
     outFile << i+1 << right << setw(15) << bd->from->getNum() << setw(15) << bd->to->getNum() << setw(15) << bd->order << endl;
   }

   //Now lets change the numbering back to what it was before
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *tmp = mol->atoms[ i ];
      tmp->setNum(oldNums[ i ] );
    }
   outFile << "@<TRIPOS>SUBSTRUCTURE" << endl; 
   outFile << "   1   UNK   1" << endl;
   outFile << endl; 
   //delete typer;
   outFile.close();
   outFile.clear();
}

void molDB::writePDB(char *file, molecule *mol, int append) {
  atomTyper *typer = new atomTyper;
  ofstream outFile;
  outFile.open(file, ios::out);

  outFile <<"COMPND   "<< mol->getName() << endl;
  outFile <<"AUTHOR     Xmodel"  <<endl;
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      atm->setNum(i+1);
      float *cd = atm->fCoords;
      QString scd0; scd0.setNum(cd[0]).truncate(6); //Makes sure the number is truncated
      QString scd1; scd1.setNum(cd[1]).truncate(6); //Makes sure the number is truncated
      QString scd2; scd2.setNum(cd[2]).truncate(6); //Makes sure the number is ttruncated 
      string sym =  typer->atomicNumToString(atm->getAN());
      outFile << left << setw(6) << "ATOM" << right << setw(5) << atm->getNum() <<"  " << left << setw(4) << sym;
      outFile <<"               "<<left << setw(8) << scd0 << setw(8) << scd1 << setw(8) << scd2 << endl;
      //outFile <<right<< setw(7) << i+1 <<" "<<left<< setw(7) << sym <<  setw(15) << cd[0] << setw(15) << cd[1] << setw(15) << cd[2] << setw(15) << atm->charge << endl;
    }

    /*
    for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[ i ];

      outFile << left << setw(6) << "CONECT" <<  right << setw(4) <<atm->getNum();
      for (int j=0; j<atm->atoms.size(); j++) {
        atom *tmp = atm->atoms[ j ];
        outFile << setw(4) << tmp->getNum();// << setw(4) << bd->order << endl;
      }
      outFile <<endl;
    }   */
  delete typer;
  outFile.close();
}

void molDB::writeSDF(const char *file, molecule *mol, int append) {
  //THis first section renumbers the atoms && bonds to make sure that everything writes correctly 
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
  
  //this->AN2SYM(1);
  for (int i=0; i<mol->atoms.size(); i++) {
     atom *atm = mol->atoms[i];
     string sym = molDB::AN2SYM(atm->getAN());
     atm->setSymbol( sym );
  }
  //Now lets make sure that all the atom->syms match the atomicNumbers
  
   ofstream outFile;
   if (append == 1) outFile.open(file, ios::app);
   else outFile.open(file, ios::out);
   
   if (!outFile) {
     QString qOutFile = file;
     QString message = "The file " + qOutFile + " wa not opened\n" + "Molecule not saved";
     QMessageBox::critical( 0, "Dynamol",message);
     return;
   }
   
   outFile << mol->getName() << endl;
   outFile <<"Dynamol 3D sdf file"<<endl;
   outFile <<endl;
   outFile << setw(3) << mol->atoms.size() << setw(3) << mol->bonds.size();
   for (int i=0; i<8; i++) {
     outFile << setw(3) << "0";
   }
   outFile << endl;
   
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      float *cd = atm->fCoords;
      QString scd0; scd0.setNum(cd[0]).truncate(6); //Makes sure the number is truncated
      QString scd1; scd1.setNum(cd[1]).truncate(6); //Makes sure the number is truncated
      QString scd2; scd2.setNum(cd[2]).truncate(6); //Makes sure the number is ttruncated 
      outFile << setw(10) << scd0 << setw(10) << scd1 << setw(10) << scd2;
      outFile <<" "<< left << setw(2) << atm->getSym().c_str()<<right;
      for (int i=0; i<5; i++) outFile << setw(3) << "0";
      outFile << endl;
   
   }
   
   for (int i=0; i<mol->bonds.size(); i++) {
     bond *bd = mol->bonds[i];
     outFile << setw(3) << bd->fromAtom()->getNum() << setw(3) << bd->toAtom()->getNum();
     outFile << setw(3) << bd->order;
     for (int i=0; i<3; i++) outFile << setw(3) << "0";
     outFile << endl;
   }
   outFile <<"M  END"<<endl;
   
   map<QString, QString>::iterator propIt = mol->propMap.begin();
   for (propIt; propIt != mol->propMap.end(); propIt++) {
   //for (int i=0; i<mol->propertyData.size(); i++) {
      QString name = propIt->first;
      QString value = propIt->second;  
      outFile << ">  <" << name << ">" << endl;
      outFile << value << endl;
      outFile << endl;
   }
   
   outFile << "$$$$" << endl;
   
}

void molDB::writeSDFX(const char *file, molecule *mol, int append) {
   //save the original atom numbering
   vector<int> originalAtomNums;
   for (int i=0; i<mol->atoms.size(); i++) {  
      int num = mol->atoms[i]->getNum();
      originalAtomNums.push_back(num);
      mol->atoms[i]->setNum(i+1);
   }
   
   ofstream outFile;
   if (append == 1) outFile.open(file, ios::app);
   else outFile.open(file, ios::out);
   
   if (!outFile) {
     return;
   }
   
   if (mol->rtti() < 13 ) outFile <<"@<MOLECULE>\t" << mol->getName() << endl;
   if (mol->rtti() == 13) outFile <<"@<CHAIN>\t" << mol->getName() << endl;
   if (mol->rtti() == 14) outFile <<"@<PROTEIN>\t" << mol->getName() << endl;
   outFile <<"Dynamol Inc."<<endl;
   outFile <<"Force_Field:" << setw(15) << mol->ffTypes << endl;
   outFile <<"Charges:"<< setw(15) << mol->chargeType << endl;
   outFile  << mol->atoms.size() << " " << mol->bonds.size() << endl;
   outFile <<"%ATOMS"<<endl;
   
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      float *cd = atm->fCoords;
      QString scd0; scd0.setNum(cd[0]).truncate(6); //Makes sure the number is truncated
      QString scd1; scd1.setNum(cd[1]).truncate(6); //Makes sure the number is truncated
      QString scd2; scd2.setNum(cd[2]).truncate(6); //Makes sure the number is ttruncated 
      outFile <<atm->getAtomicNum()<< setw(4)<<atm->getSym()<<setw(10) << scd0 << setw(10) << scd1 << setw(10) << scd2;
      outFile << setw(15) << atm->getCharge() << setw(10) <<atm->getFFType() << setw(10);
      if (mol->rtti() >= 13) {
         fragment *frag = dynamic_cast<fragment *>(atm->getParent());
         string tmp = frag->getName();
         typeFrag(frag);
         chain *ch = dynamic_cast<chain *>(frag->getParent());
	 //outFile << "*" << setw(10) <<"*"<<setw(10);
	 //outFile <<ch->getName() << setw(12)<<frag->getName() << setw(10);
	 
	 //int test = 0; 
	 //cin >> test;
	 if (ch->getName() == " ") 
	    outFile << "*" << setw(10); 
	 else {
            QString cName = ch->getName();
            cName.replace(' ', "_");
            outFile << cName << setw(10);// << frag->getName() <<setw(10);
	 }   
	 outFile << frag->getName() << setw(10);
         if (frag->type == 0) outFile << "HELIX"<<endl;
         else if (frag->type == 1) outFile << "SHEET" << endl;
         else if (frag->type == 2) outFile << "TURN" << endl;
         
         frag->setName(tmp);
      }
      
      else outFile <<"*"<<setw(8) << "*" << setw(8) << "*" << endl;
      //for (int i=0; i<5; i++) outFile << setw(3) << "0";   
   }
   
   outFile  <<"%BONDS"<<endl;
   for (int i=0; i<mol->bonds.size(); i++) {
     bond *bd = mol->bonds[i];
     outFile << bd->fromAtom()->getNum() << setw(15) << bd->toAtom()->getNum();
     outFile << setw(15) << bd->order << endl;
   }
   
 
   
   map<QString, QString>::iterator propIt = mol->propMap.begin();
   for (propIt; propIt != mol->propMap.end(); propIt++) {
      QString name = propIt->first;
      QString value = propIt->second;
      QString type = mol->getPropType(name);
      outFile <<"$ "<<name<<"\t";
      if (type != "none") {
      	outFile << type <<"\t";
      } else {
      	outFile <<"*\t";
      }
      outFile << value << endl;
      outFile << endl;
   }   
   
   //Now reset the atom numbering
   for (int i=0; i<mol->atoms.size(); i++) {  
      mol->atoms[i]->setNum(originalAtomNums[i]);
   }
}

void molDB::typeFrag(fragment *frag) {
   string name = frag->getName();
   if (name == "ASP") {
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         if (atm->getAtomicNum() == 1) {
            if (atm->atoms[0]->getAtomicNum() == 8) {
               frag->setName("ASP_N");
               return;
            }
         }
      }
   }
   
   
   if (name == "GLU") {
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         if (atm->getAtomicNum() == 1) {
            if (atm->atoms[0]->getAtomicNum() == 8) {
               frag->setName("GLU_N");
               return;
            }
         }
      }
   }
   
   //Check for degenerate cases
   if (name == "ASN") {
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         if (atm->getSym() == "OD2") {
            frag->setName("ASP");
            typeFrag(frag);
         }
      }
   }
   
   if (name == "HIS" || name =="HIS_P" || name == "HIS_D" || name == "HIS_E") {
      bool delta = false;
      bool epsilon = false;
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         if (atm->getAtomicNum() ==1 && atm->atoms[0]->getSym() == "ND1") delta = true;
         if (atm->getAtomicNum() ==1 && atm->atoms[0]->getSym() == "NE2") epsilon = true;      
      }
      if (delta && epsilon) frag->setName("HIS_P");
      if (delta && !epsilon) frag->setName("HIS_D");
      if (!delta && epsilon) frag->setName("HIS_E");   
   }
}


void molDB::readSDToMolVec(QString fileName, vector<molecule *> &molVec) {
   ifstream inFile(fileName.latin1(), ios::in);
   if (!inFile) {
      return;
   }
   //determine how many molecules are int he SD file
   int molCount = 0;
   string tmpString;
   while (inFile >> tmpString) {
    if (tmpString == "$$$$") molCount++;
   }
   inFile.close();
   inFile.clear();
   inFile.open(fileName.latin1(), ios::in);
   if (molCount == 0) 
      molCount = 1;
   
   
   for (int i=0; i<molCount; i++) {
    bool hasSulfer = false;
    molecule *mol = new molecule();
    
    string Name, tmp, atmNumString, bdNumString;
    getline(inFile, Name);
    mol->setName(Name);
    
    getline(inFile, tmp);
    getline(inFile, tmp);
    getline(inFile, tmp);

    if (tmp.size() == 0) {
      QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"This error is likely due to an extra line in the SD header");
      delete mol;
      
      return;
    }
    
    atmNumString = tmp.substr(0,3);
    if (!checkFloatNum(atmNumString)) {
    	QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"Did not find an integer value for number of atoms");
	delete mol;
	return;
    }
    
    bdNumString =  tmp.substr(3,3);
    if (!checkIntNum(bdNumString)) {
    	QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"Did not find an integer value for number of bonds");
	delete mol;
	return;
    }
    
    int atmNum = atoi(atmNumString.c_str() );
    int bdNum = atoi(bdNumString.c_str() );

    
    for (int j=0; j<atmNum; j++) {
      float x, y, z;
      string sym;
      
      inFile >> x >> y >> z >> sym;
      if (!inFile) {
      	QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"Line read failed!");
	delete mol;
	return;
      }
     
      getline(inFile, tmp);    //There is other information that you can read from the sd 
      int atomicNum = SYM2AN(sym);
      mol->addAtom(j+1, sym, x, y, z, atomicNum);
    }
   
    for (int j=0; j<bdNum; j++) {
      int num, from, to, order;
      inFile >> from >> to >>order;
      getline(inFile, tmp);
      mol->addBond(j+1, from, to, order);
    }

    while (inFile >> tmp) {
      if (tmp == ">") {
        inFile >> tmp;
      	string name = tmp.substr(1,tmp.size()-2);
	getline(inFile, tmp);
	string data;
	getline(inFile, data);
	//inFile >> data;
        mol->addPropValuePair(name, data);
	//mol->propertyNames.push_back(name);
	//mol->propertyData.push_back(data);
      }
      if (tmp.substr(0,4) == "$$$$") {
         break;
	 delete mol;
      }
    }
   getline(inFile, tmp); //just to get that last little bit
   int input = 0;

   mol->updateValence();
   molVec.push_back(mol);
   static int counter = 0;
   counter++;
  } 
}

molecule *molDB::readSD(QString fileName, int offset, bool show) {
   ifstream inFile(fileName.latin1(), ios::in);
   
   if (!inFile) {
      return NULL;
   }
   
   inFile.seekg(offset);
   
   molecule *mol = new molecule;
   
   string Name, tmp, atmNumString, bdNumString;
   if (offset != 0)
      getline(inFile, tmp);
      
    getline(inFile, Name);
    mol->setName(Name);
    getline(inFile, tmp);
    getline(inFile, tmp);
    getline(inFile, tmp);

    if (tmp.size() == 0) {
      QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"This error is likely due to an extra line in the SD header");
      delete mol;
      
      return NULL;
    }
     
    atmNumString = tmp.substr(0,3);
    if (!checkFloatNum(atmNumString)) {
    	QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"Did not find an integer value for number of atoms");
	delete mol;
	return NULL;
    }
    
    bdNumString =  tmp.substr(3,3);
    if (!checkIntNum(bdNumString)) {
    	QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"Did not find an integer value for number of bonds");
	delete mol;
	return NULL;
    }
    
    int atmNum = atoi(atmNumString.c_str() );
    int bdNum = atoi(bdNumString.c_str() );

    
    for (int j=0; j<atmNum; j++) {
      float x, y, z;
      string sym;
      
      inFile >> x >> y >> z >> sym;
      if (!inFile) {
      	QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"Line read failed!");
	delete mol;
	return NULL;
      }
     
      getline(inFile, tmp);    //There is other information that you can read from the sd 
      int atomicNum = SYM2AN(sym);
      mol->addAtom(j+1, sym, x, y, z, atomicNum);
    }

    string line;
    for (int j=0; j<bdNum; j++) {
      int num, from, to, order;
      getline(inFile, line);
      QString qFrom = line.substr(0,3);
      QString qTo = line.substr(3,3);
      QString qOrder = line.substr(8,1);
      from =  qFrom.toInt();
      to = qTo.toInt();
      order = qOrder.toInt();

      mol->addBond(j+1, from, to, order);
    }
  
    while (inFile >> tmp) {
      if (tmp == ">") {
        inFile >> tmp;
      	string name = tmp.substr(1,tmp.size()-2);
	getline(inFile, tmp);
	string data;
	getline(inFile, data);
        mol->addPropValuePair(name, data);;
      }
      if (tmp.substr(0,4) == "$$$$") {
         break;
      }
    }
    
    if (show) {
      emit newMolecule(mol);
    }
    return mol;
}

//This is a static function
int molDB::scanSDFile(string fileName) {
return 0;
}

// This is a static funtion
molecule *molDB::getMolNum(int) {
return 0;
}











































