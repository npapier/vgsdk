// VGSDK - Copyright (C) 2004, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_BASIC_HIT_HPP
#define _VGEGL_BASIC_HIT_HPP

#include <list>
#include <vgd/node/Node.hpp>
#include <vgm/Vector.hpp>
#include <vgm/Matrix.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace basic
{



/**
 * @brief Abstraction of an element in the OpenGL picking buffer.
 *
 * @ingroup g_rayCasting
 */
struct VGEGL_API Hit
{
	/**
	 * @brief Default constructor
	 */
	Hit();

	/**
	 * @brief Accessors to hit buffer
	 */
	//@{

	/**
	 * @brief The minimum depth value
	 *
	 * @return depth value
	 */
	const float&	minDepthValue() const;

	/**
	 * @brief The minimum depth value
	 *
	 * @return depth value
	 */
	float&			minDepthValue();

	/**
	 * @brief The maximum depth value
	 *
	 * @return depth value
	 */
	const float&	maxDepthValue() const;

	/**
	 * @brief The maximum depth value
	 *
	 * @return depth value
	 */
	float&			maxDepthValue();

	/**
	 * @brief The stack name.
	 * 
	 * The first element is the bottom most.
	 * 
	 * @return the stack name.
	 */
	const std::list< GLuint >&	stackName() const;

	/**
	 * @brief The stack name.
	 * 
	 * The first element is the bottom most.
	 * 
	 * @return the stack name.
	 */
	std::list< GLuint >&	stackName();
	//@}



	/**
	 * @name Accessors to extended hit buffer informations.
	 */
	//@{

	/**
	 * @brief Nearest vertex (i.e. at the minimum depth).
	 *
	 * @return nearest vertex.
	 */
	const vgm::Vec3f& nearestVertex() const;

	/**
	 * @brief Nearest vertex in object space (i.e. at the minimum depth).
	 *
	 * @return nearest vertex.
	 */
	const vgm::Vec3f& nearestVertexO() const;

	/**
	 * @brief Nearest vertex in scene space (i.e. at the minimum depth).
	 *
	 * @return nearest vertex.
	 */
	const vgm::Vec3f& nearestVertexS() const;

	/**
	 * @brief Nearest vertex (i.e. at the minimum depth).
	 *
	 * @return nearest vertex.
	 */
	vgm::Vec3f& nearestVertex();

	/**
	 * @brief Nearest vertex in object space (i.e. at the minimum depth).
	 *
	 * @return nearest vertex.
	 */
	vgm::Vec3f& nearestVertexO();

	/**
	 * @brief Nearest vertex in scene space (i.e. at the minimum depth).
	 *
	 * @return nearest vertex.
	 */
	vgm::Vec3f& nearestVertexS();

	/**
	 * @brief Farthest vertex (i.e. at the minimum depth).
	 *
	 * @return farthest vertex.
	 */
	const vgm::Vec3f& farthestVertex() const;

	/**
	 * @brief Farthest vertex (i.e. at the minimum depth).
	 *
	 * @return farthest vertex.
	 */
	vgm::Vec3f& farthestVertex();


	const vgm::MatrixR& modelviewO() const			{ return m_modelviewO; }
	vgm::MatrixR& modelviewO()						{ return m_modelviewO; }

	const vgm::MatrixR& modelviewS() const			{ return m_modelviewS; }
	vgm::MatrixR& modelviewS()						{ return m_modelviewS; }

	/**
	 * @brief The stack of node.
	 * 
	 * First element is the bottom most.
	 */
	const vgd::node::PNodeList&	stackNode() const;

	/**
	 * @brief The stack of node.
	 * 
	 * First element is the bottom most.
	 */
	vgd::node::PNodeList&			stackNode();
	//@}



private:
	/**
	 * @name Data
	 */
	//@{
	float   m_fMinDepthValue;
	float   m_fMaxDepthValue;

	std::list< GLuint > m_listStackName;
	//@}
	
	/**
	 * @name Extended data.
	 */
	//@{

	vgm::MatrixR m_modelviewO;
	vgm::MatrixR m_modelviewS;

	vgm::Vec3f m_vec3fMin;
	vgm::Vec3f m_vec3fMinO;
	vgm::Vec3f m_vec3fMinS;
	vgm::Vec3f m_vec3fMax;

	vgd::node::PNodeList	m_listStackNode;
	//@}
};

/**
 * @brief A list of hit.
 */
typedef std::list< Hit > HitList;



} // namespace basic

} // namespace vgeGL

#endif //#ifndef _VGEGL_BASIC_HIT_HPP
