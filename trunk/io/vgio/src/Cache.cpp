// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgio/Cache.hpp"

#include <vgd/Shp.hpp>
#include <vgd/basic/IImage.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/basic/ImageInfo.hpp>



namespace vgio
{



ImageCache::ImageCache( const std::string name )
: vge::rc::TManager< std::string, vgd::basic::IImage >(name)
{
}



vgd::Shp< vgd::basic::IImage > ImageCache::load( const std::string pathFilename )
{
	vgd::Shp< vgd::basic::IImage > retVal;

	// Searches in cache
	vgd::basic::IImage * iimage = getInstance()->get< vgd::basic::IImage >( pathFilename );

	if ( iimage == 0 )
	{
		// No match is found for the key in cache
		vgd::basic::Image * image( new vgd::basic::Image );
		const bool loadingRetVal = image->load( pathFilename );

		if ( loadingRetVal )
		{
			// Loading successes
			iimage = image;
			const bool addingRetVal = getInstance()->add( pathFilename, image );
			assert( addingRetVal );
		}
		else
		{
			// Loading fails
			return retVal;
		}
	}
	// else match is found for the key in cache. So returns it.

	// Returns a copy of the image
	retVal.reset( new vgd::basic::ImageInfo(*iimage) );

	return retVal;
}



vgd::Shp< ImageCache > ImageCache::getInstance()
{
	// @todo Uses boost for singleton
	if ( m_imageCache == 0 )
	{
		m_imageCache.reset( new ImageCache("imageCache") );
	}

	return m_imageCache;
}



vgd::Shp< ImageCache > ImageCache::m_imageCache;



} // namespace vgio
