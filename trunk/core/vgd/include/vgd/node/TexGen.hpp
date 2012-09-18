// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXGEN_HPP
#define _VGD_NODE_TEXGEN_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract node to control the generation of texture coordinates S, T, R and Q.
 *
 * 
 *
 * New fields defined by this node :
 * - SFBool \c on = (true)<br>
 *   Specifies if the texture generation is enabled or disabled.<br>
 *<br>
 *
 * @ingroup g_abstractNodes
 */
struct VGD_API TexGen : public vgd::node::MultiAttribute
{



	/**
	 * @name Accessors to field on
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c on.
	 */
	typedef bool OnValueType;

	/**
	 * @brief The default value of field named \c on.
	 */
	static const OnValueType DEFAULT_ON;

	/**
	 * @brief Type definition of the field named \c on
	 */
	typedef vgd::field::TSingleField< OnValueType > FOnType;


	/**
	 * @brief Gets the value of field named \c on.
	 */
	const OnValueType getOn() const;

	/**
	 * @brief Sets the value of field named \c on.
	 */
	void setOn( const OnValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c on.
	 *
	 * @return the name of field \c on.
	 */
	static const std::string getFOn( void );

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
	TexGen( const std::string nodeName );

};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXGEN_HPP
