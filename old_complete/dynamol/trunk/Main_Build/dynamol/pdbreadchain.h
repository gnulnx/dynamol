/***************************************************************************
                          pdbreadchain.h  -  description
                             -------------------
    begin                : Fri May 2 2003
    copyright            : (C) 2003 by John Furr
    email                : john.furr@albmolecular.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, ||     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PDBREADCHAIN_H
#define PDBREADCHAIN_H

#include "pdbreadfrag.h"

/**
  *@author John Furr
  */

class pdbReadChain {
public: 
	pdbReadChain();
	~pdbReadChain();

	void printStats();
  void    setName(string name);
  string  getName();
  vector<pdbReadFrag *> chain;
  vector<string>		hetAtoms;

private:
  string name;
};

#endif





































