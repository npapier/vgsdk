const uint32 Texture1D::gethTextureDimension() const
{
	return 1;
}


void Texture1D::sethDefaults()
{
	sethFunction( FUN_REPLACE );
	setWrap( WRAP_S, CLAMP );
	setFilter( MIN_FILTER, LINEAR );
	setFilter( MAG_FILTER, LINEAR );
}
