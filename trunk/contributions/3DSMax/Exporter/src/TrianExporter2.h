// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#ifndef __TRIANEXPORTER2__H
#define __TRIANEXPORTER2__H

#include <fstream>
#include <string>
#include <vector>

#include "IGame.h"
#include "IGameObject.h"
#include "IGameProperty.h"
#include "IGameControl.h"
#include "IGameModifier.h"
#include "IConversionManager.h"
#include "IGameError.h"

#include "MyErrorProc.h"

class TrianExporter2
{
public:
	//Default Constructor
	TrianExporter2( void );

	//Constructor
	TrianExporter2( BOOL triOrientation, unsigned int version );

	//Deconstructor
	~TrianExporter2( void );

	//Do Export
	int DoExport( const TCHAR * name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0 );

protected:
	//Export the materials from the game scene.
	void ExportMaterials( void );

	//Export a node from the game scene.
	void ExportNodeInfo( IGameNode * node );

	//Dump the material
	void DumpMaterial( IGameMaterial * mat );

	//Dump the property.
	void DumpProperty( IGameProperty * prop );

	//Dump the texture.
	void DumpTexture( IGameMaterial * mat );

	//Dump the mesh
	void DumpMesh( IGameMesh * gm, TCHAR * meshName );

	//Search method for use with DumpMesh.
	// @todo Optimize
	int Search( Point3 v, Point3 n, Point2 t );

	//Dump the wire color.
	void DumpWireColor( IGameNode * node );

	// Dump matrix 4x4
	void DumpMatrix( GMatrix * matrix );

	//Dump a Matrix 3x3
	void DumpMatrix( Matrix3 * matrix );

	//Dump Texture Tiling.
	void DumpTexTiling( int textTiling );

	//Find the path of the destination directory.
	void FindDirectoryPath( const TCHAR * name );

	//Find the path of the max file directory.
	void FindMaxDirPath();

	//Read the config file for the options.
	BOOL ReadCFGFile( void );

	//Get Last error Message.
	int GetErrorMsg( TSTR &errorMsg );

	//Check openIL error.
	const bool isILError();

	//Update progress bar
	void updateProgress( std::string msg );

private:
	//Game Scene.
	IGameScene * m_pIGame;

	//Triangle Orientation
	BOOL m_triOrientation;

	//Version of the exporter.
	unsigned int m_version;

	//Options for extension.
	BOOL m_expMaterials, m_expNormals, m_expTexCoord;

	//Cfg file path.
	TSTR m_cfgFile;

	//Directory path of where to save the file.
	std::string m_path;

	//Directory to the max file.
	std::string m_pathMax;

	//Tables for vertices, normals and texCoords from the Game mesh.
	std::vector< Point3 >	m_fVertices, m_fNormals;
	std::vector< Point2 >	m_fTexCoords;
	std::vector< int >		m_fVertexIndex;

	//An interface pointer the plug-in may use to call methods of 3ds max.
	Interface *m_interface;

	// The percentage complete (0 to 99). This is what causes the progress bar to move.
	int m_percent;
	int m_percentInc;

	//Output stream
	std::ofstream m_of;
};

#endif //__TRIANEXPORTER2__H
