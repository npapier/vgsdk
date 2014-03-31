// VGSDK - Copyright (C) 2013, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_TRIANGLE_HPP
#define _VGM_TRIANGLE_HPP

#include "vgm/vgm.hpp"
#include "vgm/Vector.hpp"



namespace vgm
{



/**
 * @brief Represents a triangle ABC in 3D space
 * 
 * @ingroup Geometry
 */
struct VGM_API Triangle
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
	Triangle();

	/**
	 * @brief Construct a triangle from three points
	 */
	Triangle( const Vec3f& A, const Vec3f& B, const Vec3f& C );
	//@}


	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Sets the triangle from three points
	 */
	void setValue( const Vec3f& A, const Vec3f& B, const Vec3f& C );


	/**
	 * @brief Gets the first point of the triangle
	 */
	const Vec3f& A() const;
	const Vec3f& getA() const;

	/**
	 * @brief Sets the first point of the triangle
	 */
	void setA( const Vec3f& A );

	/**
	 * @brief Get the second point of the triangle
	 */
	const Vec3f& B() const;
	const Vec3f& getB() const;

	/**
	 * @brief Sets the second point of the triangle
	 */
	void setB( const Vec3f& B );


	/**
	 * @brief Get the third point of the triangle
	 */
	const Vec3f& C() const;
	const Vec3f& getC() const;

	/**
	 * @brief Sets the third point of the triangle
	 */
	void setC( const Vec3f& C );

	//@}


	/**
	 * @name Helpers
	 */
	//@{

	/**
	 * @brief Returns B()-A()
	 */
	const Vec3f AB() const;

	/**
	 * @brief Returns C()-B()
	 */
	const Vec3f BC() const;

	/**
	 * @brief Returns A()-C()
	 */
	const Vec3f CA() const;
	//@}


	/**
	 * @name Some useful computing methods
	 */
	//@{

	/**
	 * @brief Get the normal  of the triangle
	 */
	const Vec3f getNormal() const;

	//@}



	/**
	 * @name Intersection methods
	 */
	//@{

	//@}

protected:

	/**
	 * @name Internal representation
	 */
	//@{
	Vec3f m_abc[3];
	//@}
};


/**
 * @brief Represents a triangle ABC in 3D space and a point P defined using barycentric coordinates
 * 
 * @ingroup Geometry
 */
struct VGM_API TriangleP : public Triangle
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
	TriangleP();

	/**
	 * @brief Construct a triangle from three points and the barycentric coordinates of a point P
	 */
	TriangleP( const Vec3f& A, const Vec3f& B, const Vec3f& C, const Vec3f& P );
	//@}


	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Sets the triangle from three points and the barycentric coordinates of a point P
	 */
	void setValue( const Vec3f& A, const Vec3f& B, const Vec3f& C, const Vec3f& P );


	/**
	 * @brief Gets the barycentric coordinates of the point P
	 */
	const Vec3f& P() const;
	const Vec3f& getP() const;

	/**
	 * @brief Sets the barycentric coordinates of the point P
	 *
	 * @see computeCartesian(const Vec3f&) for additionnal informations about barycentric coordinates of P.
	 */
	void setP( const Vec3f& P );

	//@}


	/**
	 * @name Some useful computing methods
	 */
	//@{

	/**
	 * @brief Computes the cartesian coordinates of a point using its barycentric coordinates
	 *
	 * @param baryCoord		the given barycentric coordinates of the point
	 * @return the cartesian coordinates of the given point
	 *
	 * @remark Two forms of barycentric coordinates are accepted. The first one uses barycentric coordinates of dimension 3 and returns baryCoord[0] * A + baryCoord[1] * B + baryCoord[2] * C.
	 * The second one uses barycentric coordinates of dimension 2 (i.e. baryCoord[2] == std::numeric_limits<float>::max()) and returns (baryCoord[0] * AB + baryCoord[1] * BC).
	 */
	const Vec3f computeCartesian( const Vec3f& baryCoord ) const;

	/**
	 * @brief Computes the cartesian coordinates of P using its barycentric coordinates
	 *
	 * @return the cartesian coordinates of the point P
	 */
	const Vec3f computeCartesian() const;

	//@}


private:
	/**
	 * @name Internal representation
	 */
	//@{
	Vec3f m_p;
	//@}
};


/**
 * @brief Represents a triangle ABC in 3D space, a point P defined using barycentric coordinates and three indices
 * 
 * @ingroup Geometry
 */
struct VGM_API TriangleExt : public TriangleP
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
	TriangleExt();

	/**
	 * @brief Construct a triangle from three points, the barycentric coordinates of a point P and three indices.
	 */
	TriangleExt( const Vec3f& A, const Vec3f& B, const Vec3f& C, const Vec3f& P, const Vec3i& indicesOfABC );
	//@}


	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Sets the triangle from three points and the barycentric coordinates of a point P and three indices.
	 */
	void setValue( const Vec3f& A, const Vec3f& B, const Vec3f& C, const Vec3f& P, const Vec3i& indicesOfABC );


	/**
	 * @brief Gets the indices of points ABC
	 */
	const Vec3i& indices() const;
	const Vec3i& getIndices() const;

	/**
	 * @brief Sets the indices of points ABC
	 */
	void setIndices( const Vec3i& indices );

	//@}


private:
	/**
	 * @name Internal representation
	 */
	//@{
	Vec3i m_indices;
	//@}
};


} // namespace vgm

#endif // #ifndef _VGM_TRIANGLE_HPP
