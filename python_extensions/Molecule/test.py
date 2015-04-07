#!/usr/bin/env python
#import molecule
from molecule import *
from ctypes import c_int, addressof

print "Test 1.  Molecule and Atom Object Creation"
m = Mol()
atm1 = m.addAtom(1, 'N1', 0, 0,0, 7)
atm2 = m.addAtom(2, 'C2', 0, 1, 0, 6)
atm3 = m.addAtom(3, 'C3', 0, 0, 1, 6)

#for a in m.atoms:
#    print "a: ", a, a.symbol, a.parent()
print "-------------------------------------------"
print "m.name: ", m.name
print "atm1: %s, %s "%( atm1.symbol,  atm1.parent())
print "atm2: %s, %s "%(atm2.symbol,  atm2.parent())
print "atm3: %s, %s"%(atm3.symbol,  atm3.parent())
raw_input()
atm = m.atoms[0]
print "atm: ", atm, atm.parent(), m.atoms[0]


print "\n\nTest 2.  Molecule and Atom Object chages"

print "atm1.symbol: " + atm1.symbol
atm1.symbol = "hello"
m.name = "Molecule Has A Test Name"

#print "\n\nTest 3.  Using a for i in m.atoms syntax"
#for i in m.atoms:
#	print str(i.num) + "\t" + i.symbol

print "\n\nTest 4.  Checking atom parent"
atm = m.atoms[0]
par = atm.parent()
print "par: ", par
raw_input()

m2 = Mol()
m2.name = "Molecule 2"

par = m2

par2 = atm.parent()
print par2.name

print "PyObject: " + str(m2.PyObject)
