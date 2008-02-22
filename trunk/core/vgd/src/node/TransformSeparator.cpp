// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TransformSeparator.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( TransformSeparator );



TransformSeparator::TransformSeparator( const std::string nodeName ) :
	vgd::node::Group( nodeName )
{
	// Add field
	addField( new FMaskType(getFMask()) );
	
	// Links
	link( getDFNode() );
}



void TransformSeparator::setToDefaults( void )
{
	Group::setToDefaults();
	
	setMask( DEFAULT_MASK );
}



void TransformSeparator::setOptionalsToDefaults()
{
	Group::setOptionalsToDefaults();
}



// MASK
int8 TransformSeparator::getMask() const
{
	return ( getFieldRO<FMaskType>(getFMask())->getValue() );
}



void TransformSeparator::setMask( const int8 mask )
{
	getFieldRW<FMaskType>(getFMask())->setValue( mask );
}



const std::string TransformSeparator::getFMask( void )
{
	return "f_mask";
}



} // namespace node

} // namespace vgd
