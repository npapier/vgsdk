#!/usr/bin/env python

# VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
# Distributed under the terms of the GNU Library General Public License (LGPL)
# as published by the Free Software Foundation.
# Author Nicolas Papier

# @todo mask type
# typedef vgd::field::SFEnum 	FOrientationType => OrientationType
# getFFieldNameRO/RW() accessors
# @todo splits doxygen comment
# @todo Special type for Flags/Mask and special field ? see TBitSet in GLSLState class
# @todo Boost.Optional OSF, OMF (OptionalSingleField, OptionalMultiField) ...
# @todo vgio ?
# @todo generates enumRegistry for vgsdk see META_NODE_HPP, META_NODE_CPP, doc, annotation.
# @order in enum
# @todo df, link(s) and methods

from __future__ import with_statement
import datetime
import os

#try:
#	import toto
#except ImportError:
#	import titi


from domParser import *

inputFile					= "nodes.xml"
headersOuputDir				= "vgd/include/vgd/node"
implementationsOutputDir	= "vgd/src/node"
headersOuputDir				= "../" + headersOuputDir
implementationsOutputDir	= "../" + implementationsOutputDir



# Parses node description file and generates node database
print ("Reads %s" % inputFile)
domRoot = xml.dom.minidom.parse(inputFile)
print ("\nAnalyses xml")
dbNodes = handleRootDom( domRoot )

# Generates node code
# @todo In 2009, adds 2008-2009 to copyright notice
def generateCopyright( fd ) :
	copyright = """// VGSDK - Copyright (C) %s, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier\n\n"""
	fd.write( copyright % datetime.date.today().year )

def generateBeginNamespace( fd ) :
	beginNamespace = """namespace vgd
{

namespace node
{\n\n\n\n"""

	fd.write( beginNamespace )

def generateEndNamespace( fd ) :
	endNamespace = """} // namespace node

} // namespace vgd

"""

	fd.write( endNamespace )

def generateFactoriesHeader( fd, node ) :
	str = """	/**
	 * @name Factories
	 */
	//@{

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values
	 */
	static vgd::Shp< nodeType > create( const std::string nodeName = "NoName" );

	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< nodeType > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}\n"""

	fd.write( str.replace("nodeType", node.name) )

def generateFactoriesImpl( fd, node ) :
	str = """vgd::Shp< nodeType > nodeType::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< nodeType > node( new nodeType(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< nodeType > nodeType::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< nodeType > node = nodeType::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}
\n\n\n"""

	fd.write( str.replace("nodeType", node.name) )

def generateMETA_NODE_HPP( fd, node ) :
	str = """public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , nodeType );
private:
	static const vgd::basic::RegisterNode<nodeType> m_registrationInstance;\n"""

	fd.write( str.replace("nodeType", node.name) )

def generateMETA_NODE_CPP( fd, node ) :

	str = """IMPLEMENT_INDEXABLE_CLASS_CPP( , nodeType );



const vgd::basic::RegisterNode<nodeType> nodeType::m_registrationInstance;
\n\n\n"""

	fd.write( str.replace("nodeType", node.name) )


def getDocOfFields( node ):
	str = ""
	for field in node.fields.itervalues() :
		if len(field.type.generateDefaultValue()) == 0 :
			str += "\n *	- %s \c %s = empty\\n\n" % (field.generateCompleteType(), field.name)
		else:
			if field.isOptional():
				str += "\n *	- %s \c [%s] = %s\\n\n" % (field.generateCompleteType(), field.name, field.type.generateDefaultValue())
			else:
				str += "\n *	- %s \c %s = %s\\n\n" % (field.generateCompleteType(), field.name, field.type.generateDefaultValue())
		str +=   " *		%s" % field.doc
	return str


def generateNodeHeader( fd, node ) :
	# copyright
	generateCopyright( fd )

	# ifndef
	beginDefine = """#ifndef _VGD_NODE_NEWNODE_HPP
#define _VGD_NODE_NEWNODE_HPP\n\n"""

	fd.write( beginDefine.replace("NEWNODE", node.name.upper()) )

	# includes
	setIncludes = []
	for field in node.fields.itervalues() :
		# type
		incoming = field.type.getNormalizedName()
		if incoming not in setIncludes :
			setIncludes.append(incoming)
		# keyType
		if isinstance(field, PairAssociativeField ) :
			incoming = field.keyType.getNormalizedName()
			if incoming not in setIncludes :
				setIncludes.append(incoming)
		#else nothing to do

	setIncludes.sort()

	for include in setIncludes :
		fd.write( "#include \"vgd/field/%s.hpp\"\n" % include )

	for base in node.inherits :
		fd.write( "#include \"vgd/node/BASECLASS.hpp\"\n".replace("BASECLASS", base ) )

	fd.write( "\n\n\n" )

	# begin namespace
	generateBeginNamespace( fd )

	# class doxygen
	classDocBrief = """/**
 * @brief docBrief\n"""

	classDoc = """ *
 * doc
 *
"""

	classFields = """ * New fields defined by this node :NEWFIELDS
 *
"""

	fd.write( classDocBrief.replace("docBrief", node.docBrief) )
	fd.write( classDoc.replace("doc", node.doc) )

	if len(node.fields) == 0:
		fd.write( " * No new field defined by this node.\n" )
	else:
		fd.write( classFields.replace("NEWFIELDS", getDocOfFields(node) ) )

	if len(node.inherits) > 0:
		toProcess = node.inherits[:]
		while ( len(toProcess) > 0 ):
			nodeName = toProcess.pop()
			if nodeName in dbNodes :
				baseNode = dbNodes[nodeName]
				toProcess.extend( baseNode.inherits )
				fd.write( """ *\n * Inherited fields from %s:%s\n""" % (nodeName, getDocOfFields(baseNode) ) )
			else:
				print( "Warning %s is not generated from xml. So inherited fields are not documented" % nodeName )
	fd.write( """ *\n""" )

	for ingroup in node.ingroup :
		fd.write( """ * @ingroup %s\n""" % ingroup )

	fd.write( " */\n" )

	# begin class
	fd.write( "struct VGD_API %s : " % node.name )

	for i, base in enumerate(node.inherits) :
		fd.write( "public vgd::node::%s" % base )
		if i != len(node.inherits)-1 :
			fd.write( ", " )

	# begin class declaration
	fd.write( "\n{\n" )

	# META_NODE_HPP.factories
	generateFactoriesHeader( fd, node )

	# Accessors (for fields)
	for field in node.fields.itervalues() :
		str = field.generateAccessorsHeader()
		fd.write( str )

	# Field name accessors
	str = """\n\n\n	/**
	 * @name Field name accessors
	 */
	//@{\n\n"""
	fd.write( str )

	for i, field in enumerate(node.fields.itervalues()) :
		str = """	/**
	 * @brief Returns the name of field \c fieldName.
	 *
	 * @return the name of field \c fieldName.
	 */
	static const std::string getFFieldName( void );\n"""

		str = str.replace( "fieldName", field.name )
		str = str.replace( "FieldName", field.getFieldName() )
		fd.write( str )
		if i != len(node.fields)-1 :
			fd.write( "\n" )

	fd.write( "\n	//@}\n" )

	# Code declaration
	if len(node.codeDeclaration) > 0 :
		fd.write( node.codeDeclaration )

	# Constructors
	str = """\n\n\n	/**
	 * @name Constructor and initializer methods
	 */
	//@{

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}

protected:
	/**
	 * @brief Default constructor
	 */
	NodeName( const std::string nodeName );\n\n"""

	fd.write( str.replace("NodeName", node.name) )

	# META_NODE_HPP.protected/private section
	generateMETA_NODE_HPP( fd, node )

	# end class declaration
	fd.write("};\n\n\n\n")

	# end namespace
	generateEndNamespace( fd )

	#endif
	endDefine = """#endif //#ifndef _VGD_NODE_NEWNODE_HPP\n"""
	fd.write( endDefine.replace("NEWNODE", node.name.upper()) )



def generateNodeImpl( fd, node ) :
	# copyright
	generateCopyright( fd )

	# includes
	fd.write( "#include \"vgd/node/NodeName.hpp\"\n\n".replace( "NodeName", node.name ) )
	fd.write( "#include \"vgd/node/detail/Node.hpp\"\n\n\n\n" )

	# begin namespace
	generateBeginNamespace( fd )

	# META_NODE_CPP.factories
	generateFactoriesImpl( fd, node )

	# Constructor
	str = """NodeName::NodeName( const std::string nodeName ) :\n"""
	fd.write( str.replace( "NodeName", node.name ) )

	for i, base in enumerate(node.inherits):
		if i == 0:
			fd.write( "\tvgd::node::%s( nodeName )" % base )
		else:
			fd.write( "\tvgd::node::%s()" % base )
		if i != len(node.inherits)-1:
			fd.write( ",\n" )

	fd.write("""\n{
	// Adds field(s)\n""")

	for field in node.fields.itervalues() :
		str = "\taddField( new FFieldNameType(getFFieldName()) );\n"
		fd.write( str.replace( "FieldName", field.getFieldName() ) )

	fd.write("""\n	// Sets link(s)
	link( getDFNode() );
}\n\n\n\n""")

	# setToDefaults
	str = """void NodeName::setToDefaults( void )
{\n"""
	fd.write( str.replace("NodeName", node.name) )

	for base in node.inherits :
		fd.write( "\tBASECLASS::setToDefaults();\n".replace("BASECLASS", base ) )

	for field in node.fields.itervalues() :
		str = field.generateDefaultSetter()
		if str != None :
			fd.write( "\t" + str + "\n" )

	fd.write("}\n\n\n\n")

	# setOptionalsToDefaults
	str = """void NodeName::setOptionalsToDefaults()
{\n"""
	fd.write( str.replace("NodeName", node.name) )

	for base in node.inherits :
		fd.write( "\tBASECLASS::setOptionalsToDefaults();\n".replace("BASECLASS", base ) )

	for field in node.fields.itervalues() :
		str = field.generateOptionalDefaultSetter()
		if str != None :
			fd.write( "\t" + str + "\n" )

	fd.write("}\n\n\n\n")

	# Accessors (for fields)
	for field in node.fields.itervalues() :
		str = field.generateAccessorsImpl( node.name )
		fd.write( str )

	# Field name accessors
	fd.write( "// Field name accessor(s)\n" )
	for i, field in enumerate(node.fields.itervalues()) :
		str = """const std::string NewNode::getFFieldName( void )
{
	return \"f_fieldName\";
}\n\n\n\n"""

		str = str.replace( "NewNode", node.name )
		str = str.replace( "FieldName", field.getFieldName() )
		str = str.replace( "fieldName", field.name )
		fd.write( str )

	# Code implementation
	if len(node.codeImplementation) > 0 :
		fd.write( node.codeImplementation )

	# META_NODE_CPP.protected/private section
	generateMETA_NODE_CPP( fd, node )

	# end namespace
	generateEndNamespace( fd )



def generatesNodes( dbNodes ) :
	for nodeName, node in dbNodes.iteritems() :
		print ("%s" % nodeName)
		with open( os.path.join(headersOuputDir, nodeName + ".hpp"), 'w' ) as fh :
			generateNodeHeader( fh, node )
		with open( os.path.join(implementationsOutputDir, nodeName + ".cpp"), 'w+' ) as fcpp :
			generateNodeImpl( fcpp, node )
		print



def generateEnumerationRegistry():
	print ("Generates Enumeration registry")

	iterItems = EnumRegistry.getIterItems()
	with open( os.path.join(headersOuputDir, "EnumRegistry" + ".hpp"), 'w' ) as fhpp :
		generateCopyright(fhpp)
		fhpp.write("""#ifndef _VGD_NODE_ENUMREGISTRY_HPP
#define _VGD_NODE_ENUMREGISTRY_HPP

#include <map>
#include <string>
#include "vgd/vgd.hpp"



namespace vgd
{

namespace node
{

struct VGD_API EnumRegistry
{
	/**
	 * @brief Converts to a string an enumeration value
	 *
	 * @param enumValue	the enumeration value to convert
	 *
	 * @return the string representing the enumeration value
	 */
	static const std::string toString( const int enumValue );

private:
	typedef std::map< const int, std::string > ToStringType;	//< typedef for the registry storing association between enum value and enum string
	static ToStringType m_toString;								//< instanciation of the registry

	/**
	 * @brief Initializes the registry
	 */
	static void initialize();
};

} // namespace node

} // namespace vgd

#endif // #ifndef _VGD_NODE_ENUMREGISTRY_HPP
""")

	with open( os.path.join(implementationsOutputDir, "EnumRegistry" + ".cpp"), 'w' ) as fcpp :
		generateCopyright(fcpp)
		fcpp.write("""#include "vgd/node/EnumRegistry.hpp"

#include <vgDebug/convenience.hpp>



namespace vgd
{

namespace node
{



const std::string EnumRegistry::toString( const int enumValue )
{
	if ( m_toString.empty() )
	{
		// Initializes the registry (only once).
		initialize();
	}

	ToStringType::const_iterator iter = m_toString.find( enumValue );

	if ( iter != m_toString.end() )
	{
		return iter->second;
	}
	else
	{
		return std::string("");
	}
}



EnumRegistry::ToStringType EnumRegistry::m_toString;



void EnumRegistry::initialize()
{""")
		for enumString, enumValue in iterItems:
			print enumString, enumValue
			enumString = enumString.split('.')[1]
			fcpp.write( """
	//
	#ifdef _DEBUG
	if ( m_toString.find( %s ) != m_toString.end() )
	{
		vgLogDebug("(%s, %s) already in enum registry");
		assert( false && "(%s, %s) already in registry" );
	}
	#endif

	m_toString[ %s ] = std::string("%s");
""" % ( enumValue, enumValue, enumString, enumValue, enumString, enumValue, enumString ) )

		fcpp.write( """
}



} // namespace node

} // namespace vgd
""")



if os.path.isdir(headersOuputDir) is False :
	os.makedirs(headersOuputDir)
if os.path.isdir(implementationsOutputDir) is False :
	os.makedirs(implementationsOutputDir)

print
print ("Generates code for nodes")
generatesNodes( dbNodes )

print
#EnumRegistry.generate()
generateEnumerationRegistry()