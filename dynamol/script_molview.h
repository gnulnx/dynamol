/***************************************************************************
                          script_molview.h  -  description
                             -------------------
    begin                : Tue Dec 30 2007
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef DYNAMOL_SCRIPT_MOLVIEW_H
#define DYNAMOL_SCRIPT_MOLVIEW_H
#include <string>
using namespace std;

namespace dynamol {
	class molView;
	class molecule;

class script_molView {
public:
    script_molView();
	script_molView(dynamol::molView *viewer);
    //~script_molView();

	static dynamol::molView *viewer;

	/** function returns all the functions and parameters for the class
		You will need to update everytime you add a new function
	*/
	string members();

	bool SetMolColor(float r, float g, float b);

	/** I think this function is obsolete */
	
	bool SetFog(float start, float end, float trans);

	bool RunScript(string filename);

	dynamol::molecule *getCurrMol();
	bool Show(dynamol::molecule *);

	bool LoadMol(string fileName);
};
};

#endif
