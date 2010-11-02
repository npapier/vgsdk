// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgUI/helpers.hpp"



namespace vgUI
{



Format::Format( const std::string str )
: m_converter( str )
{}


const std::string Format::str() const
{
	return m_converter.str();
}


Format& Format::operator %( const int param )
{
	m_converter % param;
	return (*this);
}


Format& Format::operator %( const float param )
{
	m_converter % param;
	return (*this);
}


Format& Format::operator %( const std::string param )
{
	m_converter % param;
	return (*this);
}


} // namespace vgUI
