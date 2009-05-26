// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Camera.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Camera > Camera::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Camera > node( new Camera(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Camera > Camera::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Camera > node = Camera::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Camera::Camera( const std::string nodeName ) :
	vgd::node::ProjectionTransformation( nodeName )
{
	// Adds field(s)
	addField( new FScissorType(getFScissor()) );
	addField( new FMatrixType(getFMatrix()) );
	addField( new FViewportType(getFViewport()) );

	// Sets link(s)
	link( getDFNode() );
}



void Camera::setToDefaults( void )
{
	ProjectionTransformation::setToDefaults();
	setMatrix( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
}



void Camera::setOptionalsToDefaults()
{
	ProjectionTransformation::setOptionalsToDefaults();
	
	setViewport( vgm::Rectangle2i(0, 0, 1600, 1200) );
}



// Scissor
const bool Camera::getScissor( ScissorValueType& value ) const
{
	return getFieldRO<FScissorType>(getFScissor())->getValue( value );
}



void Camera::setScissor( const ScissorValueType& value )
{
	getFieldRW<FScissorType>(getFScissor())->setValue( value );
}



void Camera::eraseScissor()
{
	getFieldRW<FScissorType>(getFScissor())->eraseValue();
}


const bool Camera::hasScissor() const
{
	return getFieldRO<FScissorType>(getFScissor())->hasValue();
}



// Matrix
const Camera::MatrixValueType Camera::getMatrix() const
{
	return getFieldRO<FMatrixType>(getFMatrix())->getValue();
}



void Camera::setMatrix( const MatrixValueType value )
{
	getFieldRW<FMatrixType>(getFMatrix())->setValue( value );
}



// Viewport
const bool Camera::getViewport( ViewportValueType& value ) const
{
	return getFieldRO<FViewportType>(getFViewport())->getValue( value );
}



void Camera::setViewport( const ViewportValueType& value )
{
	getFieldRW<FViewportType>(getFViewport())->setValue( value );
}



void Camera::eraseViewport()
{
	getFieldRW<FViewportType>(getFViewport())->eraseValue();
}


const bool Camera::hasViewport() const
{
	return getFieldRO<FViewportType>(getFViewport())->hasValue();
}



// Field name accessor(s)
const std::string Camera::getFScissor( void )
{
	return "f_scissor";
}



const std::string Camera::getFMatrix( void )
{
	return "f_matrix";
}



const std::string Camera::getFViewport( void )
{
	return "f_viewport";
}



const vgm::Vec3f Camera::applyViewport( const vgm::Vec3f& vertex )
{
	vgm::Rectangle2i viewport;
	const bool isDefined = getViewport( viewport );
	assert( isDefined );

	const vgm::Vec2f o(	static_cast<float>(viewport.x()) + static_cast<float>(viewport.width()) * 0.5f,
						static_cast<float>(viewport.y()) + static_cast<float>(viewport.height()) * 0.5f );

	const vgm::Vec2f p(	static_cast<float>(viewport.width()),
						static_cast<float>(viewport.height()) );

	const float fFar	(	1.f	);
	const float fNear	(	0.f	);

	const vgm::Vec3f window(	p[0] * 0.5f * vertex[0] + o[0],
								p[1] * 0.5f * vertex[1] + o[1],
								(fFar - fNear) * 0.5f * vertex[2] + (fNear+fFar)*0.5f );

	return window;
}




IMPLEMENT_INDEXABLE_CLASS_CPP( , Camera );



const vgd::basic::RegisterNode<Camera> Camera::m_registrationInstance;



} // namespace node

} // namespace vgd
