// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/IBoundingBox.hpp"



namespace vgd
{

namespace node
{



const vgm::Box3f& IBoundingBox::getBoundingBox() const
{
	assert( isBoundingBoxValid() );

	return ( m_boundingBox );
}



vgm::XfBox3f IBoundingBox::getXfBoundingBox() const
{
	assert( isBoundingBoxValid() );

	vgm::XfBox3f xfBox(m_boundingBox);
	xfBox.setTransform( m_transformation );

	return ( xfBox );
}



vgm::Box3f IBoundingBox::getProjectXfBoundingBox() const
{
	vgm::XfBox3f xfBox = getXfBoundingBox();

	return ( xfBox.project() );
}




} // namespace node

} // namespace vgd
