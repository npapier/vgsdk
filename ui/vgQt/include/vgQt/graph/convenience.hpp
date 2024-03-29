// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGQT_GRAPH_CONVENIENCE_HPP_
#define _VGQT_GRAPH_CONVENIENCE_HPP_

#include <string>
#include <vgd/field/FieldManager.hpp>

namespace vgd { namespace node { struct IBoundingBox; } }



namespace vgUI
{

namespace graph
{



/**
 * @brief	Retrieves a field value as a string.
 *
 * @param	fieldManager	a shared pointer to a field manager
 * @param	fieldName		a string containing a field name
 *
 * @return	a string containing the desired field value
 *
 * @todo	Throw an exception on error (missing field).
 */
const std::string getFieldAsString( const vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName );



const std::string toString( const vgd::node::IBoundingBox * ibb );




} // namespace graph

} // namespace vgUI

#endif // _VGQT_GRAPH_CONVENIENCE_HPP_
