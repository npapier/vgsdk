// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGIO_OPERATORS_HPP
#define _VGIO_OPERATORS_HPP

#include <ostream>
#include <sstream>

#include <vgm/Box.hpp>
#include <vgm/Matrix.hpp>
#include <vgm/Plane.hpp>
#include <vgm/Vector.hpp>

#include <vgd/field/Enum.hpp>
#include <vgd/field/TMultiField.hpp>
#include <vgd/field/TOptionalField.hpp>
#include <vgd/field/TPairAssociativeField.hpp>
#include <vgd/field/TSingleField.hpp>

#include <vgd/node/Camera.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/Light.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Primitive.hpp>
#include <vgd/node/VertexShape.hpp>

#include "vgio/vgio.hpp"

namespace vgd { namespace node { struct Group; } }



namespace vgio
{

/**
 * @brief Configures the ostream
 *
 * Sets boolalpha and precision of 3
 */
VGIO_API void configure( std::ostream & os );

}



/**
 * @brief	Writes into an output stream the textual representation of the draw style nodes bounding box parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::BoundingBoxParameterType & boundingBoxParameter );



/**
 * @brief	Writes into an output stream the textual representation of the draw style nodes bounding box parameter value.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::BoundingBoxValueType & boundingBoxValue );



/**
 * @brief	Writes into an output stream the textual representation of the draw style nodes normal length parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::NormalLengthParameterType & normalLengthParameter );



/**
 * @brief	Writes into an output stream the textual representation of the draw style nodes shape parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::ShapeParameterType & shapeParameter );



/**
 * @brief	Writes into an output stream the textual representation of the draw style nodes shape parameter value.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::ShapeValueType & shapeValue );



/**
 * @brief	Writes into an output stream the textual representation of the draw style nodes show orientation parameter type.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::DrawStyle::ShowOrientationParameterType & showOrientationParameter );



/**
 * @brief	Writes into an output stream the textual representation of the light nodes on parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::Light::OnParameterType & on );



/**
 * @brief	Writes into an output stream the textual representation of the light model nodes ambient parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::AmbientParameterType & ambient );



/**
 * @brief	Writes into an output stream the textual representation of the light model nodes model parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::ModelParameterType & model );



/**
 * @brief	Writes into an output stream the textual representation of the light model nodes two-sided parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::TwoSidedParameterType & twoSided );



/**
 * @brief	Writes into an output stream the textual representation of the light model nodes model value.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::ModelValueType & value );



/**
 * @brief	Writes into an output stream the textual representation of the light model nodes viewer parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::ViewerParameterType & viewer );



/**
 * @brief	Writes into an output stream the textual representation of the light model nodes viewer value.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::LightModel::ViewerValueType & value );



/**
 * @brief	Writes into an output stream the textual representation of the primitive type.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::Primitive::Type & primitiveType );



/**
 * @brief	Writes into an output stream the textual representation of the primitive value type.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::VertexShape::PrimitiveValueType & primitiveValue );



/**
 * @brief	Writes into an output stream the field of type @c T managed by the given editor.
 */
template< typename T >
std::ostream & operator << ( std::ostream & os, const vgd::field::EditorRO< T > & editor )
{
	vgio::configure(os);

	os << *editor;

	return os;
}



/**
 * @brief	Writes into an output stream the field of type @c T managed by the given editor.
 */
template< typename T >
std::ostream & operator << ( std::ostream & os, const vgd::field::EditorRW< T > & editor )
{
	vgio::configure(os);

	os << *editor;

	return os;
}



/**
 * @brief	Writes into an output stream the given multi-field.
 */
template< typename T >
std::ostream & operator << ( std::ostream & os, const vgd::field::TMultiField< T > & field )
{
	if ( field.size() == 0 )
	{
		os << "empty";
	}
	else
	{
		static const uint	limit = 3;
		const uint			end = field.size() > limit ? limit : field.size();

		for( uint i = 0; i != end; ++i )
		{
			os << field[i];
			if( i != end - 1 )
			{
				os << ", ";
			}
		}

		if( field.size() > limit )
		{
			os << ", ...";
		}
	}

	return os;
}



/**
 * @brief	Writes into an output stream the given pair associative field.
 */
template< typename K, typename D >
std::ostream & operator << ( std::ostream & os, const vgd::field::TPairAssociativeField< K, D > & field )
{
	if ( field.size() == 0 )
	{
		os << "empty";
	}
	else
	{
		typename vgd::field::TPairAssociativeField< K, D >::const_iterator	i;

		for( i = field.begin(); i != field.end(); ++i )
		{
			if( i != field.begin() )
			{
				os << std::endl;
			}
			os << i->first << " : " << i->second;
		}
	}

	return os;
}



/**
 * @brief	Writes into an output stream the given single associative field.
 */
template< typename K >
std::ostream & operator << ( std::ostream & os, const vgd::field::TSingleAssociativeField< K > & field )
{
	if ( field.size() == 0 )
	{
		os << "empty";
	}
	else
	{
		typename vgd::field::TSingleAssociativeField< K >::const_iterator	i;

		for( i = field.begin(); i != field.end(); ++i )
		{
			if( i != field.begin() )
			{
				os << std::endl;
			}
			os << *i << " ";
		}
	}

	return os;
}



/**
 * @brief	Writes into an output stream the given single field
 */
template< typename T >
std::ostream & operator << ( std::ostream & os, const vgd::field::TSingleField< T > & field )
{
	os << field.getValue();
	return os;
}




/**
 * @brief	Writes into an output stream the given optional field
 */
template< typename T >
std::ostream & operator << ( std::ostream & os, const vgd::field::TOptionalField< T > & field )
{
	if ( field.hasValue() )
	{
		T value;
		field.getValue( value );
		os << value;
	}
	else
	{
		os << "empty";
	}

	return os;
}



/**
 * @brief	Writes into an output stream the given node.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::Shp< vgd::node::Group > & node );



/**
 * @brief	Writes into an output stream the given node.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::Shp< vgd::node::Node > & node );



/**
 * @brief	Writes into an output stream the box.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgm::Box3f & box );



/**
 * @brief	Writes into an output stream the box.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgm::XfBox3f & box );



/**
 * @brief	Writes into an output stream the given matrix.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgm::MatrixR & matrix );



/**
 * @brief	Writes into an output stream the given rectangle.
 */
template< typename T >
std::ostream & operator << ( std::ostream & os, const vgm::Rectangle< T > & rect )
{
	if ( rect.isInvalid() )
	{
		os << "invalid";
	}
	else
	{
		os << "(" << rect[0] << ", " << rect[1] << ", " << rect[2] << ", " << rect[3] << ")";
	}

	return os;
}



/**
 * @brief	Writes into an output stream the given rotation.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgm::Rotation & rotation );



/**
 * @brief	Writes into an output stream the given vector.
 */
template< typename T, int N >
std::ostream & operator << ( std::ostream & os, const vgm::Vector< T, N > & vector )
{
	if ( vector.isInvalid() )
	{
		os << "invalid";
	}
	else if ( vector.isNull() )
	{
		os << "null";
	}
	else
	{
		os << "(";
		for( uint i = 0; i < vector.getSize(); ++i )
		{
			os << vector[i];
			if( i != vector.getSize() - 1 )
			{
				os << ", ";
			}
		}
		os << ")";
	}

	return os;
}



/**
 * @brief	Writes into an output stream the given plane.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgm::Plane & plane );



/**
 * @brief	Writes into an output stream the given enumeration.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::field::Enum & enumValue );



/**
 * @brief	Writes into an output stream the integer.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const int8 & integer );

/**
 * @brief	Writes into an output stream the integer.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const uint8 & integer );



/**
 * @brief	Appends to string anything that has a serialization operator.
 */
template< typename T >
std::string & operator << ( std::string & buffer, const T & value )
{
	std::ostringstream	os;

	os << value;
	buffer += os.str();

	return buffer;
}


/**
 * @brief	Serializes a given object to a string.
 */
template< typename T >
const std::string toString( const T & value )
{
	std::string	buffer;
	buffer << value;

	return buffer;
}



#endif // #ifndef _VGIO_OPERATORS_HPP
