/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <qobject.h>
#include <iostream>
#include <vector>

using namespace std;

class XmodelView;
class molChangeEvent;
class dynoThread;


/**
@author jfurr
*/
class jobManager : public QObject
{
Q_OBJECT
public:
   jobManager(QObject *parent = 0, const char *name = 0);

   ~jobManager();
    
   bool eventFilter(QObject *obj, QEvent *e);

   void setXmodelView(XmodelView *view);
   
   /** This function returns true if it is able to register the job in the previous job database */
   bool registerJob(dynoThread *thread); 
   
   /** Returns true if the thread was removed...false otherwise */
   bool removeJob(QString name);

    
   vector<QString> jobNames;
   vector<dynoThread *> threads;
   
   vector<dynoThread *> threadTrash;
private:
    XmodelView *view;
    
signals:
   void jobDone(QString jobName);
};

#endif





































