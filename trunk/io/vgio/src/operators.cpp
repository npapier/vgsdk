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



std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::BoundingBoxParameterType & boundingBoxParameter )
{
	switch(boundingBoxParameter)
	{
	case vgd::node::DrawStyle::BOUNDING_BOX:	os << "BOUNDING_BOX"; break;
	default:									os << "unsupported"; break;
	}
	
	return os;	
}



std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::BoundingBoxValueType & boundingBoxValue )
{
	switch(boundingBoxValue)
	{
	case vgd::node::DrawStyle::NO_BOUNDING_BOX:				os << "NO_BOUNDING_BOX"; break;
	case vgd::node::DrawStyle::OBJECT_SPACE:				os << "OBJECT_SPACE"; break;
	case vgd::node::DrawStyle::AA_OBJECT_SPACE:				os << "AA_OBJECT_SPACE"; break;
	case vgd::node::DrawStyle::OBJECT_AND_AA_OBJECT_SPACE:	os << "OBJECT_AND_AA_OBJECT_SPACE"; break;
	default:												os << "unsupported"; break;
	}
	
	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::NormalLengthParameterType & normalLengthParameter )
{
	switch(normalLengthParameter)
	{
	case vgd::node::DrawStyle::NORMAL_LENGTH:	os << "NORMAL_LENGTH"; break;
	default:									os << "unsupported"; break;
	}
	
	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::ShapeParameterType & shapeParameter )
{
	switch(shapeParameter)
	{
	case vgd::node::DrawStyle::SHAPE:	os << "SHAPE"; break;
	default:							os << "unsupported"; break;
	}
	
	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::ShapeValueType & shapeValue )
{
	switch(shapeValue)
	{
	case vgd::node::DrawStyle::NONE:				os << "NONE"; break;
	case vgd::node::DrawStyle::POINT:				os << "POINT"; break;
	case vgd::node::DrawStyle::FLAT:				os << "FLAT"; break;
	case vgd::node::DrawStyle::SMOOTH:				os << "SMOOTH"; break;
	case vgd::node::DrawStyle::WIREFRAME:			os << "WIREFRAME"; break;
	case vgd::node::DrawStyle::HIDDEN_LINE:			os << "HIDDEN_LINE"; break;
	case vgd::node::DrawStyle::FLAT_HIDDEN_LINE:	os << "FLAT_HIDDEN_LINE"; break;
	case vgd::node::DrawStyle::SMOOTH_HIDDEN_LINE:	os << "SMOOTH_HIDDEN_LINE"; break;
	case vgd::node::DrawStyle::NEIGHBOUR:			os << "NEIGHBOUR"; break;
	default:										os << "unsupported"; break;
	}
	
	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::ShowOrientationParameterType & showOrientationParameter )
{
	switch( showOrientationParameter )
	{
	case vgd::node::DrawStyle::SHOW_ORIENTATION:	os << "SHOW_ORIENTATION"; break;
	default:										os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::Light::OnParameterType & on )
{
	switch( on )
	{
	case vgd::node::Light::ON:	os << "ON"; break;
	default:					os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::AmbientParameterType & ambient )
{
	switch( ambient )
	{
	case vgd::node::LightModel::AMBIENT:	os << "AMBIENT"; break;
	default:								os << "unsupported"; break;
	}

	return os;
}




std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::ModelParameterType & model )
{
	switch( model )
	{
	case vgd::node::LightModel::MODEL:	os << "MODEL"; break;
	default:							os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::ModelValueType & value )
{
	switch( value )
	{
	case vgd::node::LightModel::LIGHTING_OFF:			os << "LIGHTING_OFF"; break;
	case vgd::node::LightModel::STANDARD_PER_VERTEX:	os << "STANDARD_PER_VERTEX"; break;
	case vgd::node::LightModel::STANDARD_PER_PIXEL:		os << "STANDARD_PER_PIXEL"; break;
	default:											os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::TwoSidedParameterType & twoSided )
{
	switch( twoSided )
	{
	case vgd::node::LightModel::TWO_SIDED:	os << "TWO_SIDED"; break;
	default:								os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::ViewerParameterType & viewer )
{
	switch( viewer )
	{
	case vgd::node::LightModel::VIEWER:	os << "VIEWER"; break;
	default:							os << "unsupported"; break;
	}

	return os;
}



std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::ViewerValueType & value )
{
	switch( value )
	{
	case vgd::node::LightModel::AT_INFINITY:	os << "AT_INFINITY"; break;
	case vgd::node::LightModel::AT_EYE:			os << "AT_EYE"; break;
	default:									os << "unsupported"; break;
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



std::ostream & operator << ( std::ostream & os, const vgd::node::VertexShape::PrimitiveValueType & primitiveValue )
{
	switch( primitiveValue.getType() )
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
