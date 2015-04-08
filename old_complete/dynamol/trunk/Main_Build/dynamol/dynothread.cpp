/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "dynothread.h"
#include "molview.h"

//Standard Library Includes
#include <iostream>
using std::cout;
using std::endl;


int dynoThread::count = 0;
molView *dynoThread::viewer = NULL;

/** The run time type infor....
dynoThread = 1;
chargeThread = 2;
energyThread = 3;
*/
int dynoThread::rtti() {return 1;}

dynoThread::dynoThread(QWidget *parent)
:QWidget(parent),
QThread()
{
   if (viewer == NULL) {
      cout <<"dynoThread::dynoThread MolView is NULL!!!!!!!!" << endl;
   }
   name = "dynoThread";
   threadNum = count;
   count++;
   stop = false;

   errorMsg = "";
}

void dynoThread::setMolView(molView *view)
{  viewer = view; }

int dynoThread::getNum() {return threadNum;}

string dynoThread::getErrorMsg()
{ return errorMsg; }

dynoThread::~dynoThread()
{
}

QString dynoThread::getName() {
   return "DynoThread";
}

void dynoThread::run() {
   emit threadStarted(this);
}

void dynoThread::setName(QString name) {this->name = name;};

void dynoThread::stopThread() {this->stop == true;}
void dynoThread::setSemaphore(QSemaphore *wait_sem) {this->wait_sem = wait_sem;}

void dynoThread::displayErrors() {
   cout <<"dynoThread::Errors:  "<< errorMsg << endl;
   vector<string> Error;
   string e = "";
   for (int i=0; i<errorMsg.size(); i++) { 
      if (errorMsg[i] == '|') {
         Error.push_back(e);
         e = "";
      } else {
         e += errorMsg[i];
      }
   }
   Error.push_back(e);

   viewer->infoText.clear();
   viewer->infoText = Error;
}



































