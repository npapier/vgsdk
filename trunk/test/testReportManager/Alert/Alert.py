'''
Created on 11 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

import config

class Alert(object):
	'''
	classdocs
	@summary: Interface to generate custom alert
	'''

	def __init__(self):
		'''
		Constructor		
		'''
		self._list = None
		self._link = None
		self._project = None
	
	#Create a simple text Alert
	def createAlert(self, test):
		alert = '- ' + test.getAttribute('name')
		
		if test.getAttribute('alert') == 'error' :
			alert += ' (new error) \r'
		if test.getAttribute('alert') == 'fps' :
			alert += ' (performance decrease by more than '+ str(config.param['highFpsLimit']) +'%/'+ str(config.param['lowFpsLimit']) +'%) \r'		
			
		return alert
	   
	#Send the alert (must be implemented in sub-classes)
	def __call__(self):
		raise NotImplementedError
	
	def initialize(self, alertList, link, project):	
		'''
		Initialize
		@param alertList: list of test which need an alert
		@param link: the link to the report.
		@param project: the project name
		'''
		self._list = alertList
		self._link = link
		self._project = project