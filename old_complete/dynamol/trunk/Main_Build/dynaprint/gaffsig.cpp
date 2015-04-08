/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                         
 *
 *   This software is provided as is with no implied waranty                                                        *
 ***************************************************************************/
#include "gaffsig.h"

#include "../dynatype/dtUtility.h"
using dt::setNum;

//Dynatype Includes

#include "../dynatype/dtGaff.h"
#include "../dynatype/molecule.h"
#include "../dynatype/atom.h"
#include "../dynatype/dtReader.h"
#include "../dynatype/dtype.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <qmessagebox.h>
#include <qprogressdialog.h>
#include <qapplication.h>
#include <qeventloop.h>
#include <algorithm>

using namespace std;

namespace fp {

gaffSig::gaffSig()
{
    basicMapSetup();
   //UNDO HERE
   //createMap();
   
   string a = setNum(10);
}

void gaffSig::processFile(string sdFile, string fpFile, int height) {
	ifstream inFile(sdFile.c_str(), ios::in | ios::binary);
	if (!inFile) {
		QString error = sdFile.c_str();
		error += " was not opened";
		cout <<"SD File not opened"  << endl;
		QMessageBox::information( 0, "Application name", error );
		return;
	}
	long int l, m;
	l = inFile.tellg();
	inFile.seekg (0, ios::end);
	m = inFile.tellg();
	inFile.seekg(0, ios::beg);

	long int size = m-l;
	long int estRecordNum = size/4854;

	//QProgressDialog progress( "Scanning SDFile", "Abort Scan", estRecordNum,
	//                       0, "progress", TRUE );
	//QEventLoop *el = QApplication::eventLoop();  
	//progress.setMinimumDuration(0); 
	//progress.setProgress( 0 );
	int c = 1;
	int offSet = inFile.tellg();
   
	map<int, long int> offSetMap;
	string name;
	string qName;
	vector<string> nameVec;
	getline(inFile, name);
	qName = name;
	if (qName == "") {
		qName = setNum(c);
	}
	nameVec.push_back(qName);
	offSetMap[c] = 0;

	while (inFile >> name) {
		if (c % 2000 == 0) {
			//progress.setProgress( c );
			//el->processEvents(QEventLoop::ExcludeUserInput);
			//if ( progress.wasCanceled() )
			//    return;
		}
		if (c == 1 || (name.substr(0,4) == "$$$$" && !inFile.eof())) {
			//if (c == 1 || (name == "$$$$" && !inFile.eof())) {
			string qName;
			if (c != 1) {
				//offSet = inFile.tellg();
				//offSet++;
				getline(inFile, name);
				offSet = inFile.tellg();
				//offSet--;
				//cout <<"Name 1: " << name << endl;
				getline(inFile, name);
				//////cout <<"name 2: " << name << endl;
				//inFile >> name;
				if (inFile.eof()) 
					break;
				qName = name;
				
				if (qName.length() == 0) {
					qName = setNum(nameVec.size()+1);
				}
				nameVec.push_back(qName);
				offSetMap[c] = offSet;
        
				// Display the name of the compound that is being exported  
	 
				//move down to atm and bond num
				getline(inFile, name);
				getline(inFile, name);
				getline(inFile, name);
				getline(inFile, name);
	 
				//determine numOfAtms and num of Bonds
				string atmNumString = name.substr(0,3);
				string bdNumString =  name.substr(3,3);
				//int atmNum = atoi(atmNumString.c_str() );
				//int bdNum = atoi(bdNumString.c_str() );
	 
				//seek to end of atom section
				getline(inFile, name);

				//int size = name.size();
				//inFile.seekg(size*(atmNum-1), ios::cur);
				//inFile.seekg(bdNum*18, ios::cur);
	 
				//map<string, string> propValMap;
			}
	 
			while (true) {
				getline(inFile, name);
				if (name.substr(0,4) == "$$$$") {
					inFile.seekg(-25, ios::cur);
					break;
				}
	    
	   
				if (inFile.eof()) {
					////cout <<"Break from here"<<endl;
					break;
					//return;
				}
			} 
     
			c++;
		}
	}
	//progress.setProgress(estRecordNum); 
	//Now start processing the indivudial molecules
	//QProgressDialog progress2( "Calculating Fingerprints (gaffFP)", "Abort Calculation", c,
	//                          0, "progress", true );
	//progress2.setMinimumDuration(0);
	//progress2.setProgress( 0 );
	ofstream outFile(fpFile.c_str(), ios::out);
	map<int, long int>::iterator mi = offSetMap.begin();
	int count = 0;

	dt::dtReader r;
	dt::dType d;
	d.setPathLength(10);

	ofstream  outFile2("bad_fp.txt", ios::out);
	outFile <<"Name \t FingerPrint"<<endl; 
	vector<string> badMolecules;
	for(unsigned int i=0; i<nameVec.size(); i++) {
		long int index = offSetMap[i+1];
		count++;
		//dt::molecule *mol = new dt::molecule;
		dt::molPtr mol( new dt::molecule );
		r.readSDF(sdFile.c_str(), mol, index);
		string tmpName = "";
     
		for (unsigned int j=0; j<mol->name.size(); j++) {
			if (mol->name[j] != ' ' ) {
				tmpName += mol->name[j];
			} else {
				tmpName += "_";
			}
		}
		
		mol->name = tmpName;

		//********* Asign the general amber forcefield atom types
		d.setGaffTypes(mol);

		//********** Start of Fingerprint routine 
		string fp = runMol(mol, 3, true);

		if (fp == "none") {
			badMolecules.push_back(nameVec[i]);
			outFile2 << mol->name << endl;
		} else {
			outFile << mol->name <<"\t" << fp << endl;
		}
		//delete mol;
		count++;
		if (count % 500 == 0) {
			////cout << count << endl;
			//progress2.setProgress( count );
			//el->processEvents(QEventLoop::ExcludeUserInput);
			//if (progress2.wasCanceled())
			//return;
		}
		//el->processEvents(QEventLoop::ExcludeUserInput);
		//if ( progress2.wasCanceled() )
		//  return;
	}

	if (badMolecules.size() != 0) {
		//string qNum; qNum.setNum(badMolecules.size());
		string qNum = setNum(badMolecules.size());
		string error = "There were " + qNum + " structures that Dynamol could\n";
		error += "not calculate fingerprints for.  The structure names are\n";
		error += "saved in  bad_fp.txt";
		QString qError = error.c_str();
		QMessageBox::warning(0, "Bad Molecules", qError);
	}
}

//string gaffSig::runMol(dt::molecule *mol, int height,  bool single) {
string gaffSig::runMol(dt::molPtr mol, int height,  bool single) {
	if (bitMap2.size() == 0 || bitMap3.size() == 0) {
		cout <<"Must call readSubSets(int heigt) first"<<endl;
		return "noFP";
	}
	this->mol = mol;
	countMapSetup();
	fp.resize(mol->atoms.size());
	for (unsigned int i=0; i<mol->atoms.size(); i++) {
		fp[i].resize( countMap.size() );
		for (unsigned int j=0; j<countMap.size(); j++) {
			fp[i][j] = 0;
		}
	}
	return buildFingerPrint(height, single);
}

gaffSig::~gaffSig()
{
}
void gaffSig::countMapSetup() {
	countMap.clear();
	//countMap["c"] = 0;  //sp2 carbon in C=O, C=S
	countMap["c1"] = 0;  
	countMap["c2"] = 0;
	countMap["c3"] = 0;
	countMap["ca"] = 0;
	
	countMap["n"] = 0;   // sp2 nitrogen in Amides
	countMap["n1"] = 0;  // sp1 nitrogen
	countMap["n2"] = 0;  // sp2 nitroge with 2 subs
	countMap["n3"] = 0;  // sp3 nitrogen with 3 subs
	//countMap["n4"] = 0;  // sp3 nitrogen with 4 subs
	//countMap["na"] = 0;  // sp2 nitrogen with 3 subs
	countMap["nh"] = 0;  // amine nitrogen
	countMap["no"] = 0;  // nitro nitrogen
	countMap["nb"] = 0;  // aromatic nitrogen

	countMap["o"]  = 0;  // sp2 oxygen C=O, COO-
	countMap["oh"] = 0;  // sp3 oxygen in hydroxyl group
	countMap["os"] = 0;  // sp3 oxygen in ethers and esters
	
	countMap["s2"] = 0;  // sp2 sulfer (P=S, C=S etc)
	countMap["sh"] = 0;  // sp3 sulfer in thiol groups
	countMap["s4"] = 0;  // hypervalent sulfer 3 subs
	countMap["s6"] = 0;  // hypervalent sulfer 4 subs
	countMap["ss"] = 0;

	countMap["p2"] = 0;  // sp2 phosphorus C=P
	countMap["p3"] = 0;  // sp3 phosphorus, 3subs
	countMap["p4"] = 0;  // hypervalent phosphorus 3 subs
	countMap["p5"] = 0;  // hypervalent phosphorus 4 subs

	countMap["f"]  = 0;  // flourine
	countMap["cl"] = 0;  // chlorine
	countMap["br"] = 0;  // bromine
	countMap["i"]  = 0;  // iodine

	//Not sure about leaving these in there
	countMap["B"] =0;
	countMap["Si"] = 0;
	countMap["Au"] = 0;
}

void gaffSig::basicMapSetup() {
   dt::dtGaff::getBasicTypeMap(basicMap);
}

bool  gaffSig::checkFFTypes() {
	for (unsigned int i=0; i<mol->atoms.size(); i++) {
		if (mol->atoms[i]->getAN() != 1) {
			string type = mol->atoms[i]->type;
			if ( basicMap.find(type) == basicMap.end()) {
				cout <<"Bad Type!!!!  " << type << endl;
				mol->propMap["gaffFP"] = type;
				return false;
			}
		}
	}
	return true;
}

string gaffSig::buildFingerPrint(int h, bool single) {
    maxDepth  = h;
    if ( !checkFFTypes() ) {
        cout <<"ChecFFTypes failed"<<endl;
	return "none";
    }
    string gaffFP;
    set<int> fpSet;
    vector<int> fpVec;
    ofstream outFile("fp.log", ios::out | ios::app);
    string oldFP = "";
	for (unsigned int i=0; i<mol->atoms.size(); i++) {
		start = mol->atoms[i];
		int atmNum = mol->atoms[i]->getNum();
		string strNum;
		stringstream ss;
		ss << atmNum;
		ss >> strNum;
		if (start->getAN() != 1) {
			countMapSetup();
			atomStack.push_front(start);
			atomSet.clear();
			atomSet.insert(start);
			
			//************** RECURSIVE PART??
			//RECENTLY ADDED THIS....had to initialize.  some types were WRONG!!!!!!!!!!!
			// You should probalby recalculate all the statistics and such
			dt::atomPtr tmp;
			prev = tmp;
			//cout <<"prev: " << prev << endl;
			next(start);
			
			string fingerPrintName = "";
			//vector<dt::atom *> atomNum(atomSet.begin(), atomSet.end());  
			vector<dt::atomPtr> atomNum(atomSet.begin(), atomSet.end());
			
			//Log Stuff
			stringstream sLine;
			//cout << atmNum <<"\t";
			for (unsigned int j = 0; j<atomNum.size(); j++) {
				//cout << atomNum[j]->getNum() <<" ";
				string type = basicMap[atomNum[j]->type];
				fingerPrintName+=type;
				countMap[type]++;
			}
			//cout << endl;

			//This section constructs the atom environment fingerprint
			string fingerPrint = "";
			map<string, int>::iterator cmi = countMap.begin();
			unsigned int count = 0;
			while (cmi != countMap.end()) {
				fp[i][count] = cmi->second;

				string num; 
				num = setNum(cmi->second);
				if (count != countMap.size()-1)
					fingerPrint += num +",";
				else
					fingerPrint += num;
		
				count++;
				cmi++;
			}

			//REDO THIS
			// THIS SECTION IS PRINTED TO FP.LOG
			// IT NOW TRACKS ATOM NUMBERS AS WELL AS BINNED FINGERPRINTS
			oldFP += strNum+"--"+fingerPrint + ":";

			// UNDO THIS (3)
			int fpNum = -1;
			if (h == 3 && bitMap3.find(fingerPrint) != bitMap3.end()) {
				fpNum = bitMap3[fingerPrint];
			}

			if (h == 2 && bitMap2.find(fingerPrint) != bitMap2.end()) {
				fpNum = bitMap2[fingerPrint];
			}
			if (single && fpNum != -1) {
				fpSet.insert(fpNum);
			} else if (fpNum != -1)  {
				fpVec.push_back(fpNum);
			}
		}
	}
	outFile << mol->name <<"\t " << oldFP << endl;

	if (!single) {
		for (unsigned int i=0; i<fpVec.size(); i++) {
			//string num; num.setNum(fpVec[i]);
			string num = setNum(fpVec[i]);  
			gaffFP += num + " ";
		}
	} else {
		set<int>::iterator it;// = fpSet.begin();
		for (it=fpSet.begin(); it != fpSet.end(); it++) {
			//string num; num.setNum(*it);
			string num = setNum(*it);
			gaffFP += num + " ";
		}
	}
	return gaffFP;
}

void gaffSig::next( dt::atomPtr atm ) {
	if (atomStack.size() == maxDepth) {
		dt::atomPtr tmp = atomStack.front();
		atomStack.pop_front();
		return;
	}

	for (unsigned int i=0; i<atm->atoms.size(); i++) {
		dt::atomPtr tmp = atm->atoms[i].lock();
		if (tmp->getAN() != 1 && tmp != start && tmp != prev) {
			prev = atm;

			atomStack.push_front(tmp);  
	
			atomSet.insert(tmp);
			next(tmp); 
		}
	}
	atomStack.pop_front();
}

void gaffSig::readSubSets(int size) {
   bitMap2.clear();
   bitMap3.clear();

   //string PATH = getenv("DYNAMOL");
   //#PATH += "/FingerPrint/gaffsig3.txt";
   string PATH = "";
   #ifdef LINUX
      PATH = getenv("DYNAMOL");
      PATH += "/FingerPrint/gaffsig3.txt";
      //cout <<"LINUX ifdef"<<endl;
   #endif
   
   #ifdef WINDOWS
      PATH = "../FingerPrint/gaffsig3.txt";
      //cout <<"Windows ifdef"<<endl;
   #endif

   ifstream inFile(PATH.c_str(), ios::in);
   if (!inFile) {
      cout <<PATH <<" was not found"<<endl;
      throw -1;
      return;
   }
   int count = 0;
   string line;
   getline(inFile, line); //read in the header
   float prob, se;
   while (inFile >> line >> prob >> se) {
      bitMap3[line] = count;
      //probMap[count] = prob;
      //seMap[count] = se;
      count++;
      if (count == size)
         break;
   }

   inFile.close();
   inFile.clear();

  
   #ifdef LINUX
      PATH = getenv("DYNAMOL");
      PATH += "/FingerPrint/gaffsig2.txt";
   #endif
   
   #ifdef WINDOWS 
      PATH = "../FingerPrint/gaffsig2.txt";
   #endif

   inFile.open(PATH.c_str(), ios::in);
   if (!inFile) {
      throw -2;
      return;
   }
   count = 0;
   //string line;
   getline(inFile, line); //read in the header
   //prob, se;
   while (inFile >> line >> prob >> se) {
      bitMap2[line] = count;
      //probMap[count] = prob;
      //seMap[count] = se;
      count++;
      if (count == size)
         break;
   }

   inFile.close();
   inFile.clear();

}

void gaffSig::createMap() {
   string PATH = "";
   #ifdef LINUX 
      PATH = getenv("DYNAMOL");
      PATH += "/FingerPrint/gaffsig3.txt";
   #endif
  
   #ifdef WINDOWS 
      PATH = "../FingerPrint/gaffsig2.txt";
   #endif
   ifstream inFile(PATH.c_str(), ios::in);
   if (!inFile) {
      //QMessageBox::critical(0, "e", "        damn ass");
      throw -1;
      return;
   }
   int count = 0;
   string line;
   getline(inFile, line); //read in the header
   float prob, se;
   while (inFile >> line >> prob >> se) {
      bitMap3[line] = count;
      //probMap[count] = prob;
      //seMap[count] = se;
      count++;
   }
   
   inFile.close();
   inFile.clear();
}

}//END namespace fp




