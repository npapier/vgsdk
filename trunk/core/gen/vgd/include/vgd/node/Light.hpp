	/**
	 * @name Accessors to field color
	 *
	 * This accessors emulates the old interface of the field color using the new fields (ambient, diffuse and specular).
	 */
	//@{

	/**
	 * @brief Enumeration of the \c color parameter.
	 */
	typedef enum
	{
		AMBIENT = 1,
		DIFFUSE,
		SPECULAR,
	} ColorParameterType;

	/**
	 * @brief Typedef for the \c color parameter value.
	 */
	typedef vgm::Vec4f  ColorValueType;

	/**
	 * @brief Typedef for the \c color field.
	 */
	typedef vgd::field::TPairAssociativeField< int /*ColorParameterType*/, ColorValueType > FColorType;

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
vgDEPRECATED( 	void 			eraseColor( const ColorParameterType param ) );
	//@}
