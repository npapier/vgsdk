// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_IBOUNDINGBOX_H
#define _VGD_NODE_IBOUNDINGBOX_H

#include "vgd/vgd.hpp"

#include <vgm/Box.hpp>
#include <vgm/Matrix.hpp>



namespace vgd
{
	
namespace node
{



struct VGD_API IBoundingBox
{
	/**
	 * @brief Compute the bounding box an set the associated transformation matrix.
	 *
	 * @remarks You should only compute/update the bounding box if necessary.
	 *
	 * @remarks Compute only if bounding box dirty flag is invalidate (i.e. Mesh has changed).
	 *
	 * @return true if bounding box has been computed, false if bounding box has been already valid or simply transformed
	 * by the matrix \c transformation.
	 */
	virtual bool computeBoundingBox( const vgm::MatrixR& transformation )=0;



	/**
	 * @name Bounding box accessors.
	 */
	//@{
	
	/**
	 * @brief Get the bounding box.
	 * 
	 * @pre isBoundingBoxValid() returns true.
	 * 
	 * @return the bounding box.
	 */
	const vgm::Box3f& getBoundingBox() const;

	/**
	 * @brief Get the bounding box transformed by the matrix.
	 * 
	 * @pre isBoundingBoxValid() returns true.
	 * 
	 * @return the bounding box with the matrix transformation.
	 * 
	 * @remarks Use project() on the returned bounding box for getting the enlarged axis aligned bounding box that 
	 * contains the transformed bounding box.
	 */
	vgm::XfBox3f getXfBoundingBox() const;

	/**
	 * @brief Gets the bounding box transformed by the matrix.
	 * 
	 * @pre isBoundingBoxValid() returns true.
	 * 
	 * @return the bounding box transformed by the matrix (same as getXfBoundingBox()->project()).
	 */
	vgm::Box3f	getProjectXfBoundingBox() const;

	/**
	 * @brief Returns true if the bounding box is valid.
	 * 
	 * The bounding box is valid if method computeBoundingBox() has been called and bounding box has not been invalidated since.
	 */
	virtual bool isBoundingBoxValid() const=0;

	/**
	 * @brief Invalidate/validate the bounding box.
	 * 
	 * @param bInvalidate	true to invalidate dirty flag bounding box, false to validate it.
	 */
	virtual void invalidateBoundingBox( bool bInvalidate = true )=0;
	//@}



protected:

	vgm::Box3f		m_boundingBox;
	
	vgm::MatrixR	m_transformation;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_IBOUNDINGBOX_H
