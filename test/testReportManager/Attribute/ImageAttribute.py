'''
Created on 30 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

from CustomAttribute import CustomAttribute
import TestReport
import os
import shutil
import re
import PIL
from PIL import Image

class ImageAttribute(CustomAttribute):
	'''
	Treat image attribute
	'''

	def __init__(self, name, attribute):
		'''
		Constructor
		@summary: move image and create thumb
		@param name: attributte name
		@param attribute: Attribute value
		Attribute value must of this form : folderName=imagePath|folderName=imagePath|..
		with folder name : the image type which also is the folder name (example : reference, screenshot, difference...)
		imagePath : path to the image
		'''
		CustomAttribute.__init__(self, name, attribute)
		self._display = False
		self.imageList = {}
		args = self._attribute.split('|')
		
		for a in args:
			folder = a.split('=')[0]
			self.imageList[folder] = []
			files = a.split('=')[1]
			externalPath = files.split(';')[0]
			filenames = str(files.split(';')[1]).split(',')
			
			internalPath = TestReport.TestReport.extpath + folder + os.sep
			
			if not os.path.exists(internalPath):
				os.mkdir(internalPath)
			
			for filename in filenames:
				if filename != "":
						
					shutil.copyfile(os.path.join(externalPath, filename), internalPath + filename)
					
					self.resizeImg(filename, internalPath)
					
					#save only the file name without extension
					self.imageList[folder].append(filename.split('.')[0])

	def getHtml(self):
		'''
		@summary: return html tab line for images
		'''
		html = ''

		htmlScreen = ''
		htmlRef = ''
		htmlDif = ''
		
		difPath = TestReport.TestReport.extpath + 'differences' + os.sep
		
		html += '		<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">\r'

		htmlScreen	+= '		<tr class="screenshot">\r'
		htmlScreen	+= '		<td>Screenshots</td>\r'
		
		htmlDif	+= '		<tr class="screenshot">\r'
		htmlDif	+= '		<td>Differences</td>\r'		
		
		htmlRef	+= '		<tr class="screenshot">\r'
		htmlRef	+= '		<td>References</td>\r'		

		for screen, ref in zip(self.imageList['screenshots'], self.imageList['references']):
			
			screenUrl = './screenshots/'+screen+'.png'
			refUrl = './references/'+ref+'.png'
			
			if os.path.exists(difPath + screen + '.png'):
				difUrl = './differences/'+screen+'.png'	
				
				htmlDif += '			<td>\r'
				htmlDif += '			<a href=\'javascript:showImg("'+screenUrl+'","'+refUrl+'","'+difUrl+'")\'><img src="./differences/'+screen+'_thumb.png" alt="differences/'+ref+'"></a>\r'					
				htmlDif += '			</td>\r'	
			else:
				htmlDif += '			<td></td>\r'	
				difUrl = ''		
			
			htmlScreen += '			<td>\r'
			htmlScreen += '			<a href=\'javascript:showImg("'+screenUrl+'","'+refUrl+'","'+difUrl+'")\'><img src="./screenshots/'+screen+'_thumb.png" alt="screenshots/'+screen+'"></a>\r'					
			htmlScreen += '			</td>\r'								
				
			htmlRef += '			<td>\r'
			htmlRef += '			<a href=\'javascript:showImg("'+screenUrl+'","'+refUrl+'","'+difUrl+'")\'><img src="./references/'+ref+'_thumb.png" alt="references/'+ref+'"></a>\r'					
			htmlRef += '			</td>\r'	
		
		htmlScreen += '		</tr>\r'
		htmlDif += '		</tr>\r'
		htmlRef	+= '		</tr>\r'
		
		html += '''
			<script type="text/javascript">
				function showImg(screen, ref, dif)
				{
					var dialog = new Element('div', { 'id': 'popup' });
					
					dialog.insert(new Element('img', { 'src': screen }));
					dialog.insert(new Element('img', { 'src': ref }));	
					if (dif != '')
					{				
						dialog.insert(new Element('img', { 'src':  dif }));
					}					
														
					var overlay = new DialogOverlay(dialog);
					overlay.show();				
				}
			</script>
		'''		
		
		html += htmlScreen + htmlDif + htmlRef

		html += '		</table>\r'
		
		return html
		
	def resizeImg (self, file, path):
		'''
		@summary: Create thumbnail of an image
		'''
		f = file.rpartition('.')
		thumb = path + f[0] + '_thumb.' + f[2]
		
		self.resize(path + file, thumb)   
			
	def resize(self, original, resize):
		'''
		@summary: Create thumbnail of an image
		'''		
		img = Image.open(original)
		wpercent = (300/float(img.size[0]))
		hsize = int((float(img.size[1])*float(wpercent)))
		img = img.resize((300,hsize), PIL.Image.ANTIALIAS)
		img.save(resize)