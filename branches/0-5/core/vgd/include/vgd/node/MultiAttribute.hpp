// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_MULTIATTRIBUTE_HPP
#define _VGD_NODE_MULTIATTRIBUTE_HPP

#include "vgd/basic/toString.hpp"
#include "vgd/field/Integer.hpp"
#include "vgd/node/Attribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract class for all multi attribute classes.
 *
 * Zero, one or more instances of the same multi-attribute could be enable in the same time (like Light, ClipPlane...).
 * A multi-attribute is qualified by an zero-based index.
 * 
 * New field added by this node :
 * 
 * - SFInt8 \c multiAttributeIndex = 0\n
 * 	Zero-based index apply to this attribute. Default value for this field is zero.
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API MultiAttribute : public vgd::node::Attribute
{
	// META_NODE_HPP( MultiAttribute ); abstract class.



	/**
	 * @name Accessors to field multiAttributeIndex.
	 */
	//@{

	/**
	 * @brief Typedef for the \c multiAttributeIndex field.
	 */	
	typedef vgd::field::SFInt8 FMultiAttributeIndexType;
		
	/**
	 * @brief Typedef for the \c multiAttributeIndex value.
	 */
	typedef int8					MultiAttributeIndexValueType;

	/**
	 * @brief Gets the \c multiAttributeIndex of the multi-attribute.
	 */
	int8		getMultiAttributeIndex() const;

	/**
	 * @brief Sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index	zero-based index of the multi-attribute.
	 */
	void		setMultiAttributeIndex( const int8 index );
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c multiAttributeIndex.
	 * 
	 * @return the name of field \c multiAttributeIndex.
	 */
	static const std::string getFMultiAttributeIndex( void );
	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	MultiAttribute( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_MULTIATTRIBUTE_HPP
