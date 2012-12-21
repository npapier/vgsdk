// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/basic/EngineProperties.hpp"

#include <vgd/node/EngineProperties.hpp>
#include "vge/engine/Engine.hpp"
#include <vge/service/Painter.hpp>



namespace vge
{

namespace handler
{

namespace basic
{



META_HANDLER_CPP( EngineProperties );



const vge::service::List EngineProperties::getServices() const
{
	vge::service::List list;

	//list.push_back( vge::service::Painter::create()				);

	return list;
}



const Handler::TargetVector EngineProperties::getTargets() const
{
	TargetVector targets;

	targets.push_back( vgd::node::EngineProperties::getClassIndexStatic() );

	return targets;
}


void EngineProperties::apply( vge::engine::Engine *engine, vgd::node::Node *node )
{
	assert( dynamic_cast< vgd::node::EngineProperties* >(node) != 0 );
	vgd::node::EngineProperties *engineProperties = dynamic_cast< vgd::node::EngineProperties* >(node);

	bool isDefined;
	float value;

	// MAXANISOTROPY
	isDefined = engineProperties->getMaxAnisotropy( value );

	if ( isDefined )
	{
		engine->setDefaultMaxAnisotropy( value );
	}
}



void EngineProperties::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
}



void EngineProperties::setToDefaults()
{
}



} // namespace basic

} // namespace handler

} // namespace vge
