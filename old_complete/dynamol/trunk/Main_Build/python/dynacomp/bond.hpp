#include <boost/python.hpp>
using namespace boost::python;

#include "../../dynacomp/bond.h"

void export_bond()
{

   /** \brief The Dynacomp Btom Class 
   *
   *   Still have quite a bit of functionality to add to this class
   */
    object bond = (
    class_<dynacomp::bond> ("bond", init<int, dynacomp::atom *, dynacomp::atom *, int>())
        .def("getOrder", &dynacomp::bond::getOrder)
    );
}
