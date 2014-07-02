// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Uniforms.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Uniforms > Uniforms::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Uniforms > node( new Uniforms(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Uniforms > Uniforms::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Uniforms > node = Uniforms::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Uniforms > Uniforms::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Uniforms > node = Uniforms::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Uniforms::Uniforms( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FComposeModeType(getFComposeMode()) );

	// Sets link(s)

	link( getDFNode() );
}



void Uniforms::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setComposeMode( (REPLACE) );
}



void Uniforms::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// ComposeMode

const Uniforms::ComposeModeValueType Uniforms::getComposeMode() const
{
	return getFieldRO<FComposeModeType>(getFComposeMode())->getValue();
}



void Uniforms::setComposeMode( const ComposeModeValueType value )
{
	getFieldRW<FComposeModeType>(getFComposeMode())->setValue( value );
}



// Field name accessor(s)
const std::string Uniforms::getFComposeMode( void )
{
	return "f_composeMode";
}



namespace
{

const bool isAnUniformName( const std::string& name )
{
	const bool retVal = (name.size()>=2) && (name[0] == 'u') && (name[1] >= 'A') && (name[1] <= 'Z');
	return retVal;
}

}


void Uniforms::clearUniforms()
{
	std::vector< std::string > fieldNames;
	getFieldNames(fieldNames);

	for( auto	i		= fieldNames.begin(),
				iEnd	= fieldNames.end();
		i != iEnd;
		++i )
	{
		const std::string& fieldName = *i;
		if ( isAnUniformName(fieldName) )
		{
			// This is the name of an uniform variable, so remove it
			removeField( fieldName );
		}
		// else not a field containing an uniform, so do nothing
	}
}


const bool Uniforms::removeUniform( const std::string& name )
{
	if ( isAnUniformName(name) )
	{
		removeField(name);
		return true;
	}
	else
	{
		return false;
	}
}


const bool Uniforms::isUniform( const std::string& name ) const
{
	return isAnUniformName(name) && isField( name );
}
IMPLEMENT_INDEXABLE_CLASS_CPP( Uniforms );
//IMPLEMENT_INDEXABLE_CLASS_CPP( , Uniforms );



const vgd::basic::RegisterNode<Uniforms> Uniforms::m_registrationInstance;



} // namespace node

} // namespace vgd

