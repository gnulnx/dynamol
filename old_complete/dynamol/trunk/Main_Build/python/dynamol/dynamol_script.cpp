#include <boost/python.hpp>
using namespace boost::python;
//#include <Python.h>

#include "molview.hpp"
#include "../dynacomp/atom.hpp"
#include "../dynacomp/bond.hpp"
#include "../dynacomp/molecule.hpp"
#include "../dynacomp/compute.hpp"

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/** \brief Python integration specific
*/

void export_atom();
void export_bond();
void export_molecule();
void export_compute();
void export_molview();

BOOST_PYTHON_MODULE(dynamol)
{
    export_atom();
    export_bond();
    export_molecule();
    export_compute();
    export_molview();
}
