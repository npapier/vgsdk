// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_EXPORTCOLLADADIALOG_HPP_
#define _VGGTK_NODE_EXPORTCOLLADADIALOG_HPP_

#include <gtkmm/dialog.h>

#include "vgGTK/vgGTK.hpp"
#include <vgGTK/node/ExportCollada.hpp>

#include <vgOpenCOLLADA/exporter/ExportSettings.hpp>


namespace vgGTK
{

namespace node
{



struct VGGTK_API ExportColladaDialog : public Gtk::Dialog
{
	/**
	 * @brief	Constructor
	 */
	ExportColladaDialog();

	vgOpenCOLLADA::exporter::ExportSettings getExportSettings();

private:

	ExportCollada	m_exportCollada;
};



} // namespace node

} // namespace vgGTK



#endif // _VGGTK_NODE_EXPORTCOLLADADIALOG_HPP_
