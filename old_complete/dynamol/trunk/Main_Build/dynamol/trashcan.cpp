/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "trashcan.h"
#include "object.h"
#include "atom.h"
#include "bond.h"
#include "molecule.h"
#include "fragment.h"
#include "chain.h"
#include "protein.h"
#include <algorithm>
#include <iterator>
#include <time.h>
using namespace std;

typedef set<atom *>::iterator atomSetIter;
typedef set<bond *>::iterator bondSetIter;
typedef set<molecule *>::iterator molSetIter;
typedef set<fragment *>::iterator fragSetIter;
typedef set<chain *>::iterator chainSetIter;
typedef set<protein *>::iterator protSetIter;

TrashCan::TrashCan() {};

TrashCan::TrashCan(vector<Object *> &objectVector)
{
   for (int i=0; i<objectVector.size(); i++) {
      if (objectVector[i]->rtti() == 9)
         bondSet.insert(dynamic_cast<bond *>(objectVector[i]));
      else if (objectVector[i]->rtti() == 10)
         atomSet.insert(dynamic_cast<atom *>(objectVector[i]));
      else if (objectVector[i]->rtti() == 11) 
         molSet.insert(dynamic_cast<molecule *>(objectVector[i]));
      else if (objectVector[i]->rtti() == 12) 
         fragSet.insert(dynamic_cast<fragment *>(objectVector[i]));
      else if (objectVector[i]->rtti() == 13) 
         chainSet.insert(dynamic_cast<chain *>(objectVector[i]));
      else if (objectVector[i]->rtti() == 14) { 
         protSet.insert(dynamic_cast<protein *>(objectVector[i]));      
         protein *p = dynamic_cast<protein *>(objectVector[i]);
      }
   }

   setToCheck = NULL;
}

TrashCan::TrashCan(atom *atm) {
   atomSet.insert(atm);
}

TrashCan::TrashCan(vector<atom *> &atomVector) {
   for (int i=0; i<atomVector.size(); i++) {
      atomSet.insert(atomVector[i]);
   }
   setToCheck = NULL;
}

TrashCan::TrashCan(vector<fragment *> &fragVector) {
   for (int i=0; i<fragVector.size(); i++) {
      fragSet.insert(fragVector[i]);
   }
   for (int i=0; i<fragVector.size(); i++) {
      fragment *frag = fragVector[i];
      fragSet.insert(frag);
     
      chain *ch = dynamic_cast<chain *>(frag->getParent());
      protein *prot;
      if (ch) {
	prot = dynamic_cast<protein *>(ch->getParent());	
	fragChainMap[frag] = ch;
      }
      if (prot) {
	fragProtMap[frag] = prot;
      }
   }
   setToCheck = NULL;
}

TrashCan::~TrashCan()
{
   //empty();
}

void TrashCan::setCheck(set<molecule *> &setToCheck) {
   this->setToCheck = &setToCheck;
}

void TrashCan::empty() {
   deleteAtoms();
   deleteMols();
   deleteFrags();
   deleteChains();
   deleteProts();
}

void TrashCan::empty(vector<atom *> &atomVector) {
   for (int i=0; i<atomVector.size(); i++) {
      atomSet.insert(atomVector[i]);
   }
   setToCheck = NULL;
   empty();
}

void TrashCan::deleteAtoms() {
   if (atomSet.size() == 0)
      return;
   vector<atom *> aVec(atomSet.begin(), atomSet.end());
   /** First we create several sets to fully encompass all of the 
   *   parents/grandparents of the atom
   */
   set<bond *> bondSet;
   set<molecule *> parentSet;
   set<fragment *> fragSet;
   set<chain *> chainSet;
   set<protein *> protSet;
 
   atomSetIter aI = atomSet.begin();
   for (aI; aI != atomSet.end(); aI++) {
      atom *atm = *aI;
      molecule *mol = dynamic_cast<molecule *>(atm->getParent());
      parentSet.insert(mol);
      if (mol->rtti() == 12)
         fragSet.insert(dynamic_cast<fragment *>(mol));
      while (mol->getParent()) {
         mol = dynamic_cast<molecule *>(mol->getParent());
         if (mol->rtti() == 12) 
	    fragSet.insert(dynamic_cast<fragment *>(mol));
         if (mol->rtti() == 13)
            chainSet.insert(dynamic_cast<chain *>(mol));
         if (mol->rtti() == 14)
            protSet.insert(dynamic_cast<protein *>(mol));

         parentSet.insert(mol);
	 
      }
   }
   time_t t1 = time(NULL);
   aI = atomSet.begin();
   for (aI; aI != atomSet.end(); aI++) {
      atom *atm = *aI;
      molecule *mol = dynamic_cast<molecule *>(atm->lastParent());
      /** Mol should not point to the last parent */
      for (int i=0; i<atm->atoms.size(); i++) {
         bond *bd = mol->getBond(atm, atm->atoms[i]);
         if (bd)
            bondSet.insert(bd);
      }
   } 
   time_t t2 = time(NULL);
   vector<bond *> bVec(bondSet.begin(), bondSet.end());

   molSetIter mI = parentSet.begin();
   for (mI; mI != parentSet.end(); mI++) {
      molecule *mol = *mI;
      set<bond *> mBSet(mol->bonds.begin(), mol->bonds.end());
      set<atom *> mASet(mol->atoms.begin(), mol->atoms.end());
	
      for (int i=0; i<aVec.size(); i++) {
         mASet.erase(aVec[i]);
      }

      for (int i=0; i<bVec.size(); i++) {
	      mBSet.erase(bVec[i]);
      }

      vector<atom *> newAVec(mASet.begin(), mASet.end());
      vector<bond *> newBVec(mBSet.begin(), mBSet.end());

      mol->atoms = newAVec;
      mol->bonds = newBVec;	
   }
   
   /** Now we will remove the molListViewItems from each atom
   *   We also go ahead and delete the atom at this point
   */
   //int test = 0;
   //cin >> test;
   for (int i=0; i<aVec.size(); i++) {
      atom *atm = aVec[i];
      for (int j=0; j<atm->atoms.size(); j++) {
         atom *tmp = atm->atoms[j];
         for (int k=0; k<tmp->atoms.size(); k++) {
            if (tmp->atoms[k] == atm) {
               tmp->atoms.erase(tmp->atoms.begin()+k);
               break;
            }
         }
      }
      //delete aVec[i]->item;
      delete aVec[i];
   }

   /** Now we delete the bonds as well */
   for (int i=0; i<bVec.size(); i++) {
     delete bVec[i];
   }
  
   /** Now perform a fragment check */
   fragSetIter fI = fragSet.begin();
   for (fI; fI != fragSet.end(); fI++) {
      fragment *frag = *fI;
      if (frag->atoms.size() == 0) {
         this->fragSet.insert(frag); 
      } 
   } 
   atomSet.clear();


   molSetIter mSet = parentSet.begin();
   for (mSet; mSet != parentSet.end(); mSet++) {
      molecule *mol = *mSet;
      for (int i=0; i<mol->atoms.size(); i++) {
         atom *atm = mol->atoms[i];
         atm->setNum(i+1); 
      }
      if (mol->atoms.size() == 0 && mol->rtti() == 11 )
         molSet.insert(mol);
         //delete mol;
   }     

    
}

void TrashCan::deleteMols() {
   if (molSet.size() == 0)
      return;
   vector<molecule *> mols(molSet.begin(), molSet.end());
   for (int i=0; i<mols.size(); i++) {
      molecule *m = mols[i];
      for (int i=0; i<m->atoms.size(); i++)
         delete m->atoms[i];
      for (int i=0; i<m->bonds.size(); i++) 
         delete m->bonds[i];
      for (int i=0; i<m->angles.size(); i++) 
         delete m->angles[i];
      for (int i=0; i<m->torsions.size(); i++) 
         delete m->torsions[i];
      for (int i=0; i<m->nonBonds.size(); i++)  
         delete m->nonBonds[i];
         
      //if (m->item)
      //   delete m->item;
       
      if (setToCheck)
         setToCheck->erase(m);

      delete m;
  }
  molSet.clear();
}


void TrashCan::deleteFrags() {
   if (fragSet.size() == 0)
      return;
   fragSetIter fIter;
   /** Gather all of the parents/grandparents
   *   You will need to remove the atoms from 
   *   Both parents and grandParents
   */
   set<molecule *> parents;
   set<chain *> cSet;
   set<protein *> pSet;
   fIter = fragSet.begin();
   while (fIter != fragSet.end()) {
      fragment *frag = *fIter;
      Object *parent = frag->getParent();
      Object *last = frag->lastParent();
      if (parent) {
	 chain *ch = dynamic_cast<chain *>(parent);
         parents.insert(ch);
         cSet.insert(ch);
      }
      if (last) {
         if (last->rtti() == 13) {
            chain *ch = dynamic_cast<chain *>(last); 
            parents.insert(ch);
            cSet.insert(ch);	
         } else
         if (last->rtti() == 14) {
            protein *pr = dynamic_cast<protein *>(last);
	    parents.insert(pr);
	    pSet.insert(pr);
         }
      }
      fIter++;
   }

   protSetIter pI = pSet.begin(); 
   chainSetIter cI = cSet.begin();
   /** Remove the frags from the various chains */
   while (cI != cSet.end()) {
      chain *ch = *cI;
      set<fragment *> fSet(ch->frags.begin(), ch->frags.end());
      fragSetIter fI = fragSet.begin();
      for (fI; fI != fragSet.end(); fI++) {
         fragment *f = *fI;
         if (setToCheck)
	    setToCheck->erase(f);
	 fSet.erase(f);
      }
      deque<fragment *> fVec(fSet.begin(), fSet.end());
      ch->frags = fVec;
      cI++;   
   }      

   /** Construct a list of bonds to delete
   *   This has to be done this way because chains/proteins
   *   May contain bonds the individual fragments do not
   */
   set<bond *> bSet;
   fragSetIter fI = fragSet.begin();
   for (fI; fI != fragSet.end(); fI++) {
      fragment *frag = *fI;
      molecule *mol = dynamic_cast<molecule *>(frag->lastParent());
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         for (int j=0; j<atm->atoms.size(); j++) {
            bond *bd = mol->getBond(atm, atm->atoms[j]);
            if (bd)
               bSet.insert(bd);
         }
      }
   }
   
   /** Now we need to move through the parent list and remove
   *   all the atoms and bonds
   */
   molSetIter mI = parents.begin();
   for (mI; mI != parents.end(); mI++) {
      molecule *mol = *mI;
      set<atom *> mASet(mol->atoms.begin(), mol->atoms.end());
      set<bond *> mBSet(mol->bonds.begin(), mol->bonds.end());

      fI = fragSet.begin();
      for (fI; fI != fragSet.end(); fI++) {
         fragment *frag = *fI;
         for (int i=0; i<frag->atoms.size(); i++) {
	    mASet.erase(frag->atoms[i]);
         }

   	 bondSetIter bI = bSet.begin();
	 for (bI; bI != bSet.end(); bI++) {
	    bond *bd = *bI;
            mBSet.erase(bd);
	 }
      }
      vector<atom *> mAVec(mASet.begin(), mASet.end());
      vector<bond *> mBVec(mBSet.begin(), mBSet.end()); 
      mol->atoms = mAVec;
      mol->bonds = mBVec;
   }

   vector<fragment *> fVec(fragSet.begin(), fragSet.end());
   for (int j=0; j<fVec.size(); j++) {
      fragment *frag = fVec[j];
      for (int i=0; i<frag->atoms.size(); i++) {
         delete frag->atoms[i];
      }
      //delete frag->item;
      delete frag;
   }

   vector<bond *> bVec(bSet.begin(), bSet.end());
   for (int i=0; i<bVec.size(); i++) {
      bond *bd = bVec[i];
      bSet.erase(bd);
      delete bd;
   }
   fragSet.clear();

   vector<chain *> cVec(cSet.begin(), cSet.end());
   for (int i=0; i<cVec.size(); i++) {
      chain *ch = cVec[i];
      if (ch->frags.size() == 0) {
          chainSet.insert(ch);
      }
   }
   
   //Now renumber all the atoms;
   molSetIter mSet = parents.begin();
   for (mSet; mSet != parents.end(); mSet++) {
      molecule *mol = *mSet;
      for (int i=0; i<mol->atoms.size(); i++) {
         atom *atm = mol->atoms[i];
         atm->setNum(i+1);
      }
   }

}

void TrashCan::deleteChains() {
   if (chainSet.size() == 0)
   	return;
   /** Gather all of the proteins into a set<protein> */
   protein *prot;
   chainSetIter cI = chainSet.begin();
   set<protein *> pSet;
   for (cI; cI != chainSet.end(); cI++) {
   	chain *ch = *cI;
	protein *p = dynamic_cast<protein *>(ch->getParent());
	pSet.insert(p);
   }
   /** Loop over the set of proteins */
   protSetIter pI = pSet.begin();
   for (pI; pI != pSet.end(); pI++) {
   	protein *p = *pI;
	
	/** Make sets of the atoms, bonds, and chains vectors
	*   This is to make removal operations much faster
	*   Notice that you are removing them from the protein
	*   vectors not the chains.  You will simply delete them 
 	*   from the chain.
	*/
	set<atom *> aSet(p->atoms.begin(), p->atoms.end());
	set<bond *> bSet(p->bonds.begin(), p->bonds.end());
	set<chain *> cSet(p->chains.begin(), p->chains.end());
	
	/** Remove/Delete the atoms and bonds in the  */
	cI = chainSet.begin();
	for (cI; cI != chainSet.end(); cI++) {
   	   chain *ch = *cI;
	   for (int i=0; i<ch->atoms.size(); i++) {
	   	aSet.erase(ch->atoms[i]);
                delete ch->atoms[i];
	   }
	   
	   for (int i=0; i<ch->bonds.size(); i++) {
	   	bSet.erase(ch->bonds[i]);
		delete ch->bonds[i];
	   }
	   
	   /** removce the chain from the proteins chains set */
	   cSet.erase(ch);
	   /** Delete the chain->item so that the listView updates */
	   //delete ch->item;
   	}
	
	/** Create vectors from the protein sets */
	vector<atom *> aVec(aSet.begin(), aSet.end());
	vector<bond *> bVec(bSet.begin(), bSet.end());
	deque<chain *> cVec(cSet.begin(), cSet.end());

	/** Reassing the protein vectors to the new vectors */
	p->atoms = aVec;
	p->bonds = bVec;
	p->chains = cVec;	
   }
   /** For each chain in the chain delete all frags */
   cI = chainSet.begin();
   for (cI; cI != chainSet.end(); cI++) {
   	chain *ch = *cI;
	for (int i=0; i<ch->frags.size(); i++) {
	   setToCheck->erase(ch->frags[i]);
	   delete ch->frags[i];
	}
	setToCheck->erase(ch);
	delete ch;
   }
   /** Now loop through the protein set one more time
   *   Check to see if the protein contains any chains
   *   if it doesn't then you need to delete the protein 
   *   as well as the protein->item
   */
   pI = pSet.begin();
   for (pI; pI != pSet.end(); pI++) {
      protein *p = *pI;
      if (p->atoms.size() == 0) {
	 protSet.erase(p);
	 setToCheck->erase(p);
	 //delete p->item;
	 delete p;
      }
   }
   /** Clear the chainSet so that next time deleteChains is called it
   *  promptly returns
   */
   chainSet.clear();
   
   /** renumber the protein */
   pI = pSet.begin();
   for (pI; pI != pSet.end(); pI++) {
      protein *p = *pI;
      for (int i=0; i<p->atoms.size(); i++) {
         atom *atm = p->atoms[i];
         atm->setNum(i+1);
      }
   }
}

void TrashCan::deleteProts() {
   if (protSet.size() == 0)
   	return;
     
   vector<protein *> prots(protSet.begin(), protSet.end());
   for (int i=0; i<prots.size(); i++) {
      protein *p = prots[i];
      for (int i=0; i<p->atoms.size(); i++)
         delete p->atoms[i];
      for (int i=0; i<p->bonds.size(); i++)
         delete p->bonds[i];
      for (int i=0; i<p->angles.size(); i++)
         delete p->angles[i];
      for (int i=0; i<p->torsions.size(); i++)
         delete p->torsions[i];
      for (int i=0; i<p->nonBonds.size(); i++) {
         delete p->nonBonds[i];
      }

      for (int j=0; j<p->chains.size(); j++) {
         chain *c = p->chains[j];
         for (int k=0; k<c->frags.size(); k++) {
	    setToCheck->erase(c->frags[k]);
            delete c->frags[k];
         }
	 setToCheck->erase(c);
         delete c;
      }
      setToCheck->erase(p); 
      //delete p->item;
      delete p;
   }
  
   protSet.clear();
}


















