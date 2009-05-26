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
	 * @pre getViewport(...) == true
	 */
	const vgm::Vec3f applyViewport( const vgm::Vec3f& vertex );
	//@}
