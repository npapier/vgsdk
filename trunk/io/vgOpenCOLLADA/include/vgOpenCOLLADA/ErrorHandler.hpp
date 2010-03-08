// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_ERRORHANDLER_HPP
#define _VGOPENCOLLADA_ERRORHANDLER_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <COLLADASaxFWLIError.h>
#include <COLLADASaxFWLIErrorHandler.h>
#include <COLLADASaxFWLStableHeaders.h>

namespace vgOpenCOLLADA
{

/**
 * @brief Class to handle errors that occur while parsing a collada file.
 */
struct VGOPENCOLLADA_API ErrorHandler : public COLLADASaxFWL::IErrorHandler
{
	ErrorHandler() {};
	virtual ~ErrorHandler() {};

	/**
	 * @brief Called when an error occured. Print a message.
	 *
	 * @return bool: if critial error, return true and stop loading scene.
	 */
	virtual bool handleError(const COLLADASaxFWL::IError* error);
};



} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_ERRORHANDLER_HPP

