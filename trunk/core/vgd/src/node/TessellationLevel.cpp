// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TessellationLevel.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< TessellationLevel > TessellationLevel::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< TessellationLevel > node( new TessellationLevel(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< TessellationLevel > TessellationLevel::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< TessellationLevel > node = TessellationLevel::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< TessellationLevel > TessellationLevel::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< TessellationLevel > node = TessellationLevel::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



TessellationLevel::TessellationLevel( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FParameter4f1Type(getFParameter4f1()) );
	addField( new FCustomCodeType(getFCustomCode()) );
	addField( new FCustomDeclarationsType(getFCustomDeclarations()) );
	addField( new FMethodType(getFMethod()) );
	addField( new FParameter4f0Type(getFParameter4f0()) );

	// Sets link(s)

	link( getDFNode() );
}



void TessellationLevel::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setCustomCode( std::string() );
	setCustomDeclarations( std::string() );
	setMethod( (UNIFORM) );
}



void TessellationLevel::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setParameter4f1( vgm::Vec4f(0.f, 0.f, 0.f, 0.f) );
	setParameter4f0( vgm::Vec4f(0.f, 0.f, 0.f, 0.f) );
}



// Parameter4f1

const TessellationLevel::Parameter4f1ValueType TessellationLevel::DEFAULT_PARAMETER4F1 = vgm::Vec4f(0.f, 0.f, 0.f, 0.f);



const bool TessellationLevel::getParameter4f1( Parameter4f1ValueType& value ) const
{
	return getFieldRO<FParameter4f1Type>(getFParameter4f1())->getValue( value );
}



void TessellationLevel::setParameter4f1( const Parameter4f1ValueType& value )
{
	getFieldRW<FParameter4f1Type>(getFParameter4f1())->setValue( value );
}



void TessellationLevel::eraseParameter4f1()
{
	getFieldRW<FParameter4f1Type>(getFParameter4f1())->eraseValue();
}


const bool TessellationLevel::hasParameter4f1() const
{
	return getFieldRO<FParameter4f1Type>(getFParameter4f1())->hasValue();
}



// CustomCode

const TessellationLevel::CustomCodeValueType TessellationLevel::DEFAULT_CUSTOMCODE = std::string();



const TessellationLevel::CustomCodeValueType TessellationLevel::getCustomCode() const
{
	return getFieldRO<FCustomCodeType>(getFCustomCode())->getValue();
}



void TessellationLevel::setCustomCode( const CustomCodeValueType value )
{
	getFieldRW<FCustomCodeType>(getFCustomCode())->setValue( value );
}



// CustomDeclarations

const TessellationLevel::CustomDeclarationsValueType TessellationLevel::DEFAULT_CUSTOMDECLARATIONS = std::string();



const TessellationLevel::CustomDeclarationsValueType TessellationLevel::getCustomDeclarations() const
{
	return getFieldRO<FCustomDeclarationsType>(getFCustomDeclarations())->getValue();
}



void TessellationLevel::setCustomDeclarations( const CustomDeclarationsValueType value )
{
	getFieldRW<FCustomDeclarationsType>(getFCustomDeclarations())->setValue( value );
}



// Method

const TessellationLevel::MethodValueType TessellationLevel::getMethod() const
{
	return getFieldRO<FMethodType>(getFMethod())->getValue();
}



void TessellationLevel::setMethod( const MethodValueType value )
{
	getFieldRW<FMethodType>(getFMethod())->setValue( value );
}



// Parameter4f0

const TessellationLevel::Parameter4f0ValueType TessellationLevel::DEFAULT_PARAMETER4F0 = vgm::Vec4f(0.f, 0.f, 0.f, 0.f);



const bool TessellationLevel::getParameter4f0( Parameter4f0ValueType& value ) const
{
	return getFieldRO<FParameter4f0Type>(getFParameter4f0())->getValue( value );
}



void TessellationLevel::setParameter4f0( const Parameter4f0ValueType& value )
{
	getFieldRW<FParameter4f0Type>(getFParameter4f0())->setValue( value );
}



void TessellationLevel::eraseParameter4f0()
{
	getFieldRW<FParameter4f0Type>(getFParameter4f0())->eraseValue();
}


const bool TessellationLevel::hasParameter4f0() const
{
	return getFieldRO<FParameter4f0Type>(getFParameter4f0())->hasValue();
}



// Field name accessor(s)
const std::string TessellationLevel::getFParameter4f1( void )
{
	return "f_parameter4f1";
}



const std::string TessellationLevel::getFCustomCode( void )
{
	return "f_customCode";
}



const std::string TessellationLevel::getFCustomDeclarations( void )
{
	return "f_customDeclarations";
}



const std::string TessellationLevel::getFMethod( void )
{
	return "f_method";
}



const std::string TessellationLevel::getFParameter4f0( void )
{
	return "f_parameter4f0";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , TessellationLevel );



const vgd::basic::RegisterNode<TessellationLevel> TessellationLevel::m_registrationInstance;



} // namespace node

} // namespace vgd

