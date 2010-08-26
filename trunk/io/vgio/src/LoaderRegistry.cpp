// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgio/LoaderRegistry.hpp"

#include <vgd/basic/FilenameExtractor.hpp>
#include <vgDebug/convenience.hpp>

namespace vgio
{

vgd::Shp< LoaderRegistry > LoaderRegistry::getLoaderRegistry()
{
	static vgd::Shp< LoaderRegistry > loaderRegistry;

	if( !loaderRegistry )
	{
		loaderRegistry.reset( new LoaderRegistry() );
	}
	
	return loaderRegistry;
}

LoaderRegistry::LoaderRegistry( )
{
}



LoaderRegistry::~LoaderRegistry( )
{
	m_loaderMap.clear();
}



std::map< std::string, vgd::Shp< vgio::ILoader > > LoaderRegistry::getLoaderMap() const
{
	return m_loaderMap;
}



void LoaderRegistry::addLoader( vgd::Shp< vgio::ILoader > loader, std::string type )
{
	assert( m_loaderMap.find(type) == m_loaderMap.end() && "Loader type already used." );

	m_loaderMap[ type ] = loader;
}



vgd::Shp< vgio::ILoader > LoaderRegistry::getLoader( std::string type )
{
	vgd::Shp< vgio::ILoader > retVal;
	
	if( m_loaderMap.find( type ) != m_loaderMap.end() )
	{
		retVal =  m_loaderMap[ type ]->clone();
	}

	return retVal;
}


} // namespace vgio
