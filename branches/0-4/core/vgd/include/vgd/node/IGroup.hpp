// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_IGROUP_HPP
#define _VGD_NODE_IGROUP_HPP

#include <list>
#include "vgd/Shp.hpp"
#include "vgd/node/Node.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Interface of Group nodes.
 * 
 * IGroup is a node that contains an ordered list of child nodes. For more details see vgd::node::Group.
 * 
 * @remarks In Group class and derived, when a child node is inserted or removed, all indices after this one are 
 * invalidated. Be careful.
 * 
 * @todo swapChild()
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API IGroup
{
	/**
	 * @brief Virtual destructor
	 */
	virtual ~IGroup();

	/**
	 * @name Insert/remove/replace accessor methods
	 */
	//@{

	/**
	 * @brief Adds a child as last one in group.
	 */
	virtual void	addChild	( vgd::Shp<Node> node )=0;

	/**
	 * @brief Adds a child so that it becomes the one with the given index.
	 */
	virtual void	insertChild	( vgd::Shp<Node> node, const int newChildIndex = 0 )=0;

	/**
	 * @brief Replaces child with given index with new child.
	 * 
	 * @pre newChildIndex>=0 and newChildIndex<=getNumChildren()
	 */
	virtual void	replaceChild( vgd::Shp<Node> newChild, const int index )=0;

	/**
	 * @brief Replaces child with another one.
	 */
	virtual void 	replaceChild( vgd::Shp<Node> oldChild, vgd::Shp<Node> newChild )=0;

	/**
	 * @brief Removes child with given index from group.
	 */
	virtual void	removeChild	( const int childIndex )=0;

	/**
	 * @brief Removes child.
	 * 
	 * @return true if sucessuful, false otherwise.
	 */
	virtual bool	removeChild	( vgd::Shp<Node> childToRemove )=0;

	/**
	 * @brief Removes all child from group.
	 */
	virtual void	removeAllChildren( void )=0;
	//@}



	/**
	 * @name Searching methods
	 */
	//@{
	
	/**
	 * @brief Find if a node is contained within Group.
	 * 
	 * @return true if node is contained within Group.
	 */
	virtual bool	containsChild( const vgd::Shp<Node> node ) const=0;

	/**
	 * @brief Finds index of given child within group.
	 * 
	 * @return a value between 0 and getNumChildren()-1 if found, if not found then return getNumChildren()
	 */
	virtual int	findChild( const vgd::Shp<Node> node ) const=0;
	//@}



	/**
	 * @name Child accessor
	 */
	//@{

	/**
	 * @brief Returns pointer to child node with the given index.
	 */
	virtual vgd::Shp<Node>	getAbstractChild( const int index )=0;

	/**
	 * @brief Returns children.
	 * 
	 * @param children	append children at the end of this list.
	 */
	virtual void			getChildren( NodeList& children ) const=0;

	/**
	 * @brief Returns number of children.
	 */
	virtual int				getNumChildren( void ) const=0;

	/**
	 * @brief Returns only enabled or disabled children.
	 * 
	 * @param children		append children at the end of this list.
 	 * @param bGetEnabled	true to get all enabled children, false to get all disabled children.
 	 * 
 	 * @remark An enabled child is a child that is mark to be traversed (all for Group, all or one or none for
 	 * Switch). An disabled children is a child that is mark to be not traversed.
	 */
	virtual void			getEnabledChildren( NodeList& children, const bool bGetEnabled = true) const=0;
	//@}


protected:
	/**
	 * @internal Updates bgl graph to reflect modifications in the children list and in the children selection list.
	 * 
	 * @remarks At the end of this method, you should validate some dirty flag.
	 */
	virtual void	updateGraph( void )=0;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_IGROUP_HPP
