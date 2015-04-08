/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "bayes.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <qmessagebox.h>
#include <math.h>
#include <sstream>
using namespace std;

Bayes::Bayes()
{
}


Bayes::~Bayes()
{
}

bool Bayes::buildEntropyFile(QString FileName)
{
   ifstream inFile(FileName.latin1(), ios::in);
   if (!inFile) {
       cout <<FileName<<" was not found"<<endl;
       QString error = FileName + " Not found";
       QMessageBox::critical(0, "File Not Found", error);
       return false;
   }
   string header;
   getline(inFile, header);
   /** YOU ARE USING THE envMap TO KEEP TRACK OF THE TOTAL NUMBER OF DIFFERENT 
   * ATOM ENVIRONMENTS  AS WELL AS THE THE NUMBER OF COMPOUNDS THAT CONTAIN 
   * THE ENVIRONMENT...THIS IS DONE WITH  THE set
   */
   vector<float> Counts(100000);
   for (int i=0; i<Counts.size(); i++) 
      Counts[i] = 0;
      string name, fp;
      float totCount = 0;
      while (inFile >> name) {
          getline(inFile, fp);
          set<float> dup;
          stringstream s(fp);
          int index;
          while (s >> index) {
             if (dup.find(index) == dup.end() && index >= 0) {
             dup.insert(index);
             Counts[index]++;
          }
      } 
      totCount++;
   }

   ofstream outFile("fp.se", ios::out);
   if (!outFile) {
       QMessageBox::critical(0, "File Error", "Can not open tmp file for writing.  Please check permissions");
       return false;
   }
   outFile << fixed;
   outFile <<"Desc\tEntropy(se)\tProb(P)"<<endl;
   for (int i=0; i<Counts.size(); i++) {
      if (Counts[i] > 0) {
         float a = Counts[i]/totCount;
         float b = (totCount-Counts[i])/totCount;
         float se = 0.0;
         if (b != 0)
            se = -a *log(a)/log(2.0) - b*log(b)/log(2.0); 
         float prob = Counts[i]/totCount;
         float gain = sqrt((1.0-se)*prob);
         outFile <<i <<setw(12) <<se <<setw(12) << prob<<endl;// <<setw(12)<<gain<< endl;	 	 
     }
  }

  return true;
}
/*
bool Bayes::selectFeatures(QString &fgSE, QString &bgSE, int descNum, float minProb)
{
    // DATA READ IN SECTION 
    ifstream activeIn(fgSE.latin1(), ios::in);
    ifstream inactiveIn(bgSE.latin1(), ios::in);

    if (!activeIn) {
	QString error = fgSE + " file not found in FingerPrint directory";
	 QMessageBox::critical(0, "File Error", error);
	 return false;
    }

    if (!inactiveIn) {
        cout <<"Bayes::selectFeatures inactiveIn not found"<<endl;
	QString error = bgSE + " file not found in FingerPrint directory";
	QMessageBox::critical(0, "File Error", error);
	return false;
    }

   string header;
   getline(activeIn, header); //get header
   getline(inactiveIn, header); //get header

   string fp;
   float prob, se;
   vector<string> act_fp, inact_fp;
   map<int, float> act_prob, inact_prob;
   map<int, float> act_se, inact_se;
   // READ IN THE ACTIVE DATA
   while (activeIn >> fp >> se >> prob ) {  
       
       if (activeIn.eof()) break;
   
      act_prob[ act_fp.size() ] = prob;
      act_se[ act_fp.size() ] = se;    
      
      act_fp.push_back(fp);      
  }

   //READ IN THE INACTIVE DATA
   while (inactiveIn >> fp >> se >> prob ) {  
       
      if (inactiveIn.eof()) break;

      inact_prob[ inact_fp.size() ] = prob;
      inact_se[ inact_fp.size() ] = se;

      inact_fp.push_back(fp);
  }

   // INFORMATION GAIN SECTION 
   vector<float> iGainSort;
   vector<string> fpSort;
   for (int i=0; i<act_fp.size(); i++) {
       int inActIndex = -1;
       for (int j=0; j< inact_fp.size(); j++) {
	   if (inact_fp[j] == act_fp[i]) {
	       inActIndex = j;
	       break;
	   }
       }
   
       if (inActIndex != -1) { //If the string is not found in inactives then move on bacause iGain neg;
	   float actSE = act_se[ i ];
	   float inactSE = inact_se[ inActIndex ];
	   float iGain = inactSE - actSE;
	   //iGainSet
	   if (act_prob[ i ] > minProb) {
	       iGainSort.push_back( iGain );
	       fpSort.push_back( act_fp[ i ] );
	   }
       }
  
   }

   //SORT THE DESCRIPTORS
   float hold;
   string sHold;
   for (int i=0; i<iGainSort.size(); i++) {
       for (int j=i+1; j<iGainSort.size(); j++) {
	   if (iGainSort[j] > iGainSort[i]) {
	       hold = iGainSort[i];
	       iGainSort[i] = iGainSort[j];
	       iGainSort[j] = hold;
    
	       sHold = fpSort[i];
	       fpSort[i] = fpSort[j];
	       fpSort[j] = sHold;
	   }
       }
   }

   //Reduce the size down to 40
   while (iGainSort.size() > descNum) {
       iGainSort.pop_back();
       fpSort.pop_back();
   }

   ofstream outFile("features.txt", ios::out);
   if (!outFile) { 
       QMessageBox::critical(0, "File Error", "Could not write tmp file.  Please check permissions");
       return false;
   }
   outFile <<"fingerprint \t iGain \t active_probability \t inactive_probability"<<endl;
   //display the results...for your personal viewing pleasure
   for (int i=0; i<iGainSort.size(); i++) {
       int actIndex, inactIndex;
       actIndex = inactIndex = -1;
       for (int j=0; j<act_fp.size(); j++) {
	   if (act_fp[j] == fpSort[i]) {
	       actIndex = j;
	       break;
	   }
       }

       for (int j=0; j<inact_fp.size(); j++) {
	   if (inact_fp[j] == fpSort[i]) {
	       inactIndex = j;
	       break;
	   }
       }

       outFile << fpSort[i] << "\t" << iGainSort[i] << "\t" << act_prob[actIndex] <<"\t"<<inact_prob[inactIndex]<< endl;
   }
   return true;
}
*/

bool Bayes::selectFeatures(QString &fgSE, QString &bgSE, int descNum, float minProb)
{
    /* DATA READ IN SECTION */
    ifstream activeIn(fgSE.latin1(), ios::in);
    ifstream inactiveIn(bgSE.latin1(), ios::in);

    if (!activeIn) {
	QString error = fgSE + " file not found in FingerPrint directory";
	 QMessageBox::critical(0, "File Error", error);
	 return false;
    }

    if (!inactiveIn) {
	QString error = bgSE + " file not found in FingerPrint directory";
	 QMessageBox::critical(0, "File Error", error);
	 return false;
    }

   string header;
   getline(activeIn, header); //get header
   getline(inactiveIn, header); //get header

   int fp;
   float prob, se;
   vector<int> act_fp, inact_fp;
   set<int> actFP;
   map<int, float> act_prob, inact_prob;
   map<int, float> act_se, inact_se;
   // READ IN THE ACTIVE DATA
   while (activeIn >> fp >> se >> prob ) {  
       
       if (activeIn.eof()) break;
   
      act_prob[ act_fp.size() ] = prob;
      act_se[ act_fp.size() ] = se;    
      
      act_fp.push_back(fp);      
      actFP.insert(fp);
  }

   //READ IN THE INACTIVE DATA
   while (inactiveIn >> fp >> se >> prob ) {  
       
      if (inactiveIn.eof()) break;

      inact_prob[ inact_fp.size() ] = prob;
      inact_se[ inact_fp.size() ] = se;

      inact_fp.push_back(fp);
  }

   /* INFORMATION GAIN SECTION */
   vector<float> iGainSort;
   vector<int> fpSort;
  
    
   for (int i=0; i<act_fp.size(); i++) {
       int inActIndex = -1;
       for (int j=0; j< inact_fp.size(); j++) {
	   if (inact_fp[j] == act_fp[i]) {
	       inActIndex = j;
	       break;
	   }
       }
   
       if (inActIndex != -1) { //If the string is not found in inactives then move on bacause iGain neg;
	   float actSE = act_se[ i ];
	   float inactSE = inact_se[ inActIndex ];
	   float iGain = inactSE - actSE;
           iGainSort.push_back(act_prob[i] / inact_prob[ inActIndex]);
           fpSort.push_back( act_fp[i] );
       }
  
   }

   //SORT THE DESCRIPTORS
   float hold;
   int sHold;
   for (int i=0; i<iGainSort.size(); i++) {
       for (int j=i+1; j<iGainSort.size(); j++) {
	   if (iGainSort[j] > iGainSort[i]) {
	       hold = iGainSort[i];
	       iGainSort[i] = iGainSort[j];
	       iGainSort[j] = hold;
    
	       sHold = fpSort[i];
	       fpSort[i] = fpSort[j];
	       fpSort[j] = sHold;
	   }
       }
   }

   //Reduce the size down to 40
   while (iGainSort.size() > descNum) {
       iGainSort.pop_back();
       fpSort.pop_back();
   }

   ofstream outFile("features.txt", ios::out);
   if (!outFile) { 
       QMessageBox::critical(0, "File Error", "Could not write tmp file.  Please check permissions");
       return false;
   }
   outFile <<"fingerprint \t iGain \t active_probability \t inactive_probability"<<endl;
   //display the results...for your personal viewing pleasure
   for (int i=0; i<iGainSort.size(); i++) {
       int actIndex, inactIndex;
       actIndex = inactIndex = -1;
       for (int j=0; j<act_fp.size(); j++) {
	   if (act_fp[j] == fpSort[i]) {
	       actIndex = j;
	       break;
	   }
       }

       for (int j=0; j<inact_fp.size(); j++) {
	   if (inact_fp[j] == fpSort[i]) {
	       inactIndex = j;
	       break;
	   }
       }

       outFile << fpSort[i] << "\t" << iGainSort[i] << "\t" << act_prob[actIndex] <<"\t"<<inact_prob[inactIndex]<< endl;
   }
   return true;
}

bool Bayes::classify(QString &features, QString &bgSE, QString &fgFP, QString &bgFP, float &hr)
{
	//QMessageBox::critical(0, "HERE", "HERE 1");
    map<string, int> bitMap;
    map<int, float> probMap;
    map<int, float> seMap;

    ifstream fIn(features.latin1(), ios::in);
    ifstream seIn(bgSE.latin1(), ios::in);
    ifstream dataIn(fgFP.latin1(), ios::in);

    if (!fIn) {
	QString error = features + " file not found in FingerPrint directory";
	QMessageBox::critical(0, "File Error", error);
	return false;
    }
    if (!seIn) {
	QString error = bgSE + " file not found in FingerPrint directory";
	QMessageBox::critical(0, "File Error", error);
	return false;;
    }
    if (!dataIn) {
	QString error = fgFP + " file not found in FingerPrint directory";
	QMessageBox::critical(0, "File Error", error);
	return false;
    }
    
    /** Read in the sinc.se file and create lookup maps */
   string header;
   getline(seIn, header);
   int count = 0;
   string bitString;
   float prob, se;
   while (seIn >> bitString >> prob >> se) {
      bitMap[bitString] = count;
      probMap[count] = prob;
      seMap[count] = se;
      count++;
   }

   /** Now lets read in the allowed features */
   getline(fIn, header);
   set<int> allowed;
   map<int, float> act_prob;
   map<int, float> inact_prob;
   float iGain, actProb, inactProb;
   while (fIn >> bitString >> iGain >> actProb >> inactProb) {
      int desc = bitMap[bitString];
      allowed.insert( desc );
      act_prob[desc] = actProb;
      inact_prob[desc] = inactProb; 
   }

   /** Now lets classify the bg compounds */
   getline(dataIn, header);
   multimap<float, string> sortMap;
   multimap<float, string>::iterator mi;

   count = 0;
   vector< multimap<float, string> > fgHits;
   vector<float> fgScores;
   vector<float> fgWorstScores;
   float worstScore = -100000;
   bool fg = true;
   set<string> fgNames;
   while (true) {
   
      while (true) {
         string line;
         getline(dataIn, line);
         if ( dataIn.eof() )
            break;

         stringstream s(line);
         string name;
         s >> name;
         if (fg) {
            fgNames.insert(name);
         }
         int dIndex;
         float actProb = 1;
         float inactProb = 1;
         while (s >> dIndex) {
            //s >> dIndex;
            //if (s.eof()) 
            //   break;
            if (allowed.find(dIndex) != allowed.end() ) {
               actProb *= act_prob[ dIndex ];
               inactProb *= inact_prob[ dIndex ];
            }
         }
         //float top = 32.0/2700000.0;
         //float top = 32.0/5454431.0;
         float top = 32.0/(32.0+5454431.0);
         //float bot = 1.0-top;
         float bot = 5454431.0/(32.0+5454431.0);
         float a = top/bot;
  
         if (inactProb == 0) {
            inactProb  = 0.000001; 
         }
         float b = actProb/inactProb;
         float score = a*b;
         //score = b;
         if (inactProb == 0.000001) {
         } 
         if (sortMap.size() < 1000) {
            sortMap.insert(pair<float, string>(score, name));
         } else {
            if (sortMap.size() >= 1000 && score > worstScore) {
               sortMap.insert(pair<float, string>(score, name));
               mi = sortMap.begin();
               worstScore = mi->first;
            }
         }
         if (sortMap.size() > 1000) {
            sortMap.erase(sortMap.begin());
         }

         count++;
      }
      if (bgFP == "NULL")
         break;
      else {
         dataIn.close();
         dataIn.clear();
         dataIn.open(bgFP.latin1(), ios::in);
         if (!dataIn) {
            QString error = bgFP + " file not found in FingerPrint directory";
            QMessageBox::critical(0, "File Error", error);
	     return false;
         }
         getline(dataIn, header);
         bgFP = "NULL";
      }
      fg = false;    
   }//end two file section

   // START THE SORT SECTION  
   mi = sortMap.end();
   ofstream outFile2("hits.txt", ios::out);
   int hits = 0;
   count = 0;
   mi--;

   while (true) {
      //for (mi; mi != sortMap.begin(); mi--) {
      outFile2 << mi->second <<"\t" << mi->first <<  endl;
      if (fgNames.find(mi->second) != fgNames.end() ) {
         hits++;
      }
      if (count == 100) 
         break;
      
      count++;

      if (mi == sortMap.begin()) 
         break;

      mi--;
   }

   hr = (float)hits/fgNames.size();

   return true;
}
//##############################################################
//######################## NEW CLASSIFY SECTION ################
//##############################################################
//##############################################################

bool Bayes::classify(QString  &features, QString &bgSE, QString &bgFP, int numHits, map<QString, float> &Hits) {

    //QMessageBox::critical(0, "HERE", "Bayes::classify");
    map<string, int> bitMap;
    map<int, float> probMap;
    map<int, float> seMap;

    ifstream fIn(features.latin1(), ios::in);
    ifstream seIn(bgSE.latin1(), ios::in);
    ifstream dataIn(bgFP.latin1(), ios::in);

    if (!fIn) {
		QString error = features + " 1file not found in FingerPrint directory";
		QMessageBox::critical(0, "File Error", error);
		return false;
    }
    if (!seIn) {
		QString error = bgSE + " 2file not found in FingerPrint directory";
		QMessageBox::critical(0, "File Error", error);
		return false;;
    }
    if (!dataIn) {
		QString error = bgFP + " 3file not found in FingerPrint directory";
		QMessageBox::critical(0, "File Error", error);
		return false;
    }
    
    /** Read in the zinc.se file and create lookup maps */
   string header;
   getline(seIn, header);
   int count = 0;
   string bitString;
   float prob, se;
   while (seIn >> bitString >> prob >> se) {
      bitMap[bitString] = count;
      probMap[count] = prob;
      seMap[count] = se;
      count++;
   }
   
   /** Now lets read in the allowed features */
   getline(fIn, header);
   set<int> allowed;
   map<int, float> act_prob;
   map<int, float> inact_prob;
   float iGain, actProb, inactProb;
   while (fIn >> bitString >> iGain >> actProb >> inactProb) {
      int desc = bitMap[bitString];
      allowed.insert( desc );
      act_prob[desc] = actProb;
      inact_prob[desc] = inactProb; 
   }

   /** Now lets classify the bg compounds */
   getline(dataIn, header);
   multimap<float, string> sortMap;
   multimap<float, string>::iterator mi;

   count = 0;
   float worstScore = -100000;
   
   while (true) {
      string line;
      getline(dataIn, line);
      if ( dataIn.eof() )
         break;

      stringstream s(line);
      string name;
      s >> name;
      
      int dIndex;
      double actProb = 1;
      double inactProb = 1;
      double allGain = 1;
      int numDescFound = 0;
      while (s >> dIndex) {
         if (allowed.find(dIndex) != allowed.end() ) {
            numDescFound++;
            actProb *= act_prob[ dIndex ];
            inactProb *= inact_prob[ dIndex ];
         }
      }
  
      double score = 0;
      if (inactProb == 0) {
         score = 1;
      }
      else if (actProb == 0) {
         score = 0;
      } else {
          double b = log(actProb) - log(inactProb);
          //score = a*b;
          score = log(actProb) - log(inactProb);
          if (actProb == 1 && inactProb == 1) {
              score = -1000000;
          }
	 // score = actProb/inactProb;
      }
      if (sortMap.size() < 100000) {
         sortMap.insert(pair<float, string>(score, name));
      } else {
         if (sortMap.size() >= 100000 && score > worstScore) {
            sortMap.insert(pair<float, string>(score, name));
            mi = sortMap.begin();
            worstScore = mi->first;
         }
      }
      if (sortMap.size() > 100000) {
         sortMap.erase(sortMap.begin());
      }

      count++;
   }
      

   // START THE SORT SECTION  
   mi = sortMap.end();
   ofstream outFile2("hits.txt", ios::out);
   int hits = 0;
   count = 0;
   mi--;

   while (true) {
      outFile2 << mi->second <<"\t" << mi->first <<  endl;
      Hits[mi->second] = mi->first;

      if (count == numHits) 
         break;
      
      count++;

      if (mi == sortMap.begin()) 
         break;

      mi--;
   }

   //int g = 0;
   //cin >> g; 
   return true;
}









