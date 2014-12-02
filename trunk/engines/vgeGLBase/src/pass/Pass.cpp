//// VGSDK - Copyright (C) 2007, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/pass/Pass.hpp"
//
//#include "vgeGL/engine/Engine.hpp"
//#include "vgeGL/technique/Technique.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace pass
//{
//
//
//
//void Pass::apply(	vge::technique::Technique * technique, vge::engine::Engine *engine, 
//					vge::visitor::TraverseElementVector* traverseElements,
//					vgd::Shp< vge::service::Service > service )
//{
//	// @todo remove this
//
//	vgeGL::technique::Technique *	castedTechnique	= dynamic_cast< vgeGL::technique::Technique * >( technique );
//	assert( castedTechnique != 0 );
//
//	vgeGL::engine::Engine *			castedEngine	= dynamic_cast< vgeGL::engine::Engine * >( engine );
//	assert( castedEngine != 0 );
//
//	apply( castedTechnique, castedEngine, traverseElements, service );
//}
//
//
//
//} // namespace pass
//
//} // namespace vgeGL
//