// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_EFFECTEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_EFFECTEXPORTER_HPP

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <boost/bimap.hpp>

#include <vgd/node/Group.hpp>
#include <vgd/node/Material.hpp>

#include <vge/technique/CollectNode.hpp>

#include <vgOpenCOLLADA/exporter/ExportSettings.hpp>

#include <COLLADASWLibraryEffects.h>

namespace vgOpenCOLLADA
{

namespace exporter
{

typedef vge::technique::collectedMapType	collectedMapType;

/**
 * @brief COLLADA effect writer.
 */
struct VGOPENCOLLADA_API EffectExporter : public COLLADASW::LibraryEffects
{
	EffectExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap, ExportSettings exportSettings );

	/**
	 * @brief start exporting
	 */
	void doExport();

	/**
	 * @biref Export an effect
	 *
	 * @param collectedMaterial list of vgsdk material/texture to export
	 */
	void exportSimpleEffect( vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial );

	/**
	 * @biref Export all color properties
	 *
	 * @param effect vgSDK material to export
	 *
	 * @param effectProfile current COLLADA exported effect
	 */
	void exportColorEffect( vgd::Shp< vgd::node::Material > effect, COLLADASW::EffectProfile &effectProfile );

	/**
	 * @biref Export all color properties
	 *
	 * @param collectedMaterial list of vgsdk material/texture to export
	 *
	 * @param effectProfile current COLLADA exported effect
	 */
	void exportTextureEffect( vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial, COLLADASW::EffectProfile &effectProfile );

private:
	collectedMapType				m_collectedMap;
	std::string						m_currentEffectName;
	ExportSettings					m_exportSettings;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_EFFECTEXPORTER_HPP

