#!/usr/bin/env python

from iterator_ext import *

x = list_int()

for i in [1, 2, 3, 4, 5]:
	x.push_back(i)

for i in x:
	print i

print "Now starting TestClass"

tc = TestClass()
print "Testing name"
tc.name = "john"
print tc.name
for i in tc.tcList:
	print i


print "Push_Back test"
tc.tcList.push_back(25)
tc.tcList.push_back(26)
for i in tc.tcList:
	print i

print "Testing list while loop"

index = 0
while index < len(tc.tcList):
	#print tc.tcList[index]
	index = index + 1


print "test vector"
tc.Vec.push_back(10.9)
tc.Vec.push_back(21.8)

for i in tc.Vec:
	print i

print tc.Vec[1]

print "Testing X"
vec = XVec()
x = X()
vec.append(x)
for i in vec:
	print i

atm = atom()
AV = vector_atom()
AV.append(atm)
for i in AV:
	print "Hi AV"

print "Trying TestClass stuff"
tc.atmVec.append(atm)
for i in tc.atmVec:
	print "Hello"


tc.AtmPtrVec.append(atm)
for i in tc.AtmPtrVec:
	print "Yo"
