// VGSDK - Copyright (C) 2004-2007, 2010, 2012 Nicolas Papier, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Alexandre Di Pino

#ifndef _VGD_NODE_VERTEXSHAPE_HPP
#define _VGD_NODE_VERTEXSHAPE_HPP

#include "vgd/vgd.hpp"

#include <vgm/Box.hpp>

#include "vgd/field/Binding.hpp"
#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/Integer.hpp"
#include "vgd/field/Primitive.hpp"
#include "vgd/field/Vector.hpp"
#include "vgd/itf/ITransformation.hpp"
#include "vgd/node/Shape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Base class for all vertex-based shape (geometry) nodes.
 * 
 * Summary of capabilities :
 * - encapsulation of geometry/material specification.
 * - bounding box.
 * - applying transformation (matrix, translation and rotation) on vertices and normals.
 *
 *
 * New field added by this node :
 * 
 * - fields that defined the geometry :
 * 	- MFVec3f \c		vertex 		= empty\n
 * 	- MFPrimitive \c	primitive	= empty\n
 * 	- MFUint32 \c		vertexIndex	= empty\n
 * 
 * - fields used by the lighting equation or by materials.
 * 	- MFVec3f \c normal				= empty\n
 * 	- MFVec3f \c tangent			= empty\n
 * 	- MFVec4f \c color4				= empty\n
 * 	- MFVec4f \c secondaryColor4	= empty\n
 * 	- MFVec2f \c texCoord			= empty\n
 * 		texCoord is a "dynamic field", see createTexUnits()...
 * 	- MFUint8 \c edgeFlag			= empty\n
 * 
 * - fields for bindings :
 * 	- SFBinding \c normalBinding 			= BIND_OFF\n
 * 	- SFBinding \c tangentBinding 			= BIND_OFF\n
 * 	- SFBinding \c color4Binding			= BIND_OFF\n
 * 	- SFBinding \c secondaryColor4Binding	= BIND_OFF\n
 * 	- SFBinding \c texCoordBinding			= BIND_OFF\n
 * 		texCoordBinding is a "dynamic field", see createTexUnits()...
 * 	- SFBinding \c edgeFlagBinding			= BIND_OFF\n
 * 
 * - SFEnum \c deformableHint = STATIC\n
 * 		Specifies a symbolic constant indicating the usage of this shape. 
 * 		Choose one value among STATIC, DYNAMIC and STREAM.
 *
 * - SFFloat tessellationLevel = 0.f\n
 * - SFFloat tessellationBias = 0.f\n
 * - SFEnum \c boundingBoxUpdatePolicy = AUTOMATIC\n
 * 		Choose one value among AUTOMATIC or ONCE.
 * 
 * @remarks BIND_OFF, BIND_PER_VERTEX could be used, other not.
 * @remarks Depends on vgd::node::DrawStyle.hpp.
 * 
 * 
 * Differents versions to gain read-only(RO) or read-write(RW) field access :
 *
 * \li read-only access		: vgd::field::EditorRO< vgd::field::MFVec3f > vertices = getFVertexRO();
 * \li read-write access	: vgd::field::EditorRW< vgd::field::MFVec3f > vertices = getFVertexRW();
 * 
 * \li read-only access		: vgd::field::EditorRO< vgd::node::VertexShape::FVertexType > vertices = getFVertexRO();
 * \li read-write access	: vgd::field::EditorRW< vgd::node::VertexShape::FVertexType > vertices = getFVertexRW();
 * 
 * \li read-only access		: vgd::field::EditorRO<vgd::field::MFVec3f> vertices = 
 * getFieldRO<vgd::field::MFVec3f>(getFVertex());
 * \li read-write access	: vgd::field::EditorRW<vgd::field::MFVec3f> vertices = 
 * getFieldRW<vgd::field::MFVec3f>(getFVertex());
 * @remarks Idem for all others fields(especially for bindings).
 * 
 * 
 * @todo Color/SecondaryColor3, ColorIndex, FogCoordinates.
 * @todo generateTexCoords that Calculates either spherical, cylindrical, or planar two-dimensional texture coordinates into texture unit tu.
 * @todo SetToDefault() that call a FieldManager method that called clear() on each field(on multifield).
 * @todo Add a lighter version of this class(with less field, or add field at run-time) and a templated one(for using int16...).
 * 
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 * @ingroup g_texturingNodes
 */

struct VGD_API VertexShape : public vgd::itf::ITransformation, public vgd::node::Shape
{
	META_NODE_HPP( VertexShape );



	/**
	 * @name Algo/Trian support.
	 */
	//@{

	// @todo vgm::Box3f computeAndRetrivesBoundingBox();
	//@}

	/**
	 * @name Bounding box.
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
		vgd::field::EditorRW< T > texCoords	= getFTexCoordRW< T >( texUnit );

		// Transform each vertex.
		for(	T::iterator	i	= texCoords->begin(),
							ie	= texCoords->end();
				i != ie;
				++i )
		{
			matrix.multVecMatrix( (*i), (*i) );
		}
	};
	//@}



	/**
	 * @name Accessors to field vertex
	 */
	//@{

	/**
	 * @brief Typedef for the \c vertex field.
	 */	
	typedef vgd::field::MFVec3f	FVertexType;
		
	/**
	 * @brief Typedef for the \c vertex value.
	 */
	typedef vgm::Vec3f			VertexValueType;

	vgd::field::EditorRO< FVertexType >		getFVertexRO() const;
	vgd::field::EditorRW< FVertexType >		getFVertexRW();

	//@}



	/**
	 * @name Accessors to field normal.
	 */
	//@{

	/**
	 * @brief Typedef for the \c normal field.
	 */	
	typedef vgd::field::MFVec3f	FNormalType;
		
	/**
	 * @brief Typedef for the \c normal value.
	 */
	typedef vgm::Vec3f			NormalValueType;

	vgd::field::EditorRO< FNormalType >		getFNormalRO() const;
	vgd::field::EditorRW< FNormalType >		getFNormalRW();

	//@}



	/**
	 * @name Accessors to field tangent.
	 */
	//@{

	/**
	 * @brief Typedef for the \c tangent field.
	 */	
	typedef vgd::field::MFVec3f	FTangentType;

	/**
	 * @brief Typedef for the \c tangent value.
	 */
	typedef vgm::Vec3f			TangentValueType;

	vgd::field::EditorRO< FTangentType >		getFTangentRO() const;
	vgd::field::EditorRW< FTangentType >		getFTangentRW();

	//@}



	/**
	 * @name Accessors to field color4.
	 */
	//@{

	/**
	 * @brief Typedef for the \c color4 field.
	 */	
	typedef vgd::field::MFVec4f	FColor4Type;
		
	/**
	 * @brief Typedef for the \c color4 value.
	 */
	typedef vgm::Vec4f			Color4ValueType;

	vgd::field::EditorRO< FColor4Type >		getFColor4RO() const;
	vgd::field::EditorRW< FColor4Type >		getFColor4RW();

	//@}



	/**
	 * @name Accessors to field secondaryColor4.
	 */
	//@{

	/**
	 * @brief Typedef for the \c secondaryColor4 field.
	 */	
	typedef vgd::field::MFVec4f	FSecondaryColor4Type;
		
	/**
	 * @brief Typedef for the \c secondaryColor4 value.
	 */
	typedef vgm::Vec4f			SecondaryColor4ValueType;

	vgd::field::EditorRO< FSecondaryColor4Type >		getFSecondaryColor4RO() const;
	vgd::field::EditorRW< FSecondaryColor4Type >		getFSecondaryColor4RW();

	//@}



	/**
	 * @name Accessors to field texCoord*.
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
	const bool hasFTexCoord( const uint index ) const;

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
	vgd::field::EditorRO< FTexCoordType > getFTexCoordRO( const int32 index = 0 ) const
	{
		return ( getFieldRO< FTexCoordType >(getFTexCoord( index )) );
	}

	/**
	 * @brief Accessor to \c texCoord field.
	 * 
	 * @param index		zero-base index for the \c texCoord field.
	 */
	template< typename FTexCoordType >
	vgd::field::EditorRW< FTexCoordType > getFTexCoordRW( const int32 index = 0 )
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


private:

	/**
	 * @brief Call this method to create dynamically one or more \c texCoord and \c texCoordBinding fields with the 
	 * specified \c fieldType and for all the desired textures units.
	 * 
	 * @param index					zero-base index for the \c texCoord field.
	 * @param num					number of contiguous fields.
	 */
	template< typename fieldType >
	void createTexUnits( const int32 index, const int32 num );

public:
	typedef std::set< uint > IndexSet;
	typedef IndexSet::const_iterator ConstIteratorIndexSet;
	typedef std::pair< ConstIteratorIndexSet, ConstIteratorIndexSet > PairConstIteratorIndexSet;
private:
	typedef IndexSet::iterator IteratorIndexSet;
	IndexSet m_texUnitsIndexSet;

public:

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
	 * Returns only the number of texture units of the first block (starting from index 0) of contiguous \c texCoord.
	 * 
	 * @return The number of texture units.
	 * 
	 * @remarks This method is relatively slow.
	 */
	const int32	getNumTexUnits() const;

	const std::pair< ConstIteratorIndexSet, ConstIteratorIndexSet > getTexUnitsIterators() const;
	//@}



	/**
	 * @name Accessors to field edgeFlag.
	 */
	//@{

	/**
	 * @brief Typedef for the \c edgeFlag field.
	 */	
	typedef vgd::field::MFUInt8	FEdgeFlagType;
		
	/**
	 * @brief Typedef for the \c edgeFlag value.
	 */
	typedef uint8				EdgeFlagValueType;

	vgd::field::EditorRO< FEdgeFlagType >		getFEdgeFlagRO() const;
	vgd::field::EditorRW< FEdgeFlagType >		getFEdgeFlagRW();

	//@}



	/**
	 * @name Accessors to field primitive.
	 */
	//@{

	/**
	 * @brief Typedef for the \c primitive field.
	 */	
	typedef vgd::field::MFPrimitive	FPrimitiveType;
		
	/**
	 * @brief Typedef for the \c primitive value.
	 */
	typedef vgd::node::Primitive	PrimitiveValueType;

	vgd::field::EditorRO< FPrimitiveType >		getFPrimitiveRO() const;
	vgd::field::EditorRW< FPrimitiveType >		getFPrimitiveRW();

	//@}




	/**
	 * @name Accessors to field vertexIndex.
	 */
	//@{

	/**
	 * @brief Typedef for the \c vertexIndex field.
	 */	
	typedef vgd::field::MFUInt32		FVertexIndexType;
		
	/**
	 * @brief Typedef for the \c vertexIndex value.
	 */
	typedef uint32						VertexIndexValueType;

	vgd::field::EditorRO< FVertexIndexType >		getFVertexIndexRO() const;
	vgd::field::EditorRW< FVertexIndexType >		getFVertexIndexRW();

	//@}






	/**
	 * @name Accessors to field normalBinding.
	 */
	//@{

	/**
	 * @brief Typedef for the \c normalBinding field.
	 */	
	typedef vgd::field::SFBinding		FNormalBindingType;
		
	/**
	 * @brief Typedef for the \c normalBinding value.
	 */
	typedef vgd::node::Binding			NormalBindingValueType;

	const vgd::node::Binding	getNormalBinding() const;
	void 						setNormalBinding( const vgd::node::Binding );
	//@}



	/**
	 * @name Accessors to field tangentBinding.
	 */
	//@{

	/**
	 * @brief Typedef for the \c tangentBinding field.
	 */	
	typedef vgd::field::SFBinding		FTangentBindingType;

	/**
	 * @brief Typedef for the \c tangentBinding value.
	 */
	typedef vgd::node::Binding			TangentBindingValueType;

	const vgd::node::Binding	getTangentBinding() const;
	void 						setTangentBinding( const vgd::node::Binding );
	//@}



	/**
	 * @name Accessors to field color4Binding.
	 */
	//@{

	/**
	 * @brief Typedef for the \c color4Binding field.
	 */	
	typedef vgd::field::SFBinding		FColor4BindingType;
		
	/**
	 * @brief Typedef for the \c color4Binding value.
	 */
	typedef vgd::node::Binding			Color4BindingValueType;

	const vgd::node::Binding	getColor4Binding() const;
	void 						setColor4Binding( const vgd::node::Binding );
	//@}
	


	/**
	 * @name Accessors to field secondaryColor4Binding.
	 */
	//@{

	/**
	 * @brief Typedef for the \c secondaryColor4Binding field.
	 */	
	typedef vgd::field::SFBinding		FSecondaryColor4BindingType;
		
	/**
	 * @brief Typedef for the \c secondaryColor4Binding value.
	 */
	typedef vgd::node::Binding			SecondaryColor4BindingValueType;

	const vgd::node::Binding	getSecondaryColor4Binding() const;
	void 						setSecondaryColor4Binding( const vgd::node::Binding );

	//@}

	
	
	/**
	 * @name Accessors to field texCoordBinding.
	 */
	//@{

	/**
	 * @brief Typedef for the \c texCoordBinding field.
	 */	
	typedef vgd::field::SFBinding		FTexCoordBindingType;
		
	/**
	 * @brief Typedef for the \c texCoordBinding value.
	 */
	typedef vgd::node::Binding			TexCoordBindingValueType;

	const vgd::node::Binding	getTexCoordBinding( const int32 texUnit ) const;
	void 						setTexCoordBinding( const int32 texUnit, const vgd::node::Binding );

	//@}
	
	
	
	/**
	 * @name Accessors to field edgeFlagBinding.
	 */
	//@{

	/**
	 * @brief Typedef for the \c edgeFlagBinding field.
	 */	
	typedef vgd::field::SFBinding		FEdgeFlagBindingType;
		
	/**
	 * @brief Typedef for the \c edgeFlagBinding value.
	 */
	typedef vgd::node::Binding			EdgeFlagBindingValueType;

	const vgd::node::Binding	getEdgeFlagBinding() const;
	void 						setEdgeFlagBinding( const vgd::node::Binding );

	//@}


	/**
	 * @name Accessors to field deformableHint
	 */
	//@{

	/**
	 * @brief Typedef for the \c deformableHint field.
	 */	
	typedef vgd::field::SFEnum FDeformableHintType;

	/**
	 * @brief Typedef for the \c deformableHint value.
	 */
	enum
	{
		STATIC = 1,		/*!< STATIC assumed to be a 1-to-n update-to-draw. Means the geometry is specified once. */
		DYNAMIC,		/*!< DYNAMIC assumed to be a n-to-n update-to-draw. Means the geometry is specified every 
						few frames. */
		STREAM,			/*!< STREAM assumed to be a 1-to-1 update-to-draw. Means the geometry is specified for each 
						frame.	*/
		DEFAULT_DEFORMABLE_HINT = STATIC
	};
	
	typedef vgd::field::Enum DeformableHintValueType;

	/**
	 * @brief Gets the deformableHint of node.
	 */
	const DeformableHintValueType	getDeformableHint() const;

	/**
	 * @brief Sets the deformableHint of node.
	 * 
	 */
	void setDeformableHint( const DeformableHintValueType value );

	//@}



	/**
	 * @name Accessors to field tessellation level.
	 */
	//@{

	/**
	 * @brief Typedef for the \c tessellation level field.
	 */	
	typedef vgd::field::SFFloat	FTessellationLevelType;

	/**
	 * @brief Typedef for the \c tessellation level value.
	 */	
	typedef float				TessellationLevelValueType;

	vgd::field::EditorRO< FTessellationLevelType >	getTessellationLevelRO() const;
	vgd::field::EditorRW< FTessellationLevelType >	getTessellationLevelRW();

	void											setTessellationLevel(const float level);
	//@}



	/**
	 * @name Accessors to field tessellation bias.
	 */
	//@{

	/**
	 * @brief Typedef for the \c tessellation bias field.
	 */	
	typedef vgd::field::SFFloat	FTessellationBiasType;

	/**
	 * @brief Typedef for the \c tessellation bias value.
	 */	
	typedef float				TessellationBiasValueType;

	vgd::field::EditorRO< FTessellationBiasType >	getTessellationBiasRO() const;
	vgd::field::EditorRW< FTessellationBiasType >	getTessellationBiasRW();

	void											setTessellationBias(const float bias);
	//@}


	/**
	 * @name Accessors to field boundingBoxUpdatePolicy
	 */
	//@{

	/**
	 * @brief Typedef for the \c boundingBoxUpdatePolicy field.
	 */	
	typedef vgd::field::SFEnum FBoundingBoxUpdatePolicyType;

	/**
	 * @brief Typedef for the \c boundingBoxUpdatePolicy value.
	 */
	enum
	{
		AUTOMATIC = 1,	/*<! AUTOMATIC means that the bounding box of this vertex based shape would be automatically 
						computed the first time and updated when field \c vertex is modified 
						(see service ComputeBoundingBox in ::vge::service namespace). */
		ONCE,			/*<! ONCE means the the bounding box of this vertex based shape would be automatically 
						computed only the first time. After the responsibility of bounding box updating is yours. */
		DEFAULT_BOUNDINGBOX_UPDATE_POLICY = AUTOMATIC
	};

	typedef vgd::field::Enum BoundingBoxUpdatePolicyValueType;

	/**
	 * @brief Gets the boundingBoxUpdatePolicy of node.
	 */
	const BoundingBoxUpdatePolicyValueType	getBoundingBoxUpdatePolicy() const;

	/**
	 * @brief Sets the boundingBoxUpdatePolicy of node.
	 * 
	 */
	void setBoundingBoxUpdatePolicy( const BoundingBoxUpdatePolicyValueType value );

	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	VertexShape( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();

	//@}


	/**
	 * @brief Invalidate bounding box dirty flag for each parents of this node.
	 */
	void invalidateParentsBoundingBoxDirtyFlag();



public:
	/**
	 * @name Fields names enumeration.
	 */
	//@{

	/**
	 * @brief Returns the name of field \c vertex.
	 * 
	 * @return the name of field \c vertex.
	 */
	static const std::string getFVertex( void );

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
	static const std::string VertexShape::getFTangent( void );

	///**
	// * @brief Returns the name of field \c tangent handidness.
	// * 
	// * @return the name of field \c tangent handidness.
	// */
	//static const std::string VertexShape::getFTangentHandidness( void );

//	/**
//	 * @brief Returns the name of field \c color3.
//	 * 
//	 * @return the name of field \c color3.
//	 */
//	static const std::string getFColor3( void );

	/**
	 * @brief Returns the name of field \c color4.
	 * 
	 * @return the name of field \c color4.
	 */
	static const std::string getFColor4( void );

//	/**
//	 * @brief Returns the name of field \c secondary \c color3.
//	 * 
//	 * @return the name of field \c secondary \c color3.
//	 */
//	static const std::string getFSecondaryColor3( void );

	/**
	 * @brief Returns the name of field \c secondary \c colors4.
	 * 
	 * @return the name of field \c secondary \c colors4.
	 */
	static const std::string getFSecondaryColor4( void );

//	/**
//	 * @brief Returns the name of field \c fog coordinates.
//	 * 
//	 * @return the name of field \c fog \c coordinates.
//	 */
//	static const std::string getFFogCoord( void );

	/**
	 * @brief Returns the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit.
	 * 
	 * @return the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit.
	 */
	static const std::string getFTexCoord( const int32 textureUnit );

	/**
	 * @brief Returns the name of field \c edge \c flag.
	 * 
	 * @return the name of field \c edge \c flag.
	 */
	static const std::string getFEdgeFlag( void );
	
	/**
	 * @brief Returns the name of field \c primitive.
	 * 
	 * @return the name of field \c primitive.
	 */
	static const std::string getFPrimitive( void );



	/**
	 * @brief Returns the name of field \c vertex \c index.
	 * 
	 * @return the name of field \c vertex \c index.
	 */
	static const std::string getFVertexIndex( void );



	/**
	 * @brief Returns the name of field \c normal \c binding.
	 * 
	 * @return the name of field \c normal \c binding.
	 */
	static const std::string getFNormalBinding( void );

	/**
	 * @brief Returns the name of field \c tangent \c binding.
	 * 
	 * @return the name of field \c tangent \c binding.
	 */
	static const std::string getFTangentBinding( void );

//	/**
//	 * @brief Returns the name of field \c color3 \c binding.
//	 * 
//	 * @return the name of field \c color3 \c binding.
//	 */
//	static const std::string getFColor3Binding( void );

	/**
	 * @brief Returns the name of field \c color4 \c binding.
	 * 
	 * @return the name of field \c color4 \c binding.
	 */
	static const std::string getFColor4Binding( void );

//	/**
//	 * @brief Returns the name of field \c secondary \c color3 \c binding.
//	 * 
//	 * @return the name of field \c \c secondary \c color3.
//	 */
//	static const std::string getFSecondaryColor3Binding( void );

	/**
	 * @brief Returns the name of field \c secondary \c colors4 \c binding.
	 * 
	 * @return the name of field \c secondary \c colors4 \c binding.
	 */
	static const std::string getFSecondaryColor4Binding( void );

//	/**
//	 * @brief Returns the name of field \c fog \c coordinates \c binding.
//	 * 
//	 * @return the name of field \c fog \c coordinates \c binding.
//	 */
//	static const std::string getFFogCoordBinding( void );

	/**
	 * @brief Returns the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit \c binding.
	 * 
	 * @return the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit \c binding.
	 */
	static const std::string getFTexCoordBinding( const int32 textureUnit );

	/**
	 * @brief Returns the name of field \c edge \c flag \c binding.
	 * 
	 * @return the name of field \c edge \c flag \c binding.
	 */
	static const std::string getFEdgeFlagBinding( void );
	
	/**
	 * @brief Returns the name of field \c deformableHint.
	 * 
	 * @return the name of field \c deformableHint.
	 */
	static const std::string getFDeformableHint();

	/**
	 * @brief Returns the name of field \c tessellation level.
	 * 
	 * @return the name of field \c tessellation level.
	 */
	static const std::string getFTessellationLevel( void );

	/**
	 * @brief Returns the name of field \c tessellation bias.
	 * 
	 * @return the name of field \c tessellation bias.
	 */
	static const std::string getFTessellationBias( void );

	/**
	 * @brief Returns the name of field \c boundingBoxUpdatePolicy.
	 * 
	 * @return the name of field \c boundingBoxUpdatePolicy.
	 */
	static const std::string getFBoundingBoxUpdatePolicy();	
	
	//@}



	/**
	 * @name Dirty flags enumeration.
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when bounding box is invalidate and must be recomputed.
	 */
	static const std::string getDFBoundingBox( void );
	
	//@}



private:

	/**
	 * @brief Number of texture unit fields
	 * 
	 * @remarks Sets to -1 if the number of texture units fields must be computed.
	 */
	mutable int32	m_numTexUnits;
};



} // namespace node

} // namespace vgd

#endif // #ifndef _VGD_NODE_VERTEXSHAPE_HPP

