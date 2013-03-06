// VGSDK - Copyright (C) 2004-2006, 2009, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgm/Vector.hpp"


namespace vgm
{



glm::vec2 glm( const vgm::Vec2f& v )
{
	glm::vec2 retVal( v[0], v[1] );
	return retVal;
}

glm::vec3 glm( const vgm::Vec3f& v )
{
	glm::vec3 retVal( v[0], v[1], v[2] );
	return retVal;
}

glm::vec4 glm( const vgm::Vec4f& v )
{
	glm::vec4 retVal( v[0], v[1], v[2], v[3] ); 
	return retVal;
}


} // namespace vgm
