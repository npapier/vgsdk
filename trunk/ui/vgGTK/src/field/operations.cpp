// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/operations.hpp"

#include <string>
#include <vgd/field/TSingleField.hpp>

#include "vgGTK/field/EntryEditor.hpp"
#include "vgGTK/field/RadioButtonEditor.hpp"



namespace vgGTK
{

namespace field
{



vgd::Shp< Editor > createEditor( const std::type_info & fieldType )
{
	vgd::Shp< Editor >	result;
	
	if( fieldType == typeid(vgd::field::TSingleField< std::string >) )	result.reset( new EntryEditor() );
	if( fieldType == typeid(vgd::field::TSingleField< bool >) )			result.reset( new RadioButtonEditor() );
	
	return result;
}



} // namespace field

} // namespace vgGTK
