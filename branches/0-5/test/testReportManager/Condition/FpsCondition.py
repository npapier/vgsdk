'''
Created on 11 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

from Condition import Condition

class FpsCondition(Condition):
	'''
	@summary: Send an alert if it raise the limit. 
	'''
	def __init__(self, highFpsLimit, lowFpsLimit):
		'''
		Constructor
		@param highFpsLimit: the range of fps allowed in percent if fps > 200
		@param lowFpsLimit: the range of fps allowed in percent if fps < 200
		'''
		Condition.__init__(self)	   
		
		self._highLimit = highFpsLimit
		self._lowLimit = lowFpsLimit
		self._currentTest = None
		
#	def shouldTrigger(self):
#		'''
#		@summary: Add an alert if a test has an fps variation
#		'''
#		# For each test in current run
##		for i in self._currentRun.getTestsList():
##			#if it's a performance test
##			if 'Fps' in i.getAttributes():
##				#for each test in last run
##				for j in self._lastRun.getTestsList():
##					#check if it's the same test
##					if j.getAttribute('name') == i.getAttribute('name'):
##						#check the variance between the two test
##						if int(i.getAttribute('Fps')) < int(j.getAttribute('Fps')) - self._limit:
##							i.addAttribute('alert', 'fps')
##							i.addAttribute('fpsAlert', self._limit)
##							i.addAttribute('fpsLast', j.getAttribute('Fps'))
##							self._alert.append(i)  
#
#		map(self.mapCurrent, self._currentRun)
#		return self._alert
	
	
	def mapCurrent(self, t):
		'''
		@param t: a test which fail in current run
		'''
		if 'Fps' in t.getAttributes():
			#save the current test to compare
			self._currentTest = t
			#check all test in last run
			map(self.mapLast, self._lastRun)
	
	
	def mapLast(self, t):
		'''
		@param t: a test which fail in last run
		'''		   
		if t.getAttribute('name') == self._currentTest.getAttribute('name'):
			#check the variance between the two test
			limit = 0
			if self._currentTest.getAttribute('Fps') > 200:
				limit = self._highLimit
			else:
				limit = self._lowLimit
				
			if t.getAttribute('Fps') != None: #if no attribut "Fps" in last test run
				if int(self._currentTest.getAttribute('Fps')) < (int(t.getAttribute('Fps')) - (int(limit) * int(t.getAttribute('Fps')) / 100)):
					self._currentTest.addAttribute('alert', 'fps')
					self._alert.append(self._currentTest)