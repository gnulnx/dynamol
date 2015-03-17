#/usr/bin/env python

from molview import *
from molecule import *
from ReadMolecule import *
#import time
#import random

def LoadMol(fileName):
	print "Filename: " + str(fileName)
	View = molView()
	if not View:
		print "View was not initizlised"

	ext = fileName[-3:]
	reader = Reader()
	mol = ""
	if ext == 'sdf' or ext ==  'mol':
		numMols = reader.scanSDF(fileName)
		index = 0;
		while index < numMols:
			mol = reader.getSDF(fileName, 0)
			print "Read mol -?- : " + mol.name
			index = index + 1
			View.Show(mol)
			#time.sleep(0.5)	
	if ext == 'pdb':
		
		numMols = reader.scanPDB(fileName)
		index = 0
		while index < 1:
		#while index < numMols:
			mol = reader.getPDBModel(fileName, index)
			index = index + 1
			
			#raw_input()
		View.Show(mol)
		del(sys.modules['PDBRead'])
		del(sys.modules['ReadMolecule'])
		#raw_input()	

	## This might be good information to save so you can retrive molecules from the file
	#FileOffSets = reader.sdread.recIndex

	#for i in FileOffSets:
	#	print i

	#View.Show(mol)

	return mol

if __name__ == '__main__':
	print "You are in the LoadMol.py main function"
	mol = ""
	if len(sys.argv) > 1:
		
		mol = LoadMol(sys.argv[1])
	else:
		mol = LoadMol("test.sdf")

	print mol.name
	print "Num atoms: " + str(len(mol.atoms))
	print "Num bonds: " + str(len(mol.bonds))
