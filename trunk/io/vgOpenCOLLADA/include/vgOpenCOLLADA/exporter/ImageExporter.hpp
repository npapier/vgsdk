// VGSDK - Copyright (C) 2010 Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_IMAGEEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_IMAGEEXPORTER_HPP

#include <boost/bimap.hpp>
#include <boost/filesystem.hpp>

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <COLLADASWLibraryImages.h>
#include <COLLADABUURI.h>

#include <vge/technique/CollectNode.hpp>

#include <vgOpenCOLLADA/exporter/ExportSettings.hpp>

namespace vgOpenCOLLADA
{

namespace exporter
{

typedef vge::technique::collectedMapType	collectedMapType;

/**
 * @brief COLLADA image writer.
 */
struct VGOPENCOLLADA_API ImageExporter : public COLLADASW::LibraryImages
{
	ImageExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap, std::string filepath, ExportSettings exportSettings );

	/**
	 * @brief start exporting
	 */
	void doExport();

private:
	collectedMapType					m_collectedMap;
	boost::filesystem::path				m_outputFilePath;
	ExportSettings						m_exportSettings;
	std::string							m_imageDirectory;
	std::string							m_imageDirectoryName;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_EFFECTEXPORTER_HPP

