// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_MATERIALEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_MATERIALEXPORTER_HPP

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <boost/bimap.hpp>

#include <vgd/node/Group.hpp>
#include <vge/technique/CollectNode.hpp>
#include <vgOpenCOLLADA/Settings.hpp>

#include "COLLADASWLibraryMaterials.h"

namespace vgOpenCOLLADA
{

namespace exporter
{

typedef vge::technique::collectedMapType	collectedMapType;

struct SceneExporter;

/**
 * @brief COLLADA effect writer.
 */
struct VGOPENCOLLADA_API MaterialExporter : public COLLADASW::LibraryMaterials
{
	MaterialExporter(COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap, vgOpenCOLLADA::Settings exportSettings );

	/**
	 * @brief start exporting
	 */
	void doExport();

private:
	collectedMapType			m_collectedMap;
	vgOpenCOLLADA::Settings		m_exportSettings;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_MATERIALEXPORTER_HPP

