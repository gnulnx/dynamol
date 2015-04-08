/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "gafffpnet.h"
#include <qtextstream.h>
#include <iostream>
#include <qmessagebox.h>
#include <fstream>

using namespace std;


gaffFpNet::gaffFpNet(const QString &host, Q_UINT16 port, QObject *parent, const char *name )
 : dynanet(host, port, parent, name)
{
   //madeConnection = false;
   gaffMode = false;
   est = false;
}


gaffFpNet::~gaffFpNet()
{
}

void gaffFpNet::setFileNames(QString &feat) {
   FEATURES = feat;
}

void gaffFpNet::timerDone() {
   //////cout <<"Timer Done"<<endl;
   if ( est == false) {
      QString error = "There was an error connecting to the server.\n";
      error += "Please try again later";
      QMessageBox::critical(0, " Server Error", error);
      closeConnection();
   }
}

void gaffFpNet::runGaffFpBg(int countSet) {
   static int count = 0;
   if (countSet != -1) {
      est = false;
      count = 0;
   }
   //////cout <<"gaffFpNet::runGaffFpBg: " << count << endl;
   QTextStream os(this);
   if (count == 0) {
      os <<"gaffFP run"<<endl;
      //////cout <<"Send gaffFP run"<<endl;
      gaffMode = true;
      t = new QTimer( this );
      connect( t, SIGNAL(timeout()), this, SLOT(timerDone()) );
      t->start( 10000, TRUE ); // 2 seconds single-shot timer  
   }
   
   if (count == 1) {
      est = true;
      //////cout <<"Sending features file"<<endl;
      sendFile(FEATURES, "features.txt");
   }
  
   if (count == 2) {
      //////cout <<"Sending:  run gafffp"<<endl;
      os << "run gafffp"<<endl;
   } 
   
   if (count == 3) {
      gaffMode = false;
      count = -1;
      closeConnection();
      emit gaffFpDone();
   } 
   count++;
}


void gaffFpNet::socketReadyRead()
{
   // read from the server
   QString msg = "";
   while ( canReadLine() ) {
      QString line = readLine();
      if (line.contains( "Gaff Ok" ) ) {
          runGaffFpBg();
      }  else if (line.contains( "Gaff Done" ) ) {
          runGaffFpBg();
      }   else if (line.contains( "File Recieved") && gaffMode) {
          runGaffFpBg();
      } else if (line.contains( "Data Read Fail") ) {
          QString error = "Server Error.  Please try again";
          QMessageBox::critical(0, "Error", error);
	  emit connClosed(); 
      } else if (line.contains("Server Busy") ) {
          QString error = "Server Busy.  Please try again";
          QMessageBox::critical(0, "Error", error);
          closeConnection();
      } else if (line.contains("file:") ) {
         getFile();
      }
   }   
   
}






