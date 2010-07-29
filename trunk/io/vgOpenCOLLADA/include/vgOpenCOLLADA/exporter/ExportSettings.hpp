// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_EXPORTSETTINGS_HPP
#define _VGOPENCOLLADA_EXPORTER_EXPORTSETTINGS_HPP

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <string>

namespace vgOpenCOLLADA
{

namespace exporter
{

enum VGOPENCOLLADA_API ExportLevel
{
	GEOMETRY,
	MATERIAL,
	TEXTURE
};

/**
 * @brief Export settings.
 */
struct VGOPENCOLLADA_API ExportSettings
{
	ExportSettings();

	ExportSettings(	bool applyGeometricalTransformation, bool triangulate,	bool invertPrimitiveOrientation, 
		bool encrypt, ExportLevel exportLevel );

	bool			getApplyGeometricalTransformation();
	bool			getTriangulate();
	bool			getInvertPrimitiveOrientation();
	bool			getEncrypt();
	ExportLevel		getExportLevel();
	std::string		getFilename();

	void			setFilename( std::string filename );

private:
	bool			m_applyGeometricalTransformation;
	bool			m_triangulate;
	bool			m_invertPrimitiveOrientation;
	bool			m_encrypt;
	ExportLevel		m_exportLevel;
	std::string		m_filename;

};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_EXPORTSETTINGS_HPP

