/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "dynanet.h"
#include <qtextstream.h>
#include <qdatastream.h>
#include <qsocket.h>
#include <iostream>
#include <qmessagebox.h>
#include <fstream>
#include <qfile.h>
#include <qtimer.h>

using namespace std;

dynanet::dynanet( const QString &host, Q_UINT16 port, QObject *parent, const char *name )
: QSocket(parent, name)
{
   this->host = host;
   this->port = port;
   logFile = "log.tmp";
   ofstream outFile(logFile.latin1(), ios::out);
   outFile.close();
   outFile.clear();
   // create the socket and connect various of its signals
   connect( this, SIGNAL(connected()), this, SLOT(socketConnected()) );
   connect( this, SIGNAL(connectionClosed()), this, SLOT(socketConnectionClosed()) );
   connect( this, SIGNAL(readyRead()), this, SLOT(socketReadyRead()) );
   connect( this, SIGNAL(error(int)), this, SLOT(socketError(int)) );
   
   madeConnection = false;
   connectToHost( host, port );
   QTimer *timer = new QTimer( this );
   //connect( timer, SIGNAL(timeout()), this, SLOT(hangUp()));
   //timer->start( 1500, TRUE );
}

void dynanet::hangUp() {
   closeConnection();
}

dynanet::~dynanet()
{
}

void dynanet::closeConnection()
{ 
   if (!madeConnection) {
      waitForMore ( 50 );
      if (madeConnection) 	
	return; 
   }
   
   close();
   if ( state() == QSocket::Closing ) {
      // We have a delayed close.
      connect( this, SIGNAL(delayedCloseFinished()), this, SLOT(socketClosed()) );
   } else {
      // The socket is closed.
      socketClosed();
   }
   emit connClosed(); 
}

void dynanet::sendToServer(QString msg)
{
   // write to the server
   QTextStream os(this);
   os << msg <<"\n";
}

/** This function is were you perform all the usefull stuff */
void dynanet::socketReadyRead()
{
   // read from the server
   QString msg = "";
   bool updateFound = false;
   while ( canReadLine() ) {
      QString line = readLine();
      if (line.contains("Update:") || updateFound==true ) {
         msg += line;
         updateFound = true;
         
      } else if (line.contains("Message:") ) {
	 msg += line;
	 updateFound = true;	
      } else if (line.contains( "Data Read Fail") ) {
          QString error = "Data Read Error.  Please try again";
          QMessageBox::critical(0, "Error", error);
      } else if (line.contains("Server Busy") ) {
          QString error = "Server Busy.  Please try again";
          QMessageBox::critical(0, "Error", line);
          closeConnection();
      } else if (line.contains("file:") ) {
         getFile();
      }
   }   
   if (updateFound) {
      closeConnection();
      QMessageBox::information(0, "Dynamol", msg); 
   }
}

void dynanet::socketConnected()
{
   madeConnection = true;
   msg = "Connected to server\n";
   emit message(msg);
}

void dynanet::socketConnectionClosed()
{  
   msg = "Connection closed by server\n";
   emit message(msg);
}

void dynanet::socketClosed()
{
   msg = "Connection closed\n";
   emit message(msg);
}

void dynanet::socketError( int e )
{
   QString eS; eS.setNum(e);
   msg = "Error number " + eS + " occurred\n";
   emit message(msg);
   void conFail();
}

QString dynanet::getMessage() {
   return msg;
}

void dynanet::sendFile(QString &fileName, const char *newName) {
   QTextStream os(this);
   ifstream inFile(fileName.latin1(), ios::in);
   if (!inFile) {
      return;
   }

   string line;
   QString message;
   QString tmp;
   message = "file:\n";

   if (newName == 0)
      message += fileName.latin1();
   else
      message += newName;

   message += "\n";
   int lineCount = 0;
   while (true) {
      getline(inFile, line);
      if (inFile.eof())
        break;

      tmp += line + "\n";
      lineCount++;
   }

   QString num; num.setNum(lineCount);
   message += num + "\n" + tmp;
   os << message << endl;
}

void dynanet::getFile() {
   QTextStream ts( this );
   QString fileName = ts.readLine();
   checkFileName(fileName);
   ofstream outLog(logFile.latin1(), ios::app);
   outLog << fileName << endl;
   
   ofstream outFile(fileName.latin1(), ios::out);
   if (!outFile) {
      return;
   }

   int numOfLines = 0;
   if ( canReadLine() ) {
      QString num = ts.readLine();
      numOfLines = num.toInt();
   } else {
   }
   
   int linesRead = 0;

   int waitCount = 0;
   while (true) {
      if (canReadLine()) {
         QString str = ts.readLine();
         outFile << str << endl;
         linesRead++;
      } else {
         waitForMore ( 50 );
         waitCount++;
         if (waitCount == 5) {
            ts <<"Data Read Fail"<<endl;
         }
      }
      if (linesRead == numOfLines) {
         break;
      } 
   }

   outFile.close();
   outFile.clear();
   ts <<"File Recieved "<< fileName << endl;
}

//create the log file.
void dynanet::setLogFile(QString fileName) {
  logFile = fileName;
  ofstream outFile(logFile.latin1(), ios::out);
  outFile.close();
  outFile.clear();
}

void dynanet::checkFileName(QString &fileName) {
   QString baseName = "";
   QString extension = "";
   bool ext = false;
   for (int i=0; i<fileName.length(); i++) {
      if (fileName[i] == '.') {
         ext = true;
      }
      if (!ext) {
         baseName += fileName[i];
      } else {
         extension += fileName[i];
      }
   }
   QString tmpName = fileName;
   int count = 0;
   QString num;
   while ( QFile::exists( tmpName ) ) {
      count++;
      num.setNum(count);
      tmpName = baseName + "_" + num + extension;
      //////////cout <<"Tyring tmpName: " << tmpName << endl;
   }
   
   fileName = tmpName;
}



