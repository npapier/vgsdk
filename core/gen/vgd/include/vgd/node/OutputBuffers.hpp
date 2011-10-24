	/**
	 * @name High-level methods
	 */
	//@{

	/**
	 * @brief Specifies which buffer must be used for rendering.
	 *
	 * @param which		index of output buffer. Default value -1 means no buffer.
	 */
	void setCurrent( const int which = -1 );


	/**
	 * @brief Specifies which buffers must be used for rendering.
	 *
	 * @param which0		index of first output buffer.
	 * @param which1		index of second output buffer.
	 */
	void setCurrent( const int which0, const int which1 );
	//@}
