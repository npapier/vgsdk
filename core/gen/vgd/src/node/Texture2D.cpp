const uint32 Texture2D::gethTextureDimension() const
{
	return 2;
}


void Texture2D::sethDefaults()
{
	sethFunction( FUN_REPLACE );
	setWrapS( CLAMP );
	setWrapT( CLAMP );
	setMinFilter( LINEAR );
	setMagFilter( LINEAR );
}
