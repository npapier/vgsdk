// VGSDK - Copyright (C) 2014, Nicolas Papier.
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
	addField( new FOpenglDebugOutputType(getFOpenglDebugOutput()) );
	addField( new FOpenglDirectStateAccessType(getFOpenglDirectStateAccess()) );

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
	setOpenglDebugOutput( (false) );
	setOpenglDirectStateAccess( (false) );
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



// OpenglDebugOutput

const EngineProperties::OpenglDebugOutputValueType EngineProperties::DEFAULT_OPENGLDEBUGOUTPUT = (false);



const bool EngineProperties::getOpenglDebugOutput( OpenglDebugOutputValueType& value ) const
{
	return getFieldRO<FOpenglDebugOutputType>(getFOpenglDebugOutput())->getValue( value );
}



void EngineProperties::setOpenglDebugOutput( const OpenglDebugOutputValueType& value )
{
	getFieldRW<FOpenglDebugOutputType>(getFOpenglDebugOutput())->setValue( value );
}



void EngineProperties::eraseOpenglDebugOutput()
{
	getFieldRW<FOpenglDebugOutputType>(getFOpenglDebugOutput())->eraseValue();
}


const bool EngineProperties::hasOpenglDebugOutput() const
{
	return getFieldRO<FOpenglDebugOutputType>(getFOpenglDebugOutput())->hasValue();
}



// OpenglDirectStateAccess

const EngineProperties::OpenglDirectStateAccessValueType EngineProperties::DEFAULT_OPENGLDIRECTSTATEACCESS = (false);



const bool EngineProperties::getOpenglDirectStateAccess( OpenglDirectStateAccessValueType& value ) const
{
	return getFieldRO<FOpenglDirectStateAccessType>(getFOpenglDirectStateAccess())->getValue( value );
}



void EngineProperties::setOpenglDirectStateAccess( const OpenglDirectStateAccessValueType& value )
{
	getFieldRW<FOpenglDirectStateAccessType>(getFOpenglDirectStateAccess())->setValue( value );
}



void EngineProperties::eraseOpenglDirectStateAccess()
{
	getFieldRW<FOpenglDirectStateAccessType>(getFOpenglDirectStateAccess())->eraseValue();
}


const bool EngineProperties::hasOpenglDirectStateAccess() const
{
	return getFieldRO<FOpenglDirectStateAccessType>(getFOpenglDirectStateAccess())->hasValue();
}



// Field name accessor(s)
const std::string EngineProperties::getFMaxAnisotropy( void )
{
	return "f_maxAnisotropy";
}



const std::string EngineProperties::getFOpenglDebugOutput( void )
{
	return "f_openglDebugOutput";
}



const std::string EngineProperties::getFOpenglDirectStateAccess( void )
{
	return "f_openglDirectStateAccess";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( EngineProperties );



const vgd::basic::RegisterNode<EngineProperties> EngineProperties::m_registrationInstance;



} // namespace node

} // namespace vgd

