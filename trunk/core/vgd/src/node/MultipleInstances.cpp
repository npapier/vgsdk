// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/MultipleInstances.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< MultipleInstances > MultipleInstances::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< MultipleInstances > node( new MultipleInstances(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< MultipleInstances > MultipleInstances::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< MultipleInstances > node = MultipleInstances::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< MultipleInstances > MultipleInstances::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< MultipleInstances > node = MultipleInstances::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



MultipleInstances::MultipleInstances( const std::string nodeName ) :
	vgd::node::Shape( nodeName )
{
	// Adds field(s)
	addField( new FShapeType(getFShape()) );
	addField( new FMatrixType(getFMatrix()) );

	// Sets link(s)

	link( getDFNode() );
}



void MultipleInstances::setToDefaults( void )
{
	Shape::setToDefaults();

}



void MultipleInstances::setOptionalsToDefaults()
{
	Shape::setOptionalsToDefaults();
}



// Shape
const MultipleInstances::ShapeValueType MultipleInstances::getShape() const
{
	return getFieldRO<FShapeType>(getFShape())->getValue();
}



void MultipleInstances::setShape( const ShapeValueType value )
{
	getFieldRW<FShapeType>(getFShape())->setValue( value );
}



// Matrix
vgd::field::EditorRO< MultipleInstances::FMatrixType > MultipleInstances::getMatrixRO() const
{
	return getFieldRO<FMatrixType>( getFMatrix() );
}



vgd::field::EditorRW< MultipleInstances::FMatrixType > MultipleInstances::getMatrixRW()
{
	return getFieldRW<FMatrixType>( getFMatrix() );
}



// Field name accessor(s)
const std::string MultipleInstances::getFShape( void )
{
	return "f_shape";
}



const std::string MultipleInstances::getFMatrix( void )
{
	return "f_matrix";
}



bool MultipleInstances::computeBoundingBox( const vgm::MatrixR& transformation )
{
	// Retrieves shape
	vgd::Shp< vgd::node::Shape > shape = vgd::dynamic_pointer_cast< vgd::node::Shape >( getShape() );

	// For each matrix, do
	using vgd::field::EditorRO;
	EditorRO< FMatrixType > matrix = getMatrixRO();

	//
	m_transformation = transformation;

	//
	m_boundingBox.makeEmpty();
	for(	FMatrixType::const_iterator	i		= matrix->begin(),
										iEnd	= matrix->end();
			i != iEnd;
			++i	)
	{
		// Updates geometrical transformation
		const vgm::MatrixR& iMatrix = *i;

		shape->computeBoundingBox( iMatrix );
		assert( shape->isBoundingBoxValid() );

		const vgm::Box3f box = shape->getProjectXfBoundingBox();

		if ( !box.isEmpty() )
		{
			m_boundingBox.extendBy( box );
		}
		else
		{
			assert( false && "Invalid child bounding box." );
		}
	}

	return true;
}



bool MultipleInstances::isBoundingBoxValid() const
{
	return true;
}



void MultipleInstances::invalidateBoundingBox( bool /*bInvalidate*/ )
{
}
IMPLEMENT_INDEXABLE_CLASS_CPP( , MultipleInstances );



const vgd::basic::RegisterNode<MultipleInstances> MultipleInstances::m_registrationInstance;



} // namespace node

} // namespace vgd

