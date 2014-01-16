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
	addField( new FDisplacementVSType(getFDisplacementVS()) );
	addField( new FParameter4f1Type(getFParameter4f1()) );
	addField( new FParameter4f0Type(getFParameter4f0()) );
	addField( new FDisplacementFunctionVSType(getFDisplacementFunctionVS()) );
	addField( new FDeclarationsTESType(getFDeclarationsTES()) );
	addField( new FDeclarationsVSType(getFDeclarationsVS()) );
	addField( new FDisplacementFunctionTESType(getFDisplacementFunctionTES()) );
	addField( new FDisplacementTESType(getFDisplacementTES()) );

	// Sets link(s)

	link( getDFNode() );
}



void Displacement::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setDisplacementVS( std::string() );
	setDeclarationsTES( std::string() );
	setDeclarationsVS( std::string() );
	setDisplacementTES( std::string() );
}



void Displacement::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setParameter4f1( vgm::Vec4f(0.f, 0.f, 0.f, 0.f) );
	setParameter4f0( vgm::Vec4f(0.f, 0.f, 0.f, 0.f) );
	setDisplacementFunctionVS( (NONE) );
	setDisplacementFunctionTES( (NONE) );
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



// Parameter4f1

const Displacement::Parameter4f1ValueType Displacement::DEFAULT_PARAMETER4F1 = vgm::Vec4f(0.f, 0.f, 0.f, 0.f);



const bool Displacement::getParameter4f1( Parameter4f1ValueType& value ) const
{
	return getFieldRO<FParameter4f1Type>(getFParameter4f1())->getValue( value );
}



void Displacement::setParameter4f1( const Parameter4f1ValueType& value )
{
	getFieldRW<FParameter4f1Type>(getFParameter4f1())->setValue( value );
}



void Displacement::eraseParameter4f1()
{
	getFieldRW<FParameter4f1Type>(getFParameter4f1())->eraseValue();
}


const bool Displacement::hasParameter4f1() const
{
	return getFieldRO<FParameter4f1Type>(getFParameter4f1())->hasValue();
}



// Parameter4f0

const Displacement::Parameter4f0ValueType Displacement::DEFAULT_PARAMETER4F0 = vgm::Vec4f(0.f, 0.f, 0.f, 0.f);



const bool Displacement::getParameter4f0( Parameter4f0ValueType& value ) const
{
	return getFieldRO<FParameter4f0Type>(getFParameter4f0())->getValue( value );
}



void Displacement::setParameter4f0( const Parameter4f0ValueType& value )
{
	getFieldRW<FParameter4f0Type>(getFParameter4f0())->setValue( value );
}



void Displacement::eraseParameter4f0()
{
	getFieldRW<FParameter4f0Type>(getFParameter4f0())->eraseValue();
}


const bool Displacement::hasParameter4f0() const
{
	return getFieldRO<FParameter4f0Type>(getFParameter4f0())->hasValue();
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



// Field name accessor(s)
const std::string Displacement::getFDisplacementVS( void )
{
	return "f_displacementVS";
}



const std::string Displacement::getFParameter4f1( void )
{
	return "f_parameter4f1";
}



const std::string Displacement::getFParameter4f0( void )
{
	return "f_parameter4f0";
}



const std::string Displacement::getFDisplacementFunctionVS( void )
{
	return "f_displacementFunctionVS";
}



const std::string Displacement::getFDeclarationsTES( void )
{
	return "f_declarationsTES";
}



const std::string Displacement::getFDeclarationsVS( void )
{
	return "f_declarationsVS";
}



const std::string Displacement::getFDisplacementFunctionTES( void )
{
	return "f_displacementFunctionTES";
}



const std::string Displacement::getFDisplacementTES( void )
{
	return "f_displacementTES";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , Displacement );



const vgd::basic::RegisterNode<Displacement> Displacement::m_registrationInstance;



} // namespace node

} // namespace vgd

