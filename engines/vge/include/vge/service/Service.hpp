// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_SERVICE_SERVICE_HPP
#define _VGE_SERVICE_SERVICE_HPP

#include "vge/vge.hpp"

#include <list>
#include <vgd/basic/ClassRegistry.hpp>

namespace vgd
{
	template<class T> struct Shp;
}



/**
 * @namespace vge::service
 * 
 * @brief Define all type of services provided by handlers.
 */



namespace vge
{

namespace service
{



/**
 * @brief Meta helper.
 */
#define META_SERVICE_HPP( lib_api, serviceType )	/** @brief Service factory.*/ \
static lib_api vgd::Shp< serviceType > create(); \
 \
IMPLEMENT_INDEXABLE_CLASS_EXPORTED_HPP( lib_api, serviceType ); \
private: \
 \
static const vgd::basic::RegisterClass<serviceType> m_registrationInstance; \
public:



/**
 * @brief Meta helper.
 */
#define META_SERVICE_CPP( lib_api, serviceType )	vgd::Shp< serviceType > serviceType::create() \
{ \
	return ( vgd::Shp< serviceType >( new serviceType ) ); \
} \
 \
IMPLEMENT_INDEXABLE_CLASS_CPP( serviceType ); \
 \
const vgd::basic::RegisterClass<serviceType> serviceType::m_registrationInstance;



struct VGE_API Service
{
	/**
	 * @brief Virtual destructor
	 */
	virtual ~Service();

	/**
	 * @brief Returns the service registry (i.e. the registered services table).
	 */
	static vgd::basic::ClassRegistry< Service >&	getClassRegistry( void );
	
	/**
	 * @brief This abstract base class must have part of the IndexableClass interface.
	 */
	virtual int32& getClassIndex()=0;
};



/**
 * @brief List of services.
 */
typedef std::list< vgd::Shp<vge::service::Service> >		List;



} // namespace service

} // namespace vge

#endif //#ifndef _VGE_SERVICE_SERVICE_HPP
