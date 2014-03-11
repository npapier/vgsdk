// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_KIT_HPP
#define _VGD_NODE_KIT_HPP

#include "vgd/field/NodeShp.hpp"
#include "vgd/field/TSingleField.hpp"
#include "vgd/node/Group.hpp"



namespace vgd
{

namespace node
{

struct Group;

/**
 * @brief Abstract base class for all node kits.
 * 
 * A kit encapsulate a scene graph. It could be very useful to simplify the view of whole scene graph for the 
 * developer by hiding some parts of the scene graph and providing to the developer higher level nodes.
 * 
 * New field added by this node :
 * 
 * - SFNode \c root = vgd::Shp<vgd::node::Group>(0)\n
 * 	A kit contains a scene graph. This field sets the root node of this scene graph. It's type must be a 
 * 	vgd::node::Group or a class derived from Group.
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API Kit : public Node, public IBoundingBox
{
	/**
	 * @name Bounding box.
	 */
	//@{

	/**
	 * @remarks getRoot() scene graph must already have compute all its bounding boxes before calling this method.
	 */
	bool computeBoundingBox( const vgm::MatrixR& transformation /* not used */ );

	bool isBoundingBoxValid() const;

	void invalidateBoundingBox( bool bInvalidate = true );
	//@}



	/**
	 * @name Accessors to field root.
	 */
	//@{

	/**
	 * @brief Typedef for the \c root field.
	 */
	typedef vgd::field::TSingleField< vgd::Shp<vgd::node::Group> >		FRootType;
		
	/**
	 * @brief Typedef for the \c root value.
	 */
	typedef vgd::Shp< vgd::node::Group >								RootValueType;
	
	/**
	 * @brief Gets the root of node.
	 * 
	 * @todo Not really read-only ? same bug in others nodes ?
	 */
	const RootValueType		getRoot() const;
protected:
	/**
	 * @brief Sets the root of node.
	 * 
	 */
	void							setRoot( const RootValueType value );
public:

	//@}



	/**
	 * @name Dirty flags enumeration.
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when bounding box is invalidate and must be recomputed.
	 */
	static const std::string getDFBoundingBox();
	
	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Kit( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();
	
	//@}
	
	

	/**
	 * @name Fields names enumeration.
	 */
	//@{

	/**
	 * @brief Returns the name of field \c root.
	 * 
	 * @return the name of field \c root.
	 */
	static const std::string getFRoot();
	
	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_KIT_HPP
