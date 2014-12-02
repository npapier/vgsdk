// VGSDK - Copyright (C) 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/EngineProperties.hpp"

#include <vgd/node/EngineProperties.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"
#include <gle/OpenGLExtensionsGen.hpp>



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( EngineProperties );



const vge::service::List EngineProperties::getServices() const
{
	vge::service::List list;

	list.push_back( vge::service::Painter::create() );

	return list;
}



/*const Handler::TargetVector EngineProperties::getTargets() const
{
	TargetVector targets;

	targets.push_back( vgd::node::EngineProperties::getClassIndexStatic() );

	return targets;
}*/


void EngineProperties::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	// TEXTURE
	vge::handler::basic::EngineProperties::apply( engine, node );

	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::EngineProperties* >(node) != 0 );
	vgd::node::EngineProperties *engineProperties = dynamic_cast< vgd::node::EngineProperties* >(node);


	// Retrieves GLSL state
	using vgeGL::engine::GLSLState;
	GLSLState& state = glEngine->getGLSLState();


	// OPENGL API USAGE
	bool bValue;

	// OPENGL DEBUG OUTPUT
	const bool hasDebugOutput = engineProperties->getOpenglDebugOutput( bValue );
	if ( hasDebugOutput )
	{
		gleGetCurrent()->setDebugOutput( bValue ? gle::OpenGLExtensions::SYNCHRONOUS : gle::OpenGLExtensions::DISABLED );
	}

	// OPENGL DSA
	const bool hasDSA = engineProperties->getOpenglDirectStateAccess( bValue );
	if ( hasDSA )
	{
		glEngine->setDSAEnabled( bValue );
	}
}



void EngineProperties::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
}



void EngineProperties::setToDefaults()
{
	// nothing to do
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
