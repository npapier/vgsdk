// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_COLLADASETTINGS_HPP_
#define _VGGTK_NODE_COLLADASETTINGS_HPP_

#include <gtkmm/box.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/frame.h>

#include "vgGTK/vgGTK.hpp"

#include <vgOpenCOLLADA/Settings.hpp>


namespace vgGTK
{

namespace node
{



/**
 * @brief	A widget that allows to configure collada import/export settings.
 */
struct VGGTK_API ColladaSettings : public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 */
	ColladaSettings();

	vgOpenCOLLADA::Settings getSettings();


private:

	Gtk::HBox					m_geometryHBox1;
	Gtk::HBox					m_geometryHBox2;
	Gtk::VBox					m_geometryVBox;
	Gtk::HBox					m_textureHBox1;
	Gtk::HBox					m_textureHBox2;
	Gtk::VBox					m_textureVBox;
	Gtk::HBox					m_miscHBox;
	Gtk::Frame					m_geometryFrame;
	Gtk::Frame					m_textureFrame;
	Gtk::Frame					m_miscFrame;
	Gtk::CheckButton			m_applyGeometricalTransformation;
	Gtk::CheckButton			m_triangulate;
	Gtk::CheckButton			m_invertPrimitiveOrientation;
	Gtk::CheckButton			m_encrypt;
	Gtk::CheckButton			m_reflective;
	Gtk::CheckButton			m_bump;
	Gtk::CheckButton			m_specular;
	Gtk::SpinButton				m_textureSize;
	Gtk::ComboBoxText			m_exportLevelCombo;
	Gtk::Label					m_textureSizeLabel;

};



} // namespace node

} // namespace vgGTK



#endif // _VGGTK_NODE_COLLADASETTINGS_HPP_
