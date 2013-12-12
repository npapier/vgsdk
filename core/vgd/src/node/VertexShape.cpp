// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/VertexShape.hpp"

#include "vgd/node/Group.hpp"
#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< VertexShape > VertexShape::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< VertexShape > node( new VertexShape(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< VertexShape > VertexShape::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< VertexShape > node = VertexShape::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< VertexShape > VertexShape::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< VertexShape > node = VertexShape::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



VertexShape::VertexShape( const std::string nodeName ) :
	vgd::node::Shape( nodeName ),
	vgd::node::ITransformation()
{
	// Adds field(s)
	addField( new FTessellationBiasType(getFTessellationBias()) );
	addField( new FTessellationLevelType(getFTessellationLevel()) );
	addField( new FTangentBindingType(getFTangentBinding()) );
	addField( new FColorBindingType(getFColorBinding()) );
	addField( new FNormalType(getFNormal()) );
	addField( new FColorType(getFColor()) );
	addField( new FDeformableHintType(getFDeformableHint()) );
	addField( new FVertexType(getFVertex()) );
	addField( new FVertexIndexType(getFVertexIndex()) );
	addField( new FBoundingBoxUpdatePolicyType(getFBoundingBoxUpdatePolicy()) );
	addField( new FTangentType(getFTangent()) );
	addField( new FNormalBindingType(getFNormalBinding()) );
	addField( new FPrimitiveType(getFPrimitive()) );

	// Adds dirty flag(s)
	addDirtyFlag(getDFBoundingBox());

	// Sets link(s)
	link( getFVertex(), getDFBoundingBox() );

	link( getDFNode() );
}



void VertexShape::setToDefaults( void )
{
	Shape::setToDefaults();
	ITransformation::setToDefaults();
	setTessellationBias( (0.f) );
	setTessellationLevel( (0.f) );
	setTangentBinding( vgd::node::Binding(vgd::node::BIND_OFF) );
	setColorBinding( vgd::node::Binding(vgd::node::BIND_OFF) );
	setDeformableHint( (STATIC) );
	setBoundingBoxUpdatePolicy( (AUTOMATIC) );
	setNormalBinding( vgd::node::Binding(vgd::node::BIND_OFF) );
}



void VertexShape::setOptionalsToDefaults()
{
	Shape::setOptionalsToDefaults();
	ITransformation::setOptionalsToDefaults();
}



// TessellationBias

const VertexShape::TessellationBiasValueType VertexShape::DEFAULT_TESSELLATIONBIAS = (0.f);



const VertexShape::TessellationBiasValueType VertexShape::getTessellationBias() const
{
	return getFieldRO<FTessellationBiasType>(getFTessellationBias())->getValue();
}



void VertexShape::setTessellationBias( const TessellationBiasValueType value )
{
	getFieldRW<FTessellationBiasType>(getFTessellationBias())->setValue( value );
}



// TessellationLevel

const VertexShape::TessellationLevelValueType VertexShape::DEFAULT_TESSELLATIONLEVEL = (0.f);



const VertexShape::TessellationLevelValueType VertexShape::getTessellationLevel() const
{
	return getFieldRO<FTessellationLevelType>(getFTessellationLevel())->getValue();
}



void VertexShape::setTessellationLevel( const TessellationLevelValueType value )
{
	getFieldRW<FTessellationLevelType>(getFTessellationLevel())->setValue( value );
}



// TangentBinding

const VertexShape::TangentBindingValueType VertexShape::getTangentBinding() const
{
	return getFieldRO<FTangentBindingType>(getFTangentBinding())->getValue();
}



void VertexShape::setTangentBinding( const TangentBindingValueType value )
{
	getFieldRW<FTangentBindingType>(getFTangentBinding())->setValue( value );
}



// ColorBinding

const VertexShape::ColorBindingValueType VertexShape::getColorBinding() const
{
	return getFieldRO<FColorBindingType>(getFColorBinding())->getValue();
}



void VertexShape::setColorBinding( const ColorBindingValueType value )
{
	getFieldRW<FColorBindingType>(getFColorBinding())->setValue( value );
}



// Normal
vgd::field::EditorRO< VertexShape::FNormalType > VertexShape::getNormalRO() const
{
	return getFieldRO<FNormalType>( getFNormal() );
}



vgd::field::EditorRW< VertexShape::FNormalType > VertexShape::getNormalRW()
{
	return getFieldRW<FNormalType>( getFNormal() );
}



// Color
vgd::field::EditorRO< VertexShape::FColorType > VertexShape::getColorRO() const
{
	return getFieldRO<FColorType>( getFColor() );
}



vgd::field::EditorRW< VertexShape::FColorType > VertexShape::getColorRW()
{
	return getFieldRW<FColorType>( getFColor() );
}



// DeformableHint

const VertexShape::DeformableHintValueType VertexShape::getDeformableHint() const
{
	return getFieldRO<FDeformableHintType>(getFDeformableHint())->getValue();
}



void VertexShape::setDeformableHint( const DeformableHintValueType value )
{
	getFieldRW<FDeformableHintType>(getFDeformableHint())->setValue( value );
}



// Vertex
vgd::field::EditorRO< VertexShape::FVertexType > VertexShape::getVertexRO() const
{
	return getFieldRO<FVertexType>( getFVertex() );
}



vgd::field::EditorRW< VertexShape::FVertexType > VertexShape::getVertexRW()
{
	return getFieldRW<FVertexType>( getFVertex() );
}



// VertexIndex
vgd::field::EditorRO< VertexShape::FVertexIndexType > VertexShape::getVertexIndexRO() const
{
	return getFieldRO<FVertexIndexType>( getFVertexIndex() );
}



vgd::field::EditorRW< VertexShape::FVertexIndexType > VertexShape::getVertexIndexRW()
{
	return getFieldRW<FVertexIndexType>( getFVertexIndex() );
}



// BoundingBoxUpdatePolicy

const VertexShape::BoundingBoxUpdatePolicyValueType VertexShape::getBoundingBoxUpdatePolicy() const
{
	return getFieldRO<FBoundingBoxUpdatePolicyType>(getFBoundingBoxUpdatePolicy())->getValue();
}



void VertexShape::setBoundingBoxUpdatePolicy( const BoundingBoxUpdatePolicyValueType value )
{
	getFieldRW<FBoundingBoxUpdatePolicyType>(getFBoundingBoxUpdatePolicy())->setValue( value );
}



// Tangent
vgd::field::EditorRO< VertexShape::FTangentType > VertexShape::getTangentRO() const
{
	return getFieldRO<FTangentType>( getFTangent() );
}



vgd::field::EditorRW< VertexShape::FTangentType > VertexShape::getTangentRW()
{
	return getFieldRW<FTangentType>( getFTangent() );
}



// NormalBinding

const VertexShape::NormalBindingValueType VertexShape::getNormalBinding() const
{
	return getFieldRO<FNormalBindingType>(getFNormalBinding())->getValue();
}



void VertexShape::setNormalBinding( const NormalBindingValueType value )
{
	getFieldRW<FNormalBindingType>(getFNormalBinding())->setValue( value );
}



// Primitive
vgd::field::EditorRO< VertexShape::FPrimitiveType > VertexShape::getPrimitiveRO() const
{
	return getFieldRO<FPrimitiveType>( getFPrimitive() );
}



vgd::field::EditorRW< VertexShape::FPrimitiveType > VertexShape::getPrimitiveRW()
{
	return getFieldRW<FPrimitiveType>( getFPrimitive() );
}



// Field name accessor(s)
const std::string VertexShape::getFTessellationBias( void )
{
	return "f_tessellationBias";
}



const std::string VertexShape::getFTessellationLevel( void )
{
	return "f_tessellationLevel";
}



const std::string VertexShape::getFTangentBinding( void )
{
	return "f_tangentBinding";
}



const std::string VertexShape::getFColorBinding( void )
{
	return "f_colorBinding";
}



const std::string VertexShape::getFNormal( void )
{
	return "f_normal";
}



const std::string VertexShape::getFColor( void )
{
	return "f_color";
}



const std::string VertexShape::getFDeformableHint( void )
{
	return "f_deformableHint";
}



const std::string VertexShape::getFVertex( void )
{
	return "f_vertex";
}



const std::string VertexShape::getFVertexIndex( void )
{
	return "f_vertexIndex";
}



const std::string VertexShape::getFBoundingBoxUpdatePolicy( void )
{
	return "f_boundingBoxUpdatePolicy";
}



const std::string VertexShape::getFTangent( void )
{
	return "f_tangent";
}



const std::string VertexShape::getFNormalBinding( void )
{
	return "f_normalBinding";
}



const std::string VertexShape::getFPrimitive( void )
{
	return "f_primitive";
}



// DIRTY FLAG(S)
const std::string VertexShape::getDFBoundingBox()
{
	return "df_boundingbox";
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
		vertex = getVertexRO();

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
		vertex = getVertexRO();

		vgd::field::EditorRO< FVertexIndexType > index;
		index = getVertexIndexRO();

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
	// Transform each vertex.
	vgd::field::EditorRW< FVertexType >		vertex		= getVertexRW();
	for(	FVertexType::iterator	i	= vertex->begin(),
									ie	= vertex->end();
			i != ie;
			i++ )
	{
		matrix.multVecMatrix( (*i), (*i) );
	}

	// Transform each normal.
	vgd::field::EditorRW< FNormalType >		normals		= getNormalRW();
	if ( normalize )
	{
		for(	FNormalType::iterator	i	= normals->begin(),
										ie	= normals->end();
				i != ie;
				i++ )
		{
			matrix.multDirMatrix( (*i), (*i) );
			i->normalize();
		}
	}
	else
	{
		for(	FNormalType::iterator	i	= normals->begin(),
										ie	= normals->end();
				i != ie;
				i++ )
		{
			matrix.multDirMatrix( (*i), (*i) );
		}
	}

	// Transform each tangent.
	vgd::field::EditorRW< FTangentType >	tangents	= getTangentRW();
	if ( normalize )
	{
		for(	FTangentType::iterator	i	= tangents->begin(),
										ie	= tangents->end();
				i != ie;
				i++ )
		{
			matrix.multDirMatrix( (*i), (*i) );
			i->normalize();
		}
	}
	else
	{
		for(	FTangentType::iterator	i	= tangents->begin(),
										ie	= tangents->end();
				i != ie;
				i++ )
		{
			matrix.multDirMatrix( (*i), (*i) );
		}
	}
}


void VertexShape::transform( const vgm::Vec3f translation )
{
	vgd::field::EditorRW< FVertexType > vertex	= getVertexRW();

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
	vgd::field::EditorRW< FVertexType > vertex	= getVertexRW();
	vgd::field::EditorRW< FNormalType > normal	= getNormalRW();

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
	if( hasTexCoord( texUnit ) )
	{
		int dim = getTexCoordDim( texUnit );
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



// TEXCOORD*
const bool VertexShape::hasTexCoord( const uint index ) const
{
	const std::type_info& fieldType(	getFieldType( getFTexCoord( index ) )	);

	return fieldType != typeid( NotFound );
}


const int8 VertexShape::getTexCoordDim( const int32 index ) const
{
	// @todo OPTME this could be optimize (see if (fieldType ... ) ).
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

}


const int32	VertexShape::getNumTexUnits() const
{
	return m_texUnitsIndexSet.size();
}


const std::pair< VertexShape::ConstIteratorIndexSet, VertexShape::ConstIteratorIndexSet > VertexShape::getTexUnitsIterators() const
{
	return std::make_pair( m_texUnitsIndexSet.begin(), m_texUnitsIndexSet.end() );
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


//
const std::string VertexShape::getFTexCoord( const int32 textureUnit )
{
	std::stringstream strStream;

	strStream << "f_texCoord" << textureUnit;

	return ( strStream.str() );
}


const std::string VertexShape::getFTexCoordBinding( const int32 textureUnit )
{

	std::stringstream strStream;
	
	strStream << "f_texCoordBinding" << textureUnit << std::ends;
	
	return ( strStream.str() );
}
IMPLEMENT_INDEXABLE_CLASS_CPP( , VertexShape );



const vgd::basic::RegisterNode<VertexShape> VertexShape::m_registrationInstance;



} // namespace node

} // namespace vgd

