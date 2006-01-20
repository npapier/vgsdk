// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_FRONTFACE_H
#define _VGD_NODE_FRONTFACE_H

#include "vgd/vgd.hpp"

#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Front face polygons definition node
 * 
 * The FrontFace node specifies if polygons are in clockwise winding in window coordinates, or counterclockwise winding 
 * in window coordinates, are taken to be front-facing.
 * 
 * New field added by this node :
 * 
 * - PAFBool \c [orientation] = CCW\n
 * 	 Specifies if front facing polygons are clockwise (CW) or conterclockwise (CCW).
 * 
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API FrontFace : public vgd::node::SingleAttribute
{
	META_NODE_HPP( FrontFace );



	/**
	 * @name Accessors to field orientation.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c orientation parameter.
	 */
	typedef enum
	{
		ORIENTATION = 1
	} OrientationParameterType;

	/**
	 * @brief Typedef for the \c orientation parameter value.
	 */
	typedef enum
	{
		CCW = 1,
		CW,
		DEFAULT_ORIENTATION = CCW
	} OrientationValueType;

	/**
	 * @brief Typedef for the \c orientation field.
	 */	
	typedef vgd::field::TPairAssociativeField< OrientationParameterType, OrientationValueType > FOrientationType;

	/**
	 * @brief Gets the \c orientation value.
	 */
	bool			getOrientation( OrientationValueType& value ) const;

	/**
	 * @brief Sets the \c orientation value.
	 */
	void 			setOrientation( OrientationValueType value );
	
	/**
	 * @brief Erase the \c orientation value.
	 */
	void 			eraseOrientation();
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c orientation.
	 * 
	 * @return the name of field \c orientation.
	 */
	static const std::string getFOrientation( void );
	//@}

	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 * 
	 * @internal Add field, dirty flags and link in the constructor.
	 */
	FrontFace( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();
	
	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_FRONTFACE_H
