// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_RECTANGLE_H
#define _VGM_RECTANGLE_H

#include "vgm/vgm.hpp"



namespace vgm
{



/**
 * @brief A very basic rectangle 2d class.
 * 
 * @ingroup Geometry
 */
struct VGM_API Rectangle2i
{
	/**
	 * @name Constructors.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 *
	 * @remarks Nothing is initialized !!!
	 */
	Rectangle2i( void ) {}

	/**
	 * @brief Constructor.
	 */
	Rectangle2i( const int32 x, const int32 y, const int32 width, const int32 height ) :
		m_x(x),
		m_y(y),
		m_width(width),
		m_height(height)
	{}
	//@}



	/**
	 * @name Accessor methods.
	 */
	//@{
	
	void				set( const int32 x, const int32 y, const int32 width, const int32 height )
	{
		m_x		= x;
		m_y		= y;
		m_width	= width;
		m_height	= height;
	}
		
	int32&			x( void )		{ return ( m_x ); }
	const int32&	x( void ) const { return ( m_x ); }

	int32&			y( void )		{ return ( m_y ); }
	const int32&	y( void ) const { return ( m_y ); }

	int32&			width( void )			{ return ( m_width ); }
	const int32&	width( void ) const		{ return ( m_width ); }

	int32&			height( void )			{ return ( m_height ); }
	const int32&	height( void ) const	{ return ( m_height ); }
	//@}



	/**
	 * @brief Test if a point is in the rectangle.
	 *
	 * @param x : x coordinate of the point to test.
	 * @param y : y coordinate of the point to test.
	 * @return \c true if the point is inside, \c false if not.
	 */
	bool isPointIn( const int32 x, const int32 y ) const
	{
		assert( m_width		> 0 );
		assert( m_height	> 0 );

		if (	(x < m_x) || 
				(x > m_x+m_width) )
		{
			return ( false );
		}

		if (	(y < m_y) ||
				(y > m_y+m_height) )
		{
			return ( false );
		}

		return ( true );
	}

private:

	/**
	 * @name rectangle definition data.
	 *
	 * m_x, m_y : The lower-left corner of the rectangle, in pixels.
	 * m_width, m_height : The width and height, respectively, of the rectangle.
	 */
	//@{
	int32 m_x;
	int32 m_y;
	int32 m_width;
	int32 m_height;
	//@}
};



} // namespace vgm

#endif // #ifndef _VGM_RECTANGLE_H
