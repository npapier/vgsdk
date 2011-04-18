// VGSDK - Copyright (C) 2011, Nicolas Papier.
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



vgd::Shp< Camera > Camera::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Camera > node = Camera::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

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
	vgd::node::GeometricalTransformation( nodeName ),
	vgd::node::ProjectionTransformation()
{
	// Adds field(s)
	addField( new FProjectionLeftType(getFProjectionLeft()) );
	addField( new FLookAtLeftType(getFLookAtLeft()) );
	addField( new FLookAtRightType(getFLookAtRight()) );
	addField( new FProjectionRightType(getFProjectionRight()) );
	addField( new FScissorType(getFScissor()) );
	addField( new FModeType(getFMode()) );
	addField( new FViewportType(getFViewport()) );

	// Sets link(s)

	link( getDFNode() );
}



void Camera::setToDefaults( void )
{
	GeometricalTransformation::setToDefaults();
	ProjectionTransformation::setToDefaults();
	setProjectionLeft( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
	setLookAtLeft( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
	setLookAtRight( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
	setProjectionRight( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
	setMode( MONOSCOPIC );
}



void Camera::setOptionalsToDefaults()
{
	GeometricalTransformation::setOptionalsToDefaults();
	ProjectionTransformation::setOptionalsToDefaults();

	setViewport( vgm::Rectangle2i(0, 0, 1600, 1200) );
}



// ProjectionLeft
const Camera::ProjectionLeftValueType Camera::getProjectionLeft() const
{
	return getFieldRO<FProjectionLeftType>(getFProjectionLeft())->getValue();
}



void Camera::setProjectionLeft( const ProjectionLeftValueType value )
{
	getFieldRW<FProjectionLeftType>(getFProjectionLeft())->setValue( value );
}



// LookAtLeft
const Camera::LookAtLeftValueType Camera::getLookAtLeft() const
{
	return getFieldRO<FLookAtLeftType>(getFLookAtLeft())->getValue();
}



void Camera::setLookAtLeft( const LookAtLeftValueType value )
{
	getFieldRW<FLookAtLeftType>(getFLookAtLeft())->setValue( value );
}



// LookAtRight
const Camera::LookAtRightValueType Camera::getLookAtRight() const
{
	return getFieldRO<FLookAtRightType>(getFLookAtRight())->getValue();
}



void Camera::setLookAtRight( const LookAtRightValueType value )
{
	getFieldRW<FLookAtRightType>(getFLookAtRight())->setValue( value );
}



// ProjectionRight
const Camera::ProjectionRightValueType Camera::getProjectionRight() const
{
	return getFieldRO<FProjectionRightType>(getFProjectionRight())->getValue();
}



void Camera::setProjectionRight( const ProjectionRightValueType value )
{
	getFieldRW<FProjectionRightType>(getFProjectionRight())->setValue( value );
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



// Mode
const Camera::ModeValueType Camera::getMode() const
{
	return getFieldRO<FModeType>(getFMode())->getValue();
}



void Camera::setMode( const ModeValueType value )
{
	getFieldRW<FModeType>(getFMode())->setValue( value );
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
const std::string Camera::getFProjectionLeft( void )
{
	return "f_projectionLeft";
}



const std::string Camera::getFLookAtLeft( void )
{
	return "f_lookAtLeft";
}



const std::string Camera::getFLookAtRight( void )
{
	return "f_lookAtRight";
}



const std::string Camera::getFProjectionRight( void )
{
	return "f_projectionRight";
}



const std::string Camera::getFScissor( void )
{
	return "f_scissor";
}



const std::string Camera::getFMode( void )
{
	return "f_mode";
}



const std::string Camera::getFViewport( void )
{
	return "f_viewport";
}



const vgm::Vec3f Camera::applyViewport( const vgm::Vec3f& vertex )
{
	assert( hasViewport() );

	vgm::Rectangle2i viewport;
	getViewport( viewport );

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



// LOOKAT/LOOKATLEFT
const Camera::LookAtValueType Camera::getLookAt() const
{
	return getLookAtLeft();
}


void Camera::setLookAt( const LookAtValueType value )
{
	setLookAtLeft(value);
}



// PROJECTION/PROJECTIONLEFT
const Camera::ProjectionValueType Camera::getProjection() const
{
	return getProjectionLeft();
}


void Camera::setProjection( const ProjectionValueType value )
{
	setProjectionLeft( value );
}



// Matrix
const Camera::MatrixValueType Camera::getMatrix() const
{
	return getFieldRO<FMatrixType>(getFProjectionLeft())->getValue();
}



void Camera::setMatrix( const MatrixValueType value )
{
	getFieldRW<FMatrixType>(getFProjectionLeft())->setValue( value );
}
IMPLEMENT_INDEXABLE_CLASS_CPP( , Camera );



const vgd::basic::RegisterNode<Camera> Camera::m_registrationInstance;



} // namespace node

} // namespace vgd

