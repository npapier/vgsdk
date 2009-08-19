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
			externalPath = a.split('=')[1]
			filename = externalPath.split('/')
			filename = filename[len(filename)-1]
			internalPath = TestReport.TestReport.extpath + folder + os.sep
			
			if not os.path.exists(internalPath):
				os.mkdir(internalPath)
			
			shutil.copyfile(externalPath, internalPath + filename)
			
			self.resizeImg(filename, internalPath)
			
			#save only the file name without extension
			self.imageList[folder] = filename.split('.')[0]

	def getHtml(self):
		'''
		@summary: return html tab line for images
		'''
		html = ''
		html += '	<tr>\r'
		html += '		<table class="details" border="0" cellpadding="5" cellspacing="2" width="95%">\r'

		html += '		<tr class="screenshot">\r'
		for folder in self.imageList:
			html += '			<td>\r'
			html += '			<a href="./'+folder+'/'+self.imageList[folder]+'.png" rel="lightbox[img]"><img src="./'+folder+'/'+self.imageList[folder]+'_thumb.png" alt="'+folder+'"></a>\r'					
			html += '			<p>'+folder+' image</p>\r'
			html += '			</td>\r'
									 
		html += '		</tr>\r'	  
		
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