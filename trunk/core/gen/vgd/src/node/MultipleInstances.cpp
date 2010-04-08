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
