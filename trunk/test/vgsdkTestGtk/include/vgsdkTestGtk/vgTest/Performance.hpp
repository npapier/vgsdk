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
		Performance(int l, vgd::node::VertexShape::DeformableHintValueType d, vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType b);
		//@}


		/**
		 * @brief return the level.
		 */
		int															getLevel();

		/**
		 * @brief return the deformable hint value
		 */
		vgd::node::VertexShape::DeformableHintValueType				getDeformableHint();

		/**
		 * @brief return boundingbox update policy value
		 */
		vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType	getBoundingBox();

		/**
		 * @brief return the deformable hint value as a string
		 */
		std::string													getDeformableHintToString();

		/**
		 * @brief return boundingbox update policy value as a string
		 */
		std::string													getBoundingBoxToString();

	private :
		int															m_level;
		vgd::node::VertexShape::DeformableHintValueType				m_deformableHint;
		vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType	m_boundingBox;
	};

	} //namespace vgTest

} //namespace vgsdkTestGtk

#endif // #ifndef _VGSDKTESTGTK_VGTEST_PERFORMANCE_HPP