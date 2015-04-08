/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr
 ***************************************************************************/
#include "licensemanager.h"
#include "qstring.h"
#include <fstream>
#include <iostream>
#include <string>
#include <qdatetime.h>
#include <qmessagebox.h>
#include "licPopUp.h"
#include <qlineedit.h>

using namespace std;

licenseManager::licenseManager()
{
}


licenseManager::~licenseManager()
{
}

bool licenseManager::simpleCheck() {
   //////////cout <<"simpleCheck"<<endl;
   QString PATH = "";
   #ifdef LINUX
      QString DYNAMOL = getenv("DYNAMOL");
      PATH = DYNAMOL + "/LICENSE.txt";
   #endif

   #ifdef WINDOWS
      PATH ="LICENSE.txt";
   #endif

   QString qLic;

   //Read in the License
   ifstream inFile;
   bool fail = false;
   inFile.open(PATH.latin1(), ios::in);
   if ( inFile ) {
      string lic;
      getline(inFile, lic);
      getline(inFile, lic);
      qLic = lic;
   } else {
      return false;
   }

   return licenseManager::checkDate(qLic);
}

bool licenseManager::checkLicense() {

   QString PATH = "";
   //LINUX 2
   #ifdef LINUX
      QString DYNAMOL = getenv("DYNAMOL");
      PATH = DYNAMOL + "/LICENSE.txt";
   #endif

   //WINDOWS 1
   #ifdef WINDOWS
      PATH ="LICENSE.txt";
   #endif LINUX

   QString qLic;
   
   //Read in the License
   ifstream inFile;
   bool fail = false;
   inFile.open(PATH.latin1(), ios::in);
   if ( inFile ) {
      string lic;
      getline(inFile, lic);
      getline(inFile, lic);
      qLic = lic;   
   }
   
   lm *LM = new lm();
   QString part1, part2, part3, part4, part5;
   while (!licenseManager::checkDate(qLic)) {
      LM->edit1->setText(part1);
      LM->edit2->setText(part2);
      LM->edit3->setText(part3);
      LM->edit4->setText(part4);
      LM->edit5->setText(part5);
      if (LM->exec()) {
         part1 += LM->edit1->text();
         part2 += LM->edit2->text();
         part3 += LM->edit3->text();
         part4 += LM->edit4->text();
         part5 += LM->edit5->text();         
      }
      qLic = part1 + part2 + part3 + part4 + part5;
      ofstream outFile(PATH.latin1(), ios::out);
      outFile <<"Dynamol Beta 3"<<endl;
      outFile << qLic << endl;
   }
   return true;
}


bool licenseManager::checkDate(QString &lic) {
   //////////cout <<"YOu are here"<<endl;
  // if (lic.length() != 25) {
//	//////////cout <<"Wrnog length: "<< lic.length() << endl;
//	return false;
 //  }
  //Decode the Licesnse
   unsigned long orig[4];
   //////////cout <<"BEFORE: " << lic << endl;
   LicenseKey::decode(lic.latin1(), orig);
   //////////cout <<"After decode: " << endl;
   QString sec1; sec1.setNum(orig[0]);
   QString sec2; sec2.setNum(orig[1]);
   QString sec3; sec3.setNum(orig[2]);
   QString sec4; sec4.setNum(orig[3]);
  
   ////////cout << "sec1: " << sec1 << endl;
   ////////cout << "sec2: " << sec2 << endl;
   ////////cout << "sec3: " << sec3 << endl;
   ////////cout << "sec4: " << sec4 << endl;
   
   int sYear = sec1.section("", 1, 4).toInt();
   int sDay = sec1.section("",5, 6).toInt();
   int sMonth = sec1.section("",7, 8).toInt();
   //int length = sec4.section("", 8,10).toInt();
   int length = sec1.section("", 9, 10).toInt()*30;
   ////cout <<"Length: " << length << endl;
   ////cout <<"Section 1: " << sec1 << endl; 
 
   //Check License against the current  date
   QDate sDate(sYear, sMonth, sDay);
   int sDayOfYear = sDate.dayOfYear();
     
   QDate date = QDate::currentDate();
   int timeUsed = sDate.daysTo(date);
   int timeRemaining = length - timeUsed;
   
   if (timeRemaining < 0) {
      QString error = "Your license has expired";
      //////////cout << error << endl;
      //QMessageBox::critical( 0, "Dynamol",error);
      return false;
   }
   
   if (timeRemaining < 10) {
      QMessageBox::critical(0, "Licese Expire", "Your license expires soon.");
   } else {
   }
   
   return checkMACS(lic);
}

bool licenseManager::checkMACS(QString &lic) {
string key = lic.latin1();
unsigned long orig[4];
LicenseKey::decode(lic.latin1(), orig);
QString qOrig;
for (int i=0; i<4; i++) {
   ////////cout << orig[i] << endl;
   QString num; num.setNum(orig[i]);
   qOrig += num;
}
////////cout <<"key is: " << key << endl;
////////cout << "qOrig: " << qOrig << endl;
string NEWKEY = "";
for (int i=0; i<qOrig.length(); i+=2) {
string tmpkey = qOrig.latin1();
string key = tmpkey.substr(i,2);
////////cout << "key: " << key << endl;
if (key == "40") {
NEWKEY = NEWKEY +"-";
}
if (key == "39") {
NEWKEY = NEWKEY +":";
}
if (key == "00") {
NEWKEY = NEWKEY + "0";
}
if (key == "01") {
NEWKEY = NEWKEY + "1";
}
if (key == "02") {
NEWKEY = NEWKEY + "2";
}
if (key == "03") {
NEWKEY = NEWKEY + "3";
}
if (key == "04") {
NEWKEY = NEWKEY + "4";
}
if (key == "05") {
NEWKEY = NEWKEY + "5";
}
if (key == "06") {
NEWKEY = NEWKEY + "6";
}
if (key == "07") {
NEWKEY = NEWKEY + "7";
}
if (key == "08") {
NEWKEY = NEWKEY + "8";
}
if (key == "09") {
NEWKEY = NEWKEY + "9";
}
if (key == "10") {
NEWKEY = NEWKEY + "A";
}
if (key == "11") {
NEWKEY = NEWKEY + "B";
}
if (key == "12") {
NEWKEY = NEWKEY + "C";
}
if (key == "13") {
NEWKEY = NEWKEY + "D";
}
if (key == "14") {
NEWKEY = NEWKEY + "E";
}
if (key == "15") {
NEWKEY = NEWKEY + "F";
}
if (key == "16") {
NEWKEY = NEWKEY + "G";
}
if (key == "17") {
NEWKEY = NEWKEY + "H";
}
if (key == "18") {
NEWKEY = NEWKEY + "I";
}
if (key == "19") {
NEWKEY = NEWKEY + "J";
}
if (key == "20") {
NEWKEY = NEWKEY + "K";
}
if (key == "21") {
NEWKEY = NEWKEY + "L";
}
if (key == "22") {
NEWKEY = NEWKEY + "M";
}
if (key == "23") {
NEWKEY = NEWKEY + "N";
}
if (key == "24") {
NEWKEY = NEWKEY + "O";
}
if (key == "25") {
NEWKEY = NEWKEY + "P";
}
if (key == "26") {
NEWKEY = NEWKEY + "Q";
}
if (key == "27") {
NEWKEY = NEWKEY + "R";
}
if (key == "28") {
NEWKEY = NEWKEY + "S";
}
if (key == "29") {
NEWKEY = NEWKEY + "T";
}
if (key == "30") {
NEWKEY = NEWKEY + "U";
}
if (key == "31") {
NEWKEY = NEWKEY + "V";
}
if (key == "32") {
NEWKEY = NEWKEY + "W";
}
if (key == "33") {
NEWKEY = NEWKEY + "X";
}
if (key == "34") {
NEWKEY = NEWKEY + "Y";
}
if (key == "35") {
NEWKEY = NEWKEY + "Z";
}
}

QString tmpKey = NEWKEY;
if (tmpKey.contains(":")) {
   ////////cout <<"DATA ONLY CHECK"<<endl;
   return true;
}

   #ifdef LINUX
      return checkMac_Linux(NEWKEY);
   #endif

   #ifdef WINDOWS
      return checkMac_Windows(NEWKEY);
   #endif
}

//bool LicenseKey::checkMac_Linux(string mac) {
bool licenseManager::checkMac_Linux(string &mac) {
   system("ifconfig > ifconf.txt");
   ifstream inFile("ifconf.txt", ios::in);
   if (!inFile) {
      QMessageBox::critical(0, "MAC FAIL", "MAC ADDRESS FAILED.  Make sure you have permission to run ifconfig");
   }
   
   /** Lets scan the output of ifconfig and look for all available network cards
   *   As soon as one matches lets bail out of this function 
   */
   string tmp;
   bool match = true;
   while (inFile >> tmp) {
      if (tmp == "HWaddr") {
	 string real_mac;
	 inFile >> real_mac;
         ////////cout <<"real mac: "<< real_mac << endl;
         if (real_mac[0] != mac[6]) {
            ////////cout <<"no match 1"<<endl;
	    match = false;
         }
         if (real_mac[1] != mac[7]) {
            ////////cout <<"no match 2"<<endl;
            match = false;
         }
	 if (real_mac[3] != mac[8]) {
            ////////cout <<"no match 3"<<endl;
            match = false;
         }
         if (real_mac[4] != mac[9]) {
            ////////cout <<"no match 4"<<endl;
            match = false;
         }
	 if (real_mac[6] != mac[11]) {
            ////////cout <<"no match 5"<<endl;
            match = false;
         }
	 if (real_mac[7] != mac[12]) {
            ////////cout <<"no match 6"<<endl;
            match = false;
         }
	 if (real_mac[9] != mac[13]) {
            ////////cout <<"no match 7"<<endl;
            match = false;
         }
	 if (real_mac[10] != mac[14]) {
            ////////cout <<"no match 8"<<endl;
            match = false;
         }
	 if (real_mac[12] != mac[16]) {
            ////////cout <<"no match 9"<<endl;
            match = false;
         }
	 if (real_mac[13] != mac[17]) {
            ////////cout <<"no match 10"<<endl;
            match = false;
         }
	 if (real_mac[15] != mac[18]) {
            ////////cout <<"no match 11"<<endl;
            match = false;
         }
	 if (real_mac[16] != mac[19]) {
            ////////cout <<"no match 12"<<endl;
            match = false;
         }

         if (match) {
	   return true;
         }

	
      }
   }
  
   //Unfortunately the mac address did not match up
   QMessageBox::critical(0, "LICENSE ERROR", "MAC Address does not match");
   return false;
}

bool licenseManager::checkMac_Windows(string &mac) {
  return true;
}





































