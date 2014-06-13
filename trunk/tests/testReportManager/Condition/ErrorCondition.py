'''
Created on 11 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

from Condition import Condition

class ErrorCondition(Condition):
	'''
	@summary: Add an alert when a test fail and if it was not yet reported.
	'''
	def __init__(self):
		'''
		Constructor
		'''
		Condition.__init__(self)
		
#	def shouldTrigger(self):
#		'''
#		@summary: Add an alert if a test fail
#		'''
#		#browse all test which fail in current run
#		for i in self._currentRun.getErrorsList():
#			diff = True
#			#browse all test which fail in last run
#			for j in self._lastRun.getErrorsList():
#				#check if the test fail also in the last run
#				#if it also fail, we don't alert
#				if j.getAttribute('name') == i.getAttribute('name'):
#					diff = False
#			#if a test don't fail in last run, we add this test for alert
#			if diff == True:
#				i.addAttribute('alert', 'error')
#				self._alert.append(i)  
#
#		#browse all test which fail in current run
#		map(self.mapCurrent, self._currentRun)
#		return self._alert	
	
	def mapCurrent(self, t):
		'''
		@summary: save the name of the test to compare it with test which fail in last run 
		@param t: a test which fail in current run
		'''
		self._diff = True
		self._errorName = t.getAttribute('name')
		
		#browse all test which fail in last run
		map(self.mapLast, self._lastRun)
		if self._diff == True:
			t.addAttribute('alert', 'error')
			self._alert.append(t)
	
	def mapLast(self, t):
		'''
		@summary: check if the test fail also in the last run
				  if it also fail, we don't alert
		@param t: a test which fail in last run
		'''
		if self._errorName == t.getAttribute('name'):
			self._diff = False
			
			
	def initialize(self, stats):
		self._stats = stats
		self._currentRun = self._stats.getRunList()[0].getErrorsList()
		self._lastRun = self._stats.getRunList()[1].getErrorsList()	   