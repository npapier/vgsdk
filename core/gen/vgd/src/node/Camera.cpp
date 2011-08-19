const vgm::Vec3f Camera::applyViewport( const vgm::Vec3f& vertex )
{
	assert( hasViewport() );

	vgm::Rectangle2i viewport;
	getViewport( viewport );

	return applyViewport( viewport, vertex );
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

	return matrix;
}



void Camera::setLookAt( const LookAtValueType value )
{
	if ( getMode() == MONOSCOPIC )
	{
		setLookAtLeft( value );
		setLookAtRight( value );
	}
	else
	{
		const vgm::Vec3f halfEyeSeparation( getEyeSeparation() / 2.f, 0.f, 0.f );

		// LEFT
		vgm::MatrixR lookAtLeft;
		lookAtLeft.setTranslate( - halfEyeSeparation );
		lookAtLeft = value * lookAtLeft;

		setLookAtLeft( lookAtLeft );

		// RIGHT
		vgm::MatrixR lookAtRight;
		lookAtRight.setTranslate( halfEyeSeparation );
		lookAtRight = value * lookAtRight;

		setLookAtRight( lookAtRight );
	}
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
/*	if ( getMode() == MONOSCOPIC )
	{*/
		setProjectionLeft( value );
		setProjectionRight( value );
/*	}
	else
	{
		const vgm::Vec3f halfEyeSeparation( getEyeSeparation() / 2.f, 0.f, 0.f );

		// LEFT
		vgm::MatrixR projectionLeft;
		projectionLeft.setTranslate( - halfEyeSeparation );
		projectionLeft = value * projectionLeft;

		setProjectionLeft( projectionLeft );

		// RIGHT
		vgm::MatrixR projectionRight;
		projectionRight.setTranslate( halfEyeSeparation );
		projectionRight = value * projectionRight;

		setProjectionRight( projectionRight );
	}*/
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
const bool Camera::gethViewport( ViewportValueType& viewport, const int drawingSurfaceWidth, const EyeUsagePolicyValueType eyeUsagePolicy ) const
{
	// Retrieves viewport field
	bool hasViewport = getViewport( viewport );

	if ( hasViewport )
	{
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

		return true;
	}
	else
	{
		return false;
	}
}

/*void Camera::sethLookAtLeftAndRight( const vgm::Vec3f lookAtEye, const vgm::Vec3f lookAtCenter, const vgm::Vec3f lookAtUp, const float eyeSeparation )
{
	vgm::MatrixR lookAt;
	lookAt.setLookAt( lookAtEye, lookAtCenter, lookAtUp );

	const vgm::Vec3f halfEyeSeparation( eyeSeparation / 2.f, 0.f, 0.f );

	// LEFT
	vgm::MatrixR lookAtLeft;
	lookAtLeft.setTranslate( - halfEyeSeparation );
	lookAtLeft = lookAt * lookAtLeft;

	setLookAtLeft( lookAtLeft );

	// RIGHT
	vgm::MatrixR lookAtRight;
	lookAtRight.setTranslate( halfEyeSeparation );
	lookAtRight = lookAt * lookAtRight;

	setLookAtRight( lookAtRight );
}
*/

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
}
