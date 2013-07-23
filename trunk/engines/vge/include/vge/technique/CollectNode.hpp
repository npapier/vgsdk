// VGSDK - Copyright (C) 2010, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGE_TECHNIQUE_COLLECTNODE_HPP
#define _VGE_TECHNIQUE_COLLECTNODE_HPP

#include <boost/bimap.hpp>

#include <vgd/node/Material.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/VertexShape.hpp>

#include "vge/technique/Technique.hpp"


namespace vge
{

namespace technique
{

enum SHAPE_TYPE
{
	VERTEXSHAPE,
	MULTIPLEINSTANCES
};

/**
 * @brief Store shape informations while collecting nodes.
 */
struct VGE_API CollectedShape
{
	CollectedShape(	vgd::Shp< vgd::node::Shape > shape, vgm::MatrixR geometricalMatrix, SHAPE_TYPE shapeType );

	~CollectedShape();
	vgd::Shp< vgd::node::Shape >					getShape();
	SHAPE_TYPE										getShapeType();

	std::string										getColladaShapeName();
	void											setColladaShapeName( std::string colladaShapeName );

	vgm::MatrixR									getGeometricalMatrix();

private:
	vgd::Shp< vgd::node::Shape >					m_shape;				///< Shape to export.
	SHAPE_TYPE										m_shapeType;				///< Type of the shape.
	std::string										m_colladaShapeName;		///< COLLADA id of the shape in library_geometry.
	vgm::MatrixR									m_geometricalMatrix;	///< Geometrical marix applied on the shape.
};



/**
 * @brief Store material/Texture informations while collecting nodes.
 */
struct VGE_API CollectedMaterial
{

	CollectedMaterial( vgd::Shp< vgd::node::Material > material, vgd::Shp< vgd::node::Texture2D > texture );

	~CollectedMaterial();

	vgd::Shp< vgd::node::Material >		getMaterial();
	vgd::Shp< vgd::node::Texture2D >	getTexture();

	void								setEffectId( std::string name );
	void								setMaterialId( std::string name );
	void								setMaterialSymbol( std::string name );
	void								setImageId( std::string name );

	std::string							getEffectId();
	std::string							getMaterialId();
	std::string							getMaterialSymbol();
	std::string							getImageId();

private:
	vgd::Shp< vgd::node::Material >		m_material;			///< vgSDK material to export.
	vgd::Shp< vgd::node::Texture2D >	m_texture;			///< vgSDK texture to export.

	std::string							m_effectId;			///< COLLADA id of the effect in library_geometry.
	std::string							m_materialId;		///< COLLADA id of the material in library_material.
	std::string							m_materialSymbol;	///< COLLADA symbol of the material of a shape in library_geometry.
	std::string							m_imageId;			///< COLLADA id of the image in library_image.
};



typedef boost::bimap< vgd::Shp< vge::technique::CollectedShape >, vgd::Shp< vge::technique::CollectedMaterial > > collectedMapType;

/**
 * @brief	CollectNode Technique.
 * 			Collect all shapes and its geometrical transformation, material, texture and stock it in a CollectedShape.
 *
 * @ingroup g_techniques_vge
 * @ingroup g_techniques
 */
struct CollectNode : public Technique
{
	VGE_API virtual void apply(	vge::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements );

	/**
	 * @brief Return the map containing all shape and material to export.
	 *
	 * @return the map
	 */
	VGE_API collectedMapType getCollectedMap();

private:
	/**
	 * @brief Adds shape and its collected material/texture to the map.
	 *
	 * @param shape		the shape to export
	 *
	 * @param matrix	geometrical matrix applied on the shape
	 *
	 * @param engine	current engine
	 *
	 * @param shapeType	the type of shape we want to create
	 */	
	void addShape( vgd::Shp< vgd::node::Shape > shape, vgm::MatrixR matrix, vge::engine::Engine * engine, SHAPE_TYPE shapeType );

	collectedMapType		m_collectedMap;	///< COLLADA id of the image in library_image.

	std::set< std::string >	m_matNameList;
	std::set< std::string >	m_texNameList;

};



} // namespace technique

} // namespace vge

#endif //#ifndef _VGE_TECHNIQUE_COLLECTNODE_HPP
