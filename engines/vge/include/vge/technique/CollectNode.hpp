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



/**
 * @brief Store shape informations while collecting nodes.
 */
struct VGE_API CollectedShape
{
	CollectedShape(	vgd::Shp< vgd::node::VertexShape > shape, vgm::MatrixR geometricalMatrix );

	~CollectedShape();
	vgd::Shp< vgd::node::VertexShape >				getShape();
	std::string										getColladaShapeName();
	void											setColladaShapeName( std::string colladaShapeName );

	vgm::MatrixR									getGeometricalMatrix();

private:
	vgd::Shp< vgd::node::VertexShape >				m_shape;
	std::string										m_colladaShapeName;
	vgm::MatrixR									m_geometricalMatrix;
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
	vgd::Shp< vgd::node::Material >		m_material;
	vgd::Shp< vgd::node::Texture2D >	m_texture;

	std::string							m_effectId;
	std::string							m_materialId;
	std::string							m_materialSymbol;
	std::string							m_imageId;
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

	VGE_API std::list< vgd::Shp< vge::technique::CollectedShape > > getCollectedShapeList();

	VGE_API collectedMapType getCollectedMap();

private:
	void addShape( vgd::Shp< vgd::node::VertexShape > shape, vgm::MatrixR matrix, vge::engine::Engine * engine );

	std::list< vgd::Shp< vge::technique::CollectedShape > > m_collectedShapeList;

	collectedMapType	m_collectedMap;

};



} // namespace technique

} // namespace vge

#endif //#ifndef _VGE_TECHNIQUE_COLLECTNODE_HPP
