// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgio/Cache.hpp"

#include <vgd/Shp.hpp>
#include <vgd/basic/IImage.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/basic/ImageInfo.hpp>
#include <vgDebug/convenience.hpp>



namespace vgio
{



ImageCache::ImageCache( const std::string name )
:	vge::rc::TManager< std::string, vgd::basic::IImage >(name),
	m_isEnabled(false)
{
}



const bool ImageCache::isEnabled() const
{
	return m_isEnabled;
}



void ImageCache::setEnabled( const bool enabled )
{
	m_isEnabled = enabled;
}



vgd::Shp< vgd::basic::IImage > ImageCache::load( const std::string pathFilename )
{
	if ( getInstance()->isEnabled() )
	{
		// USES THE CACHE
		vgd::Shp< vgd::basic::IImage > retVal;

		// Searches in cache
		vgd::basic::IImage * iimage = getInstance()->get< vgd::basic::IImage >( pathFilename );

		if ( iimage == 0 )
		{
			// No match is found for the key in cache
			vgd::basic::Image * image( new vgd::basic::Image );

			vgLogDebug2("vgio: load image %s", pathFilename.c_str() );
			const bool loadingRetVal = image->load( pathFilename );

			if ( loadingRetVal )
			{
				// Loading successes
				iimage = image;
				const bool addingRetVal = getInstance()->add( pathFilename, image );
				vgLogDebug2("vgio: image %s added to cache.", pathFilename.c_str() );
				assert( addingRetVal );
			}
			else
			{
				// Loading fails
				vgLogDebug2("vgio: load image %s fails", pathFilename.c_str() );
				return retVal;
			}
		}
		else
		{
			// A match is found for the key in cache. So returns it.
			vgLogDebug2("vgio: image %s found in cache.", pathFilename.c_str() );
		}

		// Returns a copy of the image
		retVal.reset( new vgd::basic::ImageInfo(*iimage) );

		return retVal;
	}
	else
	{
		// DON'T USE THE CACHE
		vgd::Shp< vgd::basic::IImage > retVal;

		vgd::Shp< vgd::basic::Image > image( new vgd::basic::Image );

		vgLogDebug2("vgio: load image %s", pathFilename.c_str() );
		const bool loadingRetVal = image->load( pathFilename );

		if ( loadingRetVal )
		{
			retVal = image;
			vgLogDebug2("vgio: load image %s done.", pathFilename.c_str() );
		}
		else
		{
			// Loading fails
			vgLogDebug2("vgio: load image %s fails", pathFilename.c_str() );
		}

		return retVal;
	}
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
