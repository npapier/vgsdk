// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Texture2D.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Texture2D > Texture2D::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Texture2D > node( new Texture2D(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Texture2D > Texture2D::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Texture2D > node = Texture2D::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Texture2D::Texture2D( const std::string nodeName ) :
	vgd::node::Texture( nodeName )
{
	// Adds field(s)

	// Sets link(s)
	link( getDFNode() );
}



void Texture2D::setToDefaults( void )
{
	Texture::setToDefaults();
}



void Texture2D::setOptionalsToDefaults()
{
	Texture::setOptionalsToDefaults();
}



// Field name accessor(s)
const uint32 Texture2D::gethTextureDimension() const
{
	return 2;
}
IMPLEMENT_INDEXABLE_CLASS_CPP( , Texture2D );



const vgd::basic::RegisterNode<Texture2D> Texture2D::m_registrationInstance;



} // namespace node

} // namespace vgd

