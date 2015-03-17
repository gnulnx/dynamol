// Copyright Ralf W. Grosse-Kunstleve 2002-2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "../../dynamol/molecule.h"
#include "../../dynamol/atom.h"
#include "../../dynamol/bond.h"
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/copy_non_const_reference.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/return_opaque_pointer.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/iterator.hpp>
#include <boost/type_traits/is_void.hpp>

#include <list>
#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <algorithm>
#include <iostream>
using namespace std;

using namespace boost::python;

class mol_wrap {
public:
	mol_wrap() {	
		//You need to take care of managing this pointer
		wrapped_mol = new dynamol::molecule();
	};

	~mol_wrap() {};

	dynamol::atom *addAtom(int num, string type, float x, float y, float z, int atomicNum=-1) {
		return wrapped_mol->addAtom(num, type, x, y, z, atomicNum);
	};

	dynamol::bond *addBond(int num, int from, int to, int order) {
		return wrapped_mol->addBond(num, from, to, order);
	};

	string GetName() {
		return wrapped_mol->GetName();
	};

	void SetName(string name) {
		wrapped_mol->SetName(name);
	};

	vector<dynamol::atom> getAtomObjs() {
		AtomObjs.clear();
		for (int i=0; i<wrapped_mol->atoms.size(); i++)
			AtomObjs.push_back(*wrapped_mol->atoms[i]);
		return AtomObjs;
	};

	vector<dynamol::bond> getBondObjs() {
		BondObjs.clear();
		for (int i=0; i<wrapped_mol->bonds.size(); i++)
			BondObjs.push_back(*wrapped_mol->bonds[i]);

		return BondObjs;
		
	};

	
private:
	dynamol::molecule *wrapped_mol;
	vector<dynamol::atom> AtomObjs;
	vector<dynamol::bond> BondObjs;
};

BOOST_PYTHON_MODULE(molecule)
{
	using boost::python::iterator;
	
	class_< vector<dynamol::atom> >("AtomVec")
		.def(vector_indexing_suite<std::vector<dynamol::atom> >())
	;

	class_< vector<dynamol::bond> >("BondVec")
		.def(vector_indexing_suite<std::vector<dynamol::bond> >())
	;


	//atom(int num, string symbol, float x, float y, float z, int atomicNum);
	class_<dynamol::atom>("Atom", init<int, std::string, float, float, float, int>())
		.def_readwrite("symbol", &dynamol::atom::symbol)
		.def_readwrite("num", &dynamol::atom::num)
		.def_readwrite("AN", &dynamol::atom::AN)
		.def("parent", &dynamol::atom::getParent, return_internal_reference<>()) 
	;


	//bond(int num, atom *from, atom *to, int order);
	class_<dynamol::bond>("Bond", init<int, dynamol::atom *, dynamol::atom *, int>())
		.def_readwrite("order", &dynamol::bond::order)
		.def_readwrite("num", &dynamol::bond::num)
		.def_readwrite("selected", &dynamol::bond::selected)
		.def("parent", &dynamol::bond::getParent, return_internal_reference<>())		
		.def("fromAtm", &dynamol::bond::getFrom, return_internal_reference<>())
		.def("toAtm", &dynamol::bond::getTo, return_internal_reference<>())
	;
	
	/*
    class_<dynamol::molecule>("Mol")
		.def("addAtom", &dynamol::molecule::addAtom, return_internal_reference<>())
		.def("addBond", &dynamol::molecule::addBond, return_internal_reference<>())
		.add_property("name", &dynamol::molecule::GetName, &dynamol::molecule::SetName)

		//This works, but I suspect there is overhead in first building the
		// AtomObj vector in class molecule and then returning
		// by values...it's like you are copying everything 2X
		// There should be some other way
		.add_property("atoms", &dynamol::molecule::getAtomObjs)
		.add_property("bonds", &dynamol::molecule::getBondObjs)
    ;
	*/
	class_<dynamol::molecule>("Mol2")
	;

	class_<mol_wrap>("Mol")
        .def("addAtom", &mol_wrap::addAtom, return_internal_reference<>())
        .def("addBond", &mol_wrap::addBond, return_internal_reference<>())
        .add_property("name", &mol_wrap::GetName, &mol_wrap::SetName)

        //This works, but I suspect there is overhead in first building the
        // AtomObj vector in class molecule and then returning
        // by values...it's like you are copying everything 2X
        // There should be some other way
        .add_property("atoms", &mol_wrap::getAtomObjs)
        .add_property("bonds", &mol_wrap::getBondObjs)
    ;
}

