// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_MULTIFIELDEDITOR_HPP_
#define _VGGTK_FIELD_MULTIFIELDEDITOR_HPP_

#include <cassert>
#include <string>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/scrollbar.h>
#include <gtkmm/table.h>
#include <gtkmm/widget.h>
#include <vgd/field/FieldManager.hpp>
#include <vgd/field/TMultiField.hpp>
#include <vgUI/helpers.hpp>

#include "vgGTK/field/FieldEditor.hpp"



namespace vgGTK
{

namespace field
{



template< typename WidgetType >
struct MultiFieldEditor : public FieldEditor, public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 *
	 * @param	visibleRows	tells the number multifield element to show for edition
	 */
	 MultiFieldEditor( const unsigned int visibleRows = 10 )
	 :	m_visibleRows( visibleRows )
	 {
		// Builds the user interface.
		for( unsigned int i = 0; i < m_visibleRows; ++i )
		{
			Gtk::Label	* label		= new Gtk::Label();
			WidgetType	* widget	= new WidgetType();
			
			widget->setFrame( false );
			widget->signalChanged().connect( sigcmem_fun(&m_signalChanged, &sigc::signal< void >::emit) );
			m_widgets.push_back( std::make_pair(label, widget) );
			m_widgetTable.attach( *label,  0, 1, i, i+1, Gtk::SHRINK );
			m_widgetTable.attach( *widget, 1, 2, i, i+1 );
		}
		
		m_widgetTable.set_col_spacing( 0, 5 );

		m_frame.add( m_widgetTable );
		m_frame.set_shadow_type( Gtk::SHADOW_IN );
		
		m_scrollbar.set_increments( 1, m_visibleRows );
		m_scrollbar.signal_change_value().connect( sigc::mem_fun(this, &MultiFieldEditor< WidgetType >::onScroll) );
		
		m_frameBox.pack_start( m_frame );
		m_frameBox.pack_start( m_scrollbar, Gtk::PACK_SHRINK, 2 );
		
		add( m_frameBox );
		add( m_status );
		set_spacing( 5 );
		
		// Initialize the data.
		m_valueIndex = m_values.begin();
	}
	
	/**
	 * @brief	Destructor
	 */
	~MultiFieldEditor()
	{
		typename WidgetContainer::iterator	i;
		
		for( i = m_widgets.begin(); i != m_widgets.end(); ++i )
		{
			delete i->first;
			delete i->second;
		}
	}
	
	Gtk::Widget& getWidget()
	{
		return *this;
	}
	
	void grabFocus()
	{
		m_widgets.begin()->second->grabFocus();
	}
	
	const bool resizable() const
	{
		return false;
	}

	void commit()
	{	
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
		
		// Refreshes the data cache from the widgets.
		refreshValuesFromWidgets();
	
		// Copies values from local cache into the field.
		typedef vgd::field::TMultiField< typename WidgetType::ValueType > FieldType;

		vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName );
		
		typename ValueContainer::iterator	source;
		typename FieldType::iterator		target;
		
		for(	source = m_values.begin(), target = fieldEditor->begin();
				source != m_values.end() && target != fieldEditor->end();
				++source, ++target )
		{
			*target = *source;
		}		
	}
	
	void refresh()
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
		
		// Copies the data from the vgsdk node field to the local cache.
		typedef vgd::field::TMultiField< typename WidgetType::ValueType > FieldType;

		vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName );
		
		m_values.clear();
		m_values.insert( m_values.end(), fieldEditor->begin(), fieldEditor->end() );
		
		m_valueIndex = m_values.begin();
		
		// Configures littles thinks of the UI
		const unsigned int	upperBound = (m_values.size() >= m_visibleRows) ? (m_values.size() - m_visibleRows - 1) : 0;
		
		m_scrollbar.set_range( 0, upperBound );
		m_status.set_text( vgUI::compose("Element Count: %1%", m_values.size()) );

		// Refreshes the widgets.
		refreshWidgetsFromValues();
	}

	sigc::signal< void > & signalChanged()
	{
		return m_signalChanged;
	}
	
	const bool validate()
	{
		return validateWidgets();
	}
	
private:
	/**
	 * @name	Widgets
	 */
	//@{
	typedef std::vector< std::pair< Gtk::Label*, WidgetType* > >	WidgetContainer;

	const unsigned int		m_visibleRows;	
	Gtk::HBox				m_frameBox;
	Gtk::Frame				m_frame;
	Gtk::Table				m_widgetTable;
	WidgetContainer			m_widgets;
	Gtk::VScrollbar			m_scrollbar;
	Gtk::Label				m_status;
	sigc::signal< void >	m_signalChanged;
	//@}
	
	/**
	 * @name	Data
	 */
	//@{
	typedef std::vector< typename WidgetType::ValueType >	ValueContainer;

	ValueContainer						m_values;
	typename ValueContainer::iterator	m_valueIndex;
	//@}
	
	/**
	 * @name	Signal Handling
	 */
	//@{
	bool onScroll( Gtk::ScrollType, double value )
	{
		static double oldValue = 0.0;
		
		if( validateWidgets() )
		{
			oldValue = value;
			
			// Stores values from the current widgets.
			refreshValuesFromWidgets();
			
			// Computes the new value index.
			const unsigned int index = static_cast< unsigned int >( value );
			
			m_valueIndex = index < m_values.size() ? m_values.begin()+index : m_values.end();
			
			// Refresh wiggets.
			refreshWidgetsFromValues();
		}
		else
		{
			m_scrollbar.set_value( value );
		}
		
		return false;
	}
	//@}
	
	/**
	 * @brief	Refreshes the values in the local cache from the widgets.
	 */
	void refreshValuesFromWidgets()
	{
		typename ValueContainer::iterator	curValue;
		typename WidgetContainer::iterator	curWidget;
		
		for(	curValue = m_valueIndex, curWidget = m_widgets.begin();
				curValue != m_values.end() && curWidget != m_widgets.end();
				++curValue, ++curWidget
				)
		{
			*curValue = curWidget->second->getValue();
		}
	}
	
	/**
	 * @brief	refreshes the widgets from the local cache values.
	 */
	void refreshWidgetsFromValues()
	{
		typename ValueContainer::iterator	curValue;
		typename WidgetContainer::iterator	curWidget;
		
		// Synchronize widgets' content with values.
		for(	curValue = m_valueIndex, curWidget = m_widgets.begin();
				curValue != m_values.end() && curWidget != m_widgets.end();
				++curValue, ++curWidget
				)
		{
			curWidget->first->set_text( vgUI::compose("%1%", std::distance(m_values.begin(), curValue) ) );
			curWidget->second->setValue( *curValue );
			curWidget->second->set_sensitive( true );
		}
		
		// Disables remaining widgets that are not used to display values.
		for( curWidget; curWidget != m_widgets.end(); ++curWidget )
		{
			curWidget->first->set_text( Glib::ustring() );
			curWidget->second->clear();
			curWidget->second->set_sensitive( false );
		}
	}
	
	/**
	 * @brief	Validates the current widgets.
	 */
	const bool validateWidgets()
	{
		bool	validate = true;
		
		for( typename WidgetContainer::iterator curWidget = m_widgets.begin(); curWidget != m_widgets.end() && validate; ++curWidget )
		{
			if( curWidget->second->is_sensitive() )
			{
				validate = curWidget->second->validate();
			}
		}
		
		return validate;
	}
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_MULTIFIELDEDITOR_HPP_
