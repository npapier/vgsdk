'''
Created on 11 juin 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

from Alert import Alert
import smtplib
import config
import platform

class MailAlert(Alert):
	'''
	@summary: Send alert by email
	'''	
	
	def __init__(self):
		'''
		Constructor	
		'''
		Alert.__init__(self)  
		self._mailServer	= config.param['mailServer']		# The SMTP server.
		self._mailRecipient = config.param['mailRecipient']	 # The recipient for notification mails.  
		self._mailSender = config.param['mailSender']		   # The sender for notification mails. 
		
	def __call__(self):
		# Builds the mail headers and body
		mail  = 'Content-Type: text/plain\r\n'
		mail += 'Subject: Test error in ' + platform.node() + ' on ' + self._project + '\r\n'
		mail += '\r\n'
		
		mail += 'There is a new failure in ' + self._project + '\r'
		mail += 'Failure list:\r'
		
		for t in self._list:
			 mail += self.createAlert(t)
		
		mail += 'Full details are available at: ' + self._link + '\r'
		mail += '\r'
		mail += 'Sincerely,\r'
		mail += 'TestBot\r'
		
		# Sends the message.
		print 'Sending mail....'
		smtpServer = smtplib.SMTP( self._mailServer )
		smtpServer.sendmail( self._mailSender, self._mailRecipient, mail )
		smtpServer.quit()