// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_EXPORTCOLLADA_HPP_
#define _VGGTK_NODE_EXPORTCOLLADA_HPP_

#include <gtkmm/box.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/frame.h>

#include "vgGTK/vgGTK.hpp"

#include <vgOpenCOLLADA/exporter/ExportSettings.hpp>


namespace vgGTK
{

namespace node
{



/**
 * @brief	A widget that allows to configure collada export settings.
 */
struct VGGTK_API ExportCollada : public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 */
	ExportCollada();

	vgOpenCOLLADA::exporter::ExportSettings getExportSettings();


private:

	Gtk::HBox					m_geometryHBox1;
	Gtk::HBox					m_geometryHBox2;
	Gtk::VBox					m_geometryVBox;
	Gtk::HBox					m_miscHBox;
	Gtk::Frame					m_geometryFrame;
	Gtk::Frame					m_miscFrame;
	Gtk::CheckButton			m_applyGeometricalTransformation;
	Gtk::CheckButton			m_triangulate;
	Gtk::CheckButton			m_counterClockwise;
	Gtk::CheckButton			m_encrypt;
	Gtk::ComboBoxText			m_exportLevelCombo;

};



} // namespace node

} // namespace vgGTK



#endif // _VGGTK_NODE_EXPORTCOLLADA_HPP_
