// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LIGHTMODEL_HPP
#define _VGD_NODE_LIGHTMODEL_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/Vec2f.hpp"
#include "vgd/field/Vec4f.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Lighting model node
 *
 * This node specifies current lighting mode (off/standard per vertex lighting/standard per pixel lighting) and some options of the lighting model. 
 *
 * New fields defined by this node :
 * - OFEnum \c [shadowMapSize] = (MEDIUM)<br>
 *   Specifies the size of the shadow map<br>
 *<br>
 * - OFEnum \c [shadowFiltering] = (LINEAR)<br>
 *   Defines depth map hardware filtering (not the filtering done in shaders).<br>
 *<br>
 * - SFEnum \c shadowMapType = (INT32)<br>
 *<br>
 * - SFFloat \c illuminationInShadow = (0.4f)<br>
 *   value=[0,1] : 0 full attenuation in shadow, 1 no attenuation in shadow<br>
 *<br>
 * - OFBool \c [twoSided] = (false)<br>
 *   Specifies whether one- or two-sided lighting calculations are done for polygons and triangles.<br>
 *<br>
 * - SFFloat \c samplingSize = (1.0)<br>
 *<br>
 * - SFBool \c option2 = (false)<br>
 *<br>
 * - OFVec4f \c [ambient] = vgm::Vec4f(0.2f, 0.2f, 0.2f, 0.0f)<br>
 *   Sets the ambient RGBA intensity of the entire scene.<br>
 *<br>
 * - SFBool \c bumpMapping = (false)<br>
 *   Specifies if the bumpmapping computation is enabled or disabled. This is a technique in computer graphics for simulating bumps and wrinkles on the surface of an object.<br>
 *<br>
 * - OFEnum \c [viewer] = (AT_INFINITY)<br>
 *   Specifies how specular reflection angles are computed. Possible values : - AT_INFINITY specular reflections are computed from the origin of the eye coordinate system. - AT_EYE specular reflection angles take the view direction to be parallel to and in the direction of the -z axis, regardless of the location of the vertex in eye coordinates.<br>
 *<br>
 * - SFBool \c ignorePostProcessing = (false)<br>
 *   true to ignore the whole post-processing stage, false to do post-processing stage if at least one PostProcessing node is defined.<br>
 *<br>
 * - OFEnum \c [model] = (STANDARD_PER_VERTEX)<br>
 *   Sets the lighting model to LIGHTING_OFF, STANDARD_PER_VERTEX or STANDARD_PER_PIXEL.<br>
 *<br>
 * - SFVec2f \c shadowPolygonOffset = vgm::Vec2f(4.f, 16.f)<br>
 *<br>
 * - OFEnum \c [shadow] = (SHADOW_OFF)<br>
 *   Specifies the algorithm used to compute shadow.<br>
 *<br>
 * - SFEnum \c option0 = (CHOICE0)<br>
 *<br>
 * - SFBool \c option1 = (false)<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_coloringAndLightingNodes
 */
struct VGD_API LightModel : public vgd::node::SingleAttribute
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
	static vgd::Shp< LightModel > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< LightModel > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< LightModel > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field shadowMapSize
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		HIGH = 322,	///< High resolution shadow map
		VERY_HIGH = 323,	///< Very high resolution shadow map
		MEDIUM = 321,	///< Medium resolution shadow map
		LOW = 320,	///< Low resolution shadow map
		DEFAULT_SHADOWMAPSIZE = MEDIUM	///< Medium resolution shadow map
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ShadowMapSizeValueType : public vgd::field::Enum
	{
		ShadowMapSizeValueType()
		{}

		ShadowMapSizeValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ShadowMapSizeValueType( const ShadowMapSizeValueType& o )
		: vgd::field::Enum(o)
		{}

		ShadowMapSizeValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 320 );
			retVal.push_back( 321 );
			retVal.push_back( 322 );
			retVal.push_back( 323 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "LOW" );
			retVal.push_back( "MEDIUM" );
			retVal.push_back( "HIGH" );
			retVal.push_back( "VERY_HIGH" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c shadowMapSize
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FShadowMapSizeType;


	/**
	 * @brief Gets the value of field named \c shadowMapSize.
	 */
	const bool getShadowMapSize( ShadowMapSizeValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c shadowMapSize.
 	 */
	void setShadowMapSize( const ShadowMapSizeValueType& value );

	/**
	 * @brief Erases the field named \c shadowMapSize.
	 */
	void eraseShadowMapSize();

	/**
	 * @brief Tests if the value of field named \c shadowMapSize has been initialized.
	 */
	const bool hasShadowMapSize() const;
	//@}



	/**
	 * @name Accessors to field shadowFiltering
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		NEAREST = 324,	///< 
		LINEAR = 325,	///< 
		DEFAULT_SHADOWFILTERING = LINEAR	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ShadowFilteringValueType : public vgd::field::Enum
	{
		ShadowFilteringValueType()
		{}

		ShadowFilteringValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ShadowFilteringValueType( const ShadowFilteringValueType& o )
		: vgd::field::Enum(o)
		{}

		ShadowFilteringValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 324 );
			retVal.push_back( 325 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "NEAREST" );
			retVal.push_back( "LINEAR" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c shadowFiltering
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FShadowFilteringType;


	/**
	 * @brief Gets the value of field named \c shadowFiltering.
	 */
	const bool getShadowFiltering( ShadowFilteringValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c shadowFiltering.
 	 */
	void setShadowFiltering( const ShadowFilteringValueType& value );

	/**
	 * @brief Erases the field named \c shadowFiltering.
	 */
	void eraseShadowFiltering();

	/**
	 * @brief Tests if the value of field named \c shadowFiltering has been initialized.
	 */
	const bool hasShadowFiltering() const;
	//@}



	/**
	 * @name Accessors to field shadowMapType
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		INT24 = 286,	///< see Texture.internalFormat documentation
		INT32 = 287,	///< see Texture.internalFormat documentation
		INT16 = 285,	///< see Texture.internalFormat documentation
		FLOAT32 = 288,	///< see Texture.internalFormat documentation
		DEFAULT_SHADOWMAPTYPE = INT32	///< see Texture.internalFormat documentation
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ShadowMapTypeValueType : public vgd::field::Enum
	{
		ShadowMapTypeValueType()
		{}

		ShadowMapTypeValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ShadowMapTypeValueType( const ShadowMapTypeValueType& o )
		: vgd::field::Enum(o)
		{}

		ShadowMapTypeValueType( const vgd::field::Enum& o )
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

			retVal.push_back( "INT16" );
			retVal.push_back( "INT24" );
			retVal.push_back( "INT32" );
			retVal.push_back( "FLOAT32" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c shadowMapType
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FShadowMapTypeType;


	/**
	 * @brief Gets the value of field named \c shadowMapType.
	 */
	const ShadowMapTypeValueType getShadowMapType() const;

	/**
	 * @brief Sets the value of field named \c shadowMapType.
	 */
	void setShadowMapType( const ShadowMapTypeValueType value );

	//@}



	/**
	 * @name Accessors to field illuminationInShadow
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c illuminationInShadow.
	 */
	typedef float IlluminationInShadowValueType;

	/**
	 * @brief The default value of field named \c illuminationInShadow.
	 */
	static const IlluminationInShadowValueType DEFAULT_ILLUMINATIONINSHADOW;

	/**
	 * @brief Type definition of the field named \c illuminationInShadow
	 */
	typedef vgd::field::TSingleField< IlluminationInShadowValueType > FIlluminationInShadowType;


	/**
	 * @brief Gets the value of field named \c illuminationInShadow.
	 */
	const IlluminationInShadowValueType getIlluminationInShadow() const;

	/**
	 * @brief Sets the value of field named \c illuminationInShadow.
	 */
	void setIlluminationInShadow( const IlluminationInShadowValueType value );

	//@}



	/**
	 * @name Accessors to field twoSided
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c twoSided.
	 */
	typedef bool TwoSidedValueType;

	/**
	 * @brief The default value of field named \c twoSided.
	 */
	static const TwoSidedValueType DEFAULT_TWOSIDED;

	/**
	 * @brief Type definition of the field named \c twoSided
	 */
	typedef vgd::field::TOptionalField< TwoSidedValueType > FTwoSidedType;


	/**
	 * @brief Gets the value of field named \c twoSided.
	 */
	const bool getTwoSided( TwoSidedValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c twoSided.
 	 */
	void setTwoSided( const TwoSidedValueType& value );

	/**
	 * @brief Erases the field named \c twoSided.
	 */
	void eraseTwoSided();

	/**
	 * @brief Tests if the value of field named \c twoSided has been initialized.
	 */
	const bool hasTwoSided() const;
	//@}



	/**
	 * @name Accessors to field samplingSize
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c samplingSize.
	 */
	typedef float SamplingSizeValueType;

	/**
	 * @brief The default value of field named \c samplingSize.
	 */
	static const SamplingSizeValueType DEFAULT_SAMPLINGSIZE;

	/**
	 * @brief Type definition of the field named \c samplingSize
	 */
	typedef vgd::field::TSingleField< SamplingSizeValueType > FSamplingSizeType;


	/**
	 * @brief Gets the value of field named \c samplingSize.
	 */
	const SamplingSizeValueType getSamplingSize() const;

	/**
	 * @brief Sets the value of field named \c samplingSize.
	 */
	void setSamplingSize( const SamplingSizeValueType value );

	//@}



	/**
	 * @name Accessors to field option2
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c option2.
	 */
	typedef bool Option2ValueType;

	/**
	 * @brief The default value of field named \c option2.
	 */
	static const Option2ValueType DEFAULT_OPTION2;

	/**
	 * @brief Type definition of the field named \c option2
	 */
	typedef vgd::field::TSingleField< Option2ValueType > FOption2Type;


	/**
	 * @brief Gets the value of field named \c option2.
	 */
	const Option2ValueType getOption2() const;

	/**
	 * @brief Sets the value of field named \c option2.
	 */
	void setOption2( const Option2ValueType value );

	//@}



	/**
	 * @name Accessors to field ambient
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c ambient.
	 */
	typedef vgm::Vec4f AmbientValueType;

	/**
	 * @brief The default value of field named \c ambient.
	 */
	static const AmbientValueType DEFAULT_AMBIENT;

	/**
	 * @brief Type definition of the field named \c ambient
	 */
	typedef vgd::field::TOptionalField< AmbientValueType > FAmbientType;


	/**
	 * @brief Gets the value of field named \c ambient.
	 */
	const bool getAmbient( AmbientValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c ambient.
 	 */
	void setAmbient( const AmbientValueType& value );

	/**
	 * @brief Erases the field named \c ambient.
	 */
	void eraseAmbient();

	/**
	 * @brief Tests if the value of field named \c ambient has been initialized.
	 */
	const bool hasAmbient() const;
	//@}



	/**
	 * @name Accessors to field bumpMapping
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c bumpMapping.
	 */
	typedef bool BumpMappingValueType;

	/**
	 * @brief The default value of field named \c bumpMapping.
	 */
	static const BumpMappingValueType DEFAULT_BUMPMAPPING;

	/**
	 * @brief Type definition of the field named \c bumpMapping
	 */
	typedef vgd::field::TSingleField< BumpMappingValueType > FBumpMappingType;


	/**
	 * @brief Gets the value of field named \c bumpMapping.
	 */
	const BumpMappingValueType getBumpMapping() const;

	/**
	 * @brief Sets the value of field named \c bumpMapping.
	 */
	void setBumpMapping( const BumpMappingValueType value );

	//@}



	/**
	 * @name Accessors to field viewer
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		AT_INFINITY = 297,	///< Specular reflections are computed from the origin of the eye coordinate system
		AT_EYE = 298,	///< Specular reflection angles take the view direction to be parallel to and in the direction of the -z axis, regardless of the location of the vertex in eye coordinates
		DEFAULT_VIEWER = AT_INFINITY	///< Specular reflections are computed from the origin of the eye coordinate system
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ViewerValueType : public vgd::field::Enum
	{
		ViewerValueType()
		{}

		ViewerValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ViewerValueType( const ViewerValueType& o )
		: vgd::field::Enum(o)
		{}

		ViewerValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 297 );
			retVal.push_back( 298 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "AT_INFINITY" );
			retVal.push_back( "AT_EYE" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c viewer
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FViewerType;


	/**
	 * @brief Gets the value of field named \c viewer.
	 */
	const bool getViewer( ViewerValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c viewer.
 	 */
	void setViewer( const ViewerValueType& value );

	/**
	 * @brief Erases the field named \c viewer.
	 */
	void eraseViewer();

	/**
	 * @brief Tests if the value of field named \c viewer has been initialized.
	 */
	const bool hasViewer() const;
	//@}



	/**
	 * @name Accessors to field ignorePostProcessing
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c ignorePostProcessing.
	 */
	typedef bool IgnorePostProcessingValueType;

	/**
	 * @brief The default value of field named \c ignorePostProcessing.
	 */
	static const IgnorePostProcessingValueType DEFAULT_IGNOREPOSTPROCESSING;

	/**
	 * @brief Type definition of the field named \c ignorePostProcessing
	 */
	typedef vgd::field::TSingleField< IgnorePostProcessingValueType > FIgnorePostProcessingType;


	/**
	 * @brief Gets the value of field named \c ignorePostProcessing.
	 */
	const IgnorePostProcessingValueType getIgnorePostProcessing() const;

	/**
	 * @brief Sets the value of field named \c ignorePostProcessing.
	 */
	void setIgnorePostProcessing( const IgnorePostProcessingValueType value );

	//@}



	/**
	 * @name Accessors to field model
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		STANDARD_PER_PIXEL = 296,	///< Lighting is computed per pixel
		LIGHTING_OFF = 294,	///< No lighting
		STANDARD_PER_VERTEX = 295,	///< Lighting is computed per vertex
		DEFAULT_MODEL = STANDARD_PER_VERTEX	///< Lighting is computed per vertex
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ModelValueType : public vgd::field::Enum
	{
		ModelValueType()
		{}

		ModelValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ModelValueType( const ModelValueType& o )
		: vgd::field::Enum(o)
		{}

		ModelValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 294 );
			retVal.push_back( 295 );
			retVal.push_back( 296 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "LIGHTING_OFF" );
			retVal.push_back( "STANDARD_PER_VERTEX" );
			retVal.push_back( "STANDARD_PER_PIXEL" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c model
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FModelType;


	/**
	 * @brief Gets the value of field named \c model.
	 */
	const bool getModel( ModelValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c model.
 	 */
	void setModel( const ModelValueType& value );

	/**
	 * @brief Erases the field named \c model.
	 */
	void eraseModel();

	/**
	 * @brief Tests if the value of field named \c model has been initialized.
	 */
	const bool hasModel() const;
	//@}



	/**
	 * @name Accessors to field shadowPolygonOffset
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c shadowPolygonOffset.
	 */
	typedef vgm::Vec2f ShadowPolygonOffsetValueType;

	/**
	 * @brief The default value of field named \c shadowPolygonOffset.
	 */
	static const ShadowPolygonOffsetValueType DEFAULT_SHADOWPOLYGONOFFSET;

	/**
	 * @brief Type definition of the field named \c shadowPolygonOffset
	 */
	typedef vgd::field::TSingleField< ShadowPolygonOffsetValueType > FShadowPolygonOffsetType;


	/**
	 * @brief Gets the value of field named \c shadowPolygonOffset.
	 */
	const ShadowPolygonOffsetValueType getShadowPolygonOffset() const;

	/**
	 * @brief Sets the value of field named \c shadowPolygonOffset.
	 */
	void setShadowPolygonOffset( const ShadowPolygonOffsetValueType value );

	//@}



	/**
	 * @name Accessors to field shadow
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		SHADOW_MAPPING_25U = 308,	///< Shadows are computed using shadow mapping algorithm pcf using twenty five uniform samples
		SHADOW_MAPPING_36U = 310,	///< Shadows are computed using shadow mapping algorithm pcf using thirty six uniform samples
		SHADOW_MAPPING_4UM = 302,	///< Shadows are computed using shadow mapping algorithm pcf using four uniform samples
		SHADOW_MAPPING_256UM = 319,	///< Shadows are computed using shadow mapping algorithm pcf using 256 uniform samples
		SHADOW_MAPPING = 300,	///< Shadows are computed using shadow mapping algorithm
		SHADOW_MAPPING_64UM = 313,	///< Shadows are computed using shadow mapping algorithm pcf using sixty four uniform samples
		SHADOW_OFF = 299,	///< Shadows are not computed
		SHADOW_MAPPING_9UM = 305,	///< Shadows are computed using shadow mapping algorithm pcf using nine uniform samples
		SHADOW_MAPPING_9U = 304,	///< Shadows are computed using shadow mapping algorithm pcf using nine uniform samples
		SHADOW_MAPPING_4U = 301,	///< Shadows are computed using shadow mapping algorithm pcf using four uniform samples
		SHADOW_MAPPING_25UM = 309,	///< Shadows are computed using shadow mapping algorithm pcf using twenty five uniform samples
		SHADOW_MAPPING_16U = 306,	///< Shadows are computed using shadow mapping algorithm pcf using sixteen uniform samples
		SHADOW_MAPPING_225U = 316,	///< Shadows are computed using shadow mapping algorithm pcf using 225 uniform samples
		SHADOW_MAPPING_225UM = 317,	///< Shadows are computed using shadow mapping algorithm pcf using 225 uniform samples
		SHADOW_MAPPING_4DM = 303,	///< Shadows are computed using shadow mapping algorithm pcf using four dithered samples
		SHADOW_MAPPING_144U = 314,	///< Shadows are computed using shadow mapping algorithm pcf using 144 uniform samples
		SHADOW_MAPPING_64U = 312,	///< Shadows are computed using shadow mapping algorithm pcf using sixty four uniform samples
		SHADOW_MAPPING_256U = 318,	///< Shadows are computed using shadow mapping algorithm pcf using 256 uniform samples
		SHADOW_MAPPING_36UM = 311,	///< Shadows are computed using shadow mapping algorithm pcf using thirty six uniform samples
		SHADOW_MAPPING_16UM = 307,	///< Shadows are computed using shadow mapping algorithm pcf using sixteen uniform samples
		SHADOW_MAPPING_144UM = 315,	///< Shadows are computed using shadow mapping algorithm pcf using 144 uniform samples
		DEFAULT_SHADOW = SHADOW_OFF	///< Shadows are not computed
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ShadowValueType : public vgd::field::Enum
	{
		ShadowValueType()
		{}

		ShadowValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ShadowValueType( const ShadowValueType& o )
		: vgd::field::Enum(o)
		{}

		ShadowValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 299 );
			retVal.push_back( 300 );
			retVal.push_back( 301 );
			retVal.push_back( 302 );
			retVal.push_back( 303 );
			retVal.push_back( 304 );
			retVal.push_back( 305 );
			retVal.push_back( 306 );
			retVal.push_back( 307 );
			retVal.push_back( 308 );
			retVal.push_back( 309 );
			retVal.push_back( 310 );
			retVal.push_back( 311 );
			retVal.push_back( 312 );
			retVal.push_back( 313 );
			retVal.push_back( 314 );
			retVal.push_back( 315 );
			retVal.push_back( 316 );
			retVal.push_back( 317 );
			retVal.push_back( 318 );
			retVal.push_back( 319 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "SHADOW_OFF" );
			retVal.push_back( "SHADOW_MAPPING" );
			retVal.push_back( "SHADOW_MAPPING_4U" );
			retVal.push_back( "SHADOW_MAPPING_4UM" );
			retVal.push_back( "SHADOW_MAPPING_4DM" );
			retVal.push_back( "SHADOW_MAPPING_9U" );
			retVal.push_back( "SHADOW_MAPPING_9UM" );
			retVal.push_back( "SHADOW_MAPPING_16U" );
			retVal.push_back( "SHADOW_MAPPING_16UM" );
			retVal.push_back( "SHADOW_MAPPING_25U" );
			retVal.push_back( "SHADOW_MAPPING_25UM" );
			retVal.push_back( "SHADOW_MAPPING_36U" );
			retVal.push_back( "SHADOW_MAPPING_36UM" );
			retVal.push_back( "SHADOW_MAPPING_64U" );
			retVal.push_back( "SHADOW_MAPPING_64UM" );
			retVal.push_back( "SHADOW_MAPPING_144U" );
			retVal.push_back( "SHADOW_MAPPING_144UM" );
			retVal.push_back( "SHADOW_MAPPING_225U" );
			retVal.push_back( "SHADOW_MAPPING_225UM" );
			retVal.push_back( "SHADOW_MAPPING_256U" );
			retVal.push_back( "SHADOW_MAPPING_256UM" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c shadow
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FShadowType;


	/**
	 * @brief Gets the value of field named \c shadow.
	 */
	const bool getShadow( ShadowValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c shadow.
 	 */
	void setShadow( const ShadowValueType& value );

	/**
	 * @brief Erases the field named \c shadow.
	 */
	void eraseShadow();

	/**
	 * @brief Tests if the value of field named \c shadow has been initialized.
	 */
	const bool hasShadow() const;
	//@}



	/**
	 * @name Accessors to field option0
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		CHOICE4 = 293,	///< 
		CHOICE0 = 289,	///< 
		CHOICE1 = 290,	///< 
		CHOICE2 = 291,	///< 
		CHOICE3 = 292,	///< 
		DEFAULT_OPTION0 = CHOICE0	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct Option0ValueType : public vgd::field::Enum
	{
		Option0ValueType()
		{}

		Option0ValueType( const int v )
		: vgd::field::Enum(v)
		{}

		Option0ValueType( const Option0ValueType& o )
		: vgd::field::Enum(o)
		{}

		Option0ValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 289 );
			retVal.push_back( 290 );
			retVal.push_back( 291 );
			retVal.push_back( 292 );
			retVal.push_back( 293 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "CHOICE0" );
			retVal.push_back( "CHOICE1" );
			retVal.push_back( "CHOICE2" );
			retVal.push_back( "CHOICE3" );
			retVal.push_back( "CHOICE4" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c option0
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FOption0Type;


	/**
	 * @brief Gets the value of field named \c option0.
	 */
	const Option0ValueType getOption0() const;

	/**
	 * @brief Sets the value of field named \c option0.
	 */
	void setOption0( const Option0ValueType value );

	//@}



	/**
	 * @name Accessors to field option1
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c option1.
	 */
	typedef bool Option1ValueType;

	/**
	 * @brief The default value of field named \c option1.
	 */
	static const Option1ValueType DEFAULT_OPTION1;

	/**
	 * @brief Type definition of the field named \c option1
	 */
	typedef vgd::field::TSingleField< Option1ValueType > FOption1Type;


	/**
	 * @brief Gets the value of field named \c option1.
	 */
	const Option1ValueType getOption1() const;

	/**
	 * @brief Sets the value of field named \c option1.
	 */
	void setOption1( const Option1ValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c shadowMapSize.
	 *
	 * @return the name of field \c shadowMapSize.
	 */
	static const std::string getFShadowMapSize( void );

	/**
	 * @brief Returns the name of field \c shadowFiltering.
	 *
	 * @return the name of field \c shadowFiltering.
	 */
	static const std::string getFShadowFiltering( void );

	/**
	 * @brief Returns the name of field \c shadowMapType.
	 *
	 * @return the name of field \c shadowMapType.
	 */
	static const std::string getFShadowMapType( void );

	/**
	 * @brief Returns the name of field \c illuminationInShadow.
	 *
	 * @return the name of field \c illuminationInShadow.
	 */
	static const std::string getFIlluminationInShadow( void );

	/**
	 * @brief Returns the name of field \c twoSided.
	 *
	 * @return the name of field \c twoSided.
	 */
	static const std::string getFTwoSided( void );

	/**
	 * @brief Returns the name of field \c samplingSize.
	 *
	 * @return the name of field \c samplingSize.
	 */
	static const std::string getFSamplingSize( void );

	/**
	 * @brief Returns the name of field \c option2.
	 *
	 * @return the name of field \c option2.
	 */
	static const std::string getFOption2( void );

	/**
	 * @brief Returns the name of field \c ambient.
	 *
	 * @return the name of field \c ambient.
	 */
	static const std::string getFAmbient( void );

	/**
	 * @brief Returns the name of field \c bumpMapping.
	 *
	 * @return the name of field \c bumpMapping.
	 */
	static const std::string getFBumpMapping( void );

	/**
	 * @brief Returns the name of field \c viewer.
	 *
	 * @return the name of field \c viewer.
	 */
	static const std::string getFViewer( void );

	/**
	 * @brief Returns the name of field \c ignorePostProcessing.
	 *
	 * @return the name of field \c ignorePostProcessing.
	 */
	static const std::string getFIgnorePostProcessing( void );

	/**
	 * @brief Returns the name of field \c model.
	 *
	 * @return the name of field \c model.
	 */
	static const std::string getFModel( void );

	/**
	 * @brief Returns the name of field \c shadowPolygonOffset.
	 *
	 * @return the name of field \c shadowPolygonOffset.
	 */
	static const std::string getFShadowPolygonOffset( void );

	/**
	 * @brief Returns the name of field \c shadow.
	 *
	 * @return the name of field \c shadow.
	 */
	static const std::string getFShadow( void );

	/**
	 * @brief Returns the name of field \c option0.
	 *
	 * @return the name of field \c option0.
	 */
	static const std::string getFOption0( void );

	/**
	 * @brief Returns the name of field \c option1.
	 *
	 * @return the name of field \c option1.
	 */
	static const std::string getFOption1( void );

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
	LightModel( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , LightModel );
private:
	static const vgd::basic::RegisterNode<LightModel> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_LIGHTMODEL_HPP
