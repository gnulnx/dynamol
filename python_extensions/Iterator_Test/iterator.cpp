// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/copy_non_const_reference.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <list>
#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <algorithm>

using namespace boost::python;

typedef std::list<int> list_int;
typedef std::list<list_int> list_list;

class X // a container element
{
public:
    std::string s;
    X():s("default") {}
    X(std::string s):s(s) {}
    std::string repr() const { return s; }
    void reset() { s = "reset"; }
    void foo() { s = "foo"; }
    bool operator==(X const& x) const { return s == x.s; }
    //bool operator!=(X const& x) const { return s != x.s; }
};

class atom
{
public:
	atom() {}
	~atom() {}
	bool operator==(atom const& a) const {return true; }
	bool operator!=(atom const& a) const { return false; }
};

class TestClass
{
public:
	std::vector<float> Vec;
	std::vector<atom> atmVec;
	std::vector<atom *> atmPtrVec;
	TestClass() {
		tcList.push_back(1);
		tcList.push_back(2);
		tcList.push_back(4);
		tcList.push_back(8);
		tcList.push_back(9);
	}
	int size() { return tcList.size(); }
	//void push_back(std::list<int> &x, int y){ tcList.push_back(y); }

	std::vector<atom> getAtomVec()
	{ return atmVec; }
	
	std::string getName() { return name; }
	void setName(std::string name) { this->name = name; }

	std::list<int> getTcList() { return tcList; }
	//void SetTcList(list<int> lList) { this->tcList = lList; }	

	std::list<int> tcList;
	std::string name;
};

void a_push_back(std::vector<atom *> &v, atom *y)
{
    v.push_back(y);
}

int a_size(std::vector<atom *> &v)
{
    return v.size();
}

void *a_get(std::vector<atom *> &v, int i)
{
    return v[i];
}

void v_push_back(std::vector<float> &v, float y)
{ 
	v.push_back(y);
}

int v_size(std::vector<float> &v)
{
	return v.size();
}

float v_get(std::vector<float> &v, int i)
{
	return v[i];
}


void push_back(list_int& x, int y)
{
    x.push_back(y);
}


int size(list_int &x)
{
	return x.size();
}

void push_list_back(list_list& x, list_int const& y)
{
    x.push_back(y);
}

int back(list_int& x)
{
    return x.back();
}

typedef std::pair<list_int::iterator,list_int::iterator> list_range;

struct list_range2 : list_range
{
    list_int::iterator& begin() { return this->first; }
    list_int::iterator& end() { return this->second; }
};

list_range range(list_int& x)
{
    return list_range(x.begin(), x.end());
}

struct two_lists
{
    two_lists()
    {
        int primes[] = { 2, 3, 5, 7, 11, 13 };
        std::copy(primes, primes + sizeof(primes)/sizeof(*primes), std::back_inserter(one));
        int evens[] = { 2, 4, 6, 8, 10, 12 };
        std::copy(evens, evens + sizeof(evens)/sizeof(*evens), std::back_inserter(two));
    }

    struct two_start
    {
        typedef list_int::iterator result_type;
        result_type operator()(two_lists& ll) const { return ll.two.begin(); }
    };
    friend struct two_start;
    
    list_int::iterator one_begin() { return one.begin(); }
    list_int::iterator two_begin() { return two.begin(); }

    list_int::iterator one_end() { return one.end(); }
    list_int::iterator two_end() { return two.end(); }
        
private:
    list_int one;
    list_int two;
};

BOOST_PYTHON_MODULE(iterator_ext)
{
    using boost::python::iterator; // gcc 2.96 bug workaround

	 class_<X>("X")
        .def(init<>())
        .def(init<X>())
        .def(init<std::string>())
        .def("__repr__", &X::repr)
        .def("reset", &X::reset)
        .def("foo", &X::foo)
    ;

    class_<std::vector<X> >("XVec")
        .def(vector_indexing_suite<std::vector<X> >())
	;
	class_< std::vector<atom> >("vector_atom")
        .def(vector_indexing_suite<std::vector<atom> >())
    ;

	class_<std::vector<atom *> >("Atm_Ptr")
		.def(vector_indexing_suite<std::vector<atom *> >())
    ;


    def("range", &::range);

    class_<list_int>("list_int")
        .def("push_back", push_back)
        .def("back", back)
        .def("__iter__", iterator<list_int>())
		.def("__len__", size)
        ;

	class_< std::vector<float> >("vector_float")
		.def("push_back", v_push_back)
		.def("__iter__", iterator< std::vector<float> >())
		.def("__len__", v_size)
		.def("__getitem__", v_get)
	;

	class_<atom>("atom")
	;


	
	class_<TestClass>("TestClass")
		.def("push_back", push_back)
		.def("back", back)
		.add_property("rovalue", &TestClass::getName)
		.add_property("name", &TestClass::getName, &TestClass::setName)
		.add_property("tcList", &TestClass::getTcList)
		.add_property("Vec", &TestClass::Vec)
		.add_property("atmVec", &TestClass::atmVec)
		.add_property("AtmPtrVec", &TestClass::atmPtrVec)
		//.add_property("atmVec", &TestClass::getAtomVec)
		
		//.def("__getitem__", a_get)
		//.def("__iter__", iterator<list_int>())
		.def("__iter__", iterator< std::list<int> >())
		.def("__len__", &TestClass::size)
		
		;
	
	/*	
    class_<list_range>("list_range")

        // We can specify data members
        .def("__iter__"
             , range(&list_range::first, &list_range::second))
        ;

    // No runtime tests for this one yet
    class_<list_range2>("list_range2")

        // We can specify member functions returning a non-const reference
        .def("__iter__", range(&list_range2::begin, &list_range2::end))
        ;

    class_<two_lists>("two_lists")

        // We can spcify member functions
        .add_property(
            "primes"
            , range(&two_lists::one_begin, &two_lists::one_end))

        // Prove that we can explicitly specify call policies
        .add_property(
            "evens"
            , range<return_value_policy<copy_non_const_reference> >(
                &two_lists::two_begin, &two_lists::two_end))

        // Prove that we can specify call policies and target
        .add_property(
            "twosies"
            , range<return_value_policy<copy_non_const_reference>, two_lists>(
                // And we can use adaptable function objects when
                // partial specialization is available.
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                two_lists::two_start()
# else
                &two_lists::two_begin
# endif 
                , &two_lists::two_end))
        ;

    class_<list_list>("list_list")
        .def("push_back", push_list_back)
        .def("__iter__", iterator<list_list,return_internal_reference<> >())
        ;
	*/

}

#include "module_tail.cpp"
