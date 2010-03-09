// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LIGHTMODEL_HPP
#define _VGD_NODE_LIGHTMODEL_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
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
 * - SFEnum \c shadowMapType = INT16<br>
 *<br>
 * - SFFloat \c illuminationInShadow = 0.4f<br>
 *   value=[0,1] : 0 full attenuation in shadow, 1 no attenuation in shadow<br>
 *<br>
 * - OFBool \c [twoSided] = false<br>
 *   Specifies whether one- or two-sided lighting calculations are done for polygons and triangles.<br>
 *<br>
 * - SFFloat \c samplingSize = 1.0<br>
 *<br>
 * - OFEnum \c [shadowQuality] = MEDIUM<br>
 *   Specifies the quality of the shadow computation<br>
 *<br>
 * - OFEnum \c [viewer] = AT_INFINITY<br>
 *   Specifies how specular reflection angles are computed. Possible values : - AT_INFINITY specular reflections are computed from the origin of the eye coordinate system. - AT_EYE specular reflection angles take the view direction to be parallel to and in the direction of the -z axis, regardless of the location of the vertex in eye coordinates.<br>
 *<br>
 * - SFBool \c useShadowSamplers = true<br>
 *   True to use GLSL shadowSampler, false to use traditionnal texture sampler.<br>
 *<br>
 * - OFVec4f \c [ambient] = vgm::Vec4f(0.2f, 0.2f, 0.2f, 0.0f)<br>
 *   Sets the ambient RGBA intensity of the entire scene.<br>
 *<br>
 * - OFEnum \c [model] = STANDARD_PER_VERTEX<br>
 *   Sets the lighting model to LIGHTING_OFF, STANDARD_PER_VERTEX or STANDARD_PER_PIXEL.<br>
 *<br>
 * - OFEnum \c [shadow] = SHADOW_OFF<br>
 *   Specifies the algorithm used to compute shadow.<br>
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
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< LightModel > createWhole( const std::string nodeName = "DefaultWhole" );

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
		INT32 = 263,	///< 
		INT16 = 264,	///< 
		FLOAT = 262,	///< 
		DEFAULT_SHADOWMAPTYPE = INT16	///< 
	};

	/**
	 * @brief Type definition of the value contained by field named \c shadowMapType.
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

			retVal.push_back( 263 );
			retVal.push_back( 264 );
			retVal.push_back( 262 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "INT32" );
			retVal.push_back( "INT16" );
			retVal.push_back( "FLOAT" );

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
	 * @name Accessors to field shadowQuality
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		HIGH = 281,	///< High resolution shadow map
		VERY_HIGH = 280,	///< Very high resolution shadow map
		MEDIUM = 282,	///< Medium resolution shadow map
		LOW = 283,	///< Low resolution shadow map
		DEFAULT_SHADOWQUALITY = MEDIUM	///< Medium resolution shadow map
	};

	/**
	 * @brief Type definition of the value contained by field named \c shadowQuality.
	 */
	struct ShadowQualityValueType : public vgd::field::Enum
	{
		ShadowQualityValueType()
		{}

		ShadowQualityValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ShadowQualityValueType( const ShadowQualityValueType& o )
		: vgd::field::Enum(o)
		{}

		ShadowQualityValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 281 );
			retVal.push_back( 280 );
			retVal.push_back( 282 );
			retVal.push_back( 283 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "HIGH" );
			retVal.push_back( "VERY_HIGH" );
			retVal.push_back( "MEDIUM" );
			retVal.push_back( "LOW" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c shadowQuality
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FShadowQualityType;


	/**
	 * @brief Gets the value of field named \c shadowQuality.
	 */
	const bool getShadowQuality( ShadowQualityValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c shadowQuality.
 	 */
	void setShadowQuality( const ShadowQualityValueType& value );

	/**
	 * @brief Erases the field named \c shadowQuality.
	 */
	void eraseShadowQuality();

	/**
	 * @brief Tests if the value of field named \c shadowQuality has been initialized.
	 */
	const bool hasShadowQuality() const;
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
		AT_INFINITY = 268,	///< Specular reflections are computed from the origin of the eye coordinate system
		AT_EYE = 269,	///< Specular reflection angles take the view direction to be parallel to and in the direction of the -z axis, regardless of the location of the vertex in eye coordinates
		DEFAULT_VIEWER = AT_INFINITY	///< Specular reflections are computed from the origin of the eye coordinate system
	};

	/**
	 * @brief Type definition of the value contained by field named \c viewer.
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

			retVal.push_back( 268 );
			retVal.push_back( 269 );

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
	 * @name Accessors to field useShadowSamplers
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c useShadowSamplers.
	 */
	typedef bool UseShadowSamplersValueType;

	/**
	 * @brief Type definition of the field named \c useShadowSamplers
	 */
	typedef vgd::field::TSingleField< UseShadowSamplersValueType > FUseShadowSamplersType;


	/**
	 * @brief Gets the value of field named \c useShadowSamplers.
	 */
	const UseShadowSamplersValueType getUseShadowSamplers() const;

	/**
	 * @brief Sets the value of field named \c useShadowSamplers.
	 */
	void setUseShadowSamplers( const UseShadowSamplersValueType value );

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
	 * @name Accessors to field model
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		STANDARD_PER_PIXEL = 267,	///< Lighting is computed per pixel
		LIGHTING_OFF = 265,	///< No lighting
		STANDARD_PER_VERTEX = 266,	///< Lighting is computed per vertex
		DEFAULT_MODEL = STANDARD_PER_VERTEX	///< Lighting is computed per vertex
	};

	/**
	 * @brief Type definition of the value contained by field named \c model.
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

			retVal.push_back( 267 );
			retVal.push_back( 265 );
			retVal.push_back( 266 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "STANDARD_PER_PIXEL" );
			retVal.push_back( "LIGHTING_OFF" );
			retVal.push_back( "STANDARD_PER_VERTEX" );

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
	 * @name Accessors to field shadow
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		SHADOW_MAPPING_16U = 274,	///< Sixteen uniform samples
		SHADOW_MAPPING = 271,	///< Shadows are computed using shadow mapping algorithm
		SHADOW_OFF = 270,	///< Shadows are not computed
		SHADOW_MAPPING_16UM = 275,	///< Sixteen unifrom samples
		SHADOW_MAPPING_64UM = 279,	///< Sixty four uniform samples
		SHADOW_MAPPING_32UM = 277,	///< Thirty two uniform samples
		SHADOW_MAPPING_4U = 272,	///< Four uniform samples
		SHADOW_MAPPING_64U = 278,	///< Sixty four uniform samples
		SHADOW_MAPPING_32U = 276,	///< Thirty two uniform samples
		SHADOW_MAPPING_4DM = 273,	///< Four dithered samples
		DEFAULT_SHADOW = SHADOW_OFF	///< Shadows are not computed
	};

	/**
	 * @brief Type definition of the value contained by field named \c shadow.
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

			retVal.push_back( 274 );
			retVal.push_back( 271 );
			retVal.push_back( 270 );
			retVal.push_back( 275 );
			retVal.push_back( 279 );
			retVal.push_back( 277 );
			retVal.push_back( 272 );
			retVal.push_back( 278 );
			retVal.push_back( 276 );
			retVal.push_back( 273 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "SHADOW_MAPPING_16U" );
			retVal.push_back( "SHADOW_MAPPING" );
			retVal.push_back( "SHADOW_OFF" );
			retVal.push_back( "SHADOW_MAPPING_16UM" );
			retVal.push_back( "SHADOW_MAPPING_64UM" );
			retVal.push_back( "SHADOW_MAPPING_32UM" );
			retVal.push_back( "SHADOW_MAPPING_4U" );
			retVal.push_back( "SHADOW_MAPPING_64U" );
			retVal.push_back( "SHADOW_MAPPING_32U" );
			retVal.push_back( "SHADOW_MAPPING_4DM" );

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
	 * @name Field name accessors
	 */
	//@{

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
	 * @brief Returns the name of field \c shadowQuality.
	 *
	 * @return the name of field \c shadowQuality.
	 */
	static const std::string getFShadowQuality( void );

	/**
	 * @brief Returns the name of field \c viewer.
	 *
	 * @return the name of field \c viewer.
	 */
	static const std::string getFViewer( void );

	/**
	 * @brief Returns the name of field \c useShadowSamplers.
	 *
	 * @return the name of field \c useShadowSamplers.
	 */
	static const std::string getFUseShadowSamplers( void );

	/**
	 * @brief Returns the name of field \c ambient.
	 *
	 * @return the name of field \c ambient.
	 */
	static const std::string getFAmbient( void );

	/**
	 * @brief Returns the name of field \c model.
	 *
	 * @return the name of field \c model.
	 */
	static const std::string getFModel( void );

	/**
	 * @brief Returns the name of field \c shadow.
	 *
	 * @return the name of field \c shadow.
	 */
	static const std::string getFShadow( void );

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
