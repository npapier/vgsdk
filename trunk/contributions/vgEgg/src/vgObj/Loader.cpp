// VGSDK - Copyright (C) 2008, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest
// Author Guillaume Brocker

#include "vgObj/Loader.hpp"

#include <fstream>
#include <sstream>

#include <vgd/Shp.hpp>
#include <vgd/basic/FilenameExtractor.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vgio/FileSystem.hpp>
#include <vgio/helpers.hpp>
#include <vgio/LoaderRegistry.hpp>


namespace
{
void computeTrianglesNormals( vgd::field::EditorRO< vgd::field::MFVec3f > &vertices, vgd::field::EditorRO< vgd::field::MFUInt32 > &vertexIndex, vgd::field::EditorRW< vgd::node::VertexShape::FNormalType > &normals, int32 beginIndex, int32 numTris )
{
	vgm::Vec3f faceNormal;
	vgm::Vec3f v1, v2;	

	for( int32 i=0; i < numTris; i++ )
	{
		// compute face normal
		int32 indexA, indexB, indexC;

		indexA = (*vertexIndex)[beginIndex];
		indexB = (*vertexIndex)[beginIndex+1];
		indexC = (*vertexIndex)[beginIndex+2];

		v1 = (*vertices)[indexB] - (*vertices)[indexA];
		v2 = (*vertices)[indexC] - (*vertices)[indexA];
		faceNormal = v1.cross(v2);

		// add this face normal to each vertex normal
		(*normals)[indexA]	+= faceNormal;
		(*normals)[indexB]	+= faceNormal;
		(*normals)[indexC]	+= faceNormal;
		beginIndex += 3;
	}
}


void computeQuadsNormals( vgd::field::EditorRO< vgd::field::MFVec3f > &vertices, vgd::field::EditorRO< vgd::field::MFUInt32 > &vertexIndex, vgd::field::EditorRW< vgd::node::VertexShape::FNormalType > &normals, int32 beginIndex, int32 numQuads )
{
	vgm::Vec3f faceNormal;
	vgm::Vec3f v1, v2;	

	for( int32 i=0; i < numQuads; i++ )
	{
		// compute face normal
		int32 indexA, indexB, indexC, indexD;

		indexA = (*vertexIndex)[beginIndex];
		indexB = (*vertexIndex)[beginIndex+1];
		indexC = (*vertexIndex)[beginIndex+2];
		indexD = (*vertexIndex)[beginIndex+3];

		v1 = (*vertices)[indexB] - (*vertices)[indexA];
		v2 = (*vertices)[indexC] - (*vertices)[indexA];
		faceNormal = v1.cross(v2);

		// add this face normal to each vertex normal
		(*normals)[indexA]	+= faceNormal;
		(*normals)[indexB]	+= faceNormal;
		(*normals)[indexC]	+= faceNormal;
		(*normals)[indexD]	+= faceNormal;
		beginIndex += 4;
	}
}

void computeNormals( vgd::Shp<vgd::node::VertexShape> vertexShape )
{
	vgd::field::EditorRW< vgd::node::VertexShape::FNormalType > normals = vertexShape->getFNormalRW();
	vgd::field::EditorRO< vgd::field::MFVec3f > verticesRO = vertexShape->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 > vertexIndexRO = vertexShape->getFVertexIndexRO();
	vgd::field::EditorRO< vgd::field::MFPrimitive > primitiveRO = vertexShape->getFPrimitiveRO();

	vgm::Vec3f faceNormal;
	vgm::Vec3f v1, v2;

	int32 numVertices;
	numVertices	= verticesRO->size();

	normals->resize( numVertices );
	for ( int j=0; j < numVertices; ++j )
	{
		(*normals)[j].setNull();
	}

	for ( unsigned int i=0; i<primitiveRO->size(); i++ )
	{
		vgd::node::Primitive curPrim = (*primitiveRO)[i];
		int32 beginIndex = curPrim.getIndex();

		if ( curPrim.getType() == vgd::node::Primitive::TRIANGLES )
		{
			int32 numTris = curPrim.getNumIndices() / 3;
			computeTrianglesNormals( verticesRO, vertexIndexRO, normals, beginIndex, numTris );
		}
		else if ( curPrim.getType() == vgd::node::Primitive::QUADS )
		{
			int32 numQuads = curPrim.getNumIndices() / 4;
			computeQuadsNormals( verticesRO, vertexIndexRO, normals, beginIndex, numQuads );
		}
	}
	// normalize normals
	for( int32 i=0; i < numVertices; i++ )
	{
		(*normals)[i].normalize();
	}

	normals.release();

	vertexShape->setNormalBinding( vgd::node::BIND_PER_VERTEX );
}

}



namespace vgObj
{

META_LOADER_CPP( vgObj::Loader, "obj" )



std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string filePath, const bool bCCW ) throw ( std::runtime_error )
{
	return load( vgio::FileSystem(), filePath, bCCW );
}



std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const vgio::Media & media, const std::string & filePath, const bool bCCW )
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
		retVal.first = loadObj( *in, group, bCCW ).first;
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


std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string pathFilename, vgd::Shp< std::vector< char > > buffer, const bool bCCW )
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

	retVal.first = loadObj( in, group, bCCW ).first;

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


std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW )
{
	vgAssertN( false, "Deprecated and no more supported" );
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
	retVal.first = false;

 	return retVal;
}




vgd::Shp< vgio::ILoader > Loader::clone()
{
	return vgd::makeShp( new Loader() );
}



std::pair< bool, vgd::Shp< vgd::node::VertexShape > > Loader::loadObj( std::istream & in, vgd::Shp< vgd::node::Group > group, const bool bCCW )
{


	std::pair< bool, vgd::Shp< vgd::node::VertexShape > >		retVal;


	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::node::VertexShape::create( group->getName() );
	retVal.first	= false;
	retVal.second = vertexShape;

	vgd::field::EditorRW<vgd::node::VertexShape::FVertexType> vertices=vertexShape->getFVertexRW();
	vgd::field::EditorRW<vgd::node::VertexShape::FNormalType> normals=vertexShape->getFNormalRW();
	vgd::field::EditorRW<vgd::field::MFUInt32> vertexIndices =vertexShape->getFVertexIndexRW();


	vgm::Vec3f result;
	unsigned int currentPIndex = 0;
	unsigned int nbFaces = 0;
	enum {
		NONE,
		TRIANGLE,
		QUAD
	} lastPrimitive=NONE, currentPrimitive;

	while (!in.eof())
	{
		std::string line;
		char token, token2;
		std::getline(in,line);
		std::istringstream ls(line);
		ls >> std::noskipws >> token >> token2 >> std::skipws;
		switch (token)
		{
		case '#':
			/* comment */
			break;
		case 'v':
			//nbVertices++;
			/* v, vn, vt */
			switch (token2)
			{
			case ' ':
				/* vertex */
				/* eat up rest of line */
				ls >> result[0] >> result[1] >> result[2];
				vertices->push_back(result);
				break;
			case 'n':
				/* normal */
				/* eat up rest of line */
				ls >> result[0] >> result[1] >> result[2];
				normals->push_back(result);
				break;
			case 't':
				/* texcoord */
				/* eat up rest of line */
				/* eat up rest of line */
				ls >> result[0] >> result[1];
				break;

			default:
				vgLogDebug("vgObj::loadObj : Unknown token %c%s", token, line.c_str() );
				break;
			}
			break;
		case 'm':
			break;
		case 'u':
			break;
		case 'g':
			/* group */
			break;
		case 'l': // for now we consider a line as a 2-vertices face
		case 'f':
			// face

			nbFaces=0;
			while( !ls.eof() )
			{
				int vertex,texture,normal;
				vgm::Vec3i info;
				ls >> vertex;
				if( ls.eof() ) // Protect from ^M end of line characters that confuse previous test
					continue;
				vertex--; // la numérotation débute à 1 dans le .obj
				vertexIndices->push_back(vertex);
				++nbFaces;

				ls >> token2;
				if(token2!='/'){
					ls.unget();
					continue;
				}

				ls >> token2;
				if(token2!='/'){
					ls.unget();
					ls >> texture;
					texture--; // la numérotation débute à 1 dans le .obj
					ls >> token2;
				}
				if(token2!='/'){
					ls.unget();
					continue;
				}
				ls >> normal;
				normal--; // la numérotation débute à 1 dans le .obj
			}
			{
			if(nbFaces==3)
				currentPrimitive = TRIANGLE;
			else if(nbFaces==4)
				currentPrimitive = QUAD;
			else
				currentPrimitive = NONE;
			vgd::field::EditorRW< vgd::field::MFPrimitive > primitive = vertexShape->getFPrimitiveRW();
			if(currentPrimitive==lastPrimitive)
			{
				vgd::node::Primitive& p = *primitive->rbegin();
				p.setNumIndices(p.getNumIndices()+nbFaces);
			}
			else
			{
				if(currentPrimitive==TRIANGLE)
				{
					vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, currentPIndex, 3 );
					primitive->push_back( prim );						
				}
				else if(currentPrimitive==QUAD)
				{
					vgd::node::Primitive prim( vgd::node::Primitive::QUADS, currentPIndex, 4 );
					primitive->push_back( prim );					
				}
			}
			currentPIndex+=nbFaces;
			lastPrimitive = currentPrimitive;
			}
			break;
		default:
			break;
		}
	}

	/*bool emptynormal=*/normals->empty();
	vertices.release();
	normals.release();
	vertexIndices.release();
//	if (emptynormal)
	computeNormals( vertexShape );
	group->addChild( vertexShape );
	retVal.first=true;
	return retVal;
}


} // namespace vgObj
