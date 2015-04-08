/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef GAFFFPNET_H
#define GAFFFPNET_H

#include <qobject.h>
#include "dynanet.h"
#include <qtimer.h>
/**
@author jfurr
*/
class gaffFpNet : public dynanet
{
Q_OBJECT
public:
   gaffFpNet(const QString &host, Q_UINT16 port, QObject *parent=0, const char *name=0 );

   ~gaffFpNet();
    
   /** Set the file names that will be sent for the gaffFP run */
   void setFileNames(QString &feat);
   
   /** \brief Have server screen zinc database
    *  
    *  Call runGaffFpFg to run a local screen of the fg compounds
    */
   void runGaffFpBg(int count = -1);

   /** This should be included in all derived classes of dynanet */
   virtual void socketReadyRead();
   
   
signals:
   void gaffFpDone();
   
private:
   /** file Names to send for gaff run */
   QString FEATURES;
   
   bool gaffMode;
   bool est; // varialbe that is set if connection is established
public slots:
   void timerDone();
   QTimer *t;
};

#endif






