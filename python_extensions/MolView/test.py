#!/urs/bin/env python

from molview import *

m = molView()
value = m.SetMolColor(0,1,0)

if not value:
	print "SetColorTest Pass"
