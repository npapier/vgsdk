void OutputBuffers::setCurrent( const int which )
{
	using vgd::field::EditorRW;

	EditorRW< FCurrentType > current = getCurrentRW();
	current->clear();
	if ( which >= 0 )
	{
		current->push_back( which );
	}
	// else nothing to do
}


void OutputBuffers::setCurrent( const int which0, const int which1 )
{
	using vgd::field::EditorRW;

	EditorRW< FCurrentType > current = getCurrentRW();
	current->clear();
	if ( which0 >= 0 )
	{
		current->push_back( which0 );
	}
	// else nothing to do

	if ( which1 >= 0 )
	{
		current->push_back( which1 );
	}
	// else nothing to do
}
