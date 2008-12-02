// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgCollada/operations.hpp"

#include <dae.h>



namespace vgCollada
{



daeElement *getAbstractElementFromURI( daeURI & uri )
{
/*	if ( uri.getState() == daeURI::uri_loaded || uri.getState() == daeURI::uri_pending ) 
	{
		uri.resolveElement();
	}*/

	return uri.getElement();
}



daeElement *getElementFromIDRef( daeIDRef & idref )
{
	if ( idref.getState() == daeIDRef::id_loaded || idref.getState() == daeIDRef::id_pending )
	{
		idref.resolveElement();
	}
	
	return idref.getElement();
}



} // namespace vgCollada
