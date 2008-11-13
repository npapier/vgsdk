// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGCOLLADA_OPERATIONS_HPP
#define _VGCOLLADA_OPERATIONS_HPP

#include <dae/daeIDRef.h>
#include <dae/daeURI.h>



namespace vgCollada
{



daeElement *getAbstractElementFromURI( daeURI & uri );

template< class T >
T *getElementFromURI( daeURI & uri )
{
	daeElement * element = getAbstractElementFromURI( uri );

	return daeSafeCast< T >( element );
}


daeElement *getElementFromIDRef( daeIDRef & idref );

template< typename TInputArray, typename TInputType >
bool findInputSourceBySemantic( TInputArray& inputs, const char* semantic, daeElement *& element, 
                                TInputType ** input = NULL, int unit = 0 )
{
    element = NULL;
    int count = 0;
    for ( size_t i = 0; i < inputs.getCount(); i++ ) {
        if ( !strcmp(semantic, inputs[i]->getSemantic()) ) {
            if ( count == unit )
            {
                element = getElementFromURI( inputs[i]->getSource() );
                *input = (TInputType*)inputs[i];
                return true;
            }
            count++;
        }
    }
    return false;
}

} // namespace vgCollada

#endif // _VGCOLLADA_OPERATIONS_HPP
