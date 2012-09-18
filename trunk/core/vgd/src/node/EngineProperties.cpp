// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/EngineProperties.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< EngineProperties > EngineProperties::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< EngineProperties > node( new EngineProperties(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< EngineProperties > EngineProperties::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< EngineProperties > node = EngineProperties::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< EngineProperties > EngineProperties::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< EngineProperties > node = EngineProperties::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



EngineProperties::EngineProperties( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FMaxAnisotropyType(getFMaxAnisotropy()) );

	// Sets link(s)

	link( getDFNode() );
}



void EngineProperties::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void EngineProperties::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setMaxAnisotropy( (1.f) );
}



// MaxAnisotropy

const EngineProperties::MaxAnisotropyValueType EngineProperties::DEFAULT_MAXANISOTROPY = (1.f);



const bool EngineProperties::getMaxAnisotropy( MaxAnisotropyValueType& value ) const
{
	return getFieldRO<FMaxAnisotropyType>(getFMaxAnisotropy())->getValue( value );
}



void EngineProperties::setMaxAnisotropy( const MaxAnisotropyValueType& value )
{
	getFieldRW<FMaxAnisotropyType>(getFMaxAnisotropy())->setValue( value );
}



void EngineProperties::eraseMaxAnisotropy()
{
	getFieldRW<FMaxAnisotropyType>(getFMaxAnisotropy())->eraseValue();
}


const bool EngineProperties::hasMaxAnisotropy() const
{
	return getFieldRO<FMaxAnisotropyType>(getFMaxAnisotropy())->hasValue();
}



// Field name accessor(s)
const std::string EngineProperties::getFMaxAnisotropy( void )
{
	return "f_maxAnisotropy";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , EngineProperties );



const vgd::basic::RegisterNode<EngineProperties> EngineProperties::m_registrationInstance;



} // namespace node

} // namespace vgd

