// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_SERVICE_PAINTER_H
#define _VGE_SERVICE_PAINTER_H

#include "vge/vge.hpp"

#include <vgd/basic/IndexableClass.hpp>
#include <vgd/basic/RegisterClass.hpp>

#include "vge/service/Service.hpp"



namespace vge
{
	
namespace service
{



struct Painter : public Service
{
	META_SERVICE_HPP( VGE_API, Painter );
};



} // namespace service

} // namespace vge

#endif //#ifndef _VGE_SERVICE_PAINTER_H
