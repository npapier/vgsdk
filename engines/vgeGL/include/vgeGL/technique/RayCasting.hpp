// VGSDK - Copyright (C) 2004, 2007, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_RAYCASTING_HPP
#define _VGEGL_TECHNIQUE_RAYCASTING_HPP

#include <set>
#include "vgeGL/basic/Hit.hpp"
#include "vgeGL/technique/Technique.hpp"

namespace vgd { namespace node { struct Shape; } }



namespace vgeGL
{

namespace technique
{


/**
 * @brief Cast a ray in the scene
 * 
 * The RayCasting technique does ray intersection with scene graphs.
 * It can be used to pass arbitrary rays through the scene for intersection detections or to cast ray under the mouse
 * pointer by using the castRay() method.
 * 
 * @remarks RayCasting could be used on Kit, but on nested Kit ?
 * 
 * @todo m_pSelectBuffer = new GLuint[4*1024]; => 1024*4 is an arbitrary buffer size.
 *
 * @ingroup g_techniques_vgeGL
 * @ingroup g_techniques
 *
 * @ingroup g_rayCasting
 */
struct VGEGL_API RayCasting : public Technique
{
	/**
	 * @name Constructor/Destructor
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	RayCasting();
	
	/**
	 * @brief Destructor.
	 */
	~RayCasting();
	
	/**
	 * @brief Release all resources.
	 * 
	 * Called by the destructor.
	 */
	void destroy();
	//@}



	/**
	 * @name Exclusion list accessors
	 */
	//@{

	/**
	 * @brief Adds a node to the exclusion list
	 *
	 * All nodes in the exclusion list are ignored by the ray casting technique.
	 * The list is cleared after each ray casting.
	 */
	void addToExclusionList( vgd::node::Shape * node );

	//@}


	/**
	 * @name Methods to cast ray
	 */
	//@{

	/**
	 * @brief Cast a ray under mouse pointer
	 * 
	 * @param engine					engine used to evaluate scene graph
	 * @param traverseElements			element of the scene graph to evaluate
	 * @param x							x-coordinate of the mouse pointer
	 * @param y							y-coordinate of the mouse pointer
	 */
	void apply(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements,
				const int32 x, const int32 y );

	/**
	 * @brief Cast a ray in the scene
	 * 
	 * @param engine					engine used to evaluate scene graph
	 * @param traverseElements			element of the scene graph to evaluate
	 * @param raySourceW				starting point of the ray (in world space)
	 * @param rayDirectionW				direction of the ray (in world space)
	 */
	void apply(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements,
				const vgm::Vec3f raySourceW, const vgm::Vec3f rayDirectionW );
	//@}



	/**
	 * @name Accessor to the result of raycasting
	 */
	//@{

	/**
	 * @brief Returns the number of hits.
	 * 
	 * @return the number of hits.
	 */
	const uint32 getHitsSize() const;
	
	/**
	 * @brief Returns the hits.
	 * 
	 * @pre getHitsSize() != 0
	 * 
	 * @return the hits.
	 */
	const vgd::Shp< vgeGL::basic::HitList >	getHits() const;

	/**
	 * @brief Returns the nearest hit.
	 * 
	 * @pre getHitsSize() != 0
	 * 
	 * @return the hit.
	 */
	const vgeGL::basic::Hit&	getNearestHit() const;
	
	/**
	 * @brief Returns the farthest hit.
	 * 
	 * @pre getHitsSize() != 0
	 * 
	 * @return the hit.
	 */
	const vgeGL::basic::Hit&	getFarthestHit() const;

	/**
	 * @brief Returns the first node from the nearest hit.
	 * 
	 * @return a reference to the node or 0 no hit have been generated.
	 */
	vgd::node::Node*	getNearestHitNode() const;

	//@}



protected:
	void apply( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements );

	/**
	 * @brief Copy constructor.
	 */
	RayCasting( const RayCasting& ) { assert( false && "No copy constructor" ); }
	
	/**
	 * @brief Fill the list of hits with informations from picking.
	 */
	void fillHits( const uint32 gluintHitsSize );
	
	/**
	 * @brief Returns reference to a node from the picking name.
	 * 
	 * @pre pickingName < m_shapes->size().
	 */
	vgd::node::Node*	searchNodeFromPickingName( const uint32 pickingName ) const;



	/**
	 * @name Ray casting data
	 */
	//@{

	std::set< vgd::node::Shape * > m_exclusionList;

	int32		m_x;
	int32		m_y;

	vgm::Vec3f m_raySourceW;
	vgm::Vec3f m_rayDirectionW;

	GLuint*	m_pSelectBuffer;

	vgm::MatrixR	m_modelview;
	vgm::MatrixR	m_projection;
	vgm::Vec4i		m_viewport;

	struct ShapeInformations
	{
		ShapeInformations( vgd::node::Node * lshape = 0, const vgm::MatrixR lmodelview = vgm::MatrixR::getInvalid() )
		:	shape		( lshape			),
			modelview	( lmodelview	)
		{}

		vgd::node::Node *	shape;
		vgm::MatrixR		modelview;
	};

	typedef std::vector< ShapeInformations > ShapeInformationsContainer;
	ShapeInformationsContainer				m_shapes;

	vgd::Shp< vgeGL::basic::HitList >		m_pHits;

	vgeGL::basic::HitList::const_iterator	m_iterNearestHit;
	vgeGL::basic::HitList::const_iterator	m_iterFarthestHit;

	//@}
	
	static const uint32 m_selectBufferSize;
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_RAYCASTING_HPP
