// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXTURE_HPP
#define _VGD_NODE_TEXTURE_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Enum.hpp"
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
 * - OFString \c [function] = empty<br>
 *   Example similar to old FUN_MODULATE: color *= texture2D(texUnitX, gl_TexCoord[X].xy);<br>
 *<br>
 * - OFIImageShp \c [image] = empty<br>
 *   Determines the source of data used to created the texture. You can set multiple times this field, but only if all successive images have the same format. The data and size of the image can changed, but that's all.<br>
 *<br>
 * - OFBool \c [mipmap] = false<br>
 *   Specifies if all levels of a mipmap array should be automatically updated when any modification to the image field (the base level of mipmap) is done.<br>
 *<br>
 * - PAFEnum \c filter = LINEAR<br>
 *   The texture minifying function (MIN_FILTER) is used whenever the pixel being textured maps to an area greater than one texture element. The texture magnification function (MAG_FILTER) is used when the pixel being textured maps to an area less than or equal to one texture element.<br>
 *<br>
 * - PAFEnum \c wrap = REPEAT<br>
 *   Sets the wrap parameter for texture coordinate S, T or R to either REPEAT, CLAMP, CLAMP_TO_EDGE, CLAMP_TO_BORDER, MIRRORED_REPEAT or ONCE. Initially, this field is set to REPEAT for S, T and R.<br>
 *<br>
 * - SFEnum \c usage = IMAGE<br>
 *   Indicating the expected usage pattern of the texture.<br>
 *<br>
 *
 * @ingroup g_abstractNodes
 */
struct VGD_API Texture : public vgd::node::MultiAttribute
{



	/**
	 * @name Accessors to field function
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c function.
	 */
	typedef std::string FunctionValueType;

	/**
	 * @brief Type definition of the field named \c function
	 */
	typedef vgd::field::TOptionalField< FunctionValueType > FFunctionType;


	/**
	 * @brief Gets the value of field named \c function.
	 */
	const bool getFunction( FunctionValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c function.
 	 */
	void setFunction( const FunctionValueType& value );

	/**
	 * @brief Erases the field named \c function.
	 */
	void eraseFunction();

	/**
	 * @brief Tests if the value of field named \c function has been initialized.
	 */
	const bool hasFunction() const;
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
		MIN_FILTER = 284,	///< Choose one value among NEAREST, LINEAR (default), NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR.
		MAG_FILTER = 285,	///< Choose one value among NEAREST or LINEAR (default).
		DEFAULT_FILTERPARAMETER = MAG_FILTER	///< Choose one value among NEAREST or LINEAR (default).
	};

	/**
	 * @brief Type definition of the value contained by field named \c filterParameter.
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

			retVal.push_back( 284 );
			retVal.push_back( 285 );

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
		NEAREST = 286,	///< 
		LINEAR = 287,	///< 
		LINEAR_MIPMAP_NEAREST = 289,	///< 
		NEAREST_MIPMAP_NEAREST = 288,	///< 
		LINEAR_MIPMAP_LINEAR = 291,	///< 
		NEAREST_MIPMAP_LINEAR = 290,	///< 
		DEFAULT_FILTER = LINEAR	///< 
	};

	/**
	 * @brief Type definition of the value contained by field named \c filter.
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

			retVal.push_back( 286 );
			retVal.push_back( 287 );
			retVal.push_back( 289 );
			retVal.push_back( 288 );
			retVal.push_back( 291 );
			retVal.push_back( 290 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "NEAREST" );
			retVal.push_back( "LINEAR" );
			retVal.push_back( "LINEAR_MIPMAP_NEAREST" );
			retVal.push_back( "NEAREST_MIPMAP_NEAREST" );
			retVal.push_back( "LINEAR_MIPMAP_LINEAR" );
			retVal.push_back( "NEAREST_MIPMAP_LINEAR" );

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
		WRAP_T = 276,	///< 
		WRAP_S = 275,	///< 
		WRAP_R = 277,	///< 
		DEFAULT_WRAPPARAMETER = WRAP_S	///< 
	};

	/**
	 * @brief Type definition of the value contained by field named \c wrapParameter.
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

			retVal.push_back( 276 );
			retVal.push_back( 275 );
			retVal.push_back( 277 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "WRAP_T" );
			retVal.push_back( "WRAP_S" );
			retVal.push_back( "WRAP_R" );

			return retVal;
		}
	};

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		CLAMP = 279,	///< 
		REPEAT = 278,	///< 
		MIRRORED_REPEAT = 282,	///< 
		CLAMP_TO_EDGE = 280,	///< 
		CLAMP_TO_BORDER = 281,	///< 
		ONCE = 283,	///< Don't set texture coordinates outside the interval [0.f, 1.f]
		DEFAULT_WRAP = REPEAT	///< 
	};

	/**
	 * @brief Type definition of the value contained by field named \c wrap.
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

			retVal.push_back( 279 );
			retVal.push_back( 278 );
			retVal.push_back( 282 );
			retVal.push_back( 280 );
			retVal.push_back( 281 );
			retVal.push_back( 283 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "CLAMP" );
			retVal.push_back( "REPEAT" );
			retVal.push_back( "MIRRORED_REPEAT" );
			retVal.push_back( "CLAMP_TO_EDGE" );
			retVal.push_back( "CLAMP_TO_BORDER" );
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
	 * @name Accessors to field usage
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		IMAGE = 273,	///< Simple image mapping
		SHADOW = 274,	///< Shadow mapping
		DEFAULT_USAGE = IMAGE	///< Simple image mapping
	};

	/**
	 * @brief Type definition of the value contained by field named \c usage.
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

			retVal.push_back( 273 );
			retVal.push_back( 274 );

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
	 * @brief Returns the name of field \c function.
	 *
	 * @return the name of field \c function.
	 */
	static const std::string getFFunction( void );

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
	 * @brief Returns the name of field \c wrap.
	 *
	 * @return the name of field \c wrap.
	 */
	static const std::string getFWrap( void );

	/**
	 * @brief Returns the name of field \c usage.
	 *
	 * @return the name of field \c usage.
	 */
	static const std::string getFUsage( void );

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
