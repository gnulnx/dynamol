#!/usr/bin/env python

from molecule import *
from SdRead import *
from PDBRead import *
import os
import sys

class Reader:

	sdread = False
	pdbread = False
	
	def __init__(self):
		pass

	def scanSDF(self, fileName):
		self.sdread = sdRead(fileName)
		return len( self.sdread.recIndex )

	def getSDF(self, fileName, num):
		if self.sdread:
			return self.sdread.getMol(fileName, num)
		else:
			self.scanSDF(fileName)
			return self.sdread.getMol(fileName, num)

	def scanPDB(self, fileName):
		self.pdbread = PDB(fileName)
		return len(self.pdbread.ModelIndex)

	def getPDBModel(self, fileName, num):
			if self.pdbread:
				return self.pdbread.getMol(fileName, num)
		

if __name__ == '__main__':
	reader = Reader()

	inFile = sys.argv[1]
	numMols = reader.scanSDF(inFile)

	mol = reader.getSDF(inFile, 0)
	for atm in mol.atoms:
		print str(atm.num) + "\t" + atm.symbol

	for bd in mol.bonds:
		fromAtm = bd.fromAtm()
		toAtm = bd.toAtm()
		print str(bd.order) + "\t" + str(bd.num) + "\t" + str(fromAtm.num) + "\t" + str(toAtm.num)

