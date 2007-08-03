//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGL_TECHNIQUE_OUTLINING_H
//#define _VGEGL_TECHNIQUE_OUTLINING_H
//
//#include "vgeGL/vgeGL.hpp"
//#include "vgeGL/technique/Technique.hpp"
//
//
//
//namespace vgeGL
//{
//	
//namespace technique
//{
//
//
//
//struct VGEGL_API Outlining : public Technique
//{
//	/**
//	 * @brief Constructor.
//	 * 
//	 * @param diffuseColor	diffuse color of the outline.
//	 * @param width			width of the outline.
//	 * 
//	 * @remarks By default, no nodes are marked to be outlined.
//	 */
//	Outlining( const vgm::Vec3f diffuseColor = vgm::Vec3f( 1.f, 1.f, 1.f ), const float width = 4.f );
//
//	/**
//	 * @brief Overwritten method.
//	 */
//	void apply( vge::engine::Engine *pEngine, vge::visitor::TraverseElementVector* pTraverseElements );
//	
//	/**
//	 * @name Accessors to technique parameters.
//	 */
//	//@{
//
//	/**
//	 * @brief Gets the diffuse color of the outline.
//	 * 
//	 * @return the diffuse color of the outline.
//	 */
//	const vgm::Vec3f&		getDiffuseColor() const	{ return ( m_diffuseColor ); }
//	 
//	/**
//	 * @brief Sets the diffuse color of the outline.
//	 * 
//	 * @param color		the diffuse color of the outline.
//	 */
//	void						setDiffuseColor( const vgm::Vec3f& color )			{ m_diffuseColor = color; }
//
//	/**
//	 * @brief Gets the witdh of the outline.
//	 * 
//	 * @return the witdh of the outline.
//	 */
//	const float&			getWidth() const	{ return (m_width); }
//
//	/**
//	 * @brief Sets the width of the outline.
//	 * 
//	 * @param width		the witdh of the outline.
//	 */
//	void						setWidth( const float width ) { m_width = width; }
//	
//	/**
//	 * @brief Gets/sets the nodes that must be outlined.
//	 * 
//	 * @return the set of nodes that must be outlined.
//	 */
//	vgd::node::PNodeSet&	getNodes() 		{ return ( m_nodes ); }
//
//	//@}
//	
//	
//	
//private:
//
//	vgm::Vec3f											m_diffuseColor;
//	float													m_width;
//	vgd::node::PNodeSet								m_nodes;
//};
//
//
//
//} // namespace technique
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGL_TECHNIQUE_OUTLINING_H
