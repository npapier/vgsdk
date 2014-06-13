'''
Created on 29 mai 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

import globals

class Test(object):
	'''
	classdocs
	@summary: A test. Contain all atttribut of the test.
	'''


	def __init__(self):
		self._attributes = {}
		self._customAttributes = []
	
	def addAttribute(self, key, value):
		'''
		@summary: add an attribute
		@param key: the attribut key
		@param value: the attribut value 
		'''		
		self._attributes[key] = value
	
	def addCustomAttribute(self, attribute):
		'''
		@summary: add a custom attribute
		@param key: the custom attribut object
		'''		   
		self._customAttributes.append(attribute)

	def getAttributes(self):
		'''
		@summary: get the attributes list
		'''		
		return self._attributes
	
	def getCustomAttributes(self):
		'''
		@summary: get the custom attributes list
		'''		
		return self._customAttributes
	
	def getAttribute(self, key):
		if self._attributes.has_key(key):
			return self._attributes[key]
		else:
			return None

	def equals(self, t):
		'''
		@summary: Check if a test is this one (based on different parameters define in global)
		'''		
		for att in t.getAttributes():
			#@todo: faire l'inverse au niveau des attributs (not in au lieu de in)
			if globals.testIdentifier.count(att) > 0:
				if att not in self._attributes:
					return False
				elif t.getAttribute(att) != self.getAttribute(att):
					return False
		
		return True