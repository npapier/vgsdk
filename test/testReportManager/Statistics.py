'''
Created on 29 mai 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

import globals
import config
import os
import CairoPlot
import glob
import shutil
import Run

class Statistics(object):
	'''
	classdocs
	@summary: Create stats graph and generate alert on failure
	'''


	def __init__(self, graphPath, projet):
		'''
		Constructor
		@summary: List all tests history path and create a lsit of run object
		@param graphPath: the directory where we put the generated graph
		'''
		self._path = config.param['path'] + 'projects' + os.sep + projet + os.sep
		self._graphPath = graphPath
		
		#@todo: regex + compacte : (\d{2})-(\d{2})-(\d{2})_(\d{4}) ?
		self._dirList = glob.glob(self._path + '[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]_[0-9][0-9]h[0-9][0-9]m[0-9][0-9]s')
		self._runList = []
		
		self.listRun()
	

	def listRun(self):
		'''
		@summary: Create a list of all run. A run is an execution of the test programm. Each run contain a tests list
		'''		
		for dir in self._dirList:
			self._runList.append(Run.Run(dir+ '/' + config.param['file'], customAttribut = False))
		
		#Reverse to have chronological order (earlier to older)
		self._runList.reverse()


	def createErrorGraph(self):
		'''
		@summary: Create a graph of all tests / errors
		'''		
		tests = []
		errors = []
		legend = []
		
		filename = 'ErrorGraph'
		
		for list in self._runList:
			tests.append(list.getTests())
			errors.append(list.getErrors())
			legend.append(list.getName())
		
		#Reverse to have chronological order (older to earlier)
		tests.reverse()
		errors.reverse()
		legend.reverse()
		
		values = {'tests' : tests, 'errors' : errors}  
		
		CairoPlot.dot_line_plot(filename, values, 400, 300, h_labels = legend, axis = True, grid = True)
		
		shutil.move(filename+'.svg', self._graphPath + filename+'.svg')


	def createPerformanceGraph(self):
		'''
		@summary: Create graph for all performance tests (a performance test is a test where the attribut "fps" is set)
		'''		
		if len(self._runList) > 0:
			ref = self._runList[0]
		else:
			return
		
		for test in ref.getTestsList():
			if 'Fps' in test.getAttributes():
				fps = []
				legend = []
				
				for run in self._runList:
					for t in run.getTestsList():
						if 'Fps' in t.getAttributes() and test.equals(t):
							fps.append(int(t.getAttribute('Fps')))
							legend.append(run.getName())
				
				filename = test.getAttribute('name')
				filename = filename.replace('/', '-')
				
				#Reverse to have chronological order
				fps.reverse()
				legend.reverse()
				
				CairoPlot.dot_line_plot(filename, fps, 400, 300, h_labels = legend, axis = True, grid = True)
				
				shutil.move(filename+'.svg', self._graphPath + filename+'.svg')

	def createRenderPerformanceGraph(self):
		'''
		@summary: Create graph for all render performance tests (a test where the attribut "MinRenderDuration", "MaxRenderDuration" and "AverageRenderDuration" are set)
		'''		
		if len(self._runList) > 0:
			ref = self._runList[0]
		else:
			return
		
		for test in ref.getTestsList():
			if 'MinRenderDuration' in test.getAttributes() and 'MaxRenderDuration' in test.getAttributes() and 'AverageRenderDuration' in test.getAttributes():
				minDuration = []
				maxDuration = []
				averageDuration = []
				legend = []
				
				for run in self._runList:
					for t in run.getTestsList():
						if 'MinRenderDuration' in t.getAttributes() and 'MaxRenderDuration' in t.getAttributes() and 'AverageRenderDuration' in t.getAttributes() and test.equals(t):
							minDuration.append(float(t.getAttribute('MinRenderDuration')))
							maxDuration.append(float(t.getAttribute('MaxRenderDuration')))
							averageDuration.append(float(t.getAttribute('AverageRenderDuration')))
							legend.append(run.getName())
				
				filename = test.getAttribute('name')
				filename = filename.replace('/', '-')
				
				#Reverse to have chronological order
				minDuration.reverse()
				maxDuration.reverse()
				averageDuration.reverse()
				legend.reverse()
				
				values = {'min' : minDuration, 'max' : maxDuration, 'average' : averageDuration} 
				
				CairoPlot.dot_line_plot(filename, values, 400, 300, h_labels = legend, axis = True, grid = True)
				
				shutil.move(filename+'.svg', self._graphPath + filename+'.svg')

	def getRunList(self):
		return self._runList
