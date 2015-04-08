/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                     
 *    john.furr@dynamol.com
 ***************************************************************************/
#include "dtAmber_03.h"
#include "molecule.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
//#include <set>
#include "atom.h"
#include "dtGaff.h"

using namespace std;

namespace dt {
	
struct res {
   string name;
   vector<string> sym;
   vector<string> type;
   vector<float>   charge;
};

//AMBER_03::AMBER_03(molecule *mol)
AMBER_03::AMBER_03(molPtr mol)
{
   string PATH = "";
   #ifdef LINUX
      PATH = getenv("DYNAMOL");   
      PATH += "/ForceField/amber_03.in";
   #endif

   #ifdef WINDOWS
      PATH = "..\\ForceField\\amber_03.in";
   #endif

   vector<res *> RES;
   //set<res *> RES2;
   ifstream inFile(PATH.c_str(), ios::in);
   if (!inFile) { 
      ofstream outFile("bad1.txt", ios::out);
      outFile <<"File was not opened"<<endl;
	  outFile <<"That was the path area"<<endl;
	  outFile << PATH.c_str() << endl;
	  
      cout <<"File not opened  "<< PATH << endl;
      exit(0);
      return;
   }
   ////cout <<"HERE 1"<<endl;
   //Now lets read in all the residue information
   res *r = NULL;
   while ( !inFile.eof() ) {
      string tmp;
      getline(inFile, tmp);
      if (tmp[0] == '#') {
         if (r != NULL) {
            RES.push_back(r);
           //ES2.insert(r);
         }
         r = new res;
         r->name = tmp;
         //cout <<"r->name: "<< r->name << endl;
      } else {
          istringstream inStream(tmp);
          string sym, type;
          float charge;
          inStream >> sym >> type >> charge;
          //if (r->name == "#LEUCINE") {
          //   cout << sym << "\t"<<type <<"\t"<<charge<<endl;
          //}
          r->sym.push_back(sym);
          r->type.push_back(type);
          r->charge.push_back(charge);
      }
   }
   
   //vector<atom *> reTypes;
   vector<atomPtr> reTypes;
   for (int i=0; i<mol->atoms.size(); i++) {
      //atom *atm = mol->atoms[i];
      atomPtr atm = mol->atoms[i];
      string find = "#";
      if (atm->fragName[0] == 'n') find += "n-";
      if (atm->fragName[0] == 'c') find += "c-";
 
      //Temoporary fragName work around. 
      //Basically you needed to have the n or c prefix to determine if you 
      //had an n-terminal or c-terminal aminoa acide.  However you 
      //didn't want to rewrite the function so you provided a quick and
      // dirty little hack.  You reassign the name after all the if statements
      string tmpName = "";
      string nameHold = atm->fragName;
      if (atm->fragName[0] == 'n' || atm->fragName[0] == 'c') {
         for (int j=1; j<atm->fragName.size(); j++) 
            tmpName += atm->fragName[j];

         atm->fragName = tmpName;
      }      
      //cout <<"Looking for: " << atm->fragName <<"\t"<<atm->fragName.size() <<"\t"<<find<< endl; 
      if (atm->fragName == "ALA") find += "ALANINE";
      else if (atm->fragName == "GLY") find += "GLYCINE";
      else if (atm->fragName == "SER") find += "SERINE";
      else if (atm->fragName == "THR") find += "THREONINE";
      else if (atm->fragName == "LEU") {
         find += "LEUCINE";
         //cout <<"Using LEUCINE"<<endl;
      }
      else if (atm->fragName == "ILE") find += "ISOLEUCINE";
      else if (atm->fragName == "VAL") find += "VALINE";
      else if (atm->fragName == "ASN") find += "ASPARAGINE";
      else if (atm->fragName == "ASN_N") find += "ASP neutral";
      else if (atm->fragName == "GLN") find += "GLUTAMINE";
      else if (atm->fragName == "GLN_N") find += "GLUTAMINE neutral";
      else if (atm->fragName == "ARG") find += "ARGININE";
      else if (atm->fragName == "HIS_D") find += "HISTIDINE DELTAH";
      else if (atm->fragName == "HIS_E") find += "HISTIDINE EPSILONH";
      else if (atm->fragName == "HIS_P") find += "HISTIDINE PLUS";
      else if (atm->fragName == "TRP") find += "TRYPTOPHAN";
      else if (atm->fragName == "PHE") find += "PHENYLALANINE";
      else if (atm->fragName == "TYR") find += "TYROSINE";
      else if (atm->fragName == "GLU") find += "GLUTAMIC ACID";
      else if (atm->fragName == "ASP") find += "ASPARTIC ACID";
      else if (atm->fragName == "LYS") find += "LYSINE";
      else if (atm->fragName == "PRO") find += "PROLINE";
      else if (atm->fragName == "CYS") find += "CYSTEINE";
      else if (atm->fragName == "MET") find += "METHIONINE";
      else if (atm->fragName == "GLY") find += "GLYCINE";
      else if (atm->fragName == "water") find = "WATER, TIP3P MODEL";
      else find = "OTHER";
     
      if (atm->getAN() == 1) {
         atm->setSymbol("h");
         typeH(atm);
      }
      if (find == "OTHER") {
	 type(atm);
      }
      else {
         for (int j=0; j<RES.size(); j++) {
            if (RES[j]->name == find) {
               bool found = false;
               for (int k=0; k<RES[j]->sym.size(); k++) {
                  //cout << RES[j]->name<<"\t"<<RES[j]->sym[k]<<endl;
                  //if (atm->getSymbol() == "HD21") {
                  //   cout <<atm->fragName<<"\t"<< atm->fragName.size()<<"\t"<<RES[j]->sym[k]<<endl;
                  //}
                  //if (find == "LEUCINE") {
                  //   cout <<"LEU "<< RES[j]->sym[k] << endl;
                  //} 
                  if (atm->getSymbol() == RES[j]->sym[k]) {
                     atm->type = RES[j]->type[k];
                     atm->charge = RES[j]->charge[k];
                     found = true;
                     break; 
                  }
               }      
               if (found) break;
            }
         }
      }
      
      if (atm->getSymbol() == "OXT") 
         atm->type = "O2";
      
      if (atm->type == "none") {
         reTypes.push_back(atm);
      }
 
   }
   for (int i=0; i<reTypes.size(); i++) {
      //atom *atm = reTypes[i];
      atomPtr atm = reTypes[i];
      //cout <<"Retyping: "<<atm->getSymbol() << setw(6)<< atm->getAN();
      //cout <<setw(6) << atm->fragName<< endl;
      type(reTypes[i]);
      //cout <<"New Type: "<<atm->getSymbol() << setw(6)<< atm->getAN();
      //cout <<setw(6) << atm->fragName<< endl;
   }
   
    mol->ffType = "AMBER_03";
}


AMBER_03::~AMBER_03()
{
}

//void AMBER_03::typeH(atom *atm) {
void AMBER_03::typeH(atomPtr atm) {
  
   //cout <<"atm->fragName: " << atm->fragName << setw(12)<<atm->atoms.size() << endl;
   //cout <<"atm->num: " << atm->num << setw(12) << atm->sym << endl;
   //atom *atm2 = atm->atoms[0];
   atomPtr atm2 = atm->atoms[0].lock();
   
   if (atm->fragName == "water") {
      if (atm2->getSymbol() == "O") {atm->setSymbol("H1"); return;}
   }
   
   if (atm->fragName == "ALA") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB1"); return;}
   }
   if (atm->fragName == "GLY") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA2"); return;}
   }
   if (atm->fragName == "SER") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "OG") {atm->setSymbol("HG"); return;}
   }
   if (atm->fragName == "THR") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB"); return;}
      if (atm2->getSymbol() == "CG2") {atm->setSymbol("HG21"); return;}
      if (atm2->getSymbol() == "OG1") {atm->setSymbol("HG1"); return;}
   }
   if (atm->fragName == "LEU") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG"); return;}
      if (atm2->getSymbol() == "CD1") {atm->setSymbol("HD11"); return;}
      if (atm2->getSymbol() == "CD2") {atm->setSymbol("HD21"); return;}
   }
   if (atm->fragName == "cLEU" || atm->fragName == "nLEU") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG"); return;}
      if (atm2->getSymbol() == "CD1") {atm->setSymbol("HD1"); return;}
      if (atm2->getSymbol() == "CD2") {atm->setSymbol("HD1"); return;}
   }

   if (atm->fragName == "ILE") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG"); return;}
      if (atm2->getSymbol() == "CG2") {atm->setSymbol("HG21"); return;}
      if (atm2->getSymbol() == "CG1") {atm->setSymbol("HG12"); return;}
      if (atm2->getSymbol() == "CD1") {atm->setSymbol("HD11"); return;}
   }   
   if (atm->fragName == "VAL") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB"); return;}
      if (atm2->getSymbol() == "CG1") {atm->setSymbol("HG11"); return;}
      if (atm2->getSymbol() == "CG2") {atm->setSymbol("HG21"); return;}
   }
   if (atm->fragName == "ASN") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "ND2") {atm->setSymbol("HD21"); return;}
   }
   if (atm->fragName == "GLN") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG2"); return;}
      if (atm2->getSymbol() == "NE2") {atm->setSymbol("HE21"); return;}
   }
   if (atm->fragName == "ARG") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG2"); return;}
      if (atm2->getSymbol() == "CD") {atm->setSymbol("HD2"); return;}
      if (atm2->getSymbol() == "NE") {atm->setSymbol("HE"); return;}
      if (atm2->getSymbol() == "NH1") {atm->setSymbol("HH11"); return;}
      if (atm2->getSymbol() == "NH2") {atm->setSymbol("HH21"); return;}
   }
   if (atm->fragName == "HIS_D") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "ND1") {atm->setSymbol("HD1"); return;}
      if (atm2->getSymbol() == "CE1") {atm->setSymbol("HE1"); return;}
      if (atm2->getSymbol() == "CD2") {atm->setSymbol("HD2"); return;}
   }
   if (atm->fragName == "HIS_E") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CE1") {atm->setSymbol("HE1"); return;}
      if (atm2->getSymbol() == "NE2") {atm->setSymbol("HE2"); return;}
      if (atm2->getSymbol() == "CD2") {atm->setSymbol("HD2"); return;}
   }
   if (atm->fragName == "HIS_P") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "ND1") {atm->setSymbol("HD1"); return;}
      if (atm2->getSymbol() == "CE1") {atm->setSymbol("HE1"); return;}
      if (atm2->getSymbol() == "NE2") {atm->setSymbol("HE2"); return;}
      if (atm2->getSymbol() == "CD2") {atm->setSymbol("HD2"); return;}
   }
   if (atm->fragName == "TRP") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CD1") {atm->setSymbol("HD1"); return;}
      if (atm2->getSymbol() == "NE1") {atm->setSymbol("HE1"); return;}
      if (atm2->getSymbol() == "CZ2") {atm->setSymbol("HZ2"); return;}
      if (atm2->getSymbol() == "CH2") {atm->setSymbol("HH2"); return;}
      if (atm2->getSymbol() == "CZ3") {atm->setSymbol("HZ3"); return;}
      if (atm2->getSymbol() == "CE3") {atm->setSymbol("HE3"); return;}
   }
   if (atm->fragName == "PHE") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CD1") {atm->setSymbol("HD1"); return;}
      if (atm2->getSymbol() == "CE1") {atm->setSymbol("HE1"); return;}
      if (atm2->getSymbol() == "CZ") {atm->setSymbol("HZ"); return;}
      if (atm2->getSymbol() == "CE2") {atm->setSymbol("HE2"); return;}
      if (atm2->getSymbol() == "CD2") {atm->setSymbol("HD2"); return;}
   }
   if (atm->fragName == "TYR") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CD1") {atm->setSymbol("HD1"); return;}
      if (atm2->getSymbol() == "CE1") {atm->setSymbol("HE1"); return;}
      if (atm2->getSymbol() == "OH") {atm->setSymbol("HH"); return;}
      if (atm2->getSymbol() == "CE2") {atm->setSymbol("HE2"); return;}
      if (atm2->getSymbol() == "CD2") {atm->setSymbol("HD2"); return;}
   }
   if (atm->fragName == "GLU") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG2"); return;}
   }
   if (atm->fragName == "GLU_N") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG2"); return;}
      if (atm2->getSymbol() == "OE2") {atm->setSymbol("HE2"); return;}
      if (atm2->getSymbol() == "OE1") {atm->setSymbol("HE2"); return;}
   }
   if (atm->fragName == "ASP") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "OD2") {atm->setSymbol("HD2"); return;}
   }
   if (atm->fragName == "ASP_N") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG2"); return;}
   }
   if (atm->fragName == "LYS") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG2"); return;}
      if (atm2->getSymbol() == "CD") {atm->setSymbol("HD2"); return;}
      if (atm2->getSymbol() == "CE") {atm->setSymbol("HE2"); return;}
      if (atm2->getSymbol() == "NZ") {atm->setSymbol("HZ1"); return;}
   }
   if (atm->fragName == "LYS_N") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG2"); return;}
      if (atm2->getSymbol() == "CD") {atm->setSymbol("HD2"); return;}
      if (atm2->getSymbol() == "CE") {atm->setSymbol("HE2"); return;}
      if (atm2->getSymbol() == "NZ") {atm->setSymbol("HZ2"); return;}
   }
   if (atm->fragName == "PRO") {
      //cout <<"Typeing Proline"<<endl; 
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CD") {atm->setSymbol("HD2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG2"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      ////cout <<"atm->sym2: " << atm2->sym << setw(12) << atm2->sym.size() << endl;
      ////cout <<"Made it here"<<endl;
   }
   if (atm->fragName == "CYS") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "SG") {atm->setSymbol("HG"); return;}
   }
   if (atm->fragName == "CYS_neg") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("HN"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
   }
   if (atm->fragName == "CYS_bridge") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
   }
   if (atm->fragName == "MET") {
      if (atm2->getSymbol() == "N") {atm->setSymbol("H"); return;}
      if (atm2->getSymbol() == "CA") {atm->setSymbol("HA"); return;}
      if (atm2->getSymbol() == "CB") {atm->setSymbol("HB2"); return;}
      if (atm2->getSymbol() == "CG") {atm->setSymbol("HG2"); return;}
      if (atm2->getSymbol() == "CE") {atm->setSymbol("HE1"); return;}
   }
}

//void AMBER_03::type(atom *atm) {
void AMBER_03::type(atomPtr atm) {
   
   dtGaff G;
   if (atm->getAN() == 6) {
      G.typeCarbon(atm);
      if (atm->type == "c") atm->type = "C";
      if (atm->type == "c3") atm->type = "CT";
      if (atm->type == "ca") atm->type =  "CA";
      if (atm->type == "c1") atm->type = "CZ";
      if (atm->type == "c2") atm->type = "CA";
      if (atm->type == "cc") atm->type = "CA";
      if (atm->type == "cd") atm->type = "CA";
      if (atm->type == "cv") atm->type = "CA";
      if (atm->type == "cp") atm->type = "CA";
      if (atm->type == "cq") atm->type = "CA";
      if (atm->type == "ce") atm->type = "CA";
      if (atm->type == "cf") atm->type = "CA";
   }
   if (atm->getAN() == 8) {
      G.typeOxygen(atm);
      if (atm->type == "o") atm->type = "O";
      if (atm->type == "oh") atm->type = "OH";
      if (atm->type == "os") atm->type = "OS";
   }
   
   if (atm->getAN() == 7) {
      G.typeNitrogen(atm);
      if (atm->type == "n") atm->type = "N";
      if (atm->type == "n2") atm->type = "N2*";
      if (atm->type == "ne") atm->type = "N2*";
      if (atm->type == "nf") atm->type = "N2*";
      if (atm->type == "nc") atm->type = "N2*";
      if (atm->type == "nd") atm->type = "N2*";
      if (atm->type == "n3") atm->type = "NT";
      if (atm->type == "n4") atm->type = "N3";
      if (atm->type == "nh") atm->type = "N2";
   }
   
   if (atm->getAN() == 1) {
      G.typeHydrogen(atm);
      if (atm->type == "hn") atm->type = "H";
      else if (atm->type == "h1") atm->type = "H1";
      else if (atm->type == "h2") atm->type = "H2";
      else if (atm->type == "h3") atm->type = "H3";
      else if (atm->type == "hc") atm->type = "HC";
      else if (atm->type == "h4") atm->type = "H4";
      else if (atm->type == "h5") atm->type = "H5";
      else if (atm->type == "hw") atm->type = "HW";
      else if (atm->type == "ho") atm->type = "HO";
      else if (atm->type == "hs") atm->type = "HS";
      else if (atm->type == "hp") atm->type = "HP";
      else if (atm->type == "hx") atm->type = "HC";
      else if (atm->type == "ha") atm->type = "HA";
      //STILL NEED HZ hydrogen bound ot sp Carbon...no dtGaff equiv???
     // ////cout <<"New h atom type: " <<atm->type << endl;

   }
   
   if (atm->getAN() == 15) {
      atm->type = "P";
   }
   if (atm->getAN() == 16) {
      G.typeSulfer(atm);
      if (atm->type == "sh") atm->type = "SH";
      else atm->type = "S";
   }
   
   if (atm->getAN() == 30)
      atm->type = "Zn";
   if (atm->getAN() == 11)
      atm->type = "Na";
   if (atm->getAN() == 19)
      atm->type = "K";
   if (atm->getAN() == 55)
      atm->type = "Cs";
   if (atm->getAN() == 37)
      atm->type = "Rb";
   if (atm->getAN() == 26)
      atm->type = "Fe";
   if (atm->getAN() == 3)
      atm->type = "Li";

}

};//end namespace



