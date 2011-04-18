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
	 * @return vertex transformed
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
	 * @brief Gets the value of field named \c lookAtLeft.
	 */
	const LookAtValueType getLookAt() const;

	/**
	 * @brief Sets the value of field named \c lookAtLeft.
	 */
	void setLookAt( const LookAtValueType value );



	typedef ProjectionLeftValueType ProjectionValueType;

	/**
	 * @brief Gets the value of field named \c projectionLeft.
	 */
	const ProjectionValueType getProjection() const;

	/**
	 * @brief Sets the value of field named \c projectionLeft.
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
