// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/IBoundingBox.hpp"



namespace vgd
{

namespace node
{



IBoundingBox::IBoundingBox()
{
	m_boundingBox.setInvalid();
	m_transformation.setIdentity();
}



IBoundingBox::~IBoundingBox()
{}



const vgm::Box3f& IBoundingBox::getBoundingBox() const
{
	assert( isBoundingBoxValid() );

	return m_boundingBox;
}



const vgm::MatrixR& IBoundingBox::getTransformation() const
{
	assert( isBoundingBoxValid() );

	return m_transformation;
}



void IBoundingBox::setBoundingBox( const vgm::Box3f& boundingBox )
{
	m_boundingBox = boundingBox;
}



void IBoundingBox::setTransformation( const vgm::MatrixR& transformation )
{
	m_transformation = transformation;
}



void IBoundingBox::reset()
{
	m_boundingBox.setInvalid();
	m_transformation.setIdentity();
}



vgm::XfBox3f IBoundingBox::getXfBoundingBox() const
{
	assert( isBoundingBoxValid() );

	vgm::XfBox3f xfBox(m_boundingBox);
	xfBox.setTransform( m_transformation );

	return xfBox;
}



vgm::Box3f IBoundingBox::getProjectXfBoundingBox() const
{
	vgm::XfBox3f xfBox = getXfBoundingBox();

	return xfBox.project();
}



} // namespace node

} // namespace vgd
