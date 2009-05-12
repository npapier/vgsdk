// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_NODE_LIGHTMODELEDITOR_HPP_
#define _VGGTK_NODE_LIGHTMODELEDITOR_HPP_

#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>

#include <vgd/Shp.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgm/Vector.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/node/internal/EnumBox.hpp"

namespace Gtk
{
	class CheckButton;
	class ColorButton;
}

namespace vgUI
{
	struct Canvas;
}



namespace vgGTK
{

namespace node
{



struct VGGTK_API LightModelEditor : public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 * 
	 * @param	lightModel	a reference to a vgd::node::LightModel node to edit (default is empty)
	 * @param	canvas		a reference to a canvas to refresh on value changes (default is null)
	 */
	LightModelEditor( vgd::Shp< vgd::node::LightModel > lightModel = vgd::Shp< vgd::node::LightModel >(), vgUI::Canvas * canvas = 0 );
	
	/**
	 * @brief	Assignes a vgd::node::LightModel node to edit.
	 * 
	 * @param	lightModel	a reference to a vgd::node::LightModel node, empty if none
	 */
	void setLightModel( vgd::Shp< vgd::node::LightModel > lightModel );
	
	/**
	 * @brief	Assignes a reference to a canvas to refresh on light model value changes.
	 * 
	 * @param	canvas	a reference to a canvas, null if none
	 */
	void setCanvas( vgUI::Canvas * canvas );
	

private:
	
	typedef internal::EnumBox< vgd::node::LightModel::ModelValueType >	ModelBox;
	typedef internal::EnumBox< vgd::node::LightModel::ViewerValueType >	ViewerBox;
		
	vgd::Shp< vgd::node::LightModel >		m_lightModel;		///< Refefences the vgd::node::LightModel node to edit
	vgUI::Canvas							* m_canvas;			///< References the canvas to refresh on value changes

	vgd::node::LightModel::ModelValueType	m_lastModelValue;	///< Holds the last model value.
	Gtk::CheckButton						* m_modelButton;	///< References the widget used to control the model field
	ModelBox								* m_modelBox;		///< References the widet used to edit the model values
	
	vgm::Vec4f								m_lastAmbientValue;		///< Holds the last ambient value
	Gtk::CheckButton						* m_ambientButton;		///< Reference the widget used to control the ambient field
	Gtk::ColorButton						* m_ambientColorButton;	///< Reference the widget used to control the ambient values
	
	vgd::node::LightModel::ViewerValueType	m_lastViewerValue;	///< Holds the last viewer value.
	Gtk::CheckButton						* m_viewerButton;	///< References the widget used to control the viewer field
	ViewerBox								* m_viewerBox;		///< References the widet used to edit the viewer field values
	
	vgd::node::LightModel::TwoSidedValueType	m_lastTwoSidedValue;		///< Holds the last two-sided value.
	Gtk::CheckButton							* m_twoSidedButton;			///< References the widget used to control the two-sided field
	Gtk::CheckButton							* m_twoSidedValueButton;	///< References the widet used to edit the two-sided field values
	

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
	 * @name	Signal Handling
	 */
	//@{
	void onAmbient();
	void onAmbientValue();
	void onModel();
	void onModelValue( const vgd::node::LightModel::ModelValueType model );
	void onTwoSided();
	void onTwoSidedValue();
	void onViewer();
	void onViewerValue( const vgd::node::LightModel::ViewerValueType viewer );
	//@}
	
};



} // namespace node

} // namespace vgGTK



#endif /*_VGGTK_NODE_LIGHTMODELEDITOR_HPP_*/
