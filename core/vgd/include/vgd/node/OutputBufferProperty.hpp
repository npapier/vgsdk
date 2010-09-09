// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_OUTPUTBUFFERPROPERTY_HPP
#define _VGD_NODE_OUTPUTBUFFERPROPERTY_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/String.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Definition of the format, type and output command of an output buffer
 *
 * @todo 
 *
 * New fields defined by this node :
 * - SFEnum \c command = COLOR<br>
 *   Specifies the pre-defined assign command execute by the fragment program.<br>
 *<br>
 * - SFEnum \c type = INTEGER<br>
 *   Specifies the type used by the buffer.<br>
 *<br>
 * - SFString \c customCommand = empty<br>
 *   Specifies the pre-defined assign command execute by the fragment program. Example : output = color.rgba; or output = vec4( clamp(color.rgb, 0.0, 1.0), ecPosition.z );<br>
 *<br>
 * - SFEnum \c format = RGB<br>
 *   Specifies the format used by the buffer.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_autoMultiAttributeNodes
 * @ingroup g_frameBufferNodes
 * @ingroup g_postProcessing
 */
struct VGD_API OutputBufferProperty : public vgd::node::MultiAttribute
{
	/**
	 * @name Factories
	 */
	//@{

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values
	 */
	static vgd::Shp< OutputBufferProperty > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< OutputBufferProperty > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< OutputBufferProperty > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field command
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		LINEAR_DEPTH = 296,	///< @todo
		NORMAL = 293,	///< @todo
		COLOR = 292,	///< @todo
		CUSTOM = 297,	///< @todo
		DEPTH = 295,	///< @todo
		POSITION = 294,	///< @todo
		DEFAULT_COMMAND = COLOR	///< @todo
	};

	/**
	 * @brief Type definition of the value contained by field named \c command.
	 */
	struct CommandValueType : public vgd::field::Enum
	{
		CommandValueType()
		{}

		CommandValueType( const int v )
		: vgd::field::Enum(v)
		{}

		CommandValueType( const CommandValueType& o )
		: vgd::field::Enum(o)
		{}

		CommandValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 292 );
			retVal.push_back( 293 );
			retVal.push_back( 294 );
			retVal.push_back( 295 );
			retVal.push_back( 296 );
			retVal.push_back( 297 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "COLOR" );
			retVal.push_back( "NORMAL" );
			retVal.push_back( "POSITION" );
			retVal.push_back( "DEPTH" );
			retVal.push_back( "LINEAR_DEPTH" );
			retVal.push_back( "CUSTOM" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c command
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FCommandType;


	/**
	 * @brief Gets the value of field named \c command.
	 */
	const CommandValueType getCommand() const;

	/**
	 * @brief Sets the value of field named \c command.
	 */
	void setCommand( const CommandValueType value );

	//@}



	/**
	 * @name Accessors to field type
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		FLOAT16 = 290,	///< @todo
		INTEGER = 289,	///< @todo
		FLOAT32 = 291,	///< @todo
		DEFAULT_TYPE = INTEGER	///< @todo
	};

	/**
	 * @brief Type definition of the value contained by field named \c type.
	 */
	struct TypeValueType : public vgd::field::Enum
	{
		TypeValueType()
		{}

		TypeValueType( const int v )
		: vgd::field::Enum(v)
		{}

		TypeValueType( const TypeValueType& o )
		: vgd::field::Enum(o)
		{}

		TypeValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 289 );
			retVal.push_back( 290 );
			retVal.push_back( 291 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "INTEGER" );
			retVal.push_back( "FLOAT16" );
			retVal.push_back( "FLOAT32" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c type
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FTypeType;


	/**
	 * @brief Gets the value of field named \c type.
	 */
	const TypeValueType getType() const;

	/**
	 * @brief Sets the value of field named \c type.
	 */
	void setType( const TypeValueType value );

	//@}



	/**
	 * @name Accessors to field customCommand
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c customCommand.
	 */
	typedef std::string CustomCommandValueType;

	/**
	 * @brief Type definition of the field named \c customCommand
	 */
	typedef vgd::field::TSingleField< CustomCommandValueType > FCustomCommandType;


	/**
	 * @brief Gets the value of field named \c customCommand.
	 */
	const CustomCommandValueType getCustomCommand() const;

	/**
	 * @brief Sets the value of field named \c customCommand.
	 */
	void setCustomCommand( const CustomCommandValueType value );

	//@}



	/**
	 * @name Accessors to field format
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		LUMINANCE_ALPHA = 288,	///< @todo
		RGB = 285,	///< @todo
		LUMINANCE = 287,	///< @todo
		RGBA = 286,	///< @todo
		DEFAULT_FORMAT = RGB	///< @todo
	};

	/**
	 * @brief Type definition of the value contained by field named \c format.
	 */
	struct FormatValueType : public vgd::field::Enum
	{
		FormatValueType()
		{}

		FormatValueType( const int v )
		: vgd::field::Enum(v)
		{}

		FormatValueType( const FormatValueType& o )
		: vgd::field::Enum(o)
		{}

		FormatValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 285 );
			retVal.push_back( 286 );
			retVal.push_back( 287 );
			retVal.push_back( 288 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "RGB" );
			retVal.push_back( "RGBA" );
			retVal.push_back( "LUMINANCE" );
			retVal.push_back( "LUMINANCE_ALPHA" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c format
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FFormatType;


	/**
	 * @brief Gets the value of field named \c format.
	 */
	const FormatValueType getFormat() const;

	/**
	 * @brief Sets the value of field named \c format.
	 */
	void setFormat( const FormatValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c command.
	 *
	 * @return the name of field \c command.
	 */
	static const std::string getFCommand( void );

	/**
	 * @brief Returns the name of field \c type.
	 *
	 * @return the name of field \c type.
	 */
	static const std::string getFType( void );

	/**
	 * @brief Returns the name of field \c customCommand.
	 *
	 * @return the name of field \c customCommand.
	 */
	static const std::string getFCustomCommand( void );

	/**
	 * @brief Returns the name of field \c format.
	 *
	 * @return the name of field \c format.
	 */
	static const std::string getFFormat( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



	/**
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
	OutputBufferProperty( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , OutputBufferProperty );
private:
	static const vgd::basic::RegisterNode<OutputBufferProperty> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_OUTPUTBUFFERPROPERTY_HPP
