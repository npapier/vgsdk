#!/usr/bin/env python

# VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier.
# Distributed under the terms of the GNU Library General Public License (LGPL)
# as published by the Free Software Foundation.
# Author Nicolas Papier



############
# REGISTRY #
############
class EnumRegistry :
	_id		= 255

	_values	= {}	# enum_string, enum_id
	_rvalues = {}	# enum_id, enum_string

	@classmethod
	def nextID( self ):
		self._id += 1
		return self._id


	@classmethod
	def register( self, nodeName, fieldName, enumValue ):
		newValue = nodeName + '.' + fieldName + '.' + enumValue
		if newValue not in self._values:
			newID = self.nextID()
			self._values[newValue] = newID
			self._rvalues[newID] = newValue
		else:
			raise StandardError("Enum value %s already defined." % newValue)


	@classmethod
	def getID( self, nodeName, fieldName, enumValue ):
		newValue = nodeName + '.' + fieldName + '.' + enumValue
		if newValue in self._values :
			return self._values[newValue]
		else :
			raise StandardError("Enum value %s not registered" % newValue )


	@classmethod
	def getString( self, id ):
		if id in self._rvalues:
			return self._rvalues[id].split('.')[2]
		else:
			raise StandardError("Enum value %i not registered" % id )


	@classmethod
	def getIterItems( self ):
		return self._values.iteritems()


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
			self.FieldName = fieldName[0].upper() + fieldName[1:]
		else:
			self.FieldName = ""

		# @todo range

	def generateTYPEDEF( self ):
		str = """\t/**
\t * @brief Type definition of the value contained by field named \c %s.
\t */
\ttypedef %s %sValueType;""" % (self.fieldName, self.generateTypeWithNamespace(), self.FieldName ) # @todo ValueType => Type
		return str

	def generateTypeWithNamespace( self ):
		if len(self.namespace) > 0 :
			return self.namespace + "::" + self.name
		else :
			return self.name

	def generateDefaultValue( self ):
		if len(self.defaultValue) == 0 :
			return ""
		else :
			if len(self.namespace) > 0 :
				return self.namespace + "::" + self.name + "(" + self.defaultValue + ")"
			else :
				return self.defaultValue

	def getNormalizedName( self ):
		return self.name[0].upper() + self.name[1:]


class Enum ( Type ):

	def __init__( self, nodeName, fieldName ):
		Type.__init__( self, "enum", nodeName, fieldName )
		self.values = {}	# enum_string, enum_doc

	def addValue( self, value, docValue = "" ):
		if value not in self.values :
			self.values[value] = docValue
			EnumRegistry.register( self.nodeName, self.fieldName, value )

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
	 * @brief Type definition of the value contained by field named \c %s.
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
	};""" % (self.fieldName, strValues, strStrings)

		str += definitionOfFieldNameType.replace( "FieldNameType", self.FieldName + "ValueType" )		# @todo ValueType => Type

		return str

	#
	def _generateDefinition( self ):
		# begin definition
		str = "enum\n\t{\n"
		# values
		for (value, docValue) in self.values.iteritems() :
			valueID = EnumRegistry.getID(self.nodeName, self.fieldName, value)
			str += "\t\t%s = %i," % ( value, valueID )
			str += "\t///< %s\n" % docValue
		# default value
		str += "\t\tDEFAULT_%s = %s\t///< %s\n" % ( self.fieldName.upper(), self.defaultValue, self.values[self.defaultValue] )
		# end definition
		str += "\t}"

		return str


	def _getIds( self ):
		keys = self.values.keys()
		ids = [ EnumRegistry.getID(self.nodeName, self.fieldName, key) for key in keys ]
		return sorted(ids)

	def _getStrings( self ):
		sortedIds = self._getIds()
		return [ EnumRegistry.getString(id) for id in sortedIds ]



#########
# FIELD #
#########
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
		return self.name[0].upper() + self.name[1:]


class SingleField ( Field ) :

	def __init__( self, name, doc ) :
		Field.__init__( self, name, doc )

	def generateAccessorsHeader( self ) :
		str = """\n\n\n	/**
	 * @name Accessors to field fieldName
	 */
	//@{

TYPEDEF_FIELDNAMEVALUETYPE

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

		if self.type.name == "enum":
			str = str.replace( "InternalFieldNameValueType", "vgd::field::Enum" )
		else:
			str = str.replace( "InternalFieldNameValueType", "FieldNameValueType" )

		str = str.replace( "TYPEDEF_FIELDNAMEVALUETYPE", self.type.generateTYPEDEF() )		# @todo ValueType => Type
		str = str.replace( "fieldName", self.name )
		str = str.replace( "FieldName", self.getFieldName() )
		str = str.replace( "FieldType", self.type.name )

		return str

	def generateAccessorsImpl( self, nodeName ) :
		str = """// FieldName
const NewNode::FieldNameValueType NewNode::getFieldName() const
{
	return getFieldRO<FFieldNameType>(getFFieldName())->getValue();
}



void NewNode::setFieldName( const FieldNameValueType value )
{
	getFieldRW<FFieldNameType>(getFFieldName())->setValue( value );
}
\n\n\n"""

		str = str.replace( "NewNode", nodeName )
		str = str.replace( "FieldName", self.getFieldName() )

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

		if self.type.name == "enum":
			str = str.replace( "InternalFieldNameValueType", "vgd::field::Enum" )
		else:
			str = str.replace( "InternalFieldNameValueType", "FieldNameValueType" )

		str = str.replace( "TYPEDEF_FIELDNAMEVALUETYPE", self.type.generateTYPEDEF() )	# @todo ValueType => Type
		str = str.replace( "fieldName", self.name )
		str = str.replace( "FieldName", self.getFieldName() )

		return str


	def generateAccessorsImpl( self, nodeName ) :
		str = """// FieldName
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

		str = str.replace( "NewNode", nodeName )
		str = str.replace( "FieldName", self.getFieldName() )

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

		if self.type.name == "enum":
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

		self.fields		= {}

		self.codeDeclaration	= ''
		self.codeImplementation	= ''

	def addField( self, newField ) :
		if newField.name not in self.fields :
			self.fields[newField.name] = newField
		else :
			print "Unable to add field named %s." % newField.name

	def addCodeDeclaration( self, code ):
		self.codeDeclaration += code

	def addCodeImplementation( self, code ):
		self.codeImplementation += code
