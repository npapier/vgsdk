	/**
	 * @name High-level methods
	 *
	 * @todo viewAll()
	 */
	//@{

	/**
	 * @brief Apply the viewport transformation (as defined in OpenGL specification) to a vertex.
	 *
	 * @param vertex	vertex to transform
	 * @return the transformed vertex
	 *
	 * @pre hasViewport()
	 */
	const vgm::Vec3f applyViewport( const vgm::Vec3f& vertex );
	//@}



	/**
	 * @name Helpers
	 */
	//@{

	typedef LookAtLeftValueType LookAtValueType;

	/**
	 * @brief Gets the value of field named \c lookAtLeft or \c lookAtRight depending of the given eye usage policy.
	 *
	 * @return	Returns \c lookAtLeft if eyeUsagePolicy is EYE_LEFT.
	 *			Returns \c lookAtRight if eyeUsagePolicy is EYE_RIGHT.
	 *			Returns \c lookAtLeft if eyeUsagePolicy is EYE_BOTH (but in this case, the precondition getLookAtLeft() == getLookAtRight() must be verified).
	 */
	const LookAtValueType getLookAt( const EyeUsagePolicyValueType eyeUsagePolicy = EyeUsagePolicyValueType(EYE_BOTH) ) const;

	/**
	 * @brief Sets the value of field named \c lookAtLeft and \c lookAtRight
	 */
	void setLookAt( const LookAtValueType value );



	typedef ProjectionLeftValueType ProjectionValueType;

	/**
	 * @brief Gets the value of field named \c projectionLeft or \c projectionRight depending of the given eye usage policy.
	 *
	 * @return	Returns \c projectionLeft if eyeUsagePolicy is EYE_LEFT.
	 *			Returns \c projectionRight if eyeUsagePolicy is EYE_RIGHT.
	 *			Returns \c projectionLeft if eyeUsagePolicy is EYE_BOTH (but in this case, the precondition getProjectionLeft() == getProjectionRight() must be verified).
	 */
	const ProjectionValueType getProjection( const EyeUsagePolicyValueType eyeUsagePolicy =  EyeUsagePolicyValueType(EYE_BOTH) ) const;

	/**
	 * @brief Sets the value of field named \c projectionLeft and \c projectionRight
	 *
	 * depends on \c mode field
	 * @todo doc
	 */
	void setProjection( const ProjectionValueType value );

	//@}



	/**
	 * @name Accessors to field matrix
	 * @deprecated
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c Matrix.
	 * @deprecated
	 */
	typedef vgm::MatrixR MatrixValueType;

	/**
	 * @brief Type definition of the field named \c matrix
	 * @deprecated
	 */
	typedef vgd::field::TSingleField< MatrixValueType > FMatrixType;


	/**
	 * @brief Gets the value of field named \c matrix.
	 * @deprecated
	 */
	vgDEPRECATED( const MatrixValueType getMatrix() const );

	/**
	 * @brief Sets the value of field named \c matrix.
	 * @deprecated
	 */
	vgDEPRECATED( void setMatrix( const MatrixValueType value ) );

	//@}



	/**
	 * @name High-level accessors
	 */
	//@{

	/**
	 * @brief Returns the value of field named \c viewport modified (if needed) by taking care of the given eye usage policy, the \c mode field and the \c imageShift field.
	 */
	const bool gethViewport( ViewportValueType& value, const int drawingSurfaceWidth, const EyeUsagePolicyValueType eyeUsagePolicy =  EyeUsagePolicyValueType(EYE_BOTH) ) const;

	/**
	 * brief Sets at once \c lookAtLeft and \c lookAtRight fields for stereoscopic rendering
	 *
	 * The first three parameters defines a 3D geometric transformation applied to monoscopic eye.
	 * The position of monoscopic eye is slightly shift along the X axis using \c eyeSeparation value to define left eye and right eye.
	 *
	 * param lookAtEye		the position of the eye point
	 * param lookAtCenter	the position of the reference point
	 * param lookAtUp		the direction of the up vector
	 * param eyeSeparation	the distance between the two eyes
	 */
	//void sethLookAtLeftAndRight( const vgm::Vec3f lookAtEye, const vgm::Vec3f lookAtCenter, const vgm::Vec3f lookAtUp, const float eyeSeparation );

	//@}
