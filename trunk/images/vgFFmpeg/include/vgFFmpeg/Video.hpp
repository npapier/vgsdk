// VGSDK - Copyright (C) 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGFFMPEG_VIDEO_HPP
#define _VGFFMPEG_VIDEO_HPP

extern "C" {
#include <libswscale/swscale.h>
}

#include <list>
#include <string>
#include <SDL.h>
#include <SDL_thread.h>
#include <vgd/Shp.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/basic/Time.hpp>
#include "vgFFmpeg/vgFFmpeg.hpp"

struct AVCodec;
struct AVCodecContext;
struct AVFormatContext;
struct AVFrame;
struct AVPacketList;


namespace vgFFmpeg
{


template< typename T >
struct MTQueue
{
	MTQueue()
	:	mutex( SDL_CreateMutex() ),
		cond(  SDL_CreateCond() )
	{}

	~MTQueue()
	{
		if ( mutex )	SDL_DestroyMutex( mutex );
		if ( cond )		SDL_DestroyCond( cond );
	}

	const int size() const
	{
		SDL_LockMutex( mutex );

		const int numElements = data.size();

		SDL_UnlockMutex( mutex );

		return numElements;
	}


	void put( vgd::Shp< T > element )
	{
		SDL_LockMutex( mutex );

		data.push_back( element );

		SDL_CondSignal( cond );

		SDL_UnlockMutex( mutex );
	}


	vgd::Shp< T > get( const bool block )
	{
		SDL_LockMutex( mutex );

		vgd::Shp< T > retVal;
		while( !quit )
		{
			if ( data.size() > 0 )
			{
				retVal = data.front();
				data.pop_front();
				break;
			}
			else if ( !block )
			{
				break;
			}
			else
			{
				SDL_CondWait( cond, mutex );
			}
		}
		SDL_UnlockMutex( mutex );
		return retVal;
	}

	void clear()
	{
		SDL_LockMutex( mutex );

		data.clear();

		SDL_UnlockMutex( mutex );
	}

private:
	std::list< vgd::Shp< T > > data;

	SDL_mutex *mutex;
	SDL_cond *cond;
};


struct VGFFMPEG_API ImageFrame
{
	ImageFrame( vgd::Shp< vgd::basic::Image > image, const int64 position )
	:	m_image		( image		),
		m_position	( position	)
	{
	}

	const vgd::Shp< vgd::basic::Image > getImage() const	{ return m_image; }
	const int64 getPosition() const							{ return m_position; }

private:
	vgd::Shp< vgd::basic::Image >	m_image;
	int64							m_position;
};



/**
 * @brief Base class to read and decode a video using FFmpeg
 *
 * @todo use boost thread instead of sdl
 * @todo better error reporting/handling
 */
struct VGFFMPEG_API Video
{
	/**
	 * @name Constructor and destructor
	 */
	//@{

	/**
	 * @brief Constructor
	 */
	Video( const std::string& pathFilename );

	/**
	 * @brief Destructor
	 */
	~Video();
	//@}


	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Returns path to video file
	 */
	const std::string getPathFilename() const;

	/**
	 * @brief	Retrieves the width.
	 */
	const int getWidth() const;

	/**
	 * @brief	Retrieves the height.
	 */
	const int getHeight() const;


	/**
	 * @brief	Retrieves the fps.
	 */
	const float getFrameRate() const;


	/**
	 * @brief	Retrieves video duration (in seconds).
	 */
	const float getDuration() const;

	/**
	 * @brief	Retrieves the current position (in seconds).
	 */
	const float getPosition() const;

	/**
	 * @brief Returns the time spent playing video
	 *
	 * @remark Takes care of pause()
	 *
	 * @return the time in milliseconds
	 */
	const int64 getPlayingElapsedTime() const;


	/**
	 * @brief	Tests if the video reading is over
	 *
	 * @return true if video reading is over, false otherwise
	 */
	const bool isOver();


	/**
	 * @brief Tests playing state
	 *
	 * @return true if video is paused, false if video is playing
	 */
	const bool isPaused() const;
	//@}


	/**
	 * @name Actions
	 */
	//@{

	/**
	 * @brief Sets the video in pause/unpause state
	 *
	 * @param newState		true to pause, false to unpause
	 */
	void pause( const bool newState = true );

	/**
	 * @brief Equivalent pause(false)
	 */
	void play();

// @todo better support for audio seeking
	/**
	 * @brief Set video position to the given time (in seconds).
	 */
	void seek( const float time );

	/**
	 * @brief Restarts the video from the beginning
	 */
	void restart();
	//@}


	/**
	 * @name Decoding method
	 */
	//@{
	const bool processPacket();

	// @todo adds param for position
	const vgd::Shp< ImageFrame > getImage();
	const int getImageQueueSize() const;
	//@}


protected:
	std::string			m_pathfilename;
	vgd::basic::Time	m_time;		///< time point for video starting

	AVFormatContext *	pFormatCtx;
	int					videoStream;
	int					audioStream;

	// video
	AVCodecContext		*pCodecCtx;
	AVCodec				*pCodec;
	SwsContext			*img_convert_ctx;

	// audio
	AVCodecContext		*aCodecCtx;
	AVCodec				*aCodec;
	SDL_AudioSpec		wanted_spec, spec;

	// decode video
	AVFrame	*pFrame; 
	AVFrame	*pFrameRGB;

	int					numBytes;
	uint8 *				buffer;

	// reading informations
	int64 currentPos;

	MTQueue< ImageFrame > imageQueue;
};



} // namespace vgFFmpeg

#endif // #ifndef _VGFFMPEG_VIDEO_HPP
