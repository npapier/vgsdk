'''
Created on 30 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

from __future__ import with_statement 
import os
from xml.dom.minidom import * 
from CustomAttribute import CustomAttribute
import TestReport

from mako.template import Template
from mako.lookup import TemplateLookup

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
		
		self._mylookup = TemplateLookup(directories=['./templates'])

	def getHtml(self):
		'''
		@summary: return html tab line for images
		'''
		
		html = ''
		html += '		<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">\r'
		
		for file in self._files:
			if file != '':
				errors = []
				time = []
				
				doc = parse(file)
				root = doc.documentElement
				
				if len(root.getElementsByTagName('error')) > 0:
				
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
					
					mytemplate = self._mylookup.get_template('XmlCompareAttributeChart.xml')
					
					with open( filename + '.xml', 'w' ) as file :
						file.write(mytemplate.render(legend=time, errors=errors))					
					
					html += '			<td align="center">\r'
					html += '''
							<object type="application/x-shockwave-flash" width="600" height="550" data="../../../charts/charts.swf">
							  <param name="movie" value="../../../charts/charts.swf" />
							  '''
				  	html += '<param name="FlashVars" value="library_path=../../../charts/charts_library&amp;xml_source=graph/'+graph+'.xml" />'
				  	html += '''
							  <param name="wmode" value="transparent" />
							</object>	
					'''
					html += '			</td>\r'
					html += '		</tr>\r'	  
		
		html += '		</table>\r'	
		return html