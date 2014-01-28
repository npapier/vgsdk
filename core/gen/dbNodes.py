#!/usr/bin/env python

# VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2013, 2014, Nicolas Papier.
# Distributed under the terms of the GNU Library General Public License (LGPL)
# as published by the Free Software Foundation.
# Author Nicolas Papier

from collections import OrderedDict


def capitalize( str ):
	"""Return a copy of the string with only its first character capitalized. Other characters are left unchanged (unlike python capitalize)"""
	return str[0].upper() + str[1:]

############
# REGISTRY #
############
class EnumRegistry :
	_id		= 255

	_values	= {}	# enum_string, enum_id
	_rvalues = {}	# enum_id, enum_string
	_enum = {}		# enum_string, enum class

	@classmethod
	def nextID( self ):
		self._id += 1
		return self._id

	@classmethod
	def _register_( self, enum, newValue ):
		if newValue not in self._values:
			newID = self.nextID()
			self._values[newValue] = newID
			self._rvalues[newID] = newValue
			self._enum[newValue] = enum
		else:
			raise StandardError("Enum value %s already defined." % newValue)


	@classmethod
	def register( self, enum, enumValue ):
		newValue = enum.buildStringID( enumValue )
		self._register_( enum, newValue )


	@classmethod
	def getID( self, enum, enumValue ):
		stringID = enum.buildStringID( enumValue )
		if stringID in self._values :
			return self._values[stringID]
		else :
			raise StandardError("Enum value %s not registered" % stringID )

	@classmethod
	def getString( self, id ):
		if id in self._rvalues:
			enumString = self._rvalues[id]
			return enumString.split('.')[-1]
		else:
			raise StandardError("Enum value %i not registered" % id )


	@classmethod
	def getIterItems( self ):
		return self._values.iteritems()

	@classmethod
	def getEnum( self, str ):
		return self._enum[str]


########
# TYPE #
########
class Type :
	def __init__( self, name, nodeName = "", fieldName = "" ):
		self.namespace		= ""
		self.name			= name

		self.defaultValue	= ""

		self.nodeName = nodeName
		self.fieldName = fieldName
		if len(fieldName)>0:
			self.FieldName = capitalize(fieldName)
		else:
			self.FieldName = ""

		self.isAnEnum = False	# True for type inheriting from vgd::field::Enum

		# @todo range

	def generateTYPEDEF( self ):
		str = """\t/**
\t * @brief Type definition of the value contained by field named \c {fieldName}.
\t */
\ttypedef {type} {FieldName}ValueType;"""
		return str.format( fieldName=self.fieldName, type=self.generateTypeWithNamespace(), FieldName=self.FieldName ) # @todo ValueType => Type

	def generateTypeWithNamespace( self ):
		if len(self.namespace) > 0 :
			return self.namespace + "::" + self.name
		else :
			return self.name

	def generateDefaultValue( self ):
		if len(self.namespace) > 0 :
			return self.namespace + '::' + self.name + '(' + self.defaultValue + ')'
		else:
			if len(self.defaultValue)>0:
				return '(' + self.defaultValue + ')'
			else:
				return self.defaultValue

	def getNormalizedName( self ):
		return capitalize(self.name)


class Enum ( Type ):

	def buildStringID( self, enumValue ):
		"""Returns, for examples, 'GeoMorph.method.NORMALIZED' for enum defined in a node field or in a node, otherwise returns
			vgd.node.BIND_PER_VERTEX for enum defined in <nodes>"""
		if len(self.nodeName) == 0:
			return '{}.{}'.format( self.namespace.replace('::', '.'), enumValue )
		else:
			return self.nodeName + '.' + self.fieldName + '.' + enumValue

	def __init__( self, nodeName = '', fieldName = ''):
		"""Construct an enumeration not defined in a vgd::node::nodeName using Enum()"""
		Type.__init__( self, 'enum', nodeName, fieldName )
		self.typename = ''	# enum typename {...};
		self.values = {}	# enum_string, enum_doc

	def setTypename( self, value ):
		self.typename = value

	def addValue( self, value, docValue = "" ):
		if value not in self.values :
			self.values[value] = docValue
			EnumRegistry.register( self, value )

	def setDefaultValue( self, defaultValue ):
		if defaultValue in self.values :
			self.defaultValue = defaultValue
		else :
			raise StandardError("Try to set unknown value %s as the default value for an enum." % defaultValue )


	# Overriden
	def generateTYPEDEF( self ):

		str =	"""\t/**
\t * @brief Definition of symbolic values
\t */
\t%s;
""" % self._generateDefinition()

		strValues = ""
		for value in self._getIds():
			strValues += """\t\t\tretVal.push_back( %s );\n""" % value

		strStrings = ""
		for string in self._getStrings():
			strStrings += """\t\t\tretVal.push_back( "%s" );\n""" % string

# @todo comments in generated code
		definitionOfFieldNameType = """
	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct FieldNameType : public vgd::field::Enum
	{
		FieldNameType()
		{}

		FieldNameType( const int v )
		: vgd::field::Enum(v)
		{}

		FieldNameType( const FieldNameType& o )
		: vgd::field::Enum(o)
		{}

		FieldNameType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

%s
			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

%s
			return retVal;
		}
	};""" % (strValues, strStrings)

		if len(self.nodeName) == 0:
			str += definitionOfFieldNameType.replace( "FieldNameType", self.typename )		# @todo ValueType => Type
		else:
			str += definitionOfFieldNameType.replace( "FieldNameType", self.FieldName + "ValueType" )		# @todo ValueType => Type

		return str

	#
	def _generateDefinition( self ):
		# begin definition
		if len(self.nodeName)==0:
			str = "enum\n\t{\n"
		else:
			str = "enum %s \n\t{\n" % self.typename
		# values
		for (value, docValue) in self.values.iteritems() :
			valueID = EnumRegistry.getID(self, value)
			str += "\t\t%s = %i," % ( value, valueID )
			str += "\t///< %s\n" % docValue
		# default value
		str += "\t\tDEFAULT_%s = %s\t///< %s\n" % ( self.fieldName.upper(), self.defaultValue, self.values[self.defaultValue] )
		# end definition
		str += "\t}"

		return str


	def _getIds( self ):
		keys = self.values.keys()
		ids = [ EnumRegistry.getID(self, key) for key in keys ]
		return sorted(ids)

	def _getStrings( self ):
		sortedIds = self._getIds()
		return [ EnumRegistry.getString(id) for id in sortedIds ]


##############
# DIRTY FLAG #
##############
class DirtyFlag:
	def __init__( self, name, linkToFields ):
		self.name			= name
		self.linkToFields	= linkToFields.split()


#########
# FIELD #
#########


declDefautFieldname = """
	/**
	 * @brief The default value of field named \c fieldName.
	 */
	static const FieldNameValueType DEFAULT_FIELDNAME;\n"""

defDefaultFieldname = """
const NewNode::FieldNameValueType NewNode::DEFAULT_FIELDNAME = {defaultValue};


"""


class Field :

	def __init__( self, name, doc ) :
		self.type		= None
		self.name		= name
		self.doc		= doc

	def generateAccessorsHeader( self ) :
		raise StandardError("Field::generateAccessorsHeader() not implemented")

	def generateAccessorsImpl( self ) :
		raise StandardError("Field::generateAccessorsImpl() not implemented")

	def generateDefaultSetter( self ) :
		raise StandardError("Field::generateDefaultSetter() not implemented")

	def generateOptionalDefaultSetter( self ) :
		raise StandardError("Field::generateOptionalDefaultSetter() not implemented")

	def generateCompleteType( self ) :
		raise StandardError("Field::generateCompleteType() not implemented")

	def isOptional( self ):
		return False

	def getFieldName( self ):
		return capitalize(self.name)


class SingleField ( Field ) :

	def __init__( self, name, doc ) :
		Field.__init__( self, name, doc )

	def generateAccessorsHeader( self ) :
		str = """\n\n\n	/**
	 * @name Accessors to field fieldName
	 */
	//@{

TYPEDEF_FIELDNAMEVALUETYPE
DECL_DEFAULT_FIELDNAME
	/**
	 * @brief Type definition of the field named \c fieldName
	 */
	typedef vgd::field::TSingleField< InternalFieldNameValueType > FFieldNameType;


	/**
	 * @brief Gets the value of field named \c fieldName.
	 */
	const FieldNameValueType getFieldName() const;

	/**
	 * @brief Sets the value of field named \c fieldName.
	 */
	void setFieldName( const FieldNameValueType value );

	//@}\n"""

		if self.type.name == "enum" or self.type.isAnEnum:
			str = str.replace( "InternalFieldNameValueType", "vgd::field::Enum" )
			str = str.replace( 'DECL_DEFAULT_FIELDNAME', '' )
		else:
			str = str.replace( "InternalFieldNameValueType", "FieldNameValueType" )
			str = str.replace( 'DECL_DEFAULT_FIELDNAME', declDefautFieldname )

		str = str.replace( "TYPEDEF_FIELDNAMEVALUETYPE", self.type.generateTYPEDEF() )		# @todo ValueType => Type
		str = str.replace( "fieldName", self.name )
		str = str.replace( "FieldName", self.getFieldName() )
		str = str.replace( "FIELDNAME", self.getFieldName().upper() )
		str = str.replace( "FieldType", self.type.name )

		return str

	def generateAccessorsImpl( self, nodeName ) :
		str = """// FieldName
DEF_DEFAULT_FIELDNAME
const NewNode::FieldNameValueType NewNode::getFieldName() const
{
	return getFieldRO<FFieldNameType>(getFFieldName())->getValue();
}



void NewNode::setFieldName( const FieldNameValueType value )
{
	getFieldRW<FFieldNameType>(getFFieldName())->setValue( value );
}
\n\n\n"""

		if self.type.name == "enum" or self.type.isAnEnum:
			str = str.replace( 'DEF_DEFAULT_FIELDNAME', '' )
		else:
			str = str.replace( 'DEF_DEFAULT_FIELDNAME', defDefaultFieldname.format(defaultValue=self.type.generateDefaultValue()) )
		str = str.replace( "NewNode", nodeName )
		str = str.replace( "FieldName", self.getFieldName() )
		str = str.replace( "FIELDNAME", self.getFieldName().upper() )

		return str

	def generateDefaultSetter( self ) :
		defaultValue = self.type.generateDefaultValue()
		if len(defaultValue) == 0 :
			return defaultValue
		else :
			return "\tset%s( %s );" % (self.getFieldName(), defaultValue )

	def generateOptionalDefaultSetter( self ) :
		return None

	def generateCompleteType( self ) :
		return "SF%s" % self.type.getNormalizedName()



class OptionalField ( Field ) :

	def __init__( self, name, doc ) :
		Field.__init__( self, name, doc )

	def generateAccessorsHeader( self ) :
		str = """\n\n\n	/**
	 * @name Accessors to field fieldName
	 */
	//@{

TYPEDEF_FIELDNAMEVALUETYPE
DECL_DEFAULT_FIELDNAME
	/**
	 * @brief Type definition of the field named \c fieldName
	 */
	typedef vgd::field::TOptionalField< InternalFieldNameValueType > FFieldNameType;


	/**
	 * @brief Gets the value of field named \c fieldName.
	 */
	const bool getFieldName( FieldNameValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c fieldName.
 	 */
	void setFieldName( const FieldNameValueType& value );

	/**
	 * @brief Erases the field named \c fieldName.
	 */
	void eraseFieldName();

	/**
	 * @brief Tests if the value of field named \c fieldName has been initialized.
	 */
	const bool hasFieldName() const;
	//@}\n"""

		if self.type.name == "enum" or self.type.isAnEnum:
			str = str.replace( "InternalFieldNameValueType", "vgd::field::Enum" )
			str = str.replace( 'DECL_DEFAULT_FIELDNAME', '' )
		else:
			str = str.replace( "InternalFieldNameValueType", "FieldNameValueType" )
			str = str.replace( 'DECL_DEFAULT_FIELDNAME', declDefautFieldname )

		str = str.replace( "TYPEDEF_FIELDNAMEVALUETYPE", self.type.generateTYPEDEF() )	# @todo ValueType => Type
		str = str.replace( "fieldName", self.name )
		str = str.replace( "FieldName", self.getFieldName() )
		str = str.replace( "FIELDNAME", self.getFieldName().upper() )

		return str


	def generateAccessorsImpl( self, nodeName ) :
		str = """// FieldName
DEF_DEFAULT_FIELDNAME
const bool NewNode::getFieldName( FieldNameValueType& value ) const
{
	return getFieldRO<FFieldNameType>(getFFieldName())->getValue( value );
}



void NewNode::setFieldName( const FieldNameValueType& value )
{
	getFieldRW<FFieldNameType>(getFFieldName())->setValue( value );
}



void NewNode::eraseFieldName()
{
	getFieldRW<FFieldNameType>(getFFieldName())->eraseValue();
}


const bool NewNode::hasFieldName() const
{
	return getFieldRO<FFieldNameType>(getFFieldName())->hasValue();
}
\n\n\n"""

		if self.type.name == "enum" or self.type.isAnEnum:
			str = str.replace( 'DEF_DEFAULT_FIELDNAME', '' )
		else:
			str = str.replace( 'DEF_DEFAULT_FIELDNAME', '\nconst NewNode::FieldNameValueType NewNode::DEFAULT_FIELDNAME = {defaultValue};\n\n\n'.format(defaultValue=self.type.generateDefaultValue()) )

		str = str.replace( "NewNode", nodeName )
		str = str.replace( "FieldName", self.getFieldName() )
		str = str.replace( "FIELDNAME", self.getFieldName().upper() )

		return str


	def generateDefaultSetter( self ) :
		# @todo Adds eraseFieldName()
		return None

	def generateOptionalDefaultSetter( self ) :
		defaultValue = self.type.generateDefaultValue()
		if len(defaultValue) == 0 :
			return defaultValue
		else :
			return "\tset%s( %s );" % (self.getFieldName(), defaultValue )

	def generateCompleteType( self ) :
		return "OF%s" % self.type.getNormalizedName()

	def isOptional( self ):
		return True


class PairAssociativeField ( Field ):

	def __init__( self, name, doc ) :
		Field.__init__( self, name, doc )
		self.keyType = None

	def generateAccessorsHeader( self ) :
		str = """\n\n\n	/**
	 * @name Accessors to field fieldName
	 */
	//@{

	/**
	 * @brief Type definition of the parameter contained by field named \c fieldName.
	 */
TYPEDEF_FIELDNAMEPARAMETERTYPE

TYPEDEF_FIELDNAMEVALUETYPE

	/**
	 * @brief Type definition of the field named \c fieldName
	 */
	typedef vgd::field::TPairAssociativeField< FieldNameParameterType, FieldNameValueType > FFieldNameType;


	/**
	 * @brief Gets the value of field named \c fieldName.
	 */
	const bool getFieldName( const FieldNameParameterType param, FieldNameValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c fieldName.
 	 */
	void setFieldName( const FieldNameParameterType param, FieldNameValueType value );

	/**
	 * @brief Erases the field named \c fieldName.
	 */
	void eraseFieldName( const FieldNameParameterType param );
	//@}\n"""

		if self.keyType.name == "enum" and len(self.keyType.values) == 1 :
			str = str.replace( " const FieldNameParameterType param,", "" )
			str = str.replace( " const FieldNameParameterType param ", "" )

		str = str.replace( "TYPEDEF_FIELDNAMEPARAMETERTYPE", self.keyType.generateTYPEDEF().replace('ParameterValueType', 'ParameterType') )
		str = str.replace( "TYPEDEF_FIELDNAMEVALUETYPE", self.type.generateTYPEDEF() )
		str = str.replace( "fieldName", self.name )
		str = str.replace( "FieldName", self.getFieldName() )

		return str

	def generateAccessorsImpl( self, nodeName ) :
		str = """// FieldName
const bool NewNode::getFieldName( const FieldNameParameterType param, FieldNameValueType& value ) const
{
	return (
		vgd::field::getParameterValue< FieldNameParameterType, FieldNameValueType >( this, getFFieldName(), static_cast<FieldNameParameterType>(param), value )
		);
}



void NewNode::setFieldName( const FieldNameParameterType param, FieldNameValueType value )
{
	vgd::field::setParameterValue< FieldNameParameterType, FieldNameValueType >( this, getFFieldName(), static_cast<FieldNameParameterType>(param), value );
}



void NewNode::eraseFieldName( const FieldNameParameterType param )
{
	vgd::field::eraseParameterValue< FieldNameParameterType, FieldNameValueType >( this, getFFieldName(), static_cast<FieldNameParameterType>(param) );
}
\n\n\n"""

		if self.keyType.name == "enum" and len(self.keyType.values) == 1 :
			str = str.replace( " const FieldNameParameterType param,", "" )
			str = str.replace( " const FieldNameParameterType param ", "" )
			str = str.replace( "param", self.keyType.values.keys()[0] )

		str = str.replace( "NewNode", nodeName )
		str = str.replace( "FieldName", self.getFieldName() )

		return str

	def generateDefaultSetter( self ) :
		# @todo Adds eraseFieldName()
		return None

	def generateOptionalDefaultSetter( self ):
		retVal = ""
		defaultValue = self.type.generateDefaultValue()

		if isinstance( self.keyType, Enum ):
			selectors = self.keyType.values.keys()
			for selector in selectors:
				if len(defaultValue)>0:
					retVal += "\tset{0}( {1}, {2} );\n".format(self.getFieldName(), selector, defaultValue )
		else:
			if len(defaultValue) > 0:
				retVal += "\tset%s( %s );\n" % (self.getFieldName(), defaultValue )
		return retVal


	def generateCompleteType( self ) :
		return "PAF%s" % self.type.getNormalizedName()



class MultiField( Field ) :

	def __init__( self, name, doc ) :
		Field.__init__( self, name, doc )

	def generateAccessorsHeader( self ) :
		str = """\n\n\n	/**
	 * @name Accessors to field fieldName
	 *
	 * @todo getFieldName( const bool rw = false ) ?
	 */
	//@{

TYPEDEF_FIELDNAMEVALUETYPE

	/**
	 * @brief Type definition of the field named \c fieldName
	 */
	typedef vgd::field::TMultiField< InternalFieldNameValueType > FFieldNameType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c fieldName.
	 */
	vgd::field::EditorRO< FFieldNameType > getFieldNameRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c fieldName.
	 */
	vgd::field::EditorRW< FFieldNameType > getFieldNameRW();

	//@}\n"""

		if self.type.name == "enum" or self.type.isAnEnum:
			str = str.replace( "InternalFieldNameValueType", "vgd::field::Enum" )
		else:
			str = str.replace( "InternalFieldNameValueType", "FieldNameValueType" )

		str = str.replace( "TYPEDEF_FIELDNAMEVALUETYPE", self.type.generateTYPEDEF() )	# @todo ValueType => Type
		str = str.replace( "fieldName", self.name )
		str = str.replace( "FieldName", self.getFieldName() )

		return str


	def generateAccessorsImpl( self, nodeName ) :
		str = """// FieldName
vgd::field::EditorRO< NewNode::FFieldNameType > NewNode::getFieldNameRO() const
{
	return getFieldRO<FFieldNameType>( getFFieldName() );
}



vgd::field::EditorRW< NewNode::FFieldNameType > NewNode::getFieldNameRW()
{
	return getFieldRW<FFieldNameType>( getFFieldName() );
}
\n\n\n"""

		str = str.replace( "NewNode", nodeName )
		str = str.replace( "FieldName", self.getFieldName() )

		return str


	def generateDefaultSetter( self ) :
		return None

	def generateOptionalDefaultSetter( self ) :
		return None

	def generateCompleteType( self ) :
		return "MF%s" % self.type.getNormalizedName()

	def isOptional( self ):
		return False



class Node :

	def __init__( self, name ) :
		# Name of class
		self.name		= name
		#
		self.inherits	= []
		# True if class is abstract, False otherwise
		self.abstract	= False

		self.docBrief	= ""
		self.doc		= ""
		self.ingroup	= []

		self.dirtyFlags	= {}

		self.enums		= []
		self.fields		= OrderedDict()

		self.extraIncludeHpp	= ''
		self.extraIncludeCpp	= ''
		self.codeDeclaration	= ''
		self.codeImplementation	= ''

	def addDirtyFlag( self, newDF ) :
		if newDF.name not in self.dirtyFlags:
			self.dirtyFlags[newDF.name] = newDF
		else:
			print ("Unable to add dirty flag named {0}.".format(newDF.name))

	def addEnum( self, newEnum ) :
		self.enums.append( newEnum )

	def addField( self, newField ) :
		if newField.name not in self.fields :
			self.fields[newField.name] = newField
		else :
			print "Unable to add field named %s." % newField.name

	def addExtraIncludeHpp( self, code ):
		self.extraIncludeHpp += code + "\n"

	def addExtraIncludeCpp( self, code ):
		self.extraIncludeCpp += code + "\n"

	def addCodeDeclaration( self, code ):
		self.codeDeclaration += code

	def addCodeImplementation( self, code ):
		self.codeImplementation += code
