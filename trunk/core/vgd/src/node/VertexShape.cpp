// VGSDK - Copyright (C) 2004-2007, 2008, 2009, 2010, 2012 Nicolas Papier, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Alexandre Di Pino

#include "vgd/node/VertexShape.hpp"

#include <sstream>

#include "vgd/node/Group.hpp"
#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( VertexShape );


void VertexShape::computeNormals()
{
	vgm::Vec3f faceNormal;		// a temp face normal
	vgm::Vec3f v1, v2;			// temp vectors
	int32 numTris;
	int32 numVertices;
	
	numTris		= getFVertexIndexRO()->size()/3;	// number of triangles	
	numVertices	= getFVertexRO()->size();			// number of vertices

	int32 i;
	int32 j=0;

	vgd::field::EditorRO< vgd::field::MFVec3f >		vertices	= getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex	= getFVertexIndexRO();
	vgd::field::EditorRW< vgd::field::MFVec3f >		normals		= getFNormalRW();

	normals->resize(0);
	normals->reserve(numVertices);

	// initialize normals to (0,0,0) if there are no normals
	for(i=0; i < numVertices; i++)
	{
		normals->push_back( vgm::Vec3f( 0.f, 0.f, 0.f ) );
	}

	// compute vertices normals
	for(i=0; i < numTris; ++i)
	{
		// compute face normal
		int32 indexA, indexB, indexC;

		indexA = (*vertexIndex)[j];
		indexB = (*vertexIndex)[j+1];
		indexC = (*vertexIndex)[j+2];

			v1 = (*vertices)[indexB] - (*vertices)[indexA];
			v2 = (*vertices)[indexC] - (*vertices)[indexA];
			faceNormal = v1.cross(v2);

			// add this face normal to each vertex normal
			(*normals)[indexA]	+= faceNormal;
			(*normals)[indexB]	+= faceNormal;
			(*normals)[indexC]	+= faceNormal;

		j += 3;
	}

	// normalize normals
	for(i=0; i < numVertices; i++)
	{
		(*normals)[i].normalize();
	}

	setNormalBinding( vgd::node::BIND_PER_VERTEX );
	//vgLogDebug("VertexShape::computeNormals() for %s", getName().c_str() );
}


void VertexShape::invalidateParentsBoundingBoxDirtyFlag() 
{
	NodeList parents;
	
	getParents( parents );
	
	// for each node.
	for(	NodeList::iterator	i	= parents.begin(),
								ie	= parents.end();
			i != ie;
			++i
		)
	{
		// Parent nodes are always group node.
		assert( (*i)->isAKindOf< vgd::node::Group >() );
		
		vgd::Shp< vgd::node::Group > group( 
			vgd::dynamic_pointer_cast< vgd::node::Group >( *i )
				);

		group->invalidateBoundingBox();
	}
}



/**
 * Bounding box dirty flag is validate when calling this method.
 * 
 * It is invalidate when RW access to vertex and is invalid if \c transformation has changed.
 * 
 * Parents nodes are invalidated when \c transformation or vertex buffer changed (i.e. when this node is invalid).
 */
bool VertexShape::computeBoundingBox( const vgm::MatrixR& transformation )
{
	// STEP 1: init. and checks matrix transformation.
	bool	bRetVal;
	bool	bInvalidateParents;
	
	// updates transformation
	if ( m_transformation != transformation )
	{
		bInvalidateParents	= true;
		bRetVal				= true;

		m_transformation	= transformation;
	}
	else
	{
		bInvalidateParents	= false;
		bRetVal				= false;
	}

	// STEP 2: updates bounding box.
	vgd::field::DirtyFlag *pDirtyFlag = getDirtyFlag( getDFBoundingBox() );
	assert( pDirtyFlag != 0 );

	const BoundingBoxUpdatePolicyValueType bbUpdatePolicy = getBoundingBoxUpdatePolicy();

	if (	(bbUpdatePolicy == AUTOMATIC && pDirtyFlag->isDirty()) ||
			(bbUpdatePolicy == ONCE && pDirtyFlag->isDirty() && m_boundingBox.isInvalid())	)
	{
		bInvalidateParents	= true;
		bRetVal				= true;

		// compute bb
		vgd::field::EditorRO< FVertexType > vertex;
		vertex = getFVertexRO();

		m_boundingBox.makeEmpty();

		for(	FVertexType::const_iterator	i	= vertex->begin(),
											ie	= vertex->end();
				i != ie;
				i++ )
		{
			m_boundingBox.extendBy( *i );
		}

		//
		pDirtyFlag->validate();
	}
	else if ( bbUpdatePolicy == ONCE && pDirtyFlag->isDirty() )
	{
		pDirtyFlag->validate();
	}
	else
	{
#ifdef DEBUG
		if ( pDirtyFlag->isDirty() )
		{
			assert( false && "Internal error." );
			pDirtyFlag->validate();
		}
#endif
	}

	if ( bInvalidateParents )
	{
		invalidateParentsBoundingBoxDirtyFlag();
	}
	
	return bRetVal;
}



bool VertexShape::isBoundingBoxValid() const
{
	return ( getDirtyFlag( getDFBoundingBox() )->isValid() );
}


	
bool VertexShape::smartComputeBoundingBox( const vgm::MatrixR& transformation )
{
	// update transformation
	m_transformation = transformation;
	
	// update bounding box	
	vgd::field::DirtyFlag *pDirtyFlag = getDirtyFlag( getDFBoundingBox() );
	assert( pDirtyFlag != 0 );

	if ( pDirtyFlag->isDirty() )
	{
		//		
		vgd::field::EditorRO< FVertexType > vertex;
		vertex = getFVertexRO();

		vgd::field::EditorRO< FVertexIndexType > index;
		index = getFVertexIndexRO();

		m_boundingBox.makeEmpty();
		
		for(	FVertexIndexType::const_iterator	i	= index->begin(),
													ie	= index->end();
				i != ie;
				i++ )
		{
			vgm::Vec3f vec( (*vertex)[*i] );
			m_boundingBox.extendBy( vec );
		}

		pDirtyFlag->validate();
		
		return true;
	}
	else
	{
		return false;
	}
}



void VertexShape::invalidateBoundingBox( bool bInvalidate )
{
	getDirtyFlag( getDFBoundingBox() )->dirty( bInvalidate );
}






void VertexShape::transform( const vgm::MatrixR& matrix, const bool normalize )
{
	vgd::field::EditorRW< FVertexType > vertex	= getFVertexRW();
	vgd::field::EditorRW< FNormalType > normal	= getFNormalRW();

	// Transform each vertex.
	for(	FVertexType::iterator	i	= vertex->begin(),
									ie	= vertex->end();
			i != ie;
			i++ )
	{
		matrix.multVecMatrix( (*i), (*i) );
	}
	
	// Transform each normal.
	if ( normalize )
	{
		for(	FNormalType::iterator	i	= normal->begin(),
										ie	= normal->end();
				i != ie;
				i++ )
		{
			matrix.multDirMatrix( (*i), (*i) );
			i->normalize();
		}
	}
	else
	{
		for(	FNormalType::iterator	i	= normal->begin(),
										ie	= normal->end();
				i != ie;
				i++ )
		{
			matrix.multDirMatrix( (*i), (*i) );
		}
	}
}



void VertexShape::transform( const vgm::Vec3f translation )
{
	vgd::field::EditorRW< FVertexType > vertex	= getFVertexRW();

	// Transform each vertex.
	for(	FVertexType::iterator	i	= vertex->begin(),
									ie	= vertex->end();
			i != ie;
			i++ )
	{
		(*i) += translation;
	}
}



void VertexShape::transform( const vgm::Rotation rotation )
{
	vgd::field::EditorRW< FVertexType > vertex	= getFVertexRW();
	vgd::field::EditorRW< FNormalType > normal	= getFNormalRW();

	// Transform each vertex.
	for(	FVertexType::iterator	i	= vertex->begin(),
									ie	= vertex->end();
			i != ie;
			i++ )
	{
		rotation.multVec( (*i), (*i) );
	}

	// Transform each normal.
	for(	FNormalType::iterator	i	= normal->begin(),
									ie	= normal->end();
			i != ie;
			i++ )
	{
		rotation.multVec( (*i), (*i) );
		i->normalize();
	}
}



void VertexShape::scale( const vgm::Vec3f scale )
{
	vgm::MatrixR transformation;
	transformation.setScale( scale );

	transform(transformation, true);
}



void VertexShape::textureTransform( const vgm::MatrixR& matrix, const int texUnit )
{
	if( hasFTexCoord( texUnit ) )
	{
		int dim = getTexCoordDim  ( texUnit );
		switch( dim )
		{
			case 1:
				//textureTransform< FTexCoord1fType >( matrix, texUnit );
				assert( false && "Texture dimension not supported" );
				break;

			case 2:
				textureTransform< FTexCoord2fType >( matrix, texUnit );
				break;

			case 3:
				textureTransform< FTexCoord3fType >( matrix, texUnit );
				break;

			case 4:
				//textureTransform< FTexCoord4fType >( matrix, texUnit );
				assert( false && "Texture dimension not supported" );
				break;
		}
	}
	else
	{
		//vgLogDebug( "No texture coordinates found for this index." );
	}
}



VertexShape::VertexShape( const std::string nodeName ) :
	vgd::node::Shape	( nodeName )
{
	// Add fields.

	// data field.
	addField( new FVertexType(getFVertex()) );
	addField( new FNormalType(getFNormal()) );
	addField( new FTangentType(getFTangent()) );
	addField( new FColor4Type(getFColor4()) );
	addField( new FSecondaryColor4Type(getFSecondaryColor4()) );
	addField( new FEdgeFlagType(getFEdgeFlag()) );
	
	addField( new FPrimitiveType(getFPrimitive()) );
	
	// index field.
	addField( new FVertexIndexType(getFVertexIndex()) );

	// binding field.
	addField( new FNormalBindingType(getFNormalBinding()) );
	addField( new FTangentBindingType(getFTangentBinding()) );
	addField( new FColor4BindingType(getFColor4Binding()) );
	addField( new FSecondaryColor4BindingType(getFSecondaryColor4Binding()) );

	addField( new FEdgeFlagBindingType(getFEdgeFlagBinding()) );
	
	// deformable field.
	addField( new FDeformableHintType(getFDeformableHint()) );

	// tessellation field
	addField( new FTessellationLevelType(getFTessellationLevel()));
	addField( new FTessellationBiasType(getFTessellationBias()));

	// bb policy
	addField( new FBoundingBoxUpdatePolicyType(getFBoundingBoxUpdatePolicy()) );

	// Add dirty flags.
	addDirtyFlag(getDFBoundingBox());

	// Links.

	// getDFBoundingBox()
	link( getFVertex(), getDFBoundingBox() );

	//
	link( getDFNode() );
}



void VertexShape::setToDefaults( void )
{
	Shape::setToDefaults();

	setNormalBinding( 				vgd::node::BIND_OFF );
	setColor4Binding( 				vgd::node::BIND_OFF );
	setSecondaryColor4Binding(		vgd::node::BIND_OFF );
	setEdgeFlagBinding(				vgd::node::BIND_OFF );
	
	setDeformableHint( DEFAULT_DEFORMABLE_HINT );
	
	setBoundingBoxUpdatePolicy( DEFAULT_BOUNDINGBOX_UPDATE_POLICY );
	
	setTessellationLevel(0.f);
	setTessellationBias(0.f);

	// Invalidates m_numTexUnits
	//m_numTexUnits = -1;
}



void VertexShape::setOptionalsToDefaults( void )
{
	Shape::setOptionalsToDefaults();
}






// VERTEX
vgd::field::EditorRO< vgd::node::VertexShape::FVertexType > VertexShape::getFVertexRO() const
{
	return ( getFieldRO< FVertexType >(getFVertex()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FVertexType > VertexShape::getFVertexRW()
{
	return ( getFieldRW< FVertexType >(getFVertex()) );
}



// NORMAL
vgd::field::EditorRO< vgd::node::VertexShape::FNormalType > VertexShape::getFNormalRO() const
{
	return ( getFieldRO< FNormalType >(getFNormal()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FNormalType > VertexShape::getFNormalRW()
{
	return ( getFieldRW< FNormalType >(getFNormal()) );
}



//TANGENT
vgd::field::EditorRO< vgd::node::VertexShape::FTangentType > VertexShape::getFTangentRO() const
{
	return ( getFieldRO< FTangentType >(getFTangent()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FTangentType > VertexShape::getFTangentRW()
{
	return ( getFieldRW< FTangentType >(getFTangent()) );
}



// COLOR
vgd::field::EditorRO< vgd::node::VertexShape::FColor4Type > VertexShape::getFColor4RO() const
{
	return ( getFieldRO< FColor4Type >(getFColor4()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FColor4Type > VertexShape::getFColor4RW()
{
	return ( getFieldRW< FColor4Type >(getFColor4()) );
}



// SECONDARY_COLOR
vgd::field::EditorRO< vgd::node::VertexShape::FSecondaryColor4Type > VertexShape::getFSecondaryColor4RO() const
{
	return ( getFieldRO< FSecondaryColor4Type >(getFSecondaryColor4()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FSecondaryColor4Type > VertexShape::getFSecondaryColor4RW()
{
	return ( getFieldRW< FSecondaryColor4Type >(getFSecondaryColor4()) );
}



// TEXCOORD
const bool VertexShape::hasFTexCoord( const uint index ) const
{
	const std::type_info& fieldType(	getFieldType( getFTexCoord( index ) )	);

	return fieldType != typeid( NotFound );
}



const int8 VertexShape::getTexCoordDim( const int32 index ) const
{
	// FIXME OPTME this could be optimize (see if (fieldType ... ) ).
	int8 retVal;

	const std::type_info& fieldType(	getFieldType( getFTexCoord( index ) )	);

	if ( fieldType != typeid( NotFound ) )
	{
		if ( fieldType == typeid(FTexCoord2fType) )
		{
			retVal = 2;
		}
		else if ( fieldType == typeid(FTexCoord3fType) )
		{
			retVal = 3;
		}
		else if ( fieldType == typeid(FTexCoord1fType) )
		{
			retVal = 1;
		}
		else
		{
			assert( fieldType == typeid(FTexCoord4fType) && "Unexpected type for texCoord field." );
			retVal = 4;
		}
	}
	else
	{
		retVal = 0;
	}

	return retVal;
}



void VertexShape::createTexUnits( const int8 texCoordDimension, const int32 index, const int32 num )
{
	assert( texCoordDimension >= 1 );
	assert( texCoordDimension <= 4 );

	assert( index >= 0 );
	assert( num >= 1 );

#ifdef _DEBUG
	for(	int32 i32 = index;
			i32 < index + num;
			++i32)
	{
		assert( !isField( getFTexCoord(i32) ) );
		assert( !isField( getFTexCoordBinding(i32) ) );
	}
#endif

	switch ( texCoordDimension )
	{
		case 2:
			createTexUnits<FTexCoord2fType>( index, num );
			break;
		
		case 3:
			createTexUnits<FTexCoord3fType>( index, num );
			break;

		case 1:
			createTexUnits<FTexCoord1fType>( index, num );
			break;

		case 4:
			createTexUnits<FTexCoord4fType>( index, num );
			break;

		default:
			assert( false && "Unexpected dimension of the texture coordinate." );
	}
}



template< typename fieldType >
void VertexShape::createTexUnits( const int32 index, const int32 num )
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

	// Invalidates m_numTexUnits
	// m_numTexUnits = -1;
}



void VertexShape::removeTexUnits( const int32 index, const int32 num )
{
	assert( index >= 0 );
	assert( num >= 1 );

	int32	i32Max = index + num;

#ifdef _DEBUG
	for(	int32 i32 = index;
			i32 < i32Max;
			++i32)
	{
		assert( isField( getFTexCoord(i32) ) );
		assert( m_texUnitsIndexSet.find(i32) != m_texUnitsIndexSet.end() );
	}
#endif

	// Removes fields
	for(	int32 i32 = index;
			i32 < i32Max;
			++i32 )
	{
		removeField( getFTexCoord(i32) );
		removeField( getFTexCoordBinding(i32) );

#ifdef _DEBUG
		const uint num = m_texUnitsIndexSet.erase( i32 );
		assert( num == 1 );
#else
		m_texUnitsIndexSet.erase( i32 );
#endif
	}

	// Links are removed automatically by the fieldManager.

	// Invalidates m_numTexUnits
	//m_numTexUnits = -1;
}



const int32	VertexShape::getNumTexUnits() const
{
	return m_texUnitsIndexSet.size();
/*
	if ( m_numTexUnits == -1 )
	{
		// m_numTexUnits is invalid, computes it.
		int32 i32 = 0;
		while ( isField( getFTexCoord(i32) ) )
		{
			assert( isField( getFTexCoordBinding(i32) ) );
			
			++i32;
		}
		
	 	// Validates m_numTexUnits.
		m_numTexUnits = i32;
	}
	
	return m_numTexUnits;*/
}



const std::pair< VertexShape::ConstIteratorIndexSet, VertexShape::ConstIteratorIndexSet > VertexShape::getTexUnitsIterators() const
{
	return std::make_pair( m_texUnitsIndexSet.begin(), m_texUnitsIndexSet.end() );
}



// EDGEFLAG
vgd::field::EditorRO< vgd::node::VertexShape::FEdgeFlagType > VertexShape::getFEdgeFlagRO() const
{
	return ( getFieldRO< FEdgeFlagType >(getFEdgeFlag()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FEdgeFlagType > VertexShape::getFEdgeFlagRW()
{
	return ( getFieldRW< FEdgeFlagType >(getFEdgeFlag()) );
}



// PRIMITIVE
vgd::field::EditorRO< vgd::node::VertexShape::FPrimitiveType > VertexShape::getFPrimitiveRO() const
{
	return ( getFieldRO< FPrimitiveType >(getFPrimitive()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FPrimitiveType > VertexShape::getFPrimitiveRW()
{
	return ( getFieldRW< FPrimitiveType >(getFPrimitive()) );
}






// VERTEX INDEX
vgd::field::EditorRO< vgd::node::VertexShape::FVertexIndexType > VertexShape::getFVertexIndexRO() const
{
	return ( getFieldRO< FVertexIndexType >(getFVertexIndex()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FVertexIndexType > VertexShape::getFVertexIndexRW()
{
	return ( getFieldRW< FVertexIndexType >(getFVertexIndex()) );
}






// NORMAL BINDING
const vgd::node::Binding VertexShape::getNormalBinding() const
{
	return ( getFieldRO< FNormalBindingType >(getFNormalBinding())->getValue() );
}



void VertexShape::setNormalBinding( const vgd::node::Binding binding )
{
	return ( getFieldRW< FNormalBindingType >(getFNormalBinding())->setValue( binding ) );
}



// TANGENT BINDING
const vgd::node::Binding VertexShape::getTangentBinding() const
{
	return ( getFieldRO< FTangentBindingType >(getFTangentBinding())->getValue() );
}



void VertexShape::setTangentBinding( const vgd::node::Binding binding )
{
	return ( getFieldRW< FTangentBindingType >(getFTangentBinding())->setValue( binding ) );
}



// COLOR BINDING
const vgd::node::Binding VertexShape::getColor4Binding() const
{
	return ( getFieldRO< FColor4BindingType >(getFColor4Binding())->getValue() );
}



void VertexShape::setColor4Binding( const vgd::node::Binding binding )
{
	return ( getFieldRW< FColor4BindingType >(getFColor4Binding())->setValue( binding ) );
}



// SECONDARY COLOR BINDING
const vgd::node::Binding VertexShape::getSecondaryColor4Binding() const
{
	return ( getFieldRO< FSecondaryColor4BindingType >(getFSecondaryColor4Binding())->getValue() );
}



void VertexShape::setSecondaryColor4Binding( const vgd::node::Binding binding )
{
	return ( getFieldRW< FSecondaryColor4BindingType >(getFSecondaryColor4Binding())->setValue( binding ) );
}



// TEX COORD BINDING
const vgd::node::Binding VertexShape::getTexCoordBinding( const int32 texUnit ) const
{
	return ( getFieldRO< FTexCoordBindingType >(getFTexCoordBinding( texUnit ))->getValue() );
}



void VertexShape::setTexCoordBinding( const int32 texUnit, const vgd::node::Binding binding )
{
	return ( getFieldRW< FTexCoordBindingType >(getFTexCoordBinding( texUnit ))->setValue( binding ) );
}



// EDGE FLAG BINDING
const vgd::node::Binding VertexShape::getEdgeFlagBinding() const
{
	return ( getFieldRO< FEdgeFlagBindingType >(getFEdgeFlagBinding())->getValue() );
}



void VertexShape::setEdgeFlagBinding( const vgd::node::Binding binding )
{
	return ( getFieldRW< FEdgeFlagBindingType >(getFEdgeFlagBinding())->setValue( binding ) );
}



// DEFORMABLE HINT
const VertexShape::DeformableHintValueType VertexShape::getDeformableHint() const
{
	return ( getFieldRO<FDeformableHintType>(getFDeformableHint())->getValue() );
}



void VertexShape::setDeformableHint( const DeformableHintValueType value )
{
	getFieldRW<FDeformableHintType>(getFDeformableHint())->setValue( value );
}



// TESSELLATION LEVEL
vgd::field::EditorRO< vgd::node::VertexShape::FTessellationLevelType >	VertexShape::getTessellationLevelRO() const
{
	return ( getFieldRO< FTessellationLevelType >(getFTessellationLevel()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FTessellationLevelType >	VertexShape::getTessellationLevelRW()
{
	return ( getFieldRW< FTessellationLevelType >(getFTessellationLevel()) );
}



void VertexShape::setTessellationLevel( const float level )
{
	return ( getFieldRW< FTessellationLevelType >(getFTessellationLevel())->setValue( level ) );
}



// TESSELLATION BIAS
vgd::field::EditorRO< vgd::node::VertexShape::FTessellationBiasType >	VertexShape::getTessellationBiasRO() const
{
	return ( getFieldRO< FTessellationBiasType >(getFTessellationBias()) );
}



vgd::field::EditorRW< vgd::node::VertexShape::FTessellationBiasType >	VertexShape::getTessellationBiasRW()
{
	return ( getFieldRW< FTessellationBiasType >(getFTessellationBias()) );
}



void VertexShape::setTessellationBias( const float bias )
{
	return ( getFieldRW< FTessellationBiasType >(getFTessellationBias())->setValue( bias ) );
}



// BOUNDINGBOX UPDATE POLICY
const VertexShape::BoundingBoxUpdatePolicyValueType VertexShape::getBoundingBoxUpdatePolicy() const
{
	return ( getFieldRO<FBoundingBoxUpdatePolicyType>(getFBoundingBoxUpdatePolicy())->getValue() );
}



void VertexShape::setBoundingBoxUpdatePolicy( const BoundingBoxUpdatePolicyValueType value )
{
	getFieldRW<FBoundingBoxUpdatePolicyType>(getFBoundingBoxUpdatePolicy())->setValue( value );
}



const std::string VertexShape::getFVertex( void )
{
	return "f_vertex";
}



const std::string VertexShape::getFNormal( void )
{
	return "f_normal";
}



const std::string VertexShape::getFTangent( void )
{
	return "f_tangent";
}



/*const std::string VertexShape::getFTangentHandidness( void )
{
	return "f_thandidness";
}*/



//const std::string VertexShape::getFColor3( void )
//{
//	return "f_color3";
//}



const std::string VertexShape::getFColor4( void )
{
	return "f_color4";
}



//const std::string VertexShape::getFSecondaryColor3( void )
//{
//	return "f_secondary_color3";
//}



const std::string VertexShape::getFSecondaryColor4( void )
{
	return "f_secondaryColor4";
}



//const std::string VertexShape::getFFogCoord( void )
//{
//	return "f_fog_coord";
//}



const std::string VertexShape::getFTexCoord( const int32 textureUnit )
{
	std::stringstream strStream;
	
	strStream << "f_texCoord" << textureUnit << std::ends;
	
	return ( strStream.str() );
}


const std::string VertexShape::getFEdgeFlag( void )
{
	return "f_edgeFlag";
}



const std::string VertexShape::getFPrimitive( void )
{
	return "f_primitive";
}






const std::string VertexShape::getFVertexIndex( void )
{
	return "f_vertexIndex";
}






const std::string VertexShape::getFNormalBinding( void )
{
	return "f_normalBinding";
}



const std::string VertexShape::getFTangentBinding( void )
{
	return "f_tangentBinding";
}



//const std::string VertexShape::getFColor3Binding( void )
//{
//	return "f_color3Binding";
//}



const std::string VertexShape::getFColor4Binding( void )
{
	return "f_color4Binding";
}



//const std::string VertexShape::getFSecondaryColor3Binding( void )
//{
//	return "f_secondary_color3_binding";
//}



const std::string VertexShape::getFSecondaryColor4Binding( void )
{
	return "f_secondaryColor4Binding";
}



//const std::string VertexShape::getFFogCoordBinding( void )
//{
//	return "f_fog_coord_binding";
//}



const std::string VertexShape::getFTexCoordBinding( const int32 textureUnit )
{
	std::stringstream strStream;
	
	strStream << "f_texCoordBinding" << textureUnit << std::ends;
	
	return ( strStream.str() );
}



const std::string VertexShape::getFEdgeFlagBinding( void )
{
	return "f_edgeFlagBinding";
}



const std::string VertexShape::getFDeformableHint( void )
{
	return "f_deformableHint";
}



const std::string VertexShape::getFTessellationLevel( void )
{
	return "f_tessellationLevel";
}



const std::string VertexShape::getFTessellationBias( void )
{
	return "f_tessellationBias";
}



const std::string VertexShape::getFBoundingBoxUpdatePolicy( void )
{
	return "f_boundingBoxUpdatePolicy";
}



const std::string VertexShape::getDFBoundingBox( void )
{
	return "df_boundingBox";
}



} // namespace node

} // namespace vgd

