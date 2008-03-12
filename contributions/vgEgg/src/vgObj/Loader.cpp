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
#include <vgd/node/VertexShape.hpp>
#include <vgDebug/Global.hpp>



namespace vgObj
{



std::pair< bool, vgd::Shp< vgd::node::VertexShape > > Loader::loadObj( const char *pathFilename, bool bCCW )
{


	std::pair< bool, vgd::Shp< vgd::node::VertexShape > >		retVal;


	vgd::basic::FilenameExtractor extractor( pathFilename );
	std::string							epathFilename;
	epathFilename	= extractor.getPathFilename();


	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::node::VertexShape::create( epathFilename );
	retVal.first	= false;
	retVal.second = vertexShape;

	// open file
	std::ifstream fp( pathFilename, std::ios::in);
	//FILE *file;
	//fopen_s(&file, pathFilename, "r");
	if(!fp.good())
	{
		vgDebug::get().logDebug("vgObj::loadObj: Unable to open file %s", pathFilename );
		return ( retVal );
	}
	else
	{
		vgDebug::get().logDebug("vgObj::loadObj: load %s", pathFilename );
	}


	vgd::field::EditorRW<vgd::node::VertexShape::FVertexType> vertices=vertexShape->getFVertexRW();
	vgd::field::EditorRW<vgd::node::VertexShape::FNormalType> normals=vertexShape->getFNormalRW();
	vgd::field::EditorRW<vgd::field::MFUInt32> vertexIndices =vertexShape->getFVertexIndexRW();


	vgm::Vec3f result;

	while (!fp.eof())
	{
		std::string line;
		char token, token2;
		std::getline(fp,line);
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
				vgDebug::get().logDebug("vgObj::loadObj : Unknown token %c%s", token, line );
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

			while(!ls.eof())
			{
				int vertex,texture,normal;
				vgm::Vec3i info;
				ls >> vertex;
				vertex--; // la numérotation débute à 1 dans le .obj
				vertexIndices->push_back(vertex);

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
			break;
		default:
			break;
		}
	}

	vgd::field::EditorRW< vgd::field::MFPrimitive > primitive = vertexShape->getFPrimitiveRW();
	vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndices->size() );
	primitive->push_back( prim );

	bool emptynormal=normals->empty();
	primitive.release();
	vertices.release();
	normals.release();
	vertexIndices.release();
//	if (emptynormal)
		vertexShape->computeNormals();
	retVal.first=true;
	return retVal;
}


} // namespace vgObj
