// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_ACCESSORS_H
#define _VGD_FIELD_ACCESSORS_H

#include <string>

#include "vgd/vgd.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/field/EditorRO.hpp"
#include "vgd/field/EditorRW.hpp"

namespace vgd
{
	namespace node
	{
		struct Node;
	}
}



namespace vgd
{
	
namespace field
{


/**
 * @brief Helper to simplify the writing of TPairAssociative accessors in node.
 */
template< typename ParameterType, typename ValueType >
bool getParameterValue(	const vgd::node::Node *pNode, const std::string fieldName,
								const ParameterType param, ValueType& value )
{
	typedef vgd::field::TPairAssociativeField< ParameterType, ValueType > FieldType;

	vgd::field::EditorRO< FieldType > feRO = pNode->template getFieldRO<FieldType>( fieldName );

	typename FieldType::const_iterator iter = feRO->find( param );
	
	if ( iter != feRO->end() )
	{
		value = iter->second;

		return ( true );
	}
	else
	{
		return ( false );
	}
}



/**
 * @brief Helper to simplify the writing of TPairAssociative accessors in node.
 */
template< typename ParameterType, typename ValueType >
void setParameterValue(	vgd::node::Node *pNode, const std::string fieldName,
								const ParameterType param, ValueType value )
{
	typedef vgd::field::TPairAssociativeField< ParameterType, ValueType > FieldType;

	vgd::field::EditorRW< FieldType > feRW( pNode->template getFieldRW< FieldType >(fieldName) );

	(*feRW)[param] = value;
}



/**
 * @brief Helper to simplify the writing of TPairAssociative accessors in node.
 */
template< typename ParameterType, typename ValueType >
void eraseParameterValue(	vgd::node::Node *pNode, const std::string fieldName,
									const ParameterType param )
{
	typedef vgd::field::TPairAssociativeField< ParameterType, ValueType > FieldType;

	vgd::field::EditorRW< FieldType > feRW( pNode->template getFieldRW< FieldType >( fieldName ) );

	feRW->erase( param );
}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_ACCESSORS_H
