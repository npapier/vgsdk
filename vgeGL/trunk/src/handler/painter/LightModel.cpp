// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/LightModel.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/LightModel.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"

#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{

META_HANDLER_CPP( LightModel );



/*const vge::service::List LightModel::getServices() const
{
	vge::service::List list;
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );

	return ( list );
}*/



const vge::handler::Handler::TargetVector LightModel::getTargets() const
{
	TargetVector targets;
	
	targets.reserve( 1 );
	targets.push_back( vgd::node::LightModel::getClassIndexStatic() );

	return ( targets );
}



void LightModel::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	//assert( dynamic_cast< vgd::node::LightModel* >(pNode) != 0 );
	//vgd::node::LightModel *pCastedNode = static_cast< vgd::node::LightModel* >(pNode);
	
	vgeGL::rc::applyUsingDisplayList< vgd::node::LightModel, LightModel >( pEngine, pNode, this );
}



void LightModel::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
{
}



void LightModel::setToDefaults()
{
}



void LightModel::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::LightModel *pNode )
{
	bool	bDefined;
	
	// MODEL
	vgd::node::LightModel::ModelValueType	modelValue;

	bDefined = pNode->getModel( modelValue );
	
	if ( bDefined )
	{
		switch ( modelValue )
		{
			case vgd::node::LightModel::LIGHTING_OFF:
				glDisable( GL_LIGHTING );
				break;

			case vgd::node::LightModel::STANDARD_PER_VERTEX:
				glEnable( GL_LIGHTING );
				break;

			case vgd::node::LightModel::STANDARD_PER_PIXEL:
				assert( false && "Not yet implemented" );
				break;
				
			default:
				assert( false && "Unknown LightModel.model value." );
		}
	}
	
	// AMBIENT
	vgm::Vec4f	ambientValue;
	bDefined = pNode->getAmbient( ambientValue );
	
	if ( bDefined )
	{
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientValue.getValue() );
	}
	
	// VIEWER
	vgd::node::LightModel::ViewerValueType	viewerValue;
	bDefined = pNode->getViewer( viewerValue );
	
	if ( bDefined )
	{
		if ( viewerValue == vgd::node::LightModel::AT_INFINITY )
		{
			glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, 0.f );
		}
		else
		{
			assert( viewerValue == vgd::node::LightModel::AT_EYE );
			glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, 1.f );
		}
	}

	// TWOSIDED
	vgd::node::LightModel::TwoSidedValueType	twosidedValue;
	bDefined = pNode->getTwoSided( twosidedValue );
	
	if ( bDefined )
	{
		glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, twosidedValue ? GL_TRUE : GL_FALSE );
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
