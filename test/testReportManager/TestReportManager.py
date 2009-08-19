#!/usr/bin/env python

"""Test Report Manager

Create test report from xml file generated by googletest (JUnit format)

Usage: python TestReportManager.py [options] [source]

Options:
  -f ..., --file=...	Generate test report for the xml file passed in parameter (full path is required)
  -d ..., --deps=...	Generate test report with dependences. The dependance is an xml report file from a project.
  -b, --dashboard		Generate the dashboard.
  -h, --help			Show this help

Examples:
  TestReportManager.py
	Show this help
  TestReportManager.py -f vgsdkViewerGtkTests.xml
	Generate test report for vgsdk test project
  TestReportManager.py -f sofaViewerGtkTests.xml -d deathtest-sofaViewerGtkTests.xml
	Generated test report for sofaviewer test project and deathtest project

"""

"""
VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson
"""

import os, sys, getopt
import TestReport
import Dashboard
import Statistics
import config

def go(file, type, deps = []):
	'''
	@summary: lauch creation of a report
	'''
	print 'Initialize all'
	t = TestReport.TestReport(file, type, deps)
		
	print 'Create statistics'
	stats = Statistics.Statistics(t.getGraphPath(), t.getProjet())
	stats.createErrorGraph()
	stats.createPerformanceGraph()  
	
	print 'Manage alert'
	#List of errors which must be sended
	if len(stats.getRunList()) > 1 :
		listErrorTest = [] 
		
		for condition in config.listCondition:
			condition.initialize(stats)
			listErrorTest = listErrorTest + condition.shouldTrigger()
		
		if len(listErrorTest) > 0:
			for alert in config.listAlert:
				alert.initialize(listErrorTest, t.getLink(), t.getProjet())
				alert()
	
	print 'Generated HTML pages'
	t.generateRootHtml()
	t.generateHtml()
	
	print 'Create "LastTest" directory'
	t.moveToLastTest()
	
	print 'Publishing'
	t.goRsync()

	return t

def usage():
	print __doc__

def main(argv):  
	'''
	@summary: Main function. Process argument and lauch the script.
	'''  
						 
	type = "normal"
	file = None
	deps = []
	dashboard = False
		 
	try:								
		opts, args = getopt.getopt(argv, "hbf:d:", ["help", "dashboard", "file=", "deps="])
	except getopt.GetoptError:		  
		usage()						 
		sys.exit(2)					 
	for opt, arg in opts:
		if opt in ("-h", "--help"):
			usage()				 
			sys.exit()							  
		elif opt in ("-f", "--file"):
			file = arg  
		elif opt in ("-d", "--deps"):
			deps.append(arg)
		elif opt in ("-b", "--dashboard"):
			dashboard = True	
		
	if file != None:
		depsTestReport = []
		if len(deps) > 0:
			for dep in deps:
				depsTestReport.append(go(dep, type))
	
		go(file, type, depsTestReport)
	
	elif dashboard == True:
		db = Dashboard.Dashboard()
		db.createDashboardHtml()
		db.createDashboardXml()
		db.createFullDashboardXml()
	
	else:
		usage()
		sys.exit()
	print 'Script done.'
	 



if __name__ == "__main__":
	main(sys.argv[1:])
 