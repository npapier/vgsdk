// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/MatrixTransform.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( MatrixTransform );



MatrixTransform::MatrixTransform( const std::string nodeName ) :
	vgd::node::GeometricalTransformation( nodeName )
{
	// Add field
	addField( new FMatrixType(getFMatrix()) );
	
	// Link(s)
	link( getDFNode() );
}



void MatrixTransform::setToDefaults( void )
{
	GeometricalTransformation::setToDefaults();

	//
	vgm::MatrixR identity;
	identity.identity();
	
	setMatrix( identity );
}



void MatrixTransform::setOptionalsToDefaults()
{
	GeometricalTransformation::setOptionalsToDefaults();
}



// MATRIX
const vgm::MatrixR& MatrixTransform::getMatrix( void ) const
{
	return ( getFieldRO<FMatrixType>(getFMatrix())->getValue() );
}



void MatrixTransform::setMatrix( const vgm::MatrixR& matrix )
{
	getFieldRW<FMatrixType>(getFMatrix())->setValue( matrix );
}



const std::string MatrixTransform::getFMatrix( void )
{
	return ( "f_matrix" );
}



} // namespace node

} // namespace vgd
