// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_MATERIALEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_MATERIALEXPORTER_HPP

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <vgd/node/Group.hpp>

#include "COLLADASWLibraryMaterials.h"

namespace vgOpenCOLLADA
{

namespace exporter
{

struct SceneExporter;

/**
 * @brief COLLADA effect writer.
 */
struct VGOPENCOLLADA_API MaterialExporter : public COLLADASW::LibraryMaterials
{
	MaterialExporter(COLLADASW::StreamWriter * streamWriter, SceneExporter * sceneExporter, vgd::Shp< vgd::node::Group > sceneGraph);

	void doExport();

private:
	vgd::Shp< vgd::node::Group >	m_sceneGraph;
	SceneExporter					*m_sceneExporter;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_MATERIALEXPORTER_HPP

