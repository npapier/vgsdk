// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGQT_ACTIONS_UI_EXPORTOPENASSETIMPORTUI_HPP_
#define _VGQT_ACTIONS_UI_EXPORTOPENASSETIMPORTUI_HPP_

#include <vgUI/actions/ExportOpenAssetImport.hpp>

#include "vgQt/actions/alg/ExportOpenAssetImport.hpp"


namespace vgQt
{
namespace actions
{
namespace ui
{


/**
 * @brief	Integrates vgQt::actions::alg::ExportOpenAssetImport in the Qt user interface.
 */
struct ExportOpenAssetImportUI : public vgUI::actions::ExportOpenAssetImport< vgQt::actions::alg::ExportOpenAssetImport >
{
	META_ACTION_HPP( ExportOpenAssetImportUI );

	ExportOpenAssetImportUI();
};


} // namespace ui
} // namespace actions
} // namespace vgQt


#endif // _VGQT_ACTIONS_UI_EXPORTOPENASSETIMPORTUI_HPP_
