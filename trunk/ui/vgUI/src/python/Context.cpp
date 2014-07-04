// VGSDK - Copyright (C) 2014, Yakhouba Keita.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Yakhouba Keita

#include "vgUI/python/Context.hpp"



namespace vgUI
{	
namespace python
{

	vgd::Shp<Context> Context::m_instance;

	Context::Context() : m_canvas(0)
	{}

	vgd::Shp<Context> Context::getInstance()
	{		
		if( m_instance == 0 )
		{
			m_instance = vgd::makeShp(new Context());
		}
		return m_instance;
	}

	void Context::setCanvas( Canvas * canvas )
	{
		m_canvas = canvas;
	}

	Canvas * Context::getCanvas()
	{
		return m_canvas;
	}

	bool Context::isCanvasValid()
	{
		return m_canvas != 0;
	}

	
	void Context::setBasicManipulator(vgUI::BasicManipulator * basic)
	{
		m_basicManipulator = basic;
	}

	vgUI::BasicManipulator * Context::getBasicManipulator()
	{
		return m_basicManipulator;
	}

} // namespace python
} // namespace vgUI
