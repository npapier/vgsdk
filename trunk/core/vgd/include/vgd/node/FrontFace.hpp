// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_FRONTFACE_HPP
#define _VGD_NODE_FRONTFACE_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Front face polygons definition node
 *
 * The FrontFace node specifies if polygons are in clockwise winding in window coordinates, or counterclockwise winding in window coordinates, are taken to be front-facing.
 *
 * New fields defined by this node :
 * - SFEnum \c orientation = CCW

 * 	Specifies if front facing polygons are clockwise (CW) or conterclockwise (CCW)
 *
 * Inherited fields :
 * @todo generates this section
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API FrontFace : public vgd::node::SingleAttribute
{
	META_NODE_HPP( FrontFace );



	/**
	 * @name Accessors to field \c orientation
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c orientation.
	 */
	typedef enum
	{
		CCW = 256,	///< (C)ounter-(C)lock(W)ise ordering
		CW = 257,	///< (C)lock(W)ise ordering
		DEFAULT_ORIENTATION = CCW	///< (C)ounter-(C)lock(W)ise ordering
	} OrientationValueType;

	/**
	 * @brief Type definition of the field named \c orientation
	 */
	typedef vgd::field::TSingleField< OrientationValueType > FOrientationType;

	/**
	 * @brief Gets the value of field named \c orientation.
	 */
	const OrientationValueType getOrientation() const;

	/**
	 * @brief Sets the value of field named \c orientation.
	 */
	void setOrientation( const OrientationValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c orientation.
	 * 
	 * @return the name of field \c orientation.
	 */
	static const std::string getFOrientation( void );

	//@}



	/**
	 * @name Constructor and initializer methods
	 */
	//@{

protected:
	/**
	 * @brief Default constructor
	 */
	FrontFace( const std::string nodeName );

public:
	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_FRONTFACE_HPP
