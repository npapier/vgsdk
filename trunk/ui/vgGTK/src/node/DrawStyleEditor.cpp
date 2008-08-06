// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/node/DrawStyleEditor.hpp"

#include <functional>

#include <gtkmm/adjustment.h>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/radiobuttongroup.h>
#include <gtkmm/spinbutton.h>

#include <vgUI/Canvas.hpp>



namespace vgGTK
{

namespace node
{



/**
 * @brief	Contains all widgets to edit the drawStyle's bounding box field
 */
struct DrawStyleEditor::BoundingBoxValueBox : public Gtk::VBox
{
	typedef std::map< vgd::node::DrawStyle::BoundingBoxValueType, Gtk::RadioButton * >	ButtonContainer;
	
	ButtonContainer	m_buttons;
	
	BoundingBoxValueBox( sigc::slot1<void, vgd::node::DrawStyle::BoundingBoxValueType > callback )
	{
		using vgd::node::DrawStyle;
		
		Gtk::RadioButtonGroup	radioGroup;
		
		m_buttons[ DrawStyle::NO_BOUNDING_BOX ]				= Gtk::manage( new Gtk::RadioButton(radioGroup, "None") );
		m_buttons[ DrawStyle::OBJECT_SPACE ]				= Gtk::manage( new Gtk::RadioButton(radioGroup, "Object Space") );
		m_buttons[ DrawStyle::AA_OBJECT_SPACE ]				= Gtk::manage( new Gtk::RadioButton(radioGroup, "AA Object Space") );
		m_buttons[ DrawStyle::OBJECT_AND_AA_OBJECT_SPACE ]	= Gtk::manage( new Gtk::RadioButton(radioGroup, "Object and AA Object Space") );
		
		set_border_width( 12 );
		
		add( *m_buttons[ DrawStyle::NO_BOUNDING_BOX ]			 );
		add( *m_buttons[ DrawStyle::OBJECT_SPACE ]				 );
		add( *m_buttons[ DrawStyle::AA_OBJECT_SPACE ]			 );
		add( *m_buttons[ DrawStyle::OBJECT_AND_AA_OBJECT_SPACE ] );
				
		m_buttons[ DrawStyle::NO_BOUNDING_BOX ]				->signal_clicked().connect( sigc::bind(callback, DrawStyle::NO_BOUNDING_BOX) );
		m_buttons[ DrawStyle::OBJECT_SPACE ]				->signal_clicked().connect( sigc::bind(callback, DrawStyle::OBJECT_SPACE) );
		m_buttons[ DrawStyle::AA_OBJECT_SPACE ]				->signal_clicked().connect( sigc::bind(callback, DrawStyle::AA_OBJECT_SPACE) );
		m_buttons[ DrawStyle::OBJECT_AND_AA_OBJECT_SPACE ]	->signal_clicked().connect( sigc::bind(callback, DrawStyle::OBJECT_AND_AA_OBJECT_SPACE) );
	}
};




/**
 * @brief	Contains all widgets to edit the drawStyle's shape field
 */
struct DrawStyleEditor::ShapeValueBox : public Gtk::VBox
{
	typedef std::map< vgd::node::DrawStyle::ShapeValueType, Gtk::RadioButton * >	ButtonContainer;
	
	ButtonContainer	m_buttons;
	
	ShapeValueBox( sigc::slot1<void, vgd::node::DrawStyle::ShapeValueType > callback )
	{
		using vgd::node::DrawStyle;
		
		Gtk::RadioButtonGroup	radioGroup;
		
		m_buttons[ DrawStyle::NONE ]				= Gtk::manage( new Gtk::RadioButton(radioGroup, "None") );
		m_buttons[ DrawStyle::POINT ]				= Gtk::manage( new Gtk::RadioButton(radioGroup, "Point") );
		m_buttons[ DrawStyle::FLAT ]				= Gtk::manage( new Gtk::RadioButton(radioGroup, "Flat") );
		m_buttons[ DrawStyle::SMOOTH ]				= Gtk::manage( new Gtk::RadioButton(radioGroup, "Smooth") );
		m_buttons[ DrawStyle::WIREFRAME ]			= Gtk::manage( new Gtk::RadioButton(radioGroup, "Wireframe") );
		m_buttons[ DrawStyle::HIDDEN_LINE ]			= Gtk::manage( new Gtk::RadioButton(radioGroup, "Hidden Line") );
		m_buttons[ DrawStyle::FLAT_HIDDEN_LINE ]	= Gtk::manage( new Gtk::RadioButton(radioGroup, "Flat Hidden Line") );
		m_buttons[ DrawStyle::SMOOTH_HIDDEN_LINE ]	= Gtk::manage( new Gtk::RadioButton(radioGroup, "Smooth Hidden Line") );
		m_buttons[ DrawStyle::NEIGHBOUR ]			= Gtk::manage( new Gtk::RadioButton(radioGroup, "Neighbour") );
		
		set_border_width( 12 );
		
		add( *m_buttons[ DrawStyle::NONE ]				 );
		add( *m_buttons[ DrawStyle::POINT ]				 );
		add( *m_buttons[ DrawStyle::FLAT ]				 );
		add( *m_buttons[ DrawStyle::SMOOTH ]			 );
		add( *m_buttons[ DrawStyle::WIREFRAME ]			 );
		add( *m_buttons[ DrawStyle::HIDDEN_LINE ]		 );
		add( *m_buttons[ DrawStyle::FLAT_HIDDEN_LINE ]	 );
		add( *m_buttons[ DrawStyle::SMOOTH_HIDDEN_LINE ] );
		add( *m_buttons[ DrawStyle::NEIGHBOUR ]			 );
		
		m_buttons[ DrawStyle::NONE ]				->signal_clicked().connect( sigc::bind(callback, DrawStyle::NONE) );
		m_buttons[ DrawStyle::POINT ]				->signal_clicked().connect( sigc::bind(callback, DrawStyle::POINT) );
		m_buttons[ DrawStyle::FLAT ]				->signal_clicked().connect( sigc::bind(callback, DrawStyle::FLAT) );
		m_buttons[ DrawStyle::SMOOTH ]				->signal_clicked().connect( sigc::bind(callback, DrawStyle::SMOOTH) );
		m_buttons[ DrawStyle::WIREFRAME ]			->signal_clicked().connect( sigc::bind(callback, DrawStyle::WIREFRAME) );
		m_buttons[ DrawStyle::HIDDEN_LINE ]			->signal_clicked().connect( sigc::bind(callback, DrawStyle::HIDDEN_LINE) );
		m_buttons[ DrawStyle::FLAT_HIDDEN_LINE ]	->signal_clicked().connect( sigc::bind(callback, DrawStyle::FLAT_HIDDEN_LINE) );
		m_buttons[ DrawStyle::SMOOTH_HIDDEN_LINE ]	->signal_clicked().connect( sigc::bind(callback, DrawStyle::SMOOTH_HIDDEN_LINE) );
		m_buttons[ DrawStyle::NEIGHBOUR ]			->signal_clicked().connect( sigc::bind(callback, DrawStyle::NEIGHBOUR) );

	}
};



/**
 * @brief	Contains all widgets to edit the DrawStyle's normal length field value.
 */
struct DrawStyleEditor::NormalLengthBox : public Gtk::VBox
{
	Gtk::Adjustment		m_adjustment;
	Gtk::SpinButton		m_spinButton;
	
	NormalLengthBox( sigc::slot0< void > callback )
	:	m_adjustment( 1.f, -100.f, 100.f, 1, 10 ),
		m_spinButton( m_adjustment, 1.f, 1 )
	{
		set_border_width( 12 );
		
		add( m_spinButton );
		
		m_adjustment.signal_value_changed().connect( callback );
	}
};



/**
 * @brief	Contains all widgets to edit the DrawStyle's show roentation field value.
 */
struct DrawStyleEditor::ShowOrientationValueBox : public Gtk::VBox
{
	Gtk::CheckButton	m_button;
	
	ShowOrientationValueBox( sigc::slot0< void > callback )
	:	m_button("Visible")
	{
		set_border_width( 12 );
		
		add( m_button );
		
		m_button.signal_clicked().connect( callback );
	}
};




DrawStyleEditor::DrawStyleEditor( vgd::Shp< vgd::node::DrawStyle > drawStyle, vgUI::Canvas * canvas )
:	m_drawStyle					( drawStyle ),
	m_canvas					( 0 ),
	m_lastNormalLengthValue		( 1.f ),
	m_normalLengthButton		( 0 ),
	m_normalLengthBox			( 0 ),
	m_lastShapeValue			( vgd::node::DrawStyle::DEFAULT_SHAPE ),
	m_shapeButton				( 0 ),
	m_shapeValueBox				( 0 ),
	m_lastShowOrientationValue	( true ),
	m_showOrientationButton		( 0 ),
	m_showOrientationValueBox	( 0 ),
	m_lastBoundingBoxValue		( vgd::node::DrawStyle::DEFAULT_BOUNDING_BOX ),
	m_boundingBoxButton			( 0 ),
	m_boundingBoxValueBox		( 0 )
{
	createContent();
	refreshWidgets();
}



void DrawStyleEditor::createContent()
{
	using vgd::node::DrawStyle;
	
	// Shape configuration widgets.
	m_shapeButton	= Gtk::manage( new Gtk::CheckButton("Shape") );
	m_shapeValueBox	= Gtk::manage( new ShapeValueBox(sigc::mem_fun(this, &DrawStyleEditor::onShapeValue)) );
			
	pack_start( *m_shapeButton, Gtk::PACK_SHRINK );
	pack_start( *m_shapeValueBox, Gtk::PACK_SHRINK );
	
	m_shapeButton->signal_clicked().connect( sigc::mem_fun(this, &DrawStyleEditor::onShape) );


	// Normal length configuration widgets.
	m_normalLengthButton	= Gtk::manage( new Gtk::CheckButton("Normal Length") );
	m_normalLengthBox		= Gtk::manage( new NormalLengthBox(sigc::mem_fun(this, &DrawStyleEditor::onNormalLengthValue)) );
	
	pack_start( *m_normalLengthButton, Gtk::PACK_SHRINK );
	pack_start( *m_normalLengthBox, Gtk::PACK_SHRINK );
	
	m_normalLengthButton->signal_clicked().connect( sigc::mem_fun(this, &DrawStyleEditor::onNormalLength) );
		

	// Show orientation widgets.
	m_showOrientationButton		= Gtk::manage( new Gtk::CheckButton("Show Orientation") );
	m_showOrientationValueBox	= Gtk::manage( new ShowOrientationValueBox(sigc::mem_fun(this, &DrawStyleEditor::onShowOrientationValue)) );
	
	pack_start( *m_showOrientationButton, Gtk::PACK_SHRINK );
	pack_start( *m_showOrientationValueBox, Gtk::PACK_SHRINK );
	
	m_showOrientationButton->signal_clicked().connect( sigc::mem_fun(this, &DrawStyleEditor::onShowOrientation) );
		
	
	// Bounding box widgets.
	m_boundingBoxButton		= Gtk::manage( new Gtk::CheckButton("Bounding Box") );
	m_boundingBoxValueBox	= Gtk::manage( new BoundingBoxValueBox( sigc::mem_fun(this, &DrawStyleEditor::onBoundingBoxValue)) );

	pack_start( *m_boundingBoxButton, Gtk::PACK_SHRINK );
	pack_start( *m_boundingBoxValueBox, Gtk::PACK_SHRINK );
	
	m_boundingBoxButton->signal_clicked().connect( sigc::mem_fun(this, &DrawStyleEditor::onBoundingBox) );
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
		m_shapeValueBox->set_sensitive( hasShape );
		if( hasShape )
		{
			m_shapeValueBox->m_buttons[ shape ]->set_active();
		}
		
		
		// Normal length
		vgd::node::DrawStyle::NormalLengthValueType	normalLength;
		bool										hasNormalLength;
		
		hasNormalLength = m_drawStyle->getNormalLength( normalLength );
		
		m_normalLengthButton->set_sensitive( true );
		m_normalLengthButton->set_active( hasNormalLength );
		m_normalLengthBox->set_sensitive( hasNormalLength );
		if( hasNormalLength )
		{
			m_normalLengthBox->m_adjustment.set_value( normalLength );
		}
		
		
		// Show orientation
		vgd::node::DrawStyle::ShowOrientationValueType	showOrientation;
		bool											hasShowOrientation;
		
		hasShowOrientation = m_drawStyle->getShowOrientation( showOrientation );
		
		m_showOrientationButton->set_sensitive( true );
		m_showOrientationButton->set_active( hasShowOrientation );
		m_showOrientationValueBox->set_sensitive( hasShowOrientation );
		if( hasShowOrientation )
		{
			m_showOrientationValueBox->m_button.set_active( showOrientation );
		}

		
		// Bounding box
		vgd::node::DrawStyle::BoundingBoxValueType	boundingBox;
		bool										hasBoundingBox;
		
		hasBoundingBox = m_drawStyle->getBoundingBox( boundingBox );
		
		m_boundingBoxButton->set_sensitive( true );
		m_boundingBoxButton->set_active( hasBoundingBox );
		m_boundingBoxValueBox->set_sensitive( hasBoundingBox );
		if( hasBoundingBox )
		{
			m_boundingBoxValueBox->m_buttons[ boundingBox ]->set_active();
		}
	}
	else
	{
		// Shape
		m_shapeButton->set_sensitive( false );
		m_shapeValueBox->set_sensitive( false );
		
		// Normal length
		m_normalLengthButton->set_sensitive( false );
		m_normalLengthBox->set_sensitive( false );
		
		// Show orientation
		m_showOrientationButton->set_sensitive( false );
		m_showOrientationValueBox->set_sensitive( false );
		
		// Bounding box
		m_boundingBoxButton->set_sensitive( false );
		m_boundingBoxValueBox->set_sensitive( false );
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
	assert( m_normalLengthBox );
	
	m_drawStyle->setNormalLength( static_cast< float >(m_normalLengthBox->m_adjustment.get_value()) );
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
	assert( m_showOrientationValueBox );
	
	m_drawStyle->setShowOrientation( m_showOrientationValueBox->m_button.get_active() );
	refreshCanvas();
}



} // namespace node

} // namespace vgGTK
