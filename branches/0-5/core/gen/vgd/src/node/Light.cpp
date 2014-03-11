// COLOR
bool Light::getColor( const ColorParameterType param, ColorValueType& value ) const
{
	if ( param == AMBIENT )
	{
		return getAmbient( value );
	}
	else if ( param == DIFFUSE )
	{
		return getDiffuse( value );
	}
	else if ( param == SPECULAR )
	{
		return getSpecular( value );
	}
	else
	{
		assert( false );
		return false;
	}
}



void Light::setColor( const ColorParameterType param, ColorValueType value )
{
	if ( param == AMBIENT )
	{
		setAmbient( value );
	}
	else if ( param == DIFFUSE )
	{
		setDiffuse( value );
	}
	else if ( param == SPECULAR )
	{
		setSpecular( value );
	}
	else
	{
		assert( false );
	}
}



void Light::eraseColor( const ColorParameterType param )
{
	if ( param == AMBIENT )
	{
		return eraseAmbient();
	}
	else if ( param == DIFFUSE )
	{
		return eraseDiffuse();
	}
	else if ( param == SPECULAR )
	{
		return eraseSpecular();
	}
	else
	{
		assert( false );
	}
}
