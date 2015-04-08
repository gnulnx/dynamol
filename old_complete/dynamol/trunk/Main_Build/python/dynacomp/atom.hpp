#include <boost/python.hpp>
using namespace boost::python;

#include "../../dynacomp/atom.h"

void export_atom()
{

   /** \brief The Dynacomp Atom Class 
   *
   *   Still have quite a bit of functionality to add to this class
   */
    object atom = ( 
    class_<dynacomp::atom> ("atom", init<int, string, float, float, float, int>())
//    	.def("getCoords", &dynacomp::atom::getCoords, return_internal_reference<>())
//	.def(int() [] )
        .def("getSymbol", &dynacomp::atom::getSymbol)
        .def("getNum", &dynacomp::atom::getNum)
        .def("numAtoms", &dynacomp::atom::numAtoms)
        .def("getAtom", &dynacomp::atom::getAtom, return_internal_reference<>())
        .def("getAN", &dynacomp::atom::getAN)
	.def("getRadii", &dynacomp::atom::getRadii)
	.def("getMass", &dynacomp::atom::getMass)
		
	.def("getFFType", &dynacomp::atom::getFFType)
	.def("setFFType", &dynacomp::atom::getFFType)
	.def("getCharge", &dynacomp::atom::getCharge)
	.def("setCharge", &dynacomp::atom::setCharge)
	.def("getEpsilon", &dynacomp::atom::getEpsilon)
	.def("setEpsilon", &dynacomp::atom::setEpsilon)
	.def("getSigma", &dynacomp::atom::getSigma)
	.def("setSigma", &dynacomp::atom::setSigma) 
    );
}
