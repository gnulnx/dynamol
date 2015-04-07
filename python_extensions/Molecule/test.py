#!/usr/bin/env python
#import molecule
from molecule import *

print "Test 1.  Molecule and Atom Object Creation"
m = Mol()
atm1 = m.addAtom(1, 'N1', 0, 0,0, 7)
atm2 = m.addAtom(2, 'C2', 0, 1, 0, 6)
atm3 = m.addAtom(3, 'C3', 0, 0, 1, 6)

print "\n\nTest 2.  Molecule and Atom Object chages"

print "atm1.symbol: " + atm1.symbol
atm1.symbol = "hello"
m.name = "Molecule Has A Test Name"

print "\n\nTest 3.  Using a for i in m.atoms syntax"
for i in m.atoms:
	print str(i.num) + "\t" + i.symbol

print "\n\nTest 4.  Checking atom parent"
atm = m.atoms[0]
par = atm.parent()
print par.name

m2 = Mol()
m2.name = "Molecule 2"

par = m2

par2 = atm.parent()
print par2.name

print "PyObject: " + str(m2.PyObject)
