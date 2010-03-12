// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_POINTSTYLE_HPP
#define _VGD_NODE_POINTSTYLE_HPP

#include "vgd/field/Float.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Defines the style to use when rendering points
 *
 * 
 *
 * New fields defined by this node :
 * - OFFloat \c [size] = 1.f<br>
 *   Specifies the rasterized diameter of both aliased and antialiased points<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API PointStyle : public vgd::node::SingleAttribute
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
	static vgd::Shp< PointStyle > create( const std::string nodeName = "NoName" );

	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< PointStyle > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field size
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c size.
	 */
	typedef float SizeValueType;

	/**
	 * @brief Type definition of the field named \c size
	 */
	typedef vgd::field::TOptionalField< SizeValueType > FSizeType;


	/**
	 * @brief Gets the value of field named \c size.
	 */
	const bool getSize( SizeValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c size.
 	 */
	void setSize( const SizeValueType& value );

	/**
	 * @brief Erases the field named \c size.
	 */
	void eraseSize();

	/**
	 * @brief Tests if the value of field named \c size has been initialized.
	 */
	const bool hasSize() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c size.
	 *
	 * @return the name of field \c size.
	 */
	static const std::string getFSize( void );

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
	PointStyle( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , PointStyle );
private:
	static const vgd::basic::RegisterNode<PointStyle> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_POINTSTYLE_HPP
