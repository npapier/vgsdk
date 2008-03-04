// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_BASICVIEWER_HPP
#define _VGGTK_BASICVIEWER_HPP

#include <vgUI/BasicViewer.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/GenericCanvas.hpp"



namespace vgGTK
{



/**
 * @brief	Implements a GTK-based specialization of vgUI::BasicViewer.
 */
struct VGGTK_API BasicViewer : public GenericCanvas< vgUI::BasicViewer >
{

	/**
	 * @name	Constructors
	 */
	//@{
	BasicViewer();

	template< typename SharedCanvasType >
	BasicViewer( const SharedCanvasType * sharedCanvas )
	:	GenericCanvas< vgUI::BasicViewer >( sharedCanvas )
	{}
	//@}

};



} // namespace vgGTK



#endif /*_VGGTK_BASICVIEWER_HPP*/
