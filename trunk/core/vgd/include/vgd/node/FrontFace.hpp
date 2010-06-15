// VGSDK - Copyright (C) 2010, Nicolas Papier.
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
 * - SFEnum \c orientation = CCW<br>
 *   Specifies if front facing polygons are clockwise (CW) or conterclockwise (CCW)<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API FrontFace : public vgd::node::SingleAttribute
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
	static vgd::Shp< FrontFace > create( const std::string nodeName = "NoName" );

	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< FrontFace > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field orientation
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		CCW = 260,	///< (C)ounter-(C)lock(W)ise ordering
		CW = 261,	///< (C)lock(W)ise ordering
		DEFAULT_ORIENTATION = CCW	///< (C)ounter-(C)lock(W)ise ordering
	};

	/**
	 * @brief Type definition of the value contained by field named \c orientation.
	 */
	struct OrientationValueType : public vgd::field::Enum
	{
		OrientationValueType()
		{}

		OrientationValueType( const int v )
		: vgd::field::Enum(v)
		{}

		OrientationValueType( const OrientationValueType& o )
		: vgd::field::Enum(o)
		{}

		OrientationValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 260 );
			retVal.push_back( 261 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "CCW" );
			retVal.push_back( "CW" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c orientation
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FOrientationType;


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
	FrontFace( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , FrontFace );
private:
	static const vgd::basic::RegisterNode<FrontFace> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_FRONTFACE_HPP
