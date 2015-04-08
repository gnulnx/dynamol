#include <boost/python.hpp>
using namespace boost::python;

#include "../../dynacomp/compute.h"

void export_compute()
{

   /** \brief The Dynacomp Atom Class 
   *
   *   Still have quite a bit of functionality to add to this class
   */
    object pyCompute = ( 
    class_<dynacomp::Compute> ("Compute")
        .def("Charges", &dynacomp::Compute::Charges, 
             "Calculate charges for the molecule")
        .def("Minimize", &dynacomp::Compute::Minimize,
             "Molecule Mechanics Energy Minimization")
    );

//	dict doc(pyCompute.attr("__doc__"));
//	doc = "The Dynamol Compute Module";
    pyCompute.attr("__doc__") = "The Dynamol Compute Module";
}
