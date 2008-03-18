#include <vgd/transaction/Group.hpp>

#include <vgd/node/Group.hpp>
#include <vgd/transaction/function.hpp>


namespace vgd
{
namespace transaction
{

	Group::Group(vgd::Shp<node::IGroup> group){
		m_node=group;
	}

	void Group::apply(){
		vgd::Shp<node::IGroup> group = m_node.lock();
		if(group)
			TransactionContainer::apply();
	}


	void Group::addChild(vgd::Shp< node::Node > node){
		vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),&node::IGroup::addChild,node);
		add_transaction(trans);
	}

	void Group::insertChild (vgd::Shp< node::Node > node, const int32 newChildIndex){
		vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),&node::IGroup::insertChild,node,newChildIndex);
		add_transaction(trans);
	}

	void Group::replaceChild (vgd::Shp< node::Node > newChild, const int32 index){
		typedef void (vgd::node::IGroup::*fptr)(vgd::Shp<vgd::node::Node>,int32);
		vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),(fptr)&node::IGroup::replaceChild,newChild,index);
		add_transaction(trans);		
	}

	void Group::replaceChild (vgd::Shp< node::Node > oldChild, vgd::Shp< node::Node > newChild){
		typedef void (vgd::node::IGroup::*fptr)(vgd::Shp<vgd::node::Node>,vgd::Shp<vgd::node::Node>);
		vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),(fptr)&node::IGroup::replaceChild,oldChild,newChild);
		add_transaction(trans);		
	}

	void Group::removeChild (const int32 childIndex){
		typedef void (vgd::node::IGroup::*fptr)(const int32);
		vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),(fptr)&node::IGroup::removeChild,childIndex);
		add_transaction(trans);
	}

	void Group::removeChild (vgd::Shp< node::Node > childToRemove){
		typedef bool (vgd::node::IGroup::*fptr)(vgd::Shp< node::Node >);
		vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),(fptr)&node::IGroup::removeChild,childToRemove);
		add_transaction(trans);
	}

	void Group::removeAllChildren (void){
		vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),&node::IGroup::removeAllChildren);
		add_transaction(trans);
	}


} // namespace transaction
} // namespace vgd
