// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/MultiSwitch.hpp"

#include "vgd/field/Integer.hpp"
#include "vgd/graph/Graph.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( MultiSwitch );



MultiSwitch::MultiSwitch( const std::string nodeName ) :
	Group(nodeName)
{
	// Add fields
	addField( new vgd::field::SFInt32(	getFWhichChild())	);
	addField( new vgd::field::MFInt32(	getFChosenChild())	);

	// Links
	link( getFWhichChild(),		getDFChildrenSelection() );
	link( getFChosenChild(),	getDFChildrenSelection() );
	
	link( getDFNode() );	
}



void MultiSwitch::setToDefaults( void )
{
	Group::setToDefaults();

	setWhichChild( MULTI_SWITCH_DEFAULT );
	removeAllFromChosenChild();
}



void MultiSwitch::setOptionalsToDefaults()
{
	Group::setOptionalsToDefaults();
}



const int32 MultiSwitch::getWhichChild( void ) const
{
	return ( getFieldRO<vgd::field::SFInt32>(getFWhichChild())->getValue() );
}



void MultiSwitch::setWhichChild( const int32 whichChild )
{
	getFieldRW<vgd::field::SFInt32>(getFWhichChild())->setValue( whichChild );
	
	updateGraph();
}



bool MultiSwitch::isChildChoosen( const int32 index ) const
{
	assert( checkChildIndex(index) && "index is out of range." );
	
	vgd::field::EditorRO<vgd::field::MFInt32> chosenChild = getFieldRO<vgd::field::MFInt32>(getFChosenChild());
	
	return ( chosenChild->find( index ) != -1 );
}



void MultiSwitch::addToChosenChild( const int32 index )
{
	assert( checkChildIndex(index) && "index is out of range." );

	if ( !isChildChoosen(index) )
	{
		vgd::field::EditorRW<vgd::field::MFInt32> chosenChild = getFieldRW<vgd::field::MFInt32>(getFChosenChild());
		chosenChild->push_back( index );
		
		updateGraph();
	}
}



void MultiSwitch::removeFromChosenChild( const int32 index )
{
	assert( checkChildIndex(index) && "index is out of range." );
	
	vgd::field::EditorRW<vgd::field::MFInt32> chosenChild = getFieldRW<vgd::field::MFInt32>(getFChosenChild());
	int32 indexChosenChild = chosenChild->find( index );
	
	if ( indexChosenChild != -1 )
	{
		// Found index in chosenChild
		chosenChild->erase( indexChosenChild );
		
		updateGraph();
	}
	// not found, nothing to be done.
}



void MultiSwitch::removeAllFromChosenChild( void )
{
	vgd::field::EditorRW<vgd::field::MFInt32> chosenChild = getFieldRW<vgd::field::MFInt32>(getFChosenChild());
	
	chosenChild->clear();
	
	updateGraph();	
}



void MultiSwitch::updateGraph()
{
	bool bChildren				= getDirtyFlag(getDFChildren())->isDirty();
	bool bChildrenSelection		= getDirtyFlag(getDFChildrenSelection())->isDirty();

	if ( bChildren || bChildrenSelection )
	{
		const int32 whichChild = getFieldRO<vgd::field::SFInt32>(getFWhichChild())->getValue();
		switch (whichChild)
		{
			
			case MULTI_SWITCH_OFF:
				graph().setEdges( this, false );
				break;
			
			case MULTI_SWITCH_ON:
			{
				// FIXME: optimize.
				std::set< int32 > setTmp;
				vgd::field::EditorRO<vgd::field::MFInt32> chosenChild = 
					getFieldRO<vgd::field::MFInt32>(getFChosenChild());

				// Convert MultiField to a set, and check index.
				for(	int32	i		= 0,
								iMax	= static_cast<int32>(chosenChild->size());
						i < iMax;
						i++ )
				{
					const int32 indexTmp = (*chosenChild)[i]; // FIXME : optme.
					assert( checkChildIndex( indexTmp ) && "index is out of range." );

					setTmp.insert( indexTmp );
				}
				
				// Modify graph.
				graph().setEdges( this, setTmp, true/*enable*/ );
			}
			break;
			
			case MULTI_SWITCH_ALL:
				graph().setEdges( this, true );
				break;

			default:
				assert( false && "unkwown value for MultiSwitch." );
				return;
		}
		
		getDirtyFlag(getDFChildren())->validate();
		getDirtyFlag(getDFChildrenSelection())->validate();
		getDirtyFlag(getDFNode())->validate();		
	}
	// else nothing
}



const std::string MultiSwitch::getFWhichChild( void )
{
	return ( "f_which_child" );
}



const std::string MultiSwitch::getFChosenChild( void )
{
	return ( "f_chosen_child" );
}



} // namespace node

} // namespace vgd
