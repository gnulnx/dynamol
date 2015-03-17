#!/usr/bin/env python

from molview import *
from molecule import *
from LoadMol2 import *
from ReadMolecule import *

import time;
import random

def ChangeColor(r, g, b):
	v = molView()
	v.SetMolColor(r, g, b)



if __name__ == '__main__':
	ChangeColor(1, 0, 1)

	for i in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]:
		print str(i)
		time.sleep(0.5)
		r = random.random()
		g = random.random()
		b = random.random()
		ChangeColor(r, g, b)
