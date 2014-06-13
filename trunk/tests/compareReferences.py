#!/usr/bin/env python

# SConsBuildFramework - Copyright (C) 2014, Nicolas Papier.
# Distributed under the terms of the GNU General Public License (GPL)
# as published by the Free Software Foundation.
# Author Nicolas Papier

import glob
import os
import Image

# Compare two images
import ImageChops
def isSameImage(im1, im2):
	return ImageChops.difference(im1, im2).getbbox() is None

# Command line options
from optparse import OptionParser
usage = """Usage: compareReferences.py
find differences between two directories (only png files are taken into account)"""

parser = OptionParser(usage)
parser.add_option("-n", "--incoming", dest="incomingDir", type="string", default="referencesIncoming")
parser.add_option("-b", "--base", dest="baseDir", type="string", default="referencesBase")

if __name__ == "__main__":
	(options, args) = parser.parse_args()

	newFiles = glob.glob( os.path.join(options.incomingDir, "*.png") )
	baseFiles = glob.glob( os.path.join(options.baseDir, "*.png") )
	newFiles = sorted( [os.path.basename(file) for file in newFiles] )
	baseFiles = sorted( [os.path.basename(file) for file in baseFiles] )

	matchedTests = sorted(list(set(baseFiles) & set(newFiles)))
	removedTests = sorted(list(set(baseFiles) - set(newFiles)))
	newTests = sorted(list(set(newFiles) - set(baseFiles)))

	message = ''
	print ( 'Compare images:\n---------------\n' )
	for file in matchedTests:
		baseImage = Image.open( os.path.join(options.baseDir, file) )
		incomingImage = Image.open( os.path.join(options.incomingDir, file) )
		if (baseImage.mode == incomingImage.mode) and isSameImage(baseImage, incomingImage):
			print ('{} : OK'.format(file.ljust(60)))
		else:
			message +=  'DIFFERENCE DETECTED in {}'.format(file)
	print

	print ( 'REPORT\n------\n')
	if len(removedTests)>0:
		print ( 'Removed test(s): {}\n'.format( list(removedTests) ) )
	if len(newTests)>0:
		print ( 'New test(s): {}\n'.format( list(newTests) ) ) 
	print message
