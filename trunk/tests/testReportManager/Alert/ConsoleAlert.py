'''
Created on 11 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

from Alert import Alert

class ConsoleAlert(Alert):
	'''
	@summary: Print alert on default output
	'''	
	
	def __init__(self):
		'''
		Constructor
		'''
		Alert.__init__(self)  
		
	def __call__(self):	
		err = 'Test with error / problem : \r'
		
		for t in self._list:
			 err += self.createAlert(t)
		
		err += 'Report link : ' + self._link + '\r'
		
		#print on console
		print err