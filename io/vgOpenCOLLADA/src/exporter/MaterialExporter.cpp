// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/MaterialExporter.hpp"

#include "vgOpenCOLLADA/exporter/SceneExporter.hpp"

#include <vgDebug/Global.hpp>
#include <vgd/visitor/helpers.hpp>


namespace vgOpenCOLLADA
{

namespace exporter
{
	
MaterialExporter::MaterialExporter(COLLADASW::StreamWriter * streamWriter, SceneExporter * sceneExporter, vgd::Shp< vgd::node::Group > sceneGraph) :
COLLADASW::LibraryMaterials ( streamWriter ),
m_sceneExporter ( sceneExporter),
m_sceneGraph( sceneGraph )
{
}

void MaterialExporter::doExport()
{
	vgDebug::get().logDebug("Exporting materials");
	openLibrary();

	std::vector<std::string> effectList = m_sceneExporter->getEffectExporter()->getEffectIdList();
	
	for(uint i = 0; i < effectList.size(); i++)
	{
		std::string effectName = effectList[i];
		std::string materialName = effectName + MATERIAL_ID_SUFFIX;
		openMaterial ( materialName, COLLADABU::Utils::checkNCName(materialName) );
		addInstanceEffect ( "#" + effectName );
		closeMaterial ();
	}

	closeLibrary();
}


} // namespace exporter

} // namespace vgOpenCOLLADA

