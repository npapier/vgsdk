// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Texture1D.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Texture1D > Texture1D::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Texture1D > node( new Texture1D(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Texture1D > Texture1D::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Texture1D > node = Texture1D::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Texture1D::Texture1D( const std::string nodeName ) :
	vgd::node::Texture( nodeName )
{
	// Adds field(s)

	// Sets link(s)
	link( getDFNode() );
}



void Texture1D::setToDefaults( void )
{
	Texture::setToDefaults();
}



void Texture1D::setOptionalsToDefaults()
{
	Texture::setOptionalsToDefaults();
}



// Field name accessor(s)
const uint32 Texture1D::gethTextureDimension() const
{
	return 1;
}
IMPLEMENT_INDEXABLE_CLASS_CPP( , Texture1D );



const vgd::basic::RegisterNode<Texture1D> Texture1D::m_registrationInstance;



} // namespace node

} // namespace vgd

