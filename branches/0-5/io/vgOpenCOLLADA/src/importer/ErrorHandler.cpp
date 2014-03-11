// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/ErrorHandler.hpp"

#include <COLLADASaxFWLSaxParserError.h>

namespace vgOpenCOLLADA
{

namespace importer
{

bool ErrorHandler::handleError(const COLLADASaxFWL::IError* error)
{
	//get a little more information
	if (error->getErrorClass() == COLLADASaxFWL::IError::ERROR_SAXPARSER)
	{
		COLLADASaxFWL::IError* _error = const_cast<COLLADASaxFWL::IError* >( error );
		COLLADASaxFWL::SaxParserError* saxParserError = static_cast<COLLADASaxFWL::SaxParserError* >( _error );
		std::cerr << saxParserError->getError().getErrorMessage() << std::endl;
	} 
	else
	{
		std::cerr << "Error of unknown type occured." << std::endl;
	}
	
	if (error->getSeverity() == COLLADASaxFWL::IError::SEVERITY_CRITICAL)
		return true;
	else
		return false;
}

} // namespace importer

} // namespace vgCollada
