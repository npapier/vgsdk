// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgDebug/Global.hpp"



namespace vgDebug
{



ILogging& get()
{
	return ( vgDebug::Global::get() );
}



ILogging& Global::get()
{
	return ( m_globalLogger );
}



Logging Global::m_globalLogger;



} // namespace vgDebug
