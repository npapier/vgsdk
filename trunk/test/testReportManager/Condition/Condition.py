'''
Created on 11 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''


class Condition(object):
	'''
	@summary: Abstract class. Must be reimplemented to define some alert conditions.
	'''
	def __init__(self):
		'''
		Constructor
		'''  
		# contain tests which need an alert
		self._alert = []
		self._stats = None
		self._currentRun = None
		self._lastRun = None
			
	def shouldTrigger(self):
		'''
		@summary: called to create alert list. Loop on the current tests list.
		@return: the list of tests which need an alert
		'''
		map(self.mapCurrent, self._currentRun)
		return self._alert
	
	def mapCurrent(self, t):
		'''
		@param t: a test from _currentTest list.
		@summary: This function is called for each test of the _currentRun list.
				  Use it like a filter to determine which test may need an alert. Save information about this test.
				  Call mapLast with _lastRun list to compare current test (if it may need an alert) with last test.
		@see: FpsCondition.py
		'''
		raise NotImplementedError
		
	def mapLast(self, t):
		'''
		@param t: a test from _lastTest list. 
		@summary: This function is called for each test of the _lastRun list.
				  Compare the currentTest (saved in mapCurrent) with the same test (executed last time) to determine if it needs an alert.
				  Add test to _alert[] if needed.
		@see: FpsCondition.py
		'''		
		raise NotImplementedError
	
	def initialize(self, stats):
		'''
		@param stats: stats object with different lists (current tests list, last tests list, current error list, etc..)
		@summary: Initialize the condition with the different list.
				  Reimplement it if you want differents lists.  
		'''
		self._stats = stats
		self._currentRun = self._stats.getRunList()[0].getTestsList()
		self._lastRun = self._stats.getRunList()[1].getTestsList()