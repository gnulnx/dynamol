/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef LICENSEMANAGER_H
#define LICENSEMANAGER_H

#include "license.h"
#include <qstring.h>
#include <string>

using namespace std;
/**
@author jfurr
*/
class licenseManager{
public:
    licenseManager();

    ~licenseManager();
    static bool checkMac_Linux(string &mac);
    static bool checkMac_Windows(string &mac);
    static bool checkLicense();
    static bool simpleCheck();
    
    static bool checkDate(QString &lic);
    static bool checkMACS(QString &lic);
    //static bool checkMac_Linux(string mac);
    //static bool checkMac_Windows(string mac);
};

#endif




































