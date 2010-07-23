// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/ExportSettings.hpp"

namespace vgOpenCOLLADA
{

namespace exporter
{


ExportSettings::ExportSettings() :
m_applyGeometricalTransformation( false ),
m_triangulate( false ),
m_counterClockwise( false ),
m_encrypt( false ),
m_exportLevel( TEXTURE ),
m_filename( "" )
{
}



ExportSettings::ExportSettings(	bool applyGeometricalTransformation, bool triangulate,	bool counterClockwise, 
							   bool encrypt, ExportLevel exportLevel ) :
m_applyGeometricalTransformation( applyGeometricalTransformation ),
m_triangulate( triangulate ),
m_counterClockwise( counterClockwise ),
m_encrypt( encrypt ),
m_exportLevel( exportLevel ),
m_filename( "" )
{
}



bool ExportSettings::getApplyGeometricalTransformation()
{
	return m_applyGeometricalTransformation;
}



bool ExportSettings::getTriangulate()
{
	return m_triangulate;
}



bool ExportSettings::getCounterClockwise()
{
	return m_counterClockwise;
}



bool ExportSettings::getEncrypt()
{
	return m_encrypt;
}



ExportLevel ExportSettings::getExportLevel()
{
	return m_exportLevel;
}



std::string ExportSettings::getFilename()
{
	return m_filename;
}



void ExportSettings::setFilename( std::string filename )
{
	m_filename = filename;
}



} // namespace exporter

} // namespace vgOpenCOLLADA

