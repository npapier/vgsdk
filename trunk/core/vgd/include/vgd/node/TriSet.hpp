// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TRISET_HPP
#define _VGD_NODE_TRISET_HPP

#include "vgd/node/VertexShape.hpp"


namespace vgd
{

namespace node
{


/**
 * @brief Shape composed by triangles with neighbours informations
 * 
 * This node is composed only by triangles.
 * Neighbours informations could be founded in vgAlg::MeshBase and vgAlg::MeshTopology
 * 
 * New field added by this node :
 * 
 * - MFInt32 \c [neighbours] = empty\n
 * 		Arrays that defined the neighbours.
 * 
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 * @ingroup g_texturingNodes
 */
struct VGD_API TriSet : public vgd::node::VertexShape
{
	META_NODE_HPP( TriSet );



	/**
	 * @name Accessors to field neighbours
	 */
	//@{

	/**
	 * @brief Enumeration of the \c neighbours parameter.
	 */
	typedef enum
	{
		NEIGHBOURS = 1
	} NeighboursParameterType;

	/**
	 * @brief Typedef for the \c neighbours parameter value.
	 */
	typedef int32 NeighboursValueType;

	/**
	 * @brief Typedef for the \c neighbours field.
	 */	
	typedef vgd::field::TPairAssociativeField< NeighboursParameterType, NeighboursValueType > FNeighboursType;

	/**
	 * @brief Gets the \c neighbours value.
	 */
	bool			getNeighbours( NeighboursValueType& value ) const;

	/**
	 * @brief Sets the \c neighbours value.
	 */
	void 			setNeighbours( NeighboursValueType value );
	
	/**
	 * @brief Erase the \c neighbours value.
	 */
	void 			eraseNeighbours();
	//@}



	/**
	 * @name Fields names enumeration
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c neighbours.
	 * 
	 * @return the name of field \c neighbours.
	 */
	static const std::string getFNeighbours();
	//@}
	
	
	
	/**
	 * @name Dirty flags enumeration
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when neighbours must be recomputed.
	 */
	static const std::string getDFNeighbours();
	//@}
	
	
	
protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	TriSet( const std::string nodeName );

	void	setToDefaults();

	void	setOptionalsToDefaults();

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TRISET_HPP
