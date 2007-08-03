// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgITK/Failed.hpp"



namespace vgITK
{



Failed::Failed(const std::string &message) throw()
: m_message(message)
{}


const char* Failed::what() const throw()
{
	return m_message.c_str();
}



} // namespace vgITK
