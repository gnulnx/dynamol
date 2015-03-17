#!/usr/bin/env python

import os
import sys

os.system("make clean")
os.system("rm molview.so")
os.system("qmake")
os.system("make")
os.system("cp libmolview.so.so molview.so")
os.system("cp libmolview.so.dylib molview.so")
os.system("rm -f libmolview.so* libmolview.so.dylib")
os.system("cp molview.so  ../../Scripts/")

print "Running test.py"
os.system("python test.py")
