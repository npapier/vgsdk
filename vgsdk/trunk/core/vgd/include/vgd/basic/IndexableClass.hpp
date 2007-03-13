// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_INDEXABLECLASS_HPP
#define _VGD_BASIC_INDEXABLECLASS_HPP

#include <vgBase/vgBase.hpp>



namespace vgd
{
	
namespace basic
{



/**
 * @brief Implementation indexable class.
 */
//template < typename className >
//struct IndexableClass
//{
//	static int32& getClassIndexStatic()
//	{
//		static int32 index = -1;
//		return index;
//	}
//	
//	virtual int32& getClassIndex()
//	{
//		assert(typeid(*this) == typeid(className));
//		
//		return ( getClassIndexStatic() );
//	}
//};



// version with MACRO.
#define IMPLEMENT_INDEXABLE_CLASS_HPP( lib_api, className )	lib_api static int32& getClassIndexStatic(); \
lib_api virtual int32& getClassIndex();



#define IMPLEMENT_INDEXABLE_CLASS_CPP( lib_api, className )	int32& className::getClassIndexStatic() \
{ \
	static int32 index = -1; \
	return index; \
} \
int32& className::getClassIndex() \
{ \
	assert(typeid(*this) == typeid(className)); \
	return ( getClassIndexStatic() ); \
}



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_INDEXABLECLASS_HPP
