#!/usr/bin/env python

# VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2013, Nicolas Papier.
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

import datetime
import os

from domParser import *

inputFile					= "nodes.xml"
headersOuputDir				= "vgd/include/vgd/node"
implementationsOutputDir	= "vgd/src/node"
headersOuputDir				= "../" + headersOuputDir
implementationsOutputDir	= "../" + implementationsOutputDir



# Generates vgd/node/Enum.[hpp,cpp]
def generateEnumHeader( fd, dbNodeEnums ):
	# copyright
	generateCopyright( fd )

	# ifndef
	beginDefine = """#ifndef _VGD_NODE_ENUM_HPP
#define _VGD_NODE_ENUM_HPP\n\n

#include "vgd/field/Enum.hpp"

"""

	fd.write(beginDefine)

	# begin namespace
	generateBeginNamespace( fd )

	for enum in dbNodeEnums:
		str = enum.generateTYPEDEF()
		fd.write( str + '\n' * 4 )

	# end namespace
	generateEndNamespace( fd )

	#endif
	endDefine = """#endif //#ifndef _VGD_NODE_ENUM_HPP\n"""
	fd.write( endDefine )


def generateEnumImpl( fd, dbNodeEnums ):
	# copyright
	generateCopyright( fd )

	# includes
	fd.write("#include \"vgd/node/Enum.hpp\"\n\n\n" )

	# begin namespace
	#generateBeginNamespace( fd )

	# end namespace
	#generateEndNamespace( fd )


def generatesEnum( dbNodeEnums ):
	print ("Generating vgd/node/Enum.hpp and Enum.cpp")
	with open( os.path.join(headersOuputDir, "Enum.hpp"), 'w' ) as fh :
		generateEnumHeader( fh, dbNodeEnums )
	with open( os.path.join(implementationsOutputDir, "Enum.cpp"), 'w+' ) as fcpp :
		generateEnumImpl( fcpp, dbNodeEnums )
	print



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
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< nodeType > create( const std::string nodeName, const uint8 index );
	
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



vgd::Shp< nodeType > nodeType::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< nodeType > node = nodeType::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

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
	IMPLEMENT_INDEXABLE_CLASS_HPP( nodeType );
private:
	static const vgd::basic::RegisterNode<nodeType> m_registrationInstance;\n"""

	fd.write( str.replace("nodeType", node.name) )

def generateMETA_NODE_CPP( fd, node ) :

	str = """IMPLEMENT_INDEXABLE_CLASS_CPP( nodeType );



const vgd::basic::RegisterNode<nodeType> nodeType::m_registrationInstance;
\n\n\n"""

	fd.write( str.replace("nodeType", node.name) )


def getDocOfFields( node ):
	str = ""
	for field in node.fields.itervalues() :
		if len(field.type.generateDefaultValue()) == 0 :
			if field.isOptional():
				str += "\n * - %s \c [%s] = empty<br>\n" % (field.generateCompleteType(), field.name)
			else:
				str += "\n * - %s \c %s = empty<br>\n" % (field.generateCompleteType(), field.name)
		else:
			if field.isOptional():
				str += "\n * - %s \c [%s] = %s<br>\n" % (field.generateCompleteType(), field.name, field.type.generateDefaultValue())
			else:
				str += "\n * - %s \c %s = %s<br>\n" % (field.generateCompleteType(), field.name, field.type.generateDefaultValue())
		if len(field.doc) > 0:
			str +=   " *   %s<br>\n" % field.doc
		str += " *<br>"
	return str


def generateNodeHeader( fd, node ) :
	# copyright
	generateCopyright( fd )

	# ifndef
	beginDefine = """#ifndef _VGD_NODE_NEWNODE_HPP
#define _VGD_NODE_NEWNODE_HPP\n\n"""

	fd.write( beginDefine.replace("NEWNODE", node.name.upper()) )

	# includes
	setIncludes = set()
	for field in node.fields.itervalues() :
		# type
		incoming = field.type.getNormalizedName()
		#	is type an enum ?
		if field.type.isAnEnum:
			# is an enum without a namespace ?
			if not field.type.namespace:
				# no, do nothing
				setIncludes.add('Enum')
				continue
			# else yes, adds #include ...

		setIncludes.add(incoming)

		# keyType
		if isinstance(field, PairAssociativeField ) :
			incoming = field.keyType.getNormalizedName()
			setIncludes.add(incoming)
		#else nothing to do

	listIncludes = list(setIncludes)
	listIncludes.sort()
	for include in listIncludes :
		fd.write( "#include \"vgd/field/%s.hpp\"\n" % include )

	for base in node.inherits :
		fd.write( "#include \"vgd/node/BASECLASS.hpp\"\n".replace("BASECLASS", base ) )

	# extra-include-hpp
	if len(node.extraIncludeHpp) > 0:
		fd.write( node.extraIncludeHpp )

	#
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
#	fd.write( """ *\n""" )

	for ingroup in node.ingroup :
		fd.write( """ * @ingroup %s\n""" % ingroup )

	fd.write( " */\n" )

	# begin class
	fd.write( "struct VGD_API %s" % node.name )

	if len(node.inherits)>0:	fd.write(" : ")
	for i, base in enumerate(node.inherits) :
		fd.write( "public vgd::node::%s" % base )
		if i != len(node.inherits)-1 :
			fd.write( ", " )

	# begin class declaration
	fd.write( "\n{\n" )

	# Enumeration definition
	for enum in node.enums:
		str = enum.generateTYPEDEF()
		fd.write( str + '\n' * 4 )

	# META_NODE_HPP.factories
	if not node.abstract:
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

	# Dirty flags
	fd.write( """\n\n	/**
	 * @name Dirty flags enumeration
	 */
	//@{\n\n""" );

	for df in node.dirtyFlags.itervalues():
		fd.write( """	/**
	 * @brief Returns name of dirty flag that is invalidate when \c {0} field is modified.
	 */
	static const std::string getDF{1}();\n""".format( df.name, capitalize(df.name) ) )

	fd.write( """\n	//@}\n""" )

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
	if not node.abstract:
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

	# extra-include-cpp
	if len(node.extraIncludeCpp) > 0:
		fd.write( node.extraIncludeCpp )

	# begin namespace
	generateBeginNamespace( fd )

	# META_NODE_CPP.factories
	if not node.abstract:
		generateFactoriesImpl( fd, node )

	# Constructor
	str = """NodeName::NodeName( const std::string nodeName )"""
	fd.write( str.replace( "NodeName", node.name ) )

	if len(node.inherits)>0:	fd.write(" :\n")
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

	# dirty flags in constructor
	dfs = ""
	links = ""
	for df in node.dirtyFlags.itervalues():
		dfs += "	addDirtyFlag(getDF{0}());\n".format( capitalize(df.name) )
		for linkToField in df.linkToFields:
			links += "	link( getF{0}(), getDF{1}() );\n".format( capitalize(linkToField), capitalize(df.name) )

	if len(dfs) > 0:
		fd.write( """\n	// Adds dirty flag(s)\n""" )
		fd.write( dfs )

	if len(node.fields)>0:
		fd.write("""\n	// Sets link(s)\n""")
		fd.write( links )
		fd.write("""\n	link( getDFNode() );\n""")
	fd.write("""}\n\n\n\n""")

	# setToDefaults
	str = """void NodeName::setToDefaults( void )
{\n"""
	fd.write( str.replace("NodeName", node.name) )

	for base in node.inherits :
		fd.write( "\tBASECLASS::setToDefaults();\n".replace("BASECLASS", base ) )

	for field in node.fields.itervalues() :
		str = field.generateDefaultSetter()
		if str != None :
			fd.write( str + "\n" )

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
			fd.write( str + "\n" )

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

	# Dirty flags
	if len(node.dirtyFlags)>0:
		fd.write("// DIRTY FLAG(S)\n")
		for df in node.dirtyFlags.itervalues():
			str = """const std::string {0}::getDF{1}()
{{
	return \"df_{2}\";
}}\n\n\n""".format(node.name, capitalize(df.name), df.name.lower())

			fd.write( str )

	# Code implementation
	if len(node.codeImplementation) > 0 :
		fd.write( node.codeImplementation )

	# META_NODE_CPP.protected/private section
	if not node.abstract:
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

namespace vgd { template<class T> struct Shp; }
namespace vgd { namespace field { struct Enum; } }



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

	/**
	 * @brief Converts the given enumeration value to the real enumeration type.
	 *
	 * @param enumValue	the enumeration value to convert
	 *
	 * @return the desired enum type
	 */
	static const vgd::Shp< vgd::field::Enum > toEnum( const int enumValue );

private:
	typedef std::map< const int, std::string > ToStringType;	//< typedef for the registry storing association between enum value and enum string
	static ToStringType m_toString;								//< instanciation of the registry

	typedef std::map< const int, vgd::Shp< vgd::field::Enum > > ToEnumType;	//< typedef for the registry storing association between enum value and the real enum type
	static ToEnumType m_toEnum;												//< instanciation of the registry

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

#include <vgDebug/helpers.hpp>
#include <vgd/Shp.hpp>
#include <vgd/field/Enum.hpp>
""")

		iterItems = EnumRegistry.getIterItems()
		includeSet = set()
		for enumString, enumValue in iterItems:
			# examples of enumString 'PostProcessing.input1.INPUT1_TEXTURE0' or 'vgd.node.BIND_OFF'
			enumNode = enumString.split('.')[0]
			if enumNode != 'vgd':
				includeSet.add(enumNode)
		for include in sorted(includeSet):
			fcpp.write( """#include <vgd/node/%s.hpp>\n""" % include )

		fcpp.write("""


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



const vgd::Shp< vgd::field::Enum > EnumRegistry::toEnum( const int enumValue )
{
	if ( m_toEnum.empty() )
	{
		// Initializes the registry (only once).
		initialize();
	}

	ToEnumType::const_iterator iter = m_toEnum.find( enumValue );

	if ( iter != m_toEnum.end() )
	{
		return iter->second;
	}
	else
	{
		return vgd::makeShp( new vgd::field::Enum() );
	}
}



EnumRegistry::ToStringType EnumRegistry::m_toString;



EnumRegistry::ToEnumType EnumRegistry::m_toEnum;



void EnumRegistry::initialize()
{
	// Initializes m_toString map
""")
		# m_toString
		iterItems = EnumRegistry.getIterItems()
		for enumString, enumValue in iterItems:
			tmp = enumString.split('.')
			print ("toString({})={} extracted from {}".format(enumValue, tmp[-1], enumString))
			enumString = tmp[-1]
			fcpp.write( """
	//
	#ifdef _DEBUG
	if ( m_toString.find( {enumValue} ) != m_toString.end() )
	{{
		vgLogDebug("({enumValue}, {enumString}) already in m_toString enum registry");
		assert( false && "({enumValue}, {enumString}) already in registry" );
	}}
	#endif

	m_toString[ {enumValue} ] = std::string("{enumString}");
""".format( enumValue=enumValue, enumString=enumString )	)

		# m_toEnum
		fcpp.write( """
	// Initializes m_toEnum map
""")

		print
		for enumString, enumValue in EnumRegistry.getIterItems():
			enum = EnumRegistry.getEnum(enumString)
			if len(enum.nodeName) == 0:
				# Enum not defined in a vgd::node::Node
				enumConstructor = '{}::{}({})'.format( enum.namespace, enum.typename, enumValue )
				print ("toEnum({})={}".format(enumValue, enumConstructor))
			else:
				enumNode, enumField, enumString = enumString.split('.')
				# Tests if the last part of field name is 'Parameter' (hack for PAF)
				if enumField.rfind('Parameter') == -1:
					enumValueType = enumField[0].upper() + enumField[1:] + 'ValueType'
				else:
					enumValueType = enumField[0].upper() + enumField[1:] + 'Type'
				enumConstructor = 'vgd::node::{}::{}({})'.format(enumNode, enumValueType, enumValue)
				print ("toEnum({})={}".format(enumValue, enumConstructor))
			fcpp.write( """
	//
	#ifdef _DEBUG
	if ( m_toEnum.find( {0} ) != m_toEnum.end() )
	{{
		vgLogDebug("({0}, {1}) already in m_toEnum enum registry");
		assert( false && "({0}, {1}) already in registry" );
	}}
	#endif

	m_toEnum[ {0} ] = vgd::makeShp( new {2} );
""".format( enumValue, enumString, enumConstructor ) )


		fcpp.write( """
}



} // namespace node

} // namespace vgd
""")


### Main ###

# Parses node description file and generates node database
print ("Reading %s" % inputFile)
domRoot = xml.dom.minidom.parse(inputFile)
print ("\nAnalysing xml")
(dbNodeEnums, dbNodes) = handleRootDom( domRoot )


if os.path.isdir(headersOuputDir) is False :
	os.makedirs(headersOuputDir)
if os.path.isdir(implementationsOutputDir) is False :
	os.makedirs(implementationsOutputDir)

print
print ("Generating code for nodes")
generatesNodes( dbNodes )

print
#EnumRegistry.generate()
generateEnumerationRegistry()

print
generatesEnum( dbNodeEnums )
