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

#include "COLLADASWLibraryMaterials.h"

namespace vgOpenCOLLADA
{

namespace exporter
{

	typedef boost::bimap< vgd::Shp< vge::technique::CollectedShape >, vgd::Shp< vge::technique::CollectedMaterial > > collectedMapType;

struct SceneExporter;

/**
 * @brief COLLADA effect writer.
 */
struct VGOPENCOLLADA_API MaterialExporter : public COLLADASW::LibraryMaterials
{
	MaterialExporter(COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap );

	/**
	 * @brief start exporting
	 */
	void doExport();

private:
	collectedMapType	m_collectedMap;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_MATERIALEXPORTER_HPP

