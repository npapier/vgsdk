// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_SCENEEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_SCENEEXPORTER_HPP

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include "vgOpenCOLLADA/exporter/GeometryExporter.hpp"
#include "vgOpenCOLLADA/exporter/EffectExporter.hpp"
#include "vgOpenCOLLADA/exporter/MaterialExporter.hpp"
#include "vgOpenCOLLADA/exporter/VisualSceneExporter.hpp"

#include <vgd/node/Group.hpp>

#include <COLLADASWStreamWriter.h>
#include <COLLADABUURI.h>

namespace vgOpenCOLLADA
{

namespace exporter
{

/**
 * @brief The COLLADA file writer frontend.
 */
struct VGOPENCOLLADA_API SceneExporter
{
	SceneExporter(std::string filepath, vgd::Shp< vgd::node::Group > sceneGraph, vgd::Shp< vgd::node::VertexShape >	node = vgd::Shp< vgd::node::VertexShape >());

	~SceneExporter(){};

	EffectExporter *getEffectExporter();

	GeometryExporter *getGeometryExporter();

	bool doExport();

private:

	void loadExporter();
	
	/**
	* @brief: export the "asset" tag.
	*/
	void exportAsset();

	void exportEffect();

	void exportMaterial();

	void exportGeometry();

	void exportVisualScene();

	void exportScene();

	/**
	* @biref: get an environnement variable.
	* 
	* @param varaibleName: the name of the system variable
	*
	* @return: the variable value.
	*/
	std::string getEnvironmentVariable( const std::string & variableName );

    COLLADASW::StreamWriter				m_streamWriter;
	COLLADASW::URI						m_outputFileUri;

	vgd::Shp< vgd::node::Group >		m_sceneGraph;
	vgd::Shp< vgd::node::VertexShape >	m_node;

	GeometryExporter					*m_geometryExporter;
	EffectExporter						*m_effectExporter;
	MaterialExporter					*m_materialExporter;
	VisualSceneExporter					*m_visualSceneExporter;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_SCENEEXPORTER_HPP

