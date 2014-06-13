'''
Created on 11 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

from Condition import Condition

class RenderPerformanceCondition(Condition):
	'''
	@summary: Send an alert if it raise the limit. 
	'''
	def __init__(self, limit):
		'''
		Constructor
		@param highFpsLimit: the range of fps allowed in percent if fps > 200
		@param lowFpsLimit: the range of fps allowed in percent if fps < 200
		'''
		Condition.__init__(self)	   
		
		self._limit = limit
		self._currentTest = None
	
	
	def mapCurrent(self, t):
		'''
		@param t: a test which fail in current run
		'''
		if 'AverageRenderDuration' in t.getAttributes():
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
			if t.getAttribute('AverageRenderDuration') != None: #if no attribut "Fps" in last test run
				test = (float(t.getAttribute('AverageRenderDuration')) + (int(self._limit) * float(t.getAttribute('AverageRenderDuration')) / 100))
				if float(self._currentTest.getAttribute('AverageRenderDuration')) > test:
					self._currentTest.addAttribute('alert', 'render')
					self._alert.append(self._currentTest)
					