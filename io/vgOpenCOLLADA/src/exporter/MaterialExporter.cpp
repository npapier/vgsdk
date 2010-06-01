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
	
MaterialExporter::MaterialExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap ) :
COLLADASW::LibraryMaterials ( streamWriter ),
m_collectedMap ( collectedMap )
{
}

void MaterialExporter::doExport()
{
	vgDebug::get().logDebug("Exporting materials");
	openLibrary();
	
	typedef collectedMapType::right_map::const_iterator right_const_iterator;

	for( right_const_iterator right_iter = m_collectedMap.right.begin(), iend = m_collectedMap.right.end();
		 right_iter != iend; ++right_iter )
	{
		vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial = right_iter->first;
		
		std::string effectName = collectedMaterial->getEffectId();
		std::string materialName = effectName + MATERIAL_ID_SUFFIX;
		collectedMaterial->setMaterialId( materialName );

		openMaterial ( materialName, COLLADABU::Utils::checkNCName(materialName) );
		addInstanceEffect ( "#" + effectName );
		closeMaterial ();
	}

	closeLibrary();
}


} // namespace exporter

} // namespace vgOpenCOLLADA

