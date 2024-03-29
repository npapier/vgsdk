// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_SERVICE_COMPUTEBOUNDINGBOX_HPP
#define _VGE_SERVICE_COMPUTEBOUNDINGBOX_HPP

#include "vge/vge.hpp"

#include <vgd/basic/IndexableClass.hpp>
#include <vgd/basic/RegisterClass.hpp>

#include "vge/service/Service.hpp"



namespace vge
{
	
namespace service
{



struct ComputeBoundingBox : public Service
{
	META_SERVICE_HPP( VGE_API, ComputeBoundingBox );
};



} // namespace service

} // namespace vge

#endif //#ifndef _VGE_SERVICE_COMPUTEBOUNDINGBOX_HPP
