#!/usr/bin/env python

from chemutil import *
import os
import sys

inFile = sys.argv[1]
util = ChemUtil()

numMols = util.scanMol2(inFile)
print numMols

index = 0
while index < numMols:
	mol = util.getMol2(inFile, index)
	index = index + 1

	incr = 12
	center = [0, 0, 0]
	for atm in mol.atoms:
		center[0] = center[0] + atm.coords[0]
		center[1] = center[1] + atm.coords[1]
		center[2] = center[2] + atm.coords[2]
		#atm.coords[0] = atm.coords[0] + incr
		#atm.coords[1] = atm.coords[1] + incr
		#atm.coords[2] = atm.coords[2] + incr

		#print atm.coords[1]

		#center[0] = center[0] + atm.coords[0]
		#center[1] = center[1] + atm.coords[1]
		#print center[1]
		#center[2] = center[2] + atm.coords[2]


	for i in [0, 1, 2]:
		print "center["+str(i)+"]: " + str(center[i]/len(mol.atoms))

	print center[0]/len(mol.atoms)
	print center[1]/len(mol.atoms)
	print center[2]/len(mol.atoms)


	print "center[1]: " + str(center[1])

	util.writeSDF("Trans.sdf", mol, 0)	
	

