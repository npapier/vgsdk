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

#include "COLLADASWLibraryVisualScenes.h"

namespace vgOpenCOLLADA
{

namespace exporter
{

	typedef boost::bimap< vgd::Shp< vge::technique::CollectedShape >, vgd::Shp< vge::technique::CollectedMaterial > > collectedMapType;

struct SceneExporter;

/**
 * @brief COLLADA effect writer.
 */
struct VGOPENCOLLADA_API VisualSceneExporter : public COLLADASW::LibraryVisualScenes
{
	VisualSceneExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap );

	void doExport();

private:
	SceneExporter					*m_sceneExporter;
	collectedMapType				m_collectedMap;

	static const std::string NODE_ID_PRAEFIX;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_VISUALSCENEEXPORTER_HPP

