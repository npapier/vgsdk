// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_OUTPUTBUFFERPROPERTY_HPP
#define _VGD_NODE_OUTPUTBUFFERPROPERTY_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Enum.hpp"
#include "vgd/field/String.hpp"
#include "vgd/field/Texture2DShp.hpp"
#include "vgd/field/Vec2f.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Definition of the size, format, type, texture node, initial state and output command of an output buffer
 *
 * 
 *
 * New fields defined by this node :
 * - SFEnum \c sizeSemantic = (SCALE_FACTOR)<br>
 *   Specifies the semantic of the size field.<br>
 *<br>
 * - SFVec2f \c size = vgm::Vec2f(1.f, 1.f)<br>
 *   Specifies the size of the output buffer (in pixel or scale factors). See sizeSemantic field for more informations.<br>
 *<br>
 * - SFEnum \c format = (RGB)<br>
 *   Specifies the format used by the buffer.<br>
 *<br>
 * - SFEnum \c type = (INTEGER)<br>
 *   Specifies the type used by the buffer.<br>
 *<br>
 * - SFBool \c current = (true)<br>
 *   Specifies if this output buffer must be used for drawing by default. See vgd::node::OutputBuffer to alter this initial state.<br>
 *<br>
 * - SFEnum \c command = (COLOR)<br>
 *   Specifies the pre-defined assign command execute by the fragment program.<br>
 *<br>
 * - SFString \c customDeclaration = std::string()<br>
 *   Specifies the declaration to copy at the beginning of the fragment program when command field is CUSTOM.<br>
 *<br>
 * - SFString \c customCommand = std::string()<br>
 *   Specifies the assign command execute by the fragment program. Example : color.rgba; or vec4( clamp(color.rgb, 0.0, 1.0), ecPosition.z ); or computeMyCustomValue( ecPosition );<br>
 *<br>
 * - OFTexture2DShp \c [textureNode] = vgd::node::Texture2DShp()<br>
 *   Specify a texture node to store the output buffer defined by this node. Use case: render to texture.<br>
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
	 * @name Accessors to field sizeSemantic
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		SCALE_FACTOR = 339,	///< The width of the output buffer is computed using the width of the drawing surface area scaled by the first component of size field (same for height and second component)
		PIXEL_SIZE = 340,	///< The size field specifies the size of the output buffer in pixels.
		DEFAULT_SIZESEMANTIC = SCALE_FACTOR	///< The width of the output buffer is computed using the width of the drawing surface area scaled by the first component of size field (same for height and second component)
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct SizeSemanticValueType : public vgd::field::Enum
	{
		SizeSemanticValueType()
		{}

		SizeSemanticValueType( const int v )
		: vgd::field::Enum(v)
		{}

		SizeSemanticValueType( const SizeSemanticValueType& o )
		: vgd::field::Enum(o)
		{}

		SizeSemanticValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 339 );
			retVal.push_back( 340 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "SCALE_FACTOR" );
			retVal.push_back( "PIXEL_SIZE" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c sizeSemantic
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FSizeSemanticType;


	/**
	 * @brief Gets the value of field named \c sizeSemantic.
	 */
	const SizeSemanticValueType getSizeSemantic() const;

	/**
	 * @brief Sets the value of field named \c sizeSemantic.
	 */
	void setSizeSemantic( const SizeSemanticValueType value );

	//@}



	/**
	 * @name Accessors to field size
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c size.
	 */
	typedef vgm::Vec2f SizeValueType;

	/**
	 * @brief The default value of field named \c size.
	 */
	static const SizeValueType DEFAULT_SIZE;

	/**
	 * @brief Type definition of the field named \c size
	 */
	typedef vgd::field::TSingleField< SizeValueType > FSizeType;


	/**
	 * @brief Gets the value of field named \c size.
	 */
	const SizeValueType getSize() const;

	/**
	 * @brief Sets the value of field named \c size.
	 */
	void setSize( const SizeValueType value );

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
		LUMINANCE_ALPHA = 344,	///< todo
		RGB = 341,	///< todo
		LUMINANCE = 343,	///< todo
		RGBA = 342,	///< todo
		LUMINANCE_FOR_DEPTH = 345,	///< if type is INTEGER, then DEPTH_COMPONENT_24 is used.
		DEFAULT_FORMAT = RGB	///< todo
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
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

			retVal.push_back( 341 );
			retVal.push_back( 342 );
			retVal.push_back( 343 );
			retVal.push_back( 344 );
			retVal.push_back( 345 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "RGB" );
			retVal.push_back( "RGBA" );
			retVal.push_back( "LUMINANCE" );
			retVal.push_back( "LUMINANCE_ALPHA" );
			retVal.push_back( "LUMINANCE_FOR_DEPTH" );

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
	 * @name Accessors to field type
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		FLOAT16 = 347,	///< todo
		INTEGER = 346,	///< todo
		FLOAT32 = 348,	///< todo
		DEFAULT_TYPE = INTEGER	///< todo
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
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

			retVal.push_back( 346 );
			retVal.push_back( 347 );
			retVal.push_back( 348 );

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
	 * @name Accessors to field current
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c current.
	 */
	typedef bool CurrentValueType;

	/**
	 * @brief The default value of field named \c current.
	 */
	static const CurrentValueType DEFAULT_CURRENT;

	/**
	 * @brief Type definition of the field named \c current
	 */
	typedef vgd::field::TSingleField< CurrentValueType > FCurrentType;


	/**
	 * @brief Gets the value of field named \c current.
	 */
	const CurrentValueType getCurrent() const;

	/**
	 * @brief Sets the value of field named \c current.
	 */
	void setCurrent( const CurrentValueType value );

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
		LINEAR_DEPTH = 353,	///< todo
		NORMAL = 350,	///< todo
		COLOR = 349,	///< todo
		CUSTOM = 354,	///< todo
		DEPTH = 352,	///< todo
		POSITION = 351,	///< todo
		DEFAULT_COMMAND = COLOR	///< todo
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
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

			retVal.push_back( 349 );
			retVal.push_back( 350 );
			retVal.push_back( 351 );
			retVal.push_back( 352 );
			retVal.push_back( 353 );
			retVal.push_back( 354 );

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
	 * @name Accessors to field customDeclaration
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c customDeclaration.
	 */
	typedef std::string CustomDeclarationValueType;

	/**
	 * @brief The default value of field named \c customDeclaration.
	 */
	static const CustomDeclarationValueType DEFAULT_CUSTOMDECLARATION;

	/**
	 * @brief Type definition of the field named \c customDeclaration
	 */
	typedef vgd::field::TSingleField< CustomDeclarationValueType > FCustomDeclarationType;


	/**
	 * @brief Gets the value of field named \c customDeclaration.
	 */
	const CustomDeclarationValueType getCustomDeclaration() const;

	/**
	 * @brief Sets the value of field named \c customDeclaration.
	 */
	void setCustomDeclaration( const CustomDeclarationValueType value );

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
	 * @brief The default value of field named \c customCommand.
	 */
	static const CustomCommandValueType DEFAULT_CUSTOMCOMMAND;

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
	 * @name Accessors to field textureNode
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c textureNode.
	 */
	typedef vgd::node::Texture2DShp TextureNodeValueType;

	/**
	 * @brief The default value of field named \c textureNode.
	 */
	static const TextureNodeValueType DEFAULT_TEXTURENODE;

	/**
	 * @brief Type definition of the field named \c textureNode
	 */
	typedef vgd::field::TOptionalField< TextureNodeValueType > FTextureNodeType;


	/**
	 * @brief Gets the value of field named \c textureNode.
	 */
	const bool getTextureNode( TextureNodeValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c textureNode.
 	 */
	void setTextureNode( const TextureNodeValueType& value );

	/**
	 * @brief Erases the field named \c textureNode.
	 */
	void eraseTextureNode();

	/**
	 * @brief Tests if the value of field named \c textureNode has been initialized.
	 */
	const bool hasTextureNode() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c sizeSemantic.
	 *
	 * @return the name of field \c sizeSemantic.
	 */
	static const std::string getFSizeSemantic( void );

	/**
	 * @brief Returns the name of field \c size.
	 *
	 * @return the name of field \c size.
	 */
	static const std::string getFSize( void );

	/**
	 * @brief Returns the name of field \c format.
	 *
	 * @return the name of field \c format.
	 */
	static const std::string getFFormat( void );

	/**
	 * @brief Returns the name of field \c type.
	 *
	 * @return the name of field \c type.
	 */
	static const std::string getFType( void );

	/**
	 * @brief Returns the name of field \c current.
	 *
	 * @return the name of field \c current.
	 */
	static const std::string getFCurrent( void );

	/**
	 * @brief Returns the name of field \c command.
	 *
	 * @return the name of field \c command.
	 */
	static const std::string getFCommand( void );

	/**
	 * @brief Returns the name of field \c customDeclaration.
	 *
	 * @return the name of field \c customDeclaration.
	 */
	static const std::string getFCustomDeclaration( void );

	/**
	 * @brief Returns the name of field \c customCommand.
	 *
	 * @return the name of field \c customCommand.
	 */
	static const std::string getFCustomCommand( void );

	/**
	 * @brief Returns the name of field \c textureNode.
	 *
	 * @return the name of field \c textureNode.
	 */
	static const std::string getFTextureNode( void );

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
	IMPLEMENT_INDEXABLE_CLASS_HPP( OutputBufferProperty );
	//IMPLEMENT_INDEXABLE_CLASS_HPP( , OutputBufferProperty );
private:
	static const vgd::basic::RegisterNode<OutputBufferProperty> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_OUTPUTBUFFERPROPERTY_HPP
