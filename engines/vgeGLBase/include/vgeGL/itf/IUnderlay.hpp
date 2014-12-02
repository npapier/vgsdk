//// VGSDK - Copyright (C) 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_ITF_IUNDERLAY_HPP
//#define _VGEGLBASE_ITF_IUNDERLAY_HPP
//
//#include <vgd/Shp.hpp>
//
//namespace vgd { namespace node { struct LayerPlan; } }
//
//
//
//namespace vgeGL
//{
//
//namespace itf
//{
//
//
//
///**
// * @brief Interface for underlay accessors
// */
//struct IUnderlay
//{
//	/**
//	 * @brief Sets the current underlay.
//	 * @param underlay	the layer plan to use for underlay
//	 */
//	virtual void setUnderlay( vgd::Shp< vgd::node::LayerPlan > underlay )=0;
//
//	/**
//	 * @brief Returns the current underlay.
//	 *
//	 * @return the installed underlay
//	 */
//	virtual vgd::Shp< vgd::node::LayerPlan > getUnderlay()=0;
//};
//
//
//
//} // namespace itf
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_ITF_IUNDERLAY_HPP
//