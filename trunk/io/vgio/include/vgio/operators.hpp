// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGIO_OPERATORS_HPP_
#define _VGIO_OPERATORS_HPP_

#include <ostream>

#include <vgm/Matrix.hpp>
#include <vgm/Vector.hpp>

#include <vgd/field/TMultiField.hpp>
#include <vgd/field/TPairAssociativeField.hpp>
#include <vgd/field/TSingleField.hpp>

#include <vgd/node/Light.hpp>
#include <vgd/node/Material.hpp>

#include "vgio/vgio.hpp"




/**
 * @brief	Writes into an output stream the textual representation of the light nodes on parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, vgd::node::Light::OnParameterType & on );



/**
 * @brief	Writes into an output stream the textual representation of the material nodes color parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::Material::ColorParameterType & colorParameter );



/**
 * @brief	Writes into an output stream the textual representation of the material nodes shininess parameter.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgd::node::Material::ShininessParameterType & shininessParameter );



/**
 * @brief	Writes into an output stream the given matrix.
 */
VGIO_API std::ostream & operator << ( std::ostream & os, const vgm::MatrixR & matrix );



/**
 * @brief	Writes into an output stream the given vector.
 */
template< typename T, int N >
std::ostream & operator << ( std::ostream & os, const vgm::Vector< T, N > & vector )
{
	os << "(";
	for( unsigned int i = 0; i < vector.getSize(); ++i )
	{
		os << vector[i];
		if( i != vector.getSize() - 1 )
		{
			os << ", ";
		}
	}
	os << ")";
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
 * @brief	Writes into an output stream the given multi-field.
 */
template< typename T >
std::ostream & operator << ( std::ostream & os, const vgd::field::TMultiField< T > & field )
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

	return os;
}



/**
 * @brief	Writes into an output stream the given pait associative field.
 */
template< typename K, typename D >
std::ostream & operator << ( std::ostream & os, const vgd::field::TPairAssociativeField< K, D > & field )
{
	using namespace vgd::field;

	TPairAssociativeField< K, D >::const_iterator	i;

	for( i = field.begin(); i != field.end(); ++i )
	{
		if( i != field.begin() )
		{
			os << std::endl;
		}
		os << i->first << ": " << i->second;
	}
	return os;
}



/**
 * @brief	Writes into an output stream the field of type @c T managed by the given editor.
 */
template< typename T >
std::ostream & operator << ( std::ostream & os, const vgd::field::EditorRO< T > & editor )
{
	os << *editor;
	return os;
}



#endif /*_VGIO_OPERATORS_HPP_*/
