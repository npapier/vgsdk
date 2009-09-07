'''
Created on 30 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

import os
from xml.dom.minidom import * 
from CustomAttribute import CustomAttribute
import TestReport
import CairoPlot

class XmlCompareAttribute(CustomAttribute):
	'''
	Treat Sofa Xml comparaison tests attribute
	'''

	def __init__(self, name, attribute):
		'''
		Constructor
		@summary: Print compare information from different xml files
		@param name: Attribute name
		@param attribute: Attribute value (path to a xml files separated by '|')
		'''
		CustomAttribute.__init__(self, name, attribute)
		self._display = False
		
		self._files = str.split(str(attribute), '|')

	def getHtml(self):
		'''
		@summary: return html tab line for images
		'''
		
		html = ''
		
		for file in self._files:
			if file != '':
				errors = []
				time = []
				
				doc = parse(file)
				root = doc.documentElement
				
				html += '		<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">\r'
				
				html += '		<tr>\r'
				html += '			<td width="40%">\r'	 
				html += '			Object: ' + root.attributes['name'].value
				html += '			<pre>'
				for error in root.getElementsByTagName('error'):
						html += 'dt: ' + error.attributes['dt'].value + '\r'
						html += 'time: ' + error.attributes['time'].value + '\r'
						html += 'error: ' + error.attributes['error'].value + '\r'
						html += '<br/>'
						
						errors.append(float(error.attributes['error'].value))
						time.append(error.attributes['time'].value)
				html += '			</pre>'
				html += '			</td>\r'
				
				graph = str.split(file, '/')[len(str.split(file, '/'))-1]
				filename = TestReport.TestReport.extpath + 'graph' + os.sep + graph
				if len(errors) > 0 or len(time) > 0:
					CairoPlot.dot_line_plot(filename, errors, 400, 300, h_labels = time, axis = True, grid = True)
				
				html += '			<td align="center">\r'
				html += '				<embed src="./graph/'+graph+'.svg" type="image/svg+xml" />\r'
				html += '			</td>\r'
				html += '		</tr>\r'	  
		
		html += '		</table>\r'	
		return html