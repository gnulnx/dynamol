/********************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 *******************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <QtGui>
#include <QApplication>
#include <iostream>
#include <cstdlib>
#include <string>
#include "gaffsig.h"

using namespace std;
using namespace fp;

int main(int argc, char *argv[])
{
	string inFile = argv[1];
	string outFile = argv[2];
	cout << "inFile: " << inFile << endl;
	cout <<"outFile: " << outFile << endl;
	fp::gaffSig gs;
	gs.readSubSets(-1);
	gs.processFile(inFile, outFile);
	return EXIT_SUCCESS;
}

