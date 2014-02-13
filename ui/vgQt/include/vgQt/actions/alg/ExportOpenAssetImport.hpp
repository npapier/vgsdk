// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGQT_ACTIONS_ALG_EXPORTOPENASSETIMPORT_HPP_
#define _VGQT_ACTIONS_ALG_EXPORTOPENASSETIMPORT_HPP_

#include <vgOpenAssetImport/actions/aiExport.hpp>


namespace vgQt
{
namespace actions
{
namespace alg
{


/**
 * @brief	Specialization of the vgOpenAssetImport::actions::aiExport action for Qt.
 */
struct ExportOpenAssetImport : public vgOpenAssetImport::actions::aiExport
{
protected:
	const boost::filesystem::path getPath();
};


} // namespace alg
} // namespace actions
} // namespace vgQt


#endif // _VGQT_ACTIONS_ALG_EXPORTOPENASSETIMPORT_HPP_
