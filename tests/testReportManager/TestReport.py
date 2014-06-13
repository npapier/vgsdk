'''
Created on 22 mai 2009

VGSDK - Copyright (C) 2009, 2010, Maxime Peresson, Nicolas Papier.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson
Author Nicolas Papier

'''

from __future__ import with_statement 
from mako.template import Template
from mako.lookup import TemplateLookup
import os
import shutil
import sys
import Run
import globals
import config
from datetime import datetime

class TestReport(object):
	'''
	classdocs
	@summary: For a XML JUnit file, creates directory, python objects and creates HTML pages.
	'''
	
	#current run path
	extpath = ''

	def __init__(self, document, type = 'normal', deps = [], path = config.param['path']):
		'''
		Constructor
		@param document: the full path of the xml document
		@param type: the rapport type (normal, vgsdk...)
		@param deps: the link of project which this one depend
		@param path: the report path
		@summary: initilaize all the stuff we need to generate a test report
		'''

		self._type = type
		self._deps = deps
		
		self._projet = str.split(document, '.')[0]
		
		#Create the test report directory based on the date/time and copy the xml file into it
		d = datetime.now()
		currentDate = d.strftime('%Y-%m-%d_%Hh%Mm%Ss')
		
		self._path = path + 'projects' + os.sep + self._projet + os.sep + currentDate + os.sep
		
		TestReport.extpath = self._path
		
		self._projectPath = path + 'projects' + os.sep + self._projet + os.sep
		
		if not os.path.exists(self._projectPath):
			print('Creating project folder ' + self._projectPath)
			os.makedirs(self._projectPath)
		
		if os.path.exists(config.param['xmlPath'] + document):
			print('Creating run folder ' + self._path)
			os.makedirs(self._path)
			
			print('Moving XML file from ' + config.param['xmlPath'] + document + ' to ' + self._path + config.param['file'])
			shutil.move(config.param['xmlPath'] + document, self._path + config.param['file'])
			#shutil.copyfile(config.param['xmlPath'] + document, self._path + config.param['file']) #for test purpose
		else :
			print('XML file not found ('+config.param['xmlPath'] + document+')')
			sys.exit(1)
			
		#create the link
		self._link = config.param['link'] + '/projects/' + self._projet + '/' + currentDate + '/index.html'
		
		#Create graph path
		self._graphPath = self._path + 'graph' + os.sep		
		os.makedirs(self._graphPath)
		
		#Parse the XML document and create the Run object
		self._file = config.param['file']
		self._doc = self._path + self._file
		self._run = Run.Run(self._doc)
		
		#Initialize template
		self._mylookup = TemplateLookup(directories=['./templates'])

	
	def generateRootHtml(self):
		'''
		@summary: Generate root HTML file (formerly generate with XSLT)
		'''		
		mytemplate = self._mylookup.get_template('TestRun.html')	
		with open( self._path + 'index.html', 'w' ) as file :
			file.write(mytemplate.render(projet=self._projet, deps=self._deps, run=self._run))
	
	def generateHtml(self):
		'''
		@summary: Generate all HTML test file (one per test)
		'''		
		filename = None
					
		for test in self._run.getTestsList():
			filename = test.getAttribute('name')
			filename = filename.replace('/', '-')
			
			mytemplate = self._mylookup.get_template('Test.html')
				
			with open( self._path + filename+'.html', 'w' ) as file :
				file.write(mytemplate.render(test=test, graphPath=self._graphPath, filename=filename))
				
		
	def generateScreenshotHtml(self):
		'''
		@summary: Generate an HTML page with all screenshot/reference images
		'''		
		mytemplate = self._mylookup.get_template('Images.html')
			
		with open( self._path + 'images.html', 'w' ) as file :
			file.write(mytemplate.render(tests=self._run.getTestsList()))
		
	def moveToLastTest(self):
		'''
		@summary: Move the test report to the "LastTest" directory
		'''		
		lastTest = self._projectPath + 'LastTest/'
		
		if os.path.exists(lastTest):
			shutil.rmtree(lastTest)
			
		shutil.copytree(self._path, lastTest)
		
	def goRsync(self):
		'''
		@summary: Synchronize the test report forlder with orange
		'''
		command = config.param['cygwinPath'] + 'rsync.exe --rsh='+ config.param['cygwinPath'] +'ssh.exe -av --chmod=u=rwX,go=rX ' + config.param['rsyncLocalPath'] + ' ' +  config.param['rsyncDistPath']
		print ("rsync command:%s\n" % command)
		os.system( command )


	def getPath(self):
		return self._path	
	
	def getProjet(self):
		return self._projet	 
	
	def getGraphPath(self):
		return self._graphPath
	
	def getLink(self):
		return self._link