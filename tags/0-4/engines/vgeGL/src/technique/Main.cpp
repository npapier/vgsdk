// VGSDK - Copyright (C) 2004, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/Main.hpp"

#include <vge/pass/ForEach.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/pass/Opaque.hpp"
#include "vgeGL/pass/Transparent.hpp"



namespace vgeGL
{

namespace technique
{



void Main::apply( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();

	prepareEval( engine, traverseElements );

	// At startup, the transparency pass is disabled. It would be enabled during the opaque pass if at least one
	// transparent shape is encountered.

	// First pass : OPAQUE PASS (draw opaque shape)
	using ::vgeGL::pass::Opaque;
	vgd::Shp< Opaque > opaque( new Opaque() );

	evaluatePass( opaque, paint );

	// Second pass : TRANSPARENT PASS (draw transparent shape).
	if ( opaque->mustDoTransparencyPass() )
	{
		using ::vgeGL::pass::Transparent;
		
		evaluatePass( vgd::makeShp( new Transparent() ), paint );
	}

	//
	finishEval();
}





} // namespace technique

} // namespace vgeGL
