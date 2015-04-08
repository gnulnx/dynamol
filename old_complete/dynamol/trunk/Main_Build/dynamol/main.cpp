/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Tue Dec 30 21:35:06 EST 2003
    copyright            : (C) 2003 by John Furr
    email                : john.furr@dynamol.com
 ***************************************************************************/

//#include <windows.h>
#include <qapplication.h>
#include <qfont.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qtranslator.h>
#include <qsplashscreen.h>
#include <qmessagebox.h>

#include <iostream>
#include "xmodel.h"
#include "test.xpm"
#include "cmdline.h"
//#include "time.h"


#include <qstringlist.h>
#include <qfontdatabase.h>

#include "licensemanager.h"
#include "dynanet.h"
#include <qdatastream.h>
#include <qfile.h>

#include <time.h>

#include "../dynabase/utility.h"

using namespace std;

int main(int argc, char *argv[])
{  
 
  vector<QString> args;
  cmdLine cmd;
  cmd.getArgs(argc, argv, args);

  QApplication a(argc, argv);
/*
  if( !licenseManager::checkLicense()) {
     QString error = "Your license has expired";
      QMessageBox::critical( 0, "Dynamol",error);
      exit(0);
  }
*/

  /**Check for random install number*/
   Q_INT32 ranNum;
   
   QString Path = "";
   #ifdef LINUX
      Path = getenv("HOME");
      Path += "/.dynamol";
   #endif
   #ifdef WINDOWS
     Path = "lCheck";
   #endif

   QFile inFile(Path);
   if (!inFile.exists()) {
      if (inFile.open( IO_WriteOnly ) ) {
         srand(time(NULL));
         ranNum = rand() % 999999999;
         QDataStream s(&inFile);
         s << ranNum;
         inFile.close();
      }
   } else {
      if (inFile.open( IO_ReadOnly) ) {
         QDataStream s( &inFile );  
         s >> ranNum; 
      }
   }
  
  QString rNum; rNum.setNum(ranNum);
  QString host = "24.97.144.147";
  dynanet update(host, 80);
 
  QString checkIn = "Version:\t0.7 ";   


   #ifdef LINUX
      checkIn += "LINUX\t";
   #endif
   
   #ifdef WINDOWS
      checkIn += "WINDOWS\t";
   #endif

   checkIn +=  "\t" + rNum;


   //if (update.madeConnection) {
      update.sendToServer(checkIn);
      
   //}
 
  QPixmap pixmap(test_xpm);
  QSplashScreen *splash = new QSplashScreen( pixmap );
  

  QFontDatabase fdb;
  QStringList fam = fdb.families();
  QFont serif("Serif");  
  a.setFont(serif, QFont::Bold);
  QTranslator tor( 0 );
  tor.load( QString("dynamol.") + QTextCodec::locale(), "." );
  a.installTranslator( &tor );
  
  splash->show();

   //LINUX 1
   #ifdef LINUX
      sleep(2);
   #endif

  XmodelApp *xmodel=new XmodelApp();
  
  
  if (args[0] != "NO") {
     xmodel->runScript(args[0]);
     return a.exec();
  } else {
     
     //xmodel->setGeometry(250, 250, 750, 750);

     xmodel->setCaption("Dynamol");
     xmodel->show();
     xmodel->setMainApp(&a);
     a.setMainWidget(xmodel);
     splash->finish( xmodel );
     return a.exec();
  }
}







































