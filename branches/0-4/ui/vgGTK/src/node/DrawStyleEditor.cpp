// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/node/DrawStyleEditor.hpp"

#include <functional>
#include <boost/assign/list_of.hpp>

#include <gtkmm/adjustment.h>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/radiobuttongroup.h>
#include <gtkmm/separator.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/tooltips.h>

#include <vgUI/Canvas.hpp>



namespace vgGTK
{

namespace node
{



DrawStyleEditor::DrawStyleEditor( vgd::Shp< vgd::node::DrawStyle > drawStyle, vgUI::Canvas * canvas )
:	m_drawStyle					( drawStyle ),
	m_canvas					( 0 ),
	m_lastNormalLengthValue		( 1.f ),
	m_normalLengthButton		( 0 ),
	m_normalLengthSpin			( 0 ),
	m_normalLengthValue			( 0 ),
	m_lastShapeValue			( vgd::node::DrawStyle::DEFAULT_SHAPE ),
	m_shapeButton				( 0 ),
	m_shapeBox					( 0 ),
	m_lastShowOrientationValue	( true ),
	m_showOrientationButton		( 0 ),
	m_showOrientationValueButton( 0 ),
	m_lastBoundingBoxValue		( vgd::node::DrawStyle::DEFAULT_BOUNDING_BOX ),
	m_boundingBoxButton			( 0 ),
	m_boundingBoxBox			( 0 )
{
	createContent();
	refreshWidgets();
}



void DrawStyleEditor::createContent()
{
	using boost::assign::list_of;
	using vgd::node::DrawStyle;
	
	// Shape configuration widgets.
	const ShapeBox::ValueContainer	shapeValues = 
		list_of< ShapeBox::Value >(DrawStyle::NONE, "None")
		(DrawStyle::POINT, "Point")
		(DrawStyle::FLAT, "Flat")
		(DrawStyle::SMOOTH, "Smooth")
		(DrawStyle::WIREFRAME, "Wireframe")
		(DrawStyle::HIDDEN_LINE, "Hidden Line")
		(DrawStyle::FLAT_HIDDEN_LINE, "Flat Hidden Line")
		(DrawStyle::SMOOTH_HIDDEN_LINE, "Smooth Hidden Line")
		(DrawStyle::NEIGHBOUR, "Neighbour");

	m_shapeButton	= Gtk::manage( new Gtk::CheckButton("Shape") );
	m_shapeBox		= Gtk::manage( new ShapeBox(shapeValues, sigc::mem_fun(this, &DrawStyleEditor::onShapeValue)) );
	
	m_shapeBox->set_border_width( 12 );
			
	pack_start( *m_shapeButton, Gtk::PACK_SHRINK );
	pack_start( *m_shapeBox, Gtk::PACK_SHRINK );
	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK, 12 );
	
	m_shapeButton->signal_clicked().connect( sigc::mem_fun(this, &DrawStyleEditor::onShape) );


	// Normal length configuration widgets.
	Gtk::VBox		* normalLengthBox			= Gtk::manage( new Gtk::VBox() );
		
	m_normalLengthButton	= Gtk::manage( new Gtk::CheckButton("Normal Length") );
	m_normalLengthValue		= Gtk::manage( new Gtk::Adjustment(1.f, -100.f, 100.f, 1, 10) );
	m_normalLengthSpin		= Gtk::manage( new Gtk::SpinButton(*m_normalLengthValue) );
		
	normalLengthBox->set_border_width( 12 );
	normalLengthBox->add( *m_normalLengthSpin );
		
	pack_start( *m_normalLengthButton, Gtk::PACK_SHRINK );
	pack_start( *normalLengthBox, Gtk::PACK_SHRINK );
	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK, 12 );
	
	m_normalLengthButton->signal_clicked().connect( sigc::mem_fun(this, &DrawStyleEditor::onNormalLength) );
	m_normalLengthValue->signal_value_changed().connect( sigc::mem_fun(this, &DrawStyleEditor::onNormalLengthValue) );

	// Show orientation widgets.
	Gtk::VBox	* showOrientationBox = Gtk::manage( new Gtk::VBox() );
	
	m_showOrientationButton			= Gtk::manage( new Gtk::CheckButton("Show Orientation") );
	m_showOrientationValueButton	= Gtk::manage( new Gtk::CheckButton("Activate") );
	
	showOrientationBox->set_border_width( 12 );
	showOrientationBox->add( *m_showOrientationValueButton );
	
	pack_start( *m_showOrientationButton, Gtk::PACK_SHRINK );
	pack_start( *showOrientationBox, Gtk::PACK_SHRINK );
	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK, 12 );
	
	m_showOrientationButton->signal_clicked().connect( sigc::mem_fun(this, &DrawStyleEditor::onShowOrientation) );
	m_showOrientationValueButton->signal_clicked().connect( sigc::mem_fun(this, &DrawStyleEditor::onShowOrientationValue) );
		
	
	// Bounding box widgets.
	const BoundingBoxBox::ValueContainer	boundingBoxValues =
		list_of< BoundingBoxBox::Value >(DrawStyle::NO_BOUNDING_BOX, "None")
		(DrawStyle::OBJECT_SPACE, "Object Space")
		(DrawStyle::AA_OBJECT_SPACE, "AA Object Space")
		(DrawStyle::OBJECT_AND_AA_OBJECT_SPACE, "Object and AA Object Space");
	
	m_boundingBoxButton	= Gtk::manage( new Gtk::CheckButton("Bounding Box") );
	m_boundingBoxBox	= Gtk::manage( new BoundingBoxBox(boundingBoxValues, sigc::mem_fun(this, &DrawStyleEditor::onBoundingBoxValue)) );
	
	m_boundingBoxBox->set_border_width( 12 );

	pack_start( *m_boundingBoxButton, Gtk::PACK_SHRINK );
	pack_start( *m_boundingBoxBox, Gtk::PACK_SHRINK );
	
	m_boundingBoxButton->signal_clicked().connect( sigc::mem_fun(this, &DrawStyleEditor::onBoundingBox) );
	
	
	// Tooltips
	Gtk::Tooltips	* tooltips = Gtk::manage( new Gtk::Tooltips() );
	
	tooltips->set_tip( *m_shapeButton, "Specifies the drawing style of shapes" );
	tooltips->set_tip( *m_normalLengthButton, "Specifies the normal length to show" );
	tooltips->set_tip( *m_showOrientationButton, "Specifies the triangle orientation feedback to show" );
	tooltips->set_tip( *m_boundingBoxButton, "Specifies the bounding box drawing style" );
}



void DrawStyleEditor::setDrawStyle( vgd::Shp< vgd::node::DrawStyle > drawStyle )
{
	m_drawStyle = drawStyle;
	refreshWidgets();
}



void DrawStyleEditor::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
}



void DrawStyleEditor::refreshCanvas()
{
	if( m_canvas != 0 )
	{
		m_canvas->refresh();
	}
}



void DrawStyleEditor::refreshWidgets()
{
	if( m_drawStyle )
	{
		// Shape
		vgd::node::DrawStyle::ShapeValueType	shape;
		bool									hasShape;
		
		hasShape = m_drawStyle->getShape( shape );
		
		m_shapeButton->set_sensitive( true );
		m_shapeButton->set_active( hasShape );
		m_shapeBox->set_sensitive( hasShape );
		if( hasShape )
		{
			m_shapeBox->setValue( shape );
		}
		
		
		// Normal length
		vgd::node::DrawStyle::NormalLengthValueType	normalLength;
		bool										hasNormalLength;
		
		hasNormalLength = m_drawStyle->getNormalLength( normalLength );
		
		m_normalLengthButton->set_sensitive( true );
		m_normalLengthButton->set_active( hasNormalLength );
		m_normalLengthSpin->set_sensitive( hasNormalLength );
		if( hasNormalLength )
		{
			m_normalLengthValue->set_value( normalLength );
		}
		
		
		// Show orientation
		vgd::node::DrawStyle::ShowOrientationValueType	showOrientation;
		bool											hasShowOrientation;
		
		hasShowOrientation = m_drawStyle->getShowOrientation( showOrientation );
		
		m_showOrientationButton->set_sensitive( true );
		m_showOrientationButton->set_active( hasShowOrientation );
		m_showOrientationValueButton->set_sensitive( hasShowOrientation );
		if( hasShowOrientation )
		{
			m_showOrientationValueButton->set_active( showOrientation );
		}

		
		// Bounding box
		vgd::node::DrawStyle::BoundingBoxValueType	boundingBox;
		bool										hasBoundingBox;
		
		hasBoundingBox = m_drawStyle->getBoundingBox( boundingBox );
		
		m_boundingBoxButton->set_sensitive( true );
		m_boundingBoxButton->set_active( hasBoundingBox );
		m_boundingBoxBox->set_sensitive( hasBoundingBox );
		if( hasBoundingBox )
		{
			m_boundingBoxBox->setValue( boundingBox );
		}
	}
	else
	{
		// Shape
		m_shapeButton->set_sensitive( false );
		m_shapeBox->set_sensitive( false );
		
		// Normal length
		m_normalLengthButton->set_sensitive( false );
		m_normalLengthSpin->set_sensitive( false );
		
		// Show orientation
		m_showOrientationButton->set_sensitive( false );
		m_showOrientationValueButton->set_sensitive( false );
		
		// Bounding box
		m_boundingBoxButton->set_sensitive( false );
		m_boundingBoxBox->set_sensitive( false );
	}
}



void DrawStyleEditor::onBoundingBox()
{
	assert( m_drawStyle );
	assert( m_boundingBoxButton );
	
	if( m_boundingBoxButton->get_active() )
	{
		m_drawStyle->setBoundingBox( m_lastBoundingBoxValue );
	}
	else
	{
		m_drawStyle->getBoundingBox( m_lastBoundingBoxValue );
		m_drawStyle->eraseBoundingBox();
	}
	refreshWidgets();
	refreshCanvas();
}



void DrawStyleEditor::onBoundingBoxValue( const vgd::node::DrawStyle::BoundingBoxValueType boundingBox )
{
	assert( m_drawStyle );
	
	m_drawStyle->setBoundingBox( boundingBox );
	refreshCanvas();
}



void DrawStyleEditor::onNormalLength()
{
	assert( m_drawStyle );
	assert( m_normalLengthButton );
	
	if( m_normalLengthButton->get_active() )
	{
		m_drawStyle->setNormalLength( m_lastNormalLengthValue );
	}
	else
	{
		m_drawStyle->getNormalLength( m_lastNormalLengthValue );
		m_drawStyle->eraseNormalLength();
	}
	refreshWidgets();
	refreshCanvas();
}



void DrawStyleEditor::onNormalLengthValue()
{
	assert( m_drawStyle );
	assert( m_normalLengthValue );
	
	m_drawStyle->setNormalLength( static_cast< float >(m_normalLengthValue->get_value()) );
	refreshCanvas();
}




void DrawStyleEditor::onShape()
{
	assert( m_drawStyle );
	assert( m_shapeButton );
	
	if( m_shapeButton->get_active() )
	{
		m_drawStyle->setShape( m_lastShapeValue );
	}
	else
	{
		m_drawStyle->getShape( m_lastShapeValue );
		m_drawStyle->eraseShape();
	}
	refreshWidgets();
	refreshCanvas();
}



void DrawStyleEditor::onShapeValue( const vgd::node::DrawStyle::ShapeValueType shape )
{
	assert( m_drawStyle );
	
	m_drawStyle->setShape( shape );
	refreshCanvas();
}



void DrawStyleEditor::onShowOrientation()
{
	assert( m_drawStyle );
	assert( m_showOrientationButton );
	
	if( m_showOrientationButton->get_active() )
	{
		m_drawStyle->setShowOrientation( m_lastShowOrientationValue );
	}
	else
	{
		m_drawStyle->getShowOrientation( m_lastShowOrientationValue );
		m_drawStyle->eraseShowOrientation();
	}
	refreshWidgets();
	refreshCanvas();
}



void DrawStyleEditor::onShowOrientationValue()
{
	assert( m_drawStyle );
	assert( m_showOrientationValueButton );
	
	m_drawStyle->setShowOrientation( m_showOrientationValueButton->get_active() );
	refreshCanvas();
}



} // namespace node

} // namespace vgGTK
