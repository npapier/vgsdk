// VGSDK - Copyright (C) 2014, Yakhouba Keita.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Yakhouba Keita

#ifndef _VGUI_CONTEXT_HPP
#define _VGUI_CONTEXT_HPP

#include "vgd/Shp.hpp"
#include "vgUI/vgUI.hpp"
#include "vgUI/Canvas.hpp"
#include "vgUI/BasicManipulator.hpp"

namespace vgUI
{
namespace python
{

/**
 *@brief class Context : a singleton giving pointer to various object giving a (canvas) context to be used by the interpreter
 */
struct VGUI_API Context
{
	/**
	*@brief uses this function to get the unique instance of the context
	*/
	static vgd::Shp<Context> getInstance();

	/**
	 *@brief use this function to set the Canvas declared in MainWindow
	 */
	void setCanvas( Canvas * cv);
	
	/**
	 *@brief get the canvas
	 */
	Canvas * getCanvas();

	/**
	 *@brief tests if the canvas we have set is valid or not ( == NULL or not )
	 */
	bool isCanvasValid();

	void setBasicManipulator(vgUI::BasicManipulator * );
	vgUI::BasicManipulator * getBasicManipulator();

private:
	/**
	*@brief Constructor
	*/
	Context();
	vgUI::BasicManipulator * m_basicManipulator;
	static vgd::Shp<Context> m_instance; ///> the only instance of the context
	Canvas	* m_canvas;

};

} // namespace python
} // namespace vgUI

#endif
