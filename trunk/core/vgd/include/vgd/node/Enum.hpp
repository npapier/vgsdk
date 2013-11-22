// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ENUM_HPP
#define _VGD_NODE_ENUM_HPP



#include "vgd/field/Enum.hpp"

namespace vgd
{

namespace node
{



	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		BIND_PER_VERTEX = 257,	///< One attribute per vertex
		BIND_OFF = 256,	///< No attribute at all
		DEFAULT_ = BIND_OFF	///< No attribute at all
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct Binding : public vgd::field::Enum
	{
		Binding()
		{}

		Binding( const int v )
		: vgd::field::Enum(v)
		{}

		Binding( const Binding& o )
		: vgd::field::Enum(o)
		{}

		Binding( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 256 );
			retVal.push_back( 257 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "BIND_OFF" );
			retVal.push_back( "BIND_PER_VERTEX" );

			return retVal;
		}
	};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ENUM_HPP
