#include <boost/python.hpp>
using namespace boost::python;

#include "../../dynacomp/molecule.h"

void export_molecule()
{
   /** This section is for thin wrapper functions.
    *
    *   These wrapper functions are necassary when wrapping overloaded functions
    *   The other options was to create a new function in the class.
    *   Creating new functions seemed like a pretty bad idea.
    */
    dynacomp::atom *(dynacomp::molecule::*addAtom1)(int, string, float, float, float, int)
    = &dynacomp::molecule::addAtom;
   
    dynacomp::bond *(dynacomp::molecule::*getBond1)(int)
    = &dynacomp::molecule::getBond;

    object mol = (
    class_<dynacomp::molecule>("molecule")
       
       .def("addAtom", addAtom1, return_internal_reference<>())
       .def("numAtoms", &dynacomp::molecule::numAtoms)
       .def("getAtom", &dynacomp::molecule::getAtom, return_internal_reference<>())

       .def("addBond", &dynacomp::molecule::addBond, return_internal_reference<>())
       .def("getBond", getBond1, return_internal_reference<>())
       .def("numBonds", &dynacomp::molecule::numBonds)


       .def("getName", &dynacomp::molecule::getName)
       .def("setName", &dynacomp::molecule::setName)
    );
}
