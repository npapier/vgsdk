#ifndef _VGD_TRANSACTION_GROUP_HPP
#define _VGD_TRANSACTION_GROUP_HPP

#include <vgd/vgd.hpp>
#include <vgd/transaction/TransactionContainer.hpp>
#include <vgd/WeakPtr.hpp>
#include <vgd/Shp.hpp>

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

	template <typename T> struct TBind;
	struct Group;


/**
 * @brief Class for the correspondancy between
 * transactional and non-transactional node.
 *
 * Specialization for TMultiField.
 */

template <> struct TBind<node::Group> {
	typedef Group TRANSACTION;
};


/**
 * @brief Class for transactional Groups.
 */
struct VGD_API Group : public TransactionContainer {
	/**
	 * @brief Creator.
	 */
	Group(vgd::Shp<node::IGroup> group);
	/**
	 * @brief Adds a child as last one in group.
	 */
	void addChild (vgd::Shp< node::Node > node);
	/** @brief Adds a child so that it becomes the one with the given index.
	 */
	void insertChild (vgd::Shp< node::Node > node, const int32 newChildIndex=0);
	/**
	 * @brief Replaces child with given index with new child.
	 */
	void replaceChild (vgd::Shp< node::Node > newChild, const int32 index);
 	/**
	 * @brief Replaces child with another one.
	 */
	void replaceChild (vgd::Shp< node::Node > oldChild, vgd::Shp< node::Node > newChild);
 	/**
	 *@brief Removes child with given index from group.
	 */
	void removeChild (const int32 childIndex);
 	/**
	 * @brief Removes child.
	 */
	void removeChild (vgd::Shp< node::Node > childToRemove);
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
	vgd::WeakPtr<node::IGroup> m_node;
};


} } // namespace vgd transaction


#endif // _VGD_TRANSACTION_GROUP_HPP
