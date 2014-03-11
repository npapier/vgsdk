// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_NODE_COLLADASETTINGSDIALOG_HPP_
#define _VGQT_NODE_COLLADASETTINGSDIALOG_HPP_

#include <vgQt/node/ColladaSettings.hpp>

#include <vgOpenCOLLADA/Settings.hpp>

#include <QDialog>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace node
{



struct VGQT_API ColladaSettingsDialog : public QDialog
{
	/**
	 * @brief	Constructor
	 */
	ColladaSettingsDialog();

    vgOpenCOLLADA::Settings getSettings();

private:

    ColladaSettings*	m_exportCollada;
};



} // namespace node

} // namespace vgQt



#endif // _VGQT_NODE_COLLADASETTINGSDIALOG_HPP_
