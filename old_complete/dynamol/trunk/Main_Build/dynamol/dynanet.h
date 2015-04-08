/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef DYNANET_H
#define DYNANET_H

#include <qobject.h>
#include <qstring.h>
/**
@author jfurr
*/

#include <qsocket.h>

class dynanet : public QSocket
{
Q_OBJECT
public:
   dynanet( const QString &host, Q_UINT16 port, QObject *parent = 0, const char *name = 0 );

   ~dynanet();
   QString getMessage();
public slots:

   /** Called when the connection with the server has been closed */
   void closeConnection();

   /** \brief Recieve a file from the dynamol server
   *
   *   This function is used to recieve a file from the dynamol Server
   */
   void getFile();
   
   /** \brief Send a file to the server */
   void sendFile(QString &fileName, const char *newName = 0);
   
   /** This slot is called when the client wants to send a new message to the server */
   void sendToServer(QString msg);

   /** This slot is called then the server has sent a message*/  
   virtual void socketReadyRead();
   
   /** This function specifies the file to save the log results to */
   void setLogFile(QString fileName);
   
   /** This function checks to see if the file already exisits.  
   *   If it does the it appends a _1, _2, _3, _4 etc until it finds an open name
   */
   void checkFileName(QString &fileName);
   
   void socketConnected();
   virtual void socketConnectionClosed();
   void socketClosed();
   void socketError( int e );


   /** brief Used with QTimer to quit trying to connect the server 
   */
   void hangUp();
private:

   
signals:
   void message(QString &);
   void conFail();
   void connClosed();
protected:
   QString msg;
   QString logFile;
public:   
   bool madeConnection;
   QString host;
   Q_UINT16 port;
};

#endif






