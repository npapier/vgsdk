// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_EFFECTEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_EFFECTEXPORTER_HPP

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <vgd/node/Group.hpp>
#include <vgd/node/Material.hpp>

#include "COLLADASWLibraryEffects.h"

namespace vgOpenCOLLADA
{

namespace exporter
{

/**
 * @brief COLLADA effect writer.
 */
struct VGOPENCOLLADA_API EffectExporter : public COLLADASW::LibraryEffects
{
	EffectExporter(COLLADASW::StreamWriter * streamWriter, vgd::Shp< vgd::node::Group > sceneGraph, bool exportVertexShape = false);

	void doExport();

	void exportSimpleEffect( vgd::Shp< vgd::node::Material > effect );

	void exportColorEffect( vgd::Shp< vgd::node::Material > effect, COLLADASW::EffectProfile &effectProfile );

	std::vector<std::string> getEffectIdList();

private:
	vgd::Shp< vgd::node::Group >	m_sceneGraph;
	bool							m_exportVertexShape;
	std::string						m_currentEffectName;
	std::vector<std::string>		m_effectIdList;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_EFFECTEXPORTER_HPP

