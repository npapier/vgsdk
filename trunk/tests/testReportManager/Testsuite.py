'''
Created on 22 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

class Testsuite(object):
	'''
	classdocs
	@summary: A test suite. Contain a list of test
	'''


	def __init__(self, name, time):
		'''
		Constructor
		@param name: testsuite name
		@param time: testsuite duration
		'''
		self._name = name
		self._time = time
		
		self._testsList = []
		
	def getTestsList(self):
		return self._testsList
	
	def getName(self):
		return self._name
	
	def getTime(self):
		return self._time