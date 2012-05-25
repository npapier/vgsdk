// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXGENEYELINEAR_HPP
#define _VGD_NODE_TEXGENEYELINEAR_HPP

#include "vgd/field/MatrixR.hpp"
#include "vgd/node/TexGen.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Generating texture coordinates using eye linear function
 *
 * See OpenGL specification for details 
 *
 * New fields defined by this node :
 * - OFMatrixR \c [parameters] = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *<br>
 *
 *
 * Inherited fields from TexGen:
 * - SFBool \c on = true<br>
 *   Specifies if the texture generation is enabled or disabled.<br>
 *<br>
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_texturingNodes
 */
struct VGD_API TexGenEyeLinear : public vgd::node::TexGen
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
	static vgd::Shp< TexGenEyeLinear > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< TexGenEyeLinear > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< TexGenEyeLinear > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field parameters
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c parameters.
	 */
	typedef vgm::MatrixR ParametersValueType;

	/**
	 * @brief Type definition of the field named \c parameters
	 */
	typedef vgd::field::TOptionalField< ParametersValueType > FParametersType;


	/**
	 * @brief Gets the value of field named \c parameters.
	 */
	const bool getParameters( ParametersValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c parameters.
 	 */
	void setParameters( const ParametersValueType& value );

	/**
	 * @brief Erases the field named \c parameters.
	 */
	void eraseParameters();

	/**
	 * @brief Tests if the value of field named \c parameters has been initialized.
	 */
	const bool hasParameters() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c parameters.
	 *
	 * @return the name of field \c parameters.
	 */
	static const std::string getFParameters( void );

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
	TexGenEyeLinear( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , TexGenEyeLinear );
private:
	static const vgd::basic::RegisterNode<TexGenEyeLinear> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXGENEYELINEAR_HPP
