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
	 * @name Accessors to field transparency
	 *
	 * This accessors emulates the old interface of the field transparency using the new field opacity.
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c transparency.
	 */
	typedef float TransparencyValueType;

	/**
	 * @brief Type definition of the field named \c transparency
	 */
	typedef vgd::field::SFFloat FTransparencyType;


	/**
	 * @brief Gets the value of field named \c transparency.
	 */
	vgDEPRECATED( const TransparencyValueType getTransparency() const );

	/**
	 * @brief Sets the value of field named \c transparency.
	 */
	vgDEPRECATED( void setTransparency( const TransparencyValueType value ) );

	//@}



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
