// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_BASIC_UNIFORMCONTAINER_HPP
#define _VGEGL_BASIC_UNIFORMCONTAINER_HPP

#include <vge/basic/UniformContainer.hpp>
#include "vgeGL/vgeGL.hpp"

namespace vgeGL { namespace engine { struct Engine; } }



namespace vgeGL
{

namespace basic
{



struct VGEGL_API UniformContainer : public vge::basic::UniformContainer
{
	/**
	 * @brief Sends all uniform variables to OpenGL
	 */
	void apply( vgeGL::engine::Engine * engine );
};



} // namespace basic

} // namespace vgeGL

#endif //#ifndef _VGEGL_BASIC_UNIFORMCONTAINER_HPP
