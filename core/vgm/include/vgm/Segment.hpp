// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_SEGMENT_HPP
#define _VGM_SEGMENT_HPP

#include "vgm/vgm.hpp"
#include "vgm/Vector.hpp"



namespace vgm
{



/**
 * @brief Represents a segment in 3D space
 * 
 * Segment provides a way of specifying a line that is bounded by two end points.
 * 
 * @ingroup Geometry
 */
struct VGM_API Segment
{
	/**
	 * @name Constructors
	 */
	//@{

	/**
	 * @brief Default constructor
	 *
	 * @remark not initialized
	 */
	Segment();

	/**
	 * @brief Construct a segment from two end points
	 */
	Segment( const Vec3f& p0, const Vec3f& p1 );
	//@}


	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Construct a segment from two end points
	 */
	void setValue( const Vec3f& p0, const Vec3f& p1 );

	/**
	 * @brief Get the first end point of the segment
	 */
	const Vec3f&	getBegin() const;

	/**
	 * @brief Get the second end point of the segment
	 */
	const Vec3f&	getEnd() const;

	//@}


	/**
	 * @name Some useful computing methods
	 */
	//@{

	/**
	 * @brief Get the direction of the segment
	 */
	const Vec3f getDirection() const;

	//@}



	/**
	 * @name Intersection methods
	 */
	//@{

	/**
	 * @brief Test if the given point P is lying on the segment.
	 * 
	 * @return true if the given point P is lying on the segment, false otherwise.
	 */
	const bool isIn( const Vec3f P ) const;
	//@}

private:

	/**
	 * @name Internal representation
	 */
	//@{
	Vec3f	m_begin;
	Vec3f	m_end;
	//@}
};

} // namespace vgm

#endif // #ifndef _VGM_SEGMENT_HPP
