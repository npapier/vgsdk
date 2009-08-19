'''
Created on 29 mai 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

from xml.dom.minidom import * 
import re
import Test
import Testsuite
import config
from Attribute.ImageAttribute import ImageAttribute

class Run(object):
	'''
	classdocs
	@summary:   A run is an execution of the test program
				This class contain all tests of the run
	'''

	def __init__(self, document, lastTest = False, customAttribut = True):
		'''
		Constructor
		@summary: Create the tests list
		@param document: the xml file generate by the test program
		@param lastTest: if we want the run of the "lastTest" folder
		@param customAttribut: if we want to treat custom attributs 
		'''
		
		#contains all testsuites with their testcases
		self._testsuites = []
		
		#contains all testcases, without any order
		self._testsList = []
		self._errorsList = []
	   
		if lastTest != True:
			self._name = re.search(r'(\d{2}-\d{2}-\d{2}_\d{2}h\d{2}m\d{2}s)', document).groups()[0]
		
		self._doc = parse(document)
		self._rootElement = None
		
		self._customAttribut = customAttribut
		
		self.listTests()		
		
		self._totalTime = self.getRootElement().attributes['time'].value
		
	def getRootElement(self):
		'''
		@summary: Get the root element of the xml file
		'''
		
		if self._rootElement == None:
				self._rootElement = self._doc.documentElement
		
		return self._rootElement
	
	def listTests(self):
		'''
		@summary: Create the list of all tests in the test run and create a list of failed test
		'''
		i = 0
		for testsuite in self.getRootElement().getElementsByTagName('testsuite'):
			j = 0
			name = testsuite.attributes['name'].value
			time = testsuite.attributes['time'].value
			self._testsuites.append(Testsuite.Testsuite(name, time))
									
			for test in testsuite.getElementsByTagName('testcase'):
				 if test.nodeType == test.ELEMENT_NODE and test.attributes['status'].value != 'notrun':
					self._testsuites[i].getTestsList().append(Test.Test())
					
					for key in test.attributes.keys():
						if config.listCustomAttribut.has_key(key) and self._customAttribut:
							att = config.listCustomAttribut[key]
							self._testsuites[i].getTestsList()[j].addCustomAttribute(att(key, test.attributes[key].value))
						else:
							self._testsuites[i].getTestsList()[j].addAttribute( key, test.attributes[key].value )
					
					if len(test.getElementsByTagName('failure')) > 0:
						self._testsuites[i].getTestsList()[j].addAttribute( 'failure', test.getElementsByTagName('failure')[0].attributes['message'].value )
						self._testsuites[i].getTestsList()[j].addAttribute( 'failure_code', test.getElementsByTagName('failure')[0].firstChild.wholeText )
						
						self._errorsList.append(self._testsuites[i].getTestsList()[j])
						
					self._testsList.append(self._testsuites[i].getTestsList()[j])
					j += 1
			
			i += 1


	def getTestsuites(self):
		'''
		@return: The tests list
		'''
		return self._testsuites
	
	def getTestsList(self):
		'''
		@return: The tests list
		'''
		return self._testsList  
	
	def getErrorsList(self):
		'''
		@return: The errors tests list
		'''
		return self._errorsList
	
	def getTests(self):
		'''
		@return: number of tests
		'''
		return len(self._testsList)

	def getErrors(self):
		'''
		@return: number of failed tests
		'''		
		return len(self._errorsList)

	def getName(self):
		'''
		@return: the name of the test run
		'''		
		return self._name					
	
	def getSuccesRate(self):
		'''
		@return: the success rate of the run 
		'''
		return 100 - (int(self.getErrors()) * 100 / int(self.getTests()))
	
	def getTime(self):
		return self._totalTime