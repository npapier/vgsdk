// VGSDK - Copyright (C) 2008, Clement Forest, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest
// Author Nicolas Papier

#ifndef _VGD_TRANSACTION_NODE_GROUP_HPP
#define _VGD_TRANSACTION_NODE_GROUP_HPP

#include <vgd/transaction/TransactionContainer.hpp>
#include <vgd/Shp.hpp>
#include <vgd/WeakPtr.hpp>

namespace vgd
{
	namespace node
	{
		struct IGroup;
		struct Group;
		struct Node;
	} // namespace node
} // namespace vgd



namespace vgd
{

namespace transaction
{

namespace node
{

/**
 * @brief Class for transactional Groups.
 */
struct VGD_API Group : public TransactionContainer 
{
	/**
	 * @brief Creator.
	 */
	Group(vgd::Shp< vgd::node::IGroup > group);

	/**
	 * @brief Adds a child as last one in group.
	 */
	void addChild (vgd::Shp< vgd::node::Node > node);

	/** @brief Adds a child so that it becomes the one with the given index.
	 */
	void insertChild (vgd::Shp< vgd::node::Node > node, const int newChildIndex=0);

	/**
	 * @brief Replaces child with given index with new child.
	 */
	void replaceChild (vgd::Shp< vgd::node::Node > newChild, const int index);

	/**
	 * @brief Replaces child with another one.
	 */
	void replaceChild (vgd::Shp< vgd::node::Node > oldChild, vgd::Shp< vgd::node::Node > newChild);

 	/**
	 *@brief Removes child with given index from group.
	 */
	void removeChild (const int childIndex);

 	/**
	 * @brief Removes child.
	 */
	void removeChild (vgd::Shp< vgd::node::Node > childToRemove);

 	/**
	 * @brief Removes all child from group.
	 */
	void removeAllChildren (void);

	/**
	 * @brief The apply function.
	 *
	 * Conditionate the application of the transaction to the validity
	 * of the WeakPtr.
	 */
	void apply();

protected:
	/**
	 * @brief The node.
	 */
	vgd::WeakPtr< vgd::node::IGroup > m_node;
};


} } } // namespace vgd transaction node


#endif // _VGD_TRANSACTION_NODE_GROUP_HPP
