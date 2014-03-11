'''
Created on 30 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

import os
from CustomAttribute import CustomAttribute

class TextAttribute(CustomAttribute):
	'''
	Treat text attribute
	'''

	def __init__(self, name, attribute):
		'''
		Constructor
		@summary: Print text from file
		@param name: Attribute name
		@param attribute: Attribute value (path to a txt file)
		'''
		CustomAttribute.__init__(self, name, attribute)
		self._display = False

	def getHtml(self):
		'''
		@summary: return html tab with formatted texte
		'''
		f = open(self._attribute, 'r')
		
		html = ''
		html += '		<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">\r'

		html += '		<tr>\r'
		html += '			<td>\r'	 
		html += '			file: ' + str.split(str(self._attribute), "/")[len(str.split(str(self._attribute), "/"))-1] + '\r' 
		html += '			<pre>'
		for line in f.readlines():
			html += line
		html += '			</pre>'
		html += '			</td>\r'
									 
		html += '		</tr>\r'	  
		html += '		</table>'
		
		return html