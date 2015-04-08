/************************************************************************
                        molview.cpp  -  description
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
	class_<dynamol::script_molView>("molView")
		.def("members", &dynamol::script_molView::members)
		.def("SetMolColor", &dynamol::script_molView::SetMolColor)
		.def("getCurrMol", &dynamol::script_molView::getCurrMol, return_internal_reference<>())
		.def("Show", &dynamol::script_molView::Show)
		.def("SetFog", &dynamol::script_molView::SetFog)	
	;
}

