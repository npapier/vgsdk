// VGSDK - Copyright (C) 2008, 2009, 2011, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgio/operators.hpp"

#include <vgd/Wkp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/VertexShape.hpp>
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


std::ostream & operator << ( std::ostream & os, const vgd::node::Primitive::Type & primitiveType )
{
	switch( primitiveType )
	{
	case vgd::node::Primitive::NONE:			os << "NONE"; break;
	case vgd::node::Primitive::POINTS:			os << "POINTS"; break;
	case vgd::node::Primitive::LINES:			os << "LINES"; break;
	case vgd::node::Primitive::LINE_STRIP:		os << "LINE_STRIP"; break;
	case vgd::node::Primitive::LINE_LOOP:		os << "LINE_LOOP"; break;
	case vgd::node::Primitive::TRIANGLES:		os << "TRIANGLES"; break;
	case vgd::node::Primitive::TRIANGLE_STRIP:	os << "TRIANGE_STRIP"; break;
	case vgd::node::Primitive::TRIANGLE_FAN:	os << "TRIANGLE_FAN"; break;
	case vgd::node::Primitive::QUADS:			os << "QUADS"; break;
	case vgd::node::Primitive::QUAD_STRIP:		os << "QUAD_STRIP"; break;
	case vgd::node::Primitive::POLYGON:			os << "POLYGON"; break;
	default:									os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::VertexShape::PrimitiveValueType & primitiveValue )
{
	return ( os << primitiveValue.getType() << "(" << primitiveValue.getIndex() << "," << primitiveValue.getNumIndices() << ")" );
}



std::ostream & operator << ( std::ostream & os, const vgd::node::Binding & bindingValue )
{
	switch( bindingValue.value() )
	{
		case vgd::node::BIND_OFF:				os << "BIND_OFF"; break;
		//case vgd::node::BIND_OVERALL:			os << "BIND_OVERALL"; break;
		//case vgd::node::BIND_PER_PRIMITIVE:		os << "BIND_PER_PRIMITIVE"; break;
		case vgd::node::BIND_PER_VERTEX:		os << "BIND_PER_VERTEX"; break;
		default:								os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::Shp< vgd::basic::IImage > & iimage )
{
	if ( iimage )
	{
		os << *iimage;
	}
	else
	{
		os << "empty";
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

std::ostream & operator << ( std::ostream & os, const vgd::Shp< vgd::node::Texture2D > & node )
{
	os << node->getName();

	return os;
}

std::ostream & operator << ( std::ostream & os, const vgd::Shp< vgd::node::VertexShape > & node )
{
	os << node->getName();

	return os;
}

std::ostream & operator << ( std::ostream & os, const vgd::Wkp< vgd::node::Node > & node )
{
	vgd::Shp< vgd::node::Node > nodeShp = node.lock();
	if ( nodeShp )
	{
		os << nodeShp->getName();
	}
	else
	{
		os << "-";
	}
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



std::ostream & operator << ( std::ostream & os, const vgm::Plane & plane )
{
	const vgm::Vec3f&	normal		= plane.getNormal();
	const float			distance	= plane.getDistanceFromOrigin();

	os << "normal: " << normal << std::endl << "distance: " << distance;

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::basic::IImage & iimage )
{
	os << "(" << iimage.width() << "x" << iimage.height() << "x" << iimage.depth() << ", ";
	os << vgd::basic::IImage::toString(iimage.format()) << ", ";
	os << vgd::basic::IImage::toString(iimage.type());
	os << ")" << std::endl;

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::field::Enum & enumValue )
{
	os << enumValue.str();

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
