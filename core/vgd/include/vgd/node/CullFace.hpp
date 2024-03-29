// VGSDK - Copyright (C) 2014, Nicolas Papier.
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
 * - SFEnum \c mode = (DISABLED)<br>
 *   Specifies whether front-facing and/or back-facing facets can be culled.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API CullFace : public vgd::node::SingleAttribute
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
	static vgd::Shp< CullFace > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< CullFace > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< CullFace > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field mode
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		DISABLED = 267,	///< Facet culling is disabled
		FRONT = 269,	///< Front-facing facets are culled
		BACK = 268,	///< Back-facing facets are culled
		FRONT_AND_BACK = 270,	///< Front-facing and back-facing facets are culled
		DEFAULT_MODE = DISABLED	///< Facet culling is disabled
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ModeValueType : public vgd::field::Enum
	{
		ModeValueType()
		{}

		ModeValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ModeValueType( const ModeValueType& o )
		: vgd::field::Enum(o)
		{}

		ModeValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 267 );
			retVal.push_back( 268 );
			retVal.push_back( 269 );
			retVal.push_back( 270 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "DISABLED" );
			retVal.push_back( "BACK" );
			retVal.push_back( "FRONT" );
			retVal.push_back( "FRONT_AND_BACK" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c mode
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FModeType;


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
	CullFace( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( CullFace );
private:
	static const vgd::basic::RegisterNode<CullFace> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_CULLFACE_HPP
