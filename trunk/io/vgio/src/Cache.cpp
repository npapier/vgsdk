// VGSDK - Copyright (C) 2008, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgio/Cache.hpp"

#include <vgd/Shp.hpp>
#include <vgd/basic/IImage.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/basic/ImageInfo.hpp>
#include <vgDebug/convenience.hpp>

#include "vgio/FileSystem.hpp"
#include "vgio/Media.hpp"


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



vgd::Shp< vgd::basic::IImage > ImageCache::load( const std::string & pathFilename )
{
	return load( FileSystem(), pathFilename );
}



vgd::Shp< vgd::basic::IImage > ImageCache::load( const Media & media, const std::string & pathFilename )
{
	if ( getInstance()->isEnabled() )
	{
		// USES THE CACHE
		vgd::Shp< vgd::basic::IImage > retVal;

		// Searches in cache
		vgd::basic::IImage * iimage = getInstance()->get< vgd::basic::IImage >( pathFilename );

		if ( iimage == 0 )
		{
			vgLogDebug2("vgio: load image %s", pathFilename.c_str() );
			iimage = loadImage( media, pathFilename );

			if ( iimage )
			{
				// Loading successes
				const bool addingRetVal = getInstance()->add( pathFilename, iimage );
				vgLogDebug2("vgio: image %s added to cache.", pathFilename.c_str() );
				assert( addingRetVal );

				// Returns a copy of the image.
				retVal.reset( new vgd::basic::ImageInfo(*iimage) );
			}
			else
			{
				// Loading fails
				vgLogDebug2("vgio: load image %s fails", pathFilename.c_str() );
			}
		}
		else
		{
			// A match is found for the key in cache. So returns a copy of it.
			vgLogDebug2("vgio: image %s found in cache.", pathFilename.c_str() );
			retVal.reset( new vgd::basic::ImageInfo(*iimage) );
		}

		return retVal;
	}
	else
	{
		// DON'T USE THE CACHE
		vgd::Shp< vgd::basic::IImage >	retVal;
		vgd::basic::IImage				* iimage;

		vgLogDebug2("vgio: load image %s", pathFilename.c_str() );
		iimage = loadImage( media, pathFilename );

		if ( iimage )
		{
			retVal.reset( iimage );
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



vgd::basic::IImage * ImageCache::loadImage( const Media & media, const std::string & pathFilename )
{
	vgd::basic::Image	* result = 0;

	// Checks the existance of the given image.
	if( ! media.exists(pathFilename) )
	{
		vgLogDebug2("vgio: image %s not found", pathFilename.c_str() );
		return 0;
	}

	// Loads the image data.
	std::vector< char >	buffer;
	bool				loadSuccess;

	loadSuccess = media.load( pathFilename, buffer );
	if( !loadSuccess )
	{
		return 0;
	}

	// Builds the image from loaded data and returns it.
	return new vgd::basic::Image( pathFilename, &buffer[0], buffer.size() );
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
