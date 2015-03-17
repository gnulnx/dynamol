#!/usr/bin/env python

from molecule import *


class PDB:
	def __init__(self, fileName):
		f = open(fileName, 'r')
		self.ModelIndex = []
		self.fileName = fileName
		#self.num = 0
		while 1:
			line = f.readline().rstrip()
			if not line:
				break

			if line[:5] == "MODEL":
				pos = f.tell()
				self.ModelIndex.append( pos )
				print "Found a Model: " + str(len(self.ModelIndex)) +"\t" + str(pos)
		f.close()
	
		if len(self.ModelIndex) == 0:
			f = open(fileName, 'r')
			prevPos = 0
			while 1:
				line = f.readline().rstrip()
				if not line:
					break
				if line[:4] == "ATOM":	
					self.ModelIndex.append(prevPos)
					break
				pos = f.tell()

		f.close()
		if len(self.ModelIndex) == 0:
			print "Is this a PDB File???"				

	def getMol(self, fileName, pos):
		
		offset = self.ModelIndex[pos]
		f = open(fileName, 'r')
		#header = f.readline().split()
		#name = header[-1]
		
		f.seek(offset)

		mol = Mol()
		mol.name = "Test"
		ChainDict = {}
		ResDict = {}
		AtmNum = 1
		NList = []
		CList = []
		while 1:
			line = f.readline().rstrip()
			if line[:6] == "ENDMDL" or not line:
				print "End of Model Reached"
				break
			if line[:4] == "ATOM":
				PDBNum = line[6:11]
				PdbName = line[12:16]
				AltLocCode = line[16:17]
				ResCode	 = line[17:20]
				ChainID	 = line[21:22]
				ResSeqNum = line[22:27]
				InsertCode = line[26:27]
				X = line[30:38]
				Y = line[38:46]
				Z = line[46:54]
				Occupancy = line[54:60]
				BValue = line[60:66]
				FootnoteNum = line[67:70]
				AtmSym = line[77:78]
				atm = mol.addAtom(int(AtmNum), AtmSym, float(X), float(Y), float(Z), -1)

				AtmNum = AtmNum + 1
				atm.ResCode = ResCode
				atm.ChainID = ChainID
				atm.PdbName = PdbName
				atm.BValue = BValue
				atm.PDBNum = PDBNum
				
				if PdbName == ' N  ':
					NList.append([int(ResSeqNum), ChainID, PdbName, atm])
				if PdbName == ' C  ':
					CList.append([int(ResSeqNum), ChainID, PdbName, atm])

				if not ResDict.has_key(ResSeqNum+ChainID):
					ResDict[ResSeqNum+ChainID] = [atm]
				else:
					ResDict[ResSeqNum+ChainID].append(atm)

				if not ChainDict.has_key(ChainID):
					ChainDict[ChainID] = [ResDict]
				
				
		self.BuildConnectionTable(mol, ResDict, CList, NList)
		CList.sort()
		NList.sort()
		return mol

	def BuildConnectionTable(self, mol, ResDict, CList, NList):
		keys = ResDict.keys()
		keys.sort()
		BondNum = 1
		for i in keys:
			ResNum = i
			Atoms = ResDict[i]
			ResCode = ResDict[i][0].ResCode
			AtomDict = {}
			for atm in Atoms:
				AtomDict[atm.PdbName] = atm

############# All Residues				
			if AtomDict.has_key(" N  ") and AtomDict.has_key(" CA "):
				bd = mol.addBond(BondNum, AtomDict[" N  "].num, AtomDict[" CA "].num, 1)
				BondNum = BondNum + 1
				if AtomDict.has_key(" H  "):
					bd = mol.addBond(BondNum, AtomDict[" N  "].num, AtomDict[" H  "].num, 1)
					BondNum = BondNum + 1
			if AtomDict.has_key(" CA ") and AtomDict.has_key(" C  "):
				bd = mol.addBond(BondNum, AtomDict[" CA "].num, AtomDict[" C  "].num, 1)
				BondNum = BondNum + 1
				if AtomDict.has_key(" HA "):
					bd = mol.addBond(BondNum, AtomDict[" CA "].num, AtomDict[" HA "].num, 1)
					BondNum = BondNum + 1
				if AtomDict.has_key(" O  "):
					bd = mol.addBond(BondNum, AtomDict[" C  "].num, AtomDict[" O  "].num, 2)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" CB "):
					bd = mol.addBond(BondNum, AtomDict[" CA "].num, AtomDict[" CB "].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HB "):
						bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" HB "].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" HB2"):
						bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" HB2"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" HB3"):
						bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" HB3"].num, 1)
						BondNum =  BondNum + 1

					if AtomDict.has_key(" OG "):
						bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" OG "].num, 1)
						BondNum =  BondNum + 1

					if AtomDict.has_key(" CG "):
						bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" CG "].num, 1)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" HG "):
							bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" HG "].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" HG1"):
							bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" HG1"].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" HG2"):
							bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" HG2"].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" HG3"):
							bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" HG3"].num, 1)
							BondNum =  BondNum + 1
########## RESIDUE SPECIFIC
			if ResCode == "GLY":
				if AtomDict.has_key(" CA "):
					if AtomDict.has_key(" HA2"):
						bd = mol.addBond(BondNum, AtomDict[" CA "].num, AtomDict[" HA2"].num, 1)	
						BondNum =  BondNum + 1
					if AtomDict.has_key(" HA3"):
						bd = mol.addBond(BondNum, AtomDict[" CA "].num, AtomDict[" HA3"].num, 1)
 						BondNum =  BondNum + 1
				
			if ResCode == "ALA":
				if AtomDict.has_key(" CA "):
					if AtomDict.has_key(" HA "):
						bd = mol.addBond(BondNum, AtomDict[" CA "].num, AtomDict[" HA "].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" CB "):
						bd = mol.addBond(BondNum, AtomDict[" CA "].num, AtomDict[" CB "].num, 1)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" HB1"):
							bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" HB1"].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" HB2"):
							bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" HB2"].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" HB3"):
							bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" HB3"].num, 1)
							BondNum =  BondNum + 1

			if ResCode == "PHE" or ResCode == "TYR":
				if AtomDict.has_key(" CG "):
					if AtomDict.has_key(" CD1"):
						bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD1"].num, 2)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" CE1"):
							bd = mol.addBond(BondNum, AtomDict[" CD1"].num, AtomDict[" CE1"].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" HD1"):
							bd = mol.addBond(BondNum, AtomDict[" CD1"].num, AtomDict[" HD1"].num, 1)
							BondNum =  BondNum + 1
					if AtomDict.has_key(" CD2"):
						bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD2"].num, 1)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" CE2"):
							bd = mol.addBond(BondNum, AtomDict[" CD2"].num, AtomDict[" CE2"].num, 2)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" HD2"):
							bd = mol.addBond(BondNum, AtomDict[" CD2"].num, AtomDict[" HD2"].num, 1)
							BondNum =  BondNum + 1
				if AtomDict.has_key(" CZ "):
					if AtomDict.has_key(" HZ "):
						bd = mol.addBond(BondNum, AtomDict[" CZ "].num, AtomDict[" HZ "].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" CE1"):
						bd = mol.addBond(BondNum, AtomDict[" CZ "].num, AtomDict[" CE1"].num, 2)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" HE1"):
							bd = mol.addBond(BondNum, AtomDict[" CE1"].num, AtomDict[" HE1"].num, 1)
							BondNum =  BondNum + 1
					if AtomDict.has_key(" CE2"):
						bd = mol.addBond(BondNum, AtomDict[" CZ "].num, AtomDict[" CE2"].num, 1)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" HE2"):
							bd = mol.addBond(BondNum, AtomDict[" CE2"].num, AtomDict[" HE2"].num, 1)
							BondNum =  BondNum + 1
					if AtomDict.has_key(" OH "):
						bd = mol.addBond(BondNum, AtomDict[" CZ "].num, AtomDict[" OH "].num, 1)
						BondNum =  BondNum + 1 
						if AtomDict.has_key(" HH "):
							bd = mol.addBond(BondNum, AtomDict[" OH "].num, AtomDict[" HH "].num, 1)
							BondNum =  BondNum + 1
				
			if ResCode == "ARG" or ResCode == "LYS":
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" CD "):	
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD "].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HD1"):
						bd = mol.addBond(BondNum, AtomDict[" CD "].num, AtomDict[" HD1"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" HD2"):
						bd = mol.addBond(BondNum, AtomDict[" CD "].num, AtomDict[" HD2"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" NE "):
						bd = mol.addBond(BondNum, AtomDict[" CD "].num, AtomDict[" NE "].num, 1)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" HE "):
							bd = mol.addBond(BondNum, AtomDict[" NE "].num, AtomDict[" HE "].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" CZ "):
							bd = mol.addBond(BondNum, AtomDict[" NE "].num, AtomDict[" CZ "].num, 2)	
							BondNum =  BondNum + 1
							if AtomDict.has_key(" NH1"):
								bd = mol.addBond(BondNum, AtomDict[" CZ "].num, AtomDict[" NH1"].num, 1)
								BondNum =  BondNum + 1
								if AtomDict.has_key("HH11"):
									bd = mol.addBond(BondNum, AtomDict[" NH1"].num, AtomDict["HH11"].num, 1)
									BondNum =  BondNum + 1
								if AtomDict.has_key("HH12"):
									bd = mol.addBond(BondNum, AtomDict[" NH1"].num, AtomDict["HH12"].num, 1)
									BondNum =  BondNum + 1
							if AtomDict.has_key(" NH2"):
								bd = mol.addBond(BondNum, AtomDict[" CZ "].num, AtomDict[" NH2"].num, 1)
								BondNum =  BondNum + 1
								if AtomDict.has_key("HH21"):
									bd = mol.addBond(BondNum, AtomDict[" NH2"].num, AtomDict["HH21"].num, 1)
									BondNum =  BondNum + 1
								if AtomDict.has_key("HH22"):
									bd = mol.addBond(BondNum, AtomDict[" NH2"].num, AtomDict["HH22"].num, 1)	
									BondNum =  BondNum + 1
					
					if AtomDict.has_key(" CE "):
						bd = mol.addBond(BondNum, AtomDict[" CD "].num, AtomDict[" CE "].num, 1)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" HE2"):
							bd = mol.addBond(BondNum, AtomDict[" CE "].num, AtomDict[" HE2"].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" HE3"):
							bd = mol.addBond(BondNum, AtomDict[" CE "].num, AtomDict[" HE3"].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key(" NZ "):
							bd = mol.addBond(BondNum, AtomDict[" CE "].num, AtomDict[" NZ "].num, 1)
							BondNum =  BondNum + 1
							if AtomDict.has_key(" HZ1"):
								bd = mol.addBond(BondNum, AtomDict[" NZ "].num, AtomDict[" HZ1"].num, 1)
								BondNum =  BondNum + 1
							if AtomDict.has_key(" HZ2"):
								bd = mol.addBond(BondNum, AtomDict[" NZ "].num, AtomDict[" HZ2"].num, 1)
								BondNum =  BondNum + 1
							if AtomDict.has_key(" HZ3"):
								bd = mol.addBond(BondNum, AtomDict[" NZ "].num, AtomDict[" HZ3"].num, 1)
								BondNum =  BondNum + 1
			
			if ResCode == "TRP":
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" CD1"):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD1"].num, 2)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HD1"):
						bd = mol.addBond(BondNum, AtomDict[" HD1"].num, AtomDict[" CD1"].num, 1)
						BondNum =  BondNum + 1
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" CD2"):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD2"].num, 1)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" NE1") and AtomDict.has_key(" CD1"):
					bd = mol.addBond(BondNum, AtomDict[" NE1"].num, AtomDict[" CD1"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HE1"):
						bd = mol.addBond(BondNum, AtomDict[" NE1"].num, AtomDict[" HE1"].num, 1)
						BondNum =  BondNum + 1
				if AtomDict.has_key(" NE1") and AtomDict.has_key(" CE2"):
					bd = mol.addBond(BondNum, AtomDict[" NE1"].num, AtomDict[" CE2"].num, 1)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" HE3") and AtomDict.has_key(" CE3"):
					bd = mol.addBond(BondNum, AtomDict[" HE3"].num, AtomDict[" CE3"].num, 1)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" CD2") and AtomDict.has_key(" CE2"):
					bd = mol.addBond(BondNum, AtomDict[" CD2"].num, AtomDict[" CE2"].num, 2)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" CZ2") and AtomDict.has_key(" CE2"):
					bd = mol.addBond(BondNum, AtomDict[" CZ2"].num, AtomDict[" CE2"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HZ2"):
						bd = mol.addBond(BondNum, AtomDict[" CZ2"].num, AtomDict[" HZ2"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" CH2"):
						bd = mol.addBond(BondNum, AtomDict[" CZ2"].num, AtomDict[" CH2"].num, 2)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" HH2"):
							bd = mol.addBond(BondNum, AtomDict[" HH2"].num, AtomDict[" CH2"].num, 1)
							BondNum =  BondNum + 1
				if AtomDict.has_key(" CD2") and AtomDict.has_key(" CE3"):
					bd = mol.addBond(BondNum, AtomDict[" CD2"].num, AtomDict[" CE3"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" CZ3"):
						bd = mol.addBond(BondNum, AtomDict[" CZ3"].num, AtomDict[" CE3"].num, 2)
						BondNum =  BondNum + 1
						if AtomDict.has_key(" HZ3"):
							bd = mol.addBond(BondNum, AtomDict[" CZ3"].num, AtomDict[" HZ3"].num, 1)
						if AtomDict.has_key(" CH2"):
							bd = mol.addBond(BondNum, AtomDict[" CZ3"].num, AtomDict[" CH2"].num, 1)
							BondNum =  BondNum + 1
			
			if ResCode == "GLN":
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" CD "):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD "].num, 1)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" OE1") and AtomDict.has_key(" CD "):
					bd = mol.addBond(BondNum, AtomDict[" OE1"].num, AtomDict[" CD "].num, 2)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" NE2") and AtomDict.has_key(" CD "):
					bd = mol.addBond(BondNum, AtomDict[" NE2"].num, AtomDict[" CD "].num, 1)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" NE2") and AtomDict.has_key("HE21"):
					bd = mol.addBond(BondNum, AtomDict[" NE2"].num, AtomDict["HE21"].num, 1)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" NE2") and AtomDict.has_key("HE22"):
					bd = mol.addBond(BondNum, AtomDict[" NE2"].num, AtomDict["HE22"].num, 1)
					BondNum =  BondNum + 1
				
			if ResCode == "ASN":
				if AtomDict.has_key(" OD1") and AtomDict.has_key(" CG "):	
					bd = mol.addBond(BondNum, AtomDict[" OD1"].num, AtomDict[" CG "].num, 2)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" ND2") and AtomDict.has_key(" CG "):
					bd = mol.addBond(BondNum, AtomDict[" ND2"].num, AtomDict[" CG "].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key("HD21"):
						bd = mol.addBond(BondNum, AtomDict[" ND2"].num, AtomDict["HD21"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HD22"):
						bd = mol.addBond(BondNum, AtomDict[" ND2"].num, AtomDict["HD22"].num, 1)
						BondNum =  BondNum + 1

			if ResCode == "GLU":
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" CD "):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD "].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" OE1"):
						bd = mol.addBond(BondNum, AtomDict[" OE1"].num, AtomDict[" CD "].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" OE2"):
						bd = mol.addBond(BondNum, AtomDict[" OE2"].num, AtomDict[" CD "].num, 1)
						BondNum =  BondNum + 1

			if ResCode == "ASP":
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" OD1"):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" OD1"].num, 1)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" OD2"):		
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" OD2"].num, 2)
					BondNum =  BondNum + 1

			if ResCode == "SER":
				if AtomDict.has_key(" CB ") and AtomDict.has_key(" OG "):
					bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" OG "].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HG "):
						bd = mol.addBond(BondNum, AtomDict[" HG "].num, AtomDict[" OG "].num, 1)
						BondNum =  BondNum + 1

			if ResCode == "MET":
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" SD "):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" SD "].num, 1)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" CE ") and AtomDict.has_key(" SD "):
					bd = mol.addBond(BondNum, AtomDict[" CE "].num, AtomDict[" SD "].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HE1"):
						bd = mol.addBond(BondNum, AtomDict[" CE "].num, AtomDict[" HE1"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" HE2"):
						bd = mol.addBond(BondNum, AtomDict[" CE "].num, AtomDict[" HE2"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" HE3"):
						bd = mol.addBond(BondNum, AtomDict[" CE "].num, AtomDict[" HE3"].num, 1)
						BondNum =  BondNum + 1
			
			if ResCode == "THR":
				if AtomDict.has_key(" CG2"):
					if AtomDict.has_key("HG21"):
						bd = mol.addBond(BondNum, AtomDict[" CG2"].num, AtomDict["HG21"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HG22"):
						bd = mol.addBond(BondNum, AtomDict[" CG2"].num, AtomDict["HG22"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HG23"):
						bd = mol.addBond(BondNum, AtomDict[" CG2"].num, AtomDict["HG23"].num, 1)
						BondNum =  BondNum + 1
				if AtomDict.has_key(" CB ") and AtomDict.has_key(" OG1"):
					bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" OG1"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HG1"):
						bd = mol.addBond(BondNum, AtomDict[" HG1"].num, AtomDict[" OG1"].num, 1)
						BondNum =  BondNum + 1
				if AtomDict.has_key(" CB ") and AtomDict.has_key(" CG2"):
					bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" CG2"].num, 1)
					BondNum =  BondNum + 1
			
			if ResCode == "LEU":
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" CD1"):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD1"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key("HD11"):
						bd = mol.addBond(BondNum, AtomDict[" CD1"].num, AtomDict["HD11"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HD12"):
						bd = mol.addBond(BondNum, AtomDict[" CD1"].num, AtomDict["HD12"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HD13"):
						bd = mol.addBond(BondNum, AtomDict[" CD1"].num, AtomDict["HD13"].num, 1)
						BondNum =  BondNum + 1
						
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" CD2"):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD2"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key("HD21"):
						bd = mol.addBond(BondNum, AtomDict[" CD2"].num, AtomDict["HD21"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HD22"):
						bd = mol.addBond(BondNum, AtomDict[" CD2"].num, AtomDict["HD22"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HD23"):
						bd = mol.addBond(BondNum, AtomDict[" CD2"].num, AtomDict["HD23"].num, 1)
						BondNum =  BondNum + 1
			
			if ResCode == "ILE":
				if AtomDict.has_key(" CB ") and AtomDict.has_key(" CG1"):
					bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" CG1"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key("HG12"):
						bd = mol.addBond(BondNum, AtomDict[" CG1"].num, AtomDict["HG12"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HG13"):
						bd = mol.addBond(BondNum, AtomDict[" CG1"].num, AtomDict["HG13"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" CD1"):
						bd = mol.addBond(BondNum, AtomDict[" CG1"].num, AtomDict[" CD1"].num, 1)
						BondNum =  BondNum + 1
						if AtomDict.has_key("HD11"):
							bd = mol.addBond(BondNum, AtomDict["HD11"].num, AtomDict[" CD1"].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key("HD12"):
							bd = mol.addBond(BondNum, AtomDict["HD12"].num, AtomDict[" CD1"].num, 1)
							BondNum =  BondNum + 1
						if AtomDict.has_key("HD13"):
							bd = mol.addBond(BondNum, AtomDict["HD13"].num, AtomDict[" CD1"].num, 1)
							BondNum =  BondNum + 1
				if AtomDict.has_key(" CB ") and AtomDict.has_key(" CG2"):
					bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" CG2"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key("HG21"):
						bd = mol.addBond(BondNum, AtomDict[" CG2"].num, AtomDict["HG21"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HG22"):
						bd = mol.addBond(BondNum, AtomDict[" CG2"].num, AtomDict["HG22"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HG23"):
						bd = mol.addBond(BondNum, AtomDict[" CG2"].num, AtomDict["HG23"].num, 1)
						BondNum =  BondNum + 1
			
			if ResCode == "VAL":
				if AtomDict.has_key(" CB ") and AtomDict.has_key(" CG1"):
					bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" CG1"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key("HG11"):
						bd = mol.addBond(BondNum, AtomDict["HG11"].num, AtomDict[" CG1"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HG12"):
						bd = mol.addBond(BondNum, AtomDict["HG12"].num, AtomDict[" CG1"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HG13"):
						bd = mol.addBond(BondNum, AtomDict["HG13"].num, AtomDict[" CG1"].num, 1)
						BondNum =  BondNum + 1
				if AtomDict.has_key(" CB ") and AtomDict.has_key(" CG2"):
					bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" CG2"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key("HG21"):
						bd = mol.addBond(BondNum, AtomDict[" CG2"].num, AtomDict["HG21"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HG22"):
						bd = mol.addBond(BondNum, AtomDict[" CG2"].num, AtomDict["HG22"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key("HG23"):
						bd = mol.addBond(BondNum, AtomDict[" CG2"].num, AtomDict["HG23"].num, 1)
 						BondNum =  BondNum + 1
			
			if ResCode == "PRO":
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" CD "):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD "].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HD2"):
						bd = mol.addBond(BondNum, AtomDict[" HD2"].num, AtomDict[" CD "].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" HD3"):
						bd = mol.addBond(BondNum, AtomDict[" HD3"].num, AtomDict[" CD "].num, 1)
						BondNum =  BondNum + 1
				if AtomDict.has_key(" N  ") and AtomDict.has_key(" CD "):
					bd = mol.addBond(BondNum, AtomDict[" N  "].num, AtomDict[" CD "].num, 1)
					BondNum =  BondNum + 1
			
			if ResCode == "HIS":
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" CD2"):		
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" CD2"].num, 2)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" CG ") and AtomDict.has_key(" ND1"):
					bd = mol.addBond(BondNum, AtomDict[" CG "].num, AtomDict[" ND1"].num, 1)
					BondNum =  BondNum + 1
				if AtomDict.has_key(" CE1") and AtomDict.has_key(" ND1"):
					bd = mol.addBond(BondNum, AtomDict[" CE1"].num, AtomDict[" ND1"].num, 2)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HE1"):
						bd = mol.addBond(BondNum, AtomDict[" CE1"].num, AtomDict[" HE1"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" HD1"):
						bd = mol.addBond(BondNum, AtomDict[" HD1"].num, AtomDict[" ND1"].num, 1)
						BondNum =  BondNum + 1
				if AtomDict.has_key(" CD2") and AtomDict.has_key(" NE2"):
					bd = mol.addBond(BondNum, AtomDict[" CD2"].num, AtomDict[" NE2"].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HD2"):
						bd = mol.addBond(BondNum, AtomDict[" CD2"].num, AtomDict[" HD2"].num, 1)
						BondNum =  BondNum + 1
					if AtomDict.has_key(" HE2"):
						bd = mol.addBond(BondNum, AtomDict[" NE2"].num, AtomDict[" HE2"].num, 1)
						BondNum =  BondNum + 1
				if AtomDict.has_key(" CE1") and AtomDict.has_key(" NE2"):
					bd = mol.addBond(BondNum, AtomDict[" CE1"].num, AtomDict[" NE2"].num, 1)
					BondNum =  BondNum + 1
			
			if ResCode == "CYS":
				if AtomDict.has_key(" CB ") and AtomDict.has_key(" SG "):
					bd = mol.addBond(BondNum, AtomDict[" CB "].num, AtomDict[" SG "].num, 1)
					BondNum =  BondNum + 1
					if AtomDict.has_key(" HG "):
						bd = mol.addBond(BondNum, AtomDict[" HG "].num, AtomDict[" SG "].num, 1)
						BondNum =  BondNum + 1

########## CONNECT C-N
		index = 0
		while index < len(CList)-1:
			if CList[index][1] == NList[index+1][1]:
				mol.addBond(BondNum, CList[index][3].num, NList[index+1][3].num, 1)
				BondNum =  BondNum + 1
			#else:
				#print "Different Chains!: " + str(CList[index][1]) + str(NList[index+1][1])
				#raw_input()

			index = index + 1

		
			
if __name__ == '__main__':
	fileName = '/home/jfurr/BCL-XL/PDB/2PON.pdb'
	pdbread = PDB(fileName)

	numMols = len(pdbread.ModelIndex)
	print "Total Models: " + str(numMols)
	
	index = 0
	while index < numMols:
		pdbread.getMol(fileName, index)
		index = index + 1


