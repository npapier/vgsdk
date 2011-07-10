// Function
const bool Texture::getFunction( FunctionValueType& value ) const
{
	return getFragmentFunction( value );
}



void Texture::setFunction( const FunctionValueType& value )
{
	setFragmentFunction( value );
}



void Texture::eraseFunction()
{
	eraseFragmentFunction();
}


const bool Texture::hasFunction() const
{
	return hasFragmentFunction();
}


// High level accessor to FUNCTION
void Texture::sethFunction( OldFunctionValueType value )
{
	if ( value == FUN_REPLACE )
	{
		const std::string function = "color = texture(texMap2D[MAI], mgl_TexCoord[MAI].xy);\n";
		setFunction( function );
	}
	else if ( value == FUN_MODULATE )
	{
		const std::string function = "color *= texture(texMap2D[MAI], mgl_TexCoord[MAI].xy);\n";
		setFunction( function );
	}
	else
	{
		vgAssertN( false, "Not yet implemented" );
	}
}
