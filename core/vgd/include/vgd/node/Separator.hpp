// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SEPARATOR_HPP
#define _VGD_NODE_SEPARATOR_HPP

#include "vgd/vgd.hpp"

#include "vgd/node/Group.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Group node that saves and restores traversal state.
 * 
 * This group node performs a push (save) of the traversal state before traversing its children and a pop (restore) 
 * after traversing them. This isolates the separator's children from the rest of the scene graph.\n
 * Separators are relatively inexpensive, so they can be used freely within scenes.
 *
 * @remarks Don't use more than 12 nested Separators (OpenGL is limited to 16 and internally up to 4 are used).
 * @remarks Transformations (projection, geometrical and texture) are NOT saved and restored by this 
 * node (TransformSeparator).
 * 
 * @todo A mask that indicates which attributes to save.
 * 
 * @ingroup g_nodes
 * @ingroup g_groupNodes
 */
struct VGD_API Separator : public vgd::node::Group
{
	META_NODE_HPP( Separator );



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Separator( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();
	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_SEPARATOR_HPP
