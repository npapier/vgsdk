// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/node/LightModelEditor.hpp"

#include <boost/assign/list_of.hpp>

#include <gtkmm/colorbutton.h>
#include <gtkmm/separator.h>
#include <gtkmm/tooltips.h>

#include <vgd/node/LightModel.hpp>
#include <vgUI/Canvas.hpp>

#include "vgGTK/convenience.hpp"



namespace vgGTK
{

namespace node
{



LightModelEditor::LightModelEditor( vgd::Shp< vgd::node::LightModel > lightModel, vgUI::Canvas * canvas )
:	m_lightModel			( lightModel							),
	m_canvas				( canvas								),	
	m_lastModelValue		( vgd::node::LightModel::DEFAULT_MODEL	),
	m_modelButton			( 0										),		
	m_modelBox				( 0										),		
	m_lastAmbientValue		( 1.f, 1.f, 1.f, 1.f					),
	m_ambientButton			( 0										),
	m_ambientColorButton	( 0										),	
	m_lastViewerValue		( vgd::node::LightModel::DEFAULT_VIEWER	),
	m_viewerButton			( 0										),		
	m_viewerBox				( 0										),
	m_lastTwoSidedValue		( true									),
	m_twoSidedButton		( 0										),		
	m_twoSidedValueButton	( 0										)		
{
	createContent();
	refreshWidgets();
}



void LightModelEditor::createContent()
{
	using boost::assign::list_of;
	using vgd::node::LightModel;
	
	
	// Model
	const ModelBox::ValueContainer modelValues =	list_of< ModelBox::Value >( LightModel::LIGHTING_OFF, "Lighting Off" )
													( LightModel::STANDARD_PER_VERTEX, "Standard Per Vertex" )
													( LightModel::STANDARD_PER_PIXEL, "Standard Per Pixel" );
	
	m_modelButton	= Gtk::manage( new Gtk::CheckButton("Model") );
	m_modelBox		= Gtk::manage( new ModelBox(modelValues, sigc::mem_fun(this,&LightModelEditor::onModelValue)) );
	
	m_modelButton->signal_clicked().connect( sigc::mem_fun(this, &LightModelEditor::onModel) );
	m_modelBox->set_border_width( 12 );
	
	pack_start( *m_modelButton, Gtk::PACK_SHRINK );
	pack_start( *m_modelBox, Gtk::PACK_SHRINK );
	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK, 12 );
	
	
	// Ambient
	Gtk::VBox	* ambientBox	= Gtk::manage( new Gtk::VBox() );
	
	m_ambientButton			= Gtk::manage( new Gtk::CheckButton("Ambient") );
	m_ambientColorButton	= Gtk::manage( new Gtk::ColorButton() );
	
	m_ambientButton->signal_clicked().connect( sigc::mem_fun(this, &LightModelEditor::onAmbient) );
	m_ambientColorButton->signal_color_set().connect( sigc::mem_fun(this, &LightModelEditor::onAmbientValue) );
	
	ambientBox->set_border_width( 12 );
	ambientBox->add( *m_ambientColorButton );
	
	pack_start( *m_ambientButton, Gtk::PACK_SHRINK );
	pack_start( *ambientBox, Gtk::PACK_SHRINK );
	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK, 12 );
	
	
	// Viewer
	const ViewerBox::ValueContainer viewerValues =	list_of< ViewerBox::Value >( LightModel::AT_INFINITY, "At Infinity" )
													( LightModel::AT_EYE, "At Eye" );
	
	m_viewerButton	= Gtk::manage( new Gtk::CheckButton("Viewer") );
	m_viewerBox		= Gtk::manage( new ViewerBox(viewerValues, sigc::mem_fun(this,&LightModelEditor::onViewerValue)) );
	
	m_viewerButton->signal_clicked().connect( sigc::mem_fun(this, &LightModelEditor::onViewer) );
	m_viewerBox->set_border_width( 12 );
	
	pack_start( *m_viewerButton, Gtk::PACK_SHRINK );
	pack_start( *m_viewerBox, Gtk::PACK_SHRINK );
	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK, 12 );
	
	
	// TwoSided
	Gtk::VBox	* twoSidedBox	= Gtk::manage( new Gtk::VBox() );
	
	m_twoSidedButton		= Gtk::manage( new Gtk::CheckButton("Two Sided") );
	m_twoSidedValueButton	= Gtk::manage( new Gtk::CheckButton("Active") );
	
	m_twoSidedButton->signal_clicked().connect( sigc::mem_fun(this, &LightModelEditor::onTwoSided) );
	m_twoSidedValueButton->signal_clicked().connect( sigc::mem_fun(this, &LightModelEditor::onTwoSidedValue) );
	
	twoSidedBox->set_border_width( 12 );
	twoSidedBox->add( *m_twoSidedValueButton );
	
	pack_start( *m_twoSidedButton, Gtk::PACK_SHRINK );
	pack_start( *twoSidedBox, Gtk::PACK_SHRINK );
	
	
	// Tooltips.
	Gtk::Tooltips	* tooltips = Gtk::manage( new Gtk::Tooltips() );
	
	tooltips->set_tip( *m_modelButton, "Specifies the lighting model" );
	tooltips->set_tip( *m_ambientButton, "Specifies the ambient color" );
	tooltips->set_tip( *m_viewerButton, "Specifies the viewer position" );
	tooltips->set_tip( *m_twoSidedButton, "Specifies two-sided lighting" );	
}



void LightModelEditor::onAmbient()
{
	assert( m_lightModel );
	assert( m_ambientButton );
	
	if( m_ambientButton->get_active() )
	{
		m_lightModel->setAmbient( m_lastAmbientValue );
	}
	else
	{
		m_lightModel->getAmbient( m_lastAmbientValue );
		m_lightModel->eraseAmbient();
	}
	refreshWidgets();
	refreshCanvas();
}



void LightModelEditor::onAmbientValue()
{
	assert( m_lightModel );
	assert( m_ambientColorButton );
	
	m_lightModel->setAmbient( color_cast(m_ambientColorButton->get_color()) );
	refreshCanvas();
}



void LightModelEditor::onModel()
{
	assert( m_lightModel );
	assert( m_modelButton );
	
	if( m_modelButton->get_active() )
	{
		m_lightModel->setModel( m_lastModelValue );
	}
	else
	{
		m_lightModel->getModel( m_lastModelValue );
		m_lightModel->eraseModel();
	}
	refreshWidgets();
	refreshCanvas();
}



void LightModelEditor::onModelValue( const vgd::node::LightModel::ModelValueType model )
{
	assert( m_lightModel );
	assert( m_modelBox );
	
	m_lightModel->setModel( m_modelBox->getValue() );
	refreshCanvas();
}
	


void LightModelEditor::onTwoSided()
{
	assert( m_lightModel );
	assert( m_twoSidedButton );
	
	if( m_twoSidedButton->get_active() )
	{
		m_lightModel->setTwoSided( m_lastTwoSidedValue );
	}
	else
	{
		m_lightModel->getTwoSided( m_lastTwoSidedValue );
		m_lightModel->eraseTwoSided();
	}
	refreshWidgets();
	refreshCanvas();
}



void LightModelEditor::onTwoSidedValue()
{
	assert( m_lightModel );
	assert( m_twoSidedValueButton );
	
	m_lightModel->setTwoSided( m_twoSidedValueButton->get_active() );
	refreshCanvas();
}



void LightModelEditor::onViewer()
{
	assert( m_lightModel );
	assert( m_viewerButton );
	
	if( m_viewerButton->get_active() )
	{
		m_lightModel->setViewer( m_lastViewerValue );
	}
	else
	{
		m_lightModel->getViewer( m_lastViewerValue );
		m_lightModel->eraseViewer();
	}
	refreshWidgets();
	refreshCanvas();
}



void LightModelEditor::onViewerValue( const vgd::node::LightModel::ViewerValueType viewer )
{
	assert( m_lightModel );
	assert( m_viewerBox );
	
	m_lightModel->setViewer( m_viewerBox->getValue() );
	refreshCanvas();
}
	


void LightModelEditor::refreshWidgets()
{
	// There is a light model node.
	if( m_lightModel )
	{
		// Model
		vgd::node::LightModel::ModelValueType	model;
		bool									hasModel;
		
		hasModel = m_lightModel->getModel( model );
		
		m_modelButton->set_sensitive( true );
		m_modelButton->set_active( hasModel );
		m_modelBox->set_sensitive( hasModel );
		if( hasModel )
		{
			m_modelBox->setValue( model );
		}
		
		
		// Ambient
		vgd::node::LightModel::AmbientValueType	ambient;
		bool									hasAmbient;
		
		hasAmbient = m_lightModel->getAmbient( ambient );
		
		m_ambientButton->set_sensitive( true );
		m_ambientButton->set_active( hasAmbient );
		m_ambientColorButton->set_sensitive( hasAmbient );
		if( hasAmbient )
		{
			m_ambientColorButton->set_color( color_cast(ambient) );
		}
		
		
		// Viewer
		vgd::node::LightModel::ViewerValueType	viewer;
		bool									hasViewer;
		
		hasViewer = m_lightModel->getViewer( viewer );
		
		m_viewerButton->set_sensitive( true );
		m_viewerButton->set_active( hasViewer );
		m_viewerBox->set_sensitive( hasViewer );
		if( hasViewer )
		{
			m_viewerBox->setValue( viewer );
		}
		
		
		// Two-Sided
		vgd::node::LightModel::TwoSidedValueType	twoSided;
		bool										hasTwoSided;
		
		hasTwoSided = m_lightModel->getTwoSided( twoSided );
		
		m_twoSidedButton->set_sensitive( true );
		m_twoSidedButton->set_active( hasTwoSided );
		m_twoSidedValueButton->set_sensitive( hasTwoSided );
		if( hasTwoSided )
		{
			m_twoSidedValueButton->set_active( twoSided );
		}
	}
	// There is no light model not.
	else
	{
		// Model
		m_modelButton->set_sensitive( false );
		m_modelBox->set_sensitive( false );
		
		// Ambient
		m_ambientButton->set_sensitive( false );
		m_ambientColorButton->set_sensitive( false );
		
		// Viewer
		m_viewerButton->set_sensitive( false );
		m_viewerBox->set_sensitive( false );

		// Two-sided
		m_twoSidedButton->set_sensitive( false );
		m_twoSidedValueButton->set_sensitive( false );
	}
}



void LightModelEditor::refreshCanvas()
{
	if( m_canvas != 0 )
	{
		m_canvas->refresh();
	}
}



void LightModelEditor::setLightModel( vgd::Shp< vgd::node::LightModel > lightModel )
{
	m_lightModel = lightModel;
	refreshWidgets();
}



void LightModelEditor::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
}



} // namespace node

} // namespace vgGTK
