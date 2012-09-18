// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXTURE_HPP
#define _VGD_NODE_TEXTURE_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/IImageShp.hpp"
#include "vgd/field/String.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract texture mapping node
 *
 * This node defines texture parameters (wrapping, filter for minifying and magnification, mipmapping and function). Be carefull, data referenced by image must be available when texture is update. This node creates a a texture from the iimage interface. So image could be an image stored in memory (with vgd::basic::ImageInfo) or from a file (with vgd::basic::Image) or a cairo image (with vgCairo::ImageSurface) @remarks When The scene graph is evaluated by vgeGL, there are a size constraint one texture that you should keep in mind.\n When the image exceed the maximum allowable size for the texture, a temporary resized copy of the \c iimage(to the maximum of the texture size) is used for defining texture. This is not very fast. Be carefull.\n - Radeon 8500 could do 2048 x 2048 for 2D texturing, 512 x 512 x 512 for 3D texturing and 2048 for cube mapping.\n - GeForce 2 could do 2048 x 2048 for 2D texturing, 64 x 64 x 64 for 3D texturing and 512 for cube mapping.\n - GeForce 3 could do 4096 x 4096 for 2D texturing, 512 x 512 x 512 for 3D texturing and 4096 for cube mapping.\n - GeForce FX could do 4096 x 4096 for 2D texturing, 512 x 512 x 512 for 3D texturing and 4096 for cube mapping.\n - GeForce 8 could do  8192 x 8192 for 2D texturing, 2048 x 2048 x 2048 for 3D texturing and 8192 for cube mapping.\n @remarks If your OpenGL implementation does'nt support advanced texturing not limited to images with power-of-two dimensions, a temporary resized copy of the \c iimage is used for all wrapping modes except \c ONCE.\n @todo More docs\n 
 *
 * New fields defined by this node :
 * - OFFloat \c [maxAnisotropy] = (1.f)<br>
 *   Specifies the maximum degree of anisotropy. If not defined the value returned by Engine::getDefaultMaxAnisotropy() is used.<br>
 *<br>
 * - OFString \c [fragmentFunction] = std::string()<br>
 *   Fragment texturing function.<br>
 *<br>
 * - PAFEnum \c wrap = (REPEAT)<br>
 *   Sets the wrap parameter for texture coordinate S, T or R to either REPEAT, CLAMP, CLAMP_TO_EDGE, CLAMP_TO_BORDER, MIRRORED_REPEAT or ONCE. Initially, this field is set to REPEAT for S, T and R.<br>
 *<br>
 * - OFIImageShp \c [image] = vgd::basic::IImageShp()<br>
 *   Determines the source of data used to created the texture. You can set multiple times this field, but only if all successive images have the same format. The data and size of the image can changed, but that's all.<br>
 *<br>
 * - OFBool \c [mipmap] = (false)<br>
 *   Specifies if all levels of a mipmap array should be automatically updated when any modification to the image field (the base level of mipmap) is done.<br>
 *<br>
 * - PAFEnum \c filter = (LINEAR)<br>
 *   The texture minifying function (MIN_FILTER) is used whenever the pixel being textured maps to an area greater than one texture element. The texture magnification function (MAG_FILTER) is used when the pixel being textured maps to an area less than or equal to one texture element.<br>
 *<br>
 * - OFString \c [vertexFunction] = std::string()<br>
 *   Vertex texturing function.<br>
 *<br>
 * - SFEnum \c internalFormat = (AUTOMATIC)<br>
 *   Specifies the desired internal format used by the GPU.<br>
 *<br>
 * - SFEnum \c usage = (IMAGE)<br>
 *   Indicating the expected usage pattern of the texture.<br>
 *<br>
 *
 * @ingroup g_abstractNodes
 */
struct VGD_API Texture : public vgd::node::MultiAttribute
{



	/**
	 * @name Accessors to field maxAnisotropy
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c maxAnisotropy.
	 */
	typedef float MaxAnisotropyValueType;

	/**
	 * @brief The default value of field named \c maxAnisotropy.
	 */
	static const MaxAnisotropyValueType DEFAULT_MAXANISOTROPY;

	/**
	 * @brief Type definition of the field named \c maxAnisotropy
	 */
	typedef vgd::field::TOptionalField< MaxAnisotropyValueType > FMaxAnisotropyType;


	/**
	 * @brief Gets the value of field named \c maxAnisotropy.
	 */
	const bool getMaxAnisotropy( MaxAnisotropyValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c maxAnisotropy.
 	 */
	void setMaxAnisotropy( const MaxAnisotropyValueType& value );

	/**
	 * @brief Erases the field named \c maxAnisotropy.
	 */
	void eraseMaxAnisotropy();

	/**
	 * @brief Tests if the value of field named \c maxAnisotropy has been initialized.
	 */
	const bool hasMaxAnisotropy() const;
	//@}



	/**
	 * @name Accessors to field fragmentFunction
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c fragmentFunction.
	 */
	typedef std::string FragmentFunctionValueType;

	/**
	 * @brief The default value of field named \c fragmentFunction.
	 */
	static const FragmentFunctionValueType DEFAULT_FRAGMENTFUNCTION;

	/**
	 * @brief Type definition of the field named \c fragmentFunction
	 */
	typedef vgd::field::TOptionalField< FragmentFunctionValueType > FFragmentFunctionType;


	/**
	 * @brief Gets the value of field named \c fragmentFunction.
	 */
	const bool getFragmentFunction( FragmentFunctionValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c fragmentFunction.
 	 */
	void setFragmentFunction( const FragmentFunctionValueType& value );

	/**
	 * @brief Erases the field named \c fragmentFunction.
	 */
	void eraseFragmentFunction();

	/**
	 * @brief Tests if the value of field named \c fragmentFunction has been initialized.
	 */
	const bool hasFragmentFunction() const;
	//@}



	/**
	 * @name Accessors to field wrap
	 */
	//@{

	/**
	 * @brief Type definition of the parameter contained by field named \c wrap.
	 */
	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		WRAP_T = 427,	///< 
		WRAP_S = 426,	///< 
		WRAP_R = 428,	///< 
		DEFAULT_WRAPPARAMETER = WRAP_S	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct WrapParameterType : public vgd::field::Enum
	{
		WrapParameterType()
		{}

		WrapParameterType( const int v )
		: vgd::field::Enum(v)
		{}

		WrapParameterType( const WrapParameterType& o )
		: vgd::field::Enum(o)
		{}

		WrapParameterType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 426 );
			retVal.push_back( 427 );
			retVal.push_back( 428 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "WRAP_S" );
			retVal.push_back( "WRAP_T" );
			retVal.push_back( "WRAP_R" );

			return retVal;
		}
	};

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		CLAMP = 430,	///< 
		REPEAT = 429,	///< 
		MIRRORED_REPEAT = 433,	///< 
		CLAMP_TO_EDGE = 431,	///< 
		CLAMP_TO_BORDER = 432,	///< 
		ONCE = 434,	///< Don't set texture coordinates outside the interval [0.f, 1.f]
		DEFAULT_WRAP = REPEAT	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct WrapValueType : public vgd::field::Enum
	{
		WrapValueType()
		{}

		WrapValueType( const int v )
		: vgd::field::Enum(v)
		{}

		WrapValueType( const WrapValueType& o )
		: vgd::field::Enum(o)
		{}

		WrapValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 429 );
			retVal.push_back( 430 );
			retVal.push_back( 431 );
			retVal.push_back( 432 );
			retVal.push_back( 433 );
			retVal.push_back( 434 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "REPEAT" );
			retVal.push_back( "CLAMP" );
			retVal.push_back( "CLAMP_TO_EDGE" );
			retVal.push_back( "CLAMP_TO_BORDER" );
			retVal.push_back( "MIRRORED_REPEAT" );
			retVal.push_back( "ONCE" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c wrap
	 */
	typedef vgd::field::TPairAssociativeField< WrapParameterType, WrapValueType > FWrapType;


	/**
	 * @brief Gets the value of field named \c wrap.
	 */
	const bool getWrap( const WrapParameterType param, WrapValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c wrap.
 	 */
	void setWrap( const WrapParameterType param, WrapValueType value );

	/**
	 * @brief Erases the field named \c wrap.
	 */
	void eraseWrap( const WrapParameterType param );
	//@}



	/**
	 * @name Accessors to field image
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c image.
	 */
	typedef vgd::basic::IImageShp ImageValueType;

	/**
	 * @brief The default value of field named \c image.
	 */
	static const ImageValueType DEFAULT_IMAGE;

	/**
	 * @brief Type definition of the field named \c image
	 */
	typedef vgd::field::TOptionalField< ImageValueType > FImageType;


	/**
	 * @brief Gets the value of field named \c image.
	 */
	const bool getImage( ImageValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c image.
 	 */
	void setImage( const ImageValueType& value );

	/**
	 * @brief Erases the field named \c image.
	 */
	void eraseImage();

	/**
	 * @brief Tests if the value of field named \c image has been initialized.
	 */
	const bool hasImage() const;
	//@}



	/**
	 * @name Accessors to field mipmap
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c mipmap.
	 */
	typedef bool MipmapValueType;

	/**
	 * @brief The default value of field named \c mipmap.
	 */
	static const MipmapValueType DEFAULT_MIPMAP;

	/**
	 * @brief Type definition of the field named \c mipmap
	 */
	typedef vgd::field::TOptionalField< MipmapValueType > FMipmapType;


	/**
	 * @brief Gets the value of field named \c mipmap.
	 */
	const bool getMipmap( MipmapValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c mipmap.
 	 */
	void setMipmap( const MipmapValueType& value );

	/**
	 * @brief Erases the field named \c mipmap.
	 */
	void eraseMipmap();

	/**
	 * @brief Tests if the value of field named \c mipmap has been initialized.
	 */
	const bool hasMipmap() const;
	//@}



	/**
	 * @name Accessors to field filter
	 */
	//@{

	/**
	 * @brief Type definition of the parameter contained by field named \c filter.
	 */
	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		MIN_FILTER = 435,	///< Choose one value among NEAREST, LINEAR (default), NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR.
		MAG_FILTER = 436,	///< Choose one value among NEAREST or LINEAR (default).
		DEFAULT_FILTERPARAMETER = MAG_FILTER	///< Choose one value among NEAREST or LINEAR (default).
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct FilterParameterType : public vgd::field::Enum
	{
		FilterParameterType()
		{}

		FilterParameterType( const int v )
		: vgd::field::Enum(v)
		{}

		FilterParameterType( const FilterParameterType& o )
		: vgd::field::Enum(o)
		{}

		FilterParameterType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 435 );
			retVal.push_back( 436 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "MIN_FILTER" );
			retVal.push_back( "MAG_FILTER" );

			return retVal;
		}
	};

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		NEAREST = 437,	///< 
		LINEAR = 438,	///< 
		LINEAR_MIPMAP_NEAREST = 440,	///< 
		NEAREST_MIPMAP_NEAREST = 439,	///< 
		LINEAR_MIPMAP_LINEAR = 442,	///< 
		NEAREST_MIPMAP_LINEAR = 441,	///< 
		DEFAULT_FILTER = LINEAR	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct FilterValueType : public vgd::field::Enum
	{
		FilterValueType()
		{}

		FilterValueType( const int v )
		: vgd::field::Enum(v)
		{}

		FilterValueType( const FilterValueType& o )
		: vgd::field::Enum(o)
		{}

		FilterValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 437 );
			retVal.push_back( 438 );
			retVal.push_back( 439 );
			retVal.push_back( 440 );
			retVal.push_back( 441 );
			retVal.push_back( 442 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "NEAREST" );
			retVal.push_back( "LINEAR" );
			retVal.push_back( "NEAREST_MIPMAP_NEAREST" );
			retVal.push_back( "LINEAR_MIPMAP_NEAREST" );
			retVal.push_back( "NEAREST_MIPMAP_LINEAR" );
			retVal.push_back( "LINEAR_MIPMAP_LINEAR" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c filter
	 */
	typedef vgd::field::TPairAssociativeField< FilterParameterType, FilterValueType > FFilterType;


	/**
	 * @brief Gets the value of field named \c filter.
	 */
	const bool getFilter( const FilterParameterType param, FilterValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c filter.
 	 */
	void setFilter( const FilterParameterType param, FilterValueType value );

	/**
	 * @brief Erases the field named \c filter.
	 */
	void eraseFilter( const FilterParameterType param );
	//@}



	/**
	 * @name Accessors to field vertexFunction
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c vertexFunction.
	 */
	typedef std::string VertexFunctionValueType;

	/**
	 * @brief The default value of field named \c vertexFunction.
	 */
	static const VertexFunctionValueType DEFAULT_VERTEXFUNCTION;

	/**
	 * @brief Type definition of the field named \c vertexFunction
	 */
	typedef vgd::field::TOptionalField< VertexFunctionValueType > FVertexFunctionType;


	/**
	 * @brief Gets the value of field named \c vertexFunction.
	 */
	const bool getVertexFunction( VertexFunctionValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c vertexFunction.
 	 */
	void setVertexFunction( const VertexFunctionValueType& value );

	/**
	 * @brief Erases the field named \c vertexFunction.
	 */
	void eraseVertexFunction();

	/**
	 * @brief Tests if the value of field named \c vertexFunction has been initialized.
	 */
	const bool hasVertexFunction() const;
	//@}



	/**
	 * @name Accessors to field internalFormat
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		DEPTH_COMPONENT_16 = 414,	///< a single component buffer used to store depth. A 16-bit integer is used to encode a texel.
		RGB_32F = 419,	///< A three component buffer. A 32-bit float is used to encode a texel.
		LUMINANCE_ALPHA_32F = 425,	///< A two component buffer. A 32-bit float is used to encode a texel.
		LUMINANCE_16F = 422,	///< A single component buffer. A 16-bit float is used to encode a texel.
		LUMINANCE_32F = 423,	///< A single component buffer. A 32-bit float is used to encode a texel.
		RGBA_32F = 421,	///< A four component buffer. A 32-bit float is used to encode a texel.
		DEPTH_COMPONENT_32F = 417,	///< a single component buffer used to store depth. A 32-bit float is used to encode a texel.
		RGBA_16F = 420,	///< A four component buffer. A 16-bit float is used to encode a texel.
		LUMINANCE_ALPHA_16F = 424,	///< A two component buffer. A 16-bit float is used to encode a texel.
		DEPTH_COMPONENT_24 = 415,	///< a single component buffer used to store depth. A 24-bit integer is used to encode a texel.
		AUTOMATIC = 413,	///< Choosed automatically an internal format matching the image format used by the texture.
		RGB_16F = 418,	///< A three component buffer. A 16-bit float is used to encode a texel.
		DEPTH_COMPONENT_32 = 416,	///< a single component buffer used to store depth. A 32-bit integer is used to encode a texel.
		DEFAULT_INTERNALFORMAT = AUTOMATIC	///< Choosed automatically an internal format matching the image format used by the texture.
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct InternalFormatValueType : public vgd::field::Enum
	{
		InternalFormatValueType()
		{}

		InternalFormatValueType( const int v )
		: vgd::field::Enum(v)
		{}

		InternalFormatValueType( const InternalFormatValueType& o )
		: vgd::field::Enum(o)
		{}

		InternalFormatValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 413 );
			retVal.push_back( 414 );
			retVal.push_back( 415 );
			retVal.push_back( 416 );
			retVal.push_back( 417 );
			retVal.push_back( 418 );
			retVal.push_back( 419 );
			retVal.push_back( 420 );
			retVal.push_back( 421 );
			retVal.push_back( 422 );
			retVal.push_back( 423 );
			retVal.push_back( 424 );
			retVal.push_back( 425 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "AUTOMATIC" );
			retVal.push_back( "DEPTH_COMPONENT_16" );
			retVal.push_back( "DEPTH_COMPONENT_24" );
			retVal.push_back( "DEPTH_COMPONENT_32" );
			retVal.push_back( "DEPTH_COMPONENT_32F" );
			retVal.push_back( "RGB_16F" );
			retVal.push_back( "RGB_32F" );
			retVal.push_back( "RGBA_16F" );
			retVal.push_back( "RGBA_32F" );
			retVal.push_back( "LUMINANCE_16F" );
			retVal.push_back( "LUMINANCE_32F" );
			retVal.push_back( "LUMINANCE_ALPHA_16F" );
			retVal.push_back( "LUMINANCE_ALPHA_32F" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c internalFormat
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FInternalFormatType;


	/**
	 * @brief Gets the value of field named \c internalFormat.
	 */
	const InternalFormatValueType getInternalFormat() const;

	/**
	 * @brief Sets the value of field named \c internalFormat.
	 */
	void setInternalFormat( const InternalFormatValueType value );

	//@}



	/**
	 * @name Accessors to field usage
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		IMAGE = 411,	///< Simple image mapping
		SHADOW = 412,	///< Shadow mapping
		DEFAULT_USAGE = IMAGE	///< Simple image mapping
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct UsageValueType : public vgd::field::Enum
	{
		UsageValueType()
		{}

		UsageValueType( const int v )
		: vgd::field::Enum(v)
		{}

		UsageValueType( const UsageValueType& o )
		: vgd::field::Enum(o)
		{}

		UsageValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 411 );
			retVal.push_back( 412 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "IMAGE" );
			retVal.push_back( "SHADOW" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c usage
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FUsageType;


	/**
	 * @brief Gets the value of field named \c usage.
	 */
	const UsageValueType getUsage() const;

	/**
	 * @brief Sets the value of field named \c usage.
	 */
	void setUsage( const UsageValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c maxAnisotropy.
	 *
	 * @return the name of field \c maxAnisotropy.
	 */
	static const std::string getFMaxAnisotropy( void );

	/**
	 * @brief Returns the name of field \c fragmentFunction.
	 *
	 * @return the name of field \c fragmentFunction.
	 */
	static const std::string getFFragmentFunction( void );

	/**
	 * @brief Returns the name of field \c wrap.
	 *
	 * @return the name of field \c wrap.
	 */
	static const std::string getFWrap( void );

	/**
	 * @brief Returns the name of field \c image.
	 *
	 * @return the name of field \c image.
	 */
	static const std::string getFImage( void );

	/**
	 * @brief Returns the name of field \c mipmap.
	 *
	 * @return the name of field \c mipmap.
	 */
	static const std::string getFMipmap( void );

	/**
	 * @brief Returns the name of field \c filter.
	 *
	 * @return the name of field \c filter.
	 */
	static const std::string getFFilter( void );

	/**
	 * @brief Returns the name of field \c vertexFunction.
	 *
	 * @return the name of field \c vertexFunction.
	 */
	static const std::string getFVertexFunction( void );

	/**
	 * @brief Returns the name of field \c internalFormat.
	 *
	 * @return the name of field \c internalFormat.
	 */
	static const std::string getFInternalFormat( void );

	/**
	 * @brief Returns the name of field \c usage.
	 *
	 * @return the name of field \c usage.
	 */
	static const std::string getFUsage( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when \c image field is modified.
	 */
	static const std::string getDFImage();
	/**
	 * @brief Returns name of dirty flag that is invalidate when \c parameters field is modified.
	 */
	static const std::string getDFParameters();

	//@}
	/**
	 * @name Accessors to field functionFragment
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c functionFragment.
	 */
	typedef FragmentFunctionValueType FunctionValueType;

	/**
	 * @brief Type definition of the field named \c functionFragment
	 */
	typedef FFragmentFunctionType FFunctionType;

	/**
	 * @brief Gets the value of field named \c functionFragment.
	 */
	const bool getFunction( FunctionValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c functionFragment.
 	 */
	void setFunction( const FunctionValueType& value );

	/**
	 * @brief Erases the field named \c functionFragment.
	 */
	void eraseFunction();

	/**
	 * @brief Tests if the value of field named \c functionFragment has been initialized.
	 */
	const bool hasFunction() const;
	//@}



	/**
	 * @name High-level accessors
	 */
	//@{

	/**
	 * @brief Returns the dimension of this texture node.
	 * 
	 * @return dimension of this texture node
	 */
	virtual const uint32 gethTextureDimension() const=0;

	//@}



	/**
	 * @name Accessors to field function
	 *
	 * This accessors emulates the old interface of the field function.
	 */
	//@{

	/**
	 * brief Enumeration of the \c function parameters.
	 */
	/*typedef enum {
		FUNCTION
	} OldFunctionParameterType;*/

	/**
	 * @brief Typedef for the \c function value.
	 */
	typedef enum
	{
		FUN_REPLACE = 0,
		FUN_MODULATE, 
//		FUN_DECAL, 
//		FUN_BLEND, 

//		FUN_ADD,
//		FUN_COMBINE,

		DEFAULT_FUN = FUN_MODULATE
	} OldFunctionValueType;

	/**
	 * brief Typedef for the \c function field.
	 */	
	//typedef vgd::field::TPairAssociativeField< OldFunctionParameterType, OldFunctionValueType > FFunctionType;

	/**
	 * brief Gets the function value.
	 */
	//vgDEPRECATED( bool			gethFunction( OldFunctionValueType& value ) const );

	/**
	 * @brief Sets the function value.
	 */
	void 			sethFunction( OldFunctionValueType value );
	
	/**
	 * brief Erase the function value.
	 */
	//void 			eraseFunction();
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
	Texture( const std::string nodeName );

};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXTURE_HPP
