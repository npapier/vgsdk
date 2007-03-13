// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGITK_FAILED_H
#define _VGITK_FAILED_H

#include <exception>
#include <string>

#include "vgITK/vgITK.hpp"



namespace vgITK
{


	
/**
 * @brief	Defines an exception class for failures.
 * 
 * @author	Nicolas Papier
 */
struct VGITK_API Failed : public std::exception
{
	
	/**
	 * @brief	constructor
	 * 
	 * @param	message	a string containing an error message
	 */
	Failed(const std::string &message) throw();
	
	/**
	 * @brief	destructor
	 */
	~Failed() throw() {};
	
	
	// Overrides
	const char* what() const throw();
	
	
private:

	/**
	 * @brief	a string containing the exception's error message
	 */
	std::string m_message;
	
};



} // namespace vgITK


#endif // #ifndef _VGITK_FAILED_H
