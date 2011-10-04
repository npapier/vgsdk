// VGSDK - Copyright (C) 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/Settings.hpp"

namespace vgOpenCOLLADA
{

Settings::Settings() :
m_applyGeometricalTransformation( false ),
m_triangulate( false ),
m_invertPrimitiveOrientation( false ),
m_encrypt( false ),
m_reflective( true ),
m_bump( true ),
m_specular( true ),
m_textureSize( 8096 ),
m_level( TEXTURE ),
m_filename( "" )
{
}



Settings::Settings(	bool applyGeometricalTransformation, bool triangulate,	bool invertPrimitiveOrientation, 
							   bool encrypt, bool reflective, bool bump, bool specular, int textureSize, LEVEL level ) :
m_applyGeometricalTransformation( applyGeometricalTransformation ),
m_triangulate( triangulate ),
m_invertPrimitiveOrientation( invertPrimitiveOrientation ),
m_encrypt( encrypt ),
m_reflective( reflective ),
m_bump( bump ),
m_specular( specular ),
m_textureSize( textureSize ),
m_level( level ),
m_filename( "" )
{
}



bool Settings::getApplyGeometricalTransformation()
{
	return m_applyGeometricalTransformation;
}



bool Settings::getTriangulate()
{
	return m_triangulate;
}



bool Settings::getInvertPrimitiveOrientation()
{
	return m_invertPrimitiveOrientation;
}



bool Settings::getEncrypt()
{
	return m_encrypt;
}



bool Settings::getReflective()
{
	return m_reflective;
}


bool Settings::getBump()
{
	return m_bump;
}



bool Settings::getSpecular()
{
	return m_specular;
}



int Settings::getTextureSize()
{
	return m_textureSize;
}



LEVEL Settings::getLevel()
{
	return m_level;
}



std::string Settings::getFilename()
{
	return m_filename;
}



void Settings::setFilename( std::string filename )
{
	m_filename = filename;
}



} // namespace vgOpenCOLLADA

