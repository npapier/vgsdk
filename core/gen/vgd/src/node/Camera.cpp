const vgm::Vec3f Camera::applyViewport( const vgm::Vec3f& vertex )
{
	vgAssert( hasViewport() );

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
