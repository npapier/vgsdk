// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CLEARFRAMEBUFFER_HPP
#define _VGD_NODE_CLEARFRAMEBUFFER_HPP

#include "vgd/field/Vec4f.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Node clearing the framebuffer
 *
 * 
 *
 * New fields defined by this node :
 * - OFVec4f \c [clearColor] = vgm::Vec4f(0.f, 0.f, 0.f, 0.f)<br>
 *   Specifies the clear color.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_frameBufferNodes
 */
struct VGD_API ClearFrameBuffer : public vgd::node::SingleAttribute
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
	static vgd::Shp< ClearFrameBuffer > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< ClearFrameBuffer > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< ClearFrameBuffer > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field clearColor
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c clearColor.
	 */
	typedef vgm::Vec4f ClearColorValueType;

	/**
	 * @brief The default value of field named \c clearColor.
	 */
	static const ClearColorValueType DEFAULT_CLEARCOLOR;

	/**
	 * @brief Type definition of the field named \c clearColor
	 */
	typedef vgd::field::TOptionalField< ClearColorValueType > FClearColorType;


	/**
	 * @brief Gets the value of field named \c clearColor.
	 */
	const bool getClearColor( ClearColorValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c clearColor.
 	 */
	void setClearColor( const ClearColorValueType& value );

	/**
	 * @brief Erases the field named \c clearColor.
	 */
	void eraseClearColor();

	/**
	 * @brief Tests if the value of field named \c clearColor has been initialized.
	 */
	const bool hasClearColor() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c clearColor.
	 *
	 * @return the name of field \c clearColor.
	 */
	static const std::string getFClearColor( void );

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
	ClearFrameBuffer( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , ClearFrameBuffer );
private:
	static const vgd::basic::RegisterNode<ClearFrameBuffer> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_CLEARFRAMEBUFFER_HPP
