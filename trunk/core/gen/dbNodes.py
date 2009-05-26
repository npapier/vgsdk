#!/usr/bin/env python

# VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
# Distributed under the terms of the GNU Library General Public License (LGPL)
# as published by the Free Software Foundation.
# Author Nicolas Papier



############
# REGISTRY #
############
class EnumRegistry :
	_id		= 255
	_values	= {}

	@classmethod
	def nextID( self ) :
		self._id += 1
		return self._id


	@classmethod
	def register( self, enumValue ) :
		if enumValue not in self._values :
			self._values[enumValue] = self.nextID()
		else :
			raise StandardError("Enum value %s already defined." % enumValue)


	@classmethod
	def getID( self, enumValue ) :
		if enumValue in self._values :
			return self._values[enumValue]
		else :
			raise StandardError("Enum value %s not registered" % enumValue )


	@classmethod
	def getIterItems( self ):
		return self._values.iteritems()


	@classmethod
	def generate( self ) :
		print "Generates enum registry"
		for value, id in self._values.iteritems() :
			print "(%s,%i)" % (value, id)



########
# TYPE #
########
class Type :
	def __init__( self, name ) :
		self.namespace		= ""
		self.name			= name

		self.defaultValue	= ""

		# @todo range

	def generateTYPEDEF( self, fieldName, postfix ) :
		return "typedef %s %s%s;" % (self.generateTypeWithNamespace(), fieldName.capitalize(), postfix)

	def generateTypeWithNamespace( self ) :
		if len(self.namespace) > 0 :
			return self.namespace + "::" + self.name
		else :
			return self.name

	def generateDefaultValue( self ) :
		if len(self.defaultValue) == 0 :
			return ""
		else :
			if len(self.namespace) > 0 :
				return self.namespace + "::" + self.name + "(" + self.defaultValue + ")"
			else :
				return self.defaultValue

	def getNormalizedName( self ):
		return self.name[0].upper() + self.name[1:]


# @todo Constructs a derived class from vgd::field::Enum to add getAllValues()...
class Enum ( Type ) :
	def __init__( self ) :
		Type.__init__( self, "enum" )
		self.values = {}

	def addValue( self, value, docValue = "" ) :
		if value not in self.values :
			self.values[value] = docValue
			EnumRegistry.register(value)

	def setDefaultValue( self, defaultValue ) :
		if defaultValue in self.values :
			self.defaultValue = defaultValue
		else :
			raise StandardError("Try to set unknown value %s as the default value for an enum.")


	# Overridden
	def generateTYPEDEF( self, fieldName, postfix ) :
		str =	"typedef vgd::field::Enum %s%s;\n\n" % (fieldName.capitalize(), postfix)
		str +=	"""\t/**
\t * @brief Definition of symbolic values
\t */
\t%s;""" % self._generateDefinition( fieldName )
		return str

	#
	def _generateDefinition( self, fieldName ) :
		# begin definition
		str = "enum\n\t{\n"
		# values
		for i, (value, docValue) in enumerate(self.values.iteritems()) :
			valueID = EnumRegistry.getID(value)
			str += "\t\t%s = %i," % ( value, valueID )
			str += "\t///< %s\n" % docValue
		# default value
		str += "\t\tDEFAULT_%s = %s\t///< %s\n" % ( fieldName.upper(), self.defaultValue, self.values[self.defaultValue] )
		# end definition
		str += "\t}"

		return str



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


class SingleField ( Field ) :

	def __init__( self, name, doc ) :
		Field.__init__( self, name, doc )

	def generateAccessorsHeader( self ) :
		str = """\n\n\n	/**
	 * @name Accessors to field fieldName
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c fieldName.
	 */
	TYPEDEF_FIELDNAMEVALUETYPE

	/**
	 * @brief Type definition of the field named \c fieldName
	 */
	typedef vgd::field::SFFieldType FFieldNameType;


	/**
	 * @brief Gets the value of field named \c fieldName.
	 */
	const FieldNameValueType getFieldName() const;

	/**
	 * @brief Sets the value of field named \c fieldName.
	 */
	void setFieldName( const FieldNameValueType value );

	//@}\n"""

		str = str.replace( "TYPEDEF_FIELDNAMEVALUETYPE", self.type.generateTYPEDEF( self.name, "ValueType" ) )
		str = str.replace( "fieldName", self.name )
		str = str.replace( "FieldName", self.name.capitalize() )
		str = str.replace( "SFFieldType", "SF" + self.type.getNormalizedName() )

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
		str = str.replace( "FieldName", self.name.capitalize() )

		return str

	def generateDefaultSetter( self ) :
		defaultValue = self.type.generateDefaultValue()
		if len(defaultValue) == 0 :
			return defaultValue
		else :
			return "set%s( %s );" % (self.name.capitalize(), defaultValue )

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

	/**
	 * @brief Type definition of the value contained by field named \c fieldName.
	 */
	TYPEDEF_FIELDNAMEVALUETYPE

	/**
	 * @brief Type definition of the field named \c fieldName
	 */
	typedef vgd::field::TOptionalField< FieldNameValueType > FFieldNameType;


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

		str = str.replace( "TYPEDEF_FIELDNAMEVALUETYPE", self.type.generateTYPEDEF( self.name, "ValueType" ) )
		str = str.replace( "fieldName", self.name )
		str = str.replace( "FieldName", self.name.capitalize() )

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
		str = str.replace( "FieldName", self.name.capitalize() )

		return str


	def generateDefaultSetter( self ) :
		# @todo Adds eraseFieldName()
		return None

	def generateOptionalDefaultSetter( self ) :
		defaultValue = self.type.generateDefaultValue()
		if len(defaultValue) == 0 :
			return defaultValue
		else :
			return "set%s( %s );" % (self.name.capitalize(), defaultValue )

	def generateCompleteType( self ) :
		return "OF%s" % self.type.getNormalizedName()

	def isOptional( self ):
		return True


class PairAssociativeField ( Field ) :

	def __init__( self, name, doc ) :
		Field.__init__( self, name, doc )
		self.keyType = Enum()

	def generateAccessorsHeader( self ) :
		str = """\n\n\n	/**
	 * @name Accessors to field fieldName
	 */
	//@{

	/**
	 * @brief Type definition of the parameter contained by field named \c fieldName.
	 */
	TYPEDEF_FIELDNAMEPARAMETERTYPE

	/**
	 * @brief Type definition of the value contained by field named \c fieldName.
	 */
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

		str = str.replace( "TYPEDEF_FIELDNAMEPARAMETERTYPE", self.keyType.generateTYPEDEF( self.name, "ParameterType" ) )
		str = str.replace( "TYPEDEF_FIELDNAMEVALUETYPE", self.type.generateTYPEDEF( self.name, "ValueType" ) )
		str = str.replace( "fieldName", self.name )
		str = str.replace( "FieldName", self.name.capitalize() )

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
		str = str.replace( "FieldName", self.name.capitalize() )

		return str

	def generateDefaultSetter( self ) :
		# @todo Adds eraseFieldName()
		return None

	def generateOptionalDefaultSetter( self ) :
		defaultValue = self.type.generateDefaultValue()
		if len(defaultValue) == 0 :
			return defaultValue
		else :
			return "set%s( %s );" % (self.name.capitalize(), defaultValue )

	def generateCompleteType( self ) :
		return "PAF%s" % self.type.getNormalizedName()



class Node :
	def __init__( self, name ) :
		self.name		= name
		self.inherits	= []

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
