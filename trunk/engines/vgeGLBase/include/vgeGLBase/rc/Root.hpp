//// VGSDK - Copyright (C) 2007, 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_RC_ROOT_HPP
//#define _VGEGLBASE_RC_ROOT_HPP
//
//#include <glo/IResource.hpp>
//#include <vgd/node/Separator.hpp>
//#include "vgeGLBase/vgeGLBase.hpp"
//
//
//
//namespace vgeGLBase
//{
//	
//namespace rc
//{
//
//
//
///**
// * @brief Root of a scene graph
// *
// * @todo Should be in vge...
// */
//struct Root : public ::glo::IResource
//{
//	/**
//	 * @brief Default constructor
//	 */
//	VGEGLBASE_API Root();
//
//	/**
//	 * @brief Gets the root node of the scene graph
//	 * 
//	 * @return the root node
//	 */
//	VGEGLBASE_API const vgd::Shp< vgd::node::Separator > getRoot() const;
//	
//	/**
//	 * @brief Gets the root node of the scene graph
//	 * 
//	 * @return the root node
//	 */
//	VGEGLBASE_API vgd::Shp< vgd::node::Separator > getRoot();
//	
//	
//	
//private:
//
//	vgd::Shp< vgd::node::Separator >	m_root;		///< The root node of the scene graph owned by this class
//};
//
//
//
//} // namespace rc
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_RC_ROOT_HPP
//