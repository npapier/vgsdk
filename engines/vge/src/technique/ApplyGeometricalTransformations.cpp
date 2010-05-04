// VGSDK - Copyright (C) 2004, 2007, 2008, 2010, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Maxime Peresson

#include "vge/technique/ApplyGeometricalTransformations.hpp"

#include "vge/pass/ForEach.hpp"
#include "vge/service/Basic.hpp"
#include "vge/engine/Engine.hpp"

#include <vgd/node/VertexShape.hpp>
#include <vgd/node/Transform.hpp>
#include <vgd/node/MatrixTransform.hpp>



namespace vge
{

namespace technique
{



void ApplyGeometricalTransformations::apply( vge::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	vgd::Shp< vge::service::Service > service = vge::service::Basic::create();

	std::vector< vgd::Shp< vgd::node::GeometricalTransformation > >* transformList = new std::vector< vgd::Shp< vgd::node::GeometricalTransformation > >();

	prepareEval( engine, traverseElements );

	assert( service != 0 );
	assert( engine != 0 );

	beginPass( PassIsolationMask(0) );

	//assert( m_engine != 0 );
	assert( getTraverseElements() != 0 );

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		if ( i->first->isAKindOf< vgd::node::VertexShape >() && i->second )
		{
			vgd::node::VertexShape * node = dynamic_cast< vgd::node::VertexShape * >( i->first );

			vgm::MatrixR&	current( engine->getGeometricalMatrix().getTop() );

			node->transform( current );
		}
		else if ( ( i->first->isAKindOf< vgd::node::Transform >() || i->first->isAKindOf< vgd::node::MatrixTransform >() ) && i->second )
		{
			vgd::Shp< vgd::node::GeometricalTransformation > transform = vgd::makeShp< vgd::node::GeometricalTransformation>( dynamic_cast< vgd::node::GeometricalTransformation * >( i->first ) );

			transformList->push_back( transform );
		}

		engine->evaluate( service, i->first, i->second );
	}

	endPass();

	// @todo comments
	std::vector< vgd::Shp< vgd::node::GeometricalTransformation > >::iterator it = transformList->begin();
	for( it; it != transformList->end(); it++ )
	{
		vgd::node::NodeList parents;
		(*it)->getParents( parents );

		std::list< vgd::Shp< vgd::node::Node > >::iterator iter = parents.begin();
		for( iter; iter != parents.end(); iter++ )
		{
			vgd::Shp< vgd::node::Group > parent = vgd::dynamic_pointer_cast< vgd::node::Group >( (*iter) );
			parent->removeChild( *it );
		}
	}

	finishEval();
}



} // namespace technique

} // namespace vge
