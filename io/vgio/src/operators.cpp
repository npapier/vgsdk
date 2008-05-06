// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgio/operators.hpp"



std::ostream & operator << ( std::ostream & os, vgd::node::Light::OnParameterType & on )
{
	switch( on )
	{
	case vgd::node::Light::ON:	os << "ON"; break;
	default:					os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::Material::ColorParameterType & colorParameter )
{
	switch( colorParameter )
	{
	case vgd::node::Material::AMBIENT:	os << "AMBIENT"; break;
	case vgd::node::Material::DIFFUSE:	os << "DIFFUSE"; break;
	case vgd::node::Material::SPECULAR:	os << "SPECULAR"; break;
	case vgd::node::Material::EMISSION:	os << "EMISSION"; break;
	default:							os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::Material::ShininessParameterType & shininessParameter )
{
	switch( shininessParameter )
	{
	case vgd::node::Material::SHININESS:	os << "SHININESS"; break;
	default:								os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgm::MatrixR & matrix )
{
	os << "{";
	for( uint i = 0; i < 4; ++i )
	{
		for( uint j = 0; j < 4; ++j )
		{
			os << matrix(i, j);
			if( j != 4-1 )
			{
				os << ", ";
			}
		}
		if( i != 4-1 )
		{
			os << std::endl;
		}
	}
	os << "}";
	return os;
}
