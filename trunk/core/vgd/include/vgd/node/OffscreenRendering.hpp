// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_OFFSCREENRENDERING_HPP
#define _VGD_NODE_OFFSCREENRENDERING_HPP

#include "vgd/field/GroupShp.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Offscreen rendering of a scene graph
 *
 * Requests the engine to do an offscreen rendering of the scene graph specified by the field root. The offscreen rendering is computed before the rendering of the canvas root. So the result could be used by the canvas scene graph. See OutputBufferProperty node documentation 
 *
 * New fields defined by this node :
 * - SFGroupShp \c root = vgd::node::GroupShp()<br>
 *   Specify the root of the scene graph to render<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_groupNodes
 */
struct VGD_API OffscreenRendering : public vgd::node::SingleAttribute
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
	static vgd::Shp< OffscreenRendering > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< OffscreenRendering > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< OffscreenRendering > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field root
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c root.
	 */
	typedef vgd::node::GroupShp RootValueType;

	/**
	 * @brief The default value of field named \c root.
	 */
	static const RootValueType DEFAULT_ROOT;

	/**
	 * @brief Type definition of the field named \c root
	 */
	typedef vgd::field::TSingleField< RootValueType > FRootType;


	/**
	 * @brief Gets the value of field named \c root.
	 */
	const RootValueType getRoot() const;

	/**
	 * @brief Sets the value of field named \c root.
	 */
	void setRoot( const RootValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c root.
	 *
	 * @return the name of field \c root.
	 */
	static const std::string getFRoot( void );

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
	OffscreenRendering( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , OffscreenRendering );
private:
	static const vgd::basic::RegisterNode<OffscreenRendering> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_OFFSCREENRENDERING_HPP
