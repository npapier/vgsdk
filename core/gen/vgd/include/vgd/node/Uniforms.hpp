	/**
	 * @name Uniforms accessors
	 */
	//@{

	/**
	 * @brief Removes all uniform variables
	 */
	void clearUniforms();


	/**
	 * @brief Sets the value of an uniform variable
	 *
	 * If isUniform(name) is false, then it creates a new single field containing the given value. Otherwise it modifies the value of the variable.
	 *
	 * @param name		name of the uniform variable. Have to start with 'u' and followed by an upper case letter (ex. uPosition).
	 * @param value		value of the uniform variable. See vgd::field::UniformValue for an exhaustive list of supported type.
	 *
	 * @todo Test if T is a supported type
	 */
	template< typename T >
	void setUniform( const std::string& name, const T& value )
	{
		vgAssertN( name[0] == 'u', "The given name '%s' have to start with 'u'", name.c_str() );
		vgAssertN( name.size()>=2, "The size of the given name '%s' have to be at least 2.", name.c_str() );
		vgAssertN( (name[1] >= 'A') && (name[1] <= 'Z'), "The second character of the given name '%s' have to be an upper case letter", name.c_str() );

		if ( !isUniform(name) )
		{
			// Non existing uniform variable
			addField( new vgd::field::TSingleField< T >(name) );

			addDirtyFlag( "df_" + name );

			link( name, name );
			link( name, getDFNode() );
		}

		// Changes the value of the uniform variable
		vgAssertN( getFieldType(name) == typeid(vgd::field::TSingleField<T>), "Try to set the uniform named '%s' with a new type '%s' instead of '%s'.", name.c_str(), typeid(vgd::field::TSingleField<T>).name(), getFieldType(name).name() );
		vgd::field::EditorRW< vgd::field::TSingleField<T> > uniform = getFieldRW< vgd::field::TSingleField<T> >( name );
		uniform->setValue( value );
	}


	/**
	 * @brief Returns the value of an uniform variable.
	 *
	 * @pre isUniform(name)
	 * @param name		name of the uniform variable.
	 *
	 * @return the value of the desired uniform variable.
	 */
	template< typename T >
	const T& getUniform( const std::string& name ) const
	{
		vgAssertN( getFieldType(name) == typeid(vgd::field::TSingleField<T>), "Try to get the uniform named '%s' with the wrong type '%s' instead of '%s'.", name.c_str(), typeid(vgd::field::TSingleField<T>).name(), getFieldType(name).name() );
		vgd::field::EditorRO< vgd::field::TSingleField<T> > uniform = getFieldRO< vgd::field::TSingleField<T> >( name );
		const T& value = uniform->getValue();
		return value;
	}


	/**
	 * @brief Remove an uniform variable
	 *
	 * @pre isAnUniformName(name)
	 *
	 * @param name		name of the variable to remove
	 * @return true if successfully removed, false otherwise
	 */
	const bool removeUniform( const std::string& name );


	/**
	 * @brief Tests if an uniform variable exists
	 *
	 * Tests if a field with the given name contains an uniform variable.
	 *
	 * @param name		name of the uniform variable
	 *
	 * @return true if the variable exists, false otherwise
	 */
	const bool isUniform( const std::string& name ) const;
	//@}
