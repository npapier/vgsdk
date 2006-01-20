// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_MAIN_H
#define _VGEGL_TECHNIQUE_MAIN_H

#include "vgeGL/vgeGL.hpp"
#include "vgeGL/technique/Technique.hpp"



namespace vgeGL
{
	
namespace technique
{



struct VGEGL_API Main : public Technique
{
	void apply( vge::engine::Engine *pEngine, vge::visitor::TraverseElementVector* pTraverseElements );
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_MAIN_H
