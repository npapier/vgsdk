// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_MULTIPLEINSTANCES_HPP
#define _VGD_NODE_MULTIPLEINSTANCES_HPP

#include "vgd/field/MatrixR.hpp"
#include "vgd/field/NodeShp.hpp"
#include "vgd/node/Shape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Instanciated the same object multiple times in the scene
 *
 * The object, defined by the shape field, is instanciated once per matrix available in the field named matrix. The matrix is concatenated to the current geometrical transformation matrix. This allows the user to put multiple copies of the same data in different locations easily and efficiently. @todo really implements vgd::node::IBoundingBox interface. useful ? 
 *
 * New fields defined by this node :
 * - SFNodeShp \c shape = empty<br>
 *   The object to instanciate multiple times.<br>
 *<br>
 * - MFMatrixR \c matrix = empty<br>
 *   The array of matrices used to transform the object in different locations<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API MultipleInstances : public vgd::node::Shape
{
	/**
	 * @name Factories
	 */
	//@{

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values
	 */
	static vgd::Shp< MultipleInstances > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< MultipleInstances > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< MultipleInstances > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field shape
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c shape.
	 */
	typedef vgd::node::NodeShp ShapeValueType;

	/**
	 * @brief Type definition of the field named \c shape
	 */
	typedef vgd::field::TSingleField< ShapeValueType > FShapeType;


	/**
	 * @brief Gets the value of field named \c shape.
	 */
	const ShapeValueType getShape() const;

	/**
	 * @brief Sets the value of field named \c shape.
	 */
	void setShape( const ShapeValueType value );

	//@}



	/**
	 * @name Accessors to field matrix
	 *
	 * @todo getMatrix( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c matrix.
	 */
	typedef vgm::MatrixR MatrixValueType;

	/**
	 * @brief Type definition of the field named \c matrix
	 */
	typedef vgd::field::TMultiField< MatrixValueType > FMatrixType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c matrix.
	 */
	vgd::field::EditorRO< FMatrixType > getMatrixRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c matrix.
	 */
	vgd::field::EditorRW< FMatrixType > getMatrixRW();

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c shape.
	 *
	 * @return the name of field \c shape.
	 */
	static const std::string getFShape( void );

	/**
	 * @brief Returns the name of field \c matrix.
	 *
	 * @return the name of field \c matrix.
	 */
	static const std::string getFMatrix( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



	bool computeBoundingBox( const vgm::MatrixR& transformation );	///< overridden method

	bool isBoundingBoxValid() const;								///< overridden method

	void invalidateBoundingBox( bool bInvalidate = true );			///< overridden method



	/**
	 * @name Constructor and initializer methods
	 */
	//@{

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}

protected:
	/**
	 * @brief Default constructor
	 */
	MultipleInstances( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , MultipleInstances );
private:
	static const vgd::basic::RegisterNode<MultipleInstances> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_MULTIPLEINSTANCES_HPP
