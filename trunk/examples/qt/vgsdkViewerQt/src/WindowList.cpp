// VGSDK - Copyright (C) 2013, Guillaume Brocker, Bryan Schuller, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgsdkViewerQt/WindowList.hpp"

#include "vgsdkViewerQt/MainWindow.hpp"


namespace vgsdkViewerQt
{


WindowList::WindowList()
: m_counter(0)
{}


void WindowList::add( MainWindow * window )
{
	Container::const_iterator found = std::find( m_windows.begin(), m_windows.end(), window );
	Q_ASSERT( found == m_windows.end() );

	m_windows.push_back( window );
	m_counter++;
}


void WindowList::closeAll()
{
	Container windows( m_windows );
	for( Container::iterator window = windows.begin(); window != windows.end(); ++window )
	{
		(*window)->close();
	}
}


const int WindowList::counter() const
{
	return m_counter;
}


void WindowList::remove( MainWindow * window )
{
	m_windows.erase( std::remove(m_windows.begin(), m_windows.end(), window) );
}


} // vgsdkVIewerQt