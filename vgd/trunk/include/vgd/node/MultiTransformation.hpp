// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_MULTITRANSFORMATION_H
#define _VGD_NODE_MULTITRANSFORMATION_H

#include "vgd/vgd.hpp"

#include "vgd/field/Bool.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all texture transformation nodes.
 * 
 * New fields added by this node :
 *
 * - SFBool \c composeTransformation = true\n
 * 	Determines if composition with current transformation matrix is enable or disable.
 * 	Sets to true if composition of matrix is enabled, false if not.
 */
struct VGD_API MultiTransformation : public vgd::node::MultiAttribute
{
	//META_NODE_HPP( MultiTransformation ); abstract class.



	/**
	 * @name Accessors to field composeTransformation.
	 */
	//@{

	/**
	 * @brief Typedef for the \c composeTransformation field.
	 */	
	typedef vgd::field::SFBool	FComposeTransformationType;
		
	/**
	 * @brief Typedef for the \c composeTransformation value.
	 */
	typedef bool					ComposeTransformationValue;

	/**
	 * @brief Gets if composition with current matrix is enable or disable.
	 * 
	 * @return true if composition of matrix is enabled, false if not.
	 */
	const bool&		getComposeTransformation( void ) const;

	/**
	 * @brief Enable/Disable composition with current matrix.
	 * 
	 * @param bComposeTransformation	true if composition of matrix is enabled, false if not.
	 */
	void				setComposeTransformation( const bool bComposeTransformation );
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{

	/**
	 * @brief Returns the name of field \c composeTransformation.
	 */
	static const std::string getFComposeTransformation( void );
	
	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	MultiTransformation( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();
		
	//@}
};



} // namespace node

} // namespace vgd

#endif // #ifndef _VGD_NODE_MULTITRANSFORMATION_H
