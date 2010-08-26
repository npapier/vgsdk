// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_TPRIMITIVEIMPORTER_HPP
#define _VGOPENCOLLADA_IMPORTER_TPRIMITIVEIMPORTER_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <boost/unordered_map.hpp>  

#include <vgOpenCOLLADA/Settings.hpp>
#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <COLLADAFWMeshPrimitive.h>
#include <COLLADAFWMesh.h>

#include <COLLADAFWPolygons.h>

namespace vgOpenCOLLADA
{

namespace importer
{

/**
 * @brief	The COLLADA primitive importer base.
 *			Works only for PrimitiveType == triangle ATM.
 *			Import triangle primitives. Each mesh/primitive (<triangles> tag) is a vertexShape.
 */
template< typename PrimitiveType >
struct VGOPENCOLLADA_API TPrimitiveImporter
{

	TPrimitiveImporter( std::vector< vgm::Vec3f > positions, std::vector< vgm::Vec3f > normals,
		std::vector< std::vector< vgm::Vec2f > > texCoords, vgOpenCOLLADA::Settings settings,
		vgd::Shp< boost::unordered_map< vgd::Shp< vgd::node::VertexShape >, int > > mapShapeMaterial,
		vgd::Shp< vgd::node::Group > group, const COLLADAFW::MeshPrimitive* meshPrimitive ) :
	m_positions( positions ),
	m_normals( normals ),
	m_texCoords( texCoords ),
	m_settings( settings ),
	m_mapShapeMaterial( mapShapeMaterial ),
	m_group( group ),
	m_primitives( (const PrimitiveType*) meshPrimitive ),
	m_positionIndices( m_primitives->getPositionIndices() ),
	m_normalIndices( m_primitives->getNormalIndices() )
	{
	}



	/**
	* @brief Import mesh primitives.
	*/
	virtual void importMeshPrimitives()
	{
		initialize();
		
		//hashmap used to check if the vertex/normal/texCoord set doesn't exists yet.
		m_hashmap.clear();
		for ( size_t j = 0; j < m_primitivesNumber; j++ )
		{
			processPrimitive( j );
		}

		vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, m_editVertexIndex->size() );
		m_editPrimitive->push_back( prim );

		if ( m_vertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX )
		{
			m_vertexShape->computeNormals();
		}

		m_group->addChild( m_vertexShape );

	}


	/**
	* @brief Initialize all class variable.
	*/
	void initialize()
	{
		//check if mesh has texture coordinates.
		m_hasTextCoords = false;
		if( m_primitives->hasUVCoordIndices() && m_texCoords.size() > 0 && m_settings.getLevel() == TEXTURE)
		{
			m_hasTextCoords = true;
		}

		m_primitivesNumber = m_positionIndices.getCount();

		m_vertexShape = vgd::node::VertexShape::create( "" ); //name is assigned during instanciation.

		(*m_mapShapeMaterial)[m_vertexShape] = m_primitives->getMaterialId();

		m_editVertexIndex = m_vertexShape->getFVertexIndexRW();

		m_editPositions = m_vertexShape->getFVertexRW();
		m_editPositions->clear();
		m_editPositions->reserve( m_primitivesNumber );

		m_editNormals = m_vertexShape->getFNormalRW();
		m_editNormals->clear();
		m_editNormals->reserve( m_primitivesNumber );
		m_vertexShape->setNormalBinding( vgd::node::BIND_PER_VERTEX );

		if ( m_hasTextCoords )
		{
			for( int i = 0; i < m_texCoords.size(); ++i )
			{
				m_vertexShape->createTexUnits( 2, i, 1 );
				m_vertexShape->setTexCoordBinding( i, vgd::node::BIND_PER_VERTEX );
				m_editTextCoords.push_back( m_vertexShape->getFTexCoordRW<vgd::field::MFVec2f>( i ) );
				m_editTextCoords[i]->clear();
				m_editTextCoords[i]->reserve( m_primitivesNumber );
			}
		}

		m_editPrimitive = m_vertexShape->getFPrimitiveRW();
		m_editPrimitive->clear();
	}


	/**
	* @brief The procedure of the loop, called for each primitives.
	*/
	void processPrimitive( int j )
	{
		std::vector<float> hash_me;

		hash_me.push_back( m_positions[ m_positionIndices[j] ][0] );
		hash_me.push_back( m_positions[ m_positionIndices[j] ][1] );
		hash_me.push_back( m_positions[ m_positionIndices[j] ][2] );

		hash_me.push_back( m_normals[ m_normalIndices[j] ][0] );
		hash_me.push_back( m_normals[ m_normalIndices[j] ][1] );
		hash_me.push_back( m_normals[ m_normalIndices[j] ][2] );

		if ( m_hasTextCoords )
		{
			for( int i = 0; i < m_texCoords.size(); ++i)
			{
				hash_me.push_back( m_texCoords[i][ m_primitives->getUVCoordIndicesArray()[i]->getIndices()[j] ][0] );
				hash_me.push_back( m_texCoords[i][ m_primitives->getUVCoordIndicesArray()[i]->getIndices()[j] ][1] );
				hash_me.push_back( m_texCoords[i][ m_primitives->getUVCoordIndicesArray()[i]->getIndices()[j] ][2] );
			}			

		}


		//create hash with vecotr of each coordinate.
		std::size_t hash = boost::hash_range(hash_me.begin(), hash_me.end());

		//if hash exist, adds index of existing set to vertex index.
		if( m_hashmap.find(hash) != m_hashmap.end() )
		{
			m_editVertexIndex->push_back( m_hashmap[hash] );
		}
		else
		{
			//adds all.
			m_editPositions->push_back( m_positions[ m_positionIndices[j] ] );
			m_editNormals->push_back( m_normals[ m_normalIndices[j] ] );

			if ( m_hasTextCoords )
			{
				for( int i = 0; i < m_texCoords.size(); ++i)
				{
					m_editTextCoords[i]->push_back( m_texCoords[i][ m_primitives->getUVCoordIndicesArray()[i]->getIndices()[j] ] );
				}
			}
			
			m_editVertexIndex->push_back( m_editPositions->size()-1 );

			m_hashmap[hash] = m_editPositions->size()-1;
		}
	}

protected:
	std::vector< vgm::Vec3f >						m_positions;
	std::vector< vgm::Vec3f >						m_normals;
	std::vector< std::vector< vgm::Vec2f > >		m_texCoords;
	vgOpenCOLLADA::Settings							m_settings;

	const PrimitiveType*							m_primitives;
	const COLLADAFW::UIntValuesArray&				m_positionIndices;
	const COLLADAFW::UIntValuesArray&				m_normalIndices;
	bool											m_hasTextCoords;
	int												m_primitivesNumber;
	vgd::Shp< vgd::node::VertexShape >				m_vertexShape;
	vgd::field::EditorRW< vgd::field::MFUInt32 >	m_editVertexIndex;
	vgd::field::EditorRW< vgd::field::MFVec3f >		m_editPositions;
	vgd::field::EditorRW< vgd::field::MFVec3f >		m_editNormals;
	std::vector< vgd::field::EditorRW< vgd::field::MFVec2f > >		m_editTextCoords;
	vgd::field::EditorRW< vgd::field::MFPrimitive >	m_editPrimitive;

	boost::unordered_map<std::size_t, int>			m_hashmap;

	vgd::Shp< boost::unordered_map< vgd::Shp< vgd::node::VertexShape >, int > > m_mapShapeMaterial;

	vgd::Shp< vgd::node::Group > m_group;

};


/**
* @brief Import polylist primitives. Each primitives (<polylist> tag) is a vertexShape.
*/
struct VGOPENCOLLADA_API PrimitivePolygonsImporter : TPrimitiveImporter< COLLADAFW::Polygons >
{

	PrimitivePolygonsImporter( std::vector< vgm::Vec3f > positions, std::vector< vgm::Vec3f > normals,
		std::vector< std::vector< vgm::Vec2f > > texCoords, vgOpenCOLLADA::Settings settings,
		vgd::Shp< boost::unordered_map< vgd::Shp< vgd::node::VertexShape >, int > > mapShapeMaterial,
		vgd::Shp< vgd::node::Group > group, const COLLADAFW::MeshPrimitive* meshPrimitive ) :
	TPrimitiveImporter( positions, normals, texCoords, settings, mapShapeMaterial, group, meshPrimitive )
	{
	}


	/**
	* @brief Import mesh primitives (specialized for polylist type).
	*/
	virtual void importMeshPrimitives()
	{
		initialize();
		
		//hashmap used to check if the vertex/normal/texCoord set doesn't exists yet.
		m_hashmap.clear();
		const COLLADAFW::IntValuesArray& faceVertexCountArray = m_primitives->getGroupedVerticesVertexCountArray();
		int indexCount = 0; //number of polygons parsed
		int faceCount = 0; //current index of faceVertexCountArray
		int lastFaceNumber = faceVertexCountArray[0]; //number of face of the last polygon

		for ( size_t j = 0; j < m_primitivesNumber; j++ )
		{
			processPrimitive( j );

			indexCount++;
			if( indexCount % lastFaceNumber == 0 )
			{
				faceCount++;
				if( lastFaceNumber != faceVertexCountArray[faceCount] || j == m_primitivesNumber-1 )
				{
					switch( lastFaceNumber )
					{
						case 3:
							m_editPrimitive->push_back( vgd::node::Primitive( vgd::node::Primitive::TRIANGLES, m_editVertexIndex->size() - indexCount, indexCount ) );
							break;
						case 4:
							m_editPrimitive->push_back( vgd::node::Primitive( vgd::node::Primitive::QUADS, m_editVertexIndex->size() - indexCount, indexCount ) );
							break;
						default:
							//editPrimitive->push_back( vgd::node::Primitive prim( vgd::node::Primitive::POLYGON, editVertexIndex->size() - indexCount, indexCount ) );
							throw std::runtime_error("Polygons with more than 4 faces are not supported.");
							break;
					}

					indexCount = 0;
					lastFaceNumber = faceVertexCountArray[faceCount];
				}
				else
				{
					//do nothing, same number of face.
					//add next polygon.
				}
			}
		}

		if ( m_vertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX )
		{
			m_vertexShape->computeNormals();
		}

		m_group->addChild( m_vertexShape );

	}

};
} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_TPRIMITIVEIMPORTER_HPP
