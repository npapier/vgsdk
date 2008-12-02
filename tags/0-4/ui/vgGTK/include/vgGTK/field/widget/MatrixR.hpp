// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_MATRIXR_HPP_
#define _VGGTK_FIELD_WIDGET_MATRIXR_HPP_

#include "vgGTK/field/widget/Widget.hpp"

#include <gtkmm/box.h>
#include <gtkmm/entry.h>

#include <vgm/Matrix.hpp>



namespace vgGTK
{

namespace field
{

namespace widget
{



struct MatrixR : public Widget< vgm::MatrixR >, public Gtk::VBox
{
	MatrixR();
	
	void clear();
	const vgm::MatrixR getValue() const;
	void setValue( const vgm::MatrixR & value );
	const bool validate();
	
	const bool resizable() const;
	void setFrame( const bool frame );

private:

	Gtk::Entry	m_elements[16];	///< Entry widgets for matrix elements.
	
	/** 
	 * @name	Signal Handlers
	 */
	//@{
	void onIdentity();
	void onNull();
	//@}
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_MATRIXR_HPP_