// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgUI/Screenshot.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <locale>

#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/logic/tribool.hpp>
#include <glo/GLSLProgram.hpp>

#include <sbf/pkg/Module.hpp>

#include <vgCairo/helpers.hpp>
#include <vgCairo/ImageSurface.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/Location2Event.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>
#include <vgd/event/SizeEvent.hpp>
#include <vgd/event/TimerEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/detail/helpers.hpp>
#include <vgd/node/MultiSwitch.hpp>
#include <vgd/node/Overlay.hpp>
#include <vgd/visitor/helpers.hpp>
#include <vgDebug/helpers.hpp>
#include <vgio/helpers.hpp>
#include <vgeGL/engine/Engine.hpp>


#include <vgd/basic/ImageUtilities.hpp>

namespace
{



/**
 * @brief Returns a string version of the given number.
 *
 * @param number		number to convert to string
 * @param minLength		prepend enough '0' so the returned string would have the desired minimum length, -1 to prepend nothing
 */
const std::string toString( const uint number, const int minLength = -1 )
{
	const std::string str = boost::lexical_cast< std::string >( number );

	if ( minLength == -1 )
	{
		return str;
	}
	else
	{
		const std::string strZero( (minLength - str.size()), '0' );
		return strZero + str;
	}
}

}

namespace vgUI
{



Screenshot::Screenshot( const uint frameNumber, vgd::Shp< vgd::basic::Image > image )
:	m_frameNumber( frameNumber )
{
	m_images.push_back( image );
	m_imagesData.push_back( image->editPixels() );
	image->editPixelsDone();

	resetCameraInformations();
}


Screenshot::Screenshot( const uint frameNumber, vgd::Shp< vgd::basic::Image > image, void * imageData )
:	m_frameNumber( frameNumber )
{
	m_images.push_back( image );
	m_imagesData.push_back( imageData );

	resetCameraInformations();
}


Screenshot::Screenshot( const uint frameNumber, std::vector< vgd::Shp< vgd::basic::Image > > images )
:	m_frameNumber( frameNumber )
{
	for(	uint i = 0;
			i != images.size();
			++i )
	{
		vgd::Shp< vgd::basic::Image > image = images[i];
		m_images.push_back( image );
		m_imagesData.push_back( image->editPixels() );
		image->editPixelsDone();
	}

	resetCameraInformations();
}


Screenshot::Screenshot( const uint frameNumber, std::vector< vgd::Shp< vgd::basic::Image > > images, std::vector< void * > imagesData )
:	m_frameNumber( frameNumber )
{
	vgAssert( images.size() == imagesData.size() );

	for(	uint i = 0;
			i != images.size();
			++i )
	{
		vgd::Shp< vgd::basic::Image > image = images[i];
		m_images.push_back( image );
		m_imagesData.push_back( imagesData[i] );
	}

	resetCameraInformations();
}


vgd::Shp< Screenshot > Screenshot::clone()
{
	std::vector< vgd::Shp< vgd::basic::Image > > images;

	for(	uint i = 0;
			i != m_images.size();
			++i )
	{
		vgd::Shp< vgd::basic::Image > image = m_images[i];

		vgd::Shp< vgd::basic::Image > cloneImage( new vgd::basic::Image( *image.get() ) );
		images.push_back( cloneImage );
	}

	vgd::Shp< Screenshot > cloned( new Screenshot( m_frameNumber, images ) );
	cloned->setCameraInformations( getNearFar(), getViewport(), getModelview(), getProjection() );

	return cloned;
}


const uint Screenshot::getFrameNumber() const
{
	return m_frameNumber;
}

void Screenshot::setFrameNumber( const uint frameNumber )
{
	m_frameNumber = frameNumber;
}


vgd::Shp< vgd::basic::Image >& Screenshot::getImage( const uint index ) const
{
	return const_cast<Screenshot*>(this)->m_images[index];
}


void *& Screenshot::getImageData( const uint index ) const
{
	return const_cast<Screenshot*>(this)->m_imagesData[index];
}


void Screenshot::setCameraInformations( const vgm::Vec2f& nearFar, const vgm::Vec4i& viewport, const vgm::MatrixR& modelview, const vgm::MatrixR& projection )
{
	m_nearFar		= nearFar;
	m_viewport		= viewport;
	m_modelview		= modelview;
	m_projection	= projection;
}


const vgm::Vec2f& Screenshot::getNearFar() const
{
	return m_nearFar;
}

const vgm::Vec4i& Screenshot::getViewport() const
{
	return m_viewport;
}

const vgm::MatrixR& Screenshot::getModelview() const
{
	return m_modelview;
}

const vgm::MatrixR& Screenshot::getProjection() const
{
	return m_projection;
}


void Screenshot::resetCameraInformations()
{
	m_nearFar.setInvalid();
	m_viewport.setInvalid();
	m_modelview.setInvalid();
	m_projection.setInvalid();
}



void Screenshot::save( const std::string path, const std::string filename, const bool feedback ) const
{
	for(	uint i = 0;
			i != m_images.size();
			++i )
	{
		save( i, path, filename, feedback );
	}


	namespace bfs = boost::filesystem;
	bfs::path cameraFilename( filename );
	saveCameraInformations( path, cameraFilename.stem().string());
}


void Screenshot::save( const uint index, const std::string path, const std::string filename, const bool feedback ) const
{
	namespace bfs = boost::filesystem;
	vgAssertN( bfs::exists( path ), "Path not found" );

	// Choose how to save (image file, raw data, ...)
	using vgd::basic::Image;
	vgd::Shp< Image > image = getImage(index);
	if (image->isEmpty() )	return;

	const bool isUINT8 = image->type() == Image::UINT8;
	const bool isRGB = image->format() == Image::RGB;
	const bool isBGR = image->format() == Image::BGR;
	const bool isRGBA = image->format() == Image::RGBA;
	const bool isBGRA = image->format() == Image::BGRA;
	const bool isColorBuffer = (isRGB || isBGR || isRGBA || isBGRA) && isUINT8;

	std::string outFilename;
	if ( isColorBuffer )
	{
		outFilename = filename.size() > 0 ?
			filename : buildFilename( "frame_color_", ".tga", index );
	}
	else
	{
		outFilename = filename.size() > 0 ?
			filename : buildFilename( "frame_" + Image::toString(image->type()) + "_" + Image::toString(image->format()) + "_", ".dat", index );
	}

	// Write to file
	const std::string pathFilename = (bfs::path(path) / outFilename).string();

	if ( feedback )	vgLogDebug( "Saving %s", pathFilename.c_str() );

	if ( isColorBuffer )
	{
		// Write to image file

		// Removes image if needed
		if ( bfs::exists( pathFilename ) )	bfs::remove( pathFilename );

		// Saves image
		image->save( pathFilename );
	}
	else
	{
		// Write raw data to file
/*		vgd::basic::MinMax minMax = vgd::basic::ImageUtilities::computeMinMax( image );
		vgLogMessage("MinMax of %s = (%f,%f)", outFilename.c_str(), minMax.getMin(), minMax.getMax() );*/

		vgio::writeFile( pathFilename, static_cast<const char*>(image->pixels()), static_cast<const uint>(image->computeMaximumOffset()) );
	}
}


void Screenshot::saveCameraInformations( const std::string path, const std::string filename ) const
{
	namespace bfs = boost::filesystem;
	vgAssertN( bfs::exists( path ), "Path not found" );

	const std::string lFilename = filename.size() > 0 ? filename + ".txt" : "camera" + toString(getFrameNumber(), 8) + ".txt";

	// Output file
	const std::string output = (bfs::path(path) / lFilename).string();

	// Saves informations
	std::ofstream file( output, std::ios::trunc | std::ios::binary );
	if ( file.is_open() )
	{
		file << "nearFar " << getNearFar().toString() << std::endl;
		file << "viewport " << getViewport().toString() << std::endl;
		file << "modelview " << getModelview().toString() << std::endl;
		file << "projection " << getProjection().toString() << std::endl;
	}
	else
	{
		vgLogDebug("Unable to open %s", output.c_str() );
	}
}


void Screenshot::mkdirs( const std::string path )
{
	namespace bfs = boost::filesystem;

	if ( bfs::exists( path ) == false )
	{
		vgLogDebug( "Creating %s", path.c_str() );

		bfs::create_directories( path );
	}
	// else nothing to do
}



const std::string Screenshot::buildFilename( const std::string filePrefix, const std::string extension, const uint index ) const
{
	// Constructs filename

	// FIXME boost::format seems to SEGV with boost 1.38 on win32, so boost lexical cast is used
	//const std::string strCount = (boost::format("%|07|") % getFrameNumber()).str();

	const std::string strFrameCount = toString( getFrameNumber(), 8 );

	const std::string strIndex = boost::lexical_cast< std::string >( index );

	const std::string filename = filePrefix + strFrameCount + "_" + strIndex + extension;

	return filename;
}


/////////////////////////
// ScreenshotContainer //
/////////////////////////
ScreenshotContainer::ScreenshotContainer()
:	// m_container
	// m_recycledContainer
	// m_path
	// m_mutex
	// m_thread
	m_scheduleInterrupt( false )
{}


ScreenshotContainer::~ScreenshotContainer()
{
	stopThread();
}


void ScreenshotContainer::push( vgd::Shp< Screenshot > screenshot )
{
	boost::recursive_mutex::scoped_lock slock( m_mutex );

	m_container.push_back( screenshot );
}


void ScreenshotContainer::pop()
{
	boost::recursive_mutex::scoped_lock slock( m_mutex );

	vgd::Shp< Screenshot > element = m_container.front();

	m_container.pop_front();

	m_recycledContainer.push_back( element );

	//vgLogDebug("++sizeBuffering()=%i", sizeBuffering());
}


vgd::Shp< Screenshot > ScreenshotContainer::popBuffering()
{
	boost::recursive_mutex::scoped_lock slock( m_mutex );

	vgAssert( m_recycledContainer.size() >= 1 );

	vgd::Shp< Screenshot > element = m_recycledContainer.front();

	m_recycledContainer.pop_front();

	//vgLogDebug("--sizeBuffering()=%i", sizeBuffering());
	return element;
}


void ScreenshotContainer::createDirs( const std::string path )
{
	namespace bfs = boost::filesystem;

	if ( bfs::exists( path ) == false )
	{
		vgLogDebug( "Creating %s", path.c_str() );

		bfs::create_directories( path );
	}
	// else nothing to do

	boost::recursive_mutex::scoped_lock slock( m_mutex );
	m_path = path;
}


void ScreenshotContainer::saveAndPop( const std::string filePrefix, const bool feedback )
{
	boost::recursive_mutex::scoped_lock slock( m_mutex );

	if ( m_container.size() >= 1 )
	{
		// Copies infos
		const std::string		path = m_path;
		vgd::Shp< Screenshot >	element = m_container.front();
		m_mutex.unlock();

		// Saves image
		assert( !path.empty() );
		element->save( path, filePrefix, feedback );

		// Removes
		pop();
	}
	//else nothing to do
}


void ScreenshotContainer::saveAndPopAll( const std::string filePrefix, const bool feedback )
{
	while( size() > 0 )
	{
		saveAndPop( filePrefix, feedback );
	}
}


const uint ScreenshotContainer::size() const
{
	boost::recursive_mutex::scoped_lock slock( m_mutex );

	return static_cast<uint>(m_container.size());
}


const uint ScreenshotContainer::sizeBuffering() const
{
	boost::recursive_mutex::scoped_lock slock( m_mutex );

	return static_cast<uint>(m_recycledContainer.size());
}


void ScreenshotContainer::setBufferingSize( const uint bufferingSize, vgd::Shp< Screenshot > element )
{
	boost::recursive_mutex::scoped_lock slock( m_mutex );

	if ( bufferingSize > m_recycledContainer.size() )
	{
		// Adding new element(s)
		for(	auto numElementsToAdd = bufferingSize - m_recycledContainer.size();
				numElementsToAdd > 0;
				--numElementsToAdd )
		{
			m_recycledContainer.push_back( element->clone() );			// openil lock
		}
	}
	else if ( bufferingSize < m_recycledContainer.size() )
	{
		// Removing element(s)
		m_recycledContainer.resize( bufferingSize );
	}
	//else == nothing to do
}


void ScreenshotContainer::startThread()
{
	m_thread = boost::thread( boost::ref(*this) );
}


void ScreenshotContainer::stopThread()
{
	boost::recursive_mutex::scoped_lock slock( m_mutex );

	if ( isStarted() )
	{
		m_thread.interrupt();
	}
}


const bool ScreenshotContainer::isStarted() const
{
	return m_thread.get_id() != boost::thread::id();
}


void ScreenshotContainer::scheduleThreadInterrupt()
{
	m_scheduleInterrupt = true;
}



boost::thread& ScreenshotContainer::getThread()
{
	boost::recursive_mutex::scoped_lock slock( m_mutex );

	return m_thread;
}


void ScreenshotContainer::sleep( uint msecs )
{
	boost::this_thread::sleep( boost::posix_time::milliseconds(msecs) );
	// @todo m_thread.sleep( boost::posix_time::milliseconds(msecs) ); ?
}


void ScreenshotContainer::operator() ()
{
	while ( !m_scheduleInterrupt )
	{
		saveAndPop("", false);
		// @todo fine tuning (sleep()...)
	}

	//
	m_scheduleInterrupt = false;

	//	Saves all images
	saveAndPopAll( "", false );
}


} // namespace vgUI
