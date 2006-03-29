// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DRAWSTYLE_HPP
#define _VGD_NODE_DRAWSTYLE_HPP

#include "vgd/vgd.hpp"

#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Drawing style definition node
 * 
 * The DrawStyle node specifies the current drawing style (flat, smooth, hidden-lines...) for all subsequent shape nodes
 * in a scene graph and if normals, orientation or bounding box must be render.
 *
 * New field added by this node :
 * 
 * - PAFInt32	\c [shape]	= SMOOTH\n
 *		Sets the drawing style of Shape. Choose one value among NONE, POINT, FLAT, SMOOTH, WIREFRAME, HIDDEN_LINE,
 * 	FLAT_HIDDEN_LINE, SMOOTH_HIDDEN_LINE or NEIGHBOUR.
 * 
 * - PAFFloat	\c [normalLength]	= 0.f\n
 * 	Sets this field to zero to disable normals rendering (or a better is to remove this field). 
 * 	Others values indicates the length of the rendered normals.
 * 
 * - PAFBool	\c [showOrientation] = false\n
 * 	Sets the field to true to render an half-arrow on each edge of triangles in order to show the triangle 
 * 	orientation (CW or CCW). The center of each triangle is drawn with a big point. A red arrow is drawn on the first
 * 	edge, a green arrow on the second and a blue arrow on the third.
 * 
 * - PAFInt32	\c [boundingBox]	= NO_BOUNDING_BOX\n
 * 	Sets the bounding box drawing style. Choose one value among NO_BOUNDING_BOX, OBJECT_SPACE, AA_OBJECT_SPACE or 
 *		OBJECT_AND_AA_OBJECT_SPACE.
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API DrawStyle : public vgd::node::SingleAttribute
{
	META_NODE_HPP( DrawStyle );


	/**
	 * @name Accessors to field shape.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c shape parameter.
	 */
	typedef enum
	{
		SHAPE = 1
	} ShapeParameterType;

	/**
	 * @brief Typedef for the \c shape parameter value.
	 */
	typedef enum
	{
		NONE		= 1,
		POINT,
		FLAT,
		SMOOTH,
		WIREFRAME,
		HIDDEN_LINE,
		FLAT_HIDDEN_LINE,
		SMOOTH_HIDDEN_LINE,
		NEIGHBOUR,
		DEFAULT_SHAPE = SMOOTH
	} ShapeValueType;

	/**
	 * @brief Typedef for the \c shape field.
	 */	
	typedef vgd::field::TPairAssociativeField< ShapeParameterType, ShapeValueType > FShapeType;

	/**
	 * @brief Gets the \c shape value.
	 */
	bool			getShape( ShapeValueType& value ) const;

	/**
	 * @brief Sets the \c shape value.
	 */
	void 			setShape( ShapeValueType value );
	
	/**
	 * @brief Erase the \c shape value.
	 */
	void 			eraseShape();
	//@}



	/**
	 * @name Accessors to field normalLength.
	 */
	//@{
	
	/**
	 * @brief Enumeration of the \c normalLength parameter.
	 */
	typedef enum
	{
		NORMAL_LENGTH = 1
	} NormalLengthParameterType;

	/**
	 * @brief Typedef for the \c normalLength parameter value.
	 */
	typedef float NormalLengthValueType;

	/**
	 * @brief Typedef for the \c normalLength field.
	 */	
	typedef vgd::field::TPairAssociativeField< NormalLengthParameterType, NormalLengthValueType > FNormalLengthType;

	/**
	 * @brief Gets the \c normalLength value.
	 */
	bool			getNormalLength( float/*NormalLengthValueType*/& value ) const;

	/**
	 * @brief Sets the \c normalLength value.
	 */
	void 			setNormalLength( float/*NormalLengthValueType*/ value );
	
	/**
	 * @brief Erase the \c normalLength value.
	 */
	void 			eraseNormalLength();
	//@}



	/**
	 * @name Accessors to field showOrientation.
	 */
	//@{
	
	/**
	 * @brief Enumeration of the \c showOrientation parameter.
	 */
	typedef enum
	{
		SHOW_ORIENTATION = 1
	} ShowOrientationParameterType;

	/**
	 * @brief Typedef for the \c showOrientation parameter value.
	 */
	typedef bool ShowOrientationValueType;

	/**
	 * @brief Typedef for the \c showOrientation field.
	 */	
	typedef vgd::field::TPairAssociativeField< ShowOrientationParameterType, ShowOrientationValueType > FShowOrientationType;

	/**
	 * @brief Gets the \c showOrientation value.
	 */
	bool			getShowOrientation( bool/*ShowOrientationValueType*/& value ) const;

	/**
	 * @brief Sets the \c showOrientation value.
	 */
	void 			setShowOrientation( bool/*ShowOrientationValueType*/ value );
	
	/**
	 * @brief Erase the \c showOrientation value.
	 */
	void 			eraseShowOrientation();
	//@}



	/**
	 * @name Accessors to field boundingBox.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c boundingBox parameter.
	 */
	typedef enum
	{
		BOUNDING_BOX = 1
	} BoundingBoxParameterType;

	/**
	 * @brief Typedef for the \c boundingBox parameter value.
	 */
	typedef enum
	{
		NO_BOUNDING_BOX	= 1,
		OBJECT_SPACE,
		AA_OBJECT_SPACE,
		OBJECT_AND_AA_OBJECT_SPACE,
		DEFAULT_BOUNDING_BOX = NONE
	} BoundingBoxValueType;

	/**
	 * @brief Typedef for the \c boundingBox field.
	 */	
	typedef vgd::field::TPairAssociativeField< BoundingBoxParameterType, BoundingBoxValueType > FBoundingBoxType;

	/**
	 * @brief Gets the \c boundingBox value.
	 */
	bool			getBoundingBox( BoundingBoxValueType& value ) const;

	/**
	 * @brief Sets the \c boundingBox value.
	 */
	void 			setBoundingBox( BoundingBoxValueType value );
	
	/**
	 * @brief Erase the \c boundingBox value.
	 */
	void 			eraseBoundingBox();
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c shape.
	 * 
	 * @return the name of field \c shape.
	 */
	static const std::string getFShape( void );
	
	/**
	 * @brief Returns the name of field \c normalLength.
	 * 
	 * @return the name of field \c normalLength.
	 */
	static const std::string getFNormalLength( void );

	/**
	 * @brief Returns the name of field \c showOrientation.
	 * 
	 * @return the name of field \c showOrientation.
	 */
	static const std::string getFShowOrientation( void );	
	
	/**
	 * @brief Returns the name of field \c boundingBox.
	 * 
	 * @return the name of field \c boundingBox.
	 */
	static const std::string getFBoundingBox( void );		
	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	DrawStyle( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_DRAWSTYLE_HPP
