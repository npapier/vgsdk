// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Program.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Program > Program::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Program > node( new Program(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Program > Program::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Program > node = Program::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Program > Program::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Program > node = Program::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Program::Program( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FVertexType(getFVertex()) );
	addField( new FVertexUseType(getFVertexUse()) );
	addField( new FTessellationControlType(getFTessellationControl()) );
	addField( new FTessellationEvaluationType(getFTessellationEvaluation()) );
	addField( new FTessellationUseType(getFTessellationUse()) );
	addField( new FGeometryType(getFGeometry()) );
	addField( new FGeometryUseType(getFGeometryUse()) );
	addField( new FFragmentType(getFFragment()) );
	addField( new FFragmentUseType(getFFragmentUse()) );

	// Sets link(s)

	link( getDFNode() );
}



void Program::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setVertex( std::string() );
	setVertexUse( (true) );
	setTessellationControl( std::string() );
	setTessellationEvaluation( std::string() );
	setTessellationUse( (false) );
	setGeometry( std::string() );
	setGeometryUse( (false) );
	setFragment( std::string() );
	setFragmentUse( (true) );
}



void Program::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// Vertex

const Program::VertexValueType Program::DEFAULT_VERTEX = std::string();



const Program::VertexValueType Program::getVertex() const
{
	return getFieldRO<FVertexType>(getFVertex())->getValue();
}



void Program::setVertex( const VertexValueType value )
{
	getFieldRW<FVertexType>(getFVertex())->setValue( value );
}



// VertexUse

const Program::VertexUseValueType Program::DEFAULT_VERTEXUSE = (true);



const Program::VertexUseValueType Program::getVertexUse() const
{
	return getFieldRO<FVertexUseType>(getFVertexUse())->getValue();
}



void Program::setVertexUse( const VertexUseValueType value )
{
	getFieldRW<FVertexUseType>(getFVertexUse())->setValue( value );
}



// TessellationControl

const Program::TessellationControlValueType Program::DEFAULT_TESSELLATIONCONTROL = std::string();



const Program::TessellationControlValueType Program::getTessellationControl() const
{
	return getFieldRO<FTessellationControlType>(getFTessellationControl())->getValue();
}



void Program::setTessellationControl( const TessellationControlValueType value )
{
	getFieldRW<FTessellationControlType>(getFTessellationControl())->setValue( value );
}



// TessellationEvaluation

const Program::TessellationEvaluationValueType Program::DEFAULT_TESSELLATIONEVALUATION = std::string();



const Program::TessellationEvaluationValueType Program::getTessellationEvaluation() const
{
	return getFieldRO<FTessellationEvaluationType>(getFTessellationEvaluation())->getValue();
}



void Program::setTessellationEvaluation( const TessellationEvaluationValueType value )
{
	getFieldRW<FTessellationEvaluationType>(getFTessellationEvaluation())->setValue( value );
}



// TessellationUse

const Program::TessellationUseValueType Program::DEFAULT_TESSELLATIONUSE = (false);



const Program::TessellationUseValueType Program::getTessellationUse() const
{
	return getFieldRO<FTessellationUseType>(getFTessellationUse())->getValue();
}



void Program::setTessellationUse( const TessellationUseValueType value )
{
	getFieldRW<FTessellationUseType>(getFTessellationUse())->setValue( value );
}



// Geometry

const Program::GeometryValueType Program::DEFAULT_GEOMETRY = std::string();



const Program::GeometryValueType Program::getGeometry() const
{
	return getFieldRO<FGeometryType>(getFGeometry())->getValue();
}



void Program::setGeometry( const GeometryValueType value )
{
	getFieldRW<FGeometryType>(getFGeometry())->setValue( value );
}



// GeometryUse

const Program::GeometryUseValueType Program::DEFAULT_GEOMETRYUSE = (false);



const Program::GeometryUseValueType Program::getGeometryUse() const
{
	return getFieldRO<FGeometryUseType>(getFGeometryUse())->getValue();
}



void Program::setGeometryUse( const GeometryUseValueType value )
{
	getFieldRW<FGeometryUseType>(getFGeometryUse())->setValue( value );
}



// Fragment

const Program::FragmentValueType Program::DEFAULT_FRAGMENT = std::string();



const Program::FragmentValueType Program::getFragment() const
{
	return getFieldRO<FFragmentType>(getFFragment())->getValue();
}



void Program::setFragment( const FragmentValueType value )
{
	getFieldRW<FFragmentType>(getFFragment())->setValue( value );
}



// FragmentUse

const Program::FragmentUseValueType Program::DEFAULT_FRAGMENTUSE = (true);



const Program::FragmentUseValueType Program::getFragmentUse() const
{
	return getFieldRO<FFragmentUseType>(getFFragmentUse())->getValue();
}



void Program::setFragmentUse( const FragmentUseValueType value )
{
	getFieldRW<FFragmentUseType>(getFFragmentUse())->setValue( value );
}



// Field name accessor(s)
const std::string Program::getFVertex( void )
{
	return "f_vertex";
}



const std::string Program::getFVertexUse( void )
{
	return "f_vertexUse";
}



const std::string Program::getFTessellationControl( void )
{
	return "f_tessellationControl";
}



const std::string Program::getFTessellationEvaluation( void )
{
	return "f_tessellationEvaluation";
}



const std::string Program::getFTessellationUse( void )
{
	return "f_tessellationUse";
}



const std::string Program::getFGeometry( void )
{
	return "f_geometry";
}



const std::string Program::getFGeometryUse( void )
{
	return "f_geometryUse";
}



const std::string Program::getFFragment( void )
{
	return "f_fragment";
}



const std::string Program::getFFragmentUse( void )
{
	return "f_fragmentUse";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , Program );



const vgd::basic::RegisterNode<Program> Program::m_registrationInstance;



} // namespace node

} // namespace vgd

