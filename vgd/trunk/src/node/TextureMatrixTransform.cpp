// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TextureMatrixTransform.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( TextureMatrixTransform );



TextureMatrixTransform::TextureMatrixTransform( const std::string nodeName ) :
	vgd::node::TextureTransformation( nodeName )
{
	// Add field
	addField( new FMatrixType(getFMatrix()) );
	
	// Link(s)
	link( getDFNode() );
}



void TextureMatrixTransform::setToDefaults( void )
{
	TextureTransformation::setToDefaults();

	//
	vgm::MatrixR identity;
	identity.setIdentity();
	
	setMatrix( identity );
}



void TextureMatrixTransform::setOptionalsToDefaults()
{
	TextureTransformation::setOptionalsToDefaults();
}



const vgm::MatrixR& TextureMatrixTransform::getMatrix( void ) const
{
	return ( getFieldRO<FMatrixType>(getFMatrix())->getValue() );
}



void TextureMatrixTransform::setMatrix( const vgm::MatrixR& matrix )
{
	getFieldRW<FMatrixType>(getFMatrix())->setValue( matrix );
}



const std::string TextureMatrixTransform::getFMatrix( void )
{
	return ( "f_matrix" );
}



} // namespace node

} // namespace vgd
