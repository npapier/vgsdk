// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgio/operators.hpp"

#include <vgd/node/Group.hpp>
#include <vgm/operations.hpp>
#include <vgm/Utilities.hpp>



namespace vgio
{

void configure( std::ostream & os )
{
	os << std::boolalpha;
	os.precision(3);
}

}



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



std::ostream & operator << ( std::ostream & os, const vgd::Shp< vgd::node::Group > & node )
{
	os << node->getName();

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::Shp< vgd::node::Node > & node )
{
	os << node->getName();

	return os;
}






std::ostream & operator << ( std::ostream & os, const vgm::Box3f & box )
{
	if ( box.isInvalid() )
	{
		os << "invalid";
	}
	else if ( box.isEmpty() )
	{
		os << "empty";
	}
	else
	{
		os << "min: "		<< box.getMin() << std::endl;
		os << "max: "		<< box.getMax() << std::endl;
		os << "center: "	<< box.getCenter() << std::endl;
		os << "size: "		<< box.getSize();
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgm::XfBox3f & box )
{
	if ( box.isInvalid() )
	{
		os << "invalid";
	}
	else if ( box.isEmpty() )
	{
		os << "empty";
	}
	else
	{
		// Projected box
		const vgm::Box3f	projectBox = box.project();

		os << "projectedBox {" << projectBox << "}" << std::endl;

		// Details on XfBox3f
		// box
		vgm::Vec3f min, max;
		box.getBounds( min, max );

		vgm::Box3f myBox( min, max );
		os << std::endl << "box {" << myBox << "}" << std::endl;

		// transformation
		const vgm::MatrixR& myMatrix = box.getTransform();
		os << std::endl << "transf: " << myMatrix;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgm::MatrixR & matrix )
{
	if ( matrix.isInvalid() )
	{
		os << "invalid";
	}
	else if ( matrix.isIdentity() )
	{
		os << "identity";
	}
	else
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
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgm::Rotation & rotation )
{
	const vgm::Rotation identity = vgm::Rotation::getIdentity();

	if ( rotation.equals( identity, vgm::Epsilon< float >::value() ) )
	{
		os << "identity";
	}
	else
	{
		// Retrieves axis and degree
		vgm::Vec3f	axis;
		float		radians;

		rotation.getValue( axis, radians);

		const float degrees = vgm::Utilities::rad2deg(radians);

		os << "( (" << axis[0] << ", " << axis[1] << ", " << axis[2] << "), " << degrees << ")";
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const int8 & integer )
{
	os << static_cast<int>(integer);

	return os;
}



std::ostream & operator << ( std::ostream & os, const uint8 & integer )
{
	os << static_cast<uint>(integer);

	return os;
}
