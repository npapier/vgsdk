// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#include "TrianImporter2.h"

TrianImporter2::TrianImporter2( BOOL coordSys )
{
	//Set the coordinate system.
	cS = coordSys;
}

TrianImporter2::~TrianImporter2( void )
{
	if( m_if.is_open() )
		m_if.close();
}

int TrianImporter2::DoImport( const TCHAR * name, ImpInterface *ii, Interface *i, BOOL suppressPrompts )
{
	//Open the input file to read the information.
	m_if.open( name );
	if( !m_if.is_open() )
		return FALSE;

	//Get the version information and make sure the start of the file is valid.
	std::string version;
	m_if >> version;
	if( version.compare( "vglExporter100" ) != 0 )
	{
		std::string errMsg = version + " is an incorrect version.";
		::MessageBox( NULL, errMsg.c_str(), "Error", MB_OK | MB_ICONERROR );
		return FALSE;
	}

	//Read the material information and only continue if it was succesful.
	if( !ReadMaterials( i ) )
	{
		::MessageBox( NULL, "Failed reading material.", "Error", MB_OK | MB_ICONERROR );
		return FALSE;
	}

	//Read all the meshes and add to the scene.
	while( !m_if.eof() )
	{
		//Get the name of the mesh.
		std::string identifier, mshName;

		m_if >> identifier >> mshName;

		//If there is no identifier, then we are finished.
		if( identifier.compare( "" ) == 0 )
			return TRUE;

		if( !Assert( identifier, "mesh" ) ) return FALSE;

		//Does the mesh have a material or just a base color.
		int matIndex = -1; Color c; float tmp;

		m_if >> identifier;
		
		//Has a material, get the index of the material.
		if( identifier.compare( "materialIndex" ) == 0 )
			m_if >> matIndex;
		//Has a wire color, get the color for the object.
		else if( identifier.compare( "color" ) == 0 )
			m_if >> c.r >> c.g >> c.b >> tmp;
		//Error in the file format.
		else
			return FALSE;

		//Create a TriObject to construct the mesh.
		TriObject * obj = CreateNewTriObject();

		//Read the mesh information.
		if( !ReadMesh( obj, matIndex ) ) 
			return FALSE;

		//Create a node representing the mesh.
		INode * node = i->CreateObjectNode( obj );

		TSTR name( mshName.c_str() );
		node->SetName( name.data() );

		//Set material or wirecolor.
		if( matIndex != -1 )
			node->SetMtl( m_materials.at( matIndex ).mtl );
		else
			node->SetWireColor( RGB( c.r * 255.0f, c.g * 255.0f, c.b * 255.0f ) );

		//Have the texture be shown on the object in the scene.
		node->SetShowFrozenWithMtl( TRUE );

		//Redraw the viewports to include this new object.
		i->RedrawViews( i->GetTime() );
	}

	//Return sucess.
	return TRUE;
}

BOOL TrianImporter2::ReadMaterials( Interface * i )
{
	//Read in the number of materials for the scene.
	std::string identifier; int numMat;
	m_if >> identifier >> numMat;

	//Assert the identifier.
	if( !Assert( identifier, "materialList" ) ) return FALSE;

	//Cycle through and add each material.
	m_materials.clear(), m_materials.reserve( numMat );
	for( int m = 0; m < numMat; m++ )
	{
		//Create a material object.
		StdMat * mat = NewDefaultStdMat();

		//Get the name of the material.
		std::string matName;
		m_if >> identifier >> matName;

		if( !Assert( identifier, "material" ) ) return FALSE;
		mat->SetName( TSTR( matName.c_str() ) );

		//Set the properties of the material.
		if( !SetProperties( mat, i ) ) return FALSE;

		//Read in the texture information.
		if( !ReadTextures( mat, i ) ) return FALSE;

		//Add the material to the mateial list in the mth position.
		i->PutMtlToMtlEditor( mat, m );

		//Add the material to the table.
		Mat mtl; mtl.mtl = mat;
		m_materials.push_back( mtl );
	}

	//Return success
	return TRUE;
}

BOOL TrianImporter2::SetProperties( StdMat * mat, Interface * i )
{
	Color c; float v;
	std::string identifier;

	//Ambient
	m_if >> identifier; 
	if( !Assert( identifier, "ambient" ) ) return FALSE;
	m_if >> c.r >> c.g >> c.b;
	mat->SetAmbient( c, i->GetTime() );
	
	//Diffuse
	m_if >> identifier;
	if( !Assert( identifier, "diffuse" ) ) return FALSE;
	m_if >> c.r >> c.g >> c.b;
	mat->SetDiffuse( c, i->GetTime() );

	//Specular
	m_if >> identifier;
	if( !Assert( identifier, "specular" ) ) return FALSE;
	m_if >> c.r >> c.g >> c.b;
	mat->SetSpecular( c, i->GetTime() );

	//Emission
	m_if >> identifier;
	if( !Assert( identifier, "emission" ) ) return FALSE;
	m_if >> c.r >> c.g >> c.b;
	mat->SetFilter( c, i->GetTime() );
	
	//Specular Level.
	m_if >> identifier;
	if( !Assert( identifier, "specularLevel" ) ) return FALSE;
	m_if >> v;
	mat->SetShinStr( v, i->GetTime() );

	//Glossiness
	m_if >> identifier;
	if( !Assert( identifier, "glossiness" ) ) return FALSE;
	m_if >> v;
	mat->SetShininess( v, i->GetTime() );

	//Opacity
	m_if >> identifier;
	if( !Assert( identifier, "transparency" ) ) return FALSE;
	m_if >> v;
	mat->SetOpacity( 1.0f - v, i->GetTime() );

	return TRUE;
}

BOOL TrianImporter2::ReadTextures( StdMat * mat, Interface * i )
{
	//Read the number of textures for the scene.
	std::string identifier; int numTex;
	m_if >> identifier >> numTex;
	if( !Assert( identifier, "textureMaps" ) ) return FALSE;

	//Cycle through each texture for this material and add.
	for( int t = 0; t < numTex; t++ )
	{
		//Make sure the texture is a texture bitmap.
		std::string type;
		m_if >> identifier >> type;
		if( !Assert( identifier, "texture" ) || !Assert( type, "Bitmap" ) ) return FALSE;

		//Create the bitmap and add to the material.
		BitmapTex * bm = NewDefaultBitmapTex();

		//Get the filename.
		std::string filename;
		m_if >> identifier >> filename;
		if( !Assert( identifier, "image" ) ) return FALSE;
		TSTR name( filename.c_str() );
		bm->SetMapName( name.data() );

		//Read in the UV Transformation Matrix.
		//NOT SURE HOW TO HANDLE THIS YET??????????????
		Matrix3 uvtrans;
		if( !GetUVTransMatrix( uvtrans ) ) return FALSE;

		//Read in the texTiling information.
		//NOT SURE HOW TO HANDLE THIS YET??????????????
		std::string u,v;
		m_if >> identifier >> u >> v;
		if( !Assert( identifier, "texTiling" ) ) return FALSE;

		//For now, since VGSDK can only handle diffuse textures, put the texture in that position.
		mat->SetSubTexmap( ID_DI, bm );
		mat->EnableMap( ID_DI, TRUE );

		//Activate the texture.
		i->ActivateTexture( bm, mat );
	}

	return TRUE;
}

BOOL TrianImporter2::ReadMesh( TriObject * obj, int matID )
{
	//Each mesh could be different.  They will not have all information. i.e. normals texCoords etc.
	std::string identifier;

	m_if >> identifier;

	//VERTEX
	if( identifier.compare( "vertex" ) == 0 )
	{
		//Get the number of vertices.
		int numVert;
		m_if >> numVert;
	
		//Set the number of vertices for the triObject and then get each vertex.
		obj->mesh.setNumVerts( numVert );

		for( int i = 0; i < numVert; i++ )
		{
			//Get the point.
			Point3 v;
			m_if >> v.x >> v.y >> v.z;
			obj->mesh.setVert( i, v );
		}

		//Get the next identifier.
		m_if >> identifier;
	}

	//NORMAL
	if( identifier.compare( "normal" ) == 0 )
	{
		//Get the number of normals.
		int numNorm;
		m_if >> numNorm;

		//Get each normal and add to object.
		for( int i = 0; i < numNorm; i++ )
		{
			//Get the normal.
			Point3 n;
			m_if >> n.x >> n.y >> n.z;
			obj->mesh.setNormal( i, n );
		}

		//Get the next identifier.
		m_if >> identifier;
	}

	//TEXCOORD
	if( identifier.compare( "texCoord" ) == 0 )
	{
		//Get the number of texCoords.
		int numTex;
		m_if >> numTex;

		//Set and store each texCoord.
		obj->mesh.setNumTVerts( numTex );

		for( int i = 0; i < numTex; i++ )
		{
			//Get the texCoord.
			UVVert t; t.z = 0.0f;
			m_if >> t.x >> t.y;
			obj->mesh.setTVert( i, t );
		}

		//Get the next identifier.
		m_if >> identifier;
	}

	//FACES
	if( identifier.compare( "triangles" ) == 0 )
	{
		//Get the number of faces.
		int numFaces;
		m_if >> numFaces;

		//Set and add each face to the obj.
		obj->mesh.setNumFaces( numFaces );
		obj->mesh.setNumTVFaces( numFaces );

		for( int i = 0; i < numFaces; i++ )
		{
			//Get three edges.
			int e1, e2, e3;
			m_if >> e1 >> e2 >> e3;

			//Set the face information.
			obj->mesh.faces[i].setVerts( e1, e2, e3 );
			obj->mesh.faces[i].setEdgeVisFlags( EDGE_VIS, EDGE_VIS, EDGE_VIS );

			//Set the texture face information.
			obj->mesh.tvFace[i].setTVerts( e1, e2, e3 );
		}

		//Return success
		return TRUE;
	}

	//If here, invalid identifier.
	return FALSE;
}

BOOL TrianImporter2::GetUVTransMatrix( Matrix3 &uvtrans )
{
	//Get the identifier and make sure everything is correct.
	std::string identifier;
	m_if >> identifier;

	if( !Assert( identifier, "uvtrans" ) ) return FALSE;

	//Cycle through and fill the matrix.
	for( int i = 0; i < 4; i++ )
	{
		//The last column in each row is only for vgsdk.
		float x, y, z, extra;
		m_if >> x >> y >> z >> extra;

		//Set the row.
		Point3 p( x, y, z );
		uvtrans.SetRow( i, p );
	}

	return TRUE;
}

BOOL TrianImporter2::Assert( std::string first, std::string second )
{
	//Compare the two strings, if they are equal return TRUE, otherwise
	//return false.
	if( first.compare( second ) == 0 )
		return TRUE;
	else
	{
		std::string errorMsg = "Error in file.\nNeeded: " + first + " Received: " + second;
		::MessageBox( NULL, errorMsg.c_str(), "Error", MB_OK | MB_ICONERROR );
		return FALSE;
	}
}
