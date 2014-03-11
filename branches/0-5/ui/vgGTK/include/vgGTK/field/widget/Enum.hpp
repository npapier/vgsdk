// VGSDK - Copyright (C) 2009, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_ENUM_HPP_
#define _VGGTK_FIELD_WIDGET_ENUM_HPP_

#include <utility>
#include <vector>
#include <gtkmm/buttonbox.h>
#include <gtkmm/radiobutton.h>
#include <vgd/field/Enum.hpp>

#include "vgGTK/field/widget/Widget.hpp"



namespace vgGTK
{

namespace field
{

namespace widget
{



/**
 * @brief	Implements a widget the edition vgd::field::Enum values.
 */
struct Enum : public Widget< vgd::field::Enum >, public Gtk::VButtonBox
{
	/**
	 * @brief	Constructor
	 */
	Enum();

	/**
	 * @name	Overrides
	 */
	//@{
	void clear();
	const vgd::field::Enum getValue() const;
	void grabFocus();
	const bool hasValue() const;
	const bool resizable() const;
	void setFrame( const bool frame );
	void setValue( const vgd::field::Enum & value );
	const bool validate();
	//@}

private:

	typedef std::pair< int, Gtk::RadioButton * >	Entry;
	typedef std::vector< Entry >					EntryContainer;

	EntryContainer	m_entries;	///< Holds all possible values and the associated widget.

	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onButtonClicked();
	//@}
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_ENUM_HPP_
