// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DRAWSTYLE_HPP
#define _VGD_NODE_DRAWSTYLE_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Drawing style definition node
 *
 * The DrawStyle node specifies the current drawing style (flat, smooth, hidden-lines...) for all subsequent shape nodes in a scene graph and if normals, orientation or bounding box must be render. 
 *
 * New fields defined by this node :
 * - OFBool \c [showOrientation] = (false)<br>
 *   Sets the field to true to render an half-arrow on each edge of triangles in order to show the triangle orientation (CW or CCW). The center of each triangle is drawn with a big point. A red arrow is drawn on the first edge, a green arrow on the second and a blue arrow on the third.<br>
 *<br>
 * - OFEnum \c [boundingBox] = (NO_BOUNDING_BOX)<br>
 *   Sets the bounding box drawing style. Choose one value among NO_BOUNDING_BOX, OBJECT_SPACE, AA_OBJECT_SPACE or OBJECT_AND_AA_OBJECT_SPACE.<br>
 *<br>
 * - OFEnum \c [shape] = (SMOOTH)<br>
 *   Sets the drawing style of Shape. Choose one value among NONE, POINT, FLAT, SMOOTH, WIREFRAME, HIDDEN_LINE, FLAT_HIDDEN_LINE, SMOOTH_HIDDEN_LINE or NEIGHBOUR.<br>
 *<br>
 * - OFFloat \c [normalLength] = (0.f)<br>
 *   Sets this field to zero to disable normals rendering (or a better way is to remove this field). Others values indicates the length of the rendered normals.<br>
 *<br>
 * - OFFloat \c [tangentLength] = (0.f)<br>
 *   Sets this field to zero to disable tangents rendering (or a better way is to remove this field). Others values indicates the length of the rendered tangents.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API DrawStyle : public vgd::node::SingleAttribute
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
	static vgd::Shp< DrawStyle > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< DrawStyle > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< DrawStyle > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field showOrientation
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c showOrientation.
	 */
	typedef bool ShowOrientationValueType;

	/**
	 * @brief The default value of field named \c showOrientation.
	 */
	static const ShowOrientationValueType DEFAULT_SHOWORIENTATION;

	/**
	 * @brief Type definition of the field named \c showOrientation
	 */
	typedef vgd::field::TOptionalField< ShowOrientationValueType > FShowOrientationType;


	/**
	 * @brief Gets the value of field named \c showOrientation.
	 */
	const bool getShowOrientation( ShowOrientationValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c showOrientation.
 	 */
	void setShowOrientation( const ShowOrientationValueType& value );

	/**
	 * @brief Erases the field named \c showOrientation.
	 */
	void eraseShowOrientation();

	/**
	 * @brief Tests if the value of field named \c showOrientation has been initialized.
	 */
	const bool hasShowOrientation() const;
	//@}



	/**
	 * @name Accessors to field boundingBox
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		AA_OBJECT_SPACE = 279,	///< 
		NO_BOUNDING_BOX = 277,	///< 
		OBJECT_AND_AA_OBJECT_SPACE = 280,	///< 
		OBJECT_SPACE = 278,	///< 
		DEFAULT_BOUNDINGBOX = NO_BOUNDING_BOX	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct BoundingBoxValueType : public vgd::field::Enum
	{
		BoundingBoxValueType()
		{}

		BoundingBoxValueType( const int v )
		: vgd::field::Enum(v)
		{}

		BoundingBoxValueType( const BoundingBoxValueType& o )
		: vgd::field::Enum(o)
		{}

		BoundingBoxValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 277 );
			retVal.push_back( 278 );
			retVal.push_back( 279 );
			retVal.push_back( 280 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "NO_BOUNDING_BOX" );
			retVal.push_back( "OBJECT_SPACE" );
			retVal.push_back( "AA_OBJECT_SPACE" );
			retVal.push_back( "OBJECT_AND_AA_OBJECT_SPACE" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c boundingBox
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FBoundingBoxType;


	/**
	 * @brief Gets the value of field named \c boundingBox.
	 */
	const bool getBoundingBox( BoundingBoxValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c boundingBox.
 	 */
	void setBoundingBox( const BoundingBoxValueType& value );

	/**
	 * @brief Erases the field named \c boundingBox.
	 */
	void eraseBoundingBox();

	/**
	 * @brief Tests if the value of field named \c boundingBox has been initialized.
	 */
	const bool hasBoundingBox() const;
	//@}



	/**
	 * @name Accessors to field shape
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		SMOOTH_HIDDEN_LINE = 275,	///< 
		FLAT = 270,	///< 
		HIDDEN_LINE = 273,	///< 
		POINT = 269,	///< 
		FLAT_HIDDEN_LINE = 274,	///< 
		WIREFRAME = 272,	///< 
		SMOOTH = 271,	///< 
		NO_SHAPE = 268,	///< 
		NEIGHBOUR = 276,	///< 
		DEFAULT_SHAPE = SMOOTH	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ShapeValueType : public vgd::field::Enum
	{
		ShapeValueType()
		{}

		ShapeValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ShapeValueType( const ShapeValueType& o )
		: vgd::field::Enum(o)
		{}

		ShapeValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 268 );
			retVal.push_back( 269 );
			retVal.push_back( 270 );
			retVal.push_back( 271 );
			retVal.push_back( 272 );
			retVal.push_back( 273 );
			retVal.push_back( 274 );
			retVal.push_back( 275 );
			retVal.push_back( 276 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "NO_SHAPE" );
			retVal.push_back( "POINT" );
			retVal.push_back( "FLAT" );
			retVal.push_back( "SMOOTH" );
			retVal.push_back( "WIREFRAME" );
			retVal.push_back( "HIDDEN_LINE" );
			retVal.push_back( "FLAT_HIDDEN_LINE" );
			retVal.push_back( "SMOOTH_HIDDEN_LINE" );
			retVal.push_back( "NEIGHBOUR" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c shape
	 */
	typedef vgd::field::TOptionalField< vgd::field::Enum > FShapeType;


	/**
	 * @brief Gets the value of field named \c shape.
	 */
	const bool getShape( ShapeValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c shape.
 	 */
	void setShape( const ShapeValueType& value );

	/**
	 * @brief Erases the field named \c shape.
	 */
	void eraseShape();

	/**
	 * @brief Tests if the value of field named \c shape has been initialized.
	 */
	const bool hasShape() const;
	//@}



	/**
	 * @name Accessors to field normalLength
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c normalLength.
	 */
	typedef float NormalLengthValueType;

	/**
	 * @brief The default value of field named \c normalLength.
	 */
	static const NormalLengthValueType DEFAULT_NORMALLENGTH;

	/**
	 * @brief Type definition of the field named \c normalLength
	 */
	typedef vgd::field::TOptionalField< NormalLengthValueType > FNormalLengthType;


	/**
	 * @brief Gets the value of field named \c normalLength.
	 */
	const bool getNormalLength( NormalLengthValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c normalLength.
 	 */
	void setNormalLength( const NormalLengthValueType& value );

	/**
	 * @brief Erases the field named \c normalLength.
	 */
	void eraseNormalLength();

	/**
	 * @brief Tests if the value of field named \c normalLength has been initialized.
	 */
	const bool hasNormalLength() const;
	//@}



	/**
	 * @name Accessors to field tangentLength
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tangentLength.
	 */
	typedef float TangentLengthValueType;

	/**
	 * @brief The default value of field named \c tangentLength.
	 */
	static const TangentLengthValueType DEFAULT_TANGENTLENGTH;

	/**
	 * @brief Type definition of the field named \c tangentLength
	 */
	typedef vgd::field::TOptionalField< TangentLengthValueType > FTangentLengthType;


	/**
	 * @brief Gets the value of field named \c tangentLength.
	 */
	const bool getTangentLength( TangentLengthValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c tangentLength.
 	 */
	void setTangentLength( const TangentLengthValueType& value );

	/**
	 * @brief Erases the field named \c tangentLength.
	 */
	void eraseTangentLength();

	/**
	 * @brief Tests if the value of field named \c tangentLength has been initialized.
	 */
	const bool hasTangentLength() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

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
	 * @brief Returns the name of field \c tangentLength.
	 *
	 * @return the name of field \c tangentLength.
	 */
	static const std::string getFTangentLength( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



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
	DrawStyle( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , DrawStyle );
private:
	static const vgd::basic::RegisterNode<DrawStyle> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_DRAWSTYLE_HPP
