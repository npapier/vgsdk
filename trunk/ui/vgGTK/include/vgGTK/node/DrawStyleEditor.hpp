// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_NODE_DRAWSTYLEEDITOR_HPP_
#define _VGGTK_NODE_DRAWSTYLEEDITOR_HPP_

#include <set>

#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/radiobutton.h>
#include <vgd/node/drawStyle.hpp>

#include "vgGTK/vgGTK.hpp"

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
	 * @para	canvas		a reference to a canvas to refresh on value changes (default is null)
	 */
	DrawStyleEditor( vgd::Shp< vgd::node::DrawStyle > drawStyle = vgd::Shp< vgd::node::DrawStyle >(), vgUI::Canvas * canvas = 0 );
	
	/**
	 * @brief	Assignes a DrawStyle node to edit.
	 * 
	 * @param	drawStyle	a reference to a DrawStyle node
	 */
	void setDrawStyle( vgd::Shp< vgd::node::DrawStyle > drawStyle );
	
	/**
	 * @brief	Assignes a reference to a canvas to refresh on draw style value changes.
	 * 
	 * @param	canvas	a reference to a canvas, null if none
	 */
	void setCanvas( vgUI::Canvas * canvas );
	
	
private:
	
	typedef std::set< Gtk::Widget * >	WidgetContainer;
	
	struct BoundingBoxValueBox;
	struct NormalLengthBox;
	struct ShapeValueBox;
	struct ShowOrientationValueBox;
	
	vgd::Shp< vgd::node::DrawStyle 	>				m_drawStyle;					///< Refefences the DrawStyle node to edit
	vgUI::Canvas									* m_canvas;						///< References the canvas to refresh on value changes
	float											m_lastNormalLengthValue;		///< Holds the last normal length value.
	Gtk::CheckButton								* m_normalLengthButton;			///< References the widget used to control the normal length field
	NormalLengthBox									* m_normalLengthBox;			///< References the widet used to edit the normal length field values
	vgd::node::DrawStyle::ShapeValueType			m_lastShapeValue;				///< Holds the last shape value.
	Gtk::CheckButton								* m_shapeButton;				///< References the widget used to control the shape field
	ShapeValueBox									* m_shapeValueBox;				///< References a widget used to edit shape field values
	vgd::node::DrawStyle::ShowOrientationValueType	m_lastShowOrientationValue;		///< Holds the last show orientation value
	Gtk::CheckButton								* m_showOrientationButton;		///< References the widget used to control the show orentation field
	ShowOrientationValueBox							* m_showOrientationValueBox;	///< References the widget used to edit show orientation values
	vgd::node::DrawStyle::BoundingBoxValueType		m_lastBoundingBoxValue;			///< Holds the last bouding box field value
	Gtk::CheckButton								* m_boundingBoxButton;			///< References the widgets used to control the bounding box field
	BoundingBoxValueBox								* m_boundingBoxValueBox;		///< Reference the widget used to edit bouding box values
	
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
	
	/**
	 * @name	Signa Handlers
	 */
	//@{
	void onBoundingBox();
	void onBoundingBoxValue( const vgd::node::DrawStyle::BoundingBoxValueType boundingBox );
	void onNormalLength();
	void onNormalLengthValue();
	void onShape();
	void onShapeValue( const vgd::node::DrawStyle::ShapeValueType shape );
	void onShowOrientation();
	void onShowOrientationValue();
	//@}
};



} // namespace node

} // namespace vgGTK



#endif /*_VGGTK_NODE_DRAWSTYLEEDITOR_HPP_*/
