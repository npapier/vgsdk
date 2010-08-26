// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/VisualSceneImporter.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <vgOpenCOLLADA/importer/Loader.hpp>
#include <vgOpenCOLLADA/importer/Reader.hpp>

#include <COLLADAFWLookAt.h>
#include <COLLADAFWMatrix.h>
#include <COLLADAFWRotate.h>
#include <COLLADAFWTranslate.h>
#include <COLLADAFWTriangles.h>
#include <COLLADAFWScale.h>


#include <vgd/node/MatrixTransform.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/Transform.hpp>
#include <vgd/node/TransformSeparator.hpp>

#include <vgd/visitor/helpers.hpp>
#include <vgd/visitor/predicate/ByRegexName.hpp>
#include <vgd/visitor/predicate/ByType.hpp>
#include <vgm/Matrix.hpp>
#include <vgm/Utilities.hpp>

namespace vgOpenCOLLADA
{

namespace importer
{

VisualSceneImporter::VisualSceneImporter( vgOpenCOLLADA::Settings settings, Reader *reader ) :
m_settings ( settings ),
m_reader( reader ),
m_switchMaterial ( reader->getSwitchMaterial() ),
m_switchVertexShape ( reader->getSwitchVertexShape() ),
m_mapShapeMaterial( reader->getMapShapeMaterial() ),
m_mapMaterial( reader->getMapMaterial() )
{
}

void VisualSceneImporter::createNode(const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode, std::string name)
{
	vgd::Shp< vgd::node::Group > vgsdkSubNode;
	//if current node contain one or more geometrical transformation, we create a TransformSeparator (to prevent from geometry transformation..)
	if( node->getTransformations().getCount() > 0 )
	{
		vgsdkSubNode = vgd::node::TransformSeparator::create(node->getName());
	}
	//else create normal group.
	else
	{
		vgsdkSubNode = vgd::node::Group::create(node->getName());
	}

	vgsdkNode->addChild(vgsdkSubNode);

	//retain parent node name and keep it if current node name is empty
	std::string nodeName;
	if( node->getName() == "" )
	{
		nodeName = name;
	}
	else
	{
		nodeName = node->getName();
	}

	createNodeTransformation(node, vgsdkSubNode);

	createNodeGeometry(node, vgsdkSubNode, nodeName);


	//recurcivity for child node.
	const COLLADAFW::NodePointerArray& childNodes = node->getChildNodes();
	for (std::size_t i = 0; i< childNodes.getCount(); i++) 
	{
		if (childNodes.getData()[i]->getType() == COLLADAFW::Node::NODE)
		{
			createNode(childNodes.getData()[i], vgsdkSubNode, nodeName);
		}
		else
		{
			continue;
		}
	}
}

//@todo problem with complex scene
void VisualSceneImporter::createNodeTransformation( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode )
{
	const COLLADAFW::TransformationPointerArray& transformations = node->getTransformations();
	for (std::size_t i = 0; i < transformations.getCount(); i++ )
	{
		const COLLADAFW::Transformation* transformation = transformations.getData()[i];

		//MATRIX
		if (transformation->getTransformationType() == COLLADAFW::Transformation::MATRIX)
		{

			vgd::Shp< vgd::node::MatrixTransform > t = vgd::node::MatrixTransform::create("matrix");
			const COLLADAFW::Matrix* matrix = static_cast<const COLLADAFW::Matrix* >( transformation );
			vgm::MatrixR m;
			//m.setTranslate( vgm::Vec3f(2,3,4) );

			for (size_t iRow = 0 ;iRow < 4 ; iRow++) 
			{
				for (size_t iCol = 0; iCol < 4; iCol++) 
				{
					m[iRow][iCol] = (float)matrix->getMatrix()[iCol][iRow];
				}
			}

			t->setMatrix(m);

			vgsdkNode->addChild(t);
		}
		//TRANSLATION
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::TRANSLATE)
		{
			vgd::Shp< vgd::node::Transform > t = vgd::node::Transform::create("translate");
			const COLLADAFW::Translate* translate = static_cast<const COLLADAFW::Translate* >( transformation );

			float x = static_cast<float >( translate->getTranslation()[0] );
			float y = static_cast<float >( translate->getTranslation()[1] );
			float z = static_cast<float >( translate->getTranslation()[2] );

			vgm::Vec3f translation = vgm::Vec3f(x, y , z);
			t->setTranslation(translation);

			vgsdkNode->addChild(t);
		}
		//ROTATION
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::ROTATE)
		{
			vgd::Shp< vgd::node::Transform > t = vgd::node::Transform::create("rotate");
			const COLLADAFW::Rotate* rotate = static_cast<const COLLADAFW::Rotate* >( transformation );						

			float x = static_cast<float >( rotate->getRotationAxis()[0] );
			float y = static_cast<float >( rotate->getRotationAxis()[1] );
			float z = static_cast<float >( rotate->getRotationAxis()[2] );

			vgm::Vec3f axis = vgm::Vec3f(x, y , z);

			float angle = static_cast<float >( rotate->getRotationAngle() );
			
			t->setRotation(vgm::Rotation(axis, vgm::Utilities::deg2rad( angle )));

			vgsdkNode->addChild(t);
		}
		//SCALE
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::SCALE)
		{
			vgd::Shp< vgd::node::Transform > t = vgd::node::Transform::create("scale");

			const COLLADAFW::Scale* scale = static_cast<const COLLADAFW::Scale* >( transformation );

			float x = static_cast<float >( scale->getScale()[0] );
			float y = static_cast<float >( scale->getScale()[1] );
			float z = static_cast<float >( scale->getScale()[2] );

			vgm::Vec3f scaleFactor = vgm::Vec3f(x, y , z);

			t->setScaleFactor(scaleFactor);

			vgsdkNode->addChild(t);
		}
		//LOOKAT
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::LOOKAT)
		{
			//@todo: test it.
			vgd::Shp< vgd::node::MatrixTransform > t = vgd::node::MatrixTransform::create("lookat");
			const COLLADAFW::Lookat* lookat = static_cast<const COLLADAFW::Lookat* >( transformation );
			vgm::MatrixR m = vgm::MatrixR();

			vgm::Vec3f eye = vgm::Vec3f((float)lookat->getEyePosition()[0], (float)lookat->getEyePosition()[1], (float)lookat->getEyePosition()[2]);
			
			vgm::Vec3f center = vgm::Vec3f((float)lookat->getInterestPointPosition()[0], (float)lookat->getInterestPointPosition()[1], (float)lookat->getInterestPointPosition()[2]);					
			
			vgm::Vec3f up = vgm::Vec3f((float)lookat->getUpAxisDirection()[0], (float)lookat->getUpAxisDirection()[1], (float)lookat->getUpAxisDirection()[2]);		
			
			m.setLookAt(eye, center, up);

			t->setMatrix(m);

			vgsdkNode->addChild(t);
		}
		//SKEW
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::SKEW)
		{
			assert( false && "Skew is not yet implement." );
		}
		else
		{
			assert( false && "Unexpected value." );
		}
	}
}

void VisualSceneImporter::createNodeGeometry( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode, std::string shapeName )
{	
	const COLLADAFW::InstanceGeometryPointerArray& geometries = node->getInstanceGeometries();
	for (std::size_t i = 0; i < geometries.getCount(); i++ )
	{
		const COLLADAFW::UniqueId& id = geometries.getData()[i]->getInstanciatedObjectId();
		const COLLADAFW::MaterialBindingArray& materialBindingArray = geometries.getData()[i]->getMaterialBindings();
		vgd::Shp< vgd::node::Group > group = vgd::visitor::findFirstByName< vgd::node::Group >(m_switchVertexShape, id.toAscii());

		vgd::visitor::predicate::ByType<vgd::node::VertexShape> predicate;
		vgd::Shp< vgd::node::NodeList > result;
		result = vgd::visitor::find( group, predicate );

		std::list< vgd::Shp < vgd::node::Node > >::iterator it = result->begin();
		for( it; it !=  result->end(); it++ )
		{
			vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >(*it);
			vertexShape->setName( shapeName );
			
			//Create multiple instances if extra tag are present
			const ExtraDataMultiInstance& callbackHandler = m_reader->getLoader()->getExtraDataMultiInstance();
			std::vector< MultiInstanceInfo > extraInfos = callbackHandler.findExtraInfo( shapeName );
			vgd::Shp< vgd::node::MultipleInstances > multipleInstances;
			bool isMultipleInstances = false;
			if( extraInfos.size() > 0 )
			{
				multipleInstances = vgd::node::MultipleInstances::create( shapeName );
				multipleInstances->setShape( vertexShape );
				createMultipleInstances( multipleInstances, extraInfos );
				isMultipleInstances = true;
			}

			vgd::Shp< vgd::node::Group > childNode = vgd::node::Group::create( node->getName() );
			vgsdkNode->addChild( childNode );

			bool hasMaterial = false;

			if ( m_settings.getLevel() > GEOMETRY )
			{
				if( m_mapShapeMaterial->find( vertexShape ) != m_mapShapeMaterial->end() )
				{
					int matId = (*m_mapShapeMaterial)[vertexShape];
					for (std::size_t j = 0; j < materialBindingArray.getCount(); j++)
					{
						if ( materialBindingArray[j].getMaterialId() == matId )
						{						
							const COLLADAFW::MaterialBinding& materialBinding = materialBindingArray[j];
							std::string id = materialBinding.getReferencedMaterial().toAscii();
							
							if( m_mapMaterial->find( id ) != m_mapMaterial->end() )
							{
								hasMaterial = true;
								vgd::Shp< vgd::node::Group > materialGroup = (*m_mapMaterial)[id];
								
								//removes texture coordinate from VertexShape if no texture are present.
								vgd::visitor::predicate::ByType< vgd::node::Texture2D > pred;
								vgd::Shp< vgd::node::NodeList > texturesResult;
								texturesResult = vgd::visitor::find( materialGroup, pred );
								if( texturesResult->size() == 0 )
								{
									for( int i = 0; i < vertexShape->getNumTexUnits(); i++)
									{
										vertexShape->removeTexUnits( i );
									}
								}

								childNode->addChild( materialGroup );
							}
						}
					}
				}
			}
			if( !hasMaterial )
			{
				//removes texture coordinate from VertexShape if no material are present.
				for( int i = 0; i < vertexShape->getNumTexUnits(); i++)
				{
					vertexShape->removeTexUnits( i );
				}
			}

			if( isMultipleInstances )
			{
				childNode->addChild( multipleInstances );
			}
			else
			{
				childNode->addChild( vertexShape );
			}
		}
	}
}



void VisualSceneImporter::createMultipleInstances( vgd::Shp< vgd::node::MultipleInstances > multipleInstances, std::vector< MultiInstanceInfo > extraInfos )
{
	vgd::field::EditorRW< vgd::node::MultipleInstances::FMatrixType > matrixEdit = multipleInstances->getMatrixRW();

	std::vector< MultiInstanceInfo >::iterator extraIter = extraInfos.begin();
	for( extraIter; extraIter != extraInfos.end(); extraIter++)
	{
		std::string strMatrix = extraIter->getMatrix();

		std::vector< std::string > numbers;
		boost::split(numbers, strMatrix, boost::is_any_of(" "));

		std::vector< std::string >::iterator nbrIter = numbers.begin();
		int iCol = 0;
		int iRaw = 0;
		vgm::MatrixR matrix;

		for( nbrIter; nbrIter != numbers.end(); nbrIter++)
		{
			if( (*nbrIter) != "" )
			{
				try
				{
					float number = boost::lexical_cast< float >( (*nbrIter) );
					matrix[iCol][iRaw] = number;
				}
				catch( const boost::bad_lexical_cast & )
				{
					assert(false && "Wrong matrix format");
				}

				if( iCol < 3 )
				{
					iCol++;
				}
				else
				{
					iCol = 0;
					iRaw++;
				}
			}
		}
		matrixEdit->push_back( matrix );
	}
}



} // namespace importer

} // namespace vgOpenCOLLADA