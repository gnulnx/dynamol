/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "scriptbondlist.h"
#include "scriptbond.h"
#include <iostream>
#include <qmessagebox.h>
using namespace std;

scriptbondlist::scriptbondlist(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
}


scriptbondlist::~scriptbondlist()
{
}

int scriptbondlist::size() {return bondList.size();}


scriptbond *scriptbondlist::front() { return bondList.front(); }
scriptbond *scriptbondlist::back() { return bondList.back();};
void scriptbondlist::push_back( scriptbond *bd ) {bondList.push_back(bd);}
void scriptbondlist::push_front( scriptbond *bd ) {bondList.push_front(bd);}
    
scriptbond *scriptbondlist::pop_back() {
   scriptbond *bd = bondList.back();
   bondList.pop_back();
   return bd;
}
scriptbond *scriptbondlist::pop_front() {
   scriptbond *bd = bondList.front();
   bondList.pop_front();
   return bd;
}

scriptbond *scriptbondlist::getBond(int index) {
   if (index < bondList.size()) {
	return bondList[index];
   } else {
	////////////cout <<"Mol List is size zero!"<<endl; 
        QMessageBox::critical(0, "Index Error", "Trying to index out of range element"); 
      	return NULL;
   }
}























