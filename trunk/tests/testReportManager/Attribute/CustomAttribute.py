'''
Created on 30 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

class CustomAttribute(object):
	'''
	@summary: interface to create custom attribute object
	In config.py, set listCustomAttribut = {'attributeName' : attributeClass }
	'''


	def __init__(self, name, attribute):
		'''
		Constructor
		@param name: attributte name
		@param attribute: Attribute value
		'''
		self._name = name
		self._attribute = attribute
		
		#if we want to display it in test report
		self._display = True
		
	def getHtml(self):
		'''
		@summary: return a Html tab line for the attribute
		'''
		raise NotImplementedError
		
	def getDisplay(self):
		'''
		@summary: return True if the attribute have to be displayed like other attribute
		'''
		return self._display
	
	def getName(self):
		'''
		@summary: get the attribute name
		'''
		return self._name
	
	def getAttribute(self):
		'''
		@summary: get the attribute value
		'''
		return self._attribute  