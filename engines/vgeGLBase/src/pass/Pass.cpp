//// VGSDK - Copyright (C) 2007, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/pass/Pass.hpp"
//
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/technique/Technique.hpp"
//
//
//
//namespace vgeGLBase
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
//	vgeGLBase::technique::Technique *	castedTechnique	= dynamic_cast< vgeGLBase::technique::Technique * >( technique );
//	assert( castedTechnique != 0 );
//
//	vgeGLBase::engine::Engine *			castedEngine	= dynamic_cast< vgeGLBase::engine::Engine * >( engine );
//	assert( castedEngine != 0 );
//
//	apply( castedTechnique, castedEngine, traverseElements, service );
//}
//
//
//
//} // namespace pass
//
//} // namespace vgeGLBase
//