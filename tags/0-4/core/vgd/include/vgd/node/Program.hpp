// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_PROGRAM_HPP
#define _VGD_NODE_PROGRAM_HPP

#include <string>
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{

/**
 * @brief OpenGL Shading Language program definition node
 * 
 * The Program node specifies the current shaders used during the rendering.
 * The developer can write vertex,fragment and/or geometry shaders in a high level language as defined
 * in the OpenGL Shading Language specification.
 * 
 * @remarks This node is only interpret during the rendering pass.
 * 
 * New field added by this node :
 * 
 * - PAFString \c shader
 *	- [VERTEX] = (empty)\n
 *		A vertex shader replaces the transformation, texture coordinate generation and lighting parts of OpenGL, and it 
 *		also adds texture access at the vertex level.
 *	- [FRAGMENT] = (empty)\n
 *		A fragment shader replaces the OpenGL fixed-function texturing, color sum and fog stages.
 *	- [GEOMETRY] = (empty)\n
 *		A geometry shader... @todo documentation
 *
 * @todo shaders documentation
 *
 * @todo 1 shader <=> 1-n string(s) or file(s) ?
 * @todo shader could be string or file => begining of string for file "file:", and nothing special for string
 * @todo uniform parameters ? and others ?
 *
 * @ingroup g_nodes
 * @ingroup g_coloringAndLightingNodes
 * @ingroup g_singleAttributeNodes
 */
struct VGD_API Program : public vgd::node::SingleAttribute
{
	META_NODE_HPP( Program );



	/**
	 * @name Accessors to field shader
	 */
	//@{

	/**
	 * @brief Enumeration of the \c shader parameters.
	 */
	typedef enum
	{
		VERTEX = 1,
		FRAGMENT,
		GEOMETRY
	} ShaderParameterType;

	/**
	 * @brief Typedef for the \c shader value.
	 */
	typedef std::string ShaderValueType;

	/**
	 * @brief Typedef for the \c shader field.
	 */	
	typedef vgd::field::TPairAssociativeField< ShaderParameterType, ShaderValueType > FShaderType;

	/**
	 * @brief Gets the shader value.
	 */
	bool			getShader( const ShaderParameterType param, ShaderValueType& value ) const;

	/**
	 * @brief Sets the shader value.
	 */
	void 			setShader( const ShaderParameterType param, ShaderValueType value );
	
	/**
	 * @brief Erase the shader value.
	 */
	void 			eraseShader( const ShaderParameterType param );
	//@}



	/**
	 * @name Fields names enumeration
	 */
	//@{

	/**
	 * @brief Returns the name of field \c shader.
	 * 
	 * @return the name of field \c shader.
	 */
	static const std::string getFShader();

	//@}



	/**
	 * @name Dirty flags enumeration
	 */
	//@{
	/**
	 * brief Returns name of dirty flag that is invalidate when vertex shader has changed.
	 */
	//static const std::string getDFVertex();

	/**
	 * brief Returns name of dirty flag that is invalidate when fragment shader has changed.
	 */
	//static const std::string getDFFragment();

	/**
	 * brief Returns name of dirty flag that is invalidate when geometry shader has changed.
	 */
	//static const std::string getDFGeometry();
	//@}



protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	Program( const std::string nodeName );

	void	setToDefaults();

	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_PROGRAM_HPP
