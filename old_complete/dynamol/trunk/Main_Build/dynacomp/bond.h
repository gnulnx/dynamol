/********************************************
 *   Copyright (C) 2004 by Dynamol          *
 *   jjohn.furr@dynamol.com                 *
 ********************************************/
#ifndef DYNACOMPBOND_H
#define DYNACOMPBOND_H

#include <string>
using std::string;

//Dynamol Type Library Includes
#include "atom.h"

namespace dynacomp {

class molecule;

	
class bond   {	
friend class molecule;
friend class atom;
friend class AM1_BCC;
public:
   bond(int num, atom *from, atom *to,  int order);
   ~bond();

   /** \brief Bond Charge Correction variable
   *
   *  This variable is used in the AM1-BCC charge routines
   */
   string bcc;
   
   /** \brief Get the bond order
   *
   */
   inline int getOrder()
   { return order; }

   inline int getNum()
   { return num; }

   //inline int bond::fromNum()
   inline int fromNum()
   { return from->getNum(); }

   //inline int bond::toNum()
   inline int toNum()
   { return to->getNum(); }

   
   inline atom *fromAtom()
   { return from; }
 
   inline atom *toAtom()
   { return to; }
   
   inline molecule *getParent()
   { return parent; }

   inline void setParent( molecule *mol)
   { this->parent = mol; }

   atom *from, *to;
   float refLen;
   float K;
   int order;
   //Conformatio stuff
   int defInc;
   bool rotable;
protected:   
   int num;
   molecule *parent;
};

}
#endif



























