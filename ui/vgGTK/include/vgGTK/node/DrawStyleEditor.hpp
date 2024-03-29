// VGSDK - Copyright (C) 2008, 2009, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_NODE_DRAWSTYLEEDITOR_HPP_
#define _VGGTK_NODE_DRAWSTYLEEDITOR_HPP_

#include <set>

#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/spinbutton.h>

#include <vgd/Shp.hpp>
#include <vgd/node/DrawStyle.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/node/internal/EnumBox.hpp"

namespace vgUI
{
	struct Canvas;
}




namespace vgGTK
{

namespace node
{



struct VGGTK_API DrawStyleEditor : public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 * 
	 * @param	drawStyle	a reference to a DrawStyle node to edit (default is empty)
	 * @param	canvas		a reference to a canvas to refresh on value changes (default is null)
	 */
	DrawStyleEditor( vgd::Shp< vgd::node::DrawStyle > drawStyle = vgd::Shp< vgd::node::DrawStyle >(), vgUI::Canvas * canvas = 0 );
	
	/**
	 * @brief	Assignes a DrawStyle node to edit.
	 * 
	 * @param	drawStyle	a reference to a DrawStyle node, empty if none
	 */
	void setDrawStyle( vgd::Shp< vgd::node::DrawStyle > drawStyle );
	
	/**
	 * @brief	Assignes a reference to a canvas to refresh on draw style value changes.
	 * 
	 * @param	canvas	a reference to a canvas, null if none
	 */
	void setCanvas( vgUI::Canvas * canvas );
	
	
protected:
	
	typedef internal::EnumBox< vgd::node::DrawStyle::ShapeValueType >		ShapeBox;
		
	vgd::Shp< vgd::node::DrawStyle >				m_drawStyle;					///< Refefences the DrawStyle node to edit
	vgUI::Canvas									* m_canvas;						///< References the canvas to refresh on value changes

	vgd::node::DrawStyle::NormalLengthValueType		m_lastNormalLengthValue;		///< Holds the last normal length value.
	Gtk::CheckButton								* m_normalLengthButton;			///< References the widget used to control the normal length field
	Gtk::Adjustment									* m_normalLengthValue;			///< References the widet used to edit the normal length field values
	Gtk::SpinButton									* m_normalLengthSpin;			///< References the widet used to edit the normal length field values
	
	vgd::node::DrawStyle::ShapeValueType			m_lastShapeValue;				///< Holds the last shape value.
	Gtk::CheckButton								* m_shapeButton;				///< References the widget used to control the shape field
	ShapeBox										* m_shapeBox;					///< References a widget used to edit shape field values
	
	vgd::node::DrawStyle::ShowOrientationValueType	m_lastShowOrientationValue;		///< Holds the last show orientation value
	Gtk::CheckButton								* m_showOrientationButton;		///< References the widget used to control the show orentation field
	Gtk::CheckButton								* m_showOrientationValueButton;	///< References the widget used to edit show orientation values

	/**
	 * @name	Signal Handlers
	 */
	//@{
	virtual void onNormalLength();
	virtual void onNormalLengthValue();
	virtual void onShape();
	virtual void onShapeValue( const vgd::node::DrawStyle::ShapeValueType shape );
	virtual void onShowOrientation();
	virtual void onShowOrientationValue();
	//@}


private:

	/**
	 * @brief	Creates the content of the widget.
	 */
	void createContent();
	
	/**
	 * @brief	Refreshes the referenced canvas.
	 */
	void refreshCanvas();
	
	/**
	 * @brief	Refreshes all widgets' state, according to the referenced DrawStyle node.
	 */
	void refreshWidgets();
	
};



} // namespace node

} // namespace vgGTK



#endif /*_VGGTK_NODE_DRAWSTYLEEDITOR_HPP_*/
