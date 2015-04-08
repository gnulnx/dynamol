#include <list>
using namespace std;

#include "../../dynamol/molview_script.h"
#include "../../dynacomp/molecule.h"

#include <boost/python.hpp>
using namespace boost::python;

void export_molview()
{
    //object mol = (
    //class_<molViewScript>("MolView")
    //   .def("selectAll", &molViewScript::selectAll)
    //   .def("
    //;
    def("selectAll", molview_selectAll);
    def("selAll", molview_selectAll);
    
    def("selectAtomType", molview_selectAtomType);
    def("selAtomType", molview_selectAtomType);

    def("selectMol", molview_selectMol);
    def("selectWithin", molview_selectWithin);
    def("selectInvert", molview_selectInvert);

    def("atomCount", molview_atomCount);

    def("getMol", molview_getMol, return_internal_reference<>());
   
	def("addMol", molview_addMol);	
};

