// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_PROGRAM_HPP
#define _VGD_NODE_PROGRAM_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/String.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief OpenGL Shading Language program definition node
 *
 * The Program node specifies the current shaders used during the rendering. The developer can write vertex, tessellation control, tessellation evaluation, geometry and/or fragment shaders in a high level language as defined in the OpenGL Shading Language specification. This node is only interpret during the rendering pass. todo shaders documentation todo shader could be string or file => begining of string for file "file:", and nothing special for string uniform parameters ? and others ? 
 *
 * New fields defined by this node :
 * - SFBool \c tessellationUse = (false)<br>
 *   Specifies if tessellationControl AND tessellationEvaluation are enabled or disabled.<br>
 *<br>
 * - SFString \c geometry = std::string()<br>
 *   A geometry shader can generate new graphics primitives, such as points, lines, and triangles, from those primitives that were sent to the beginning of the graphics pipeline.<br>
 *<br>
 * - SFBool \c geometryUse = (false)<br>
 *   Specifies if geometry shader is enabled or disabled.<br>
 *<br>
 * - SFString \c tessellationEvaluation = std::string()<br>
 *   A tessellation evaluation shader evaluates the surface in uvw coordinates.      It interpolates attributes and applies displacements.  There is one invocation per generated vertex<br>
 *<br>
 * - SFString \c vertex = std::string()<br>
 *   A vertex shader replaces the transformation, texture coordinate generation and lighting parts of OpenGL, and it also adds texture access at the vertex level.<br>
 *<br>
 * - SFBool \c fragmentUse = (true)<br>
 *   Specifies if fragment shader is enabled or disabled.<br>
 *<br>
 * - SFString \c fragment = std::string()<br>
 *   A fragment shader replaces the OpenGL fixed-function texturing, color sum and fog stages.<br>
 *<br>
 * - SFBool \c vertexUse = (true)<br>
 *   Specifies if vertex shader is enabled or disabled.<br>
 *<br>
 * - SFString \c tessellationControl = std::string()<br>
 *   A tessellation control shader transforms the input coordinates to a regular surface representation.     It also computes the required tessellation level based on distance to the eye, screen space spanning, hull curvature, or displacement roughness.      There is one invocation per output vertex.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_coloringAndLightingNodes
 * @ingroup g_singleAttributeNodes
 */
struct VGD_API Program : public vgd::node::SingleAttribute
{
	/**
	 * @name Factories
	 */
	//@{

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values
	 */
	static vgd::Shp< Program > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Program > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Program > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field tessellationUse
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tessellationUse.
	 */
	typedef bool TessellationUseValueType;

	/**
	 * @brief The default value of field named \c tessellationUse.
	 */
	static const TessellationUseValueType DEFAULT_TESSELLATIONUSE;

	/**
	 * @brief Type definition of the field named \c tessellationUse
	 */
	typedef vgd::field::TSingleField< TessellationUseValueType > FTessellationUseType;


	/**
	 * @brief Gets the value of field named \c tessellationUse.
	 */
	const TessellationUseValueType getTessellationUse() const;

	/**
	 * @brief Sets the value of field named \c tessellationUse.
	 */
	void setTessellationUse( const TessellationUseValueType value );

	//@}



	/**
	 * @name Accessors to field geometry
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c geometry.
	 */
	typedef std::string GeometryValueType;

	/**
	 * @brief The default value of field named \c geometry.
	 */
	static const GeometryValueType DEFAULT_GEOMETRY;

	/**
	 * @brief Type definition of the field named \c geometry
	 */
	typedef vgd::field::TSingleField< GeometryValueType > FGeometryType;


	/**
	 * @brief Gets the value of field named \c geometry.
	 */
	const GeometryValueType getGeometry() const;

	/**
	 * @brief Sets the value of field named \c geometry.
	 */
	void setGeometry( const GeometryValueType value );

	//@}



	/**
	 * @name Accessors to field geometryUse
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c geometryUse.
	 */
	typedef bool GeometryUseValueType;

	/**
	 * @brief The default value of field named \c geometryUse.
	 */
	static const GeometryUseValueType DEFAULT_GEOMETRYUSE;

	/**
	 * @brief Type definition of the field named \c geometryUse
	 */
	typedef vgd::field::TSingleField< GeometryUseValueType > FGeometryUseType;


	/**
	 * @brief Gets the value of field named \c geometryUse.
	 */
	const GeometryUseValueType getGeometryUse() const;

	/**
	 * @brief Sets the value of field named \c geometryUse.
	 */
	void setGeometryUse( const GeometryUseValueType value );

	//@}



	/**
	 * @name Accessors to field tessellationEvaluation
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tessellationEvaluation.
	 */
	typedef std::string TessellationEvaluationValueType;

	/**
	 * @brief The default value of field named \c tessellationEvaluation.
	 */
	static const TessellationEvaluationValueType DEFAULT_TESSELLATIONEVALUATION;

	/**
	 * @brief Type definition of the field named \c tessellationEvaluation
	 */
	typedef vgd::field::TSingleField< TessellationEvaluationValueType > FTessellationEvaluationType;


	/**
	 * @brief Gets the value of field named \c tessellationEvaluation.
	 */
	const TessellationEvaluationValueType getTessellationEvaluation() const;

	/**
	 * @brief Sets the value of field named \c tessellationEvaluation.
	 */
	void setTessellationEvaluation( const TessellationEvaluationValueType value );

	//@}



	/**
	 * @name Accessors to field vertex
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c vertex.
	 */
	typedef std::string VertexValueType;

	/**
	 * @brief The default value of field named \c vertex.
	 */
	static const VertexValueType DEFAULT_VERTEX;

	/**
	 * @brief Type definition of the field named \c vertex
	 */
	typedef vgd::field::TSingleField< VertexValueType > FVertexType;


	/**
	 * @brief Gets the value of field named \c vertex.
	 */
	const VertexValueType getVertex() const;

	/**
	 * @brief Sets the value of field named \c vertex.
	 */
	void setVertex( const VertexValueType value );

	//@}



	/**
	 * @name Accessors to field fragmentUse
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c fragmentUse.
	 */
	typedef bool FragmentUseValueType;

	/**
	 * @brief The default value of field named \c fragmentUse.
	 */
	static const FragmentUseValueType DEFAULT_FRAGMENTUSE;

	/**
	 * @brief Type definition of the field named \c fragmentUse
	 */
	typedef vgd::field::TSingleField< FragmentUseValueType > FFragmentUseType;


	/**
	 * @brief Gets the value of field named \c fragmentUse.
	 */
	const FragmentUseValueType getFragmentUse() const;

	/**
	 * @brief Sets the value of field named \c fragmentUse.
	 */
	void setFragmentUse( const FragmentUseValueType value );

	//@}



	/**
	 * @name Accessors to field fragment
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c fragment.
	 */
	typedef std::string FragmentValueType;

	/**
	 * @brief The default value of field named \c fragment.
	 */
	static const FragmentValueType DEFAULT_FRAGMENT;

	/**
	 * @brief Type definition of the field named \c fragment
	 */
	typedef vgd::field::TSingleField< FragmentValueType > FFragmentType;


	/**
	 * @brief Gets the value of field named \c fragment.
	 */
	const FragmentValueType getFragment() const;

	/**
	 * @brief Sets the value of field named \c fragment.
	 */
	void setFragment( const FragmentValueType value );

	//@}



	/**
	 * @name Accessors to field vertexUse
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c vertexUse.
	 */
	typedef bool VertexUseValueType;

	/**
	 * @brief The default value of field named \c vertexUse.
	 */
	static const VertexUseValueType DEFAULT_VERTEXUSE;

	/**
	 * @brief Type definition of the field named \c vertexUse
	 */
	typedef vgd::field::TSingleField< VertexUseValueType > FVertexUseType;


	/**
	 * @brief Gets the value of field named \c vertexUse.
	 */
	const VertexUseValueType getVertexUse() const;

	/**
	 * @brief Sets the value of field named \c vertexUse.
	 */
	void setVertexUse( const VertexUseValueType value );

	//@}



	/**
	 * @name Accessors to field tessellationControl
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c tessellationControl.
	 */
	typedef std::string TessellationControlValueType;

	/**
	 * @brief The default value of field named \c tessellationControl.
	 */
	static const TessellationControlValueType DEFAULT_TESSELLATIONCONTROL;

	/**
	 * @brief Type definition of the field named \c tessellationControl
	 */
	typedef vgd::field::TSingleField< TessellationControlValueType > FTessellationControlType;


	/**
	 * @brief Gets the value of field named \c tessellationControl.
	 */
	const TessellationControlValueType getTessellationControl() const;

	/**
	 * @brief Sets the value of field named \c tessellationControl.
	 */
	void setTessellationControl( const TessellationControlValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c tessellationUse.
	 *
	 * @return the name of field \c tessellationUse.
	 */
	static const std::string getFTessellationUse( void );

	/**
	 * @brief Returns the name of field \c geometry.
	 *
	 * @return the name of field \c geometry.
	 */
	static const std::string getFGeometry( void );

	/**
	 * @brief Returns the name of field \c geometryUse.
	 *
	 * @return the name of field \c geometryUse.
	 */
	static const std::string getFGeometryUse( void );

	/**
	 * @brief Returns the name of field \c tessellationEvaluation.
	 *
	 * @return the name of field \c tessellationEvaluation.
	 */
	static const std::string getFTessellationEvaluation( void );

	/**
	 * @brief Returns the name of field \c vertex.
	 *
	 * @return the name of field \c vertex.
	 */
	static const std::string getFVertex( void );

	/**
	 * @brief Returns the name of field \c fragmentUse.
	 *
	 * @return the name of field \c fragmentUse.
	 */
	static const std::string getFFragmentUse( void );

	/**
	 * @brief Returns the name of field \c fragment.
	 *
	 * @return the name of field \c fragment.
	 */
	static const std::string getFFragment( void );

	/**
	 * @brief Returns the name of field \c vertexUse.
	 *
	 * @return the name of field \c vertexUse.
	 */
	static const std::string getFVertexUse( void );

	/**
	 * @brief Returns the name of field \c tessellationControl.
	 *
	 * @return the name of field \c tessellationControl.
	 */
	static const std::string getFTessellationControl( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



	/**
	 * @name Constructor and initializer methods
	 */
	//@{

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}

protected:
	/**
	 * @brief Default constructor
	 */
	Program( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Program );
private:
	static const vgd::basic::RegisterNode<Program> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_PROGRAM_HPP
