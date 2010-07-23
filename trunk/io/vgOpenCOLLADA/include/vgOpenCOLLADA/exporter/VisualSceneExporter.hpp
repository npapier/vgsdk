// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_VISUALSCENEEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_VISUALSCENEEXPORTER_HPP

#include <boost/bimap.hpp>

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <vgd/node/Group.hpp>
#include <vge/technique/CollectNode.hpp>
#include <vgOpenCOLLADA/exporter/ExportSettings.hpp>

#include "COLLADASWLibraryVisualScenes.h"

namespace vgOpenCOLLADA
{

namespace exporter
{

typedef vge::technique::collectedMapType	collectedMapType;

/**
 * @brief COLLADA effect writer.
 */
struct VGOPENCOLLADA_API VisualSceneExporter : public COLLADASW::LibraryVisualScenes
{
	VisualSceneExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap, ExportSettings exportSettings );

	void doExport();

private:
	collectedMapType				m_collectedMap;
	ExportSettings					m_exportSettings;

	static const std::string NODE_ID_PRAEFIX;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_VISUALSCENEEXPORTER_HPP

