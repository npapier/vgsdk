// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_COLLADASETTINGSDIALOG_HPP_
#define _VGGTK_NODE_COLLADASETTINGSDIALOG_HPP_

#include <gtkmm/dialog.h>

#include "vgGTK/vgGTK.hpp"
#include <vgGTK/node/ColladaSettings.hpp>

#include <vgOpenCOLLADA/Settings.hpp>


namespace vgGTK
{

namespace node
{



struct VGGTK_API ColladaSettingsDialog : public Gtk::Dialog
{
	/**
	 * @brief	Constructor
	 */
	ColladaSettingsDialog();

	vgOpenCOLLADA::Settings getSettings();

private:

	ColladaSettings	m_exportCollada;
};



} // namespace node

} // namespace vgGTK



#endif // _VGGTK_NODE_COLLADASETTINGSDIALOG_HPP_
