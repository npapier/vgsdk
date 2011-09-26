// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/OutputBufferProperty.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< OutputBufferProperty > OutputBufferProperty::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< OutputBufferProperty > node( new OutputBufferProperty(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< OutputBufferProperty > OutputBufferProperty::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< OutputBufferProperty > node = OutputBufferProperty::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< OutputBufferProperty > OutputBufferProperty::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< OutputBufferProperty > node = OutputBufferProperty::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



OutputBufferProperty::OutputBufferProperty( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Adds field(s)
	addField( new FSizeSemanticType(getFSizeSemantic()) );
	addField( new FCustomCommandType(getFCustomCommand()) );
	addField( new FFormatType(getFFormat()) );
	addField( new FCommandType(getFCommand()) );
	addField( new FTypeType(getFType()) );
	addField( new FCustomDeclarationType(getFCustomDeclaration()) );
	addField( new FSizeType(getFSize()) );

	// Sets link(s)

	link( getDFNode() );
}



void OutputBufferProperty::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setSizeSemantic( SCALE_FACTOR );

	setFormat( RGB );
	setCommand( COLOR );
	setType( INTEGER );

	setSize( vgm::Vec2f(1.f, 1.f) );
}



void OutputBufferProperty::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
}



// SizeSemantic
const OutputBufferProperty::SizeSemanticValueType OutputBufferProperty::getSizeSemantic() const
{
	return getFieldRO<FSizeSemanticType>(getFSizeSemantic())->getValue();
}



void OutputBufferProperty::setSizeSemantic( const SizeSemanticValueType value )
{
	getFieldRW<FSizeSemanticType>(getFSizeSemantic())->setValue( value );
}



// CustomCommand
const OutputBufferProperty::CustomCommandValueType OutputBufferProperty::getCustomCommand() const
{
	return getFieldRO<FCustomCommandType>(getFCustomCommand())->getValue();
}



void OutputBufferProperty::setCustomCommand( const CustomCommandValueType value )
{
	getFieldRW<FCustomCommandType>(getFCustomCommand())->setValue( value );
}



// Format
const OutputBufferProperty::FormatValueType OutputBufferProperty::getFormat() const
{
	return getFieldRO<FFormatType>(getFFormat())->getValue();
}



void OutputBufferProperty::setFormat( const FormatValueType value )
{
	getFieldRW<FFormatType>(getFFormat())->setValue( value );
}



// Command
const OutputBufferProperty::CommandValueType OutputBufferProperty::getCommand() const
{
	return getFieldRO<FCommandType>(getFCommand())->getValue();
}



void OutputBufferProperty::setCommand( const CommandValueType value )
{
	getFieldRW<FCommandType>(getFCommand())->setValue( value );
}



// Type
const OutputBufferProperty::TypeValueType OutputBufferProperty::getType() const
{
	return getFieldRO<FTypeType>(getFType())->getValue();
}



void OutputBufferProperty::setType( const TypeValueType value )
{
	getFieldRW<FTypeType>(getFType())->setValue( value );
}



// CustomDeclaration
const OutputBufferProperty::CustomDeclarationValueType OutputBufferProperty::getCustomDeclaration() const
{
	return getFieldRO<FCustomDeclarationType>(getFCustomDeclaration())->getValue();
}



void OutputBufferProperty::setCustomDeclaration( const CustomDeclarationValueType value )
{
	getFieldRW<FCustomDeclarationType>(getFCustomDeclaration())->setValue( value );
}



// Size
const OutputBufferProperty::SizeValueType OutputBufferProperty::getSize() const
{
	return getFieldRO<FSizeType>(getFSize())->getValue();
}



void OutputBufferProperty::setSize( const SizeValueType value )
{
	getFieldRW<FSizeType>(getFSize())->setValue( value );
}



// Field name accessor(s)
const std::string OutputBufferProperty::getFSizeSemantic( void )
{
	return "f_sizeSemantic";
}



const std::string OutputBufferProperty::getFCustomCommand( void )
{
	return "f_customCommand";
}



const std::string OutputBufferProperty::getFFormat( void )
{
	return "f_format";
}



const std::string OutputBufferProperty::getFCommand( void )
{
	return "f_command";
}



const std::string OutputBufferProperty::getFType( void )
{
	return "f_type";
}



const std::string OutputBufferProperty::getFCustomDeclaration( void )
{
	return "f_customDeclaration";
}



const std::string OutputBufferProperty::getFSize( void )
{
	return "f_size";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , OutputBufferProperty );



const vgd::basic::RegisterNode<OutputBufferProperty> OutputBufferProperty::m_registrationInstance;



} // namespace node

} // namespace vgd

