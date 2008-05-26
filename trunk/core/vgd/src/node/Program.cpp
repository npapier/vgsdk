// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Program.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Program );



Program::Program( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add fields
	addField( new FShaderType(getFShader()) );

	// Add dirty flags
	//addDirtyFlag(getDFVertex());
	//addDirtyFlag(getDFFragment());
	//addDirtyFlag(getDFGeometry());

	// Link(s)
	link( getDFNode() );
}



void Program::setToDefaults()
{
	SingleAttribute::setToDefaults();
}



void Program::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// SHADER
bool Program::getShader( const ShaderParameterType param, ShaderValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ShaderParameterType, ShaderValueType >( this, getFShader(), param, value )
		);
}



void Program::setShader( const ShaderParameterType param, ShaderValueType value )
{
	vgd::field::setParameterValue< ShaderParameterType, ShaderValueType >( this, getFShader(), param, value );
}



void Program::eraseShader( const ShaderParameterType param )
{
	vgd::field::eraseParameterValue< ShaderParameterType, ShaderValueType >( this, getFShader(), param );
}



const std::string Program::getFShader()
{
	return "f_shader";
}



/*const std::string Program::getDFVertex()
{
	return "df_vertex";
}



const std::string Program::getDFFragment()
{
	return "df_fragment";
}



const std::string Program::getDFGeometry()
{
	return "df_geometry";
}*/



} // namespace node

} // namespace vgd
