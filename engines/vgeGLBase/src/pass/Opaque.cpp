//// VGSDK - Copyright (C) 2007, 2009, 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/pass/Opaque.hpp"
//
//#include <vgd/node/Material.hpp>
//#include <vgd/node/Shape.hpp>
//#include <vgeGL/engine/Engine.hpp>
//#include <vgm/operations.hpp>
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
//Opaque::Opaque()
//:	m_mustDoTransparencyPass( false )
//{}
//
//
//
//void Opaque::apply(	vgeGL::technique::Technique * technique, vgeGL::engine::Engine *engine, 
//					vge::visitor::TraverseElementVector* traverseElements,
//					vgd::Shp< vge::service::Service > service )
//{
//	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
//
//	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
//			i != iEnd;
//			++i )
//	{
//		if ( (i->first)->isAKindOf< vgd::node::Shape >() )
//		{
//			if ( vgm::equals( engine->getGLState().getOpacity(), 1.f ) )
//			{
//				// object is opaque, draw it.
//				engine->evaluate( service, *i );
//			}
//			else
//			{
//				m_mustDoTransparencyPass = true;
//			}
//		}
//		else
//		{
//			engine->evaluate( service, *i );
//		}
//	}
//}
//
//
//
//const bool Opaque::mustDoTransparencyPass() const
//{
//	return m_mustDoTransparencyPass;
//}
//
//
//
//} // namespace pass
//
//} // namespace vgeGL
//