// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#include "TrianExporter2.h"

#include <algorithm>
#include <bmmlib.h>
#include <Path.h>
//#include <iparamb2.h>
#include <strclass.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <vgm/Utilities.hpp>


TrianExporter2::TrianExporter2( void )
: m_percent(0)
{
	//Initialize.
	m_triOrientation = TRUE;
	m_version		 = 100;
	m_pIGame		 = 0;

	//Options
	m_expMaterials = m_expNormals = m_expTexCoord = FALSE;

	// Initializes openil
	ilInit();
	iluInit();
}

TrianExporter2::TrianExporter2( BOOL triOrientation, unsigned int version )
: m_percent(0)
{
	//Initialize
	m_triOrientation = triOrientation;
	m_version		 = version;
	m_pIGame		 = 0;

	//Options
	m_expMaterials = m_expNormals = m_expTexCoord = FALSE;

	// Initializes openil
	ilInit();
	iluInit();
}

TrianExporter2::~TrianExporter2( void )
{
	if( m_pIGame != 0 )
	{
		m_pIGame->ReleaseIGame();
		m_pIGame = 0;
	}
}

// Dummy function for progress bar
DWORD WINAPI fn2( LPVOID arg )
{
	return( 0 );
}

int TrianExporter2::DoExport( const TCHAR * name, ExpInterface *ei, Interface *i, BOOL suppressPrompts, DWORD options )
{
	//Set the current interface
	m_interface = i;

	//Get the directory of the config file to get the options.
	m_cfgFile += i->GetDir( APP_PLUGCFG_DIR );
	m_cfgFile += "\\";
	m_cfgFile += "vglExporter.cfg";

	//Read the options.
	ReadCFGFile();

	//Find the directory path for the output file.
	//This is used later when saving the textures, if they exist.
	FindDirectoryPath( name );
	FindMaxDirPath();

	//Open the file.
	TSTR tstrName(name);
	TSTR path, filename;
	SplitPathFile( tstrName, &path, &filename );

	m_of.open( name );

	//Make sure there were no problems opening the file.
	if( !m_of.is_open() )
	{
		std::string error = "Error opening output file...";
		error.append( name );
		::MessageBox( NULL, error.c_str(), "Error", MB_OK | MB_ICONERROR );
		return FALSE;
	}

	//Output the version.
	m_of << "vgsdkExporter" << m_version << std::endl;
	
	//Setup the error procedure
	MyErrorProc pErrorProc;
	SetErrorCallBack( &pErrorProc );

	//Get the Game Scene.
	m_pIGame = GetIGameInterface();

	//Start the progress bar.
	TSTR progressMsg;
	progressMsg = TSTR("Exporting to ") + filename;
	m_interface->ProgressStart( progressMsg, TRUE, fn2, NULL );

/*//Setup the conversion manager
//IGameConversionManager * cm = GetConversionManager();

//Set up the my coordinate system.
//cm->SetCoordSystem( IGameConversionManager::IGAME_USER );

UserCoord myCoordSystem = {
	1,	//Right Handed
	1,	//X axis goes right
	3,	//Y Axis goes down
	4,	//Z Axis goes in.
	1,	//U Tex axis is right
	1,  //V Tex axis is Down
};

cm->SetUserCoordSystem( myCoordSystem );

//Set the coordinate system.
//cm->SetCoordSystem( IGameConversionManager::IGAME_OGL);*/

	//Initialize the game scene.
	m_pIGame->InitialiseIGame( options & SCENE_EXPORT_SELECTED );

	//Export the material information first.
	if( m_expMaterials )
	{
		//Update the progress Bar.
		std::string msg("Processing materials...");
		updateProgress( msg );

		ExportMaterials();
	}

	//Initialize percent of exportation and export the mesh information.
	const int percentAfterMaterial = 10;
	m_percent = percentAfterMaterial;

	m_percentInc = m_pIGame->GetTopLevelNodeCount() > 0 ?
		(100-percentAfterMaterial) / m_pIGame->GetTopLevelNodeCount() :
		100-percentAfterMaterial;

	for( int l = 0; l < m_pIGame->GetTopLevelNodeCount(); ++l, m_percent = percentAfterMaterial + l * m_percentInc )
	{
		// Cancel export ?
		if ( m_interface->GetCancel() )
		{
			int retVal = MessageBox(m_interface->GetMAXHWnd(), _T("Really Cancel"),
									_T("Question"), MB_ICONQUESTION | MB_YESNO );

			if ( retVal == IDYES)
			{
				break;
			}
			else if ( retVal == IDNO)
			{
				m_interface->SetCancel(FALSE);
			}
		}

		//Get the node.
		IGameNode * node = m_pIGame->GetTopLevelNode( l );

		//Update the progress Bar.
		std::string msg("Processing ");
		msg += node->GetName();
		updateProgress( msg );
		
		//Check for selected state.
		if( node->IsTarget() )
			continue;

		//If a valid node, Export the node.
		if( !node )
			continue;
		ExportNodeInfo( node );
	}

	m_percent = 100;
	progressMsg = TSTR("Finished exporting ") + filename;
	updateProgress( progressMsg.data() );

	//Stop the progress bar.
	m_interface->ProgressEnd();

	//Release the game scene.
	m_pIGame->ReleaseIGame();
	m_pIGame = 0;

	//Close the output file.
	m_of.close();

	//return success.
	return TRUE;
}

void TrianExporter2::ExportMaterials( void )
{
	//Get the number of materials.
	int numMats = m_pIGame->GetRootMaterialCount();

	//Output to file.
	m_of << "materialList " << numMats << std::endl;

	//Cycle through each material and dump the contents to file.
	for( int i = 0; i < numMats; i++ )
	{
		//Get the material.
		IGameMaterial * mat = m_pIGame->GetRootMaterial( i );

		//If its valid dump, otherwise continue.
		if( mat )
			DumpMaterial( mat );

		// Progress
		m_percent += static_cast<int>( 
						static_cast<float>(i+1)/static_cast<float>(numMats) * 10.f
						);
		std::string msg("Processing materials...");
		updateProgress( msg );
	}
}

void TrianExporter2::ExportNodeInfo( IGameNode * node )
{
	BOOL tmpTexCoord = m_expTexCoord;

	//If the node is a group owner, do nothing with it.
	if( !node->IsGroupOwner() )
	{
		//Get the game object.
		IGameObject * obj = node->GetIGameObject();

		//We will only dump the info if it is a IGAME_MESH.
		if( obj->GetIGameType() == IGameObject::IGAME_MESH )
		{
			//Get the Mesh.
			IGameMesh * gm = ( IGameMesh * )obj;

			gm->SetCreateOptimizedNormalList();

			//If initialization works, dump the mesh.
			if( gm->InitializeData() && gm->GetNumberOfFaces() != 0 )
			{
				//First output the name of the mesh.
				m_of << "mesh " << *node->GetName() << std::endl;

				//Output the material id.
				if( node->GetMaterialIndex() != -1 )
					m_of << "materialIndex " << node->GetMaterialIndex() << std::endl;
				else
				{
					//If there is a wire color, leave out the texCoords even if they exists.
					m_expTexCoord = FALSE;
					DumpWireColor( node );  //Dump the wire color if no material.
				}

				//Dump the mesh.
				DumpMesh( gm, node->GetName() );
			}
		}
	}
	
	m_expTexCoord = tmpTexCoord;
}

void TrianExporter2::DumpMaterial( IGameMaterial * mat )
{
	//Get the name of the material and output to file.
	TCHAR * name = mat->GetMaterialName();

	m_of << "material " << *name << std::endl;

	//Get each property if the material does not have sub materials.
	if( !mat->IsMultiType() )
	{
		/*
		 * If the material does not have a given property, the default
		 * value listed in the Red Book is used.
		 */
		IGameProperty * prop;

		//Ambient Data
		prop = mat->GetAmbientData();
		m_of << "ambient ";
		if( !prop )
			m_of << "0.2 0.2 0.2" << std::endl;
		else
			DumpProperty( prop );
			
		//Diffuse Data
		prop = mat->GetDiffuseData();
		m_of << "diffuse ";
		if( !prop )
			m_of << "0.8 0.8 0.8" << std::endl;
		else
			DumpProperty( prop );

		//Specular Data
		prop = mat->GetSpecularData();
		m_of << "specular ";
		if( !prop )
			m_of << "0.0 0.0 0.0" << std::endl;
		else
			DumpProperty( prop );

		//Emission Data
		prop = mat->GetEmissiveData();
		m_of << "emission ";
		if( !prop )
			m_of << "0.0 0.0 0.0" << std::endl;
		else
			DumpProperty( prop );
	
		//Specular Level Data.
		prop = mat->GetSpecularLevelData();
		m_of << "specularLevel ";
		if( !prop )
			m_of << "0.0" << std::endl;
		else
			DumpProperty( prop );

		//Glossiness Data ( value from 0 to 1 )
		prop = mat->GetGlossinessData();
		m_of << "glossiness ";
		if( !prop )
			m_of << "0.0" << std::endl;
		else
			DumpProperty( prop );
	
		//Transparency
		prop = mat->GetOpacityData();
		m_of << "transparency ";
		if( !prop )
			m_of << "0.0" << std::endl;
		else
		{
			float t;
			prop->GetPropertyValue( t );
			m_of << 1.0f - t << std::endl;
		}
	}

	//Dump the texture information, if needed
	DumpTexture( mat );

/*	//If the material has submaterials, dump each sub material.
	//@todo Loading .trian2 file with submaterials !!!
	if( mat->IsMultiType() )
	{
		for( int i = 0; i < mat->GetSubMaterialCount(); i++ )
		{
			IGameMaterial * subMat = mat->GetSubMaterial( i );

			//If a valid sub material, dump it.
			if( subMat )
				DumpMaterial( subMat );
		}
	}*/
}

void TrianExporter2::DumpProperty( IGameProperty * prop )
{
	if ( prop == 0 )
	{
		m_of << "na" << std::endl;
		return;
	}

	Point4 p4; Point3 p3; int i; TCHAR *s; float f;

	//Output the property based on its type.
	switch( prop->GetType() )
	{
	case IGAME_POINT3_PROP:
		prop->GetPropertyValue( p3 );
		m_of << p3.x << " " << p3.y << " " << p3.z << std::endl;
		break;

	case IGAME_INT_PROP:
		prop->GetPropertyValue( i );
		m_of << i << std::endl;
		break;

	case IGAME_FLOAT_PROP:
		prop->GetPropertyValue( f );
		m_of << f << std::endl;
		break;

	case IGAME_STRING_PROP:
		prop->GetPropertyValue( s );
		m_of << *s << std::endl;
		break;

	case IGAME_POINT4_PROP:
		prop->GetPropertyValue( p4 );
		m_of << p4.w << " " << p4.x << " " << p4.y << " " << p4.z << std::endl;
		break;

	case IGAME_UNKNOWN_PROP:
	default:
		m_of << "unknown" << std::endl;
		assert(false);
		break;
	}
}

void TrianExporter2::DumpTexture( IGameMaterial * mat )
{
	// Don't export texture maps if tex coordinates are not exported
	if ( !m_expTexCoord )
	{
		m_of << "textureMaps " << 0 << std::endl;
		return;
	}

	//Get the number of textures and output.
	const int numTex = mat->GetNumberOfTextureMaps();

	//@todo FIXME remove this limitation
	// Don't export more than one texture map
	const int numTexToExport = std::min<int>(numTex, 1 /* todo numTexToExportFromGUI*/ );

	m_of << "textureMaps " << numTexToExport << std::endl;

	//For each texture output its information.
	for( int i = 0; i < numTexToExport; i++ )
	{
		//Get the texture.
		IGameTextureMap * tex = mat->GetIGameTextureMap( i );

		//Get 3dsmax texmap and co
		Texmap *	pTexMap		= tex->GetMaxTexmap();
		/*BitmapTex*	pBitmapTex	= (BitmapTex*)pTexMap;
		assert( pBitmapTex != 0 );*/

		//Texture map must be valid or a textured bitmap to continue.
		// if it is a textured bitmap.
		if( !tex || !tex->IsEntitySupported() )
			continue;

		//Print
		m_of << "texture Bitmap" << std::endl;

		//Get path, filename and extensiopn of bitmap
		TCHAR * source = tex->GetBitmapFileName();

		TSTR tstrSource( source );

		TSTR tstrPath, tstrFilename, tstrExtension;
		SplitFilename( tstrSource, &tstrPath, &tstrFilename, &tstrExtension );

		TSTR tstrFilenameDestination = TSTR("trian2_") + tstrFilename + TSTR(".png");

		//See if the directory is actually included.
		m_of << "image " << tstrFilenameDestination << std::endl;

		//Set up path for new location.
		std::string destination( m_path );
		destination.append( tstrFilenameDestination.data() );

		//Process texture image
		ILuint imageSrc, imageDst;

		ilGenImages(1, &imageSrc );
		ilBindImage( imageSrc );

		// try to load the bitmap using pathfilename from material
		std::string msgLoad("Loading image ");
		msgLoad += tstrFilename;
		updateProgress( msgLoad );

		ilLoadImage(source);

		bool imageLoaded = !isILError();

		// try to load from others map paths (if needed only)
		for(	int i=0;
				!imageLoaded &&
				(i < TheManager->GetMapDirCount());
				++i )
		{
			const TCHAR *newDir = TheManager->GetMapDir(i);

			using MaxSDK::Util::Path;
			
			Path otherSource( newDir );
			otherSource.Append(		Path( tstrFilename + tstrExtension )	);
			otherSource.Normalize();

			std::string msgLoad("Try another location to loading image ");
			msgLoad += tstrFilename;
			updateProgress( msgLoad );

			ilLoadImage( otherSource.GetCStr() );

			imageLoaded = !isILError();
		}

		if ( !imageLoaded )
		{
			//display the message box.
			std::string msg = "Unable to load: "; msg.append( source );
			::MessageBox( NULL, msg.c_str(), "ERROR", MB_OK | MB_ICONERROR );
		}

		std::string msgFlip("Flip image ");
		msgFlip += tstrFilename;
		updateProgress( msgFlip );

		const int width		= ilGetInteger( IL_IMAGE_WIDTH );
		const int height	= ilGetInteger( IL_IMAGE_HEIGHT );

		const int bpp		= ilGetInteger( IL_IMAGE_BYTES_PER_PIXEL );
		//const int format	= ilGetInteger( IL_IMAGE_FORMAT );
		//const int type	= ilGetInteger( IL_IMAGE_TYPE );

		//iluFlipImage();
		ILubyte *dataSrc = ilGetData();

		imageDst = ilCloneCurImage();
		//ilGenImages(1, &imageDst );
		ilBindImage( imageDst );

		/*ilTexImage( width, height, 1,
					bpp, format, type,
					0 );*/

		ILubyte *dataDst = ilGetData();

		int sizeOfOneLine = width * bpp;

		// Flip
		for( int	iSrc = 0;
					iSrc <= height-1;
					++iSrc)
		{
			memcpy(	&(dataDst[ sizeOfOneLine * ( (height-1) - iSrc ) ]),
					&(dataSrc[ sizeOfOneLine * iSrc ]),
					sizeOfOneLine );
		}

		// Scale
		std::string msgScale("Resize image ");
		msgScale += tstrFilename;
		updateProgress( msgScale );

		iluImageParameter( ILU_FILTER, ILU_SCALE_MITCHELL ); // ILU_SCALE_BOX

        const int widthPow2		= vgm::Utilities::nextPower2( width );
		const int heightPow2	= vgm::Utilities::nextPower2( height );
		const int widthPow2Final	= std::min<int>( widthPow2, 4096 );
		const int heightPow2Final	= std::min<int>( heightPow2, 4096 );

		iluScale( widthPow2Final, heightPow2Final, 1 );

		if ( isILError() )
		{
			::MessageBox( NULL, "Error during image resizing", "ERROR", MB_OK | MB_ICONERROR );
		}

		// Save
		DeleteFile( destination.c_str() ); // @todo delete file only if exists

		std::string msgSave("Saving image ");
		msgSave += tstrFilenameDestination;
		updateProgress( msgSave );

		ilSaveImage(destination.c_str());

		if ( isILError() ) 
		{
			//display the message box.
			std::string msg = "Unable to save : "; msg.append( destination );
			::MessageBox( NULL, msg.c_str(), "ERROR", MB_OK | MB_ICONERROR );
		}

		ilDeleteImages( 1, &imageSrc );
		ilDeleteImages( 1, &imageDst );

// IGameTextureMap
/* No values !!!
IGameProperty * prop = tex->GetClipUData();
DumpProperty(prop);

prop = tex->GetClipVData();
DumpProperty(prop);

prop = tex->GetClipHData();
DumpProperty(prop);

prop = tex->GetClipWData();
DumpProperty(prop);*/

		// Get the texture xform
		IGameUVGen *pUVGen = tex->GetIGameUVGen();
		GMatrix uvtrans = pUVGen->GetUVTransform();

		m_of << "uvtrans" << std::endl;
		DumpMatrix( &uvtrans );

/* No values 
DumpProperty( pUVGen->GetUOffsetData() );
DumpProperty( pUVGen->GetVOffsetData() );
DumpProperty( pUVGen->GetUTilingData() );
DumpProperty( pUVGen->GetVTilingData() );
DumpProperty( pUVGen->GetUAngleData() );
DumpProperty( pUVGen->GetVAngleData() );
DumpProperty( pUVGen->GetWAngleData() ); */

/*
StdUVGen*	pStdUVGen	= pBitmapTex->GetUVGen();

IParamBlock2* pUVWCropParam = (IParamBlock2*)(pBitmapTex->GetReference(1));
if( pUVWCropParam )
{
	float uvOffsetX, uvOffsetY;
	float uvScaleX, uvScaleY;

	pUVWCropParam->GetValue(0, 0, uvOffsetX, FOREVER);
	pUVWCropParam->GetValue(1, 0, uvOffsetY, FOREVER);
	pUVWCropParam->GetValue(2, 0, uvScaleX,  FOREVER);
	pUVWCropParam->GetValue(3, 0, uvScaleY,  FOREVER);
}*/
		//Last get the texture tiling information of the texture.
		int texTiling = pTexMap->GetTextureTiling();

		//Dump the texttiling.
		DumpTexTiling( texTiling );
	}	
}

void TrianExporter2::DumpMesh( IGameMesh * gm, TCHAR * meshName )
{
	//Tables for the Game mesh.
	std::vector< Point3 > vertices; std::vector< int > vertexIndex;
	std::vector< Point3 > normals; std::vector< int > normalIndex;
	std::vector< Point2 > texCoords; std::vector< int > texCoordIndex;

	//Get all of the vertices from the Game mesh.
	std::string msgVertices("Process vertices of ");
	msgVertices += TSTR(meshName);
	updateProgress( msgVertices );

	int numVertices = gm->GetNumberOfVerts();
	vertices.clear(), vertices.reserve( numVertices );
	for( int i = 0; i < numVertices; i++ )
	{
		Point3 v;
		if( gm->GetVertex( i, v ) )
			vertices.push_back( v ) ;
	}

	//Get all the normals from the Game mesh, if requested to.
	std::string msgNormals("Process normals of ");
	msgNormals += TSTR(meshName);
	updateProgress( msgNormals );

	int numNormals = gm->GetNumberOfNormals();

	if ( m_expNormals && (numNormals == 0) )
	{
		::MessageBox(0,"No normals","Warnings",MB_OK|MB_ICONEXCLAMATION);
	}

	m_expNormals &= ( numNormals > 0 );

	if( m_expNormals )
	{
		normals.clear(), normals.reserve( numNormals );

		for( int i = 0; i < numNormals; i++ )
		{
			Point3 n;
			if( gm->GetNormal( i, n ) )
				normals.push_back( n );
		}
	}

	//Get all the texCoords from the Game Mesh, if requested to.
	std::string msgTexCoords("Process texture coordinates of ");
	msgTexCoords += TSTR(meshName);
	updateProgress( msgTexCoords );

	int numTexCoords = gm->GetNumberOfTexVerts();
	m_expTexCoord &= ( numTexCoords > 0 );
	if( m_expTexCoord )
	{
		texCoords.clear(), texCoords.reserve( numTexCoords );
		for( int i = 0; i < numTexCoords; i++ )
		{
			Point2 t;
			if( gm->GetTexVertex( i, t ) )
				texCoords.push_back( t );
		}
	}

	//Get all of the vertex indices from the Game mesh.
	std::string msgIndices("Process indices of ");
	msgIndices += TSTR(meshName);
	updateProgress( msgIndices );

	int numFaces = gm->GetNumberOfFaces();
	vertexIndex.clear(), vertexIndex.reserve( numFaces * 3 );
	if( m_expNormals )
		normalIndex.clear(), normalIndex.reserve( numFaces * 3 );
	if( m_expTexCoord )
		texCoordIndex.clear(), texCoordIndex.reserve( numFaces * 3 );

	for( int i = 0; i < numFaces; i++ )
	{
		FaceEx * f = gm->GetFace( i );

		//Push all information back based on the desired orientation.
		if( m_triOrientation )
		{
			vertexIndex.push_back( f->vert[2] );
			vertexIndex.push_back( f->vert[1] );
			vertexIndex.push_back( f->vert[0] );

			if( m_expNormals )
			{
				normalIndex.push_back( f->norm[2] );
				normalIndex.push_back( f->norm[1] );
				normalIndex.push_back( f->norm[0] );
			}
			if( m_expTexCoord )
			{
				texCoordIndex.push_back( f->texCoord[2] );
				texCoordIndex.push_back( f->texCoord[1] );
				texCoordIndex.push_back( f->texCoord[0] );
			}
		}
		else
		{
			vertexIndex.push_back( f->vert[0] );
			vertexIndex.push_back( f->vert[1] );
			vertexIndex.push_back( f->vert[2] );
		
			if( m_expNormals )
			{
				normalIndex.push_back( f->norm[0] );
				normalIndex.push_back( f->norm[1] );
				normalIndex.push_back( f->norm[2] );
			}
			if( m_expTexCoord )
			{
				texCoordIndex.push_back( f->texCoord[0] );
				texCoordIndex.push_back( f->texCoord[1] );
				texCoordIndex.push_back( f->texCoord[2] );
			}
		}
	}

	//VGL requires that each vertex have its own tex coord and normal information.  3DS
	//Max however does not export the information per vertex.  Thus, the following makes sure
	//that the texture and normal information is valid for VGSDK.
	//Clear previous final information.

	float percent = static_cast<float>(m_percent);
	const float percentInc = static_cast<float>(m_percentInc) / static_cast<float>(vertexIndex.size());

	m_fVertices.clear(), m_fNormals.clear(), m_fTexCoords.clear(), m_fVertexIndex.clear();
	int currentVertexIndex = 0;
	for( int i = 0; i < vertexIndex.size(); i++ )
	{
		//Storage.
		Point3 v = Point3( 0.0f, 0.0f, 0.0f ), n = Point3( 0.0f, 0.0f, 0.0f );
		Point2 t = Point2( 0.0f, 0.0f );

		//Store current vertex.
		v = vertices.at( vertexIndex.at( i ) );

		//Store normal if exporting normal.
		if( m_expNormals )
			n = normals.at( normalIndex.at( i ) );

		//Store texCoord if exporting texCoords.
		if( m_expTexCoord )
			t = texCoords.at( texCoordIndex.at( i ) );

		//See if this combination already exists in the final lists.
		int exists = Search( v, n, t );

		if( exists != -1 )
			m_fVertexIndex.push_back( exists );
		else
		{
			m_fVertices.push_back( v );
			if( m_expNormals )
				m_fNormals.push_back( n );
			if( m_expTexCoord )
				m_fTexCoords.push_back( t );
			m_fVertexIndex.push_back( currentVertexIndex++ );
		}

		//Progress
		percent += percentInc;
		if ( static_cast<int>(percent) > m_percent )
		{
			m_percent = static_cast<int>(percent);
			std::string msgAdapt("Final mesh processing of ");
			msgAdapt += TSTR(meshName);
			updateProgress( msgAdapt );
		}
	}

	// Progress
	std::string msgWrite("Write mesh of ");
	msgWrite += TSTR(meshName);
	updateProgress( msgWrite );

	//Write Information to file.
	//VERTEX
	m_of << "vertex " << m_fVertices.size() << std::endl;
	for( int i = 0; i < m_fVertices.size(); i++ )
	{
		Point3 v = m_fVertices.at( i );
		m_of << v.x << " " << v.y << " " << v.z << std::endl;
	}

	// NORMAL
	if( m_expNormals )
	{
		m_of << "normal " << m_fNormals.size() << std::endl;

		for(	int i = 0;
				i < m_fNormals.size();
				++i )
		{
			Point3 n = m_fNormals[i];
			m_of << n.x << " " << n.y << " " << n.z << std::endl;
		}
	}

	//TEXCOORD
	if( m_expTexCoord )
	{
		m_of << "texCoord " << m_fTexCoords.size() << std::endl;
		for( int i = 0; i < m_fTexCoords.size(); i++ )
		{
			Point2 t = m_fTexCoords.at( i );

			m_of << t.x << " " << t.y << std::endl;
		}
	}

	//VERTEX INDEX
	m_of << "triangles " << m_fVertexIndex.size() / 3 << std::endl;
	for( int i = 0; i < m_fVertexIndex.size(); )
	{
		int a = m_fVertexIndex.at( i++ );
		int b = m_fVertexIndex.at( i++ );
		int c = m_fVertexIndex.at( i++ );

		m_of << a << " " << b << " " << c << std::endl;
	}
}

int TrianExporter2::Search( Point3 v, Point3 n, Point2 t )
{
	//Run through the final vertices, texCoords, normals lists and see
	//if the combination already exists.
	for( int i = 0; i < m_fVertices.size(); i++ )
	{
		//First check the vertices.
		bool found = (m_fVertices[i] == v);

		if (!found)
			continue;

		//Check normals
		if( m_expNormals )
		{
			found = (m_fNormals[i] == n);
		
			if (!found)
				continue;
		}

		//Check texCoords.
		if( m_expTexCoord )
		{
			found = (m_fTexCoords[i] == t);
		
			//if (!found) continue;
		}

		//If there was a match, return the index.
		if( found )
		{
            return i;
		}
		//else continue
	}

	return -1;
}

void TrianExporter2::DumpWireColor( IGameNode * node )
{
	//Get the color.
	DWORD color = node->GetMaxNode()->GetWireColor();

	//Output the color.
	m_of << "color ";
	m_of << GetRValue( color ) / 255.0f << " "; //Red Value.
	m_of << GetGValue( color ) / 255.0f << " "; //Green Value.
	m_of << GetBValue( color ) / 255.0f << " "; //Blue Value.
	m_of << "1" << std::endl;					//Opacity Value.
}

void TrianExporter2::DumpMatrix( GMatrix *matrix )
{
	Point4 p;

	//Get each row and output.
	for( int i = 0; i < 4; i++ )
	{
		//Get the row.
		p = matrix->GetRow( i );

		m_of << p.x << " " << p.y << " " << p.z << " " << p.w << std::endl;
	}
}

void TrianExporter2::DumpMatrix( Matrix3 * mat )
{
	Point3 p;

	//Get each row and output.
	for( int i = 0; i < 4; i++ )
	{
		//Get the row.
		p = mat->GetRow( i );

		m_of << p.x << " " << p.y << " " << p.z;

		if( i != 3 )
			m_of << " 0 ";
		else
			m_of << " 1" << std::endl;
	}
}

void TrianExporter2::DumpTexTiling( int texTiling )
{
	//Standard
	m_of << "texTiling ";

	//Handle U
	if( texTiling & U_WRAP )
		m_of << "uWrap ";
	else if( texTiling & U_MIRROR )
		m_of << "uMirror ";
	else
		m_of << "uClamp ";

	//Handle V
	if( texTiling & V_WRAP )
		m_of << "vWrap ";
	else if( texTiling & V_MIRROR )
		m_of << "vMirror ";
	else
		m_of << "vClamp ";

	m_of << std::endl;
}

void TrianExporter2::FindDirectoryPath( const TCHAR * name )
{
	//Extract the directory.
	std::string full( name );

	//Find the last Occurence of '/'
	int index = full.rfind( "\\" );

	if( index != std::string::npos )
		m_path = full.substr( 0, index + 1 );
}

void TrianExporter2::FindMaxDirPath()
{
	//Get the full max file directory from the interface.
	TSTR full = m_interface->GetCurFilePath();

	//Remove the file name to get the directory path.
	m_pathMax = std::string( full.data() );

	int index = m_pathMax.rfind( "\\" );

	m_pathMax = m_pathMax.substr( 0, index + 1 );
}

BOOL TrianExporter2::ReadCFGFile( void )
{
	//File
	FILE * cfgStream;

	//Try and open the file.
	cfgStream = fopen( m_cfgFile, "rb" );
	if( !cfgStream )
		return FALSE;

	//Read the data.
	BOOL tmp;

	tmp = fgetc( cfgStream );
	m_triOrientation = fgetc( cfgStream );
	m_expMaterials	 = fgetc( cfgStream );
	m_expNormals	 = fgetc( cfgStream );
	m_expTexCoord	 = fgetc( cfgStream );

	//Close the file.
	fclose( cfgStream );

	return TRUE;
}

int TrianExporter2::GetErrorMsg( TSTR &errorMsg )
{
	//The last system error.
	int error = GetLastError();

	switch( error )
	{
	case ERROR_FILE_EXISTS:
		errorMsg += TSTR( "File Exists." );
		break;
	case ERROR_FILE_NOT_FOUND:
		errorMsg += TSTR( "File Not Found." );
		break;
	case ERROR_PATH_NOT_FOUND:
		errorMsg += TSTR( "Path not found." );
		break;
	case ERROR_NOT_READY:
		errorMsg += TSTR( "File not ready." );
		break;
	case ERROR_ACCESS_DENIED:
		errorMsg += TSTR( "Access Denied." );
		break;
	case 1235:
		errorMsg += TSTR( "Failed Acessing the drive." );
		break;
	default:
		errorMsg += TSTR( "unknown error." );
		break;
	}

	return error;
}

const bool TrianExporter2::isILError()
{
	ILenum ilError = ilGetError();
	return ( ilError != IL_NO_ERROR );
}

void TrianExporter2::updateProgress( std::string msg )
{
	TSTR tstrMsg = msg.c_str();
	m_interface->ProgressUpdate( m_percent, FALSE, tstrMsg.data() );
}
