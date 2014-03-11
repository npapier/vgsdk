// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGSDKTESTGTK_VGTEST_PERFORMANCE_HPP
#define _VGSDKTESTGTK_VGTEST_PERFORMANCE_HPP

#include <vector>

#include <vgd/node/VertexShape.hpp>

namespace vgsdkTestGtk
{

namespace vgTest
{

/**
 * @brief Container for different performance test param
 */
struct Performance
{
	/**
	 * @name Constructors
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	Performance();


	/**
	 * @brief Constructor
	 */
	Performance(const int l, const vgd::node::VertexShape::DeformableHintValueType d, const vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType b);
	//@}


	/**
	 * @brief return the level.
	 */
	const int														getLevel() const;

	/**
	 * @brief return the deformable hint value
	 */
	const vgd::node::VertexShape::DeformableHintValueType			getDeformableHint() const;

	/**
	 * @brief return boundingbox update policy value
	 */
	const vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType	getBoundingBox() const;

	/**
	 * @brief return the deformable hint value as a string
	 */
	const std::string												getDeformableHintToString() const;

	/**
	 * @brief return boundingbox update policy value as a string
	 */
	const std::string												getBoundingBoxToString() const;

private :
	int															m_level;
	vgd::node::VertexShape::DeformableHintValueType				m_deformableHint;
	vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType	m_boundingBox;
};

} //namespace vgTest

} //namespace vgsdkTestGtk

#endif // #ifndef _VGSDKTESTGTK_VGTEST_PERFORMANCE_HPP