// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Switch.hpp"

#include "vgd/field/Integer.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Switch );



Switch::Switch( const std::string nodeName ) :
	Group(nodeName)
{
	// Add field
	addField( new vgd::field::SFInt8(getFWhichChild()) );

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



const int8 Switch::getWhichChild( void ) const
{
	return ( getFieldRO<vgd::field::SFInt8>(getFWhichChild())->getValue() );
}



void Switch::setWhichChild( const int8 whichChild )
{
	getFieldRW<vgd::field::SFInt8>(getFWhichChild())->setValue( whichChild );
	
	updateGraph();
}



void Switch::updateGraph( void )
{
#ifdef _DEBUG
	std::string name = getName();
#endif

	bool bChildren				= getDirtyFlag(getDFChildren())->isDirty();
	bool bChildrenSelection		= getDirtyFlag(getDFChildrenSelection())->isDirty();

	if ( bChildren || bChildrenSelection )
	{
		const int8 whichChild = getFieldRO<vgd::field::SFInt8>(getFWhichChild())->getValue();
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
				assert( checkChildIndex(whichChild) && "index is out of range." );
				
				std::set< int32 > setIndex;
				setIndex.insert( static_cast< int32 >(whichChild) );
				
				graph().setEdges( this, setIndex, true );
			}
		}
		getDirtyFlag(getDFChildren())->validate();
		getDirtyFlag(getDFChildrenSelection())->validate();
		getDirtyFlag(getDFNode())->validate();
	}
	// else nothing
}



const std::string Switch::getFWhichChild(void)
{
	return ( "f_whichChild" );
}
	


} // namespace node

} // namespace vgd
