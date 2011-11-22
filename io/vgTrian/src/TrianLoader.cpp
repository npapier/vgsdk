// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgTrian/TrianLoader.hpp"

#include <sstream>

#include <vgDebug/helpers.hpp>
#include <vgd/basic/FilenameExtractor.hpp>

#include <vgd/node/Group.hpp>
#include <vgd/node/Primitive.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vgio/FileSystem.hpp>
#include <vgio/helpers.hpp>



namespace vgTrian
{



META_LOADER_CPP( vgTrian::TrianLoader, "trian" )



const bool TrianLoader::loadTrian( std::istream & in, vgd::Shp< vgd::node::Group > group, const bool bCCW )
{
	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::node::VertexShape::create( group->getName() );

	// read nb of vertices
	int32 i32NumVertices;
	in >> i32NumVertices;

	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex		= vertexShape->getFVertexRW();
	vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex	= vertexShape->getFVertexIndexRW();

	// setCounterClockWiseFlag( false ); FIXME

	// read vertices
	vertex->clear();
	vertex->reserve(i32NumVertices);

	for (int32 i=0; i<i32NumVertices; i++)
	{
		float x, y, z;
		in >> x >> y >> z;

		vertex->push_back( vgm::Vec3f(x,y,z) );
	}

	// read nb of faces
	int32 i32NumTriangles;
	in >> i32NumTriangles;

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

		in >> lEdge1 >> lEdge2 >> lEdge3;

		vertexIndex->push_back(lEdge1);
		vertexIndex->push_back(lEdge2);
		vertexIndex->push_back(lEdge3);

		// read the three neighbours of triangle
		int32 lNeighbour1;
		int32 lNeighbour2;
		int32 lNeighbour3;

		in >> lNeighbour1 >> lNeighbour2 >> lNeighbour3;

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

			in >> lEdge1 >> lEdge2 >> lEdge3;

			vertexIndex->push_back(lEdge3);
			vertexIndex->push_back(lEdge2);
			vertexIndex->push_back(lEdge1);

			// read the three neighbours of triangle
			int32 lNeighbour1;
			int32 lNeighbour2;
			int32 lNeighbour3;

			in >> lNeighbour1 >> lNeighbour2 >> lNeighbour3;
			//m_vNeighbours.push_back(lNeighbour3);
			//m_vNeighbours.push_back(lNeighbour2);
			//m_vNeighbours.push_back(lNeighbour1);
		}
	}

	//m_i32NextEdge = vertexIndex->getNum();

	// primitive
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = vertexShape->getFPrimitiveRW();
	primitive->clear();

	vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() );
	primitive->push_back( prim );

	vertex.release();
	vertexIndex.release();

	//
	vertexShape->computeNormals();

	group->addChild( vertexShape );

	return true;
}



vgd::Shp< vgd::node::VertexShape > TrianLoader::loadTrian( const std::string& pathFilename, const bool bCCW )
{
	vgd::Shp< vgd::node::VertexShape > retVal;

	std::pair< bool, vgd::Shp< vgd::node::Group > > retValLoading = load( pathFilename, bCCW );

	if ( retValLoading.first )
	{
		retVal = retValLoading.second->getChild< vgd::node::VertexShape >(0);
	}
	// else nothing to do

	return retVal;
}



const bool TrianLoader::saveTrian( vgd::Shp< vgd::node::VertexShape > shape, const std::string& pathFilename, const bool bCCW )
{
	bool retVal = false;

	vgd::basic::FilenameExtractor	extractor( pathFilename );
	std::string						filename;
	std::string						epathFilename;

	std::string path	= extractor.getPath();
	filename			= extractor.getFilename();
	epathFilename		= extractor.getPathFilename();

	// open file
	std::ofstream fp( pathFilename.c_str() );

	if (!fp.good())
	{
		vgLogDebug("vgTrian::saveTrian: Unable to open file %s", pathFilename.c_str() );

		return retVal;
	}
	else
	{
		vgLogDebug("vgTrian::saveTrian: saved %s", pathFilename.c_str() );
	}

	// write nb of vertices
	vgd::field::EditorRO< vgd::field::MFVec3f >	vertex		= shape->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt32>	vertexIndex	= shape->getFVertexIndexRO();
	
	int32 i32NumVertices = vertex->size();
	fp << i32NumVertices << std::endl;


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
	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives = shape->getFPrimitiveRO();
	assert( primitives->size() == 1 );
	vgd::node::Primitive primitive = (*primitives)[0];
	assert( primitive.getType() == vgd::node::Primitive::TRIANGLES );
	assert( primitive.getIndex() == 0 );
	assert( static_cast<uint32>(primitive.getNumIndices()) == vertexIndex->size() );

	//
	retVal = true;

	vgLogDebug("vgTrian::saveTrian: save %s done.", pathFilename.c_str() );
	//vgLogStatus("vgTrian::saveTrian: save %s done.", pathFilename.c_str() );

	return retVal;
}



std::pair< bool, vgd::Shp< vgd::node::Group > > TrianLoader::load( const std::string filePath, const bool bCCW )
{
	return load( vgio::FileSystem(), filePath, bCCW );
}



std::pair< bool, vgd::Shp< vgd::node::Group > > TrianLoader::load( const vgio::Media & media, const std::string & filePath, const bool bCCW )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
	retVal.first = false;

	vgd::Shp< vgd::node::Group > group;

	vgd::basic::FilenameExtractor extractor( filePath.c_str() );
	std::string path			= extractor.getPath();
	std::string filename		= extractor.getFilename();
	std::string epathFilename	= extractor.getPathFilename();

	if ( path.length() == 0 )
	{
		path = ".";
	}

	group = vgd::node::Group::create( epathFilename );
	retVal.second = group;

	// Open file
	vgd::Shp< std::istream > in = media.open( filePath );

	if (!in)
	{
		vgLogDebug("Unable to open file %s", filePath.c_str() );

		return retVal;
	}
	else
	{
		vgLogDebug("load %s", filePath.c_str() );
		retVal.first = loadTrian( *in, group, bCCW );
		if ( retVal.first )
		{
			vgLogDebug("load %s done", filePath.c_str() );
		}
		else
		{
			vgLogDebug("Error during loading %s", filePath.c_str() );
		}
		return retVal;
	}
}



std::pair< bool, vgd::Shp< vgd::node::Group > > TrianLoader::load( const std::string pathFilename, vgd::Shp< std::vector< char > > buffer, const bool bCCW )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
	retVal.first = false;

	vgd::Shp< vgd::node::Group > group = vgd::node::Group::create( pathFilename );
	retVal.second = group;

	std::stringstream in( std::string(buffer->begin(), buffer->end()) );

	vgd::basic::FilenameExtractor extractor( pathFilename.c_str() );
	std::string path = extractor.getPath();

	if ( path.length() == 0 )
	{
		path = ".";
	}

	retVal.first = loadTrian( in, group, bCCW );

	if ( retVal.first )
	{
		vgLogDebug("load %s done", pathFilename.c_str() );
	}
	else
	{
		vgLogDebug("Error during loading %s", pathFilename.c_str() );
	}
	return retVal;
}



std::pair< bool, vgd::Shp< vgd::node::Group > > TrianLoader::load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW )
{
	vgAssertN( false, "Deprecated and no more supported" );
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
	retVal.first = false;

 	return retVal;
}



vgd::Shp< vgio::ILoader > TrianLoader::clone()
{
	return vgd::makeShp( new TrianLoader() );
}



} // namespace vgTrian
