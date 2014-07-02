// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_VERTEXSHAPE_HPP
#define _VGD_NODE_VERTEXSHAPE_HPP

#include "vgd/field/Binding.hpp"
#include "vgd/field/Enum.hpp"
#include "vgd/field/Primitive.hpp"
#include "vgd/field/Uint.hpp"
#include "vgd/field/Vec3f.hpp"
#include "vgd/field/Vec4f.hpp"
#include "vgd/node/Shape.hpp"
#include "vgd/node/ITransformation.hpp"
#include "vgd/field/Float.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Base class for all vertex-based shape (geometry) nodes
 *
 * Summary of capabilities :\n 	- encapsulation of geometry/material specification.\n 	- bounding box.\n 	- applying transformation (matrix, translation and rotation) on vertices and normals.\n Fields that defined the geometry :\n 	- MFVec3f \c		vertex 		= empty\n 	- MFUint32 \c		vertexIndex	= empty\n 	- MFPrimitive \c	primitive	= empty\n Fields used by the lighting equation and by materials : \n 	- MFVec3f \c normal				= empty\n 	- MFVec3f \c tangent			= empty\n 	- MFVec4f \c color				= empty\n 	- MFVec2f \c texCoord			= empty\n 		texCoord is a "dynamic field", see createTexUnits()...\n Fields for defining bindings :\n 	- SFBinding \c normalBinding 			= BIND_OFF\n 	- SFBinding \c tangentBinding 			= BIND_OFF\n 	- SFBinding \c colorBinding 			= BIND_OFF\n 	- SFBinding \c texCoordBinding			= BIND_OFF\n 		texCoordBinding is a "dynamic field", see createTexUnits()...\n getDFBoundingBox() returns dirty flag that is invalidate when bounding box is invalidate and must be recomputed 
 *
 * New fields defined by this node :
 * - SFBinding \c normalBinding = vgd::node::Binding(vgd::node::BIND_OFF)<br>
 *<br>
 * - SFBinding \c tangentBinding = vgd::node::Binding(vgd::node::BIND_OFF)<br>
 *<br>
 * - SFBinding \c colorBinding = vgd::node::Binding(vgd::node::BIND_OFF)<br>
 *<br>
 * - SFEnum \c boundingBoxUpdatePolicy = (AUTOMATIC)<br>
 *<br>
 * - SFEnum \c deformableHint = (STATIC)<br>
 *   Specifies a symbolic constant indicating the usage of this shape. Choose one value among STATIC, DYNAMIC and STREAM.<br>
 *<br>
 * - MFVec3f \c vertex = vgm::Vec3f()<br>
 *<br>
 * - MFUint \c vertexIndex = empty<br>
 *<br>
 * - MFPrimitive \c primitive = vgd::node::Primitive()<br>
 *<br>
 * - MFVec3f \c normal = vgm::Vec3f()<br>
 *<br>
 * - MFVec3f \c tangent = vgm::Vec3f()<br>
 *<br>
 * - MFVec4f \c color = vgm::Vec4f()<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 * @ingroup g_texturingNodes
 */
struct VGD_API VertexShape : public vgd::node::Shape, public vgd::node::ITransformation
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
	static vgd::Shp< VertexShape > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< VertexShape > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< VertexShape > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field normalBinding
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c normalBinding.
	 */
	typedef vgd::node::Binding NormalBindingValueType;

	/**
	 * @brief Type definition of the field named \c normalBinding
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FNormalBindingType;


	/**
	 * @brief Gets the value of field named \c normalBinding.
	 */
	const NormalBindingValueType getNormalBinding() const;

	/**
	 * @brief Sets the value of field named \c normalBinding.
	 */
	void setNormalBinding( const NormalBindingValueType value );

	//@}



	/**
	 * @name Accessors to field tangentBinding
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tangentBinding.
	 */
	typedef vgd::node::Binding TangentBindingValueType;

	/**
	 * @brief Type definition of the field named \c tangentBinding
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FTangentBindingType;


	/**
	 * @brief Gets the value of field named \c tangentBinding.
	 */
	const TangentBindingValueType getTangentBinding() const;

	/**
	 * @brief Sets the value of field named \c tangentBinding.
	 */
	void setTangentBinding( const TangentBindingValueType value );

	//@}



	/**
	 * @name Accessors to field colorBinding
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c colorBinding.
	 */
	typedef vgd::node::Binding ColorBindingValueType;

	/**
	 * @brief Type definition of the field named \c colorBinding
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FColorBindingType;


	/**
	 * @brief Gets the value of field named \c colorBinding.
	 */
	const ColorBindingValueType getColorBinding() const;

	/**
	 * @brief Sets the value of field named \c colorBinding.
	 */
	void setColorBinding( const ColorBindingValueType value );

	//@}



	/**
	 * @name Accessors to field boundingBoxUpdatePolicy
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		AUTOMATIC = 468,	///< AUTOMATIC means that the bounding box of this vertex based shape would be automatically computed the first time and updated when field \c vertex is modified (see service ComputeBoundingBox in ::vge::service namespace).
		ONCE = 469,	///< DYNAMIC assumed to be a n-to-n update-to-draw. Means the geometry is specified every few frames.
		DEFAULT_BOUNDINGBOXUPDATEPOLICY = AUTOMATIC	///< AUTOMATIC means that the bounding box of this vertex based shape would be automatically computed the first time and updated when field \c vertex is modified (see service ComputeBoundingBox in ::vge::service namespace).
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct BoundingBoxUpdatePolicyValueType : public vgd::field::Enum
	{
		BoundingBoxUpdatePolicyValueType()
		{}

		BoundingBoxUpdatePolicyValueType( const int v )
		: vgd::field::Enum(v)
		{}

		BoundingBoxUpdatePolicyValueType( const BoundingBoxUpdatePolicyValueType& o )
		: vgd::field::Enum(o)
		{}

		BoundingBoxUpdatePolicyValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 468 );
			retVal.push_back( 469 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "AUTOMATIC" );
			retVal.push_back( "ONCE" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c boundingBoxUpdatePolicy
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FBoundingBoxUpdatePolicyType;


	/**
	 * @brief Gets the value of field named \c boundingBoxUpdatePolicy.
	 */
	const BoundingBoxUpdatePolicyValueType getBoundingBoxUpdatePolicy() const;

	/**
	 * @brief Sets the value of field named \c boundingBoxUpdatePolicy.
	 */
	void setBoundingBoxUpdatePolicy( const BoundingBoxUpdatePolicyValueType value );

	//@}



	/**
	 * @name Accessors to field deformableHint
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		DYNAMIC = 471,	///< DYNAMIC assumed to be a n-to-n update-to-draw. Means the geometry is specified every few frames.
		STATIC = 470,	///< STATIC assumed to be a 1-to-n update-to-draw. Means the geometry is specified once.
		STREAM = 472,	///< STREAM assumed to be a 1-to-1 update-to-draw. Means the geometry is specified for each frame.
		DEFAULT_DEFORMABLEHINT = STATIC	///< STATIC assumed to be a 1-to-n update-to-draw. Means the geometry is specified once.
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct DeformableHintValueType : public vgd::field::Enum
	{
		DeformableHintValueType()
		{}

		DeformableHintValueType( const int v )
		: vgd::field::Enum(v)
		{}

		DeformableHintValueType( const DeformableHintValueType& o )
		: vgd::field::Enum(o)
		{}

		DeformableHintValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 470 );
			retVal.push_back( 471 );
			retVal.push_back( 472 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "STATIC" );
			retVal.push_back( "DYNAMIC" );
			retVal.push_back( "STREAM" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c deformableHint
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FDeformableHintType;


	/**
	 * @brief Gets the value of field named \c deformableHint.
	 */
	const DeformableHintValueType getDeformableHint() const;

	/**
	 * @brief Sets the value of field named \c deformableHint.
	 */
	void setDeformableHint( const DeformableHintValueType value );

	//@}



	/**
	 * @name Accessors to field vertex
	 *
	 * @todo getVertex( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c vertex.
	 */
	typedef vgm::Vec3f VertexValueType;

	/**
	 * @brief Type definition of the field named \c vertex
	 */
	typedef vgd::field::TMultiField< VertexValueType > FVertexType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c vertex.
	 */
	vgd::field::EditorRO< FVertexType > getVertexRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c vertex.
	 */
	vgd::field::EditorRW< FVertexType > getVertexRW();

	//@}



	/**
	 * @name Accessors to field vertexIndex
	 *
	 * @todo getVertexIndex( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c vertexIndex.
	 */
	typedef uint VertexIndexValueType;

	/**
	 * @brief Type definition of the field named \c vertexIndex
	 */
	typedef vgd::field::TMultiField< VertexIndexValueType > FVertexIndexType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c vertexIndex.
	 */
	vgd::field::EditorRO< FVertexIndexType > getVertexIndexRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c vertexIndex.
	 */
	vgd::field::EditorRW< FVertexIndexType > getVertexIndexRW();

	//@}



	/**
	 * @name Accessors to field primitive
	 *
	 * @todo getPrimitive( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c primitive.
	 */
	typedef vgd::node::Primitive PrimitiveValueType;

	/**
	 * @brief Type definition of the field named \c primitive
	 */
	typedef vgd::field::TMultiField< PrimitiveValueType > FPrimitiveType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c primitive.
	 */
	vgd::field::EditorRO< FPrimitiveType > getPrimitiveRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c primitive.
	 */
	vgd::field::EditorRW< FPrimitiveType > getPrimitiveRW();

	//@}



	/**
	 * @name Accessors to field normal
	 *
	 * @todo getNormal( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c normal.
	 */
	typedef vgm::Vec3f NormalValueType;

	/**
	 * @brief Type definition of the field named \c normal
	 */
	typedef vgd::field::TMultiField< NormalValueType > FNormalType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c normal.
	 */
	vgd::field::EditorRO< FNormalType > getNormalRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c normal.
	 */
	vgd::field::EditorRW< FNormalType > getNormalRW();

	//@}



	/**
	 * @name Accessors to field tangent
	 *
	 * @todo getTangent( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tangent.
	 */
	typedef vgm::Vec3f TangentValueType;

	/**
	 * @brief Type definition of the field named \c tangent
	 */
	typedef vgd::field::TMultiField< TangentValueType > FTangentType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c tangent.
	 */
	vgd::field::EditorRO< FTangentType > getTangentRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c tangent.
	 */
	vgd::field::EditorRW< FTangentType > getTangentRW();

	//@}



	/**
	 * @name Accessors to field color
	 *
	 * @todo getColor( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c color.
	 */
	typedef vgm::Vec4f ColorValueType;

	/**
	 * @brief Type definition of the field named \c color
	 */
	typedef vgd::field::TMultiField< ColorValueType > FColorType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c color.
	 */
	vgd::field::EditorRO< FColorType > getColorRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c color.
	 */
	vgd::field::EditorRW< FColorType > getColorRW();

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c normalBinding.
	 *
	 * @return the name of field \c normalBinding.
	 */
	static const std::string getFNormalBinding( void );

	/**
	 * @brief Returns the name of field \c tangentBinding.
	 *
	 * @return the name of field \c tangentBinding.
	 */
	static const std::string getFTangentBinding( void );

	/**
	 * @brief Returns the name of field \c colorBinding.
	 *
	 * @return the name of field \c colorBinding.
	 */
	static const std::string getFColorBinding( void );

	/**
	 * @brief Returns the name of field \c boundingBoxUpdatePolicy.
	 *
	 * @return the name of field \c boundingBoxUpdatePolicy.
	 */
	static const std::string getFBoundingBoxUpdatePolicy( void );

	/**
	 * @brief Returns the name of field \c deformableHint.
	 *
	 * @return the name of field \c deformableHint.
	 */
	static const std::string getFDeformableHint( void );

	/**
	 * @brief Returns the name of field \c vertex.
	 *
	 * @return the name of field \c vertex.
	 */
	static const std::string getFVertex( void );

	/**
	 * @brief Returns the name of field \c vertexIndex.
	 *
	 * @return the name of field \c vertexIndex.
	 */
	static const std::string getFVertexIndex( void );

	/**
	 * @brief Returns the name of field \c primitive.
	 *
	 * @return the name of field \c primitive.
	 */
	static const std::string getFPrimitive( void );

	/**
	 * @brief Returns the name of field \c normal.
	 *
	 * @return the name of field \c normal.
	 */
	static const std::string getFNormal( void );

	/**
	 * @brief Returns the name of field \c tangent.
	 *
	 * @return the name of field \c tangent.
	 */
	static const std::string getFTangent( void );

	/**
	 * @brief Returns the name of field \c color.
	 *
	 * @return the name of field \c color.
	 */
	static const std::string getFColor( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when \c boundingBox field is modified.
	 */
	static const std::string getDFBoundingBox();

	//@}
	/**
	 * @brief Invalidate bounding box dirty flag for each parents of this node.
	 */
	void invalidateParentsBoundingBoxDirtyFlag();

	/**
	 * @name Bounding box
	 */
	//@{

	/**
	 * @brief Compute the bounding box.
	 *
	 * @remarks It computes the bounding box using only the vertex field (the vertexIndex field is not used, if there is 
	 * unused vertex, then the bounding box could be less accurate).
	 *
	 * @remarks Compute only if bounding box dirty flag is invalidate (i.e. Mesh has changed).
	 *
	 * @return true if bounding box has been computed, false if bounding box has been already valid or simply transformed
	 * by the matrix \c transformation.
	 */
	bool computeBoundingBox( const vgm::MatrixR& transformation );

	bool isBoundingBoxValid() const;

	/**
	 * @brief Compute the bounding box.
	 * 
	 * The bounding box is compute using vertex and vertexIndex field. So a unused vertex don't modify the bounding box.
	 * This is slower than the simple computeBoundingBox() but always accurate.
	 * 
	 * @remarks Compute only if bounding box dirty flag is invalidate (but be carefull bounding box dirty flag is only 
	 * invalidate if a vertex has changed and NOT vertex index !!!).
	 * 
	 * @remarks Compute only if bounding box dirty flag is invalidate (i.e. Mesh has changed).
	 *
	 * @return true if bounding box has been computed, false if bounding box has been already valid or simply transformed
	 * by the matrix \c transformation.
	 */
	bool smartComputeBoundingBox( const vgm::MatrixR& transformation );
	
	void invalidateBoundingBox( bool bInvalidate = true );

	//@}



	/**
	 * @name Actions on VertexShape
	 */
	//@{

	void transform( const vgm::MatrixR& matrix, const bool normalize = true );

	void transform( const vgm::Vec3f translation );

	void transform( const vgm::Rotation rotation );

	void scale( const vgm::Vec3f scale );

	/**
	* @brief	Check the texture coordinates dimension and call the template texutureTransform method to
	*			transform the texture coordinates at the given index with the given matrix.
	* 
	* @param matrix the transformation matrix
	*
	* @param texUnit the texture unit index
	*/
	void textureTransform( const vgm::MatrixR& matrix, const int texUnit = 0 );

	/**
	* @brief Transform the texture coordinates at the given index with the given matrix.
	* 
	* @param matrix the transformation matrix
	*
	* @param texUnit the texture unit index
	*/
	template< typename T >
	void textureTransform( const vgm::MatrixR& matrix, const int texUnit )
	{
		vgd::field::EditorRW< T > texCoords	= getTexCoordRW< T >( texUnit );

		// Transform each texCoord
		for( typename T::iterator	i	= texCoords->begin(),
									ie	= texCoords->end();
									i  != ie;
									++i )
		{
			matrix.multVecMatrix( (*i), (*i) );
		}
	};

	//@}


	/**
	 * @name Accessors to field \c texCoord*
	 */
	//@{

	/**
	 * @brief Typedef for the \c texCoord field.
	 */
	typedef vgd::field::MFFloat	FTexCoord1fType;
	
	/**
	 * @brief Typedef for the \c texCoord field.
	 */
	typedef vgd::field::MFVec2f	FTexCoord2fType;

	/**
	 * @brief Typedef for the \c texCoord field.
	 */	
	typedef vgd::field::MFVec3f	FTexCoord3fType;

	/**
	 * @brief Typedef for the \c texCoord field.
	 */
	typedef vgd::field::MFVec4f	FTexCoord4fType;

	/**
	 * @brief Typedef for the \c texCoord value.
	 */
	typedef float				TexCoord1fValueType;
	
	/**
	 * @brief Typedef for the \c texCoord value.
	 */
	typedef vgm::Vec2f			TexCoord2fValueType;
	
	/**
	 * @brief Typedef for the \c texCoord value.
	 */
	typedef vgm::Vec3f			TexCoord3fValueType;
	
	/**
	 * @brief Typedef for the \c texCoord value.
	 */
	typedef vgm::Vec4f			TexCoord4fValueType;


	/**
	 * @brief Returns true if the specified field is existing.
	 *
	 * @param index		zero-base index for the \c texCoord field.
	 */
	const bool hasTexCoord( const uint index ) const;

	/**
	 * @brief Returns the dimension of the i-th \c texCoord field.
	 * 
	 * @param index		zero-base index for the \c texCoord field.
	 * 
	 * @return The dimension of the texture coordinates for the i-th \c texCoord field (zero is returned if there is no
	 * texture coordinate for the specified field).
	 * 
	 * @remarks Expected values are 0, 1, 2, 3 and 4.
	 */
	const int8 getTexCoordDim( const int32 index ) const;


	/**
	 * @brief Accessor to \c texCoord field.
	 * 
	 * @param index		zero-base index for the \c texCoord field.
	 */
	template< typename FTexCoordType >
	vgd::field::EditorRO< FTexCoordType > getTexCoordRO( const int32 index = 0 ) const
	{
		return ( getFieldRO< FTexCoordType >(getFTexCoord( index )) );
	}

	/**
	 * @brief Accessor to \c texCoord field.
	 * 
	 * @param index		zero-base index for the \c texCoord field.
	 */
	template< typename FTexCoordType >
	vgd::field::EditorRW< FTexCoordType > getTexCoordRW( const int32 index = 0 )
	{
		return ( getFieldRW< FTexCoordType >(getFTexCoord( index )) );
	}

	/**
	 * @brief Call this method to create dynamically one or more \c texCoord and \c texCoordBinding fields with the 
	 * specified dimensions (for the coordinate).
	 * 
	 * \c texCoord fields should have preferably contiguous index. If not, only the first block (starting from index 0) 
	 * of contiguous \c texCoord would be used.
	 * A field \c texCoord with an index of \c i is used with the texture (Texture2D, Texture3D...) that has a multi 
	 * attribute index of \c i.
	 * 
	 * @param texCoordDimension		dimension of the texture coordinate (1, 2, 3 or 4)
	 * @param index				zero-base index for the \c texCoord field
	 * @param num				number of contiguous fields
	 * 
	 * @remarks Call this method before any access to texture coordinate or binding related methods with a specific 
	 * index.
	 * 
	 * @remarks Texture coordinates and bindings, initialized by this method, must not be already created.
	 */
	void createTexUnits( const int8 texCoordDimension = 2, const int32 index = 0, const int32 num = 1 );

	/**
	 * @brief Call this method to remove dynamically one \c or more texCoord and \c texCoordBinding fields.
	 * 
	 * @param index					zero-base index for the \c texCoord field.
	 * @param num					number of contiguous fields.
	 * 
	 * @remarks Texture coordinates and bindings, initialized by this method, must be already created.
	 */
	void removeTexUnits( const int32 index = 0, const int32 num = 1 );

	/**
	 * @brief Returns the number of texture units actually used by this node.
	 *
	 * @return The number of texture units.
	 */
	const int32 getNumTexUnits() const;


	// Iterators
	typedef std::set< uint > IndexSet;
	typedef IndexSet::const_iterator ConstIteratorIndexSet;
	const std::pair< ConstIteratorIndexSet, ConstIteratorIndexSet > getTexUnitsIterators() const;

private:
	typedef std::pair< ConstIteratorIndexSet, ConstIteratorIndexSet > PairConstIteratorIndexSet;
	typedef IndexSet::iterator IteratorIndexSet;
	IndexSet m_texUnitsIndexSet;

	/**
	 * @brief Call this method to create dynamically one or more \c texCoord and \c texCoordBinding fields with the 
	 * specified \c fieldType and for all the desired textures units.
	 * 
	 * @param index					zero-base index for the \c texCoord field.
	 * @param num					number of contiguous fields.
	 */
	template< typename fieldType >
	void createTexUnits( const int32 index, const int32 num )
	{
		// Adds fields
		int32	i32Max = index + num;

		for(	int32 i32 = index;
				i32 < i32Max;
				++i32 )
		{
			addField( new fieldType(getFTexCoord(i32)) );
			addField( new FTexCoordBindingType(getFTexCoordBinding(i32)) );

			assert( m_texUnitsIndexSet.find( i32 ) == m_texUnitsIndexSet.end() );
			m_texUnitsIndexSet.insert( i32 );
		}
		
		// Links
		for(	int32 i32 = index;
				i32 < i32Max;
				++i32 )
		{
			link( getFTexCoord(i32), getDFNode() );
			link( getFTexCoordBinding(i32), getDFNode() );
		}

		// Defaults bindings
		for(	int32 i32 = index;
				i32 < i32Max;
				++i32 )
		{
			setTexCoordBinding( i32, vgd::node::BIND_OFF );
		}
	}
public:
	//@}


	/**
	 * @name Accessors to field \c texCoordBinding*
	 */
	//@{

	/**
	 * @brief Typedef for the \c texCoordBinding field.
	 */	
	typedef vgd::field::SFBinding		FTexCoordBindingType;

	/**
	 * @brief Typedef for the \c texCoordBinding value.
	 */
	typedef vgd::node::Binding	TexCoordBindingValueType;

	const vgd::node::Binding	getTexCoordBinding( const int32 texUnit ) const;
	void 						setTexCoordBinding( const int32 texUnit, const vgd::node::Binding );

	//@}


	/**
	 * @brief Returns the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit.
	 * 
	 * @return the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit.
	 */
	static const std::string getFTexCoord( const int32 textureUnit );

	/**
	 * @brief Returns the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit \c binding.
	 * 
	 * @return the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit \c binding.
	 */
	static const std::string getFTexCoordBinding( const int32 textureUnit );



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
	VertexShape( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( VertexShape );
//	IMPLEMENT_INDEXABLE_CLASS_HPP( , VertexShape );
private:
	static const vgd::basic::RegisterNode<VertexShape> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_VERTEXSHAPE_HPP
