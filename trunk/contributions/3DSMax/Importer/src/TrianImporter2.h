// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#ifndef __TRIANIMPORTER2__H
#define __TRIANIMPORTER2__H

#include "Max.h"
#include "stdmat.h"

#include <fstream>
#include <string>
#include <vector>

struct Mat
{
	StdMat * mtl;
};

class TrianImporter2
{
public:
	//Constructor
	TrianImporter2( BOOL coordSys );

	//Deconstructor
	~TrianImporter2( void );

	//Importer
	int DoImport( const TCHAR * name, ImpInterface *ii, Interface *i, BOOL suppressPrompts = FALSE );

private:
	//Read the materials from file.
	BOOL ReadMaterials( Interface * i );

	//Set the Properties of a material.
	BOOL SetProperties( StdMat * mat, Interface * i );

	//Read the textures.
	BOOL ReadTextures( StdMat * mat, Interface * i );

	//Read the mesh.
	BOOL ReadMesh( TriObject * obj, int matID );

	//Get the UV Transformation Matrix
	BOOL GetUVTransMatrix( Matrix3 & uvtrans );

	//Similar to assert, but will display "Invalid file format" instead of closing and
	//crashing the program.
	BOOL Assert( std::string first, std::string second );

	//Input Stream.
	std::ifstream m_if;

	//Table to hold the materials.
	std::vector< Mat > m_materials;

	//Coordinate System
	BOOL cS;
};

#endif //__TRIANIMPORTER2__H
