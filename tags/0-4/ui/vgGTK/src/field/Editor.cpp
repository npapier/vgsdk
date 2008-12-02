// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/Editor.hpp"



namespace vgGTK
{

namespace field
{



Editor::~Editor()
{}



void Editor::setField( vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName )
{
	m_fieldManager	= fieldManager;
	m_fieldName		= fieldName;
	
	refresh();
}



} // namespace field

} // namespace vgGTK
