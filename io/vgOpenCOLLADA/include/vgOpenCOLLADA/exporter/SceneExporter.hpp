// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_SCENEEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_SCENEEXPORTER_HPP

#include <boost/bimap.hpp>

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include "vgOpenCOLLADA/exporter/EffectExporter.hpp"
#include "vgOpenCOLLADA/exporter/ExportSettings.hpp"
#include "vgOpenCOLLADA/exporter/GeometryExporter.hpp"
#include "vgOpenCOLLADA/exporter/ImageExporter.hpp"
#include "vgOpenCOLLADA/exporter/MaterialExporter.hpp"
#include "vgOpenCOLLADA/exporter/VisualSceneExporter.hpp"

#include <vgd/node/Group.hpp>

#include <vge/technique/CollectNode.hpp>

#include <COLLADASWStreamWriter.h>

namespace vgOpenCOLLADA
{

namespace exporter
{

typedef vge::technique::collectedMapType	collectedMapType;

/**
 * @brief The COLLADA file writer frontend.
 */
struct VGOPENCOLLADA_API SceneExporter
{
	SceneExporter( ExportSettings exportSettings, vgd::Shp< vgd::node::Group > rootNode );

	~SceneExporter();

	/**
	 * @brief start exporting
	 */
	bool doExport();

private:

	/**
	 * @brief prepare the scene to be exported corresponding to the settings
	 */
	void prepareExport();

	/**
	 * @brief loads all exporters
	 */
	void loadExporter();
	
	/**
	 * @brief collects all nodes which need to be exported
	 */
	void collectNodes();

	/**
	* @brief export COLLADA asset tag
	*/
	void exportAsset();

	/**
	* @brief call the ImageExporter to export COLLADA image library
	*/
	void exportImage();

	/**
	* @brief call the EffectExporter to export COLLADA effect library
	*/
	void exportEffect();

	/**
	* @brief call the MaterialExporter to export COLLADA material library
	*/
	void exportMaterial();

	/**
	* @brief call the GeometryExporter to export COLLADA geometry library
	*/
	void exportGeometry();

	/**
	* @brief call the VisualSceneExporter to export COLLADA visual scene (scene graph creation)
	*/
	void exportVisualScene();

	/**
	* @briefexport export COLLADA scene tag
	*/
	void exportScene();

	/**
	* @biref: get an environnement variable.
	* 
	* @param varaibleName: the name of the system variable
	*
	* @return: the variable value.
	*/
	std::string getEnvironmentVariable( const std::string & variableName );

    COLLADASW::StreamWriter									m_streamWriter;
	ExportSettings											m_exportSettings;
	std::string												m_outputFileUri;

	vgd::Shp< vgd::node::Group >							m_rootNode;
	collectedMapType										m_collectedMap;

	GeometryExporter										*m_geometryExporter;
	EffectExporter											*m_effectExporter;
	ImageExporter											*m_imageExporter;
	MaterialExporter										*m_materialExporter;
	VisualSceneExporter										*m_visualSceneExporter;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_SCENEEXPORTER_HPP

