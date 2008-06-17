// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CULLFACE_HPP
#define _VGD_NODE_CULLFACE_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Cull face facets definition node
 *
 * The CullFace node specifies whether front-facing and/or back-facing facets can be culled. Facets include triangles, quadrilaterals, polygons and rectangles. FrontFace node specifies which of the clockwise and counterclockwise facets are front-facing and back-facing. See vgd::node::FrontFace.
 *
 * New fields defined by this node :
 * - SFEnum \c mode = DISABLED

 * 	Specifies whether front-facing and/or back-facing facets can be culled.
 *
 * Inherited fields :
 * @todo generates this section
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API CullFace : public vgd::node::SingleAttribute
{
	META_NODE_HPP( CullFace );



	/**
	 * @name Accessors to field \c mode
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c mode.
	 */
	typedef enum
	{
		DISABLED = 258,	///< Facet culling is disabled
		FRONT = 260,	///< Front-facing facets are culled
		BACK = 259,	///< Back-facing facets are culled
		FRONT_AND_BACK = 261,	///< Front-facing and back-facing facets are culled
		DEFAULT_MODE = DISABLED	///< Facet culling is disabled
	} ModeValueType;

	/**
	 * @brief Type definition of the field named \c mode
	 */
	typedef vgd::field::TSingleField< ModeValueType > FModeType;

	/**
	 * @brief Gets the value of field named \c mode.
	 */
	const ModeValueType getMode() const;

	/**
	 * @brief Sets the value of field named \c mode.
	 */
	void setMode( const ModeValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c mode.
	 * 
	 * @return the name of field \c mode.
	 */
	static const std::string getFMode( void );

	//@}



	/**
	 * @name Constructor and initializer methods
	 */
	//@{

protected:
	/**
	 * @brief Default constructor
	 */
	CullFace( const std::string nodeName );

public:
	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_CULLFACE_HPP
