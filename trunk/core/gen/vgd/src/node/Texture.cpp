// FUNCTION
void Texture::sethFunction( OldFunctionValueType value )
{
	const std::string strIndex = vgd::basic::toString( getMultiAttributeIndex() );

	if ( value == FUN_REPLACE )
	{
		std::string function = "color = texture(texMap2D[" + strIndex + "], mgl_TexCoord[" + strIndex + "].xy);\n";
//		std::string function = "color = texture(texMap2D[" + strIndex + "], gl_TexCoord[" + strIndex + "].xy);\n";
		setFunction( function );
	}
	else if ( value == FUN_MODULATE )
	{
		std::string function = "color *= texture(texMap2D[" + strIndex + "], mgl_TexCoord[" + strIndex + "].xy);\n";
//		std::string function = "color *= texture(texMap2D[" + strIndex + "], gl_TexCoord[" + strIndex + "].xy);\n";
		setFunction( function );
	}
	else
	{
		assert( false );
	}
}
