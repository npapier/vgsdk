// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Displacement.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Displacement > Displacement::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Displacement > node( new Displacement(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Displacement > Displacement::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Displacement > node = Displacement::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Displacement > Displacement::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Displacement > node = Displacement::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Displacement::Displacement( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FDeclarationsVSType(getFDeclarationsVS()) );
	addField( new FDisplacementVSType(getFDisplacementVS()) );
	addField( new FDeclarationsTESType(getFDeclarationsTES()) );
	addField( new FDisplacementTESType(getFDisplacementTES()) );
	addField( new FComposeModeType(getFComposeMode()) );
	addField( new FDisplacementFunctionVSType(getFDisplacementFunctionVS()) );
	addField( new FDisplacementFunctionTESType(getFDisplacementFunctionTES()) );

	// Sets link(s)

	link( getDFNode() );
}



void Displacement::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setDeclarationsVS( std::string() );
	setDisplacementVS( std::string() );
	setDeclarationsTES( std::string() );
	setDisplacementTES( std::string() );
	setComposeMode( (REPLACE) );
}



void Displacement::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setDisplacementFunctionVS( (NONE) );
	setDisplacementFunctionTES( (NONE) );
}



// DeclarationsVS

const Displacement::DeclarationsVSValueType Displacement::DEFAULT_DECLARATIONSVS = std::string();



const Displacement::DeclarationsVSValueType Displacement::getDeclarationsVS() const
{
	return getFieldRO<FDeclarationsVSType>(getFDeclarationsVS())->getValue();
}



void Displacement::setDeclarationsVS( const DeclarationsVSValueType value )
{
	getFieldRW<FDeclarationsVSType>(getFDeclarationsVS())->setValue( value );
}



// DisplacementVS

const Displacement::DisplacementVSValueType Displacement::DEFAULT_DISPLACEMENTVS = std::string();



const Displacement::DisplacementVSValueType Displacement::getDisplacementVS() const
{
	return getFieldRO<FDisplacementVSType>(getFDisplacementVS())->getValue();
}



void Displacement::setDisplacementVS( const DisplacementVSValueType value )
{
	getFieldRW<FDisplacementVSType>(getFDisplacementVS())->setValue( value );
}



// DeclarationsTES

const Displacement::DeclarationsTESValueType Displacement::DEFAULT_DECLARATIONSTES = std::string();



const Displacement::DeclarationsTESValueType Displacement::getDeclarationsTES() const
{
	return getFieldRO<FDeclarationsTESType>(getFDeclarationsTES())->getValue();
}



void Displacement::setDeclarationsTES( const DeclarationsTESValueType value )
{
	getFieldRW<FDeclarationsTESType>(getFDeclarationsTES())->setValue( value );
}



// DisplacementTES

const Displacement::DisplacementTESValueType Displacement::DEFAULT_DISPLACEMENTTES = std::string();



const Displacement::DisplacementTESValueType Displacement::getDisplacementTES() const
{
	return getFieldRO<FDisplacementTESType>(getFDisplacementTES())->getValue();
}



void Displacement::setDisplacementTES( const DisplacementTESValueType value )
{
	getFieldRW<FDisplacementTESType>(getFDisplacementTES())->setValue( value );
}



// ComposeMode

const Displacement::ComposeModeValueType Displacement::getComposeMode() const
{
	return getFieldRO<FComposeModeType>(getFComposeMode())->getValue();
}



void Displacement::setComposeMode( const ComposeModeValueType value )
{
	getFieldRW<FComposeModeType>(getFComposeMode())->setValue( value );
}



// DisplacementFunctionVS

const bool Displacement::getDisplacementFunctionVS( DisplacementFunctionVSValueType& value ) const
{
	return getFieldRO<FDisplacementFunctionVSType>(getFDisplacementFunctionVS())->getValue( value );
}



void Displacement::setDisplacementFunctionVS( const DisplacementFunctionVSValueType& value )
{
	getFieldRW<FDisplacementFunctionVSType>(getFDisplacementFunctionVS())->setValue( value );
}



void Displacement::eraseDisplacementFunctionVS()
{
	getFieldRW<FDisplacementFunctionVSType>(getFDisplacementFunctionVS())->eraseValue();
}


const bool Displacement::hasDisplacementFunctionVS() const
{
	return getFieldRO<FDisplacementFunctionVSType>(getFDisplacementFunctionVS())->hasValue();
}



// DisplacementFunctionTES

const bool Displacement::getDisplacementFunctionTES( DisplacementFunctionTESValueType& value ) const
{
	return getFieldRO<FDisplacementFunctionTESType>(getFDisplacementFunctionTES())->getValue( value );
}



void Displacement::setDisplacementFunctionTES( const DisplacementFunctionTESValueType& value )
{
	getFieldRW<FDisplacementFunctionTESType>(getFDisplacementFunctionTES())->setValue( value );
}



void Displacement::eraseDisplacementFunctionTES()
{
	getFieldRW<FDisplacementFunctionTESType>(getFDisplacementFunctionTES())->eraseValue();
}


const bool Displacement::hasDisplacementFunctionTES() const
{
	return getFieldRO<FDisplacementFunctionTESType>(getFDisplacementFunctionTES())->hasValue();
}



// Field name accessor(s)
const std::string Displacement::getFDeclarationsVS( void )
{
	return "f_declarationsVS";
}



const std::string Displacement::getFDisplacementVS( void )
{
	return "f_displacementVS";
}



const std::string Displacement::getFDeclarationsTES( void )
{
	return "f_declarationsTES";
}



const std::string Displacement::getFDisplacementTES( void )
{
	return "f_displacementTES";
}



const std::string Displacement::getFComposeMode( void )
{
	return "f_composeMode";
}



const std::string Displacement::getFDisplacementFunctionVS( void )
{
	return "f_displacementFunctionVS";
}



const std::string Displacement::getFDisplacementFunctionTES( void )
{
	return "f_displacementFunctionTES";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( Displacement );



const vgd::basic::RegisterNode<Displacement> Displacement::m_registrationInstance;



} // namespace node

} // namespace vgd

