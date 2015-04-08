/***************************************************************************
                          protein.h  -  description
                             -------------------
    begin                : Sun Feb 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef PROTEIN_H
#define PROTEIN_H

#include "molecule.h"

#include <vector>
#include <deque>
#include <string>
//#include <set>

using namespace std;

class chain;
/**
  *@author John Furr
  */

/** Class protien is treated as a container class as well.  It is composed of chains && other structures.
    It did not make sense to inherit from class fragment || class chain.  Since a protein is really
    just a collection of chains which are themselves a collection of fragments which are in essence
    special molecules.  Anyway that is my current reasoning...wheather it is right || wrong it is time to make
    a desicion && go with it.
*/
class protein :public molecule {
  friend class pdbReader;
public:
   static int protCreate;
   static int protDestroy;
   static bool lock;
   protein();
   virtual ~protein();
   virtual protein &operator=(const protein &prot);

  virtual int numOfChains();
 
	/**	This one will most likely be used when you just want to build a random protein chain.
	*/
  void    addChain(chain *ch);

	/** This is used when reading in pdb files
	*/
	void		addChain(chain *ch, vector<string> hetAtoms, vector<string> conectVec);

  /** Renumbers the bonds in numerical order...Note I don't think that they
      Will coorespond to the pdb bonds any longer
  */
  void    reNumberBonds();

  /** This function check for metal atoms and creates a special metal chain for the */
  void metalCheck();
  
  /** This is resposible for removing the chain from the proteins
   chain deque
  */
  void removeChain(chain *ch);

  
  void			addConect(chain *ch, vector<string> conect);
  void			addConect(fragment *ch, vector<string> conect);  //Might be temporary

  void      setChainsToBegin();
  chain     *getCurrentChain();
  int      nextChain();         //return 1 on success...0 on fail
  int      prevChain();         //return 1 on succes ....0 on fail


  virtual void setSelected(bool state, bool children);
  virtual int  rtti(); //returns 14;

  deque<chain *> chains;
  //set<chain *> chains;
private:
  deque<chain *>::iterator currentChain;
  
  void 	protein::appendAtom(int &num, string &name, double &X, double &Y, double &Z, float &temp, chain *ch);
  void 	protein::appendAtom(int &num, string &name, double &X, double &Y, double &Z, float &temp, fragment *ch);

protected:
  

};

#endif





































