// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/HandlerRegistry.hpp"

#include <sstream>

#include "vge/handler/Handler.hpp"



namespace vge
{

namespace handler
{



bool HandlerRegistry::add( Handler *pHandler )
{
	std::pair< HandlersSet::iterator, bool > retVal;
	retVal = m_handlers.insert( vgd::Shp<Handler>(pHandler) );
	
	return ( retVal.second );
}



std::string HandlerRegistry::get() const
{
	std::stringstream strStream;
	
	for(	HandlersSet::const_iterator i = m_handlers.begin();
			i != m_handlers.end();
			i++ )
	{
		strStream << "(" << typeid(*i).name() << ") ";
	}
	strStream << std::endl << std::ends;

	return ( std::string(strStream.str()) );
}



uint32 HandlerRegistry::getNumRegistered() const
{
	return ( static_cast<uint32>(m_handlers.size()) );
}



std::pair< HandlerRegistry::HandlersSet::iterator, HandlerRegistry::HandlersSet::iterator >
	HandlerRegistry::getIterators()
{
	return ( 
		std::pair< HandlerRegistry::HandlersSet::iterator, HandlerRegistry::HandlersSet::iterator >(
			m_handlers.begin(),
			m_handlers.end() )
			);
}


			
} // namespace handler

} // namespace vge
