	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		SHININESS,
		EMISSION,
		SPECULAR,
		AMBIENT,
		DIFFUSE
	};



	/**
	 * @name Accessors to field color
	 *
	 * This accessors emulates the old interface of the field color using the new fields.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c color parameter.
	 */
	typedef int /*vgd::field::EnumType*/ ColorParameterType;

	/**
	 * @brief Typedef for the \c color parameter value.
	 */
	typedef vgm::Vec3f  ColorValueType;

	/**
	 * @brief Gets the \c color value.
	 */
	vgDEPRECATED( bool			getColor( const ColorParameterType param, ColorValueType& value ) const );

	/**
	 * @brief Sets the \c color value.
	 */
	vgDEPRECATED( void 			setColor( const ColorParameterType param, ColorValueType value ) );

	/**
	 * @brief Erase the \c color value.
	 */
	vgDEPRECATED( void 			eraseColor( const ColorParameterType param ) );
	//@}
