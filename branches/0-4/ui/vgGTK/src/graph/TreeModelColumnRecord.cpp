// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/graph/TreeModelColumnRecord.hpp"



namespace vgGTK
{

namespace graph
{



TreeModelColumnRecord::TreeModelColumnRecord()
{
	// Fills the tree model column record with desired tree model columns.
	add( m_nodeColumn );
	add( m_nameColumn );
	add( m_typeColumn );
	add( m_activeColumn );
	add( m_sharedColumn );
}



} // namespace graph

} // namespace vgGTK
