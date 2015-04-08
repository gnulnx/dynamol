/***************************************************************************
                          script_molview.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@gmail.com


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/
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
