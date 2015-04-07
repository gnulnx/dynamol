#!/usr/bin/env python

import os
import sys

os.system("make clean")
print "rm molecule.so lib*"
os.system("rm molecule.so lib*")
os.system("qmake")
os.system("make")
os.system("cp libmolecule.so.so molecule.so")
os.system("cp libmolecule.so.dylib molecule.so")
#os.system("rm -f libmolecule.so* libmolecule.so.dylib")
#os.system("cp molecule.so  ../../Scripts/")
sys.exit(0)

print "Running test.py"

os.system("python test.py")
