/**********************************************
 *   Copyright (C) 2004 by Dynamol 
 *   john.furr@dynamol.com 
 **********************************************/
#include "dtGaff.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include <iostream>
#include <iomanip>
#include <fstream>

namespace dt {
	
dtGaff::dtGaff() {}
//dtGaff::dtGaff(molecule *mol)
dtGaff::dtGaff(molPtr mol)
{   
   this->mol = mol;
   bool allGood = true;
   for (unsigned int i=0; i<mol->atoms.size(); i++) {      
      this->i = i;
      atomPtr atm = mol->atoms[i];
         
      bool wasTyped = false;
      if (atm->getAN() == 6)  wasTyped = typeCarbon(atm);
      if (atm->getAN() == 7)  wasTyped = typeNitrogen(atm);
      if (atm->getAN() == 8)  wasTyped = typeOxygen(atm);
      if (atm->getAN() == 1)  wasTyped = typeHydrogen(atm);
      if (atm->getAN() == 16) wasTyped = typeSulfer(atm);
      if (atm->getAN() == 15) wasTyped = typePhosphorus(atm);
      
      
      
      if (atm->getAN() == 9)  {wasTyped = true; atm->type="f";}
      if (atm->getAN() == 17) {wasTyped = true; atm->type="cl";}
      if (atm->getAN() == 35) {wasTyped = true; atm->type="br";}
      if (atm->getAN() == 53) {wasTyped = true; atm->type="i";}
      
      if (atm->getAN() == 3) {wasTyped = true; atm->type="Li";}
      if (atm->getAN() == 4) {wasTyped = true; atm->type="Be";}
      if (atm->getAN() == 5) {wasTyped = true; atm->type="B";}
      if (atm->getAN() == 11) {wasTyped = true; atm->type="Na";}
      if (atm->getAN() == 12) {wasTyped = true; atm->type="Mg";}
      if (atm->getAN() == 13) {wasTyped = true; atm->type="Al";}
      if (atm->getAN() == 14) {wasTyped = true; atm->type="Si";}
      if (atm->getAN() == 19) {wasTyped = true; atm->type="K";}
      if (atm->getAN() == 20) {wasTyped = true; atm->type="Ca";}
      if (atm->getAN() == 38) {wasTyped = true; atm->type="Sr";}
      if (atm->getAN() == 56) {wasTyped = true; atm->type="Ba";}
      if (atm->getAN() == 21) {wasTyped = true; atm->type="Sc";}
      if (atm->getAN() == 22) {wasTyped = true; atm->type="Ti";}
      if (atm->getAN() == 23) {wasTyped = true; atm->type="V";}
      if (atm->getAN() == 24) {wasTyped = true; atm->type="Cr";}
      if (atm->getAN() == 25) {wasTyped = true; atm->type="Mn";}
      if (atm->getAN() == 26) {wasTyped = true; atm->type="Fe";}
      if (atm->getAN() == 27) {wasTyped = true; atm->type="Co";}
      if (atm->getAN() == 28) {wasTyped = true; atm->type="Ni";}
      if (atm->getAN() == 29) {wasTyped = true; atm->type="Cu";}
      if (atm->getAN() == 30) {wasTyped = true; atm->type="Zn";}
      if (atm->getAN() == 31) {wasTyped = true; atm->type="Ga";}
      if (atm->getAN() == 32) {wasTyped = true; atm->type="Ge";}
      if (atm->getAN() == 33) {wasTyped = true; atm->type="As";}
      if (atm->getAN() == 34) {wasTyped = true; atm->type="Se";}
      if (atm->getAN() == 44) {wasTyped = true; atm->type="Ru";}
      if (atm->getAN() == 45) {wasTyped = true; atm->type="Rh";}
	  if (atm->getAN() == 79) {wasTyped = true; atm->type="Au";}
      
      if (!wasTyped) {
        //////cout <<"No Type for: " << atm->num << endl;
        allGood = false;
      }
 
     
   }
  
   fixConjugation();
  
   mol->ffType = "GAFF";
    
}


dtGaff::~dtGaff()
{
}

bool   dtGaff::typeCarbon(atomPtr atm) {
   if (atm->atoms.size() == 4) sp3Carbon(atm);
   else if (atm->atoms.size() == 3) sp2Carbon(atm);
   else if (atm->atoms.size() == 2) spCarbon(atm);

   return true; //should get rid of the return type
}

bool   dtGaff::sp3Carbon(atomPtr atm) {
   //Check for 3 && 4 memebered dtRings
   for (unsigned int i=0; i<atm->atomProps.size(); i++) {
      if (atm->atomProps[i] == "RG3" ) { atm->type = "cx"; return true;}
      else if (atm->atomProps[i] == "RG4" ) {atm->type = "cy"; return true;}
   }
   atm->type = "c3";
   return true;    
}

bool   dtGaff::sp2Carbon(atomPtr atm) {
   
   //check for carbon C=O amd C=S
   if (atm->atoms.size() == 3) {
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();
         unsigned int atomSize = level1->atoms.size();
         if ( isXA(level1) && atomSize == 1) {atm->type="c"; return true;}
      }
   }
 
   //Now lets check for planar ring carb
   //Now lets do ring check stuff
   bool isRing = false; //meanin AR2, AR3
   bool pure = false;
   for (unsigned int i=0; i<atm->atomProps.size(); i++) {
      ////////cout <<"prop: " << atm->atomProps[i] << endl;
      //You will want to check for the bridge system at the end I think
      if (atm->atomProps[i] == "AR1") 
         pure = true; 
      else if (atm->atomProps[i] == "AR2" || atm->atomProps[i] == "AR3")
         isRing = true;
   }   
   
   if (pure) {
      int AR1_count = 0;
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();
         
         for (unsigned int j=0; j<level1->atomProps.size(); j++) {
            if (level1->atomProps[j] == "AR1") {
              
               for (unsigned int k=0; k<mol->unsortedRings.size(); k++) {
                  //Make sure level1 && at are not part of the same ring
                  int ringCheck = 0;
                  for (unsigned int l=0; l<mol->unsortedRings[k].size(); l++) {
                     int num = mol->unsortedRings[k][l];
                     if (atm->getNum() == num) ringCheck++;
                     else if (level1->getNum() == num) ringCheck++;
                  }
                  if (ringCheck == 2) break;
                  AR1_count++; 
                  break;
               }
            }
         }
      }
      if (AR1_count == 3) {
         atm->type = "cp"; return true;
      }
      else {atm->type = "ca"; 
      return true;}
   }
   if (isRing && conjugatedRingCheck(atm) ) return true;
   else if (conjugatedChainCheck(atm) ) return true;

   for (unsigned int i=0; i<atm->atomProps.size(); i++) {
     if (atm->atomProps[i] == "RG3") {atm->type="cu"; return true;}
     if (atm->atomProps[i] == "RG4") {atm->type="cv"; return true;}
   }
   atm->type = "c2"; return true;
   return false;
}

bool   dtGaff::conjugatedRingCheck(atomPtr atm) {
   //This section is dependand upon the atoms environement
   //Check for sb && db property
   int sbCount = 0;
   int dbCount = 0;
   for (unsigned int i=0; i<atm->atomProps.size(); i++) {
     if ( atm->atomProps[i] == "sb" ) sbCount++;
     if ( atm->atomProps[i] == "db" ) dbCount++;
   }
   if (sbCount == dbCount == 1);
      
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();
         
         // (C3(C3))  &  (C3(C2))  &  (C3(XB2))  &  (XB2(XB2))
         if (level1->atoms.size() == 3) { 
            for (unsigned int j=0; j<level1->atoms.size(); j++) {
               //atom *level2 = level1->atoms[j];
               atomPtr level2 = level1->atoms[j].lock();
               unsigned int atomSize = level2->atoms.size();
               
               if (level2->getAN() == 6 && atomSize == 3) {atm->type = "cc"; return true;}
               if (level2->getAN() == 6 && atomSize == 2) {atm->type = "cc"; return true;}
               if ( isXB(level2) && atomSize == 2) {atm->type = "cc"; return true;}
            }
         }
         
         //XB2(XB2)) & XB2(C2)) & XB2(C3))
         if ( isXB(level1) && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->atoms.size(); j++) {
               //atom *level2 = level1->atoms[i];
               //atom *level2 = level1->atoms[j]; //MADE CHANGE HERE
               atomPtr level2 = level1->atoms[j].lock();
               unsigned int atomSize = level2->atoms.size();
               
               if (isXB(level2) && atomSize==2) {atm->type="cc"; return true;}
               if (level2->getAN()==6 && atomSize==2) {atm->type="cc"; return true;}
               if (level2->getAN()==6 && atomSize==3) {atm->type="cc"; return true;}
            }
         }
         
         //C3[sb']
         if (level1->getAN() == 6 && level1->atoms.size() == 3) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (from==level1 && to==atm && bd->order == 1) {atm->type="cc"; return true;}
               if (to==level1 && from==atm && bd->order == 1) {atm->type="cc"; return true;}
            }
         }
      
      	 //Now check (XB2[sb'])
         if (isXB(level1) && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (from==level1 && to==atm && bd->order == 1) {atm->type="cc"; return true;}
               if (to==level1 && from==atm && bd->order == 1) {atm->type="cc"; return true;}
            }
        }
      
         //(XD3[sb', db])  &  (XD4(sb', db])      
         if ( isXD(level1) && (level1->atoms.size() == 3 || level1->atoms.size() == 4)) {
            bool singleCheck = false;
            bool doubleCheck = false;
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();           
               if (bd->order == 2) doubleCheck = true;
               if (from == level1 && to == atm && bd->order == 1) singleCheck = true;
               if (to == level1 && from == atm && bd->order == 1) singleCheck = true;
            }
            if (singleCheck && doubleCheck) {atm->type="cc"; return true;}
         }
         
   }
   return false;
}

bool   dtGaff::conjugatedChainCheck(atomPtr atm) {
   int sbCount = 0;
   int dbCount = 0;
   
   for (unsigned int i=0; i<atm->atomProps.size(); i++) {
     if ( atm->atomProps[i] == "sb" ) sbCount++;
     if ( atm->atomProps[i] == "db" ) dbCount++;
   }

   if (sbCount >= 1 && dbCount >= 1) {
      
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         atomPtr level1 = atm->atoms[i].lock();
         if (level1->getAN() == 6 && level1->atoms.size() == 3) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               bondPtr bd = level1->bonds[j].lock();
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="ce"; return true;}
               if (from==atm && bd->order == 1) {atm->type="ce"; return true;}
            }
         }
         
         if (level1->getAN() == 6 && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               bondPtr bd = level1->bonds[j].lock();
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="ce"; return true;}
               if (from==atm && bd->order == 1) {atm->type="ce"; return true;}
            }
         }
      
         //Now check (XB2[sb'])
         if (isXB(level1) && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               bondPtr bd = level1->bonds[j].lock();
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="ce"; return true;}
               if (from==atm && bd->order == 1) {atm->type="ce"; return true;}
            }
         }
      
         //(XD3[sb', db])  &  (XD4(sb', db])      
         if ( isXD(level1) && (level1->atoms.size() == 3 || level1->atoms.size() == 4)) {
            bool singleCheck = false;
            bool doubleCheck = false;
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock(); 
               if (bd->order == 2) doubleCheck = true;
               if (to == atm && bd->order == 1) singleCheck = true;
               if (from == atm && bd->order == 1) singleCheck = true;
            }
         
            if (singleCheck && doubleCheck) {atm->type="ce"; return true;}
         }
      }
   }
   return false;
}

bool   dtGaff::spCarbon(atomPtr atm) {
   //Still need to do conjugated chain checks
   int sbCount = 0;
   int tbCount = 0;
   for (unsigned int i=0; i<atm->bonds.size(); i++) {
     //bond *bd = atm->bonds[i];
     bondPtr bd = atm->bonds[i].lock();
     if (bd->order == 1) sbCount++;
     else if (bd->order == 3) tbCount++;
   }
  // //////cout <<"sbCount: " << sbCount << endl;
  // //////cout <<"tbCount: " << tbCount << endl;
   if (sbCount >= 1 && tbCount >= 1) {
     // //////cout <<"Yeah you are trying to type it here"<<endl;
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();
         unsigned int atomSize = level1->atoms.size();
         //(C2[sb'])   &  (C3(sb']
         if (level1->getAN() == 6 && (atomSize == 2 || atomSize == 3)) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to == atm && bd->order == 1) {atm->type="cg"; return true;}
               if (from == atm && bd->order == 1) {atm->type="cg"; return true;}
            }
         }
         
         //(N1[sb']
         if (level1->getAN() == 7 && atomSize == 1) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock(); 
               if (to == atm && bd->order == 1) {atm->type="cg"; return true;}
               if (from == atm && bd->order == 1) {atm->type="cg"; return true;}
            }
         }
         
         //(XB2[sb']
         if ( isXB(level1) && atomSize == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock(); 
               if (to == atm && bd->order == 1) {atm->type="cg"; return true;}
               if (from == atm && bd->order == 1) {atm->type="cg"; return true;}
            }
         }
      }  
      
   }
   if (atm->atoms.size() == 2) {atm->type="c1"; return true;}
   if (atm->atoms.size() == 1) {atm->type="c2"; return true;}
   return false;
}

bool dtGaff::typeNitrogen(atomPtr atm) {
   //cout <<"You are in type nitrogen"<<endl;
   //cout <<"atm->atoms.size(): " << atm->atoms.size() << endl;
   //Check for amide fist
   for (unsigned int i=0; i<atm->atoms.size(); i++) {
      //atom *level1 = atm->atoms[i];
      atomPtr level1 = atm->atoms[i].lock();
      //check for the ring thing
      bool notAroRing = true;
      for (unsigned int j=0; j<level1->atomProps.size(); j++) {
         if (level1->atomProps[j] == "RG6" && atm->atoms.size() != 3)  {
	         notAroRing = false;
         }
      }
      if (level1->getAN() == 6 && level1->atoms.size() == 3 && notAroRing) {
         for (unsigned int j=0; j<level1->atoms.size(); j++) {
           //atom *level2 = level1->atoms[j]; 
           atomPtr level2 = level1->atoms[j].lock();
           if ( isXA(level2) && level2->atoms.size() == 1 ) {atm->type = "n"; return true;}
         }
      }
   }
   if (atm->atoms.size() == 4) {atm->type = "n4"; return true;}
   
   //Now check for nitro
   int nitroCount = 0;
   for (unsigned int i=0; i<atm->atoms.size(); i++) {
     //atom *level1 = atm->atoms[i];
     atomPtr level1 = atm->atoms[i].lock();
     if (level1->getAN() == 8 && level1->atoms.size() == 1) nitroCount++;
   }
   if (nitroCount == 2) {atm->type = "no"; return true;}
   
   //This section checks for the nb case were tbo is 4 && atoms.size() == 3
   // aka the biphenyl case
   int tbo = 0;
   //cout <<"atm->bonds.size(): " << atm->bonds.size() << endl;
   for (unsigned int i=0; i<atm->bonds.size(); i++) {
      bondPtr bd = atm->bonds[i].lock();
      //tbo += atm->bonds[i]->order;
      tbo += bd->order;
   }
   //cout <<"tbo: " << tbo << endl;
   //int g = 0; cin >> g;
   if (tbo == 4 && atm->atoms.size() == 3) {
      int aroCheck = 0;
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();
         for (unsigned int j=0; j<level1->atomProps.size(); j++) {
            if (level1->atomProps[j] == "AR1") aroCheck++;
         }   
      }
      if (aroCheck == 3) {atm->type = "nb"; return true;}   
   }
   
   if (atm->atoms.size() == 3 && tbo == 4) {atm->type = "na"; return true;}
  
   if (atm->atoms.size() == 3 && tbo == 3) {
      for (unsigned int i=0; i<atm->atomProps.size(); i++) {
        if (atm->atomProps[i] == "AR1") {atm->type = "na"; return true;}
        if (atm->atomProps[i] == "AR2") {atm->type = "na"; return true;}
        if (atm->atomProps[i] == "AR3") {atm->type = "na"; return true;}
      }
      
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();
         for (unsigned int j=0; j<level1->atomProps.size(); j++) {
           if (level1->atomProps[j] == "AR1") {atm->type = "nh"; return true;}
           if (level1->atomProps[j] == "AR2") {atm->type = "nh"; return true;}
           if (level1->atomProps[j] == "AR3") {atm->type = "nh"; return true;} 
         }
         
         if (level1->getAN() == 6 && level1->atoms.size() == 3) {
           for (unsigned int j=0; j<level1->bonds.size(); j++) {
	           if (level1->bonds[j].lock()->order == 2) 
              {atm->type = "nh"; return true;}
           }
         }
         if (level1->getAN() == 7 && level1->atoms.size() == 2) {
           for (unsigned int j=0; j<level1->bonds.size(); j++) {
	           if (level1->bonds[j].lock()->order == 2) 
              {atm->type = "nh"; return true;}
           }
         }
         if (level1->getAN() == 15 && level1->atoms.size() == 2) {
           for (unsigned int j=0; j<level1->bonds.size(); j++) {
	           if (level1->bonds[j].lock()->order == 2) 
              {atm->type = "nh"; return true;}
           }
         }
      }
      
      atm->type = "n3"; 
      return true;     
   }
   
   //Now check for pure aromatic
   if (atm->atoms.size() == 2) {
     bool isRing = false;
     for (unsigned int i=0; i<atm->atomProps.size(); i++) {
       if (atm->atomProps[i] == "AR1") {atm->type = "nb"; return true;}
       if (atm->atomProps[i] == "AR2") isRing = true;
       else if (atm->atomProps[i] == "AR3") isRing = true;
     }
     
     if (isRing) {
        if (ringNitrogen(atm) ) return true;
     } else {
        if ( chainNitrogen(atm) ) return true;
     }
   }
   
   if (atm->atoms.size() == 2) {
      int sb = 0;
      int db = 0;
      int tb = 0;
      for (unsigned int i=0; i<atm->bonds.size(); i++) {
         bondPtr bd = atm->bonds[i].lock();
         if (bd->order == 1) sb++;
         if (bd->order == 2) db++;
         if (bd->order == 3) tb++; 
      }
      if (db == 2) {atm->type="n1"; return true;}
      if (sb ==1 && tb == 1) {atm->type="n1"; return true;}
      atm->type="n2";
      return true;
   }
   
   if (atm->atoms.size() == 1) {atm->type="n1"; return true;}
   return false;
}

bool dtGaff::ringNitrogen(atomPtr atm) {
  ////////cout <<"Lets check out those ring nitrogen properties!"<<endl;
   
   for (unsigned int i=0; i<atm->atoms.size(); i++) {
      //atom *level1 = atm->atoms[i];
      atomPtr level1 = atm->atoms[i].lock();
      if (level1->atoms.size() == 3 && level1->getAN() == 6) {
         for (unsigned int j=0; j<level1->atoms.size(); j++) {
            //atom * level2 = level1->atoms[j];
            atomPtr level2 = level1->atoms[j].lock();
            if (level2->getAN() == 6 && level2->atoms.size() == 2) {atm->type="nc"; return true;}
            if (level2->getAN() == 6 && level2->atoms.size() == 3) {atm->type="nc"; return true;}
            if (isXB(level2) && level2->atoms.size() == 2) {atm->type="nc"; return true;}
         }
      }
      
      if (isXB(level1) && level1->atoms.size() == 2) {
         for (unsigned int j=0; j<level1->atoms.size(); j++) {
            //atom *level2 = level1->atoms[j];
            atomPtr level2 = level1->atoms[j].lock();
            if (isXB(level2) && level2->atoms.size() == 2) {atm->type="nc"; return true;}
            if (level2->getAN()==6 && level2->atoms.size() == 2) {atm->type="nc"; return true;}
            if (level2->getAN()==6 && level2->atoms.size() == 3) {atm->type="nc"; return true;}
         }
      }

      //Now check (C3[sb'])
      if (level1->getAN() == 6 && level1->atoms.size() == 3) {
         for (unsigned int j=0; j<level1->bonds.size(); j++) {
            //bond *bd = level1->bonds[j];
            bondPtr bd = level1->bonds[j].lock();
            //atom *from = bd->from;
            //atom *to = bd->to;
            atomPtr from = bd->from.lock();
            atomPtr to = bd->to.lock();
            if (from == level1 && to == atm && bd->order == 1) {atm->type="nc"; return true;}
            if (to == level1 && from == atm && bd->order == 1) {atm->type="nc"; return true;}
         }
      }

      //Now check (XB2[sb'])
      if (isXB(level1) && level1->atoms.size() == 2) {
         for (unsigned int j=0; j<level1->bonds.size(); j++) {
            //bond *bd = level1->bonds[j];
            bondPtr bd = level1->bonds[j].lock();
            //atom *from = bd->from;
            //atom *to = bd->to;
            atomPtr from = bd->from.lock();
            atomPtr to = bd->to.lock();
            if (from == level1 && to == atm && bd->order == 1) {atm->type="nc"; return true;}
            if (to == level1 && from == atm && bd->order == 1) {atm->type="nc"; return true;}
         }
      }

      //(XD3[sb', db])  &  (XD4(sb', db])      
      if ( isXD(level1) && (level1->atoms.size() == 3 || level1->atoms.size() == 4)) {
         bool singleCheck = false;
         bool doubleCheck = false;
         for (unsigned int j=0; j<level1->bonds.size(); j++) {
            //bond *bd = level1->bonds[j];
            bondPtr bd = level1->bonds[j].lock();
            //atom *from = bd->from;
            //atom *to = bd->to;
            atomPtr from = bd->from.lock();
            atomPtr to = bd->from.lock(); 
            if (bd->order == 2) doubleCheck = true;
            if (from == level1 && to == atm && bd->order == 1) singleCheck = true;
            if (to == level1 && from == atm && bd->order == 1) singleCheck = true;
         }
         
         if (singleCheck && doubleCheck) {atm->type="nc"; return true;}
      }    
   }
  return false;
}

bool dtGaff::chainNitrogen(atomPtr atm) {
   int sbCount = 0;
   int dbCount = 0;
   
   for (unsigned int i=0; i<atm->atomProps.size(); i++) {
     if ( atm->atomProps[i] == "sb" ) sbCount++;
     if ( atm->atomProps[i] == "db" ) dbCount++;
   }
  // //////cout <<"conjugatedChainCheck "<< sbCount << "\t" << dbCount << endl;
   if (sbCount >= 1 && dbCount >= 1) {
      
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();
         //C3[sb']  &  C2[sb']
         if (level1->getAN() == 6 && level1->atoms.size() == 3) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="ne"; return true;}
               if (from==atm && bd->order == 1) {atm->type="ne"; return true;}
            }
         }
         
         if (level1->getAN() == 6 && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="ne"; return true;}
               if (from==atm && bd->order == 1) {atm->type="ne"; return true;}
            }
         }
         //Now check (XA2[sb'])
         if (isXA(level1) && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="ne"; return true;}
               if (from==atm && bd->order == 1) {atm->type="ne"; return true;}
            }
         }
         
         //Now check (XB2[sb'])
         if (isXB(level1) && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="ne"; return true;}
               if (from==atm && bd->order == 1) {atm->type="ne"; return true;}
            }
         }
      
         //(XD3[sb', db])  &  (XD4(sb', db])      
         if ( isXD(level1) && (level1->atoms.size() == 3 || level1->atoms.size() == 4)) {
            bool singleCheck = false;
            bool doubleCheck = false;
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (bd->order == 2) doubleCheck = true;
               if (to == atm && bd->order == 1) singleCheck = true;
               if (from == atm && bd->order == 1) singleCheck = true;
            }
         
            if (singleCheck && doubleCheck) {atm->type="ne"; return true;}
         }
      }
   }
   
   return false;
}

bool  dtGaff::isXA(atomPtr atm) {
  if (atm->getAN() == 8 )  return true;
  if (atm->getAN() == 16 ) return true;
  return false;
}
bool  dtGaff::isXB(atomPtr atm) {
   if (atm->getAN() == 7 || atm->getAN() == 15) return true;
   return false;
}
bool  dtGaff::isXC(atomPtr atm) {
   if (atm->getAN() == 9) return true;
   if (atm->getAN() == 17) return true;
   if (atm->getAN() == 35) return true;
   if (atm->getAN() == 53) return true;
   return false;
}
bool  dtGaff::isXD(atomPtr atm) {
   if (atm->getAN() == 16 || atm->getAN() == 15) return true;
   return false;
}

bool dtGaff::typeOxygen(atomPtr atm) {
   if (atm->atoms.size() == 1) {atm->type="o"; return true;}
   
   int hNum = 0;
   for (unsigned int i=0; i<atm->atoms.size(); i++) {
     //atom *tmp = atm->atoms[i];
     atomPtr tmp = atm->atoms[i].lock();
     if (tmp->getAN() == 1) hNum++;
   }
   
   if (atm->atoms.size() == 2 && hNum == 1) {atm->type="oh"; return true;}
   if (atm->atoms.size() == 2 && hNum == 2) {atm->type="oh"; return true;}
   if (atm->atoms.size() == 3 && hNum == 1) {atm->type="oh"; return true;}
   if (atm->atoms.size() == 3 && hNum == 2) {atm->type="oh"; return true;}
   if (atm->atoms.size() == 3 && hNum == 3) {atm->type="oh"; return true;}
   if (atm->atoms.size() == 2) {atm->type="os"; return true;}
   if (atm->atoms.size() == 3) {atm->type="os"; return true;}
   
   atm->type="os";
   return true;
   
}

bool dtGaff::typeHydrogen(atomPtr atm) {
   if (atm->atoms.size() != 1) return false;
   if (atm->atoms[0].lock()->getAN() == 7) {atm->type="hn"; return true;}
   if (atm->atoms[0].lock()->getAN() == 8) {atm->type="ho"; return true;}
   if (atm->atoms[0].lock()->getAN() == 16) {atm->type="hs"; return true;}
   if (atm->atoms[0].lock()->getAN() == 15) {atm->type="hp"; return true;}
   
   //atom *level1 = atm->atoms[0];
   atomPtr level1 = atm->atoms[0].lock();
   // (C(N4));
   if (level1->getAN() == 6) {
      for (unsigned int i=0; i<level1->atoms.size(); i++) {
         //atom *level2 = level1->atoms[i];
         atomPtr level2 = level1->atoms[i].lock();
         if (level2->getAN() == 7 && level2->atoms.size() == 4) {atm->type="hx"; return true;};
      }
   }
   
    // (O(H1));
   if (level1->getAN() == 8) {
      for (unsigned int i=0; i<level1->atoms.size(); i++) {
         //atom *level2 = level1->atoms[i];
         atomPtr level2 = level1->atoms[i].lock();
         if (level2 != atm) {
            if (level2->getAN() == 8 && level2->atoms.size() == 1) {atm->type="hw"; return true;};
         }
      }
   }
   
   int EWD = 0;
   for (unsigned int i=0; i<level1->atoms.size(); i++) {
      if ( isEWD(level1->atoms[i].lock()) ) EWD++;
   }
   
   if (level1->getAN() == 6 && level1->atoms.size() == 4 && EWD == 3) {atm->type="h3"; return true;}
   if (level1->getAN() == 6 && level1->atoms.size() == 4 && EWD == 2) {atm->type="h2"; return true;}
   if (level1->getAN() == 6 && level1->atoms.size() == 4 && EWD == 1) {atm->type="h1"; return true;}
   if (level1->getAN() == 6 && level1->atoms.size() == 4 && EWD == 0) {atm->type="hc"; return true;}
  
   ////////cout <<"EWD is: " << EWD << setw(12)<<"atmNum is " << atm->num<< endl; 
   //Check for C3(O1)...not in the param file correctly
   if (level1->getAN() == 6 && level1->atoms.size() == 3) {
      for (int unsigned i=0; i<level1->atoms.size(); i++) {
         //atom *level2 = level1->atoms[i];
         atomPtr level2 = level1->atoms[i].lock();
         unsigned int atomSize = level2->atoms.size();
         if ( isXA(level2) && atomSize==1) {atm->type="ha";}// return true;}
      }
   }
   if (level1->getAN() == 6 && level1->atoms.size() == 3 && EWD == 2) {atm->type="h5"; return true;}
   if (level1->getAN() == 6 && level1->atoms.size() == 3 && EWD == 1) {atm->type="h4"; return true;}
   
   atm->type="ha";
   return true;
}

/** this returns true if the atom is an elctron withdrawing group
   defined as:   N, O, F, Cl, Br
   */
bool dtGaff::isEWD(atomPtr atm) {
   if (atm->getAN() == 7) return true;
   if (atm->getAN() == 8) return true;
   if (atm->getAN() == 9) return true;
   if (atm->getAN() == 17) return true;
   if (atm->getAN() == 35) return true;
   return false;
}

bool dtGaff::typeSulfer(atomPtr atm) {
   //if (atm->atoms.size() == 1) {atm->type = "s2"; return true;}
   if (atm->atoms.size() == 1) {atm->type = "s2"; return true;}
   
   if (atm->atoms.size() == 2) {
      for (unsigned int i=0; i<atm->atomProps.size(); i++) {
         if (atm->atomProps[i] == "db") {atm->type="s2"; return true;}
         if (atm->atomProps[i] == "tb") {atm->type="s2"; return true;}
      }
      
      int hCount = 0;
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();
         if (level1->getAN() == 1) hCount++;
      }
      
      if (hCount == 1) {atm->type="sh"; return true;}
      if (hCount == 2) {atm->type="sh"; return true;}   
      
      atm->type="ss";
      return true;
   }
   
   if (atm->atoms.size() == 3) {
      bool hasDouble = false;
      for (unsigned int i=0; i<atm->atomProps.size(); i++) {
         if (atm->atomProps[i] == "db") hasDouble = true;
      }
      
      if (hasDouble) {
         
         for (unsigned int i=0; i<atm->atoms.size(); i++) {
            //atom *level1 = atm->atoms[i];
            atomPtr level1 = atm->atoms[i].lock(); 
            //(XB2[sb']
            if ( isXB(level1) && level1->atoms.size() == 2) {
               for (unsigned int j=0; j<level1->bonds.size(); j++) {
                  //bond *bd = level1->bonds[j];
                  bondPtr bd = level1->bonds[j].lock();
                  //atom *from = bd->from;
                  //atom *to = bd->to;
                  atomPtr from = bd->from.lock();
                  atomPtr to = bd->to.lock(); 
                  if (bd->order == 1) {
                     if (to == atm || from == atm) {atm->type="sx"; return true;}
                     if (from == atm || to == atm) {atm->type="sx"; return true;}
                  }               
               }
            }       
            //(C3[sb'])
            if ( level1->getAN() == 6 && level1->atoms.size() == 3) {
               for (unsigned int j=0; j<level1->bonds.size(); j++) {
                  //bond *bd = level1->bonds[j];
                  bondPtr bd = level1->bonds[j].lock();
                  //atom *from = bd->from;
                  //atom *to = bd->to;
                  atomPtr from = bd->from.lock();
                  atomPtr to = bd->to.lock();
                  if (bd->order == 1) {
                     if (to == atm || from == atm) {atm->type="sx"; return true;}
                     if (from == atm || to == atm) {atm->type="sx"; return true;}
                  }               
               }
            }   
            
            //(XD3[sb', db]
            unsigned int size = level1->atoms.size();
            if ( isXD(level1) && (size == 3 || size == 4)) {
               bool sb = false;
               bool db = false;
               for (unsigned int j=0; j<level1->bonds.size(); j++) {
                  //bond *bd = level1->bonds[j];
                  bondPtr bd = level1->bonds[j].lock();
                  //atom *from = bd->from;
                  //atom *to = bd->to;
                  atomPtr from = bd->from.lock();
                  atomPtr to = bd->to.lock();
                  if (bd->order == 1) {
                     if (to == atm || from == atm) sb = true;
                     if (from == atm || to == atm) sb = true;
                  } 
                  if (bd->order == 2) db = true;              
               }
               if (sb && db) {atm->type="sx"; return true;}
            }               
         }
      }
      atm->type="s4";
      return true;
   }
   
   if(atm->atoms.size() == 4) {
   bool hasDouble = false;
      for (unsigned int i=0; i<atm->atomProps.size(); i++) {
         if (atm->atomProps[i] == "db") hasDouble = true;
      }
      
      if (hasDouble) {
         
         for (unsigned int i=0; i<atm->atoms.size(); i++) {
            //atom *level1 = atm->atoms[i];
            atomPtr level1 = atm->atoms[i].lock();
            
            //(XB2[sb']
            if ( isXB(level1) && level1->atoms.size() == 2) {
               for (unsigned int j=0; j<level1->bonds.size(); j++) {
                  //bond *bd = level1->bonds[j]; 
                  bondPtr bd = level1->bonds[j].lock();
                  //atom *from = bd->from;
                  //atom *to = bd->to;
                  atomPtr from = bd->from.lock();
                  atomPtr to = bd->to.lock();
                  if (bd->order == 1) {
                     if (to == atm || from == atm) {atm->type="sy"; return true;}
                     if (from == atm || to == atm) {atm->type="sy"; return true;}
                  }               
               }
            }       
            //(C3[sb'])
            if ( level1->getAN() == 6 && level1->atoms.size() == 3) {
               for (unsigned int j=0; j<level1->bonds.size(); j++) {
                  //bond *bd = level1->bonds[j];
                  bondPtr bd = level1->bonds[j].lock();
                  //atom *from = bd->from;
                  //atom *to = bd->to;
                  atomPtr from = bd->from.lock();
                  atomPtr to = bd->to.lock();
                  if (bd->order == 1) {
                     if (to == atm || from == atm) {atm->type="sy"; return true;}
                     if (from == atm || to == atm) {atm->type="sy"; return true;}
                  }               
               }
            }   
            
            //(XD3[sb', db]
            int size = level1->atoms.size();
            if ( isXD(level1) && (size == 3 || size == 4)) {
               bool sb = false;
               bool db = false;
               for (unsigned int j=0; j<level1->bonds.size(); j++) {
                  //bond *bd = level1->bonds[j];
                  bondPtr bd = level1->bonds[j].lock();
                  //atom *from = bd->from;
                  //atom *to = bd->to;
                  atomPtr from = bd->from.lock();
                  atomPtr to = bd->to.lock();
                  if (bd->order == 1) {
                     if (to == atm || from == atm) sb = true;
                     if (from == atm || to == atm) sb = true;
                  } 
                  if (bd->order == 2) db = true;              
               }
               if (sb && db) {atm->type="sy"; return true;}
            }               
         }
      }
      atm->type="s6";
      return true;
   }
   
   if(atm->atoms.size() == 5) atm->type = "s6"; return true;
   if(atm->atoms.size() == 6) atm->type = "s6"; return true;
   
   return false;
}

bool dtGaff::typePhosphorus(atomPtr atm) {
   ////////cout <<"typePhosphorus"<<endl;
   //Need to do stuff for dtRings && then for chains
   bool isAR1 = false;
   for (unsigned int i=0; i<atm->atomProps.size(); i++) {
      //////cout <<atm->atomProps[i] << endl;
      if (atm->atomProps[i] == "AR2" || atm->atomProps[i] == "AR3") {
         ////////cout <<"Doing the ring???"<< endl;
         if ( ringPhosphorus(atm) ) return true; 
      }
      if (atm->atomProps[i] == "AR1") isAR1 = true;
   }
   ////////cout <<"You are now here!"<<endl;
   
   if ( isAR1 ) {atm->type = "pb"; return true;}
   ////////cout <<"Should be checking chain stuff"<<endl;
   if ( chainPhosphorus(atm) ) return true;
     
   return false;
}

bool dtGaff::ringPhosphorus(atomPtr atm) {
////////cout <<"Lets check out those ring nitrogen properties!"<<endl;
   for (unsigned int i=0; i<atm->atoms.size(); i++) {
      //atom *level1 = atm->atoms[i];
      atomPtr level1 = atm->atoms[i].lock();
      if (level1->atoms.size() == 3 && level1->getAN() == 6) {
         for (unsigned int j=0; j<level1->atoms.size(); j++) {
            //atom * level2 = level1->atoms[j];
            atomPtr level2 = level1->atoms[j].lock();
            if (level2->getAN() == 6 && level2->atoms.size() == 2) {atm->type="pc"; return true;}
            if (level2->getAN() == 6 && level2->atoms.size() == 3) {atm->type="pc"; return true;}
            if (isXB(level2) && level2->atoms.size() == 2) {atm->type="pc"; return true;}
         }
      }
         
      if (isXB(level1) && level1->atoms.size() == 2) {
         for (unsigned int j=0; j<level1->atoms.size(); j++) {
            //atom *level2 = level1->atoms[j];
            atomPtr level2 = level1->atoms[j].lock();
            if (isXB(level2) && level2->atoms.size() == 2) {atm->type="pc"; return true;}
            if (level2->getAN() == 6 && level2->atoms.size() == 2) {atm->type="pc"; return true;}
            if (level2->getAN() == 6 && level2->atoms.size() == 3) {atm->type="pc"; return true;}
         }
      }
         
      //Now check (C3[sb'])
      if (level1->getAN() == 6 && level1->atoms.size() == 3) {
         for (unsigned int j=0; j<level1->bonds.size(); j++) {
            //bond *bd = level1->bonds[j];
            bondPtr bd = level1->bonds[j].lock();
            //atom *from = bd->from;
            //atom *to = bd->to;
            atomPtr from = bd->from.lock();
            atomPtr to = bd->to.lock();
            if (from == level1 && to == atm && bd->order == 1) {atm->type="pc"; return true;}
            if (to == level1 && from == atm && bd->order == 1) {atm->type="pc"; return true;}
         }
      }
      
      //Now check (XB2[sb'])
      if (isXB(level1) && level1->atoms.size() == 2) {
         for (unsigned int j=0; j<level1->bonds.size(); j++) {
            //bond *bd = level1->bonds[j];
            bondPtr bd = level1->bonds[j].lock();
            //atom *from = bd->from;
            //atom *to = bd->to;
            atomPtr from = bd->from.lock();
            atomPtr to = bd->to.lock();
            if (from == level1 && to == atm && bd->order == 1) {atm->type="pc"; return true;}
            if (to == level1 && from == atm && bd->order == 1) {atm->type="pc"; return true;}
         }
      }
      
      //(XD3[sb', db])  &  (XD4(sb', db])      
      if ( isXD(level1) && (level1->atoms.size() == 3 || level1->atoms.size() == 4)) {
         bool singleCheck = false;
         bool doubleCheck = false;
         for (unsigned int j=0; j<level1->bonds.size(); j++) {
            //bond *bd = level1->bonds[j];
            bondPtr bd = level1->bonds[j].lock();
            //atom *from = bd->from;
            //atom *to = bd->to;
            atomPtr from = bd->from.lock();
            atomPtr to = bd->to.lock();
            if (bd->order == 2) doubleCheck = true;
            if (from == level1 && to == atm && bd->order == 1) singleCheck = true;
            if (to == level1 && from == atm && bd->order == 1) singleCheck = true;
         }
         
         if (singleCheck && doubleCheck) {atm->type="pc"; return true;}
      }
         
   }
  return false;
}

bool dtGaff::chainPhosphorus(atomPtr atm) {
int sbCount = 0;
   int dbCount = 0;
   ////////cout <<"ChainPhosphorus"<<endl;
   for (unsigned int i=0; i<atm->atomProps.size(); i++) {
     if ( atm->atomProps[i] == "sb" ) sbCount++;
     if ( atm->atomProps[i] == "db" ) dbCount++;
   }
   if (sbCount >= 1 && dbCount >= 1 && atm->atoms.size() == 2) {
      
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();
         //C3[sb']  &  C2[sb']
         if (level1->getAN() == 6 && level1->atoms.size() == 3) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock(); 
               if (to==atm && bd->order == 1) {atm->type="pe"; return true;}
               if (from==atm && bd->order == 1) {atm->type="pe"; return true;}
            }
         }
         
         if (level1->getAN() == 6 && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="pe"; return true;}
               if (from==atm && bd->order == 1) {atm->type="pe"; return true;}
            }
         }
         //Now check (XA2[sb'])
         if (isXA(level1) && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="pe"; return true;}
               if (from==atm && bd->order == 1) {atm->type="pe"; return true;}
            }
         }
         
         //Now check (XB2[sb'])
         if (isXB(level1) && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="pe"; return true;}
               if (from==atm && bd->order == 1) {atm->type="pe"; return true;}
            }
         }
      
         //(XD3[sb', db])  &  (XD4(sb', db])      
         if ( isXD(level1) && (level1->atoms.size() == 3 || level1->atoms.size() == 4)) {
            bool singleCheck = false;
            bool doubleCheck = false;
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (bd->order == 2) doubleCheck = true;
               if (to == atm && bd->order == 1) singleCheck = true;
               if (from == atm && bd->order == 1) singleCheck = true;
            }
         
            if (singleCheck && doubleCheck) {atm->type="pe"; return true;}
         }
      }
      
      atm->type = "p2"; 
      return true;
   }
   
   if (dbCount >= 1 && atm->atoms.size() == 1) {
      atm->type == "p2";
      return true;
   }
   
   if (dbCount >= 1 && atm->atoms.size() == 3) {
      ////////cout <<"Yeah you are in the right block"<<endl;
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();         
         //Now check (XB2[sb'])
         if (isXB(level1) && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="px"; return true;}
               if (from==atm && bd->order == 1) {atm->type="px"; return true;}
            }
         }
      
         //C3[sb']
         if (level1->getAN() == 6 && level1->atoms.size() == 3) {
            ////////cout <<"YOu are here"<<endl;
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="px"; return true;}
               if (from==atm && bd->order == 1) {atm->type="px"; return true;}
            }
         }
         //(XD3[sb', db])  &  (XD4(sb', db])      
         if ( isXD(level1) && (level1->atoms.size() == 3 || level1->atoms.size() == 4)) {
            bool singleCheck = false;
            bool doubleCheck = false;
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (bd->order == 2) doubleCheck = true;
               if (to == atm && bd->order == 1) singleCheck = true;
               if (from == atm && bd->order == 1) singleCheck = true;
            }
         
            if (singleCheck && doubleCheck) {atm->type="px"; return true;}
         }
         
         //Now check (XA2[sb'])
         if (isXA(level1) && level1->atoms.size() == 1) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to; 
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="px"; return true;}
               if (from==atm && bd->order == 1) {atm->type="px"; return true;}
            }
         }   
      }
      atm->type="p4";
      return true;
   }
   
   if (atm->atoms.size() == 3) {atm->type = "p3"; return true;}
   
   
   if (dbCount >= 1 && atm->atoms.size() == 4) {
      
      for (unsigned int i=0; i<atm->atoms.size(); i++) {
         //atom *level1 = atm->atoms[i];
         atomPtr level1 = atm->atoms[i].lock();         
         //Now check (XB2[sb'])
         if (isXB(level1) && level1->atoms.size() == 2) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to; 
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="py"; return true;}
               if (from==atm && bd->order == 1) {atm->type="py"; return true;}
            }
         }
      
          if (level1->getAN() == 6 && level1->atoms.size() == 3) {
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (to==atm && bd->order == 1) {atm->type="py"; return true;}
               if (from==atm && bd->order == 1) {atm->type="py"; return true;}
            }
         }
         
         //(XD3[sb', db])  &  (XD4(sb', db])      
         if ( isXD(level1) && (level1->atoms.size() == 3 || level1->atoms.size() == 4)) {
            bool singleCheck = false;
            bool doubleCheck = false;
            for (unsigned int j=0; j<level1->bonds.size(); j++) {
               //bond *bd = level1->bonds[j];
               bondPtr bd = level1->bonds[j].lock();
               //atom *from = bd->from;
               //atom *to = bd->to;
               atomPtr from = bd->from.lock();
               atomPtr to = bd->to.lock();
               if (bd->order == 2) doubleCheck = true;
               if (to == atm && bd->order == 1) singleCheck = true;
               if (from == atm && bd->order == 1) singleCheck = true;
            }
         
            if (singleCheck && doubleCheck) {atm->type="py"; return true;}
         }
      }
      atm->type = "p5";
      return true;
   }
   
   if (atm->atoms.size() >= 4) {
      atm->type = "p5";
      return true;
   }
  
   return false;
}

void dtGaff::fixConjugation() {
   for (unsigned int j=0; j<mol->bonds.size(); j++) {
   for (unsigned int i=0; i<mol->bonds.size(); i++) {
      //bond *bd = mol->bonds[i];
      bondPtr bd = mol->bonds[i];
      //atom *from = bd->from;
      //atom *to = bd->to;
      atomPtr from = bd->from.lock();
      atomPtr to = bd->to.lock();
      int order = bd->order;
      
      //bool singleCheck = false;
      //bool doubleCheck = false;
      
      bool fromGroupI = false;
      bool fromGroupII = false;
      bool toGroupI = false;
      bool toGroupII = false;
      
      if ( isGroupI(from))   fromGroupI = true;
      if ( isGroupII(from))  fromGroupII = true;
      
      if ( isGroupI(to))   toGroupI = true;
      if ( isGroupII(to))  toGroupII = true;
      
      if (order == 1) {
         if (fromGroupI && toGroupII && !from->changed) {flipGroup(from); from->changed = true;}
         else if (fromGroupI && toGroupII && !to->changed) {flipGroup(to); to->changed = true;}
         else if (fromGroupII && toGroupI && !from->changed) {flipGroup(from); from->changed = true;}
         else if (fromGroupII && toGroupI && !to->changed) {flipGroup(to); to->changed = true;}
      }
      if (order == 2) {
         if (fromGroupII && toGroupII && !from->changed) {flipGroup(from); from->changed = true;}
         else if (fromGroupII && toGroupII && !to->changed) {flipGroup(to); to->changed = true;}
         else if (fromGroupI && toGroupI && !from->changed) {flipGroup(from); from->changed = true;}
         else if (fromGroupI && toGroupI && !to->changed) {flipGroup(to); to->changed = true;}
      }   
   }
   
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      mol->atoms[i]->changed = false;
   }
   }
   
   //Now lets check for a n bonded to a cc a cd 
   //Note this is a hack that should probably be fixed in the atom typeing routines above
   //Why is the nitrogen types as a n in a ring??????
//   for (int i=0; i<mol->bonds.size(); i++) {
 
//   }
}

bool dtGaff::isGroupI(atomPtr atm) {
   if (atm->type == "ce") return true;
   if (atm->type == "cc") return true;
   if (atm->type == "ne") return true;
   if (atm->type == "nc") return true;
   if (atm->type == "pe") return true;
   if (atm->type == "pc") return true;
   if (atm->type == "cp") return true;
   return false;
}
   
bool dtGaff::isGroupII(atomPtr atm) {
   if (atm->type == "cf") return true;
   if (atm->type == "cd") return true;
   if (atm->type == "nf") return true;
   if (atm->type == "nd") return true;
   if (atm->type == "pf") return true;
   if (atm->type == "pd") return true;
   if (atm->type == "cq") return true;
   return false;
}

void dtGaff::flipGroup(atomPtr atm) {
   if (atm->type == "ce") {atm->type = "cf"; return;}
   if (atm->type == "cc") {atm->type = "cd"; return;}
   if (atm->type == "ne") {atm->type = "nf"; return;}
   if (atm->type == "nc") {atm->type = "nd"; return;}
   if (atm->type == "pe") {atm->type = "pf"; return;}
   if (atm->type == "pc") {atm->type = "pd"; return;}
   if (atm->type == "cp") {atm->type = "cq"; return;}
   
   if (atm->type == "cf") {atm->type = "ce"; return;}
   if (atm->type == "cd") {atm->type = "cc"; return;}
   if (atm->type == "nf") {atm->type = "ne"; return;}
   if (atm->type == "nd") {atm->type = "nc"; return;}
   if (atm->type == "pf") {atm->type = "pe"; return;}
   if (atm->type == "pd") {atm->type = "pc"; return;}
   if (atm->type == "cq") {atm->type = "cp"; return;}
}


/** \brief This function returns a complex->basic type converter
*    
*    This function returns a map that can be used to convert a complex
*    GAFF type ex( cc(cd) ne(nf), etc) to its basic type equivalent
*/
void dtGaff::getBasicTypeMap(map<string, string> &basicMap) {
   //THIS SECTION MAPS BASIC TYPES TO BASIC TYPES
   basicMap.clear();
   //basicMap["c"]  = "c";
   basicMap["c"] = "c2";
   basicMap["c1"] = "c1";
   basicMap["c2"] = "c2";
   basicMap["c3"] = "c3";
   basicMap["ca"] = "ca";

   basicMap["n"]  = "n";  
   basicMap["n1"] = "n1";
   basicMap["n2"] = "n2";
   basicMap["n3"] = "n3";

   basicMap["n4"] = "n3";
   basicMap["na"] = "n2";
   basicMap["nh"] = "nh";
   basicMap["no"] = "no";
   basicMap["nb"] = "nb";

   basicMap["o"]  = "o";
   basicMap["oh"] = "oh";
   basicMap["os"] = "os";

   basicMap["s2"] = "s2";
   basicMap["sh"] = "sh";
   basicMap["s4"] = "s4";
   basicMap["s6"] = "s6";
   basicMap["ss"] = "ss";

   basicMap["p2"] = "p2";
   basicMap["p3"] = "p3";
   basicMap["p4"] = "p4";
   basicMap["p5"] = "p5";

   basicMap["f"]  = "f";
   basicMap["cl"] = "cl";
   basicMap["br"] = "br";
   basicMap["i"]  = "i";

   basicMap["B"] = "B";
   basicMap["Au"] = "Au";
   basicMap["Si"] = "Si";

   //NOW START THE SECTION FOR SPECIAL TYPES MAPPING BACK TO BASIC TYPES
   basicMap["cg"] = "c1";
   basicMap["ch"] = "c1";
	
   basicMap["cc"] = "c2";
   basicMap["cd"] = "c2";
   basicMap["ce"] = "c2";
   basicMap["cf"] = "c2";
	
   basicMap["cp"] = "ca";
   basicMap["cq"] = "ca";
	
   basicMap["cu"] = "c2";
   basicMap["cv"] = "c2";
   basicMap["cx"] = "c3";
   basicMap["cy"] = "c3";

   basicMap["nc"] = "n2";
   basicMap["nd"] = "n2";
   basicMap["ne"] = "n2";
   basicMap["nf"] = "n2";

   basicMap["pc"] = "p2";
   basicMap["pd"] = "p2";
   basicMap["pe"] = "p2";
   basicMap["pf"] = "p2";

   basicMap["px"] = "p3";
   basicMap["py"] = "p3";

   basicMap["sx"] = "s4";
   basicMap["sy"] = "s6";
}


void dtGaff::getBasicTypeMap2(map<string, string> &basicMap) {
   //THIS SECTION MAPS BASIC TYPES TO BASIC TYPES
   basicMap.clear();
   basicMap["c"]  = "c";
   basicMap["c1"] = "c1";
   basicMap["c2"] = "c2";
   basicMap["c3"] = "c3";
   basicMap["ca"] = "ca";

   basicMap["n"]  = "n";  
   basicMap["n1"] = "n1";
   basicMap["n2"] = "n2";
   basicMap["n3"] = "n3";
   basicMap["n4"] = "n4";
   basicMap["na"] = "na";
   basicMap["nh"] = "nh";
   basicMap["no"] = "no";
   basicMap["nb"] = "nb";

   basicMap["o"]  = "o";
   basicMap["oh"] = "oh";
   basicMap["os"] = "os";

   basicMap["s2"] = "s2";
   basicMap["sh"] = "sh";
   basicMap["s4"] = "s4";
   basicMap["s6"] = "s6";
   basicMap["ss"] = "ss";

   basicMap["p2"] = "p2";
   basicMap["p3"] = "p3";
   basicMap["p4"] = "p4";
   basicMap["p5"] = "p5";

   basicMap["f"]  = "f";
   basicMap["cl"] = "cl";
   basicMap["br"] = "br";
   basicMap["i"]  = "i";

   basicMap["B"] = "B";
   basicMap["Au"] = "Au";
   basicMap["Si"] = "Si";

   //NOW START THE SECTION FOR SPECIAL TYPES MAPPING BACK TO BASIC TYPES
   basicMap["cg"] = "c1";
   basicMap["ch"] = "c1";
	
   basicMap["cc"] = "c2";
   basicMap["cd"] = "c2";
   basicMap["ce"] = "c2";
   basicMap["cf"] = "c2";
	
   basicMap["cp"] = "ca";
   basicMap["cq"] = "ca";
	
   basicMap["cu"] = "c2";
   basicMap["cv"] = "c2";
   basicMap["cx"] = "c3";
   basicMap["cy"] = "c3";

   basicMap["nc"] = "n2";
   basicMap["nd"] = "n2";
   basicMap["ne"] = "n2";
   basicMap["nf"] = "n2";

   basicMap["pc"] = "p2";
   basicMap["pd"] = "p2";
   basicMap["pe"] = "p2";
   basicMap["pf"] = "p2";

   basicMap["px"] = "p3";
   basicMap["py"] = "p3";

   basicMap["sx"] = "s4";
   basicMap["sy"] = "s6";
}

} //end namespace

