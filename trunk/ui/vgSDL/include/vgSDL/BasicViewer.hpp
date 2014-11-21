// VGSDK - Copyright (C) 2008, 2014, Nicolas Papier, Philippe Sengchanpheng.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier
// Author Philippe Sengchanpheng

#ifndef _VGSDL_BASICVIEWER_HPP
#define _VGSDL_BASICVIEWER_HPP

#include <vgUI/BasicViewer.hpp>

#include "vgSDL/vgSDL.hpp"
#include "vgSDL/GenericCanvas.hpp"



namespace vgSDL
{



/**
 * @brief	Implements a SDL-based specialization of vgUI::BasicViewer.
 */
struct VGSDL_API BasicViewer : public GenericCanvas< vgUI::BasicViewer >
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



} // namespace vgSDL



#endif /*_VGSDL_BASICVIEWER_HPP*/
