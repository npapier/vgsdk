// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Dragger.hpp"

#include <limits>
#include "vgd/field/TAccessors.hpp"
#include "vgd/node/Group.hpp"
#include "vgd/node/WireBox.hpp"
#include "vgd/node/MatrixTransform.hpp"




namespace vgd
{

namespace node
{



Dragger::Dragger( const std::string nodeName ) :
	vgd::node::IDragger( nodeName ),
	m_startingPoint(std::numeric_limits<float>::max(), std::numeric_limits<float>::max() )
{
	// Add field
	addField( new FFeedbackType(getFFeedback()) );	
	addField( new FBindingsType(getFBindings()) );	

	// Link(s)
	link( getDFNode() );
}



void Dragger::setToDefaults()
{
	IDragger::setToDefaults();
	
	// Initialize dragger.root (construct sub scene graph).
	using vgd::node::Group;
	using vgd::node::MatrixTransform;
	using vgd::node::SurroundScale;	
	using vgd::node::TransformSeparator;

	// sg
	vgd::Shp< Group >						pGroup( Group::create("dragger.group") );

	vgd::Shp< MatrixTransform >		pMatrixTransform( MatrixTransform::create("dragger.group.matrixTransform") );

	// feedback sg
	vgd::Shp< TransformSeparator >pTransformSeparator( TransformSeparator::create("dragger.group.transformSeparator") );
	
	vgd::Shp< SurroundScale >		pSurroundScale( SurroundScale::create("dragger.group.transformSeparator.surroundScale") );
	pSurroundScale->setComposeTransformation( false );

	vgd::Shp< Switch >				pSwitch( Switch::create("dragger.group.transformSeparator.switch") );

	setRoot( pGroup );
	pGroup->addChild( pMatrixTransform );
	pGroup->addChild( pTransformSeparator );
	pTransformSeparator->addChild( pSurroundScale );
	pTransformSeparator->addChild( pSwitch );

	// init. fields
	setFeedback( false );
	
	//
	setBindingsToDefaults();
	setTransformationToDefaults();
}



void Dragger::setOptionalsToDefaults()
{
	IDragger::setOptionalsToDefaults();
}



// FEEDBACK
const Dragger::FeedbackValueType Dragger::getFeedback() const
{
	return ( getFieldRO<FFeedbackType>(getFFeedback())->getValue() );
}



void Dragger::setFeedback( const FeedbackValueType value )
{
	getFieldRW<FFeedbackType>(getFFeedback())->setValue( value );
}



// SURROUND
void Dragger::setSurround( const SurroundValueType value )
{
	IDragger::setSurround( value );
	
	// update surround node.
	getSurroundNode()->setSurround( value );
}



// STATE
void Dragger::setCurrentState( const CurrentStateValueType value )
{
	IDragger::setCurrentState( value );

	// update visual feedback
	if ( getFeedback() )
	{
		// switch to the feedback sub-scene graph		
		getFeedbackSwitchNode()->setWhichChild( value );
	}
	else
	{
		// disable visual feedback
		getFeedbackSwitchNode()->setWhichChild( vgd::node::Switch::SWITCH_NONE );
	}
}



// BINDINGS
bool Dragger::getBindings( const BindingsParameterType param, BindingsValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< BindingsParameterType, BindingsValueType >( this, getFBindings(), param, value )
		);
}



void Dragger::setBindings( const BindingsParameterType param, BindingsValueType value )
{
	vgd::field::setParameterValue< BindingsParameterType, BindingsValueType >( this, getFBindings(), param, value );
}



void Dragger::eraseBindings( const BindingsParameterType param )
{
	vgd::field::eraseParameterValue< BindingsParameterType, BindingsValueType >( this, getFBindings(), param );
}



const std::string Dragger::getFFeedback()
{
	return ( "f_feedback" );
}



const std::string Dragger::getFBindings()
{
	return ( "f_bindings" );
}



const vgm::Vec2f&	Dragger::getStartingPoint() const
{
	return ( m_startingPoint );
}



void Dragger::setStartingPoint( const vgm::Vec2f& startingPoint )
{
	m_startingPoint = startingPoint;
}



bool Dragger::isStartingPoint() const
{
	return ( m_startingPoint == vgm::Vec2f( std::numeric_limits<float>::max(), std::numeric_limits<float>::max() ) );
}



const vgm::MatrixR& Dragger::getMatrix() const
{
	const vgm::MatrixR& matrix( getMatrixTransformNode()->getMatrix() );
	
	return ( matrix );
}



void Dragger::setMatrix( const vgm::MatrixR& matrix )
{
	getMatrixTransformNode()->setMatrix( matrix );
}



vgd::Shp< vgd::node::MatrixTransform > Dragger::getMatrixTransformNode() const
{
	using vgd::node::MatrixTransform;
	
	vgd::Shp< MatrixTransform > pMatrixTransform = getRoot()->getChild<vgd::node::MatrixTransform>(0);
	
	return ( pMatrixTransform );
}



vgd::Shp< vgd::node::SurroundScale > Dragger::getSurroundNode() const
{
	using vgd::node::SurroundScale;
	
	vgd::Shp< vgd::node::TransformSeparator > pTransformSeparator = getRoot()->getChild<vgd::node::TransformSeparator>(1);
	
	vgd::Shp< SurroundScale > pSurroundScale = pTransformSeparator->getChild<vgd::node::SurroundScale>(0);

	return ( pSurroundScale );
}



vgd::Shp< vgd::node::Switch > Dragger::getFeedbackSwitchNode() const
{
	using vgd::node::Switch;
	
	vgd::Shp< vgd::node::TransformSeparator > pTransformSeparator = getRoot()->getChild<vgd::node::TransformSeparator>(1);
	
	vgd::Shp< Switch > pSwitch = pTransformSeparator->getChild<vgd::node::Switch>(1);

	return ( pSwitch );
}



void Dragger::setupNullFeedback( const uint32 numberOfState )
{
	vgd::Shp< vgd::node::Switch > pFeedbackSwitch = getFeedbackSwitchNode();
	
	pFeedbackSwitch->removeAllChildren();
	
	vgd::Shp< vgd::node::Group> pGroup = vgd::node::Group::create("");

	for(	uint32	i = 0;
			i < numberOfState;
			++i )
	{
		pFeedbackSwitch->addChild( pGroup );
	}
}



void Dragger::setupBoundingBoxFeedback( const uint32 numberOfState )
{
	vgd::Shp< vgd::node::Switch > pFeedbackSwitch = getFeedbackSwitchNode();
	
	pFeedbackSwitch->removeAllChildren();
	
	vgd::Shp< vgd::node::WireBox >	pWireBox	= vgd::node::WireBox::create("");
	
	for(	uint32	i = 0;
			i < numberOfState;
			++i )
	{
		pFeedbackSwitch->addChild( pWireBox );
	}
}



} // namespace node

} // namespace vgd
