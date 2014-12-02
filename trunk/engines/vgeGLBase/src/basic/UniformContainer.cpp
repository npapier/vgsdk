//// VGSDK - Copyright (C) 2010, 2011, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/basic/UniformContainer.hpp"
//
//#include <boost/tuple/tuple.hpp>
//#include <glo/GLSLProgram.hpp>
//#include "vgeGL/engine/Engine.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace basic
//{
//
//
//
//namespace
//{
//
///**
// * @brief Sets an OpenGL uniform variable
// */
//struct SetUniformVisitor : public boost::static_visitor<>
//{
//	/**
//	 * @brief Default constructor
//	 *
//	 * @param engine	engine used for rendering
//	 */
//	SetUniformVisitor( vgeGL::engine::Engine * engine )
//	:	m_engine	( engine	)
//	{}
//
//	/**
//	 * @brief Sets the name of the uniform variable that must be initialiazed
//	 *
//	 * @param name		name of uniform
//	 */
//	void setName( const std::string& name )
//	{
//		m_name = name;
//	}
//
//	/**
//	 * @name OpenGL uniform variable setters
//	 */
//	//@{
//
//	void operator() ( int value ) const
//	{
//		m_engine->getCurrentProgram()->setUniform1i( m_name, value );
//	}
//
//	void operator() ( float value ) const
//	{
//		m_engine->getCurrentProgram()->setUniform1f( m_name, value );
//	}
//
//	void operator() ( vgm::Vec2f value ) const
//	{
//		m_engine->getCurrentProgram()->setUniform2fv( m_name, value.getValue() );
//	}
//
//	void operator() ( vgm::Vec3f value ) const
//	{
//		m_engine->getCurrentProgram()->setUniform3fv( m_name, value.getValue() );
//	}
//
//	void operator() ( vgm::Vec4f value ) const
//	{
//		m_engine->getCurrentProgram()->setUniform4fv( m_name, value.getValue() );
//	}
//
//	void operator() ( vgm::MatrixR value ) const
//	{
//		m_engine->getCurrentProgram()->setUniformMatrix4fv( m_name, reinterpret_cast< GLfloat * >(value.getValue()) );
//	}
//	//@}
//
//private:
//	vgeGL::engine::Engine * m_engine;	///< engine used for rendering
//	std::string				m_name;		///< name of uniform
//};
//
//
//
///**
// * @brief Sets an OpenGL uniform variable
// */
//struct DeclarationGeneratorVisitor : public boost::static_visitor<>
//{
//	/**
//	 * @brief Sets the name of the uniform variable that must be initialiazed
//	 *
//	 * @param name		name of uniform
//	 */
//	void setName( const std::string& name )
//	{
//		m_name = name;
//	}
//
//	/**
//	 * @name OpenGL uniform variable declaration generators
//	 */
//	//@{
//
//	void operator() ( int value )
//	{
//		m_decl = "uniform int " + m_name + ";\n";
//	}
//
//	void operator() ( float value )
//	{
//		m_decl = "uniform float " + m_name + ";\n";
//	}
//
//	void operator() ( vgm::Vec2f value )
//	{
//		m_decl = "uniform vec2 " + m_name + ";\n";
//	}
//
//	void operator() ( vgm::Vec3f value )
//	{
//		m_decl = "uniform vec3 " + m_name + ";\n";
//	}
//
//	void operator() ( vgm::Vec4f value )
//	{
//		m_decl = "uniform vec4 " + m_name + ";\n";
//	}
//
//	void operator() ( vgm::MatrixR value )
//	{
//		m_decl = "uniform mat4 " + m_name + ";\n";
//	}
//	//@}
//
//	const std::string& getDeclaration() const { return m_decl; }
//
//private:
//	std::string	m_name;		///< name of uniform
//	std::string	m_decl;
//};
//
//}
//
//
//
//const std::string UniformContainer::generateDeclarations()
//{
//	std::string retVal;
//
//	DeclarationGeneratorVisitor visitor;
//	ConstIteratorType i, iEnd;
//	for(	boost::tie( i, iEnd ) = getIterators();
//			i != iEnd;
//			++i )
//	{
//		visitor.setName( i->first );
//		boost::apply_visitor( visitor, i->second );
//		retVal += visitor.getDeclaration();
//	}
//	return retVal;
//}
//
//
//void UniformContainer::apply( vgeGL::engine::Engine * engine )
//{
//	SetUniformVisitor visitor( engine );
//	ConstIteratorType i, iEnd;
//	for(	boost::tie( i, iEnd ) = getIterators();
//			i != iEnd;
//			++i )
//	{
//		visitor.setName( i->first );
//		boost::apply_visitor( visitor, i->second );
//	}
//}
//
//
//
//} // namespace basic
//
//} // namespace vgeGL
//