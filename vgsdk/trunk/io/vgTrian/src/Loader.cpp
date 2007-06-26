// VGSDK - Copyright (C) 2004, 2006, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgTrian/Loader.hpp"

#include <vgDebug/Global.hpp>
#include <vgd/basic/FilenameExtractor.hpp>
#include <vgd/basic/Image.hpp>

#include <vgd/node/Group.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Primitive.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/TextureMatrixTransform.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/node/VertexShape.hpp>



namespace vgTrian
{



std::pair< bool, vgd::Shp< vgd::node::VertexShape > > Loader::loadTrian( const char* pathFilename, const bool bCCW )
{
	std::pair< bool, vgd::Shp< vgd::node::VertexShape > >		retVal;

	vgd::basic::FilenameExtractor extractor( pathFilename );
	std::string							filename;
	std::string							epathFilename;
	
	retVal.first	= false;

	m_path			= extractor.getPath();
	filename		= extractor.getFilename();
	epathFilename	= extractor.getPathFilename();

	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::node::VertexShape::create( epathFilename );
	retVal.second = vertexShape;

	// open file
	std::ifstream fp( pathFilename, std::ios::in);

	if (!fp.good())
	{
		vgDebug::get().logDebug("vgTrian::loadTrian: Unable to open file %s", pathFilename );
		//vgDebug::get().logStatus("vgTrian::loadTrian: Unable to open file %s", pathFilename );		

		return ( retVal );
	}
	else
	{
		vgDebug::get().logDebug("vgTrian::loadTrian: load %s", pathFilename );
		//vgDebug::get().logStatus("vgTrian::loadTrian: load %s", pathFilename );		
	}

	// read nb of vertices
	int32 i32NumVertices;
	fp >> i32NumVertices;
	
	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex		= vertexShape->getFVertexRW();
	vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex	= vertexShape->getFVertexIndexRW();

	// setCounterClockWiseFlag( false ); FIXME

	// read vertices
	vertex->clear();
	vertex->reserve(i32NumVertices);

	for (int32 i=0; i<i32NumVertices; i++)
	{
		float x, y, z;
		fp >> x >> y >> z;
		
		vertex->push_back( vgm::Vec3f(x,y,z) );
	}

	// read nb of faces
	int32 i32NumTriangles;
	fp >> i32NumTriangles;

	// reserve memory for edges.
	// and neighbours FIXME
	vertexIndex->clear();
	vertexIndex->reserve(3*i32NumTriangles);
	// FIXME m_vNeighbours.reserve(3*i32NumTriangles);

	if ( bCCW )
	{
		// read indices of faces
		for (int32 i=0; i<i32NumTriangles; i++)
		{
			// read the three edges of triangle
			int32 lEdge1;
			int32 lEdge2;
			int32 lEdge3;				
	
			fp >> lEdge1 >> lEdge2 >> lEdge3;
	
			vertexIndex->push_back(lEdge1);
			vertexIndex->push_back(lEdge2);				
			vertexIndex->push_back(lEdge3);

			// read the three neighbours of triangle
			int32 lNeighbour1;
			int32 lNeighbour2;
			int32 lNeighbour3;				
	
			fp >> lNeighbour1 >> lNeighbour2 >> lNeighbour3;

			//m_vNeighbours.push_back(lNeighbour1);
			//m_vNeighbours.push_back(lNeighbour2);
			//m_vNeighbours.push_back(lNeighbour3);
		}
	}
	else
	{
		// read indices of faces
		for (int32 i=0; i<i32NumTriangles; i++)
		{
			// read the three edges of triangle
			int32 lEdge1;
			int32 lEdge2;
			int32 lEdge3;				
	
			fp >> lEdge1 >> lEdge2 >> lEdge3;
	
			vertexIndex->push_back(lEdge3);
			vertexIndex->push_back(lEdge2);				
			vertexIndex->push_back(lEdge1);
	
			// read the three neighbours of triangle
			int32 lNeighbour1;
			int32 lNeighbour2;
			int32 lNeighbour3;				
	
			fp >> lNeighbour1 >> lNeighbour2 >> lNeighbour3;
			//m_vNeighbours.push_back(lNeighbour3);
			//m_vNeighbours.push_back(lNeighbour2);
			//m_vNeighbours.push_back(lNeighbour1);
		}
	}

	//m_i32NextEdge = vertexIndex->getNum();
	
	//close file
	fp.close();

	// primitive
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = vertexShape->getFPrimitiveRW();
	primitive->clear();

	vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() );
	primitive->push_back( prim );

	//
	retVal.first = true;

	vgDebug::get().logDebug("vgTrian::loadTrian: load %s done.", pathFilename );
	//vgDebug::get().logStatus("vgTrian::loadTrian: load %s done.", pathFilename );	

	return retVal;
}



std::pair< bool, vgd::Shp< vgd::node::TriSet > > Loader::loadTrian( const std::string& pathFilename, const bool bCCW )
{
	std::pair< bool, vgd::Shp< vgd::node::TriSet > >		retVal;

	vgd::basic::FilenameExtractor	extractor( pathFilename );
	std::string						filename;
	std::string						epathFilename;
	
	retVal.first	= false;

	m_path			= extractor.getPath();
	filename		= extractor.getFilename();
	epathFilename	= extractor.getPathFilename();

	vgd::Shp< vgd::node::TriSet > triset = vgd::node::TriSet::create( epathFilename );
	retVal.second = triset;

	// open file
	std::ifstream fp( pathFilename.c_str() );

	if (!fp.good())
	{
		vgDebug::get().logDebug("vgTrian::loadTrian: Unable to open file %s", pathFilename.c_str() );
		//vgDebug::get().logStatus("vgTrian::loadTrian: Unable to open file %s", pathFilename.c_str() );		

		return ( retVal );
	}
	else
	{
		vgDebug::get().logDebug("vgTrian::loadTrian: load %s", pathFilename.c_str() );
		//vgDebug::get().logStatus("vgTrian::loadTrian: load %s", pathFilename.c_str() );		
	}

	// read nb of vertices
	int32 i32NumVertices;
	fp >> i32NumVertices;
	
	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex		= triset->getFVertexRW();
	vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex	= triset->getFVertexIndexRW();

	// setCounterClockWiseFlag( false ); FIXME

	// read vertices
	vertex->clear();
	vertex->reserve(i32NumVertices);

	for (int32 i=0; i<i32NumVertices; i++)
	{
		float x, y, z;
		fp >> x >> y >> z;
		
		vertex->push_back( vgm::Vec3f(x,y,z) );
	}

	// read nb of faces
	int32 i32NumTriangles;
	fp >> i32NumTriangles;

	// reserve memory for edges.
	// and neighbours FIXME
	vertexIndex->clear();
	vertexIndex->reserve(3*i32NumTriangles);
	// FIXME m_vNeighbours.reserve(3*i32NumTriangles);

	if ( bCCW )
	{
		// read indices of faces
		for (int32 i=0; i<i32NumTriangles; i++)
		{
			// read the three edges of triangle
			int32 lEdge1;
			int32 lEdge2;
			int32 lEdge3;				
	
			fp >> lEdge1 >> lEdge2 >> lEdge3;
	
			vertexIndex->push_back(lEdge1);
			vertexIndex->push_back(lEdge2);				
			vertexIndex->push_back(lEdge3);

			// read the three neighbours of triangle
			int32 lNeighbour1;
			int32 lNeighbour2;
			int32 lNeighbour3;				
	
			fp >> lNeighbour1 >> lNeighbour2 >> lNeighbour3;

			//m_vNeighbours.push_back(lNeighbour1);
			//m_vNeighbours.push_back(lNeighbour2);
			//m_vNeighbours.push_back(lNeighbour3);
		}
	}
	else
	{
		// read indices of faces
		for (int32 i=0; i<i32NumTriangles; i++)
		{
			// read the three edges of triangle
			int32 lEdge1;
			int32 lEdge2;
			int32 lEdge3;				
	
			fp >> lEdge1 >> lEdge2 >> lEdge3;
	
			vertexIndex->push_back(lEdge3);
			vertexIndex->push_back(lEdge2);				
			vertexIndex->push_back(lEdge1);
	
			// read the three neighbours of triangle
			int32 lNeighbour1;
			int32 lNeighbour2;
			int32 lNeighbour3;				
	
			fp >> lNeighbour1 >> lNeighbour2 >> lNeighbour3;
			//m_vNeighbours.push_back(lNeighbour3);
			//m_vNeighbours.push_back(lNeighbour2);
			//m_vNeighbours.push_back(lNeighbour1);
		}
	}

	//m_i32NextEdge = vertexIndex->getNum();
	
	//close file
	fp.close();

	// primitive
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = triset->getFPrimitiveRW();
	primitive->clear();

	vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() );
	primitive->push_back( prim );

	//
	retVal.first = true;

	vgDebug::get().logDebug("vgTrian::loadTrian: load %s done.", pathFilename.c_str() );
	//vgDebug::get().logStatus("vgTrian::loadTrian: load %s done.", pathFilename.c_str() );	

	return retVal;
}



const bool Loader::saveTrian( vgd::Shp< vgd::node::TriSet > triset, const std::string& pathFilename, const bool bCCW )
{
	bool retVal = false;

	vgd::basic::FilenameExtractor	extractor( pathFilename );
	std::string						filename;
	std::string						epathFilename;

	m_path			= extractor.getPath();
	filename		= extractor.getFilename();
	epathFilename	= extractor.getPathFilename();

	// open file
	std::ofstream fp( pathFilename.c_str() );

	if (!fp.good())
	{
		vgDebug::get().logDebug("vgTrian::saveTrian: Unable to open file %s", pathFilename.c_str() );
		//vgDebug::get().logStatus("vgTrian::saveTrian: Unable to open file %s", pathFilename.c_str() );		

		return retVal;
	}
	else
	{
		vgDebug::get().logDebug("vgTrian::saveTrian: saved %s", pathFilename.c_str() );
		//vgDebug::get().logStatus("vgTrian::saveTrian: save %s", pathFilename.c_str() );		
	}

	// write nb of vertices
	vgd::field::EditorRO< vgd::field::MFVec3f >	vertex		= triset->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt32>	vertexIndex	= triset->getFVertexIndexRO();
	
	int32 i32NumVertices = vertex->size();
	fp << i32NumVertices << std::endl;

	// setCounterClockWiseFlag( false ); @todo support

	// write vertices
	for (int32 i=0; i<i32NumVertices; i++)
	{
		const vgm::Vec3f v = (*vertex)[i];

		fp << v[0] << " " << v[1] << " " << v[2] << std::endl;
	}

	// write nb of faces
	int32 i32NumTriangles = vertexIndex->size() / 3;
	assert( vertexIndex->size() % 3 == 0 );

	fp << i32NumTriangles << std::endl;

	if ( bCCW )
	{
		// write edges and neighbours
		// write indices of faces and dummy neighbours
		for (int32 i=0; i<i32NumTriangles; ++i)
		{
			// write the three edges of triangles
			const int32 lEdge1 = (*vertexIndex)[ i*3		]; 
			const int32 lEdge2 = (*vertexIndex)[ i*3 + 1	];
			const int32 lEdge3 = (*vertexIndex)[ i*3 + 2	];
	
			fp << lEdge3 << " " << lEdge2 << " " << lEdge1 << " ";
	
			// write the three neighbours of triangles
			// @todo Real support of neighbours
			const int32 lNeighbour1 = -1;
			const int32 lNeighbour2 = -1;
			const int32 lNeighbour3 = -1;	
	
			fp << lNeighbour1 << " " << lNeighbour2 << " " << lNeighbour3 << std::endl;
		}
	}
	else
	{
		// write edges and neighbours
		// write indices of faces and dummy neighbours
		for (int32 i=0; i<i32NumTriangles; ++i)
		{
			// write the three edges of triangles
			const int32 lEdge1 = (*vertexIndex)[ i*3		]; 
			const int32 lEdge2 = (*vertexIndex)[ i*3 + 1	];
			const int32 lEdge3 = (*vertexIndex)[ i*3 + 2	];
	
			fp << lEdge1 << " " << lEdge2 << " " << lEdge3 << " ";
	
			// write the three neighbours of triangles
			// @todo Real support of neighbours
			const int32 lNeighbour1 = -1;
			const int32 lNeighbour2 = -1;
			const int32 lNeighbour3 = -1;	
	
			fp << lNeighbour1 << " " << lNeighbour2 << " " << lNeighbour3 << std::endl;
		}
	}

	//m_i32NextEdge = vertexIndex->getNum();

	//close file
	fp.close();

	// primitive
	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives = triset->getFPrimitiveRO();
	assert( primitives->size() == 1 );
	vgd::node::Primitive primitive = (*primitives)[0];
	assert( primitive.getType() == vgd::node::Primitive::TRIANGLES );
	assert( primitive.getIndex() == 0 );
	assert( primitive.getNumIndices() == vertexIndex->size() );

	//
	retVal = true;

	vgDebug::get().logDebug("vgTrian::saveTrian: save %s done.", pathFilename.c_str() );
	//vgDebug::get().logStatus("vgTrian::saveTrian: save %s done.", pathFilename.c_str() );

	return retVal;
}



std::pair< bool, vgd::Shp< vgd::node::Group > >	Loader::loadTrian2( const char *pathFilename, bool bCCW  )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > >		retVal;

	retVal.first	= false;
	
	vgd::Shp< vgd::node::Group > group;

	vgd::basic::FilenameExtractor extractor( pathFilename );
	m_path						= extractor.getPath();
	std::string filename		= extractor.getFilename();
	std::string epathFilename	= extractor.getPathFilename();
	
	if ( m_path.length() == 0 )
	{
		m_path = ".";
	}
	
	group = vgd::node::Group::create( epathFilename );
	retVal.second = group;

	// open file
	m_fp.open(pathFilename, std::ios::in);

	if (!m_fp.is_open())
	{
		vgDebug::get().logDebug("vgTrian::loadTrian2: Unable to open file %s", pathFilename );
		//vgDebug::get().logStatus("vgTrian::loadTrian2: Unable to open file %s", pathFilename );		

		return ( retVal );
	}
	else
	{
		vgDebug::get().logDebug("vgTrian::loadTrian2: load %s", pathFilename );
		//vgDebug::get().logStatus("vgTrian::loadTrian2: load %s", pathFilename );
	}
	
	// VERSION
	std::string version;
	m_fp >> version;
	
	if (	(version.compare( "vgsdkExporter100" ) != 0) &&
			(version.compare( "vglExporter100" ) != 0 )
		) 
	{
		return retVal;
	}
	
	// MATERIALS
	vgd::Shp< vgd::node::Switch > switchMaterial = loadMaterials();
	
	if ( switchMaterial->getNumChildren() > 0 )
	{
		group->addChild( switchMaterial );
	}

	// NODE
	while ( !m_fp.eof() )
	{
		std::string name;
		int			integer;
		
		m_fp >> name;
		if ( name.compare("") == 0 )
		{
			break;
		}
		else if ( name == "mesh" )
		{
			// mesh GeoSphere01
			std::string meshName;
			
			m_fp >> meshName;
			
			vgDebug::get().logDebug("vgTrian::loadTrian2: load mesh %s", meshName.c_str() );
			//vgDebug::get().logStatus("vgTrian::loadTrian2: load mesh %s", meshName.c_str() );
			
			m_fp >> name;
			if ( name == "materialIndex" )
			{
				m_fp >> integer;
			
				group->addChild( switchMaterial->getAbstractChild( integer ) );
			}
			else if ( name == "color" )
			{
				std::string	matName( meshName );
				matName		+= "wireColor";
				group->addChild( loadWireColor( matName ) );
			}

			vgd::Shp< vgd::node::VertexShape > vertexShape = loadMesh( meshName );
			if ( vertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX )
			{
				vertexShape->computeNormals();
			}
		
			group->addChild( vertexShape );
		}
		else
		{
			assert( false && "Unknown node" );
		}
	}

	retVal.first = true;
	
	vgDebug::get().logDebug("vgTrian::loadTrian2: load %s done", pathFilename );	
	//vgDebug::get().logStatus("vgTrian::loadTrian2: load %s done", pathFilename );

	//close file
	m_fp.clear();
	m_fp.close();

	return retVal;
}



vgd::Shp< vgd::node::Switch > Loader::loadMaterials()
{
	vgd::Shp< vgd::node::Switch > switchGroup = vgd::node::Switch::create("materials");
	
	// materialList x
	std::string name;
	int32 materialCount;
		
	m_fp >> name;
	if ( name != "materialList" )
	{
		assert( false && "materialList missing ?" );
		return switchGroup;
	}
	
	m_fp >> materialCount;
	
	//material Bricks_Bricks_1
	//ambient 0.1 0.1 0.1
	//diffuse 0.5 0.5 0.5
	//specular 0.9 0.9 0.9
	//emission 0 0 0
	//specularLevel 0
	//glossiness 0
	//opacity 1
	for(	int i=0;
			i < materialCount;
			++i )
	{
		std::string	name;
		std::string matName;

		m_fp >> name;
		if ( name != "material" )
		{
			assert( false );
			continue;
		}
		
		m_fp >> matName;
		vgd::Shp< vgd::node::Group > container = vgd::node::Group::create( matName );
		switchGroup->addChild( container );
		
		vgDebug::get().logDebug("vgTrian::loadTrian2: load material %s", matName.c_str() );
		//vgDebug::get().logStatus("vgTrian::loadTrian2: load material %s", matName.c_str() );		

		vgd::Shp< vgd::node::Material > material = vgd::node::Material::create( matName );
		container->addChild( material );
		vgm::Vec3f color;
				
		// ambient
		m_fp >> name >> color[0] >> color[1] >> color[2];
		assert( name == "ambient" );

		material->setColor( vgd::node::Material::AMBIENT, color );
		
		// diffuse
		m_fp >> name >> color[0] >> color[1] >> color[2];
		assert( name == "diffuse" );

		material->setColor( vgd::node::Material::DIFFUSE, color );
		
		// specular
		m_fp >> name >> color[0] >> color[1] >> color[2];
		assert( name == "specular" );

		material->setColor( vgd::node::Material::SPECULAR, color );
		
		// emission
		m_fp >> name >> color[0] >> color[1] >> color[2];
		assert( name == "emission" );

		material->setColor( vgd::node::Material::EMISSION, color );
		
		// specularLevel/glosiness
		float	real;
		m_fp >> name >> real;
		assert( name == "specularLevel" );
		// FIXME not used.
		
		m_fp >> name >> real;
		assert( name == "glossiness" );
		
		material->setShininess( real );

		// transparency
		m_fp >> name >> real;
		assert( name == "transparency" );
		
		material->setTransparency( 1.f - real );

		loadTextureMaps( container );
	}
	
	return ( switchGroup );
}



void Loader::loadTextureMaps( vgd::Shp< vgd::node::Group > group )
{
	// textureMaps 2
	std::string name;
	int			textureMapSize;
		
	m_fp >> name >> textureMapSize;
	assert( name == "textureMaps" );
	
	for(	int i=0;
			i < textureMapSize;
			++i )
	{
		// texture Bitmap
		m_fp >> name;
		assert( name == "texture" );
		
		m_fp >> name;
		assert( name == "Bitmap" );
		
		// BITMAP TEXTURE
		vgd::Shp< vgd::node::Texture2D > tex = vgd::node::Texture2D::create( name );
		tex->setMultiAttributeIndex( (int8)i );

		// image Brkrun.JPG
		std::string	filename;
		m_fp >> name >> filename;
		assert( name == "image" );
		
		vgDebug::get().logDebug("vgTrian::loadTrian2: load image %s/%s", m_path.c_str(), filename.c_str() );
		//vgDebug::get().logStatus("vgTrian::loadTrian2: load image %s/%s", m_path.c_str(), filename.c_str() );
		vgd::Shp< vgd::basic::Image > image( 
			new vgd::basic::Image( m_path + '/' + filename ) 
			);

		tex->setIImage( image );

		// default value.
		using vgd::node::Texture2D;

		if ( true /*isGL_SGIS_generate_mipmap()*/ )		/// @todo Available from OpenGL 1.4
		{
			vgDebug::get().logDebug("vgTrian::loadTrian2: Automatic mipmap generation (GL_SGIS_generate_mipmap detected)." );
			tex->setMipmap( true );
			tex->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR_MIPMAP_LINEAR );
			tex->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );
		}
		else
		{
			vgDebug::get().logDebug("vgTrian::loadTrian2: No automatic mipmap generation (GL_SGIS_generate_mipmap not detected)." );
			tex->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR );
			tex->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );
		}

		// uvtrans 1 0 0 0   0 1 0 0   0 0 1 0   0 0 0 0
		vgm::MatrixR	matrix;
		
		m_fp >> name;
		assert( name == "uvtrans" );
		m_fp >> matrix[0][0] >> matrix[0][1] >> matrix[0][2] >> matrix[0][3];
		m_fp >> matrix[1][0] >> matrix[1][1] >> matrix[1][2] >> matrix[1][3];		
		m_fp >> matrix[2][0] >> matrix[2][1] >> matrix[2][2] >> matrix[2][3];
		m_fp >> matrix[3][0] >> matrix[3][1] >> matrix[3][2] >> matrix[3][3];
				
//		TransformSeparator  = texture
		if ( true /*!matrix.isIdentity()*/ )
		{
			using vgd::node::TextureMatrixTransform;
			vgd::Shp< TextureMatrixTransform > texTransform = TextureMatrixTransform::create( filename );

			texTransform->setMultiAttributeIndex( (int8)i );
			texTransform->setComposeTransformation( false );
			texTransform->setMatrix( matrix );
			
			if ( i == 0 )																							// add only the first texture map ??? FIXME
			{
				group->addChild( texTransform );
				group->addChild( tex );
			}
		}
		else
		{
			if ( i == 0 )									// add only the first texture map ??? FIXME
			{
				group->addChild( tex );
			}
		}

		// texTiling uWrap vWrap
		m_fp >> name;
		assert( name == "texTiling" );

		//
		m_fp >> name;
		
		if ( name == "uWrap" )
		{
			tex->setWrap( vgd::node::Texture2D::WRAP_S, vgd::node::Texture2D::REPEAT );
		}
		else if ( name == "uMirror" )
		{
			tex->setWrap( vgd::node::Texture2D::WRAP_S, vgd::node::Texture2D::MIRRORED_REPEAT );
		}
		else if ( name == "uClamp" )
		{
			tex->setWrap( vgd::node::Texture2D::WRAP_S, vgd::node::Texture2D::CLAMP );
		}
		else
		{
			assert( false );
		}
		
		//
		m_fp >> name;
		
		if ( name == "vWrap" )
		{
			tex->setWrap( vgd::node::Texture2D::WRAP_T, vgd::node::Texture2D::REPEAT );
		}
		else if ( name == "vMirror" )
		{
			tex->setWrap( vgd::node::Texture2D::WRAP_T, vgd::node::Texture2D::MIRRORED_REPEAT );
		}
		else if ( name == "vClamp" )
		{
			tex->setWrap( vgd::node::Texture2D::WRAP_T, vgd::node::Texture2D::CLAMP );
		}
		else
		{
			assert( false );
		}		

		tex->setFunction( vgd::node::Texture2D::FUN_MODULATE );
	}
}



vgd::Shp< vgd::node::VertexShape > Loader::loadMesh( std::string meshName )
{
	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::node::VertexShape::create( meshName );

	std::string fieldName;


	// VERTEX
	
	m_fp >> fieldName;
	
	if ( fieldName == "vertex" )
	{
		// read nb of vertices
		int32 vertexSize;
		m_fp >> vertexSize;
		
		vgd::field::EditorRW< vgd::field::MFVec3f >	vertex		= vertexShape->getFVertexRW();

		// setCounterClockWiseFlag( false ); FIXME

		// read vertices
		vertex->clear();
		vertex->reserve( vertexSize );
	
		for (	int i=0;
				i < vertexSize;
				++i)
		{
			float x, y, z;
			m_fp >> x >> y >> z;
			vertex->push_back( vgm::Vec3f(x,y,z) );
		}
		
		// next field
		m_fp >> fieldName;		
	}

	
	
	// NORMAL
	if ( fieldName == "normal" )
	{
		// read nb of normals
		int32 normalSize;
		m_fp >> normalSize;
		
		vgd::field::EditorRW< vgd::field::MFVec3f >	normal = vertexShape->getFNormalRW();

		// read normals
		normal->clear();
		normal->reserve( normalSize );
	
		for (	int i=0; 
				i < normalSize;
				++i )
		{
			float x, y, z;
			m_fp >> x >> y >> z;
			normal->push_back( vgm::Vec3f(x,y,z).getNormalized() );
		}
		
		vertexShape->setNormalBinding( vgd::node::BIND_PER_VERTEX );
		
		// next field
		m_fp >> fieldName;
	}



	// TEXCOORD
	if ( fieldName == "texCoord" )
	{
		// read nb of texCoord
		int32 texCoordSize;
		m_fp >> texCoordSize;

		vertexShape->createTexUnits( 2, 0, 1 );											// ??????????FIXME multitexture multiTexcoord
		
		// FIXME only for MFVec2f...
		vgd::field::EditorRW< vgd::field::MFVec2f >	texCoord = vertexShape->getFTexCoordRW<vgd::field::MFVec2f>( 0 );

		// read texCoords
		texCoord->clear();
		texCoord->reserve( texCoordSize );
	
		for (	int i=0; 
				i < texCoordSize;
				++i )
		{
			float x, y;
			m_fp >> x >> y;
			texCoord->push_back( vgm::Vec2f(x,y) );
		}
		
		vertexShape->setTexCoordBinding( 0, vgd::node::BIND_PER_VERTEX );

		// next field
		m_fp >> fieldName;
	}



	// TRIANGLES
	if ( fieldName == "triangles" )
	{
		// read nb of faces
		int32 i32NumTriangles;
		m_fp >> i32NumTriangles;
		
		// reserve memory for edges.
		// and neighbours FIXME
		vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex	= vertexShape->getFVertexIndexRW();	
		vertexIndex->clear();
		vertexIndex->reserve( 3*i32NumTriangles );
	
		// read indices of faces
		for (	int i=0;
				i < i32NumTriangles;
				++i )
		{
			// read the three edges of triangle
			int32 lEdge1;
			int32 lEdge2;
			int32 lEdge3;				
	
			m_fp >> lEdge1 >> lEdge2 >> lEdge3;
	
			vertexIndex->push_back(lEdge1);
			vertexIndex->push_back(lEdge2);				
			vertexIndex->push_back(lEdge3);
		}

		//m_i32NextEdge = vertexIndex->getNum();
	
		// primitive
		vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = vertexShape->getFPrimitiveRW();
		primitive->clear();

		vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() );
		primitive->push_back( prim );
	}

	// ???
	
	return vertexShape;
}



vgd::Shp< vgd::node::Material > Loader::loadWireColor( std::string nodeName )
{
	// color : already readed.
	// 0.52549 0.431373 0.0313725 0
	
	std::string	name;
	vgm::Vec3f	color3;
	float			opacity;
	
	m_fp >> color3[0] >> color3[1] >> color3[2] >> opacity;
	
	vgd::Shp< vgd::node::Material > material;
	
	material = vgd::node::Material::create( nodeName );
	material->setColor( vgd::node::Material::AMBIENT, color3 );
	material->setColor( vgd::node::Material::DIFFUSE, color3 );
	material->setTransparency( 1.f - opacity );
	
	return material;
}



} // namespace vgTrian
