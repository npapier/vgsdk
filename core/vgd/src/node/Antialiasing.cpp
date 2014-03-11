// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Antialiasing.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Antialiasing > Antialiasing::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Antialiasing > node( new Antialiasing(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Antialiasing > Antialiasing::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Antialiasing > node = Antialiasing::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Antialiasing > Antialiasing::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Antialiasing > node = Antialiasing::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Antialiasing::Antialiasing( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FTechniqueType(getFTechnique()) );

	// Sets link(s)

	link( getDFNode() );
}



void Antialiasing::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setTechnique( (FXAA1) );
}



void Antialiasing::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// Technique

const Antialiasing::TechniqueValueType Antialiasing::getTechnique() const
{
	return getFieldRO<FTechniqueType>(getFTechnique())->getValue();
}



void Antialiasing::setTechnique( const TechniqueValueType value )
{
	getFieldRW<FTechniqueType>(getFTechnique())->setValue( value );
}



// Field name accessor(s)
const std::string Antialiasing::getFTechnique( void )
{
	return "f_technique";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , Antialiasing );



const vgd::basic::RegisterNode<Antialiasing> Antialiasing::m_registrationInstance;



} // namespace node

} // namespace vgd

