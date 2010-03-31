// VGSDK - Copyright (C) 2009, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_RECTANGLE_HPP_
#define _VGGTK_FIELD_WIDGET_RECTANGLE_HPP_

#include <boost/lexical_cast.hpp>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/table.h>
#include <vgm/Rectangle.hpp>

#include "vgGTK/field/widget/Widget.hpp"



namespace vgGTK
{

namespace field
{

namespace widget
{


/**
 * @brief	Implements a widget for vgm::Rectangle edition.
 */
template< typename T >
struct Rectangle : public Widget< vgm::Rectangle< T > >, public Gtk::Table
{
	Rectangle()
	:	Gtk::Table( 3, 4 )
	{
		Gtk::Label	* positionLabel	= Gtk::manage( new Gtk::Label("<b>Position</b>") );
		Gtk::Label	* sizeLabel		= Gtk::manage( new Gtk::Label("<b>Size</b>") );
		Gtk::Label	* xLabel		= Gtk::manage( new Gtk::Label("x") );
		Gtk::Label	* yLabel		= Gtk::manage( new Gtk::Label("y") );
		Gtk::Label	* widthLabel	= Gtk::manage( new Gtk::Label("width") );
		Gtk::Label	* heightLabel	= Gtk::manage( new Gtk::Label("height") );

		set_row_spacings( 2 );
		set_col_spacing( 1, 12 );

		positionLabel->set_use_markup( true );
		positionLabel->set_alignment( 0.f, 0.5f );

		sizeLabel->set_use_markup( true );
		sizeLabel->set_alignment( 0.f, 0.5f );

		xLabel->set_alignment( 1.f, 0.5f );
		yLabel->set_alignment( 1.f, 0.5f );
		widthLabel->set_alignment( 1.f, 0.5f );
		heightLabel->set_alignment( 1.f, 0.5f );

		xLabel->set_padding( 10, 0 );
		yLabel->set_padding( 10, 0 );
		widthLabel->set_padding( 10, 0 );
		heightLabel->set_padding( 10, 0 );

		m_x.set_size_request( 75, -1 );
		m_y.set_size_request( 75, -1 );
		m_width.set_size_request( 75, -1 );
		m_height.set_size_request( 75, -1 );

		m_x.set_activates_default();
		m_y.set_activates_default();
		m_width.set_activates_default();
		m_height.set_activates_default();

		attach( *positionLabel, 0, 2, 0, 1 );
		attach( *sizeLabel, 2, 4, 0, 1 );

		attach( *xLabel, 0, 1, 1, 2 );
		attach( m_x, 1, 2, 1, 2 );

		attach( *widthLabel, 2, 3, 1, 2 );
		attach( m_width, 3, 4, 1, 2 );

		attach( *yLabel, 0, 1, 2, 3 );
		attach( m_y, 1, 2, 2, 3 );

		attach( *heightLabel, 2, 3, 2, 3 );
		attach( m_height, 3, 4, 2, 3 );


		// Defines the focus order.
		std::vector< Gtk::Widget * >	focusChain;

		focusChain.push_back( &m_x );
		focusChain.push_back( &m_y );
		focusChain.push_back( &m_width );
		focusChain.push_back( &m_height );

		set_focus_chain( focusChain );


		// Connects children change signal to our change signal.
		m_x     .signal_changed().connect( sigc::mem_fun(&m_signalChanged, &sigc::signal< void >::emit) );
		m_y     .signal_changed().connect( sigc::mem_fun(&m_signalChanged, &sigc::signal< void >::emit) );
		m_width .signal_changed().connect( sigc::mem_fun(&m_signalChanged, &sigc::signal< void >::emit) );
		m_height.signal_changed().connect( sigc::mem_fun(&m_signalChanged, &sigc::signal< void >::emit) );
	}

	void clear()
	{
		m_x.set_text( Glib::ustring() );
		m_y.set_text( Glib::ustring() );
		m_width.set_text( Glib::ustring() );
		m_height.set_text( Glib::ustring() );
	}

	const vgm::Rectangle< T > getValue() const
	{
		const T	x		= toNumber( m_x.get_text() );
		const T	y		= toNumber( m_y.get_text() );
		const T	width	= toNumber( m_width.get_text() );
		const T	height	= toNumber( m_height.get_text() );

		return vgm::Rectangle< T >(x, y, width, height);
	}

	const bool hasValue() const
	{
		return	m_x.get_text().empty() == false			||
				m_y.get_text().empty() == false			||
				m_width.get_text().empty() == false		||
				m_height.get_text().empty() == false;
	}

	void setValue( const vgm::Rectangle< T > & value )
	{
		m_x.set_text( Glib::ustring::compose("%1", value.x()) );
		m_y.set_text( Glib::ustring::compose("%1", value.y()) );
		m_width.set_text( Glib::ustring::compose("%1", value.width()) );
		m_height.set_text( Glib::ustring::compose("%1", value.height()) );
	}

	const bool validate()
	{
		return true; /// To be done.
	}

	void grabFocus()
	{
		m_x.grab_focus();
	}
	
	const bool resizable() const
	{
		return false;
	}

	void setFrame( const bool frame )
	{ /* nothing to do */ }

private:

	Gtk::Entry	m_x;		///< The widget used to edit the x value.
	Gtk::Entry	m_y;		///< The widget used to edit the y value.
	Gtk::Entry	m_width;	///< The widget used to edit the width value.
	Gtk::Entry	m_height;	///< The widget used to edit the height value.

	static const T toNumber( const Glib::ustring & text )
	{
		try
		{
			return boost::lexical_cast< T >( text );
		}
		catch( const boost::bad_lexical_cast & )
		{
			return static_cast< T >( 0 );
		}
	}
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_RECTANGLE_HPP_
