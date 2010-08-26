// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_SETTINGS_HPP
#define _VGOPENCOLLADA_SETTINGS_HPP

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <string>

namespace vgOpenCOLLADA
{

enum VGOPENCOLLADA_API LEVEL
{
	GEOMETRY,
	MATERIAL,
	TEXTURE
};

/**
 * @brief Export settings.
 */
struct VGOPENCOLLADA_API Settings
{
	Settings();

	Settings(	bool applyGeometricalTransformation, bool triangulate,	bool invertPrimitiveOrientation, 
		bool encrypt, bool reflective, bool bump, bool specular, int textureSize, LEVEL exportLevel );

	bool			getApplyGeometricalTransformation();
	bool			getTriangulate();
	bool			getInvertPrimitiveOrientation();
	bool			getEncrypt();
	bool			getReflective();
	bool			getBump();
	bool			getSpecular();
	int				getTextureSize();
	LEVEL			getLevel();
	std::string		getFilename();

	void			setFilename( std::string filename );

private:
	bool			m_applyGeometricalTransformation;
	bool			m_triangulate;
	bool			m_invertPrimitiveOrientation;
	bool			m_encrypt;
	bool			m_reflective;
	bool			m_bump;
	bool			m_specular;
	int				m_textureSize;
	LEVEL			m_level;
	std::string		m_filename;

};

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_SETTINGS_HPP

