const uint32 Texture1D::gethTextureDimension() const
{
	return 1;
}


void Texture1D::sethDefaults()
{
	sethFunction( FUN_REPLACE );
	setWrapS( CLAMP );
	setMinFilter( LINEAR );
	setMagFilter( LINEAR );
}
