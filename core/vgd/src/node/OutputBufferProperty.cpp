// VGSDK - Copyright (C) 2010, Nicolas Papier.
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
	addField( new FCommandType(getFCommand()) );
	addField( new FTypeType(getFType()) );
	addField( new FCustomCommandType(getFCustomCommand()) );
	addField( new FFormatType(getFFormat()) );

	// Sets link(s)

	link( getDFNode() );
}



void OutputBufferProperty::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setCommand( COLOR );
	setType( INTEGER );

	setFormat( RGB );
}



void OutputBufferProperty::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
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



// Field name accessor(s)
const std::string OutputBufferProperty::getFCommand( void )
{
	return "f_command";
}



const std::string OutputBufferProperty::getFType( void )
{
	return "f_type";
}



const std::string OutputBufferProperty::getFCustomCommand( void )
{
	return "f_customCommand";
}



const std::string OutputBufferProperty::getFFormat( void )
{
	return "f_format";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , OutputBufferProperty );



const vgd::basic::RegisterNode<OutputBufferProperty> OutputBufferProperty::m_registrationInstance;



} // namespace node

} // namespace vgd

