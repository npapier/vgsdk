// VGSDK - Copyright (C) 2004-2006, 2008, 2010, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

/*
 * This file is a work based on the open source release of Open Inventor (from SGI).
 */

/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

/*
 * Author(s)		:	Paul S. Strauss, Nick Thompson, David Mott.
 */

#ifndef _VGM_BOX_HPP
#define _VGM_BOX_HPP

#include "vgm/vgm.hpp"
#include "vgm/Matrix.hpp"
#include "vgm/Vector.hpp"



namespace vgm
{



/**
 * @defgroup Boxes Boxes (2D/3D boxes).
 *
 * A box has planes parallel to the major axes and can therefore be specified by two points on 
 * a diagonal.  The points with minimum and maximum x, y, and z coordinates are used.
 * 
 * @ingroup Geometry
 */
//@{

/**
 * @brief 3d box class
 *
 * A 3d box has planes parallel to the major axes and can therefore be specified by two points on
 * a diagonal.
 * 
 * @ingroup Geometry
 */
struct VGM_API Box3f
{
	/**
	 * @name Constructors and destructor
	 */
	//@{

	/**
	 * @brief Default constructor for a 3D float box.
	 *
	 * Default constructor leaves box totally empty.
	 */
	Box3f();

	/**
	 * @brief Constructor for a 3D float box.given bounds.
	 *
	 * Constructors (\b xmin, \b ymin, \b zmin) and (\b xmax, \b ymax, and \b zmax) are the bounds of the box.
	 * \b min and \b max are the corners of the diagonal that define the box.
	 *
	 * @deprecated
	 */
	vgDEPRECATED( Box3f(	float xmin, float ymin, float zmin,
							float xmax, float ymax, float zmax) ); 

	/**
	 * @brief Constructor given minimum and maximum points .
	 *
	 * Constructors \b min and \b max are the bounds of the box.
	 * \b min and \b max are the corners of the diagonal that define the box.
	 */
	Box3f(const Vec3f& min, const Vec3f& max);

	/**
	 * @brief Destructor.
	 */
	virtual ~Box3f();
	//@}


	/**
	 * @name Returns the minimum and maximum points of the box
	 */
	//@{

	/**
	 * @brief Returns the min point.
	 *
	 * The minimum point is the corner of the box with the lowest X, Y, and Z values.
	 */
	const Vec3f& getMin() const;

	/**
	 * @brief Returns the max point.
	 *
	 * The maximum point is the corner of the box with the highest X, Y, and Z values.
	 */
	const Vec3f& getMax() const;
	//@}


	/**
	 * @name Bounding box accessors
	 */
	//@{

	/**
	 * @brief Returns the center of a box.
	 */
	const Vec3f getCenter() const;

	/**
	 * @brief Returns origin (minimum point) of box.
	 *
	 * Gets box origin which is the same as the minimum corner of the box.
	 *
	 * @deprecated
	 */
	vgDEPRECATED( void	getOrigin( float& originX, float& originY, float& originZ) const );

	/**
	 * @brief Returns origin (minimum point) of box.
	 *
	 * Gets box origin which is the same as the minimum corner of the box.
	 */
	const vgm::Vec3f getOrigin() const;

	/**
	 * @brief Returns size of box.
	 *
	 * @deprecated
	 */
	vgDEPRECATED( void getSize( float& sizeX, float& sizeY, float& sizeZ) const );

	/**
	 * @brief Returns size of box.
	 */
	const vgm::Vec3f getSize() const;


	/**
	 * @brief Invalidates the box.
	 *
	 * @remarks This is a special state of empty box. So an invalid box is always empty, but an empty box is not always invalid.
	 */
	void setInvalid( void );

	/**
	 * @brief Returns an invalid box
	 */
	static const Box3f getInvalid();

	/**
	 * @brief Tests if the box is invalid.
	 */
	const bool isInvalid( void ) const;

	/**
	 * @brief Tests if the box is valid.
	 */
	const bool isValid( void ) const;


	/**
	 * @brief Sets Box3f to contain nothing.
	 *
	 * Makes an empty box.
	 */
	void makeEmpty();

	/**
	 * @brief Checks if the box is empty (degenerate).
	 *
	 * Returns \c true if the box is empty, and \c false otherwise.
	 *
	 * Note that this relies on boxes being completely degenerate if
	 * they are degenerate at all.  All member functions preserve this
	 * invariant.
	 */
	bool isEmpty() const;

	//@}


	/**
	 * @name Bounds accessor methods
	 */
	//@{

	/**
	 * @brief Set bounds.
	 *
	 * Sets the corners of the box.
	 *
	 * @deprecated
	 */
	vgDEPRECATED( void	setBounds(
		float xmin, float ymin, float zmin,
		float xmax, float ymax, float zmax) );

	/**
	 * @brief Set bounds.
	 *
	 * Sets the corners of the box.
	 */
	void setBounds( const Vec3f& min, const Vec3f& max);

	/**
	 * @brief Get bounds.
	 *
	 * Gets the corners of the box.
	 */
	void getBounds(
		float& xmin, float& ymin, float& zmin,
		float& xmax, float& ymax, float& zmax) const;

	/**
	 * @brief Get bounds.
	 *
	 * Gets the corners of the box.
	 */
	void getBounds( Vec3f& min, Vec3f& max ) const;
	//@}


	/**
	 * @name Transformation accessors
	 */
	//@{

	/**
	 * @brief Transforms Box3f.
	 *
	 * Transforms box by matrix, enlarging box to contain result.
	 *
	 * Clever method courtesy of Graphics Gems, pp. 548-550.
	 *
	 * This works for projection matrices as well as simple affine
	 * transformations.  Coordinates of the box are rehomogenized if there
	 * is a projection matrix.
	 */
	void	transform( const MatrixR& m);
	//@}


	/**
	 * @name Extends this box
	 *
	 *  Extends this box(if necessary) to contain the specified object(point or other box)
	 */
	//@{

	/**
	 * @brief Extends Box3f (if necessary) to contain given 3D point.
	 */
	void	extendBy( const Vec3f& pt );

	/**
	 * @brief Extends Box3f (if necessary) to contain given Box3f.
	 */
	void	extendBy( const Box3f& bb );
	//@}


	/**
	 * @name Intersection methods
	 */
	//@{

	/**
	 * @brief Returns \c true if intersection of given point and Box3f is not empty.
	 */
	bool	intersect( const Vec3f& pt ) const;

	/**
	 * @brief Returns \c true if intersection of given Box3f and Box3f is not empty.
	 */
	bool	intersect( const Box3f& bb ) const;
	//@}


	/**
	 * @name Some useful computing methods
	 */
	//@{

	/**
	 * @brief Finds the extent of a box along a particular direction.
	 *
	 * The span is the total distance the box occupies along a given direction. The total
	 * distance is returned in the form of a minimum and maximum distance from the origin 
	 * of each of the corners of the box along the given direction. The difference between
	 * these two values is the span.
	 */
	void	getSpan( const Vec3f& direction, float& dMin, float& dMax) const;

	/**
	 * @brief Returns true if bounding box is completely outside the
	 * view-volume defined by the model+view+projection matrix given.
	 *
	 * "cullBits" keeps track of which view-volume clipping planes the
	 * box is completely inside of; if a 'parent' bounding box of this
	 * bounding box was found to be completely inside the left/right
	 * clipping planes, the low bit of cullBits will be set to zero,
	 * and this routine will not test this box against those planes.
	 * When cullBits is zero, it is a waste of time to call this
	 * function!  Before calling this the first time, set cullBits to 7.
	 *
	 * @todo documentation of cullBits.
	 */
	bool	outside(const MatrixR& MVP, int32& cullBits) const;

	/**
	 * @brief Returns the closest point on the box to the given point.
	 *
	 * Returns the point on the center of the Z face if passed the center.
	 */
	const Vec3f getClosestPoint(const Vec3f& point);
	//@}


	/**
	 * @name Volume accessors
	 */
	//@{

	/**
	 * @brief Checks if the box has volume, i.e. all three dimensions have positive size.
	 *
	 * @return Returns \c true if all three dimensions of the box have positive size,
	 * and \c false otherwise.
	 */
	bool	hasVolume() const;

	/**
	 * @brief Gives the volume of the box (0 for an empty box).
	 *
	 * @return Returns the volume of the box.
	 */
	float	getVolume() const;
	//@}


	/**
	 * @name Comparison methods
	 *
	 * @todo equals(), notEquals()
	 */
	//@{

	/**
	 * @brief Equality comparison.
	 */
	bool	operator ==( const Box3f& b2 ) const;

	/**
	 * @brief Difference comparison.
	 */
	bool	operator !=( const Box3f& b2 ) const;
	//@}

protected:

	/**
	 * @name Helper methods
	 */
	//@{

	/**
	 * Given a range in object space, find the minimum or maximum for the
	 * X,Y,Z or W coordinates in the transformed space.
	 * 3 multiplies, 3 adds, 3 comparisons/branches.
	 * Reverse min and max for the opposite test...
	 *
	 * @todo Must be in another utility class.
	 */
	static inline float minExtreme( const Vec3f &min, const Vec3f &max, 
		const MatrixR &MVP, int32 whichCoord);
	
	static inline int32 quadrant( const float x, const float y );

	static int32 findQuadrant( float x, float y, float z,
		int32 n, const MatrixR  &MVP );
	//@}

	/**
	 * @brief Minimum point.
	 */
	Vec3f	m_min;

	/**
	 * @brief Maximum point.
	 */
	Vec3f	m_max;
};



/**
 * @brief 3D box class with an associated transformation matrix.
 *
 * A 3D box with an arbitrary transformation applied.  This class is useful when
 * a box will be transformed frequently; if an Box3f is used for this
 * purpose it will expand each time it is transformed in order to keep itself
 * axis-aligned.  Transformations can be accumulated on an XfBox3f without 
 * expanding the box, and after all transformations have been done, the box can
 * be expanded to an axis-aligned box if necessary.
 * 
 * @ingroup Geometry
 */
struct VGM_API XfBox3f : private Box3f
{
	/**
	 * @name Constructors and destructor
	 */
	//@{

	/**
	 * @copydoc Box3f::Box3f()
	 */
	XfBox3f();

	/**
	 * @copydoc Box3f::Box3f(float,float,float,float,float,float)
	 */
	vgDEPRECATED( XfBox3f(	float xmin, float ymin, float zmin,
							float xmax, float ymax, float zmax ) );

	/**
	 * @copydoc Box3f::Box3f(const Vec3f&,const Vec3f&)
	 */
	XfBox3f( const Vec3f& min, const Vec3f& max );

	/**
	 * @brief Constructor given Box3f.
	 */
	XfBox3f( const Box3f& box );

	/**
	 * @brief Destructor
	 */
	~XfBox3f();
	//@}


	/**
	 * @name Bounding box accessors
	 */
	//@{

	/**
	 * @remark Take care of transformation on the box
	 */
	const Vec3f getCenter() const;

	vgDEPRECATED( void getOrigin ( float& originX, float& originY, float&originZ) const );
	const vgm::Vec3f getOrigin() const;

	vgDEPRECATED( void getSize( float& sizeX, float& sizeY, float& sizeZ) const );
	const vgm::Vec3f getSize() const;

	void setInvalid( void );
	static const Box3f getInvalid();
	const bool isInvalid( void ) const;
	const bool isValid( void ) const;

	void	makeEmpty();
	bool	isEmpty() const;
	//@}


	/**
	 * @name Bounds accessor methods
	 */
	//@{

	void	setBounds(
		float xmin, float ymin, float zmin,
		float xmax, float ymax, float zmax );

	void	setBounds( const Vec3f& min, const Vec3f& max);

	void	getBounds(
		float& xmin, float& ymin, float& zmin,
		float& xmax, float& ymax, float& zmax ) const;

	void	getBounds( Vec3f& min, Vec3f& max ) const;
	//@}


	/**
	 * @name Transformation accessors
	 */
	//@{

	void	transform( const MatrixR& m );

	/**
	 * @brief Set the transformation on the box.
	 *
	 * This is careful about non-invertable transformations.
	 */
	void	setTransform( const MatrixR& m );

	/**
	 * @brief Get the transformation on the box.
	 */
	const MatrixR&	getTransform() const;

	/**
	 * @brief Get the inverse transformation on the box.
	 */
	const MatrixR&	getInverse() const;
	//@}


	/**
	 * @name Extends this box
	 *
	 * Extends this box (if necessary) to contain the specified object(point or other box)
	 */
	//@{

	/**
	 * @brief Extends Box3f (if necessary) to contain given 3D point.
	 *
	 * Extends the box (if necessary) to contain the given 3D point.  If the
	 * box has had a non-identity transformation applied using the
	 * setTransform() method, the point is assumed to be in the transformed
	 * space.  For example, the following code sequence :
	 * \code XfBox3f bbox;
	 * bbox.extendBy(Vec3f(0,0,0));
	 * Matrix trans; 
	 * trans.setTranslate(Vec3f(1,1,1));
	 * bbox.setTransform(trans);
	 * bbox.extendBy(Vec3f(0,0,0));
	 * will result in a bounding box extending from (-1,-1,-1) to
	 * (0,0,0) in bbox'es local (untransformed) space.
	 * \endcode
	 */
	void	extendBy( const Vec3f& pt );

	/**
	 * @brief Extends XfBox3f (if necessary) to contain given Box3f.
	 *
	 * If the box has had a non-identity transformation applied using the
	 * \c setTransform() method, the given Box3f is assumed to be in the
	 * transformed space.
	 */
	void	extendBy( const Box3f& bb );

	/**
	 * @brief Extends Box3f (if necessary) to contain given XfBox3f.
	 */
	void	extendBy( const XfBox3f& bb );
	//@}


	/**
	 * @name Intersection methods
	 */
	//@{

	/**
	 * @brief Returns \c true if intersection of given point and XfBox3f is not empty.
	 */
	bool	intersect( const Vec3f& pt ) const;

	/**
	 * @brief Returns \c true if intersection of given Box3f and XfBox3f is not empty.
	 */
	bool	intersect( const Box3f& bb ) const;
	//@}


	/**
	 * @name Volume accessors
	 */
	//@{

	bool	hasVolume() const;

	float	getVolume() const;
	//@}


	/**
	 * @name Some useful computing methods
	 */
	//@{
	void	getSpan( const Vec3f &direction,
					 float& dMin, float& dMax) const;

	/**
	 * @brief Projects an XfBox3f to an Box3f.
	 */
	Box3f	project() const;
	//@}


	/**
	 * @name Comparison methods
	 */
	//@{

	/**
	 * @brief Equality comparison.
	 */
	bool	operator ==( const XfBox3f& b2 ) const;

	/**
	 * @brief Difference comparison.
	 */
	bool	operator !=( const XfBox3f& b2 ) const;
	//@}

private:

	/**
	 * @name These are incorrect for XfBox3f, so we hide them.
	 */
	//@{
	const Vec3f&	getMin() const	{ return Box3f::getMin(); }
	const Vec3f&	getMax() const	{ return Box3f::getMax(); }
	//@}

	/**
	 * @name The box is transformed by this xform.
	 *
	 * We'll mark inverse[0][0] with numeric_limits<float>::max() (max floating point
	 * value) as special value to indicate degenerate transform.
	 */
	//@{
	MatrixR		xform;
	MatrixR		xformInv;
	//@}
};

//@}

} // namespace vgm

#endif // #ifndef _VGM_BOX_HPP
