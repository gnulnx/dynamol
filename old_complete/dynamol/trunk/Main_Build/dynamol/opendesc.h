/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef OPENDESC_H
#define OPENDESC_H

#include <set>
#include <vector>
using namespace std;

#include <qstring.h>
//Include from the descriptor project
#include "../descriptors/switchboard.h"

/**
@author jfurr
*/


class molecule;
class dynaScript;

class OpenDesc{
public:
   /** Constructor will pop up the descSel dialog box.  The results of the dialog selction
   *   will be stored in the set<QString> descSet variable
   */
   OpenDesc(dynaScript *ide, vector<QString> &descVec);

   ~OpenDesc();
   
   /** This function is resposible for calculating all of the descripts for the molecule
   *   The descripts are stored as propValue pairs in the molecule
   */
   void runMol( molecule *mol );  

private:
   
   /** The descSet holds the names of the class:function descriptor pairs
   *   For instance in the Count Descriptor class.  You would see 
   *   <pre>
   *   Counts:nCarbon
   *   Counts:nNitrogen
   *   etc..
   *   <pre>
   *
   *   A set is used to make sure that no duplicates are inserted.
   */
   set<QString> descSet;

   /** This variable is a pointer to the dynScript scripting engine.
   */
   dynaScript *ide;
     
  /** This is the switch board from the descriptor library */
  switchBoard s; 
   
};

#endif








