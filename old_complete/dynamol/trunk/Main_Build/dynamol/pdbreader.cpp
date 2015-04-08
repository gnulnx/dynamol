/***************************************************************************
                          pdbreader.cpp  -  description
                             -------------------
    begin                : Fri May 2 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "pdbreader.h"
#include <qstring.h>

#include "pdbreadfrag.h"
#include "pdbreadchain.h"
#include "fragfactory.h"

#include "protein.h"
#include "chain.h"
#include "fragment.h"

pdbReader::pdbReader() {};


void pdbReader::readPDB(string fileName, list<protein *> &protList) {
  ////qDebug("You are in pdbReader");
  ifstream inFile;
  inFile.open(fileName.c_str(), ios::in);
  if (!inFile) {
    return;
  }

  //This gets the first line of the File the HEADER
  string headerLine, pdbName;
  getline(inFile, headerLine);
  QString header = headerLine;
  if (header.contains("HEADER") ) {
     pdbName =  headerLine.substr(62, 4);
  } else {
     pdbName = fileName;
  }
  /* This first section will read in the data for the assignment of helices, sheets, && strands
  */
  vector< vector<int> >  helices, sheets, turns;
  vector< string >  helixChain, sheetChain, turnChain;
  vector< int > currentHelix, currentSheet, currentTurn;
  int startNum, endNum;
  string line, start, end, chainStr;
  int startCount = 0;
  while (true) {
    getline(inFile, line);
    if (line.substr(0,6) == "HELIX ") {
        startCount++;
        chainStr = line.substr(19,1);
        helixChain.push_back(chainStr);
        start = line.substr(21, 5);
        end = line.substr(33, 5);
        startNum = atoi(start.c_str());
        endNum   = atoi(end.c_str());
        currentHelix.clear();
        for (int i=startNum; i<=endNum; i++) {
          currentHelix.push_back(i);
        }
        helices.push_back(currentHelix);
    } else if (line.substr(0,6) == "SHEET ") {
        startCount++;
        chainStr = line.substr(21,1);
        
        sheetChain.push_back(chainStr);
        start = line.substr(22, 5);
        end = line.substr(33, 5);
        startNum = atoi(start.c_str());
        endNum   = atoi(end.c_str());
        currentSheet.clear();
        for (int i=startNum; i<=endNum; i++) {
          currentSheet.push_back(i);
        }
        sheets.push_back(currentSheet);
    } else if (line.substr(0,6) == "TURN  ") {
        startCount++;
        chainStr = line.substr(19,1);
        turnChain.push_back(chainStr);
        start = line.substr(22, 26);
        end = line.substr(33, 37);
        startNum = atoi(start.c_str());
        endNum   = atoi(end.c_str());
        currentTurn.clear();
        for (int i=startNum; i<=endNum; i++) {
          currentTurn.push_back(i);
        }
        turns.push_back(currentTurn);
    } else if (line.substr(0,5) == "SCALE" 
              || (startCount > 0 && line.substr(0,6) != "HELIX " 
              && line.substr(0,6) != "SHEET " 
              && line.substr(0,6) != "TURN  ")) {
      break;
    } 
    //int test = 0;
    //cin >> test;
    //if (line.substr(0,6) == "ATOM  ") break;
    if ( inFile.eof() ) break;
  }
  if (inFile.eof()) {
     inFile.close();
     inFile.clear();
     inFile.open(fileName.c_str(), ios::in);
     if (!inFile) {
	return; 
     }
  }
  int tester = 0;
  //list<protein *> *protList = new list<protein *>;
  protein *prot = new protein; //initialize to actual protein as it might be used
  prot->setName(pdbName);
  chain *ch = NULL;   //initialize to NULL.
  ////qDebug("Starting main pdbreader read loop");
  while (true) {
      getline(inFile, line);
      if (line.substr(0,6) == "MODEL ") {
          prot = readProtein(inFile, line);
          prot->setName(pdbName);
          if (prot != NULL) 
              protList.push_back(prot);
      } else if (line.substr(0,6) == "ATOM  " || line.substr(0,6) == "HETATM") {
	////qDebug("Reading chain");
	ch = readChain(inFile, line);
	////qDebug("Done reading chain");
        if (ch != NULL) { 
          prot->addChain(ch); 
        }
      }
      if (line.substr(0,6) == "END   ") {
        if (protList.size() == 0) { 
          protList.push_back(prot);
        }
        break;
        
      }  
      if (line.size() == 3 && line.substr(0,3) == "END") {
        if (protList.size() == 0) { 
          protList.push_back(prot);
        }
        break;
      }     
  }
  ////qDebug("Well you did get this far");
  for (int i=0; i<prot->chains.size(); i++) {
    chain *tmpChain = prot->chains[i];
    for (int j=0; j<tmpChain->frags.size(); j++) {
      fragment *frag = tmpChain->frags[j];
      //This part is for the helices
      for (int k=0; k<helixChain.size(); k++) {
        if (helixChain[k] == tmpChain->getName()) {
          for (int l=0; l<helices[k].size(); l++) {
            if (helices[k][l] == frag->getNum()) {
              frag->type = HELIX;
            }
          }
        }
      }

      //This part is for the sheets
      for (int k=0; k<sheetChain.size(); k++) {
        if (sheetChain[k] == tmpChain->getName()) {
          for (int l=0; l<sheets[k].size(); l++) {
            if (sheets[k][l] == frag->getNum()) {
              frag->type = SHEET;
            }
          }
        }
      }

      //This part is for the turns
      
    }
  }

  int test =0;
  for (int i=0; i<prot->chains.size(); i++) {
    for (int j=prot->chains[i]->frags.size()-1; j>=0; j--) {
      fragment *frag = prot->chains[i]->frags[j];
    }
    //cin >> test;
  }
  //exit(0);
  inFile.close();
}

protein     *pdbReader::readProtein(ifstream &inFile, string &line) {
  protein *prot = new protein;
  chain *ch = NULL;
  while (true) {
      if (line.substr(0,6) == "ATOM  " || line.substr(0,6) == "HETATM") {
          ch = readChain(inFile, line);
          if (ch != NULL) { 
            prot->addChain(ch);
          }
      }
      if(line.substr(0,6) == "ENDMDL" || line.substr(0,6) == "END   ") {
          return prot;
      }
      getline(inFile, line);
  }
}

chain       *pdbReader::readChain(ifstream &inFile, string &line)  {
    string chainName = line.substr(21,1);
    if (chainName == " ") chainName = "John Doe";
    chain *ch = new chain();
    ch->setName(chainName);

    fragment *frag = NULL;

    while (true) {
      if (line.size() > 6 && (line.substr(0,6) == "ATOM  " || line.substr(0,6) == "HETATM")) {
          string resNum = line.substr(23,4);
	  frag = readFrag(inFile, line);
          if (frag != NULL) {
             frag->setNum(atoi(resNum.c_str()));
             ch->addFrag(frag);
          } else {
          }
      }
      if (line.substr(0,6) == "TER   " || line.substr(0,6) == "END   ") {
        return ch;
      }
      if (line.size() == 3 &&  line.substr(0,3) == "END") {
        return ch;
      }
      if (line.size() < 7) {
        return ch;
      }
      if (line.substr(0,6) == "MASTER") {
        getline(inFile, line);
      }
      if (line.substr(0,6) == "CONECT") {
        getline(inFile, line);
      }
    }
    
}

fragment   *pdbReader::readFrag(ifstream &inFile, string &line) {
  string resNum = line.substr(23,4);
  string resName = line.substr(17,3);
  vector<string> fragData;
  fragFactory createFrag;

  fragment *frag;
  while (true) {
    if (line.size() < 7 && (line.substr(0,6) != "END   " || line.substr(0,6) != "ENDMDL")) break;
    if (inFile.eof()) break;
    if (line.substr(0,6) == "CONECT") break;
    if (resNum != line.substr(23,4)) break;
    else if (line.substr(0,6) == "TER   ") break;
    string resName = line.substr(16,4);
    // UNCOMMENT IF YOU WANT TO READ MULTIPLE RESIDUE DEFINITION
    // FOR ECAMPLE THE HSP-90 case
    if (resName[0] == ' ' || resName[0] == 'A')
       fragData.push_back(line);
    getline(inFile, line);
  }

  
  if (fragData.size() != 0) {
    frag = createFrag.getNewFrag(resName, &fragData);
    return frag;
  } else {
    return NULL;
  }

}

pdbReader::pdbReader(string fileName) {
	ifstream inFile;
	inFile.open(fileName.c_str(), ios::in);

	vector<string> lineVec;
	list<string>		lineList;
	string line;
	int test = 0;
	
	string currentFrag, tmpString;
	while (!inFile.eof()) {
    	getline(inFile, line);
		tmpString = line.substr(0,6);
		if (tmpString == "ATOM  " || tmpString == "HETATM" ||  tmpString == "CONECT" || tmpString == "TER   " || tmpString == "ENDMDL"){
      lineVec.push_back(line);
		}
	}

	string header, serialNum, resName, atomType, chainName ;
	pdbReadFrag *frag = new pdbReadFrag;
	pdbReadChain *chain  = new pdbReadChain;
	pdbReadChain *tmpChain;
  string resNum;
  //string tmpChain = "hello world";

	for (int i=0; i<lineVec.size(); i=i) {
           resName = lineVec[i].substr(16,4); 
           while (resName[0] != ' ' || resName[0] != 'A')
              i++;
           resName = lineVec[i].substr(17,3);
           header = lineVec[i].substr(0,6);
	   atomType = lineVec[i].substr(12,4);    
	   //resName = lineVec[i].substr(17,3);
           //resName = lineVec[i].substr(16,4);
           chainName = lineVec[i].substr(21,1);
           resNum = lineVec[i].substr(22,4);
    
	   if (atomType == " OXT") {
	      i++;
	   }

     if (header == "ENDMDL") {
     }
    
		
     if (header == "TER   ") {
	 if (chain->hetAtoms.size() != 0 || chain->chain.size() != 0) {
	 tmpChain = chain;
         chains.push_back(chain);
      }
      chain = new pdbReadChain;
      i++;
      
      header = lineVec[i].substr(0,6);

      //My new crap is sitting here stinking up the whole joint.
      if (header == "ENDMDL") {
        i=lineVec.size()+1;
      }
			resName = lineVec[i].substr(17,3);
		}

		if (header == "CONECT") {
			conectVec.push_back(lineVec[i]);
			i++;
		} else {
      if (chainName != " ") {
        chain->setName(chainName);
      } else {
        chain->setName("no_pdb_name");
      }
    }
		

		if (header == "HETATM") {			
			chain->hetAtoms.push_back(lineVec[i]);
      
			resName = lineVec[i].substr(17,3);
      chainName = lineVec[i].substr(21,1);
      resNum  =  lineVec[i].substr(22,4);
      i++;
		}
    if (header == "ATOM  " ) {
      int nCount = 0;
			if (resName == "ALA") {
        resNum    = lineVec[i].substr(22,4);
        pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "ALA" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="ARG") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);       
				while (lineVec[ i ].substr(17,3) == "ARG" && lineVec[i].substr(0,6) != "TER   ") {
            if (lineVec[i].substr(12,4) == " N  ") {
            //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
            }
            frag->frag.push_back(lineVec[i]);
					  i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="MET") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "MET" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			}  else if(resName =="SER") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "SER" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="GLU") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "GLU" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="PRO") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "PRO" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="LYS") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "LYS" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="ASN") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "ASN" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="ASP") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "ASP" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="CYS") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "CYS" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="GLN") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "GLN" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="GLY") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "GLY" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="HIS") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "HIS" && lineVec[i].substr(0,6) != "TER   ")  {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="ILE") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "ILE" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="LEU") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "LEU" && lineVec[i].substr(0,6) != "TER   ") {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="PHE") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "PHE" && lineVec[i].substr(0,6) != "TER   ")  {
          if (lineVec[i].substr(12,4) == " N  ") {
          //if (lineVec[i].substr(22,4) != resNum) {  
              nCount++;
              if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="THR") {
        resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "THR" && lineVec[i].substr(0,6) != "TER   ") {
          //if (lineVec[i].substr(12,4) == " N  ") {
          if (lineVec[i].substr(22,4) != resNum) {
              //nCount++;
              //if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="TRP") {
        //resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "TRP" && lineVec[i].substr(0,6) != "TER   ") {
          //if (lineVec[i].substr(12,4) == " N  ") {
          if (lineVec[i].substr(22,4) != resNum) {  
              //nCount++;
              //if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="TYR") {
        //resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "TYR" && lineVec[i].substr(0,6) != "TER   ")  {
          //if (lineVec[i].substr(12,4) == " N  ") {
          if (lineVec[i].substr(22,4) != resNum) {
              //nCount++;
              //if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else if(resName =="VAL") {
        //resNum    = lineVec[i].substr(22,4);
				pdbReadFrag *frag = new pdbReadFrag;
        frag->setNum(resNum);
				while (lineVec[ i ].substr(17,3) == "VAL" && lineVec[i].substr(0,6) != "TER   ") {
          //if (lineVec[i].substr(12,4) == " N  ") {
          if (lineVec[i].substr(22,4) != resNum) {
              //nCount++;
              //if (nCount == 2)
                break;
          }
          frag->frag.push_back(lineVec[i]);
					i++;
				}
        //resName.append(resNum);
        frag->setName(resName);
				chain->chain.push_back(frag);
			} else {
				chain->hetAtoms.push_back(lineVec[i]);
			}
	  
		}
		
	}
  
  //chain->setName(chainName);
  if (tmpChain != chain || chains.size() == 0) {
		chains.push_back(chain);
	}

  inFile.close();
	//printStats();
}

pdbReader::~pdbReader(){
}

void pdbReader::printStats() {
	int test =0;
	for (unsigned int i=0; i<chains.size(); i++) {
		chains[i]->printStats();
	}
}





































