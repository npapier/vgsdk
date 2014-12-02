//// VGSDK - Copyright (C) 2004, 2007, 2008, 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/technique/Main.hpp"
//
//#include <vge/pass/ForEach.hpp>
//#include <vge/service/Painter.hpp>
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/pass/Opaque.hpp"
//#include "vgeGLBase/pass/Transparent.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace technique
//{
//
//
//
//void Main::apply( vgeGLBase::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
//{
//	//
//	vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();
//
//	prepareEval( engine, traverseElements );
//
//	// First pass : OPAQUE PASS (draw opaque shape)
//	const bool mustDoTransparencyPass = evaluateOpaquePass( paint );
//
//	// Second pass : TRANSPARENT PASS (draw transparent shape).
//	if ( mustDoTransparencyPass )
//	{
//		evaluateTransparentPass( paint );
//	}
//
//	//
//	finishEval();
//}
//
//
//
//const bool Main::evaluateOpaquePass( vgd::Shp< vge::service::Service > service, const PassIsolationMask isolationMask, const bool nestedPass )
//{
//	// At startup, the transparent pass is disabled. It would be enabled during the opaque pass if at least one
//	// transparent shape is encountered.
//
//	using ::vgeGLBase::pass::Opaque;
//	vgd::Shp< Opaque > opaque( new Opaque() );
//
//	evaluatePass( opaque, service, isolationMask, nestedPass );
//
//	return opaque->mustDoTransparencyPass();
//}
//
//
//
//void Main::evaluateTransparentPass( vgd::Shp< vge::service::Service > service, const PassIsolationMask isolationMask, const bool nestedPass )
//{
//	using ::vgeGLBase::pass::Transparent;
//
//	evaluatePass( vgd::makeShp( new Transparent() ), service, isolationMask, nestedPass );
//}
//
//
//
//} // namespace technique
//
//} // namespace vgeGLBase
//