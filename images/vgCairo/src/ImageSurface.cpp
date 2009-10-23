// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgCairo/ImageSurface.hpp"

//#include <cstring>



namespace vgCairo
{



ImageSurface::ImageSurface(	const uint32 width, const uint32 height )
:	m_edit	(	false 	),
	m_pixels(	0		)
	// m_surface
	// m_cairo
{
	// Allocates and initializes pixel buffer 
	//const uint numPixels	= width*height;
	//const uint sizeOfPixels	= numPixels * 4;
	//m_pixels = new uint8[sizeOfPixels] )
	//std::memset( m_pixels, 0, sizeOfPixels );
	// Creates cairo surface and context
	//m_surface	= cairo_image_surface_create_for_data( m_pixels, CAIRO_FORMAT_ARGB32, width, height, 4 * width );

	// Creates cairo surface and context
	m_surface	= cairo_image_surface_create( CAIRO_FORMAT_ARGB32, width, height );
	checkCairoSurfaceStatus();

	m_pixels	= cairo_image_surface_get_data( m_surface );

	m_cairo		= cairo_create( m_surface );
	checkCairoSurfaceStatus();
}



ImageSurface::ImageSurface(	const std::string filename )
:	m_edit	(	false 	),
	m_pixels(	0		)
	// m_surface
	// m_cairo
{
	// Creates cairo surface and context
	m_surface	= cairo_image_surface_create_from_png( filename.c_str() );
	checkCairoSurfaceStatus();

	m_pixels	= cairo_image_surface_get_data( m_surface );

	m_cairo		= cairo_create( m_surface );
	checkCairoSurfaceStatus();
}



ImageSurface::~ImageSurface()
{
	cairo_destroy( m_cairo );
	cairo_surface_destroy( m_surface );

	//delete [] m_pixels;
}



const uint32 ImageSurface::components() const
{ 
	return 4;
}



const uint32 ImageSurface::width() const
{
	return cairo_image_surface_get_width( m_surface );
}



const uint32 ImageSurface::height() const
{
	return cairo_image_surface_get_height( m_surface );
}



const uint32 ImageSurface::depth() const
{
	return 1;
}



const ImageSurface::Format ImageSurface::format() const
{
	assert( cairo_image_surface_get_format( m_surface ) == CAIRO_FORMAT_ARGB32 );

	return BGRA;
}



const ImageSurface::Type ImageSurface::type() const
{
	return UINT8;
}



const void* ImageSurface::pixels() const
{
	return m_pixels;
}



void* ImageSurface::editPixels()
{
	assert( !m_edit );

	m_edit = true;

	return m_pixels;
}



void ImageSurface::editPixelsDone()
{
	assert( m_edit );
	
	m_edit = false;
}



void ImageSurface::write( const std::string filename )
{
	cairo_surface_write_to_png( m_surface, filename.c_str() );
}



void ImageSurface::checkCairoSurfaceStatus()
{
	assert( cairo_surface_status( m_surface ) == CAIRO_STATUS_SUCCESS );
}



} // namespace vgCairo
