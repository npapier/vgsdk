namespace
{

const bool isAnUniformName( const std::string& name )
{
	const bool retVal = (name.size()>=2) && (name[0] == 'u') && (name[1] >= 'A') && (name[1] <= 'Z');
	return retVal;
}

}


void Uniforms::clearUniforms()
{
	std::vector< std::string > fieldNames;
	getFieldNames(fieldNames);

	for( auto	i		= fieldNames.begin(),
				iEnd	= fieldNames.end();
		i != iEnd;
		++i )
	{
		const std::string& fieldName = *i;
		if ( isAnUniformName(fieldName) )
		{
			// This is the name of an uniform variable, so remove it
			removeField( fieldName );
		}
		// else not a field containing an uniform, so do nothing
	}
}


const bool Uniforms::removeUniform( const std::string& name )
{
	if ( isAnUniformName(name) )
	{
		removeField(name);
		return true;
	}
	else
	{
		return false;
	}
}


const bool Uniforms::isUniform( const std::string& name ) const
{
	return isAnUniformName(name) && isField( name );
}
