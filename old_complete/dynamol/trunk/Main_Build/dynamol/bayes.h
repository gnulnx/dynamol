/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef BAYES_H
#define BAYES_H
#include <qstring.h>
#include <map>

using namespace std;
/**
@author jfurr
*/
class Bayes{
public:
   Bayes();

   ~Bayes();
   static bool buildEntropyFile(QString FileName);
   static bool selectFeatures(QString &fgSE, QString &bgSE, int descNum, float minProb);
   
   /** This method allows you to screen a test set and a background set
   *   In one quick pass
   */
   static bool classify(QString &features, QString &bgSE, QString &fgFP, QString &bgFP, float &hr);
   
   /** This function is used to run a set of selected featurs against
   *   the zinc.fp and zinc.se
   */
   static bool classify(QString  &features, QString &bgSE, QString &bgFP, int numHits, map<QString, float> &Hits);
   
private:
};

#endif






