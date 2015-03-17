#!/usr/bin/env python

import os
import sys


class Check:
	a = []
	def __init__(self):
		self.a = [1, 2, 3, 4, 5]
	def __len__(self):
		return len(self.a)
	def __getitem__(self, i):
		return self.a[i]

if __name__ == '__main__':
	c = Check()
	print len(c)
	print c[2]
