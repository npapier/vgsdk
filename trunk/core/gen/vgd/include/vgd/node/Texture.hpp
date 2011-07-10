	/**
	 * @name Accessors to field functionFragment
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c functionFragment.
	 */
	typedef FragmentFunctionValueType FunctionValueType;

	/**
	 * @brief Type definition of the field named \c functionFragment
	 */
	typedef FFragmentFunctionType FFunctionType;

	/**
	 * @brief Gets the value of field named \c functionFragment.
	 */
	const bool getFunction( FunctionValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c functionFragment.
 	 */
	void setFunction( const FunctionValueType& value );

	/**
	 * @brief Erases the field named \c functionFragment.
	 */
	void eraseFunction();

	/**
	 * @brief Tests if the value of field named \c functionFragment has been initialized.
	 */
	const bool hasFunction() const;
	//@}



	/**
	 * @name High-level accessors
	 */
	//@{

	/**
	 * @brief Returns the dimension of this texture node.
	 * 
	 * @return dimension of this texture node
	 */
	virtual const uint32 gethTextureDimension() const=0;

	//@}



	/**
	 * @name Accessors to field function
	 *
	 * This accessors emulates the old interface of the field function.
	 */
	//@{

	/**
	 * brief Enumeration of the \c function parameters.
	 */
	/*typedef enum {
		FUNCTION
	} OldFunctionParameterType;*/

	/**
	 * @brief Typedef for the \c function value.
	 */
	typedef enum
	{
		FUN_REPLACE = 0,
		FUN_MODULATE, 
//		FUN_DECAL, 
//		FUN_BLEND, 

//		FUN_ADD,
//		FUN_COMBINE,

		DEFAULT_FUN = FUN_MODULATE
	} OldFunctionValueType;

	/**
	 * brief Typedef for the \c function field.
	 */	
	//typedef vgd::field::TPairAssociativeField< OldFunctionParameterType, OldFunctionValueType > FFunctionType;

	/**
	 * brief Gets the function value.
	 */
	//vgDEPRECATED( bool			gethFunction( OldFunctionValueType& value ) const );

	/**
	 * @brief Sets the function value.
	 */
	void 			sethFunction( OldFunctionValueType value );
	
	/**
	 * brief Erase the function value.
	 */
	//void 			eraseFunction();
	//@}
