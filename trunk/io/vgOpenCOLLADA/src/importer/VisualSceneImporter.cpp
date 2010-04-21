// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/VisualSceneImporter.hpp"

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

VisualSceneImporter::VisualSceneImporter( LOAD_TYPE loadType, vgd::Shp< vgd::node::Switch > switchMaterial, vgd::Shp< vgd::node::Switch > switchVertexShape ) :
m_loadType ( loadType ),
m_switchMaterial ( switchMaterial ),
m_switchVertexShape ( switchVertexShape )
{
}

void VisualSceneImporter::createNode(const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode, std::string name)
{
	vgd::Shp< vgd::node::Group > vgsdkSubNode;
	//if direct child of the rootnode, we create a TransformSeparator (to prevent from geometry transformation..)
	//@todo optimize it, don't put transformSeparator if not needed
	if(true /*vgsdkNode == m_group*/)
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

		}
	}
}

void VisualSceneImporter::createNodeGeometry( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode, std::string shapeName )
{	
	const COLLADAFW::InstanceGeometryPointerArray& geometries = node->getInstanceGeometries();
	for (std::size_t i = 0; i < geometries.getCount(); i++ )
	{
		const COLLADAFW::UniqueId& id = geometries.getData()[i]->getInstanciatedObjectId();

		//add each material before adding geometry coresponding geometry.
		//@todo check if every vertexshape are instanciate ==> every vertexhshape got 1 material : not true.
		const COLLADAFW::MaterialBindingArray& materialBindingArray = geometries.getData()[i]->getMaterialBindings();
		vgd::Shp< vgd::node::Group > group = vgd::visitor::findFirstByName< vgd::node::Group >(m_switchVertexShape, id.toAscii());

		//for each instanciate material, we search the coresponding vertexshape.
		for (std::size_t j = 0; j < materialBindingArray.getCount(); j++)
		{				
			vgd::Shp< vgd::node::Group > childNode = vgd::node::Group::create( node->getName() );
			vgsdkNode->addChild( childNode );

			const COLLADAFW::MaterialBinding& materialBinding = materialBindingArray[j];
			//search material.
			int matId = materialBinding.getMaterialId();
			int classId = materialBinding.getReferencedMaterial().getClassId();
			int objectId = (int)materialBinding.getReferencedMaterial().getObjectId();
			vgd::Shp< vgd::node::Group > material;
			if ( m_loadType > LOAD_GEOMETRY )
			{
				std::stringstream ss;
				ss << "mat:UniqueID\\(" << classId << "," << objectId << "\\)" << ".*";
				std::string regex = ss.str();

				vgd::visitor::predicate::ByRegexName predicate(regex);
				material = vgd::visitor::findFirst< vgd::node::Group >( m_switchMaterial, predicate );
				childNode->addChild( material );
			}
			
			//search coresponding vertexshape (matID = vertexshape name).
			std::stringstream ss2;
			ss2 << matId;
			std::string name = ss2.str();
			vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::visitor::findFirstByName< vgd::node::VertexShape >(group, name);
			vertexShape->setName( shapeName );

			//check if vertexshape contains texture coordinates and no texture are binded to it.
			//if yes, removes texture coordinates.
			if ( m_loadType > LOAD_GEOMETRY )
			{
				vgd::visitor::predicate::ByType< vgd::node::Texture2D > type;
				if( !vgd::visitor::findFirst< vgd::node::Texture2D >( material, type ) )
				{
					if( vertexShape->hasFTexCoord(0) )
					{
						vertexShape->setTexCoordBinding(0, vgd::node::BIND_OFF);
						vertexShape->removeTexUnits(0);
					}
				}
			}
			else
			{
				if( vertexShape->hasFTexCoord(0) )
				{
					vertexShape->setTexCoordBinding(0, vgd::node::BIND_OFF);
					vertexShape->removeTexUnits(0);
				}
			}
			childNode->addChild( vertexShape );
		}
	}
}


} // namespace importer

} // namespace vgOpenCOLLADA