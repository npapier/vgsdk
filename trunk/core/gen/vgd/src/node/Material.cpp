// Transparency
const Material::TransparencyValueType Material::getTransparency() const
{
	return getOpacity();
}



void Material::setTransparency( const TransparencyValueType value )
{
	setOpacity( value );
}



// Color
bool Material::getColor( const ColorParameterType param, ColorValueType& value ) const
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
	else if ( param == EMISSION )
	{
		return getEmission( value );
	}
	else
	{
		assert( false );
		return false;
	}
}



void Material::setColor( const ColorParameterType param, ColorValueType value )
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
	else if ( param == EMISSION )
	{
		setEmission( value );
	}
	else
	{
		assert( false );
	}
}



void Material::eraseColor( const ColorParameterType param )
{
	if ( param == AMBIENT )
	{
		eraseAmbient();
	}
	else if ( param == DIFFUSE )
	{
		eraseDiffuse();
	}
	else if ( param == SPECULAR )
	{
		eraseSpecular();
	}
	else if ( param == EMISSION )
	{
		eraseEmission();
	}
	else
	{
		assert( false );
	}
}
