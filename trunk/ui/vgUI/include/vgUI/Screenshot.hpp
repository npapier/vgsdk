// VGSDK - Copyright (C) 2013, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGUI_SCREENSHOT_HPP
#define _VGUI_SCREENSHOT_HPP

#include <boost/thread.hpp>

#include <boost/date_time/posix_time/posix_time.hpp> // @todo uses vgsdk time classes
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>
#include <sbf/pkg/Module.hpp>
#include <vgDebug/helpers.hpp>

#include <vgd/Shp.hpp>
#include <vgm/Matrix.hpp>
#include "vgUI/vgUI.hpp"

namespace vgd { namespace basic { struct Image; } }



namespace vgUI
{

/**
 * @brief Container of images to record a complete frame rendered with camera informations
 *
 * @todo add time
 */
struct Screenshot
{
	/**
	 * @brief Constructor
	 * @remark Lock on openil by editPixels()
	 */
	Screenshot( const uint frameNumber, vgd::Shp< vgd::basic::Image > image );

	/**
	 * @brief Constructor
	 *
	 * @remark No lock on openil
	 */
	Screenshot( const uint frameNumber, vgd::Shp< vgd::basic::Image > image, void * imageData );

	/**
	 * @brief Constructor
	 *
	 * @remark Lock on openil by editPixels()
	 */
	Screenshot( const uint frameNumber, std::vector< vgd::Shp< vgd::basic::Image > > images );

	/**
	 * @brief Constructor
	 *
	 * @pre images.size() == imagesData.size()
	 * @remark No lock on openil
	 */
	Screenshot( const uint frameNumber, std::vector< vgd::Shp< vgd::basic::Image > > images, std::vector< void * > imagesData );


	/**
	 * @remark Lock on openil by editPixels()
	 */
	vgd::Shp< Screenshot > clone();


	/**
	 * @name Accessors
	 */
	//@{
	const uint getFrameNumber() const;
	void setFrameNumber( const uint frameNumber );

	vgd::Shp< vgd::basic::Image > getImage( const uint index ) const;
	void * getImageData( const uint index ) const; ///< Returns a pointer to the image data in memory

	void setCameraInformations( const vgm::Vec2f nearFar, const vgm::Vec4i viewport, const vgm::MatrixR& modelview, const vgm::MatrixR& projection );
	const vgm::Vec2f& getNearFar() const;
	const vgm::Vec4i& getViewport() const;
	const vgm::MatrixR& getModelview() const;
	const vgm::MatrixR& getProjection() const;

	void resetCameraInformations();
	//@}


	/**
	 * @brief Saves all images and camera informations stored by this class.
	 */
	void save( const std::string path, const std::string filename = "", const bool feedback = true ) const;

	/**
	 * @brief Saves one image to a file
	 *
	 * @param index
	 * @param filename	name of image file (with extension .png or .tga ) or
	 *					empty to automatically construct a filename using prefix 'frame', appending frame counter, an '_' and image index.
	 *
	 * @pre path directory must exist
	 *
	 * @remark If image specified by given parameters already exists, then it is overridden. Otherwise the image file is simply created.
	 */
	void save(const uint index, const std::string path, const std::string filename = "", const bool feedback = true ) const;

	void saveCameraInformations( const std::string path, const std::string filename = "" ) const;

	void mkdirs( const std::string path ); // @todo remove me
private:
	const std::string buildFilename( const std::string filePrefix, const std::string extension, const uint index ) const;

	uint											m_frameNumber;	///< the frame number to identify a screenshot. This attribute could be used to order a sequence of screenshots.
	std::vector< vgd::Shp< vgd::basic::Image >	>	m_images;		///< all captured images
	std::vector< void * >							m_imagesData;	///< all captured images. See getImageData()

	vgm::Vec2f										m_nearFar; // => gl_FragCoord.z from linearDepth
	// for unproject
	vgm::Vec4i										m_viewport;
	vgm::MatrixR									m_modelview;
	vgm::MatrixR									m_projection;
};



/**
 * @brief Container of screenshots
 *
 * - MT-Safe
 * - Buffering system (pre-allocation of contained elements and recycling of elements)
 * - Thread to apply action on container
 *
 * @todo template version and more generic (Producer/Container/Consumer/Action...)
 */
struct ScreenshotContainer
{
	/**
	 * @brief Default constructor
	 */
	ScreenshotContainer(); 

	/**
	 * @brief Destructor
	 *
	 * Stop the thread (if needed)
	 */
	~ScreenshotContainer();


	/**
	 * @brief Adds an element to the back to the queue
	 */
	void push( vgd::Shp< Screenshot > screenshot );


	/**
	 * @brief Removes an element from the front of the queue
	 *
	 * @remarks Adds element to the recycling container.
	 */
	void pop();

	/**
	 * @brief Returns and removes an element for the front of the recycled queue.
	 *
	 * @pre sizeRecycled() >= 1
	 * @return the element to recycle
	 */
	vgd::Shp< Screenshot > popBuffering();
 


	/**
	 * @brief Recursive directory creation function.
	 *
	 * @remarks All images saved after would be written in this directory.
	 */
	void createDirs( const std::string path );

	/**
	 * @brief Writes the screenshot from the front of the queue and removes it.
	 *
	 * @param filePrefix		start of the filename used to save the screenshot
	 * @param feedback			true to log feedback, false otherwise
	 *
	 * @remark lock openil.
	 */
	void saveAndPop( const std::string filePrefix, const bool feedback = false );

	/**
	 * @brief Writes each screenshot and removes it from the queue.
	 *
	 * @remark lock openil.
	 */
	void saveAndPopAll( const std::string filePrefix, const bool feedback = false );


	/**
	 * @brief Returns the number of elements in the queue.
	 */
	const uint size() const;

	/**
	 * @brief Returns the number of elements in the buffering queue.
	 */
	const uint sizeBuffering() const;

	/**
	 * @brief Sets the number of elements in the buffering system.
	 *
	 * @param bufferingSize		number of elements in the buffer container
	 * @param element			copying the given element to fill the buffer. element.clone() have to exist and return a cloned object.
	 *
	 * @remark 60 elements * 1080p in RBG24 => 356MB
	 */
	void setBufferingSize( const uint bufferingSize, vgd::Shp< Screenshot > element );


	/**
	 * @name Thread related
	 */
	//@{

	void startThread();
	void stopThread();

	const bool isStarted() const;

	void scheduleThreadInterrupt();

	boost::thread& getThread();

	void sleep( uint msecs );

	// Callable type for boost::thread
	void operator() ();
	//@}

protected:

	std::list< vgd::Shp< Screenshot > >	m_container;

	std::list< vgd::Shp< Screenshot > >	m_recycledContainer;

	std::string							m_path;

	mutable boost::recursive_mutex		m_mutex;
	boost::thread 						m_thread;
	bool								m_scheduleInterrupt;
};


} // namespace vgUI

#endif // #ifndef _VGUI_SCREENSHOT_HPP
