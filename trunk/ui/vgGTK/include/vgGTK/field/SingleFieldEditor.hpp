// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_SINGLEFIELDEDITOR_HPP_
#define _VGGTK_FIELD_SINGLEFIELDEDITOR_HPP_

#include <vgd/field/EditorRO.hpp>
#include <vgd/field/EditorRW.hpp>
#include <vgd/field/TSingleField.hpp>

#include "vgGTK/field/Editor.hpp"



namespace vgGTK
{

namespace field
{



/**
 * @brief	Abstract editor for vgd::field::TSingleField<T>.
 */
struct SingleFieldEditor : public Editor
{

protected:

	/**
	 * @brief	Retrieves the value of the field.
	 *
	 * @return	the value of the field
	 */
	template< typename T > const T & getFieldValue() const
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TSingleField< T > FieldType;

		vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName );
	
		return fieldEditor.get()->getValue();
	}
	
	/**
	 * @brief	Assignes a new value to the field.
	 *
	 * @param	value	the new value for the field
	 */
	template< typename T > void setFieldValue( const T & value )
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TSingleField< T > FieldType;
		
		vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName );
	
		return fieldEditor.get()->setValue( value );
	}
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_SINGLEFIELDEDITOR_HPP_
