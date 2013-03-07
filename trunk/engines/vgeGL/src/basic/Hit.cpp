// VGSDK - Copyright (C) 2004, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/basic/Hit.hpp"



namespace vgeGL
{

namespace basic
{



Hit::Hit() :
    m_fMinDepthValue(1.f), m_fMaxDepthValue(0.f),
    m_vec3fMin( 0.f, 0.f, 0.f ),
    m_vec3fMinO( 0.f, 0.f, 0.f ),
    m_vec3fMinS( 0.f, 0.f, 0.f ),
    m_vec3fMax( 0.f, 0.f, 0.f )
{}



const float& Hit::minDepthValue() const
{
	return ( m_fMinDepthValue );
}



float& Hit::minDepthValue()
{
	return ( m_fMinDepthValue );
}



const float& Hit::maxDepthValue() const
{
	return ( m_fMaxDepthValue );
}



float& Hit::maxDepthValue()
{
	return ( m_fMaxDepthValue );
}



const std::list< GLuint >& Hit::stackName() const
{ 
	return ( m_listStackName );
}



std::list< GLuint >& Hit::stackName()
{ 
	return ( m_listStackName );
}



const vgm::Vec3f& Hit::nearestVertex() const
{
	return m_vec3fMin;
}

const vgm::Vec3f& Hit::nearestVertexO() const
{
	return m_vec3fMinO;
}

const vgm::Vec3f& Hit::nearestVertexS() const
{
	return m_vec3fMinS;
}


vgm::Vec3f& Hit::nearestVertex()
{
	return m_vec3fMin;
}

vgm::Vec3f& Hit::nearestVertexO()
{
	return m_vec3fMinO;
}

vgm::Vec3f& Hit::nearestVertexS()
{
	return m_vec3fMinS;
}


const vgm::Vec3f& Hit::farthestVertex() const
{
	return ( m_vec3fMax );
}



vgm::Vec3f& Hit::farthestVertex()
{
	return ( m_vec3fMax );
}



const vgd::node::PNodeList& Hit::stackNode() const
{
	return ( m_listStackNode ); 
}



vgd::node::PNodeList& Hit::stackNode()
{
	return ( m_listStackNode ); 
}



} // namespace basic

} // namespace vgeGL
