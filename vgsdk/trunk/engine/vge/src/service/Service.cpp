// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/service/Service.hpp"



namespace vge
{

namespace service
{



Service::~Service()
{}



vgd::basic::ClassRegistry< Service >&	Service::getClassRegistry( void )
{
	static vgd::basic::ClassRegistry< Service > serviceRegistry;
	
	return ( serviceRegistry );
}



} // namespace service

} // namespace vge
