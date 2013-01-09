// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ENGINEPROPERTIES_HPP
#define _VGD_NODE_ENGINEPROPERTIES_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Definition of several properties of vgsdk engine
 *
 * This node defines the default anisotropy used during texture filtering, global tessellation properties. 
 *
 * New fields defined by this node :
 * - SFFloat \c tessellationBias = (0.55f)<br>
 *   Specifies the tessellation bias used by the Phong Tessellation algorithm (only used if tessellation is enabled).<br>
 *<br>
 * - OFFloat \c [maxAnisotropy] = (1.f)<br>
 *   Specifies the engine default maximum degree of anisotropy (see vgd::node::Texture).<br>
 *<br>
 * - SFFloat \c tessellationFactor = (2.0f)<br>
 *   Specifies the tessellation level used by the tessellation control shaders to tessellate the incoming primitive (only used if tessellation is enabled).<br>
 *<br>
 * - SFBool \c tessellation = (false)<br>
 *   Specifies if the tessellation is enabled or disabled.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 */
struct VGD_API EngineProperties : public vgd::node::SingleAttribute
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
	static vgd::Shp< EngineProperties > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< EngineProperties > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< EngineProperties > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field tessellationBias
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tessellationBias.
	 */
	typedef float TessellationBiasValueType;

	/**
	 * @brief The default value of field named \c tessellationBias.
	 */
	static const TessellationBiasValueType DEFAULT_TESSELLATIONBIAS;

	/**
	 * @brief Type definition of the field named \c tessellationBias
	 */
	typedef vgd::field::TSingleField< TessellationBiasValueType > FTessellationBiasType;


	/**
	 * @brief Gets the value of field named \c tessellationBias.
	 */
	const TessellationBiasValueType getTessellationBias() const;

	/**
	 * @brief Sets the value of field named \c tessellationBias.
	 */
	void setTessellationBias( const TessellationBiasValueType value );

	//@}



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
	 * @name Accessors to field tessellationFactor
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tessellationFactor.
	 */
	typedef float TessellationFactorValueType;

	/**
	 * @brief The default value of field named \c tessellationFactor.
	 */
	static const TessellationFactorValueType DEFAULT_TESSELLATIONFACTOR;

	/**
	 * @brief Type definition of the field named \c tessellationFactor
	 */
	typedef vgd::field::TSingleField< TessellationFactorValueType > FTessellationFactorType;


	/**
	 * @brief Gets the value of field named \c tessellationFactor.
	 */
	const TessellationFactorValueType getTessellationFactor() const;

	/**
	 * @brief Sets the value of field named \c tessellationFactor.
	 */
	void setTessellationFactor( const TessellationFactorValueType value );

	//@}



	/**
	 * @name Accessors to field tessellation
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tessellation.
	 */
	typedef bool TessellationValueType;

	/**
	 * @brief The default value of field named \c tessellation.
	 */
	static const TessellationValueType DEFAULT_TESSELLATION;

	/**
	 * @brief Type definition of the field named \c tessellation
	 */
	typedef vgd::field::TSingleField< TessellationValueType > FTessellationType;


	/**
	 * @brief Gets the value of field named \c tessellation.
	 */
	const TessellationValueType getTessellation() const;

	/**
	 * @brief Sets the value of field named \c tessellation.
	 */
	void setTessellation( const TessellationValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c tessellationBias.
	 *
	 * @return the name of field \c tessellationBias.
	 */
	static const std::string getFTessellationBias( void );

	/**
	 * @brief Returns the name of field \c maxAnisotropy.
	 *
	 * @return the name of field \c maxAnisotropy.
	 */
	static const std::string getFMaxAnisotropy( void );

	/**
	 * @brief Returns the name of field \c tessellationFactor.
	 *
	 * @return the name of field \c tessellationFactor.
	 */
	static const std::string getFTessellationFactor( void );

	/**
	 * @brief Returns the name of field \c tessellation.
	 *
	 * @return the name of field \c tessellation.
	 */
	static const std::string getFTessellation( void );

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
	EngineProperties( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , EngineProperties );
private:
	static const vgd::basic::RegisterNode<EngineProperties> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ENGINEPROPERTIES_HPP
