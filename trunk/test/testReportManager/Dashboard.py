'''
Created on 22 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''
from __future__ import with_statement 
import config
import os
import glob
import Run
import xml.dom.minidom


class Dashboard(object):
	'''
	classdocs
	@summary: Creates differents dashboard full/lite and HTML or XML.
	'''


	def __init__(self):
		'''
		Constructor
		'''
		self._projectsPath = config.param['path'] + 'projects'
		self._projects = os.listdir(self._projectsPath)
		self._runList = {}
		
		for project in self._projects:
			self._runList[project] = Run.Run(self._projectsPath + os.sep + project + os.sep + 'LastTest' + os.sep + config.param['file'], True, False)	
		
		
		self._projectList = {}
		for project in self._projects:
			self._projectList[project] = {}
			dirList = glob.glob(self._projectsPath + os.sep + project + os.sep + '[0-9][0-9]-[0-9][0-9]-[0-9][0-9]_[0-9][0-9][0-9][0-9][0-9][0-9]')   
			dirList.reverse()
			for run in dirList:
					date = str.split(run, os.sep)
					date = date[len(date)-1]
					self._projectList[project][date] = Run.Run(run + os.sep + config.param['file'], True, False)	
			
		
	def createDashboardXml(self):
		doc = xml.dom.minidom.Document()
		root = doc.createElement('dashboard')
		root.setAttribute('link', config.param['link'] + 'index.html')
		doc.appendChild(root)
		
		for project in self._runList:
			p = doc.createElement('project')
			p.setAttribute('name', project)
			p.setAttribute('link', config.param['link'] + 'projects/' + project + '/LastTest/')
			
			if self._runList[project].getErrors() > 0:
				p.setAttribute('errors', str(self._runList[project].getErrors()))
				p.setAttribute('status', 'failure')
			else:
				p.setAttribute('status', 'success')
			
			root.appendChild(p) 
		
		root.appendChild(p)
		
		with open( config.param['path'] + 'dashboard.xml', 'w' ) as file :
			file.write(doc.toprettyxml())
		
	def createFullDashboardXml(self):
		doc = xml.dom.minidom.Document()
		root = doc.createElement('dashboard')
		root.setAttribute('link', config.param['link'] + 'index.html')
		doc.appendChild(root)
		
		for project in self._projectList:
			p = doc.createElement('project')
			p.setAttribute('name', project)
			
			for run in self._projectList[project]:
				r = doc.createElement('run')
				r.setAttribute('date', run)
				r.setAttribute('link', config.param['link'] + 'projects/' + project + '/'+run+'/')
				r.setAttribute('tests', str(self._projectList[project][run].getTests()))
				
				if self._projectList[project][run].getErrors() > 0:
					r.setAttribute('errors', str(self._runList[project].getErrors()))
					r.setAttribute('status', 'failure')
				else:
					r.setAttribute('status', 'success')
				
				p.appendChild(r)
			
			root.appendChild(p)
		
		with open( config.param['path'] + 'fulldashboard.xml', 'w' ) as file :
			file.write(doc.toprettyxml())	
	
	def createDashboardHtml(self):
		#self.createLiteDashboardHtml()
		self.createFullDashboardHtml()
	
	
	def createLiteDashboardHtml(self):
		html = self.getHtmlHeader()
		html += '''
		<h1>Tests Dashboard</h1>
		
		<br />
		<table>
		'''
		for project in self._runList:
			html += '<tr>'
			html += '<td class="LastBuild db_header"><a href="index2.html#'+project+'">'+project+'</a></td>'
			if self._runList[project].getErrors() > 0:
				html += '<td align="center" class="LastBuild db_failure"><a href="index2.html#'+project+'">#details</a><br />Error(s): '+str(self._runList[project].getErrors())+'</td>'
			else:
				html += '<td align="center" class="LastBuild db_success"><a href="index2.html#'+project+'">#details</a><br />Run successful</td>'
		
			html += '</tr>'

		html += '''
		</table>
		</body>
		</html>
		'''
		
		with open( config.param['path'] + 'index.html', 'w' ) as file :
			f.write(html)
		
		
	def createFullDashboardHtml(self):
		html = self.getHtmlHeader()
		html += '''
		<h1>Tests Dashboard</h1>
		
		<br />
		<hr size="1"/>
		'''
				
		for project in self._runList:
			run = self._runList[project]
			
			html += '<div id="' + project + '">'
			html += '<h2><a href="projects/' + project + '/LastTest/index.html">' + project + '<a/></h2>'
			html += '''
			<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">
			<tr valign="top">
				<th>Tests</th>
				<th>Errors</th>
				<th>Success rate</th>
				<th>Time</th>
			</tr>
			<tr valign="top">
			'''
			html += '<td width="25%">' + str(run.getTests()) +'</td>'
			html += '<td width="25%">' + str(run.getErrors()) +'</td>'
			html += '<td width="25%">' + str(run.getSuccesRate()) + '%</td>'
			html += '<td width="25%">' + str(run.getTime()) + '</td>'
			html += '''
			</tr>
			</table>
			'''	 

			if len(run.getErrorsList()) > 0:
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
				for test in run.getErrorsList():
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
						html +='		<a href="projects/' + project + '/LastTest/' + testFileName + '.html">here</a>\r'
						html +='	</td>\r'		
						html +='</tr>\r'		   
			
			html += '</table>'
			html += '<p/>'
			
			html += '<a href="#top">Back to top</a>'  
			html += '</div>'		  
		
		
		
		html += '</body>\r'
		html += '</html>\r'		
		
		with open( config.param['path'] + 'index.html', 'w' ) as file :
			file.write(html)
		
	def getHtmlHeader(self):
		html = '''
		<html>
			<head>
				<title>Dashboard</title>
				<link rel="stylesheet" type="text/css" href="./css/style.css" />
				<link rel="stylesheet" type="text/css" href="./css/lightbox.css" />
				<script type="text/javascript" src="./js/prototype.js"></script>
				<script type="text/javascript" src="./js/scriptaculous.js?load=effects,builder"></script>
				<script type="text/javascript" src="./js/lightbox.js"></script>
				<script type="text/javascript" src="./js/tooltip.js"></script>
		
			</head>
			<body>	 
		'''
		return html