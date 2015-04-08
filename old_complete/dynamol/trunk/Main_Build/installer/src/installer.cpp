/***************************************************************************
 *   Copyright (C) 2004 by jfurr                                           *
 *   jfurr@jabba.albmolecular.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "installer.h"
#include "dynamol.xpm"
#include <qpixmap.h>
#include <qinputdialog.h>
#include <qmessagebox.h>
#include <fstream>
#include <iostream>
#include <qdir.h>
#include <vector>
#include <qprogressdialog.h>
#include "envprompt.h"
#include <qcheckbox.h>

using namespace std;

installer::installer(QString fileName)
    : QMainWindow( 0, "installer", WDestructiveClose )
{
   this->fileName = fileName;
   //ncout <<"FileName is: " << fileName  << endl;
   QPixmap p(dynamol_xpm); 
   setPaletteBackgroundPixmap(p);
   
   showFullScreen();
   createDir();
   copyStuff();
   updateProfile();
   
   //cout <<"Cleared the system"<<endl;
   system("clear");
   system("echo Dynamol has been succefully setup.  Enjoy!");
   /*
   system("echo Environment variables have been set for all users.  The following files have been backed up.  ***Note /home/\~ means user home directory");
   system("echo '/etc/bashrc ---> /etc/bashrc.bckup'");
   system("echo '/home/~/.bashrc ----> /home/~/.bashrc.bckup'");
   system("echo '/home/~/.bash_profile -----> /home/~/.bash_profile.bckup'");
   system("echo ");
   */
   
   system("echo 'If the installer set the environment variables for you then just restart a console and type 'dynamol''");
   exit(1);
}


installer::~installer()
{
}


void installer::createDir() {
   bool ok;
      
   while (true) {
      QString dir = QInputDialog::getText(
      "Dynamol", "Enter Dir for Installation", QLineEdit::Normal,
      "/usr/local/", &ok, this );
   
      if ( !ok ) {
         system("clear");
         exit(0);
      }
      //QString msg = "Preparing to install";
      //QMessageBox::information( 0, "Dynamol",msg);
      
      //dir += "/dynamol/";
      installDir = dir;
      QString makeDir = "mkdir ";
      makeDir += dir;
      system(makeDir.latin1());
   
      QString testFile = dir;
      testFile += "/test";
   
      QString touch = "touch ";
      touch += testFile;
      system(touch.latin1());
   
      ifstream inFile(testFile.latin1(), ios::in);
      if (!inFile) {
   	QString error = "Could not create directory\nPerhaps you do not have permission?";
	QMessageBox::critical( 0, "Dynamol",error);
      } else {
         QString rm = "rm -f ";
	 rm += testFile;
	 system(rm.latin1());
	 break;
      }
   }
}
//fileCheck.setProgress(i);
void installer::copyStuff() {
   
   ifstream inFile2(fileName.latin1(), ios::in);
   if (!inFile2) {
      QString error = "Critical Error....Aborting install\n";
      error += "File not opened in copyStuff()";
      QMessageBox::critical( 0, "Dynamol",error);
      exit(0);
   }
   
   //Lets find out how many lines there are
   int numOfLines = 0;
   string tmp;
   while ( !inFile2.eof() ) {
      getline(inFile2, tmp);
      numOfLines++;
   }
   
   inFile2.close();
   
   ifstream inFile(fileName.latin1(), ios::in);
   
   if (!inFile) {
      QString error = "Critical Error....Aborting install\n";
      error += "File not opened in copyStuff()";
      QMessageBox::critical( 0, "Dynamol",error);
      exit(0);
   }
   
   QString LABEL = "Copying Files";
   int num = 100;
   
  
   
   bool dynamol = false;
   bool dynatype = false;
   string line;
   int c = 0;
   while ( !inFile.eof() ) {
   	getline(inFile, line);
        c++;
	if ( line == "#DYNAMOL" ) {
	   dynamol = true;	
	   break;
	}
   }
   
   if (!dynamol) {
      QString error = "Critical Error....Aborting install";
      QMessageBox::critical( 0, "Dynamol",error);
      exit(0);
   }
   QProgressDialog fileCheck( LABEL, "Cancel", numOfLines-c, this, "Copy Files", FALSE );
   fileCheck.show();
   QString dynamolTar = installDir;
   dynamolTar += "/dynamol.tar.gz";
   
   int count = 0;
   
   ofstream outFile(dynamolTar.latin1(), ios::out);
   while ( !inFile.eof() ) {
      
      if (count % 50 == 0) fileCheck.setProgress(count);
      count++;
      getline(inFile, line);
      if (line == "#DYNATYPE" ) break;
      else outFile << line << endl;
   }
   
   QString unTar = "tar xvfzm ";
   unTar += dynamolTar;
   unTar += " -C ";
   unTar += installDir;
   unTar += " > /dev/null";
   system(unTar.latin1());
   system("clear");
   //delete old libs directory
   QString rmLib = "rm -rf " + installDir + "/dynamol/.libs";
   //cout <<"rmLib: " << rmLib.latin1() << endl;
   system(rmLib.latin1());
   QString mvLib = "mv LIBS " + installDir +"/dynamol/.libs";
   system(mvLib.latin1());
   system("rm -rf LIBS installShield libs.tar.gz");
}

void installer::updateProfile() {
   envprompt *prompt = new envprompt(this);
   if (prompt->exec() and prompt->checkBox->isChecked() ) {  
   
      QString DYNAMOL = installDir;
      DYNAMOL += "/dynamol";
   
      QString exp = "export DYNAMOL=";
      exp += DYNAMOL;
   
      setenv("DYNAMOL", DYNAMOL.latin1(), 1);
   
     // QString PATH = "export PATH=$PATH:";
     // PATH += DYNAMOL;
     // PATH += "/bin";

      QString PATH = "export PATH=" + DYNAMOL + "/bin:$PATH";  
 
      QDir D("/home/");
   
      QStringList users = D.entryList(); 
   
      //First lets do the /home/user/.bashrc
      for(int i=0; i<users.size(); i++) {
         //You should definetly check to see if the varialbes had been previously set.
         QString currDir = "/home/";
         currDir += users[i];
         currDir += "/.bashrc";
      
         QString backup = "cp ";
         backup += currDir;
         backup += " ";
         backup += currDir;
         backup += ".bckup";
         //cout <<"Backup: " << backup << endl;
	
         system(backup.latin1());
	
         QString echo1 = "echo '";
         echo1 += exp;
         echo1 += "' >> ";
         echo1 += currDir;
      
         QString echo2 = "echo '";
         echo2 += PATH;
         echo2 += "' >> ";
         echo2 += currDir;
	
         //Make sure that old environment varialbles are removed
         if (checkProfileFile(currDir) ) {
            system(echo1.latin1());
            system(echo2.latin1());
         }
      }
   
      //Now lets add variables to the /home/user/.bash_profile
      //First lets do the /home/user/.bashrc
      for(int i=0; i<users.size(); i++) {
         //You should definetly check to see if the varialbes had been previously set.
         QString currDir = "/home/";
         currDir += users[i];
         currDir += "/.bash_profile";
      
         QString backup = "cp ";
         backup += currDir;
         backup += " ";
         backup += currDir;
         backup += ".bckup";
         //cout <<"Backup: " << backup << endl;
	
         system(backup.latin1());
   	
         QString echo1 = "echo '";
         echo1 += exp;
         echo1 += "' >> ";
         echo1 += currDir;
      
         QString echo2 = "echo '";
         echo2 += PATH;
         echo2 += "' >> ";
         echo2 += currDir;
	
         //Make sure that old environment varialbles are removed
         if (checkProfileFile(currDir) ) {
            system(echo1.latin1());
            system(echo2.latin1());
         }
      }
   
      system("cp /etc/bashrc /etc/bashrc.bckup");
      QString etc = "echo " + exp + " >> /etc/bashrc";
      QString etc2 = "echo " + PATH + " >> /etc/bashrc";
      if ( checkProfileFile("/etc/bashrc") ) {
         system(etc.latin1());
         system(etc2.latin1());
      }
   }
}

bool installer::checkProfileFile(QString file) {
   ifstream inFile(file.latin1(), ios::in);
   if (!inFile) {
      return false;
   }
   
   vector<QString> profileFile;
   string line;
   while ( !inFile.eof() ) {
      getline(inFile, line);
      QString qLine = line;
      if (!qLine.contains("dynamol") ) profileFile.push_back(qLine);
   }
   
   ofstream outFile(file.latin1(), ios::out);
   
   int blankCount = 0;
   for (int i=0; i<profileFile.size(); i++) {
      //cout <<"Lengths: "<<profileFile[i].length() << endl;
      if (profileFile[i].length() == 0) blankCount++;
      else blankCount = 0;
      if (blankCount < 2)
         outFile << profileFile[i] << endl;
   }
   
   return true;
}
