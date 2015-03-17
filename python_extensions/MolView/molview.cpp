// Copyright Ralf W. Grosse-Kunstleve 2002-2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "../../dynamol/script_molview.h"
#include "../../dynamol/molecule.h"
#include "../../dynamol/atom.h"
#include "../../dynamol/bond.h"

#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <iostream>
using namespace std;
#include <string>
using namespace boost::python;

BOOST_PYTHON_MODULE(molview)
{
	class_<script_molView>("molView")
		.def("members", &script_molView::members)
		.def("SetMolColor", &script_molView::SetMolColor)
		.def("getCurrMol", &script_molView::getCurrMol, return_internal_reference<>())
		.def("Show", &script_molView::Show)
		.def("SetFog", &script_molView::SetFog)	
	;
}

