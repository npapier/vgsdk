// VGSDK - Copyright (C) 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgCollada/Reader.hpp"

#include <dom/domConstants.h>
#include <dom/domCOLLADA.h>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgDebug/convenience.hpp>
//#include "vgCollada/detail/DaeSingleton.hpp" @todo

#include "vgCollada/domSourceAdapter.hpp"
#include "vgCollada/operations.hpp"



namespace vgCollada
{



const bool Reader::load( const std::string& fileURI )
{
/*	// Normalizes fileURI
	std::string fURI;

	if ( fileURI[1] == ':' )
	{
		fURI = "/" + fileURI;
	}
	else
	{
		fURI = fileURI;
	}*/

//	// Retrieves dae interface
//	vgd::Shp< DAE > dae = detail::DaeSingleton::getDefault();

	// Creates new dae interface
	if ( m_dae )
	{
		// @todo always good ?
		DAE::cleanup();
	}

	m_dae.reset( new DAE );

	vgd::Shp< DAE >& dae = m_dae;

	// Resets previously loaded scene.
	m_root.reset();

	// Loads file
	const daeInt retVal = dae->load( fileURI.c_str() );

	// Is there any errrors ?
	if ( retVal != DAE_OK )	// @todo DAE_ERR_COLLECTION_ALREADY_EXISTS
	{
		const char *error			= daeErrorString(retVal);
		const std::string strError	= error;

		vgLogDebug3( "vgCollada: Error in load( %s ) : %s ", fileURI.c_str(), strError.c_str() );

		return false;
	}

	// retVal == DAE_OK
	vgLogDebug2( "vgCollada: load( %s ) successfully.", fileURI.c_str() );

	// Creates root of scene graph
	using vgd::node::Group;
	m_root = Group::create(fileURI);

	// @todo traverse the document...
	//domCOLLADA *document = dae->getDom( fileURI.c_str() );

	// Retrieves the geometries
	const uint geometryCount = dae->getDatabase()->getElementCount(NULL, COLLADA_ELEMENT_GEOMETRY, NULL);

	for( uint geometryIndex=0;  geometryIndex != geometryCount;	++geometryIndex )
	{
		daeElement *currentGeometry;

		daeInt error = dae->getDatabase()->getElement(	(daeElement**)&currentGeometry,
														geometryIndex,
														NULL, COLLADA_ELEMENT_GEOMETRY, NULL	);
		assert( error == DAE_OK );
		assert( currentGeometry != 0 );

		if ( currentGeometry )
		{
			domGeometry *geometryElement = (domGeometry*) currentGeometry;
			assert( geometryElement != 0 );

			using vgd::node::VertexShape;
			
			vgd::Shp< VertexShape > vertexShape = processGeometry( geometryElement );
			if ( vertexShape != 0 )
			{
				m_root->addChild( vertexShape );
			}
		}
	}

	return true;
}



vgd::Shp< vgd::node::Group > Reader::getRoot() const
{
	return m_root;
}



vgd::Shp< vgd::node::VertexShape > Reader::processGeometry( domGeometry * geometry )
{
	// Creates returned value
	using vgd::node::VertexShape;
	vgd::Shp< VertexShape > vertexShape;

	// Extracts mesh from geometry
	domMeshRef mesh = geometry->getMesh();

	if ( mesh == 0 )
	{
		// No mesh in Geometry
		vgLogError2("No mesh in %s", geometry->getId() );

		return vertexShape;
	}

	// Processes Mesh

	// Creates vertex shape and sets it name
	vertexShape = VertexShape::create( geometry->getId() );

	// Fills the vertex shape
	fillVertexShape( mesh, vertexShape );

	return vertexShape;
}



void Reader::fillVertexShape( domMesh *mesh, vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	// Repository of sources
	SourceMap sources;

	// For each element, do
	const uint32 count = mesh->getContents().getCount();
	for( uint32 i = 0; i != count; ++i )
	{
		daeElement * element = mesh->getContents()[i];

		// domVertices
		if ( daeSafeCast< domVertices >( element ) )
		{
			continue;
		}

		// domSource
		domSource *source = daeSafeCast< domSource >( element );

		if ( source )
		{
			sources.insert(
				std::make_pair(	source->getId(),
								vgd::makeShp( new domSourceAdapter(source) ) )
							);
			continue;
		}

		// domTriangles
		domTriangles * triangles = daeSafeCast< domTriangles >( element );

		if ( triangles )
		{
			processSinglePPrimitive( triangles, sources, vgd::node::Primitive::TRIANGLES, vertexShape );
			continue;
		}

		vgLogWarning3( "Unsupported primitive type %s in geometry %s\n", mesh->getContents()[i]->getTypeName(), vertexShape->getName().c_str() );
	}
}



template< typename T >
void Reader::processSinglePPrimitive(	T * group, SourceMap& sources,
										const vgd::node::Primitive& primitiveType,
										vgd::Shp< vgd::node::VertexShape > vertexShape )
{
//std::map< uint, std::vector< uint > > indexMap;
//IndexMap index_map;

//	resolveArrays(	group->getInput_array(), sources,
//					indexMap, vertexShape );

	//
	domUint			maxOffset				= 0;

	domVertices	*	vertices				= 0;
	domUint			vertexOffset			= 0;

	domSource	*	normalSource			= 0;
	domUint			normalOffset			= 0;

	domSource	*	textureSource			= 0;
	domUint			textureOffset			= 0;

	// inputs with offset
	domInputLocalOffset_Array& inputsOffset = group->getInput_array();

	for ( size_t i = 0; i < inputsOffset.getCount(); i++ )
	{
		domInputLocalOffsetRef	input		= inputsOffset[i];

		domUint				offset		= input->getOffset();
		std::string			semantic	= input->getSemantic(); // xsNMTOKEN
		domURIFragmentType	source		= input->getSource();
		//domUint				set			= input->getSet();

		// Updates the maximum offset
		maxOffset = std::max( maxOffset, offset );

		//
		if ( semantic == "VERTEX" )
		{
			vertices = getElementFromURI< domVertices >( source );

			if ( vertices == 0 )
			{
				vgLogDebug("vgCollada: Unable to find vertices.");
				return;
			}

			vertexOffset = offset;
		}
		else if ( semantic == "NORMAL" )
		{
			normalSource	= getElementFromURI< domSource >( source );
			normalOffset	= offset;
		}
		else if ( semantic == "TEXCOORD" )
		{
			textureSource	= getElementFromURI< domSource >( source );
			textureOffset	= offset;
		}
		else
		{
			vgLogDebug2("vgCollada: semantic %s not yet supported", semantic.c_str() );
		}
	}

	// inputs without offset (in vertices)
	vgd::Shp< domSourceAdapter> dsaVertex;

	const domInputLocal_Array& inputs = vertices->getInput_array();
	for ( size_t i = 0; i < inputs.getCount(); i++ )
	{
		domInputLocalRef	input		= inputs[i];

		std::string			semantic	= input->getSemantic();
		domURIFragmentType	source		= input->getSource();

		if ( semantic == "POSITION" )
		{
			domSource * positionSource = getElementFromURI< domSource >( source );

			if ( positionSource )
			{
				// Retrieves positions
				SourceMap::const_iterator iter = sources.find( positionSource->getId() );
				if ( iter != sources.end() )
				{
					dsaVertex = iter->second;

					//
					if ( dsaVertex->getArrayType() != domSourceAdapter::VEC3F )
					{
						vgLogDebug("vgCollada: Unexpected array type for vertices.");
						return;
					}
				}
				else
				{
					vgLogDebug("vgCollada: Unable to locate domSourceAdapter for POSITION");
					return;
				}
			}
			else
			{
				vgLogDebug("vgCollada: Unable to find POSITION semantic.");
				return;
			}
		}
		else
		{
			vgLogDebug2("vgCollada: semantic %s not yet supported", semantic.c_str() );
		}
	}

	//
	vgd::Shp< domSourceAdapter> dsaNormal;
	//vgd::Shp< domSourceAdapter> 	dsaTexture;

// @todo a function begin
	// Retrieves dsa for normals
	if ( normalSource )
	{
		SourceMap::const_iterator iter = sources.find( normalSource->getId() );
		if ( iter != sources.end() )
		{
			dsaNormal = iter->second;

			//
			if ( dsaNormal->getArrayType() != domSourceAdapter::VEC3F )
			{
				vgLogDebug("vgCollada: Unexpected array type for normals.");
				return;
			}
		}
		else
		{
			vgLogDebug("vgCollada: Unable to locate domSourceAdapter for NORMAL");
			return;
		}
	}
	else
	{
		vgLogDebug("vgCollada: Unable to find NORMAL semantic.");
		return;
	}
// @todo a function end

	std::vector< vgm::Vec3f >& vertexArray	= dsaVertex->getVec3fArray();
	std::vector< vgm::Vec3f >& normalArray	= dsaNormal->getVec3fArray();
	// @todo std::vector< vgm::Vec3f >& normalArray	= dsaTexture->getVec2fArray();

	// processP
	const uint		primCount	= static_cast<uint>(group->getCount());
	domPRef			prim		= group->getP();
	// @todo group->getMaterial();

	domListOfUInts	pData		= prim->getValue();

	vgd::field::EditorRW< vgd::field::MFVec3f>	vertex		= vertexShape->getVertexRW();
	vgd::field::EditorRW< vgd::field::MFVec3f >	normal		= vertexShape->getNormalRW();
	// @todo tex
	vgd::field::EditorRW< vgd::field::MFUInt>	vertexIndex	= vertexShape->getVertexIndexRW();

	vertex->clear();
	//vertex->resize( primCount * 3 );
	normal->clear();
	//normal->resize( primCount * 3 );

	vertexIndex->clear();
	//vertexIndex->resize( primCount * 3 );

	//typedef std::list< domUint > DatabaseElementType;
	//typedef std::set< DatabaseElementType > DatabaseType;
	//DatabaseType database;
	//std::vector< DatabaseElementType >

	const size_t shift = static_cast< size_t >(maxOffset+1);
	uint currentVertexIndex = 0;
	for ( uint i = 0; i < primCount * 3; ++i )
	{
		// always duplicate
		// const domUint indexVertex = pData[ i*shift + static_cast<size_t>(vertexOffset) ];
		// (*vertex)[i] = vertexArray[ static_cast< size_t >(indexVertex) ];

		// const domUint indexNormal = pData[ i*shift + static_cast<size_t>(normalOffset) ];
		// (*normal)[i] = normalArray[ static_cast< size_t >(indexNormal) ];

		// (*vertexIndex)[i] = i;

		const domUint indexVertex = pData[ i*shift + static_cast<size_t>(vertexOffset) ];
		const domUint indexNormal = pData[ i*shift + static_cast<size_t>(normalOffset) ];

		const vgm::Vec3f v = vertexArray[ static_cast< size_t >(indexVertex) ];
		const vgm::Vec3f n = normalArray[ static_cast< size_t >(indexNormal) ];

		//DatabaseElementType currentElement; // @todo boost::assign
		//currentElement.push_back(indexVertex);
		//currentElement.push_back(indexNormal);

		uint foundIndex = vertex->size();
		for( uint j = 0; j < vertex->size(); ++j )
		{
			bool found = (*vertex)[j] == v;
			if ( !found )	continue;

			found = (*normal)[j] == n;
			if ( !found )	continue;

			if ( found )
			{
				foundIndex = j;
				break;
			}
			// else continue
		}

		if ( foundIndex == vertex->size() )
		{
			// Unable to find the (v,n) tuple in vertex shape
			vertex->push_back( v );
			normal->push_back( n );
			vertexIndex->push_back( currentVertexIndex );
			++currentVertexIndex;
		}
		else
		{
			// the (v,n) tuple in vertex shape found in vertex shape
			vertexIndex->push_back( foundIndex );
		}
	}

	if ( dsaNormal )
	{
		vertexShape->setNormalBinding( vgd::node::BIND_PER_VERTEX );
	}
	//vertexShape->computeNormals();

	// primitive
	vgd::field::EditorRW< vgd::field::MFPrimitive > primitive = vertexShape->getPrimitiveRW();
	//primitive->clear();
	vgd::node::Primitive singlePrimitive( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() ); // @todo removes vgd::node::Primitive::TRIANGLES
	primitive->push_back( singlePrimitive );

	//
	vertex.release();
	normal.release();
	vertexIndex.release();
}

} // namespace vgCollada
