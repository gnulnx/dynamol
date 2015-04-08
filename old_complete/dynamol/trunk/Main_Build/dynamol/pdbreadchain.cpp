/***************************************************************************
                          pdbreadchain.cpp  -  description
                             -------------------
    begin                : Fri May 2 2003
    copyright            : (C) 2003 by Dynamol
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "pdbreadchain.h"

pdbReadChain::pdbReadChain(){
}
pdbReadChain::~pdbReadChain(){
}

//Not to sure about the code here...well actually I am not sure about the cide==
void    pdbReadChain::setName(string name)    {
  //if (name != " ") {
    this->name = name;
  //}
  //////////////cout <<"Name was set to: " << name << endl;
};
string  pdbReadChain::getName()               {return this->name;};

void pdbReadChain::printStats() {
	////////////cout <<"-------------------New Chain--------------------------"<<endl;
		////////////cout <<"chain.size(): " << chain.size()<<endl;
		////////////cout <<"hetAtoms.size(): " << hetAtoms.size() << endl;
		for (unsigned int i=0; i< chain.size(); i++) {
			 chain[i]->printStats();
		}

		////////////cout <<"-----------------Chain hetAtoms------------------------"<<hetAtoms.size()<<endl;
		for (unsigned int j=0; j<hetAtoms.size(); j++) {
				////////////cout <<hetAtoms[j] << endl;
		}
}







































