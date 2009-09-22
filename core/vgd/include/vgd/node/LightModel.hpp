// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LIGHTMODEL_HPP
#define _VGD_NODE_LIGHTMODEL_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Enum.hpp"
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
 *	- OFEnum \c [viewer] = AT_INFINITY\n
 *		Specifies how specular reflection angles are computed. Possible values : - AT_INFINITY specular reflections are computed from the origin of the eye coordinate system. - AT_EYE specular reflection angles take the view direction to be parallel to and in the direction of the -z axis, regardless of the location of the vertex in eye coordinates.
 *	- OFEnum \c [model] = STANDARD_PER_VERTEX\n
 *		Sets the lighting model to LIGHTING_OFF, STANDARD_PER_VERTEX or STANDARD_PER_PIXEL.
 *	- OFEnum \c [shadow] = NONE\n
 *		Specifies the algorithm used to compute shadow.
 *	- OFBool \c [twoSided] = false\n
 *		Specifies whether one- or two-sided lighting calculations are done for polygons and triangles.
 *	- OFVec4f \c [ambient] = vgm::Vec4f(0.2f, 0.2f, 0.2f, 0.0f)\n
 *		Sets the ambient RGBA intensity of the entire scene.
 *
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
	 * @name Accessors to field viewer
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		AT_INFINITY = 265,	///< Specular reflections are computed from the origin of the eye coordinate system
		AT_EYE = 266,	///< Specular reflection angles take the view direction to be parallel to and in the direction of the -z axis, regardless of the location of the vertex in eye coordinates
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

			retVal.push_back( 265 );
			retVal.push_back( 266 );

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
	 * @name Accessors to field model
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		STANDARD_PER_PIXEL = 264,	///< Lighting is computed per pixel
		LIGHTING_OFF = 262,	///< No lighting
		STANDARD_PER_VERTEX = 263,	///< Lighting is computed per vertex
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

			retVal.push_back( 264 );
			retVal.push_back( 262 );
			retVal.push_back( 263 );

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
		NONE = 267,	///< Shadows are not computed
		SHADOW_MAPPING = 268,	///< Shadows are computed using shadow mapping algorithm
		DEFAULT_SHADOW = NONE	///< Shadows are not computed
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

			retVal.push_back( 267 );
			retVal.push_back( 268 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "NONE" );
			retVal.push_back( "SHADOW_MAPPING" );

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
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c viewer.
	 *
	 * @return the name of field \c viewer.
	 */
	static const std::string getFViewer( void );

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

	/**
	 * @brief Returns the name of field \c twoSided.
	 *
	 * @return the name of field \c twoSided.
	 */
	static const std::string getFTwoSided( void );

	/**
	 * @brief Returns the name of field \c ambient.
	 *
	 * @return the name of field \c ambient.
	 */
	static const std::string getFAmbient( void );

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
