// VGSDK - Copyright (C) 2008, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Program.hpp"

#include <vgd/node/Program.hpp>
#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/engine/Engine.hpp"
//#include "vgeGL/rc/GLSLProgram.hpp"
//#include "vgeGL/rc/TSyncAndBindHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Program );



const vge::handler::Handler::TargetVector Program::getTargets() const
{
	TargetVector targets;

	targets.push_back( vgd::node::Program::getClassIndexStatic() );

	return targets;
}



void Program::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::Program* >(node) != 0 );
	vgd::node::Program *castedNode = static_cast< vgd::node::Program* >(node);

	// Retrieves GLSL state
	using vgeGL::engine::GLSLState;
	GLSLState& state = glEngine->getGLSLState();

	state.setEnabled( GLSLState::PROGRAM );
	state.setProgram( castedNode );

	// Validates node
	node->getDirtyFlag(node->getDFNode())->validate();

/* This code installs immediately the program.
	using vgeGL::rc::applyUsingSyncAndBind;
	applyUsingSyncAndBind< vgd::node::Program, vgeGL::handler::painter::Program, vgeGL::rc::GLSLProgram >( 
			glEngine, castedNode, this );*/

	// Validates node
	// assert( node->getDirtyFlag(node->getDFNode())->isValid() && "Node dirty flag not validated." ); not always true
}



void Program::unapply( vge::engine::Engine * /*engine*/, vgd::node::Node * /*node*/ )
{
}



void Program::setToDefaults()
{
	//glo::GLSLProgram::useFixedPaths();
}



void Program::bind( vgeGL::engine::Engine * /*engine*/, vgd::node::Program * /*node*/, vgeGL::rc::GLSLProgram * /*resource*/ )
{
	/*assert( resource != 0 );
	// assert( !resource->isEmpty() );

	resource->use();*/
}



void Program::synchronize( vgeGL::engine::Engine * /*engine*/, vgd::node::Program * /*node*/, vgeGL::rc::GLSLProgram * /*resource*/ )
{/*
	bool defined;
	vgd::node::Program::ShaderValueType value;

	// @todo Clears the resource

	// VERTEX
	defined = node->getShader( vgd::node::Program::VERTEX, value );

	if ( defined )
	{
		resource->addShader( value.c_str(), glo::GLSLProgram::VERTEX, false );
	}

	// FRAGMENT
	defined = node->getShader( vgd::node::Program::FRAGMENT, value );

	if ( defined )
	{
		resource->addShader( value.c_str(), glo::GLSLProgram::FRAGMENT, false );
	}

	// GEOMETRY
	defined = node->getShader( vgd::node::Program::GEOMETRY, value );

	if ( defined )
	{
		resource->addShader( value.c_str(), glo::GLSLProgram::GEOMETRY, false );
	}

	// Link stage
	const bool retVal = resource->link();

	if ( retVal )
	{
		// Validates node dirty flag
		vgd::field::DirtyFlag * nodeDF = node->getDirtyFlag( node->getDFNode() );
		nodeDF->validate();
	}
	// else nothing to do. Don't validate df.*/
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
