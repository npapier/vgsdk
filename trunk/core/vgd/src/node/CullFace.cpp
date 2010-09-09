// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/CullFace.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< CullFace > CullFace::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< CullFace > node( new CullFace(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< CullFace > CullFace::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< CullFace > node = CullFace::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< CullFace > CullFace::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< CullFace > node = CullFace::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



CullFace::CullFace( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FModeType(getFMode()) );

	// Sets link(s)

	link( getDFNode() );
}



void CullFace::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setMode( DISABLED );
}



void CullFace::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// Mode
const CullFace::ModeValueType CullFace::getMode() const
{
	return getFieldRO<FModeType>(getFMode())->getValue();
}



void CullFace::setMode( const ModeValueType value )
{
	getFieldRW<FModeType>(getFMode())->setValue( value );
}



// Field name accessor(s)
const std::string CullFace::getFMode( void )
{
	return "f_mode";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , CullFace );



const vgd::basic::RegisterNode<CullFace> CullFace::m_registrationInstance;



} // namespace node

} // namespace vgd

