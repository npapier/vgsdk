// VGSDK - Copyright (C) 2004-2006, 2008, 2009, Nicolas Papier.
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
 * @see	Rectangle2i, Rectangle2f, Rectangle2d
 *
 * @ingroup Geometry
 */
template< typename T >
struct Rectangle : public vgm::Vector< T, 4 >
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
	 * @see getInvalid
	 */
	Rectangle()
	{}

	/**
	 * @brief Constructor
	 *
	 * @post getPosition() == (value, value) and getSize() == (value, value)
	 */
	Rectangle( const T value )
	: vgm::Vector<T,4>( value, value, value, value )
	{}

	/**
	 * @brief Constructor
	 */
	Rectangle( const T x, const T y, const T width, const T height )
	: vgm::Vector<T,4>( x, y, width, height )
	{}

	/**
	 * @brief Constructor with value affectation from array of n components.
	 */
	explicit Rectangle( const T* v )
	: vgm::Vector<T,4>( v )
	{}


//	/**
//	 * brief Constructor with value affectation from array of n components.
//	 */
//	template< typename InType >
//	explicit Rectangle< T, N >( const InType* v );


	/**
	 * @brief Copy constructor.
	 */
	Rectangle( const Rectangle& v )
	{
		setValue( v );
	}

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
			Vector<T,4>::m_tCoord[i] = static_cast< T >( v[i] );
		}
	}


	/**
	 * @brief Assign operator.
	 */
	Rectangle& operator=( const Rectangle& v )
	{
		if ( this != &v )
		{
			setValue( v );
		}
	
		return *this;
	}
	//@}


	/**
	 * @name	Accessors
	 */
	//@{
	void set( const T x, const T y, const T width, const T height )
	{
		setValue( x, y, width, height );
	}

	T&			x()				{ return Vector<T,4>::m_tCoord[0]; }
	const T&	x() const		{ return Vector<T,4>::m_tCoord[0]; }

	T&			y()				{ return Vector<T,4>::m_tCoord[1]; }
	const T&	y() const 		{ return Vector<T,4>::m_tCoord[1]; }

	T&			width()			{ return Vector<T,4>::m_tCoord[2]; }
	const T&	width() const	{ return Vector<T,4>::m_tCoord[2]; }

	T&			height()		{ return Vector<T,4>::m_tCoord[3]; }
	const T&	height() const	{ return Vector<T,4>::m_tCoord[3]; }

	T*			getValue()			{ return Vector<T, 4>::getValue(); }
	const T*	getValue() const	{ return Vector<T, 4>::getValue(); }

	//T&			operator[]( const uint i )			{ return m_tCoord[i]; }
	//const T&	operator[]( const uint i ) const	{ return m_tCoord[i]; }

	const vgm::Vector< T, 2 > getPosition() const { return vgm::Vector< T, 2 >( x(), y() ); }

	const vgm::Vector< T, 2 > getSize() const { return vgm::Vector< T, 2 >( width(), height() ); }
	// @todo Rectangle( position, size )

	void setPosition( const vgm::Vector< T, 2 > position ) { Vector<T,4>::m_tCoord[0] = position[0]; Vector<T,4>::m_tCoord[1] = position[1]; }
	void setSize( const vgm::Vector< T, 2 > size ) { Vector<T,4>::m_tCoord[2] = size[0]; Vector<T,4>::m_tCoord[3] = size[1]; }
	//@}


	/**
	 * @name Comparison methods
	 */
	//@{

	/**
	 * @brief Equality comparison.
	 */
	bool operator ==( const Rectangle& other ) const
	{
		return Vector<T, 4>::operator ==( other );
	}

	/**
	 * @brief Difference comparison.
	 */
	bool operator !=( const Rectangle& other ) const
	{
		return Vector<T, 4>::operator !=( other );
	}

	/**
	 * @brief Equality comparison within given tolerance, for each component.
	 */
	bool equals( const Rectangle& other, const float tolerance ) const
	{ 
		return Vector<T, 4>::equals( other, tolerance );
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
		return Vector<T, 4>::isInvalid();
	}

	/**
	 * @brief	Set the rectangle invalid.
	 */
	void setInvalid()
	{
		Vector<T, 4>::setInvalid();
	}

	/**
	 * @brief	Creates an invalid rectangle.
	 *
	 * @return	an invalid rectangle
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
	 * @param x		x coordinate of the point to test.
	 * @param y		y coordinate of the point to test.
	 * @return \c true if the point is inside, \c false if not.
	 */
	const bool isPointIn( const T x, const T y ) const
	{
		assert( width() > static_cast< T >( 0 ) );
		assert( height() > static_cast< T >( 0 ) );

		if (	(x < x()) ||
				(x > x() + width()) )
		{
			return false;
		}

		if (	(y < y()) ||
				(y > y() + height()) )
		{
			return false;
		}

		return true;
	}
};



typedef Rectangle< int		>	Rectangle2i;	///< An integer based rectangle.
typedef Rectangle< float	>	Rectangle2f;	///< A float based rectangle.
typedef Rectangle< double	>	Rectangle2d;	///< A float based rectangle.



} // namespace vgm

#endif // #ifndef _VGM_RECTANGLE_HPP
