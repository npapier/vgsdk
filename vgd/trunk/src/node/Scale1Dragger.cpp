// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Scale1Dragger.hpp"

#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgd/node/WireBox.hpp>

#include <vgm/Matrix.hpp>



namespace vgd
{

namespace node
{



META_NODE_CPP( Scale1Dragger );



Scale1Dragger::Scale1Dragger( const std::string nodeName ) :
	vgd::node::Dragger( nodeName )
{
	// Add field
	addField( new FScaleType(getFScale()) );
	
	// Link(s)
	link( getDFNode() );
}



void Scale1Dragger::setToDefaults()
{
	Dragger::setToDefaults();
	setCurrentState( SCALE1DRAGGER_DEFAULT );

	// Add feedback scene-graph.
	setBoundingBoxAndAxisFeedback();	
}



void Scale1Dragger::setOptionalsToDefaults()
{
	Dragger::setOptionalsToDefaults();
}



void Scale1Dragger::setTransformationToDefaults()
{
	setScale( 1.f );
}



void Scale1Dragger::setBindingsToDefaults()
{
	// .bindings
	using vgd::event::ButtonStateSet;
	using vgd::event::KeyboardButtonEvent;	
	using vgd::event::MouseButtonEvent;
	
	// scale_x*
	ButtonStateSet bssScaleX;
	setBindings( SCALE_X, bssScaleX );
	
	//
	bssScaleX.setDown( MouseButtonEvent::MOUSE_BUTTON_1 );
	setBindings( SCALE_X_ACTIVE, bssScaleX );
}



void Scale1Dragger::setNullFeedback()
{
	setupNullFeedback( 3 );
}



void Scale1Dragger::setBoundingBoxFeedback()
{
	setupBoundingBoxFeedback( 3 );
}



void Scale1Dragger::setBoundingBoxAndAxisFeedback()
{
	vgd::Shp< vgd::node::VertexShape > pLine = vgd::node::VertexShape::create("line");

	// Initialize geometry.

	// VERTEX
	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex = pLine->getFVertexRW();
	vertex->reserve( 2 );

	vertex->push_back( vgm::Vec3f(-0.5 - 0.2f, 0.f, 0.f)	);
	vertex->push_back( vgm::Vec3f(0.5f + 0.2f, 0.f, 0.f) );

	// VERTEX INDEX
	vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex		= pLine->getFVertexIndexRW();
	vertexIndex->reserve( 2 );
	
	vertexIndex->push_back(0);
	vertexIndex->push_back(1);

	// PRIMITIVE
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive	= pLine->getFPrimitiveRW();
	vgd::node::Primitive prim( vgd::node::Primitive::LINE_STRIP, 0, vertexIndex->size() );
	primitive->push_back( prim );
	
	vgd::Shp< vgd::node::Switch > pFeedbackSwitch = getFeedbackSwitchNode();
	
	pFeedbackSwitch->removeAllChildren();
	
	vgd::Shp< vgd::node::WireBox >	pWireBox	= vgd::node::WireBox::create("");

	vgd::Shp< vgd::node::Group > pGroup = vgd::node::Group::create("group");
	pGroup->addChild( pWireBox );
	pGroup->addChild( pLine );	
	
	for(	uint32	i = 0;
			i < 3;
			++i )
	{
		pFeedbackSwitch->addChild( pGroup );
	}
}



// SCALE
const float Scale1Dragger::getScale( void ) const
{
	return ( getFieldRO<FScaleType>(getFScale())->getValue() );
}



void Scale1Dragger::setScale( const float scale )
{
	getFieldRW<FScaleType>(getFScale())->setValue( scale );
}



vgm::MatrixR Scale1Dragger::computeMatrixFromFields() const
{
	vgm::MatrixR matrix;
	
	matrix.setScale( vgm::Vec3f( getScale(), 1.f, 1.f ) );

	return ( matrix );
}



const std::string Scale1Dragger::getFScale()
{
	return ( "f_scale" );
}



} // namespace node

} // namespace vgd
