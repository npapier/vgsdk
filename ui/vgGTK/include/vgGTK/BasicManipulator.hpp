// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_BASICMANIPULATOR_HPP
#define _VGGTK_BASICMANIPULATOR_HPP

#include <vgUI/BasicManipulator.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/GenericCanvas.hpp"
#include "vgGTK/event/Keyboard.hpp"
#include "vgGTK/event/Mouse.hpp"



namespace vgGTK
{



/**
 * @brief	Implements a GTK-based specialization of the vgUI::BasicManipulator.
 */
struct VGGTK_API BasicManipulator : public GenericCanvas< vgUI::BasicManipulator >
{
	/**
	 * @name	Constructors
	 */
	//@{
	BasicManipulator();

	template< typename SharedCanvasType >
	BasicManipulator( const SharedCanvasType * sharedCanvas )
	:	GenericCanvas< vgUI::BasicManipulator >( sharedCanvas ),
		m_keyboard( new vgGTK::event::Keyboard() ),
		m_mouse( new vgGTK::event::Mouse() )
	{}
	//@}

protected:

	/**
	 * @name	Overrides
	 */
	//@{
	void on_realize();
	void on_unrealize();
	//@}

private:

	vgd::Shp< vgGTK::event::Keyboard >	m_keyboard;	///< The GTK keyboard device.
	vgd::Shp< vgGTK::event::Mouse >		m_mouse;	///< The GTK mouse device.

};



} // namespace vgGTK



#endif /*_VGGTK_BASICMANIPULATOR_HPP*/
