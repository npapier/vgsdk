'''
Created on 22 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''
from __future__ import with_statement 
from mako.template import Template
from mako.lookup import TemplateLookup
import config
import os
import stat
import glob
import Run
import xml.dom.minidom


class TestDashboard(object):
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
			dirList = glob.glob(self._projectsPath + os.sep + project + os.sep + '[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]_[0-9][0-9]h[0-9][0-9]m[0-9][0-9]s')   
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
		os.chmod( config.param['path'] + 'dashboard.xml', stat.S_IREAD|stat.S_IWRITE | stat.S_IRGRP | stat.S_IROTH )
		
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
					r.setAttribute('errors', str(self._projectList[project][run].getErrors()))
					r.setAttribute('status', 'failure')
				else:
					r.setAttribute('status', 'success')
				
				p.appendChild(r)
			
			root.appendChild(p)
		
		with open( config.param['path'] + 'fulldashboard.xml', 'w' ) as file :
			file.write(doc.toprettyxml())
		os.chmod( config.param['path'] + 'fulldashboard.xml', stat.S_IREAD|stat.S_IWRITE | stat.S_IRGRP | stat.S_IROTH )
	
	def createDashboardHtml(self):
		mylookup = TemplateLookup(directories=['./templates'])
		mytemplate = mylookup.get_template('TestDashboard.html')		
		with open( config.param['path'] + 'index.html', 'w' ) as file :
			file.write(mytemplate.render(runList=self._runList))
		os.chmod( config.param['path'] + 'index.html', stat.S_IREAD|stat.S_IWRITE | stat.S_IRGRP | stat.S_IROTH )
