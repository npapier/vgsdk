'''
Created on 26 mai 2009

VGSDK - Copyright (C) 2009, Maxime Peresson.
Distributed under the terms of the GNU Library General Public License (LGPL)
as published by the Free Software Foundation.
Author Maxime Peresson

'''

#Description of xml attribut
description = { 
	#common for all tests
	'name' : "Test name",
	'classname' : "The test suite and the test param list",
	'status' : "Test status",
	'type' : "Error / Failure of the test",
	'time' : "Total time of the test",
	
	#for specialized tests
	'Description' : "Test description",
	'Shape' : "The shape used",
	'Object' : "The object used",
	'Scene' : "The scene used",
	'Scenario' : "The scenario used",
	'Fps' : "Ratio Frame/Duration",
	'Duration' : "Duration of the performance test",
	'Frame' : "Number of iteration during the test duration",
	'BoundingBoxUpdatePolicyValue' :  "Can be AUTOMATIC (default) and ONCE",
	'DeformableHintValue' : "Can be STATIC (default), DYNAMIC and STREAM",
	'GeometryLevel' : "The level geometry",
	'PixelDiff' : "Number of pixel which differ from the reference",
	
	'VerificationError' : 'Sofa Verification error',
	'VerificationErrorByDof' : 'Sofa Verification error by DOF',
	}

#Attributes which identify a test
testIdentifier = [
	'Shape',
	'Object',
	'GeometryLevel',
	'DeformableHintValue',
	'BoundingBoxUpdatePolicyValue'
	]
