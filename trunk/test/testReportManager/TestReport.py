'''
Created on 22 mai 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

import os
import shutil
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
		self._path = path + 'projects' + os.sep + self._projet + os.sep + d.strftime('%m-%d-%y_%H%M%S') + os.sep
		
		TestReport.extpath = self._path
		
		self._projectPath = path + 'projects' + os.sep + self._projet + os.sep
		
		if not os.path.exists(self._projectPath):
			os.mkdir(self._projectPath)
		
		os.mkdir(self._path)
		shutil.copyfile(config.param['xmlPath'] + document, self._path + config.param['file']) #@todo: cp -> mv
		
		#create the link
		self._link = config.param['link'] + '/projects/' + self._projet + '/' + d.strftime('%m-%d-%y_%H%M%S') + '/index.html'
		
		#Create graph path
		self._graphPath = self._path + 'graph' + os.sep		
		os.mkdir(self._graphPath)	   
		
				
		#Parse the XML document and create the Run object
		self._file = config.param['file']
		self._doc = self._path + self._file
		self._run = Run.Run(self._doc)

	
	def generateRootHtml(self):
		'''
		@summary: Generate root HTML file (formerly generate with XSLT)
		'''		
		filename = None	 
		
		html = self.getHtmlHeader()   
		
		html += '<h1>Test Report for: ' + self._projet + '</h1>\r'
		html += '<table width="100%">\r'
		html += '	<tr>\r'
		html += '		<td align="left">\r'
		if len(self._deps) > 0:
			html += 'This report depends on :'
		for deps in self._deps:
			html += '<br/><a href="'+deps.getLink()+'">Test Report</a>'
		html += '		</td>\r'
		html += '		<td align="right">This report uses <a href="http://jakarta.apache.org/ant">Ant</a> CSS.</td>\r'
		html += '	</tr>\r'
		html += '</table>\r'
		html += '<hr size="1"/>\r'
		
		html += '''
		<h2>Summary</h2>
		<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">
		<tr valign="top">
			<th>Tests</th>
			<th>Errors</th>
			<th>Success rate</th>
			<th>Time</th>
		</tr>
		<tr valign="top">
		'''

		html += '<td>' + str(self._run.getTests()) +'</td>'
		html += '<td>' + str(self._run.getErrors()) +'</td>'
		html += '<td>' + str(self._run.getSuccesRate()) + '%</td>'
		html += '<td>' + str(self._run.getTime()) + '</td>'
		html += '''
		</tr>
		<tr>
			<td colspan="5" style="text-align:center">
				<embed src="./graph/ErrorGraph.svg" type="image/svg+xml" />
			</td>
		</tr>
		</table>
		'''  
		for testsuite in self._run.getTestsuites():
			if len(testsuite.getTestsList()) > 0:
				html += '<h3>TestCase ' + testsuite.getName() +'</h3>'
				html += '<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">'
				html +='''
					<tr valign="top">
					<th width="20%">Name</th>
					<th width="65%">Description</th>
					<th width="5%">Status</th>
					<th width="5%">Time(s)</th>
					<th width="5%">Details</th>
					</tr>
					'''
				for test in testsuite.getTestsList():
					if test.getAttribute('status') != 'notrun':
						html +='<tr valign="top">\r'
						html +='	<td>' + test.getAttribute('name') + '</td>\r'
						html +='	<td>\r'
						if test.getAttribute('Description') != None: 
							html += test.getAttribute('Description')
						if test.getAttribute('failure') != None:
							html += '<p class="error">\r'
							html += '			'+ test.getAttribute('failure') + '\r'
							html += '			<code>\r'
							html += '			<br/><br/>\r'
							html += '			'+ test.getAttribute('failure_code') +'\r'
							html += '			</code>\r'	
							html += '</p>\r'				
						html +='	</td>\r'
						html +='	<td>' + test.getAttribute('status') + '</td>\r'
						html +='	<td>' + test.getAttribute('time') + '</td>\r'
						html +='	<td>\r'
						
						testFileName = test.getAttribute('name')
						testFileName = testFileName.replace('/', '-')				
						html +='		<a href="' + testFileName + '.html">here</a>\r'
						html +='	</td>\r'		
						html +='</tr>\r'		   
				
				html += '</table>'
				html += '<p/>'
				
				html += '<a href="#top">Back to top</a>'
		
		html += '</body>\r'
		html += '</html>\r'
		
		
		
		f = open(self._path + 'index.html', 'w')
		f.write(html)
		f.close()
	
	
	def generateHtml(self):
		'''
		@summary: Generate all HTML test file (one per test)
		'''		
		filename = None
					
		for test in self._run.getTestsList():
			filename = test.getAttribute('name')
			filename = filename.replace('/', '-')
			
			col = len(test.getAttributes())
			
			#HTML header				
			html = None
			html = self.getHtmlHeader()
			
			#Title and table declaration
			html += '<h2>'+ test.getAttribute('name') +'</h2>\r'
			html += '	<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">\r'
			html += '	<tr valign="top">\r'				 
			
			#Table header
			for key in test.getAttributes():
				if key != 'failure' and key != 'failure_code':
					html += '		<div id="'+key+'_tooltip" class="tooltip" style="display:none">'+globals.description[key]+'</div>'
					html += '		<th id="'+key+'">'+key+'</th>\r'
					html += '		<script type="text/javascript">\r'
					html += '			var my_tooltip = new Tooltip("'+key+'", "'+key+'_tooltip")\r'
					html += '		</script>\r'
			
			for att in test.getCustomAttributes():
				if att.getDisplay() == True:
					html += '		<th>'+att.getName()+'</th>\r'
			html += '	</tr>\r'
			
			#Value of each column
			html += '	<tr valign="top">\r'
			for key in test.getAttributes():
				if key != 'failure' and key != 'failure_code':
					html += '		<td>' + test.getAttribute(key) + '</td>\r'
			
			for att in test.getCustomAttributes():
				if att.getDisplay() == True:
					html += '		<td>'+att.getAttribute()+'</td>\r'			
				
			html += '	</tr>\r'
			
			#Special line for failed test
			if test.getAttribute('failure') != None:
				html += '	<tr class="error">\r'
				html += '		<td colspan="'+str(col)+'">\r'
				html += '			'+ test.getAttribute('failure') + '\r'
				html += '			<code>\r'
				html += '			<br/><br/>\r'
				html += '			'+ test.getAttribute('failure_code') +'\r'
				html += '			</code>\r'   
				html += '		</td>\r'
				html += '	</tr>\r'
			
			#Special line for compare test (print screentshot/reference/difference image)
			for customAttribute in test.getCustomAttributes():
				html += customAttribute.getHtml()
			
			#Special line for graph (performance test)
			if os.path.isfile(self._graphPath + filename + '.svg'):   
				html += '	<tr>\r'
				html += '		<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">\r'
				html += '		<tr class="screenshot">\r'
				html += '			<td colspan="' + str(col) + '">\r'
				html += '				<embed src="./graph/' + filename + '.svg" type="image/svg+xml" />\r'
				html += '			</td>\r'
				html += '		</tr>\r'					
				html += '		</table>\r'
				html += '	</tr>\r' 
			
			html += '	</table>\r'
			html += '	<a href="index.html">Back</a>\r'
			html += '</body>\r'
			html += '</html>\r'
	
			f = open(self._path + filename+'.html', 'w')
			f.write(html)
			f.close()
				
		
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
	
	def getHtmlHeader(self):
		html = '''
		<html>
			<head>
				<title>Test Details</title>
				<link rel="stylesheet" type="text/css" href="../../../css/style.css" />
				<link rel="stylesheet" type="text/css" href="../../../css/lightbox.css" />
				<script type="text/javascript" src="../../../js/prototype.js"></script>
				<script type="text/javascript" src="../../../js/scriptaculous.js?load=effects,builder"></script>
				<script type="text/javascript" src="../../../js/lightbox.js"></script>
				<script type="text/javascript" src="../../../js/tooltip.js"></script>
		
			</head>
			<body>
		'''
		
		return html