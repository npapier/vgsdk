// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2010, 2012, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgTrian/Loader.hpp"

#include <sstream>

#include <vgAlg/actions/Decrypt.hpp>
#include <vgAlg/node/VertexShape.hpp>

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

#include <vgio/Cache.hpp>
#include <vgio/FileSystem.hpp>
#include <vgio/helpers.hpp>


namespace vgTrian
{

META_LOADER_CPP( vgTrian::Loader, "trian2" )

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
		vgLogDebug("vgTrian::loadTrian: Unable to open file %s", pathFilename );
		//vgLogStatus("vgTrian::loadTrian: Unable to open file %s", pathFilename );

		return ( retVal );
	}
	else
	{
#ifdef _DEBUG
		vgLogDebug("vgTrian::loadTrian: load %s", pathFilename );
#endif
		//vgLogStatus("vgTrian::loadTrian: load %s", pathFilename );
	}

	// read nb of vertices
	int32 i32NumVertices;
	fp >> i32NumVertices;
	
	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex		= vertexShape->getVertexRW();
	vgd::field::EditorRW< vgd::field::MFUInt>	vertexIndex	= vertexShape->getVertexIndexRW();

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
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = vertexShape->getPrimitiveRW();
	primitive->clear();

	vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() );
	primitive->push_back( prim );

	//
	retVal.first = true;

#ifdef _DEBUG
	vgLogDebug("vgTrian::loadTrian: load %s done.", pathFilename );
	//vgLogStatus("vgTrian::loadTrian: load %s done.", pathFilename );
#endif

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
		vgLogDebug("vgTrian::loadTrian: Unable to open file %s", pathFilename.c_str() );
		//vgLogStatus("vgTrian::loadTrian: Unable to open file %s", pathFilename.c_str() );

		return ( retVal );
	}
	else
	{
#ifdef _DEBUG
		vgLogDebug("vgTrian::loadTrian: load %s", pathFilename.c_str() );
		//vgLogStatus("vgTrian::loadTrian: load %s", pathFilename.c_str() );
#endif
	}

	// read nb of vertices
	int32 i32NumVertices;
	fp >> i32NumVertices;
	
	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex		= triset->getVertexRW();
	vgd::field::EditorRW< vgd::field::MFUInt>	vertexIndex	= triset->getVertexIndexRW();

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
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = triset->getPrimitiveRW();
	primitive->clear();

	vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() );
	primitive->push_back( prim );

	//
	retVal.first = true;

#ifdef _DEBUG
	vgLogDebug("vgTrian::loadTrian: load %s done.", pathFilename.c_str() );
	//vgLogStatus("vgTrian::loadTrian: load %s done.", pathFilename.c_str() );
#endif

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
		vgLogDebug("vgTrian::saveTrian: Unable to open file %s", pathFilename.c_str() );
		//vgLogStatus("vgTrian::saveTrian: Unable to open file %s", pathFilename.c_str() );

		return retVal;
	}
	else
	{
#ifdef _DEBUG
		vgLogDebug("vgTrian::saveTrian: saved %s", pathFilename.c_str() );
		//vgLogStatus("vgTrian::saveTrian: save %s", pathFilename.c_str() );
#endif
	}

	// write nb of vertices
	vgd::field::EditorRO< vgd::field::MFVec3f >	vertex		= triset->getVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt>	vertexIndex	= triset->getVertexIndexRO();
	
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
	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives = triset->getPrimitiveRO();
	assert( primitives->size() == 1 );
	vgd::node::Primitive primitive = (*primitives)[0];
	assert( primitive.getType() == vgd::node::Primitive::TRIANGLES );
	assert( primitive.getIndex() == 0 );
	assert( static_cast<uint32>(primitive.getNumIndices()) == vertexIndex->size() );

	//
	retVal = true;

#ifdef _DEBUG
	vgLogDebug("vgTrian::saveTrian: save %s done.", pathFilename.c_str() );
	//vgLogStatus("vgTrian::saveTrian: save %s done.", pathFilename.c_str() );
#endif

	return retVal;
}



/*std::pair< bool, vgd::Shp< vgd::node::Group > >	Loader::loadTrian2( const char *pathFilename, bool bCCW ) //, const bool useCache )
{
	return load( pathFilename, bCCW );
}*/



std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const vgio::Media & media, const std::string & filePath, const bool bCCW )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > >		retVal;
	retVal.first	= false;

	// m_useCache = useCache;

	vgd::Shp< vgd::node::Group > group;

	vgd::basic::FilenameExtractor extractor( filePath.c_str() );
	m_path						= extractor.getPath();
	std::string filename		= extractor.getFilename();
	std::string epathFilename	= extractor.getPathFilename();
	
	if ( m_path.length() == 0 )
	{
		m_path = ".";
	}
	
	group = vgd::node::Group::create( epathFilename );
	retVal.second = group;

	// Open file
	vgd::Shp< std::istream >	in = media.open( filePath );

	if (!in)
	{
		vgLogDebug("vgTrian::loadTrian2: Unable to open file %s", filePath.c_str() );
		//vgLogStatus("vgTrian::loadTrian2: Unable to open file %s", pathFilename );

		return ( retVal );
	}
	else
	{
#ifdef _DEBUG
		vgLogDebug("vgTrian::loadTrian2: load %s", filePath.c_str() );
		//vgLogStatus("vgTrian::loadTrian2: load %s", pathFilename );
#endif
	}

	retVal.first = loadTrian2( media, *in, group );

	if( retVal.first )
	{
#ifdef _DEBUG
		vgLogDebug("vgTrian::loadTrian2: load %s done", filePath.c_str() );
		//vgLogStatus("vgTrian::loadTrian2: load %s done", pathFilename );
#endif
	}
	else
	{
		vgLogDebug("vgTrian::loadTrian2: Unable to open file %s", filePath.c_str() );
		//vgLogStatus("vgTrian::loadTrian2: Unable to open file %s", pathFilename );
	}
	return retVal;
}



std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string filePath, const bool bCCW )
{
	return load( vgio::FileSystem(), filePath, bCCW );
}



std::pair< bool, vgd::Shp< vgd::node::Group > >	Loader::load( const std::string pathFilename, vgd::Shp< std::vector< char > > buffer, bool bCCW )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > >		retVal;
	retVal.first	= false;

	vgd::Shp< vgd::node::Group > group = vgd::node::Group::create( pathFilename );
	retVal.second = group;

	std::stringstream	in( std::string(buffer->begin(), buffer->end()) );
	
	vgd::basic::FilenameExtractor extractor( pathFilename.c_str() );
	m_path						= extractor.getPath();
	
	if ( m_path.length() == 0 )
	{
		m_path = ".";
	}

	retVal.first = loadTrian2( vgio::FileSystem(), in, group );

	if( retVal.first )
	{
#ifdef _DEBUG
		vgLogDebug("vgTrian::loadTrian2: load %s done", pathFilename.c_str() );
		//vgLogStatus("vgTrian::loadTrian2: load %s done", pathFilename );
#endif
	}
	else
	{
		vgLogDebug("vgTrian::loadTrian2: Unable to open file %s", pathFilename.c_str() );
		//vgLogStatus("vgTrian::loadTrian2: Unable to open file %s", pathFilename );
	}
	return retVal;
}



std::pair< bool, vgd::Shp< vgd::node::Group > >	Loader::load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW )
{
	m_imageMap = imageMap;
	
	return load( filePath, outBuffer, bCCW );
}



const bool Loader::loadTrian2( const vgio::Media & media, std::istream & in, vgd::Shp< vgd::node::Group > group )
{
	// VERSION
	std::string version;
	in >> version;
	
	if (	(version.compare( "vgsdkExporter100" ) != 0) &&
			(version.compare( "vglExporter100" ) != 0 )
		) 
	{
		return false;
	}
	
	// MATERIALS
	vgd::Shp< vgd::node::Switch > switchMaterial = loadMaterials( media, in );
	
	if ( switchMaterial->getNumChildren() > 0 )
	{
		group->addChild( switchMaterial );
	}

	// NODE
	while ( !in.eof() )
	{
		std::string name;
		int			integer;
		
		in >> name;
		if ( name.compare("") == 0 )
		{
			break;
		}
		else if ( name == "mesh" )
		{
			// mesh GeoSphere01
			std::string meshName;
			
			in >> meshName;

#ifdef _DEBUG
			vgLogDebug("vgTrian::loadTrian2: load mesh %s", meshName.c_str() );
			//vgLogStatus("vgTrian::loadTrian2: load mesh %s", meshName.c_str() );
#endif
			
			in >> name;
			if ( name == "materialIndex" )
			{
				in >> integer;
			
				group->addChild( switchMaterial->getAbstractChild( integer ) );
			}
			else if ( name == "color" )
			{
				std::string	matName( meshName );
				matName		+= "wireColor";
				group->addChild( loadWireColor( in, matName ) );
			}

			vgd::Shp< vgd::node::VertexShape > vertexShape = loadMesh( in, meshName );
			if ( vertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX )
			{
				vgAlg::node::computeNormals( vertexShape );
			}

			group->addChild( vertexShape );
			
		}
		else
		{
			assert( false && "Unknown node" );
		}
	}

	return true;
}



vgd::Shp< vgd::node::Switch > Loader::loadMaterials( const vgio::Media & media, std::istream & in )
{
	vgd::Shp< vgd::node::Switch > switchGroup = vgd::node::Switch::create("materials");
	
	// materialList x
	std::string name;
	int32 materialCount;
		
	in >> name;
	if ( name != "materialList" )
	{
		assert( false && "materialList missing ?" );
		return switchGroup;
	}
	
	in >> materialCount;
	
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

		in >> name;
		if ( name != "material" )
		{
			assert( false );
			continue;
		}
		
		in >> matName;
		vgd::Shp< vgd::node::Group > container = vgd::node::Group::create( matName );
		switchGroup->addChild( container );

#ifdef _DEBUG
		vgLogDebug("vgTrian::loadTrian2: load material %s", matName.c_str() );
		//vgLogStatus("vgTrian::loadTrian2: load material %s", matName.c_str() );
#endif

		vgd::Shp< vgd::node::Material > material = vgd::node::Material::create( matName );
		container->addChild( material );
		vgm::Vec3f color;
				
		// ambient
		in >> name >> color[0] >> color[1] >> color[2];
		assert( name == "ambient" );

		material->setAmbient( color );
		
		// diffuse
		in >> name >> color[0] >> color[1] >> color[2];
		assert( name == "diffuse" );

		material->setDiffuse( color );
		
		// specular
		in >> name >> color[0] >> color[1] >> color[2];
		assert( name == "specular" );

		material->setSpecular( color );
		
		// emission
		in >> name >> color[0] >> color[1] >> color[2];
		assert( name == "emission" );

		material->setEmission( color );
		
		// specularLevel/glosiness
		float	real;
		in >> name >> real;
		assert( name == "specularLevel" );
		// FIXME not used.
		
		in >> name >> real;
		assert( name == "glossiness" );
		
		material->setShininess( real );

		// transparency
		in >> name >> real;
		assert( name == "transparency" );
		
		material->setOpacity( 1.f - real );

		loadTextureMaps( media, in, container );
	}
	
	return ( switchGroup );
}



void Loader::loadTextureMaps( const vgio::Media & media, std::istream & in, vgd::Shp< vgd::node::Group > group )
{
	// textureMaps 2
	std::string name;
	int			textureMapSize;
		
	in >> name >> textureMapSize;
	assert( name == "textureMaps" );
	
	for(	int i=0;
			i < textureMapSize;
			++i )
	{
		// texture Bitmap
		in >> name;
		assert( name == "texture" );
		
		in >> name;
		assert( name == "Bitmap" );
		
		// BITMAP TEXTURE

		// image Brkrun.JPG
		std::string	filename;
		in >> name >> filename;
		assert( name == "image" );

		vgd::Shp< vgd::node::Texture2D > tex = vgd::node::Texture2D::create( filename, (int8)i );

#ifdef _DEBUG
		vgLogDebug("vgTrian::loadTrian2: load image %s/%s", m_path.c_str(), filename.c_str() );
		//vgLogStatus("vgTrian::loadTrian2: load image %s/%s", m_path.c_str(), filename.c_str() );
#endif

		vgd::Shp< vgd::basic::IImage > image;

		if( m_imageMap.size() > 0 )
		{
			image = m_imageMap[ filename ];
		}
		else
		{
			// Gathers the image from the cache.
			image = vgio::ImageCache::load( media, m_path + '/' + filename );
		}
		
		
		/*if ( m_useCache )
		{
			image = vgio::ImageCache::load( m_path + '/' + filename );
			vgLogDebug("vgTrian::loadTrian2: image %s/%s found in cache.", m_path.c_str(), filename.c_str() );
		}
		else
		{
			image.reset( new vgd::basic::Image( m_path + '/' + filename ) );
		}*/

		tex->setImage( image );

		// default value.
		using vgd::node::Texture2D;

		if ( true /*isGL_SGIS_generate_mipmap()*/ )		/// @todo Available from OpenGL 1.4
		{
			//vgLogDebug("vgTrian::loadTrian2: Automatic mipmap generation (GL_SGIS_generate_mipmap detected)." );
			tex->setMipmap( true );
			tex->setMinFilter( Texture2D::LINEAR_MIPMAP_LINEAR );
			tex->setMagFilter( Texture2D::LINEAR );
		}
		else
		{
			vgLogDebug("vgTrian::loadTrian2: No automatic mipmap generation (GL_SGIS_generate_mipmap not detected)." );
			tex->setMinFilter( Texture2D::LINEAR );
			tex->setMagFilter( Texture2D::LINEAR );
		}

		// uvtrans 1 0 0 0   0 1 0 0   0 0 1 0   0 0 0 0
		vgm::MatrixR	matrix;
		
		in >> name;
		assert( name == "uvtrans" );
		in >> matrix[0][0] >> matrix[0][1] >> matrix[0][2] >> matrix[0][3];
		in >> matrix[1][0] >> matrix[1][1] >> matrix[1][2] >> matrix[1][3];
		in >> matrix[2][0] >> matrix[2][1] >> matrix[2][2] >> matrix[2][3];
		in >> matrix[3][0] >> matrix[3][1] >> matrix[3][2] >> matrix[3][3];
				
//		TransformSeparator  = texture
		if ( true /*!matrix.isIdentity()*/ )
		{
			using vgd::node::TextureMatrixTransform;
			vgd::Shp< TextureMatrixTransform > texTransform = TextureMatrixTransform::create( filename );
			texTransform->setMultiAttributeIndex( (int8)i );

			texTransform->setComposeTransformation( false );
			texTransform->setMatrix( matrix );

			group->addChild( texTransform );
			group->addChild( tex );
		}
		else
		{
			group->addChild( tex );
		}

		// texTiling uWrap vWrap
		in >> name;
		assert( name == "texTiling" );

		//
		in >> name;
		
		if ( name == "uWrap" )
		{
			tex->setWrapS( vgd::node::Texture2D::REPEAT );
		}
		else if ( name == "uMirror" )
		{
			tex->setWrapS( vgd::node::Texture2D::MIRRORED_REPEAT );
		}
		else if ( name == "uClamp" )
		{
			tex->setWrapS( vgd::node::Texture2D::CLAMP );
		}
		else
		{
			assert( false );
		}
		
		//
		in >> name;
		
		if ( name == "vWrap" )
		{
			tex->setWrapT( vgd::node::Texture2D::REPEAT );
		}
		else if ( name == "vMirror" )
		{
			tex->setWrapT( vgd::node::Texture2D::MIRRORED_REPEAT );
		}
		else if ( name == "vClamp" )
		{
			tex->setWrapT( vgd::node::Texture2D::CLAMP );
		}
		else
		{
			assert( false );
		}

		tex->sethFunction( vgd::node::Texture2D::FUN_MODULATE );
	}
}



vgd::Shp< vgd::node::VertexShape > Loader::loadMesh( std::istream & in, const std::string & meshName )
{
	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::node::VertexShape::create( meshName );

	std::string fieldName;


	// VERTEX
	
	in >> fieldName;
	
	if ( fieldName == "vertex" )
	{
		// read nb of vertices
		int32 vertexSize;
		in >> vertexSize;

		vgd::field::EditorRW< vgd::field::MFVec3f >	vertex		= vertexShape->getVertexRW();

		// setCounterClockWiseFlag( false ); FIXME

		// read vertices
		vertex->clear();
		vertex->reserve( vertexSize );

		for (	int i=0;
				i < vertexSize;
				++i)
		{
			float x, y, z;
			in >> x >> y >> z;
			vertex->push_back( vgm::Vec3f(x,y,z) );
		}
		
		// next field
		in >> fieldName;
	}



	// NORMAL
	if ( fieldName == "normal" )
	{
		// read nb of normals
		int32 normalSize;
		in >> normalSize;
		
		vgd::field::EditorRW< vgd::field::MFVec3f >	normal = vertexShape->getNormalRW();

		// read normals
		normal->clear();
		normal->reserve( normalSize );
	
		for (	int i=0; 
				i < normalSize;
				++i )
		{
			float x, y, z;
			in >> x >> y >> z;
			normal->push_back( vgm::Vec3f(x,y,z).getNormalized() );
		}
		
		vertexShape->setNormalBinding( vgd::node::BIND_PER_VERTEX );
		
		// next field
		in >> fieldName;
	}



	// TEXCOORD
	if ( fieldName == "texCoord" )
	{
		// read nb of texCoord
		int32 texCoordSize;
		in >> texCoordSize;

		vertexShape->createTexUnits( 2, 0, 1 );											// ??????????FIXME multitexture multiTexcoord
		
		// FIXME only for MFVec2f...
		vgd::field::EditorRW< vgd::field::MFVec2f >	texCoord = vertexShape->getTexCoordRW<vgd::field::MFVec2f>( 0 );

		// read texCoords
		texCoord->clear();
		texCoord->reserve( texCoordSize );
	
		for (	int i=0; 
				i < texCoordSize;
				++i )
		{
			float x, y;
			in >> x >> y;
			texCoord->push_back( vgm::Vec2f(x,y) );
		}
		
		vertexShape->setTexCoordBinding( 0, vgd::node::BIND_PER_VERTEX );

		// next field
		in >> fieldName;
	}



	// TRIANGLES
	if ( fieldName == "triangles" )
	{
		// read nb of faces
		int32 i32NumTriangles;
		in >> i32NumTriangles;

		// reserve memory for edges.
		// and neighbours FIXME
		vgd::field::EditorRW< vgd::field::MFUInt>	vertexIndex	= vertexShape->getVertexIndexRW();	
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

			in >> lEdge1 >> lEdge2 >> lEdge3;

			vertexIndex->push_back(lEdge1);
			vertexIndex->push_back(lEdge2);
			vertexIndex->push_back(lEdge3);
		}

		//m_i32NextEdge = vertexIndex->getNum();

		// primitive
		vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = vertexShape->getPrimitiveRW();
		primitive->clear();

		vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() );
		primitive->push_back( prim );
	}

	// ???

	return vertexShape;
}



vgd::Shp< vgd::node::Material > Loader::loadWireColor( std::istream & in, const std::string & nodeName )
{
	// color : already readed.
	// 0.52549 0.431373 0.0313725 0

	std::string	name;
	vgm::Vec3f	color3;
	float		opacity;

	in >> color3[0] >> color3[1] >> color3[2] >> opacity;

	vgd::Shp< vgd::node::Material > material;

	material = vgd::node::Material::create( nodeName );
	material->setAmbient( color3 );
	material->setDiffuse( color3 );
	material->setOpacity( 1.f - opacity );

	return material;
}



vgd::Shp< vgio::ILoader > Loader::clone()
{
	return vgd::makeShp( new Loader() );
}



} // namespace vgTrian
