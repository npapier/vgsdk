


	bool computeBoundingBox( const vgm::MatrixR& transformation );	///< overridden method

	bool isBoundingBoxValid() const;								///< overridden method

	void invalidateBoundingBox( bool bInvalidate = true );			///< overridden method


	/**
	 *@name High-level accessors
	 */
	//@{

	/**
	 * @brief Sets default value for simulationPass0 and simulationPass1 fields.
	 */
	void sethSimulationPassToDefault();
	//@}
