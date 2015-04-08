#include <boost/python.hpp>
using namespace boost::python;

#include "../../dynacomp/compute.h"

#include "atom.hpp"
#include "bond.hpp"
#include "molecule.hpp"
#include "compute.hpp"

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/** \brief Python integration specific
*/
//include <boost/python.hpp>
//#include <Python.h>

// ################# C++ WRAPPER PORTION ################
namespace dynacomp {
}

void export_atom();
void export_bond();
void export_molecule();
void export_compute();

BOOST_PYTHON_MODULE(dynacomp)
{
    export_atom();
    export_bond();
    export_molecule();
    export_compute();
}
