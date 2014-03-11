// VGSDK - Copyright (C) 2008, Clement Forest, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest
// Author Nicolas Papier

#include <vgd/transaction/node/Group.hpp>

#include <vgd/node/Group.hpp>
#include <vgd/transaction/function.hpp>


namespace vgd
{

namespace transaction
{

namespace node
{

Group::Group(vgd::Shp<vgd::node::IGroup> group){
	m_node=group;
}

void Group::apply(){
	vgd::Shp<vgd::node::IGroup> group = m_node.lock();
	if(group)
		TransactionContainer::apply();
}


void Group::addChild(vgd::Shp< vgd::node::Node > node){
	vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),&vgd::node::IGroup::addChild,node);
	add_transaction(trans);
}

void Group::insertChild (vgd::Shp< vgd::node::Node > node, const int newChildIndex){
	vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),&vgd::node::IGroup::insertChild,node,newChildIndex);
	add_transaction(trans);
}

void Group::replaceChild (vgd::Shp< vgd::node::Node > newChild, const int index){
	typedef void (vgd::node::IGroup::*fptr)(vgd::Shp<vgd::node::Node>,int);
	vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),(fptr)&vgd::node::IGroup::replaceChild,newChild,index);
	add_transaction(trans);		
}

void Group::replaceChild (vgd::Shp< vgd::node::Node > oldChild, vgd::Shp< vgd::node::Node > newChild){
	typedef void (vgd::node::IGroup::*fptr)(vgd::Shp<vgd::node::Node>,vgd::Shp<vgd::node::Node>);
	vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),(fptr)&vgd::node::IGroup::replaceChild,oldChild,newChild);
	add_transaction(trans);		
}

void Group::removeChild (const int childIndex){
	typedef void (vgd::node::IGroup::*fptr)(const int);
	vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),(fptr)&vgd::node::IGroup::removeChild,childIndex);
	add_transaction(trans);
}

void Group::removeChild (vgd::Shp< vgd::node::Node > childToRemove){
	typedef bool (vgd::node::IGroup::*fptr)(vgd::Shp< vgd::node::Node >);
	vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),(fptr)&vgd::node::IGroup::removeChild,childToRemove);
	add_transaction(trans);
}

void Group::removeAllChildren (void){
	vgd::Shp<Transaction> trans = createFunctionTransaction(m_node.lock().get(),&vgd::node::IGroup::removeAllChildren);
	add_transaction(trans);
}


} } } // namespace node transaction vgd
