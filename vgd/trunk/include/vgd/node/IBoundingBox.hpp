// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_IBOUNDINGBOX_HPP
#define _VGD_NODE_IBOUNDINGBOX_HPP

#include "vgd/vgd.hpp"

#include <vgm/Box.hpp>
#include <vgm/Matrix.hpp>



namespace vgd
{
	
namespace node
{



/**
 * @brief Interface for node with a bounding box.
 * 
 * Interface for node that contains a bounding box and a matrix that transformation the bounding box.
 */
struct VGD_API IBoundingBox
{
	/**
	 * @name Constructor/Destructor.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 * 
	 * @post getBoundingBox().isEmpty() and getTransformation().isIdentity()
	 */
	IBoundingBox();
	
	/**
	 * @brief Virtual destructor.
	 */
	virtual ~IBoundingBox();

	//@}



	/**
	 * @name Methods that must be implemented by derived classes.
	 */
	//@{

	/**
	 * @brief Upate the bounding box and its associated transformation matrix.
	 *
	 * @remarks You should only compute/update the bounding box if necessary. Compute only if bounding box dirty flag 
	 * is invalidate (i.e. Mesh has changed for Shape nodes, or for Group nodes when children have changed).
	 *
	 * @return true if bounding box has been computed, false if bounding box has been already valid or simply transformed
	 * by the matrix \c transformation.
	 */
	virtual bool computeBoundingBox( const vgm::MatrixR& transformation )=0;

	/**
	 * @brief Returns true if the bounding box is valid.
	 * 
	 * The bounding box is valid if method computeBoundingBox() has been called and bounding box has not been 
	 * invalidated since.
	 */
	virtual bool isBoundingBoxValid() const=0;

	/**
	 * @brief Invalidate/validate the bounding box.
	 * 
	 * @param bInvalidate	true to invalidate dirty flag bounding box, false to validate it.
	 */
	virtual void invalidateBoundingBox( bool bInvalidate = true )=0;
	
	//@}



	/**
	 * @name Bounding box accessors.
	 */
	//@{
	
	/**
	 * @brief Gets the bounding box.
	 * 
	 * @pre isBoundingBoxValid() returns true.
	 * 
	 * @return the bounding box.
	 */
	const vgm::Box3f& getBoundingBox() const;
	
	/**
	 * @brief Gets the transformation applied on the bounding box.
	 * 
	 * @pre isBoundingBoxValid() returns true.
	 * 
	 * @return a matrix.
	 */
	const vgm::MatrixR& getTransformation() const;

	/**
	 * @brief Sets the bounding box.
	 * 
	 * @param boundingBox	the new bounding box.
	 */
	void setBoundingBox( const vgm::Box3f& boundingBox );
	
	/**
	 * @brief Sets the transformation applied on the bounding box.
	 * 
	 * @param transformation	the matrix.
	 */
	void setTransformation( const vgm::MatrixR& transformation );
	
	/**
	 * @brief Reset the bounding box.
	 * 
	 * @post getBoundingBox().isEmpty() and getTransformation().isIdentity()
	 */
	void reset();
	
	//@}


	/**
	 * @name Bounding Box high level accessors.
	 */
	//@{

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

	//@}



protected:

	/**
	 * @brief The bounding box
	 */
	vgm::Box3f		m_boundingBox;
	
	/**
	 * @brief The matrix applied on the bounding box.
	 */
	vgm::MatrixR	m_transformation;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_IBOUNDINGBOX_HPP
