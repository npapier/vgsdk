// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Switch.hpp"

#include "vgd/field/Integer.hpp"
#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Switch );



Switch::Switch( const std::string nodeName ) :
	Group(nodeName)
{
	// Adds field
	addField( new vgd::field::SFInt32(getFWhichChild()) );

	// Links
	link( getFWhichChild(), getDFChildrenSelection() );
	link( getFWhichChild(), getDFBoundingBox() );

	link( getDFNode() );
}



void Switch::setToDefaults( void )
{
	Group::setToDefaults();

	setWhichChild( SWITCH_DEFAULT );
}



void Switch::setOptionalsToDefaults()
{
	Group::setOptionalsToDefaults();
}



const int Switch::getWhichChild( void ) const
{
	return ( getFieldRO<vgd::field::SFInt32>(getFWhichChild())->getValue() );
}



void Switch::setWhichChild( const int whichChild )
{
	getFieldRW<vgd::field::SFInt32>(getFWhichChild())->setValue( whichChild );

	updateGraph();
}



void Switch::updateGraph( void )
{
//#ifdef _DEBUG
//	std::string name = getName();
//#endif

	const bool bChildren			= getDirtyFlag(getDFChildren())->isDirty();
	const bool bChildrenSelection	= getDirtyFlag(getDFChildrenSelection())->isDirty();

	if ( bChildren || bChildrenSelection )
	{
		const int whichChild = getFieldRO<vgd::field::SFInt32>(getFWhichChild())->getValue();

		switch (whichChild)
		{
			case SWITCH_ALL:
				graph().setEdges( this, true );
				break;
			
			case SWITCH_NONE:
				graph().setEdges( this, false );
				break;
	
			default:
			{
				// assert( checkChildIndex(whichChild) && "index is out of range." ); @todo a warning in log

				std::set< int > setIndex;
				setIndex.insert( whichChild );

				graph().setEdges( this, setIndex, true );
			}
		}

		// Validates dirty flags
		getDirtyFlag(getDFChildren())->validate();
		getDirtyFlag(getDFChildrenSelection())->validate();
	}
	// else nothing
}



const std::string Switch::getFWhichChild(void)
{
	return "f_whichChild";
}



} // namespace node

} // namespace vgd
