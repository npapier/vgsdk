#!/usr/bin/env python

# VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2013, Nicolas Papier.
# Distributed under the terms of the GNU Library General Public License (LGPL)
# as published by the Free Software Foundation.
# Author Nicolas Papier

import os
import xml.dom.minidom

from dbNodes import *



currentNodeName = ""
currentFieldName = ""



def getText( nodeList ) :
	text = ""
	for node in nodeList :
		if node.nodeType == node.TEXT_NODE :
			text = text + node.data
	return text


def handleEnum( domEnum, inNodesTag = False ) :
	# default
	attrDefault = domEnum.getAttributeNode("default")
	if attrDefault == None :
		raise StandardError("Enum without default value.")

	# [name]
	attrName = domEnum.getAttributeNode("name")

	global currentNodeName
	global currentFieldName

	if attrName == None:
		# anonymous Enum() used by field of a vgd::node::Node
		enum = Enum( currentNodeName, currentFieldName )
	else:
		# Named Enum()
		if inNodesTag:
			# direct child of <nodes>
			enum = Enum()
			enum.namespace = 'vgd::node'
			enum.setTypename( attrName.value )
		else:
			# Named Enum() in vgd::node::Node
			enum = Enum( currentNodeName, attrName.value )
			enum.setTypename( attrName.value )

	# value
	domValues = domEnum.getElementsByTagName("value")
	for domValue in domValues :
		attrName	= domValue.getAttributeNode("name")
		attrDoc		= domValue.getAttributeNode("doc")
		if attrName is None or attrDoc is None :
			raise StandardError("Enum must have both name and doc attributes.")
		enum.addValue( attrName.value, attrDoc.value )

	# Sets default value in enum
	enum.setDefaultValue( attrDefault.value )

	# Returns the enum
	return enum


def handleType( domType ) :
	# Return value
	type = None

	# name
	attrName = domType.getAttributeNode("name")
	if attrName == None :
		raise StandardError("Type must have an attribute name.")

	# Construct new type
	if attrName.value == "enum" :
		domEnums = domType.getElementsByTagName("enum")
		if domEnums.length != 1 :
			raise StandardError("The type, named enum, must have one enum child node.")
		type = handleEnum( domEnums[0] )
	else :
		global currentNodeName
		global currentFieldName
		type = Type( attrName.value, currentNodeName, currentFieldName )

		# [namespace]
		attrNamespace = domType.getAttributeNode("namespace")
		if attrNamespace:
			type.namespace = attrNamespace.value

		# [default]
		attrDefault = domType.getAttributeNode("default")
		if attrDefault:
			type.defaultValue = attrDefault.value

		# [enum]
		attrEnum = domType.getAttributeNode("enum")
		if attrEnum:
			type.isAnEnum = attrEnum.value

	# Returns the type
	return type



def handleOneType( dom ) :
	"""handle <type></type> to reuse an existing type or <enum></enum> to define a specialized vgSDK vgd::field::Enum"""

	# is there a <type> ?
	domTypes = dom.getElementsByTagName("type")
	if domTypes.length == 1 :
		type = handleType( domTypes[0] )
		return type
	else:
		# is there an <enum> ?
		domEnums = dom.getElementsByTagName("enum")
		if domEnums.length == 1 :
			enum = handleEnum( domEnums[0] )
			return enum
		else:
			raise StandardError("One type or enum expected, but encountered %s type(s) in a %s named %s." % (domTypes.length, dom.nodeName, dom.getAttributeNode("name").value) )


def handleTwoTypes( dom ) :

	# Return value
	types = []

	domTypes = dom.getElementsByTagName("type")
	if domTypes.length == 1 :
		types.append( handleType(domTypes[0]) )
	elif domTypes.length == 2 :
		global currentFieldName
		currentFieldNameBak = currentFieldName
		currentFieldName += "Parameter"
		print currentFieldName
		types.append( handleType(domTypes[0]) )
		currentFieldName = currentFieldNameBak
		print currentFieldName
		types.append( handleType(domTypes[1]) )
	else :
		raise StandardError("One or two type(s) expected, but encountered %s type(s) in a %s named %s." % (domTypes.length, dom.nodeName, dom.getAttributeNode("name").value) )

	#
	return types


def handleSF( domSF ) :
	# name and doc
	attrName	= domSF.getAttributeNode("name")
	attrDoc		= domSF.getAttributeNode("doc")

	if attrName == None or attrDoc == None :
		raise StandardError("Single Field must have both name and doc attributes.")

	# Creates single field
	global currentFieldName
	currentFieldName = attrName.value
	sf = SingleField(attrName.value, attrDoc.value)

	# type
	type = handleOneType(domSF)
	if type == None :
		raise StandardError("In single field named %s, the type of field is not defined" % sf.name )
	else :
		sf.type = type

	return sf


def handleOF( domOF ) :
	# name and doc
	attrName	= domOF.getAttributeNode("name")
	attrDoc		= domOF.getAttributeNode("doc")

	if attrName == None or attrDoc == None :
		raise StandardError("Optional Field must have both name and doc attributes.")

	# Creates optional field
	global currentFieldName
	currentFieldName = attrName.value
	of = OptionalField(attrName.value, attrDoc.value)

	# type
	type = handleOneType(domOF)
	if type == None :
		raise StandardError("In optional field named %s, the type of field is not defined" % of.name )
	else :
		of.type = type

	return of


def handlePAF( domPAF ) :
	# name and doc
	attrName	= domPAF.getAttributeNode("name")
	attrDoc		= domPAF.getAttributeNode("doc")

	if attrName == None or attrDoc == None :
		raise StandardError("Pair Associative Field must have both name and doc attributes.")

	# Creates pair associative field
	global currentFieldName
	currentFieldName = attrName.value
	paf = PairAssociativeField(attrName.value, attrDoc.value)

	# types
	types = handleTwoTypes(domPAF)
	if len(types) == 0 :
		raise StandardError("In pair associative field named %s, the type of field is not defined." % paf.name )
	elif len(types) == 1 :
		paf.keyType = Enum( currentNodeName, currentFieldName )
		paf.keyType.addValue( paf.name.upper(), paf.doc )
		paf.keyType.setDefaultValue( paf.name.upper() )
		paf.type = types[0]
	elif len(types) == 2 :
		paf.keyType	= types[0]
		paf.type	= types[1]
	else:
		raise StandardError("In pair associative field named %s, the type of field is not well defined." % paf.name )

	return paf


def handleMF( domMF ) :
	# name and doc
	attrName	= domMF.getAttributeNode("name")
	attrDoc		= domMF.getAttributeNode("doc")

	if attrName == None or attrDoc == None :
		raise StandardError("Multi Field must have both name and doc attributes.")

	# Creates multi field
	global currentFieldName
	currentFieldName = attrName.value
	mf = MultiField(attrName.value, attrDoc.value)

	# type
	type = handleOneType(domMF)
	if type == None :
		raise StandardError("In multi field named %s, the type of field is not defined" % sf.name )
	else :
		mf.type = type

	return mf


def handleDoxygen( domDoxygen, node ) :
	# docBrief
	docBriefs = domDoxygen.getElementsByTagName("docBrief")
	if docBriefs.length > 0 :
		node.docBrief = getText( docBriefs[0].childNodes )

	# doc
	docs = domDoxygen.getElementsByTagName("doc")
	for doc in docs :
		node.doc += getText( doc.childNodes ) + " "

	# ingroup
	ingroups = domDoxygen.getElementsByTagName("ingroup")
	for ingroup in ingroups :
		node.ingroup.append( getText(ingroup.childNodes) )


def handleDF( domDF ) :
	# Retrieves df attributes
	attrName = domDF.getAttributeNode("name")
	attrLinkToFields = domDF.getAttributeNode("linkToFields")

	# Checks
	if attrName == None or attrLinkToFields == None :
		raise StandardError("Dirty flags must have both name and linkToFields attributes.")

	#
	df = DirtyFlag(attrName.value, attrLinkToFields.value)
	return df


def handleNode( domNode ) :
	# Retrieves node attributes
	attrName = domNode.getAttributeNode("name")
	attrInherits = domNode.getAttributeNode("inherits")
	attrAbstract = domNode.getAttributeNode("abstract")

	# Constructs node
	global currentNodeName
	currentNodeName = attrName.value

	node = Node(attrName.value)

	# Prints a message
	print "Found %s" % node.name

	#
	if attrInherits != None :
		node.inherits = attrInherits.value.split()
	else :
		node.inherits = []
	if attrAbstract != None :
		if attrAbstract.value in ['true', 'false']:
			node.abstract = attrAbstract.value
		else:
			raise StandardError("abstract must be equal to true or false.")

	# Handles doxygen
	domDoxygens = domNode.getElementsByTagName("doxygen")
	if domDoxygens.length > 0 :
		handleDoxygen( domDoxygens[0], node )

	# Handles df (dirty flags)
	domDFs = domNode.getElementsByTagName("df")
	for domDF in domDFs:
		df = handleDF( domDF )
		print ("link('{}', '{}')".format(df.name, df.linkToFields))
		node.addDirtyFlag( df )

	# Handles enumeration definition
	for domChild in domNode.childNodes:
		if domChild.nodeName == 'enum':
			enum = handleEnum( domChild )
			node.addEnum( enum )

	# Handles sf (single field)
	domSingleFields = domNode.getElementsByTagName("sf")
	for domSingleField in domSingleFields :
		sf = handleSF( domSingleField )
		node.addField( sf )

	# Handles of (optional field)
	domOptionalFields = domNode.getElementsByTagName("of")
	for domOptionalField in domOptionalFields :
		of = handleOF( domOptionalField )
		node.addField( of )

	# Handles paf
	domPairAssociativeFields = domNode.getElementsByTagName("paf")
	for domPairAssociativeField in domPairAssociativeFields :
		paf = handlePAF( domPairAssociativeField )
		node.addField( paf )

	# Handles mf (multi-fields)
	domMultiFields = domNode.getElementsByTagName("mf")
	for domMultiField in domMultiFields :
		mf = handleMF( domMultiField )
		node.addField( mf )

	# @todo handles other field type.

	#@todo handle method, attribute...

	# Handles codehpp, includehpp, codecpp and includecpp
	domCodeHpps = domNode.getElementsByTagName("codehpp")
	for domCodeHpp in domCodeHpps :
		node.addCodeDeclaration( getText( domCodeHpp.childNodes ) )

	domIncludeHpps = domNode.getElementsByTagName("includehpp")
	for domIncludeHpp in domIncludeHpps :
		pathfilename = getText( domIncludeHpp.childNodes )
		if os.path.exists(pathfilename):
			with open( os.path.join(pathfilename), 'r' ) as file:
				node.addCodeDeclaration( file.read() )
		else:
			print ('WARNING: %s in <includehpp> refers to a missing path !' % pathfilename )

	domCodeCpps = domNode.getElementsByTagName("codecpp")
	for domCodeCpp in domCodeCpps :
		node.addCodeImplementation( getText( domCodeCpp.childNodes ) )

	domIncludeCpps = domNode.getElementsByTagName("includecpp")
	for domIncludeCpp in domIncludeCpps :
		pathfilename = getText( domIncludeCpp.childNodes )
		if os.path.exists(pathfilename):
			with open( os.path.join(pathfilename), 'r' ) as file:
				node.addCodeImplementation( file.read() )
		else:
			print ('WARNING: %s in <includecpp> refers to a missing path !' % pathfilename )

	return node



def handleListEnum( domEnums ):
	dbNodeEnums = []
	for domEnum in domEnums :
		attrName = domEnum.getAttributeNode("name")
		if attrName == None:
			print ('No name in vgd::node enum')
		else:
			print ('Found vgd::node::{} enum'.format(attrName.value))
		enum = handleEnum(domEnum, True)
		dbNodeEnums.append( enum )

	return dbNodeEnums


def handleListNode( domNodes ) :
	dbNodes = {}
	for domNode in domNodes :
		node = handleNode(domNode)
		if node.name not in dbNodes :
			dbNodes[node.name] = node
		else :
			print "Unable to add node named %s." % node.name

	return dbNodes


def handleRootDom( domRoot ):
	# Process <enum> in <nodes>
	print ('Process <enum> in <nodes>')
	domEnums = []
	nodesElement = domRoot.documentElement
	for element in nodesElement.childNodes:
		if element.nodeType == element.ELEMENT_NODE and element.tagName == 'enum':
			domEnums.append( element )
	dbNodeEnums = handleListEnum( domEnums )
	print

	# Process <node> in <nodes>
	print ('Process <node> in <nodes>')
	domNodes = domRoot.getElementsByTagName("node")
	dbNodes = handleListNode( domNodes )
	print

	return (dbNodeEnums, dbNodes)
