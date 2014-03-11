const uint32 Texture2D::gethTextureDimension() const
{
	return 2;
}


void Texture2D::sethDefaults()
{
	sethFunction( FUN_REPLACE );
	setWrap( WRAP_S, CLAMP );
	setWrap( WRAP_T, CLAMP );
	setFilter( MIN_FILTER, LINEAR );
	setFilter( MAG_FILTER, LINEAR );
}
