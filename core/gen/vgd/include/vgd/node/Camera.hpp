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
	 */
	const vgm::Vec3f applyViewport( const vgm::Vec3f& vertex );

	/**
	 * @brief Apply the viewport transformation (as defined in OpenGL specification) to a vertex.
	 *
	 * @param viewport	the viewport used to compute the transformation
	 * @param vertex	vertex to transform
	 * @return the transformed vertex
	 */
	static const vgm::Vec3f applyViewport( const vgm::Rectangle2i& viewport, const vgm::Vec3f& vertex );

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
	void gethViewport( ViewportValueType& value, const int drawingSurfaceWidth, const EyeUsagePolicyValueType eyeUsagePolicy =  EyeUsagePolicyValueType(EYE_BOTH) ) const;


	/**
	 * @brief Sets the value of the field named \c fovy and recompute the projection matrix using the value of aspect zNear and zFar optional fields if they are presents.
	 * Otherwise, only sets the fovy field.
	 */
	void sethFovy( const FovyValueType fovy);

	//@}
