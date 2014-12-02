//// VGSDK - Copyright (C) 2004, 2007, 2008, 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/technique/Main.hpp"
//
//#include <vge/pass/ForEach.hpp>
//#include <vge/service/Painter.hpp>
//#include "vgeGL/engine/Engine.hpp"
//#include "vgeGL/pass/Opaque.hpp"
//#include "vgeGL/pass/Transparent.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace technique
//{
//
//
//
//void Main::apply( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
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
//	using ::vgeGL::pass::Opaque;
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
//	using ::vgeGL::pass::Transparent;
//
//	evaluatePass( vgd::makeShp( new Transparent() ), service, isolationMask, nestedPass );
//}
//
//
//
//} // namespace technique
//
//} // namespace vgeGL
//