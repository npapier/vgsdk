// VGSDK - Copyright (C) 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/basic/UniformContainer.hpp"

#include <boost/tuple/tuple.hpp>
#include <glo/GLSLProgram.hpp>
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace basic
{



namespace
{

/**
 * @brief Sets an OpenGL uniform variable
 */
struct UniformVisitor : public boost::static_visitor<>
{
	/**
	 * @brief Default constructor
	 *
	 * @param engine	engine used for rendering
	 */
	UniformVisitor( vgeGL::engine::Engine * engine )
	:	m_engine	( engine	)
	{}

	/**
	 * @brief Sets the name of the uniform variable that must be initialiazed
	 *
	 * @param name		name of uniform
	 */
	void setName( const std::string& name )
	{
		m_name = name;
	}

	/**
	 * @name OpenGL uniform variable setters
	 */
	//@{

	void operator() ( float value ) const
	{
		m_engine->getCurrentProgram()->setUniform1f( m_name, value );
	}

	void operator() ( vgm::Vec2f value ) const
	{
		m_engine->getCurrentProgram()->setUniform2fv( m_name, value.getValue() );
	}

	void operator() ( vgm::Vec3f value ) const
	{
		m_engine->getCurrentProgram()->setUniform3fv( m_name, value.getValue() );
	}

	void operator() ( vgm::Vec4f value ) const
	{
		m_engine->getCurrentProgram()->setUniform4fv( m_name, value.getValue() );
	}

	void operator() ( vgm::MatrixR value ) const
	{
		m_engine->getCurrentProgram()->setUniformMatrix4fv( m_name, reinterpret_cast< GLfloat * >(value.getValue()) );
	}
	//@}

private:
	vgeGL::engine::Engine * m_engine;	///< engine used for rendering
	std::string				m_name;		///< name of uniform
};

}



void UniformContainer::apply( vgeGL::engine::Engine * engine )
{
	UniformVisitor visitor( engine );
	ConstIteratorType i, iEnd;
	for(	boost::tie( i, iEnd ) = getIterators();
			i != iEnd;
			++i )
	{
		visitor.setName( i->first );
		boost::apply_visitor( visitor, i->second );
	}
}



} // namespace basic

} // namespace vgeGL
