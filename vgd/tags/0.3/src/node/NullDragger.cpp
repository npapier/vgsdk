// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/NullDragger.hpp"

#include <vgm/Matrix.hpp>



namespace vgd
{

namespace node
{



META_NODE_CPP( NullDragger );



NullDragger::NullDragger( const std::string nodeName ) :
	vgd::node::Dragger( nodeName )
{
}



void NullDragger::setToDefaults()
{
	Dragger::setToDefaults();
	setCurrentState( NULLDRAGGER_DEFAULT );

	// Add feedback scene-graph.
	setBoundingBoxFeedback();	
}



void NullDragger::setOptionalsToDefaults()
{
	Dragger::setOptionalsToDefaults();
}



void NullDragger::setTransformationToDefaults()
{
}



void NullDragger::setBindingsToDefaults()
{
	// .bindings
	using vgd::event::ButtonStateSet;
	
	// 
	ButtonStateSet bss;
	setBindings( NONE, bss );
}



void NullDragger::setNullFeedback()
{
	setupNullFeedback( 1 );
}



void NullDragger::setBoundingBoxFeedback()
{
	setupBoundingBoxFeedback( 1 );
}



vgm::MatrixR NullDragger::computeMatrixFromFields() const
{
	return ( vgm::MatrixR::getIdentity() );
}



} // namespace node

} // namespace vgd
