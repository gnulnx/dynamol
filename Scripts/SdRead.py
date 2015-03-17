#!/usr/bin/env python

from molecule import *

class sdRead:
	
	#num = 0
	#recIndex = [ 0 ]

	# the init function scans the SD file.  the number of records
	# is determined by len( recIndex )
	# A File handle is left open (It's close din __del__
	def __init__(self, fileName):
		self.f = open(fileName, "rb")
		self.recIndex = [ 0 ]
		self.num = 0
		count = 2
		while 1:
			line = self.f.readline()
			if not line:
				break
			if line[:4] == "$$$$":
				pos = self.f.tell()
				if self.f.readline():
					self.recIndex.append( pos )
					count = count + 1

	# close the file handle
	def __del__(self):
		self.f.close()

	# Read a mol from an sd file.  
	# {pos} must be less than the number of records
	def getMol(self, fileName, pos):
		index = self.recIndex[ pos ]
		self.f.seek( index )	
		
		# Read Header Block
		name = self.f.readline().rstrip()
		mol = Mol()
		mol.Props = {}
		mol.name = name

		vender_id = self.f.readline().rstrip()
		blank = self.f.readline().rstrip()
		numLine = self.f.readline().rstrip()

		atmNum = int( numLine[:3] )
		bdNum = int( numLine[3:6] )
		

		## Read Atom Block
		count = 0
		while count < atmNum:
			atmLine = self.f.readline().rstrip()
			if len( atmLine ) > 34:
				x = float( atmLine[:10] )
				y = float( atmLine[10:20] )
				z = float( atmLine[20:30] )
				sym = atmLine[31:34]
				charge = atmLine[36:39]
			if len( atmLine) > 48:
				parity = atmLine[39:42]
				hCount = atmLine[42:45]
				stereo = atmLine[45:48]
		
			count = count + 1
			atm = mol.addAtom(count, sym, x, y, z, -1)
			if len(atmLine) > 48:
				atm.chiralFlag = int(parity)

			atm.formalCharge = int(charge)
		
		## Read Bond Block
		count = 0
		while count < bdNum:
			bdLine = self.f.readline()
			fromNum = int( bdLine[:3] )
			toNum = int( bdLine[3:6] )
			order = int( bdLine[6:9] )

			count = count + 1
			mol.addBond(count, fromNum, toNum, order)

		## Need to support reading properties
		while 1:
			line = self.f.readline()
			if not line:
				break

			if line[:4] == "$$$$":
				break

			if line[:3] == "> <":
				line = ">  <" + line[3:]
			### THE SECTION FOR THE 3 Space might not work right now
			if line[:4] == ">  <":
		
				name =  line[4:].split(">")[0]
				value = ""
				while line[:4] != "":	
					line = self.f.readline()[:-1]
					if not line:
						break
					value = value + line + "\n"

				value = value.rstrip()
				mol.Props[name] = value

		return mol

	def writeMol(self, fileName, mol, append=1):
		f = ""
		if append:
			f = open(fileName, "a")
		else:
			f = open(fileName, "w")

		f.write( mol.name + "\n" )
		f.write( mol.vender_id + "\n")
		f.write( "\n" )
		f.write( "%(atmNum)3d%(bdNum)3d 0  0  0  0  0  0  0  0999 V2000\n" % {'atmNum':len(mol.atoms), 'bdNum':len(mol.bonds)} )

		for atm in mol.atoms:
			x = atm.coords[0]
			y = atm.coords[1]
			z = atm.coords[2]

			atm_line = "%(x)10f%(y)10f%(z)10f %(sym)3s 0  0  %(chiral)1i  %(charge)1i  0  0  0  0  0  0  0  0\n" % {'x':x, 'y':y, 'z':z, 'sym':atm.symbol, 'chiral':atm.chiralFlag, 'charge':atm.formalCharge}
			f.write( atm_line )		

		for bd in mol.bonds:
			order = bd.order
			fromNum = bd.fromNum
			toNum = bd.toNum
	
			bd_line = "%(from)3d%(to)3d%(order)3i  0  0  0  0\n" % {'from':fromNum, 'to':toNum, 'order':order}
			f.write( bd_line )
			
		f.write("M  END\n")
		## Code to Write properties out
		f.write("$$$$\n")

