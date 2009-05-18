// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/field/DirtyFlag.hpp"



namespace vgd
{
	
namespace field
{



DirtyFlag::DirtyFlag( const std::string& strFlagName, const bool bIsDirty )
:	NamedObject		(strFlagName),
	m_bIsDirty		(bIsDirty)
{}



DirtyFlag::~DirtyFlag()
{}



const bool DirtyFlag::isDirty() const
{
	return m_bIsDirty;
}



const bool DirtyFlag::isValid() const
{
	return ( !m_bIsDirty );
}



void DirtyFlag::dirty( const bool setToDirty )
{
	m_bIsDirty = setToDirty;
}



void DirtyFlag::validate( const bool setToValid )
{
	m_bIsDirty = !setToValid;
}



} // namespace field

} // namespace vgd
