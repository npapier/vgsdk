//// VGSDK - Copyright (C) 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_POSTPROCESSING_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_POSTPROCESSING_HPP
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//#include <utility>
//#include <vgd/node/PostProcessing.hpp>
//#include <vge/handler/painter/MultiAttribute.hpp>
//
//
//
//namespace vgeGLBase
//{
//
//namespace handler
//{
//
//namespace painter
//{
//
//
//
///**
// * @brief Send render commands for the PostProcessing node.
// */
//struct VGEGLBASE_API PostProcessing : public vge::handler::painter::MultiAttribute
//{
//	META_HANDLER_HPP( PostProcessing );
//
//	const TargetVector getTargets() const;
//
//	void apply( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
//
//	/**
//	 * @brief Returns a pair containing glsl code implementing and applying the desired filter
//	 */
//	static std::pair< std::string, std::string > getFilter( vgd::node::PostProcessing *, const vgd::node::PostProcessing::FilterValueType& /*filter*/ );
//
//	/**
//	 * @brief Returns a pair containing glsl code implementing and applying the desired scaling for the filter
//	 *
//	 * @return	first element of the pair is the scale factor that must be applied to input texture coordinates,
//	 *			last element of the pair is the scale factor that must be applied to shape vertices.
//	 */
//	static std::pair< float, float > getScale( const vgd::node::PostProcessing::FilterValueType& filter );
//};
//
//
//
//} // namespace painter
//
//} // namespace handler
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_POSTPROCESSING_HPP
//