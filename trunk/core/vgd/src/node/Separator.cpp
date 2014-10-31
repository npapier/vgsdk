// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Separator.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Separator > Separator::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Separator > node( new Separator(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Separator > Separator::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Separator > node = Separator::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Separator > Separator::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Separator > node = Separator::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Separator::Separator( const std::string nodeName ) :
	vgd::node::Group( nodeName )
{
	// Adds field(s)
	addField( new FFullSeparationType(getFFullSeparation()) );
	addField( new FTessellationLevelSeparationType(getFTessellationLevelSeparation()) );
	addField( new FDisplacementSeparationType(getFDisplacementSeparation()) );

	// Sets link(s)

	link( getDFNode() );
}



void Separator::setToDefaults( void )
{
	Group::setToDefaults();
	setFullSeparation( (true) );
	setTessellationLevelSeparation( (false) );
	setDisplacementSeparation( (false) );
}



void Separator::setOptionalsToDefaults()
{
	Group::setOptionalsToDefaults();
}



// FullSeparation

const Separator::FullSeparationValueType Separator::DEFAULT_FULLSEPARATION = (true);



const Separator::FullSeparationValueType Separator::getFullSeparation() const
{
	return getFieldRO<FFullSeparationType>(getFFullSeparation())->getValue();
}



void Separator::setFullSeparation( const FullSeparationValueType value )
{
	getFieldRW<FFullSeparationType>(getFFullSeparation())->setValue( value );
}



// TessellationLevelSeparation

const Separator::TessellationLevelSeparationValueType Separator::DEFAULT_TESSELLATIONLEVELSEPARATION = (false);



const Separator::TessellationLevelSeparationValueType Separator::getTessellationLevelSeparation() const
{
	return getFieldRO<FTessellationLevelSeparationType>(getFTessellationLevelSeparation())->getValue();
}



void Separator::setTessellationLevelSeparation( const TessellationLevelSeparationValueType value )
{
	getFieldRW<FTessellationLevelSeparationType>(getFTessellationLevelSeparation())->setValue( value );
}



// DisplacementSeparation

const Separator::DisplacementSeparationValueType Separator::DEFAULT_DISPLACEMENTSEPARATION = (false);



const Separator::DisplacementSeparationValueType Separator::getDisplacementSeparation() const
{
	return getFieldRO<FDisplacementSeparationType>(getFDisplacementSeparation())->getValue();
}



void Separator::setDisplacementSeparation( const DisplacementSeparationValueType value )
{
	getFieldRW<FDisplacementSeparationType>(getFDisplacementSeparation())->setValue( value );
}



// Field name accessor(s)
const std::string Separator::getFFullSeparation( void )
{
	return "f_fullSeparation";
}



const std::string Separator::getFTessellationLevelSeparation( void )
{
	return "f_tessellationLevelSeparation";
}



const std::string Separator::getFDisplacementSeparation( void )
{
	return "f_displacementSeparation";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( Separator );



const vgd::basic::RegisterNode<Separator> Separator::m_registrationInstance;



} // namespace node

} // namespace vgd

