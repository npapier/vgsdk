'''
Created on 11 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

from Alert.ConsoleAlert import ConsoleAlert
from Alert.MailAlert import MailAlert
from Condition.FpsCondition import FpsCondition
from Condition.ErrorCondition import ErrorCondition
from Attribute.ImageAttribute import ImageAttribute
from Attribute.XmlCompareAttribute import XmlCompareAttribute

param = {
		'xmlPath' : 'D:/local/bin/tests/',
		'path' : 'D:/local/tests/',
		'file' : 'tests.xml',
		'link' : 'http://example.com/TestsReport/',
		
		'cygwinPath' : 'C:/cygwin/bin/',
		'rsyncLocalPath' : '/cygdrive/d/local/tests/',
		'rsyncDistPath' : 'username@192.168.1.10:/home/username/public_html/tests',
		 
		'mailServer' : 'localhost',
		'mailRecipient' : ['username@example.com'], # @note: example 'usr@example.com', 'usr2@example.com', 'usr@example.net'
		'mailSender' : 'username@example.com',
		 
		#'highFpsLimit' : 25, #@see FpsCondition.py
		#'lowFpsLimit' : 10 #@see FpsCondition.py
		
		'renderLimit' : 20 #@see FpsCondition.py
		}

#List of conditions
listCondition = [RenderPerformanceCondition(param['renderLimit']), ErrorCondition()] 

#List of alert type
listAlert = [MailAlert(), ConsoleAlert()]

listCustomAttribut = {
					'ImagePath' : ImageAttribute,
					'CompareErrorFiles' : XmlCompareAttribute,
					}