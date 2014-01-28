// VGSDK - Copyright (C) 2014, Nicolas Papier.
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
	addField( new FProjectionRightType(getFProjectionRight()) );
	addField( new FLookAtRightType(getFLookAtRight()) );
	addField( new FViewportType(getFViewport()) );
	addField( new FFovyType(getFFovy()) );
	addField( new FModeType(getFMode()) );
	addField( new FEyeSeparationType(getFEyeSeparation()) );
	addField( new FImageShiftType(getFImageShift()) );
	addField( new FRightEyeType(getFRightEye()) );
	addField( new FScissorType(getFScissor()) );
	addField( new FAspectType(getFAspect()) );
	addField( new FZNearType(getFZNear()) );
	addField( new FZFarType(getFZFar()) );

	// Sets link(s)

	link( getDFNode() );
}



void Camera::setToDefaults( void )
{
	GeometricalTransformation::setToDefaults();
	ProjectionTransformation::setToDefaults();
	setProjectionLeft( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
	setLookAtLeft( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
	setProjectionRight( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
	setLookAtRight( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
	setViewport( vgm::Rectangle2i(0, 0, 1600, 1200) );
	setFovy( (45.f) );
	setMode( (MONOSCOPIC) );
	setEyeSeparation( (0.f) );
	setImageShift( (0.f) );
	setRightEye( (true) );
}



void Camera::setOptionalsToDefaults()
{
	GeometricalTransformation::setOptionalsToDefaults();
	ProjectionTransformation::setOptionalsToDefaults();
	setScissor( vgm::Rectangle2i(0, 0, 1600, 1200) );
	setAspect( (1) );
	setZNear( (0.01f) );
	setZFar( (3996.f) );
}



// ProjectionLeft

const Camera::ProjectionLeftValueType Camera::DEFAULT_PROJECTIONLEFT = vgm::MatrixR(vgm::MatrixR::getIdentity());



const Camera::ProjectionLeftValueType Camera::getProjectionLeft() const
{
	return getFieldRO<FProjectionLeftType>(getFProjectionLeft())->getValue();
}



void Camera::setProjectionLeft( const ProjectionLeftValueType value )
{
	getFieldRW<FProjectionLeftType>(getFProjectionLeft())->setValue( value );
}



// LookAtLeft

const Camera::LookAtLeftValueType Camera::DEFAULT_LOOKATLEFT = vgm::MatrixR(vgm::MatrixR::getIdentity());



const Camera::LookAtLeftValueType Camera::getLookAtLeft() const
{
	return getFieldRO<FLookAtLeftType>(getFLookAtLeft())->getValue();
}



void Camera::setLookAtLeft( const LookAtLeftValueType value )
{
	getFieldRW<FLookAtLeftType>(getFLookAtLeft())->setValue( value );
}



// ProjectionRight

const Camera::ProjectionRightValueType Camera::DEFAULT_PROJECTIONRIGHT = vgm::MatrixR(vgm::MatrixR::getIdentity());



const Camera::ProjectionRightValueType Camera::getProjectionRight() const
{
	return getFieldRO<FProjectionRightType>(getFProjectionRight())->getValue();
}



void Camera::setProjectionRight( const ProjectionRightValueType value )
{
	getFieldRW<FProjectionRightType>(getFProjectionRight())->setValue( value );
}



// LookAtRight

const Camera::LookAtRightValueType Camera::DEFAULT_LOOKATRIGHT = vgm::MatrixR(vgm::MatrixR::getIdentity());



const Camera::LookAtRightValueType Camera::getLookAtRight() const
{
	return getFieldRO<FLookAtRightType>(getFLookAtRight())->getValue();
}



void Camera::setLookAtRight( const LookAtRightValueType value )
{
	getFieldRW<FLookAtRightType>(getFLookAtRight())->setValue( value );
}



// Viewport

const Camera::ViewportValueType Camera::DEFAULT_VIEWPORT = vgm::Rectangle2i(0, 0, 1600, 1200);



const Camera::ViewportValueType Camera::getViewport() const
{
	return getFieldRO<FViewportType>(getFViewport())->getValue();
}



void Camera::setViewport( const ViewportValueType value )
{
	getFieldRW<FViewportType>(getFViewport())->setValue( value );
}



// Fovy

const Camera::FovyValueType Camera::DEFAULT_FOVY = (45.f);



const Camera::FovyValueType Camera::getFovy() const
{
	return getFieldRO<FFovyType>(getFFovy())->getValue();
}



void Camera::setFovy( const FovyValueType value )
{
	getFieldRW<FFovyType>(getFFovy())->setValue( value );
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



// EyeSeparation

const Camera::EyeSeparationValueType Camera::DEFAULT_EYESEPARATION = (0.f);



const Camera::EyeSeparationValueType Camera::getEyeSeparation() const
{
	return getFieldRO<FEyeSeparationType>(getFEyeSeparation())->getValue();
}



void Camera::setEyeSeparation( const EyeSeparationValueType value )
{
	getFieldRW<FEyeSeparationType>(getFEyeSeparation())->setValue( value );
}



// ImageShift

const Camera::ImageShiftValueType Camera::DEFAULT_IMAGESHIFT = (0.f);



const Camera::ImageShiftValueType Camera::getImageShift() const
{
	return getFieldRO<FImageShiftType>(getFImageShift())->getValue();
}



void Camera::setImageShift( const ImageShiftValueType value )
{
	getFieldRW<FImageShiftType>(getFImageShift())->setValue( value );
}



// RightEye

const Camera::RightEyeValueType Camera::DEFAULT_RIGHTEYE = (true);



const Camera::RightEyeValueType Camera::getRightEye() const
{
	return getFieldRO<FRightEyeType>(getFRightEye())->getValue();
}



void Camera::setRightEye( const RightEyeValueType value )
{
	getFieldRW<FRightEyeType>(getFRightEye())->setValue( value );
}



// Scissor

const Camera::ScissorValueType Camera::DEFAULT_SCISSOR = vgm::Rectangle2i(0, 0, 1600, 1200);



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



// Aspect

const Camera::AspectValueType Camera::DEFAULT_ASPECT = (1);



const bool Camera::getAspect( AspectValueType& value ) const
{
	return getFieldRO<FAspectType>(getFAspect())->getValue( value );
}



void Camera::setAspect( const AspectValueType& value )
{
	getFieldRW<FAspectType>(getFAspect())->setValue( value );
}



void Camera::eraseAspect()
{
	getFieldRW<FAspectType>(getFAspect())->eraseValue();
}


const bool Camera::hasAspect() const
{
	return getFieldRO<FAspectType>(getFAspect())->hasValue();
}



// ZNear

const Camera::ZNearValueType Camera::DEFAULT_ZNEAR = (0.01f);



const bool Camera::getZNear( ZNearValueType& value ) const
{
	return getFieldRO<FZNearType>(getFZNear())->getValue( value );
}



void Camera::setZNear( const ZNearValueType& value )
{
	getFieldRW<FZNearType>(getFZNear())->setValue( value );
}



void Camera::eraseZNear()
{
	getFieldRW<FZNearType>(getFZNear())->eraseValue();
}


const bool Camera::hasZNear() const
{
	return getFieldRO<FZNearType>(getFZNear())->hasValue();
}



// ZFar

const Camera::ZFarValueType Camera::DEFAULT_ZFAR = (3996.f);



const bool Camera::getZFar( ZFarValueType& value ) const
{
	return getFieldRO<FZFarType>(getFZFar())->getValue( value );
}



void Camera::setZFar( const ZFarValueType& value )
{
	getFieldRW<FZFarType>(getFZFar())->setValue( value );
}



void Camera::eraseZFar()
{
	getFieldRW<FZFarType>(getFZFar())->eraseValue();
}


const bool Camera::hasZFar() const
{
	return getFieldRO<FZFarType>(getFZFar())->hasValue();
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



const std::string Camera::getFProjectionRight( void )
{
	return "f_projectionRight";
}



const std::string Camera::getFLookAtRight( void )
{
	return "f_lookAtRight";
}



const std::string Camera::getFViewport( void )
{
	return "f_viewport";
}



const std::string Camera::getFFovy( void )
{
	return "f_fovy";
}



const std::string Camera::getFMode( void )
{
	return "f_mode";
}



const std::string Camera::getFEyeSeparation( void )
{
	return "f_eyeSeparation";
}



const std::string Camera::getFImageShift( void )
{
	return "f_imageShift";
}



const std::string Camera::getFRightEye( void )
{
	return "f_rightEye";
}



const std::string Camera::getFScissor( void )
{
	return "f_scissor";
}



const std::string Camera::getFAspect( void )
{
	return "f_aspect";
}



const std::string Camera::getFZNear( void )
{
	return "f_zNear";
}



const std::string Camera::getFZFar( void )
{
	return "f_zFar";
}



const vgm::Vec3f Camera::applyViewport( const vgm::Vec3f& vertex )
{
	return applyViewport( getViewport(), vertex );
}



const vgm::Vec3f Camera::applyViewport( const vgm::Rectangle2i& viewport, const vgm::Vec3f& vertex )
{
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



// LOOKAT
const Camera::LookAtValueType Camera::getLookAt( const EyeUsagePolicyValueType eyeUsagePolicy ) const
{
	vgm::MatrixR matrix;

	// MONOSCOPIC
	if ( getMode() == MONOSCOPIC )
	{
		switch ( eyeUsagePolicy.value() )
		{
			case EYE_LEFT:
				matrix = getLookAtLeft();
				break;

			case EYE_RIGHT:
				matrix = getLookAtRight();
				break;

			case EYE_BOTH:
			{
				const Camera::LookAtValueType left	= getLookAtLeft();
				const Camera::LookAtValueType right	= getLookAtRight();

				vgAssertN( left.equals(right), "lookAtLeft != lookAtRight" );
				matrix = left;
				break;
			}

			//case DEFAULT_EYEUSAGEPOLICY: = EYE_BOTH
			default:
				vgAssertN( false, "Unexpected value for eye usage policy %i", eyeUsagePolicy );
				matrix.setIdentity();
		}
	}
	else
	// STEREOSCOPIC
	{
		const vgm::Vec3f halfEyeSeparation( getEyeSeparation() / 2.f, 0.f, 0.f );

		switch ( eyeUsagePolicy.value() )
		{
			case EYE_LEFT:
			{
				vgm::MatrixR eyeSeparation;
				eyeSeparation.setTranslate( halfEyeSeparation );
				matrix = getLookAtLeft();
				matrix = matrix * eyeSeparation;
				break;
			}

			case EYE_RIGHT:
			{
				vgm::MatrixR eyeSeparation;
				eyeSeparation.setTranslate( -halfEyeSeparation );
				matrix = getLookAtRight();
				matrix = matrix * eyeSeparation;
				break;
			}

			case EYE_BOTH:
			{
				vgAssertN( false, "EYE_BOTH not allowed in non MONOSCOPIC mode" );
				break;
			}

			//case DEFAULT_EYEUSAGEPOLICY: = EYE_BOTH
			default:
				vgAssertN( false, "Unexpected value for eye usage policy %i", eyeUsagePolicy );
				matrix.setIdentity();
		}
	}

	return matrix;
}



void Camera::setLookAt( const LookAtValueType value )
{
	setLookAtLeft( value );
	setLookAtRight( value );
}



// PROJECTION
const Camera::ProjectionValueType Camera::getProjection( const EyeUsagePolicyValueType eyeUsagePolicy ) const
{
	vgm::MatrixR matrix;

	switch ( eyeUsagePolicy.value() )
	{
		case EYE_LEFT:
			matrix = getProjectionLeft();
			break;

		case EYE_RIGHT:
			matrix = getProjectionRight();
			break;

		case EYE_BOTH:
		{
			const Camera::ProjectionValueType left	= getProjectionLeft();
			const Camera::ProjectionValueType right	= getProjectionRight();

			vgAssertN( left.equals(right), "projectionLeft != projectionRight" );

			matrix = left;
			break;
		}

		default:
			vgAssertN( false, "Unexpected value for eye usage policy %i", eyeUsagePolicy );
			matrix.setIdentity();
	}

	return matrix;
}



void Camera::setProjection( const ProjectionValueType value )
{
	setProjectionLeft( value );
	setProjectionRight( value );
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



// High-level
void Camera::gethViewport( ViewportValueType& viewport, const int drawingSurfaceWidth, const EyeUsagePolicyValueType eyeUsagePolicy ) const
{
	// Retrieves viewport field
	viewport = getViewport();

	const float drawingSurfaceWidthf = static_cast< float >( drawingSurfaceWidth );

	const float halfImageShift = (drawingSurfaceWidthf/16.f) * getImageShift()/100.f;

	switch ( eyeUsagePolicy.value() )
	{
		case EYE_LEFT:
			viewport[0] -= static_cast< int >( halfImageShift );
			break;

		case EYE_RIGHT:
			viewport[0] += static_cast< int >( halfImageShift );
			break;

		case EYE_BOTH:
			// Nothing to do
			break;

		default:
			vgAssertN( false, "Unexpected value for eye usage policy %i", eyeUsagePolicy );
	}
}


void Camera::sethFovy( const FovyValueType fovy)
{
	Camera::AspectValueType aspect;
	Camera::ZNearValueType zNear;
	Camera::ZFarValueType zFar;

	setFovy( fovy );

	if ( getAspect( aspect ) && getZNear( zNear ) && getZFar( zFar ) )
	{
		vgm::MatrixR matrix;
		matrix.setPerspective( fovy, aspect, zNear, zFar );
		setProjection( matrix );
	}
	else
	{
		vgAssertN( false, "sethFovy() called before zNear, zFar and aspect have been initialized.");
	}
}
IMPLEMENT_INDEXABLE_CLASS_CPP( , Camera );



const vgd::basic::RegisterNode<Camera> Camera::m_registrationInstance;



} // namespace node

} // namespace vgd

