// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/MultipleInstances.hpp"

#include <vgd/node/MultipleInstances.hpp>
#include <vgDebug/convenience.hpp>
#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( MultipleInstances );



const vge::handler::Handler::TargetVector MultipleInstances::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::MultipleInstances::getClassIndexStatic() );

	return targets;
}



void MultipleInstances::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::MultipleInstances* >(node) != 0 );
	vgd::node::MultipleInstances *pCastedNode = static_cast< vgd::node::MultipleInstances* >(node);

	//vgeGL::rc::applyUsingDisplayList< vgd::node::MultipleInstances, MultipleInstances >( engine, node, this );
	paint( pGLEngine, pCastedNode );
}



void MultipleInstances::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void MultipleInstances::setToDefaults()
{
}



void MultipleInstances::paint( vgeGL::engine::Engine * engine, vgd::node::MultipleInstances * multipleInstances )
{
	// SHAPE
	const vgd::Shp< vgd::node::Shape > shape = vgd::dynamic_pointer_cast< vgd::node::Shape >( multipleInstances->getShape() );

	// MATRIX
	using vgd::field::EditorRO;
	typedef vgd::node::MultipleInstances::FMatrixType FMatrixType;

	EditorRO< FMatrixType > matrix = multipleInstances->getMatrixRO();

	// Gets the geometrical matrix transformation.
	const vgm::MatrixR backup( engine->getGeometricalMatrix().getTop() );
	vgm::MatrixR current;

	//
	for(	FMatrixType::const_iterator	i		= matrix->begin(),
										iEnd	= matrix->end();
			i != iEnd;
			++i	)
	{
		// Updates geometrical transformation
		const vgm::MatrixR& iMatrix = *i;
		current = iMatrix * backup;

		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixf( reinterpret_cast<float*>( current.getValue() ) );

		engine->paint( shape );
	}

	//
	glMatrixMode( GL_MODELVIEW );
	glLoadMatrixf( reinterpret_cast<const float*>( backup.getValue() ) );

	// Validates node df
	multipleInstances->getDirtyFlag(multipleInstances->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
