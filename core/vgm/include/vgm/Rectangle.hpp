// VGSDK - Copyright (C) 2004-2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGM_RECTANGLE_HPP
#define _VGM_RECTANGLE_HPP

#include "vgm/Vector.hpp"



namespace vgm
{



/**
 * @brief	A very basic rectangle 2d class.
 *
 * <tt>rectangle[0]</tt> and <tt>rectangle[1]</tt> hold respectively the @c x and @c y coordinates of the low-left corner.
 * <tt>rectangle[2]</tt> and <tt>rectangle[3]</tt> hold respectively the width and the height of the rectangle.
 *
 * @see	Rectangle2i, Rectangle2f
 *
 * @ingroup Geometry
 */
template< typename T >
struct Rectangle
{
	/**
	 * @name Constructors
	 */
	//@{

	/**
	 * @brief	Default constructor
	 *
	 * @remark	Beware, the rectangle is not initialized !
	 *
	 * @see		getInvalid
	 */
	Rectangle() {}

	/**
	 * @brief Constructor
	 */
	Rectangle( const T x, const T y, const T width, const T height )
	: m_rectangle( x, y, width, height )
	{}

	/**
	 * @brief Constructor from another rectangle.
	 *
	 * When both types don't match, then convertion occurs (static_cast).
	 */
	template< typename InType >
	explicit Rectangle< T >( const Rectangle< InType > & v )
	{
		for( uint i = 0; i < 4; ++i )
		{
			m_rectangle[i] = static_cast< T >( v[i] );
		}
	}
	//@}


	/**
	 * @name	Accessors
	 */
	//@{
	void set( const T x, const T y, const T width, const T height )
	{
		m_rectangle.setValue( x, y, width, height );
	}

	T&			x()				{ return m_rectangle[0]; }
	const T&	x() const		{ return m_rectangle[0]; }

	T&			y()				{ return m_rectangle[1]; }
	const T&	y() const 		{ return m_rectangle[1]; }

	T&			width()			{ return m_rectangle[2]; }
	const T&	width() const	{ return m_rectangle[2]; }

	T&			height()		{ return m_rectangle[3]; }
	const T&	height() const	{ return m_rectangle[3]; }

	T*			getValue()			{ return m_rectangle.getValue(); }
	const T*	getValue() const	{ return m_rectangle.getValue(); }

	T&			operator[]( const unsigned int i )			{ return m_rectangle[i]; }
	const T&	operator[]( const unsigned int i ) const	{ return m_rectangle[i]; }
	//@}


	/**
	 * @name Comparison methods
	 */
	//@{

	/**
	 * @brief Equality comparison.
	 */
	bool			operator ==( const Rectangle& other ) const { return m_rectangle == other.m_rectangle; }

	/**
	 * @brief Difference comparison.
	 */
	bool			operator !=( const Rectangle& other ) const { return m_rectangle != other.m_rectangle; }

	/**
	 * @brief Equality comparison within given tolerance, for each component.
	 */
	bool			equals( const Rectangle& other, const float tolerance ) const
	{ 
		return m_rectangle.equals( other.m_rectangle, tolerance ); 
	}
	//@}


	/**
	 * @name	Validity
	 */
	//@{
	/**
	 * @brief	Tells if the rectangle has been set invalid.
	 *
	 * @return	true or false
	 */
	const bool isInvalid() const
	{
		return m_rectangle.isInvalid();
	}

	/**
	 * @brief	Set the rectangle invalid.
	 */
	void setInvalid()
	{
		m_rectangle.setInvalid();
	}

	/**
	 * @brief	Creates an invalid rectangle.
	 *
	 * @return	an invaild rectangle
	 */
	static const Rectangle getInvalid()
	{
		Rectangle	rectangle;
		rectangle.setInvalid();

		return rectangle;
	}
	//@}


	/**
	 * @brief Tests if a point is in the rectangle.
	 *
	 * @param x : x coordinate of the point to test.
	 * @param y : y coordinate of the point to test.
	 * @return \c true if the point is inside, \c false if not.
	 */
	const bool isPointIn( const T x, const T y ) const
	{
		assert( m_rectangle[2] > static_cast< T >( 0 ) );
		assert( m_rectangle[3] > static_cast< T >( 0 ) );

		if (	(x < m_rectangle[0]) ||
				(x > m_rectangle[0]+m_rectangle[2]) )
		{
			return false;
		}

		if (	(y < m_rectangle[1]) ||
				(y > m_rectangle[1]+m_rectangle[3]) )
		{
			return false;
		}

		return true;
	}

private:

	/**
	 * @brief	Holds raw rectangle data.
	 *
	 * <tt>m_rectangle[0]</tt> and <tt>m_rectangle[1]</tt> hold respectively the @c x and @c y coordinates of the low-left corner.
	 * <tt>m_rectangle[2]</tt> and <tt>m_rectangle[3]</tt> hold respectively the width and the height of the rectangle.
	 */
	Vector< T, 4 >	m_rectangle;
};



typedef Rectangle< int >	Rectangle2i;	///< An integer based rectangle.
typedef Rectangle< float >	Rectangle2f;	///< A float based rectangle.
typedef Rectangle< double >	Rectangle2d;	///< A float based rectangle.



} // namespace vgm

#endif // #ifndef _VGM_RECTANGLE_HPP
