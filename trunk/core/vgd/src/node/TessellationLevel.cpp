// VGSDK - Copyright (C) 2014, Nicolas Papier.
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
	addField( new FMethodType(getFMethod()) );
	addField( new FCustomDeclarationsType(getFCustomDeclarations()) );
	addField( new FCustomCodeType(getFCustomCode()) );
	addField( new FComposeModeType(getFComposeMode()) );

	// Sets link(s)

	link( getDFNode() );
}



void TessellationLevel::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setMethod( (UNIFORM) );
	setCustomDeclarations( std::string() );
	setCustomCode( std::string() );
	setComposeMode( (REPLACE) );
}



void TessellationLevel::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
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



// ComposeMode

const TessellationLevel::ComposeModeValueType TessellationLevel::getComposeMode() const
{
	return getFieldRO<FComposeModeType>(getFComposeMode())->getValue();
}



void TessellationLevel::setComposeMode( const ComposeModeValueType value )
{
	getFieldRW<FComposeModeType>(getFComposeMode())->setValue( value );
}



// Field name accessor(s)
const std::string TessellationLevel::getFMethod( void )
{
	return "f_method";
}



const std::string TessellationLevel::getFCustomDeclarations( void )
{
	return "f_customDeclarations";
}



const std::string TessellationLevel::getFCustomCode( void )
{
	return "f_customCode";
}



const std::string TessellationLevel::getFComposeMode( void )
{
	return "f_composeMode";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( TessellationLevel );



const vgd::basic::RegisterNode<TessellationLevel> TessellationLevel::m_registrationInstance;



} // namespace node

} // namespace vgd

