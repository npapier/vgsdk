// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_LAYERS_H
#define _VGEGL_HANDLER_PAINTER_LAYERS_H

#include "vgeGL/vgeGL.hpp"

#include <vgd/node/Layers.hpp>
#include <vge/handler/painter/Group.hpp>

namespace vgeGL
{
	namespace engine
	{
		struct Engine;
	}
	
	namespace rc
	{
		struct DisplayList;
	}	
}



namespace vgeGL
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Render a vgd::node::Layers.
 */
struct VGEGL_API Layers : public vge::handler::painter::Group
{
	META_HANDLER_HPP( Layers );

	//const vge::service::List			getServices	() const;
	const TargetVector					getTargets()	const;

	void	apply				( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
	
	void	paint				( vgeGL::engine::Engine*, vgd::node::Layers* );

private:
	/**
	 * @brief Scan the whole image and ...
	 * 
	 * @pre pScissor->format() == RGBA or pScissor->format() == BGRA or pScissor->format() == LUMINANCE_ALPHA
	 * @pre pScissor->format() == pImage->format()
	 * 
	 * @pre pScissor->type() == UINT8
	 * @pre pImage->type() == UINT8
	 * @pre same size for image and scissor.
	 * 
	 * @param pScissor	image to scan.
	 * @param pImage		image to scan.
	 */
	void	applyScissorMask( vgd::Shp< vgd::basic::IImage > pScissor, vgd::Shp< vgd::basic::IImage > pImage );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_LAYERS_H
