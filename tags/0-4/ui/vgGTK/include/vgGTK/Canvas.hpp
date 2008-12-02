// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_CANVAS_HPP
#define _VGGTK_CANVAS_HPP

#include "vgGTK/vgGTK.hpp"

#include <vgUI/Canvas.hpp>

#include "vgGTK/GenericCanvas.hpp"


namespace vgGTK
{



/**
 * @brief	Implements a GTK-based specialization of vgUI::Canvas.
 */
struct VGGTK_API Canvas : public GenericCanvas< vgUI::Canvas >
{

	/**
	 * @name	Constructors
	 */
	//@{
	Canvas();

	template< typename SharedCanvasType >
	Canvas(	const SharedCanvasType * sharedCanvas )
	:	GenericCanvas< vgUI::Canvas >( sharedCanvas )
	{}
	//@}

};



} // namespace vgGTK



#endif /*_VGGTK_CANVAS_HPP*/
