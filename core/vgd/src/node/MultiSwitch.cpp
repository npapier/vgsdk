// VGSDK - Copyright (C) 2004, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/node/MultiSwitch.hpp"

#include "vgd/field/Integer.hpp"
#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( MultiSwitch );



MultiSwitch::MultiSwitch( const std::string nodeName ) :
	Group(nodeName)
{
	// Adds fields
	addField( new vgd::field::SFInt32(	getFWhichChild())	);
	addField( new vgd::field::MFInt32(	getFChosenChild())	);

	// Links
	link( getFWhichChild(),		getDFChildrenSelection() );
	link( getFWhichChild(),		getDFBoundingBox() );
	link( getFChosenChild(),	getDFChildrenSelection() );
	link( getFChosenChild(),	getDFBoundingBox() );

	link( getDFNode() );
}



void MultiSwitch::setToDefaults( void )
{
	Group::setToDefaults();

	setWhichChild( MULTI_SWITCH_DEFAULT );
	clearChoosenChildren();
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

	return ( chosenChild->find( index ) != chosenChild->size() );
}



void MultiSwitch::addToChoosenChildren( const int32 index )
{
	assert( checkChildIndex(index) && "index is out of range." );

	if ( !isChildChoosen(index) )
	{
		vgd::field::EditorRW<vgd::field::MFInt32> chosenChild = getFieldRW<vgd::field::MFInt32>(getFChosenChild());
		chosenChild->push_back( index );

		updateGraph();
	}
}



void MultiSwitch::removeFromChoosenChildren( const int32 index )
{
	assert( checkChildIndex(index) && "index is out of range." );

	vgd::field::EditorRW<vgd::field::MFInt32> chosenChild = getFieldRW<vgd::field::MFInt32>(getFChosenChild());
	const int32 indexChosenChild = chosenChild->find( index );

	if ( indexChosenChild != chosenChild->size() )
	{
		// Found index in chosenChild
		chosenChild->erase( indexChosenChild );

		updateGraph();
	}
	// not found, nothing to be done.
}



void MultiSwitch::clearChoosenChildren( void )
{
	vgd::field::EditorRW<vgd::field::MFInt32> chosenChild = getFieldRW<vgd::field::MFInt32>(getFChosenChild());

	chosenChild->clear();

	updateGraph();
}



void MultiSwitch::updateGraph()
{
	const bool bChildren			= getDirtyFlag(getDFChildren())->isDirty();
	const bool bChildrenSelection	= getDirtyFlag(getDFChildrenSelection())->isDirty();

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
				// @todo optimize
				std::set< int > setTmp;
				vgd::field::EditorRO<vgd::field::MFInt32> chosenChild = 
					getFieldRO<vgd::field::MFInt32>(getFChosenChild());

				// Converts MultiField to a set, and check index.
				for(	int32	i		= 0,
								iMax	= static_cast<int32>(chosenChild->size());
						i < iMax;
						i++ )
				{
					const int32 indexTmp = (*chosenChild)[i]; // FIXME : optme.
					//assert( checkChildIndex( indexTmp ) && "index is out of range." ); @todo a warning in log

					setTmp.insert( indexTmp );
				}

				// Updates graph
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

		// Validates dirty flags
		getDirtyFlag(getDFChildren())->validate();
		getDirtyFlag(getDFChildrenSelection())->validate();
	}
	// else nothing
}



const std::string MultiSwitch::getFWhichChild( void )
{
	return "f_which_child";
}



const std::string MultiSwitch::getFChosenChild( void )
{
	return "f_chosen_child";
}



} // namespace node

} // namespace vgd
