// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgUI/actions/ExportOpenAssetImport.hpp"

#include <vgOpenAssetImport/actions/aiPostProcessing.hpp>



namespace vgUI
{

namespace actions
{


// EXPORTOPENASSETIMPORTCOLLADA
META_ACTION_CPP( ExportOpenAssetImportCollada, 42 )


ExportOpenAssetImportCollada::ExportOpenAssetImportCollada( )
: IActionUI( "Export/Export", "Collada (.dae)", "ExportOpenAssetImportCollada", DEFAULT, "", new vgOpenAssetImport::actions::aiExportCollada() )
{}


const bool ExportOpenAssetImportCollada::isValide( State state )
{
	return state.isShape();
}


// EXPORTOPENASSETIMPORTOBJ
META_ACTION_CPP( ExportOpenAssetImportObj, 43 )


ExportOpenAssetImportObj::ExportOpenAssetImportObj( )
: IActionUI( "Export/Export", "Wavefront (.obj)", "ExportOpenAssetImportObj", DEFAULT, "", new vgOpenAssetImport::actions::aiExportObj() )
{}


const bool ExportOpenAssetImportObj::isValide( State state )
{
	return state.isShape();
}


// EXPORTOPENASSETIMPORTSTL
META_ACTION_CPP( ExportOpenAssetImportStl, 44 )


ExportOpenAssetImportStl::ExportOpenAssetImportStl( )
: IActionUI( "Export/Export", "Stereolithography (.stl)", "ExportOpenAssetImportStl", DEFAULT, "", new vgOpenAssetImport::actions::aiExportStl() )
{}


const bool ExportOpenAssetImportStl::isValide( State state )
{
	return state.isShape();
}


// EXPORTOPENASSETIMPORTPLY
META_ACTION_CPP( ExportOpenAssetImportPly, 45 )


ExportOpenAssetImportPly::ExportOpenAssetImportPly( )
: IActionUI( "Export/Export", "Stanford Polygon Library (.ply)", "ExportOpenAssetImportPly", DEFAULT, "", new vgOpenAssetImport::actions::aiExportPly() )
{}


const bool ExportOpenAssetImportPly::isValide( State state )
{
	return state.isShape();
}


} // namespace actions

} // namespace vgUI
