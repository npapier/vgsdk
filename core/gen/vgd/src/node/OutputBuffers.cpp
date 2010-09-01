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
