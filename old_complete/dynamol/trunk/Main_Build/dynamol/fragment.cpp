/***************************************************************************
                          fragment.cpp  -  description
                             -------------------
    begin                : Sun Feb 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/
#include "pdbreadfrag.h"
#include "fragment.h"
#include "chain.h"
#include "protein.h"
#include <deque>
#include "atom.h"
#include "bond.h"

using namespace std;
int fragment::fragCreate = 0;
int fragment::fragDestroy = 0;

int fragment::rtti()          {return 12;};
fragment::fragment()
: molecule()
{
  fragCreate++;
  fragType = "default";
  type = TURN;
  
  nTer = cTer = false;
}
fragment::~fragment(){
  
}

fragment &fragment::operator=(const fragment &frag) {
   if (this == &frag) return *this;
   
   /** This variable will tell us if the atoms are ordered
   *   If they are then we can speed up the addBond process
   *   We also order the atom numbers
   *   The original atom numbers are re-set at the end
   */
   const int size = frag.atoms.size();
   //int *nums = new int[size];
   for (int i=0; i<frag.atoms.size(); i++) {
      atom *atm = frag.atoms[i];
      //nums[i] = frag.atoms[i]->getNum();
      //atm->setNum(i+1);
      float *cd = atm->fCoords;
      int AN = atm->getAtomicNum();
      //////////////cout <<"atm->getNum(): " << atm->getNum() << endl;
      addAtom(atm->getNum() , atm->getSym(), cd[0], cd[1], cd[2], AN);
      atm->setCharge( atm->getCharge() );
   }
   //////////////cout <<"Now here in molecule::operaot="<<endl;
   /** This section adds new bonds 
   *   This also takes care of setting the atom->atoms
   */
   for (int i=0; i<frag.bonds.size(); i++) {
      bond *bd = frag.bonds[i];
      int fNum = bd->fromAtom()->getNum();
      int tNum = bd->toAtom()->getNum();
      ////////////cout <<"bd->getNum() : " << bd->getNum() << setw(12) << bd->fromAtom()->getNum() << setw(12) << bd->toAtom()->getNum() << endl;
      bond *newBond = addBond(bd->getNum(), fNum, tNum, bd->getOrder());
      if (newBond) newBond->defInc = bd->defInc;
   }
   
   /** Now lets reassign the atom's numbers */
   /*
   for (int i=0; i<frag.atoms.size(); i++) {
      atom *atm = frag.atoms[i];
      atm->setNum(nums[i]);
   }
   */
   
   /** Now lets set the molecules name */
   setName(frag.name);
}


vector<atom *>  *fragment::getAtomList()  {return &atoms;};
vector<bond *>  *fragment::getBondList()  {return &bonds;};
string        fragment::getType()       {return fragType;};
int  fragment::getFragNum()                        {return fragNum;};
void fragment::setFragNum(int fragNum)             {this->fragNum = fragNum;};

atom *fragment::addNewAtom(int num, string type, double x, double y, double z, int atomicNum) {
    molecule *prot, *ch;
    prot = ch = NULL;
    if (getParent() != NULL) 
	ch = dynamic_cast<molecule *>(getParent());
    if (ch->getParent() != NULL) 
	prot = dynamic_cast<molecule *>(ch->getParent() );

    atom *atm = NULL;
    int numOfAtoms = 0;
    if (prot != NULL) {
        numOfAtoms = prot->atoms.size();
        atm = prot->addAtom(numOfAtoms, type, x, y, z, atomicNum);
        ch->atoms.push_back(atm);
        this->atoms.push_back(atm);
    }
    else if (prot == NULL && ch != NULL) {
        numOfAtoms = ch->atoms.size();
        atm = ch->addAtom(numOfAtoms, type, x, y, z, atomicNum);
        this->atoms.push_back(atm);
    }
    else if (ch == NULL && prot == NULL) {
        numOfAtoms = atoms.size();
        atm = addAtom(numOfAtoms, type, x, y, z, atomicNum);
    }  

    QString atomName = atm->getSym().c_str();
    molListViewItem  *atomItem = new molListViewItem(getItem(), atomName, atm);
    atm->setItem(atomItem);
    return atm;
}

bond *fragment::addNewBond(atom *from, atom *to, int order) {
    //////////////cout << "fragment::addNewBond" << endl;
    //////////////cout << "fragment::addNewAtom" << endl;
    molecule *prot, *ch;
    prot = ch = NULL;
    if (getParent() != NULL) ch = dynamic_cast<molecule *>(getParent());
    if (ch->getParent() != NULL) prot = dynamic_cast<molecule *>(ch->getParent() );

    
    int bdNum = 0;
	bond *bd = NULL;
    if (prot != NULL) {
      bdNum = prot->bonds.size();
      bd = new bond(bdNum, from, to, order);
      prot->bonds.push_back(bd);
      ch->bonds.push_back(bd);
      bonds.push_back(bd);   
    }
    else
    if (prot == NULL && ch != NULL) {
      bdNum = ch->bonds.size();
      bd = new bond(bdNum, from, to, order);
      ch->bonds.push_back(bd);
      bonds.push_back(bd);
    }
    else
    if (prot == NULL && ch == NULL) {
      bdNum = bonds.size();
      bd = new bond(bdNum, from, to, order);
      bonds.push_back(bd);
    }

	return bd;
}





































