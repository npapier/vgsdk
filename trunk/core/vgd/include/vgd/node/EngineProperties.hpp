// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ENGINEPROPERTIES_HPP
#define _VGD_NODE_ENGINEPROPERTIES_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Definition of several properties of vgsdk engine
 *
 * This node defines the default anisotropy used during texture filtering and OpenGL api usage hints (GL_ARB_debug_output extension and DSA). 
 *
 * New fields defined by this node :
 * - OFFloat \c [maxAnisotropy] = (1.f)<br>
 *   Specifies the engine default maximum degree of anisotropy (see vgd::node::Texture).<br>
 *<br>
 * - OFBool \c [openglDebugOutput] = (false)<br>
 *   Specifies if the OpenGL debug output system is enabled or disabled (see setDebugOutput() in gle).<br>
 *<br>
 * - OFBool \c [openglDirectStateAccess] = (false)<br>
 *   Specifies if the OpenGL DSA functions have to be used or not (see GL_EXT_direct_state_access extension)<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 */
struct VGD_API EngineProperties : public vgd::node::SingleAttribute
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
	static vgd::Shp< EngineProperties > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< EngineProperties > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< EngineProperties > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field maxAnisotropy
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c maxAnisotropy.
	 */
	typedef float MaxAnisotropyValueType;

	/**
	 * @brief The default value of field named \c maxAnisotropy.
	 */
	static const MaxAnisotropyValueType DEFAULT_MAXANISOTROPY;

	/**
	 * @brief Type definition of the field named \c maxAnisotropy
	 */
	typedef vgd::field::TOptionalField< MaxAnisotropyValueType > FMaxAnisotropyType;


	/**
	 * @brief Gets the value of field named \c maxAnisotropy.
	 */
	const bool getMaxAnisotropy( MaxAnisotropyValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c maxAnisotropy.
 	 */
	void setMaxAnisotropy( const MaxAnisotropyValueType& value );

	/**
	 * @brief Erases the field named \c maxAnisotropy.
	 */
	void eraseMaxAnisotropy();

	/**
	 * @brief Tests if the value of field named \c maxAnisotropy has been initialized.
	 */
	const bool hasMaxAnisotropy() const;
	//@}



	/**
	 * @name Accessors to field openglDebugOutput
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c openglDebugOutput.
	 */
	typedef bool OpenglDebugOutputValueType;

	/**
	 * @brief The default value of field named \c openglDebugOutput.
	 */
	static const OpenglDebugOutputValueType DEFAULT_OPENGLDEBUGOUTPUT;

	/**
	 * @brief Type definition of the field named \c openglDebugOutput
	 */
	typedef vgd::field::TOptionalField< OpenglDebugOutputValueType > FOpenglDebugOutputType;


	/**
	 * @brief Gets the value of field named \c openglDebugOutput.
	 */
	const bool getOpenglDebugOutput( OpenglDebugOutputValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c openglDebugOutput.
 	 */
	void setOpenglDebugOutput( const OpenglDebugOutputValueType& value );

	/**
	 * @brief Erases the field named \c openglDebugOutput.
	 */
	void eraseOpenglDebugOutput();

	/**
	 * @brief Tests if the value of field named \c openglDebugOutput has been initialized.
	 */
	const bool hasOpenglDebugOutput() const;
	//@}



	/**
	 * @name Accessors to field openglDirectStateAccess
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c openglDirectStateAccess.
	 */
	typedef bool OpenglDirectStateAccessValueType;

	/**
	 * @brief The default value of field named \c openglDirectStateAccess.
	 */
	static const OpenglDirectStateAccessValueType DEFAULT_OPENGLDIRECTSTATEACCESS;

	/**
	 * @brief Type definition of the field named \c openglDirectStateAccess
	 */
	typedef vgd::field::TOptionalField< OpenglDirectStateAccessValueType > FOpenglDirectStateAccessType;


	/**
	 * @brief Gets the value of field named \c openglDirectStateAccess.
	 */
	const bool getOpenglDirectStateAccess( OpenglDirectStateAccessValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c openglDirectStateAccess.
 	 */
	void setOpenglDirectStateAccess( const OpenglDirectStateAccessValueType& value );

	/**
	 * @brief Erases the field named \c openglDirectStateAccess.
	 */
	void eraseOpenglDirectStateAccess();

	/**
	 * @brief Tests if the value of field named \c openglDirectStateAccess has been initialized.
	 */
	const bool hasOpenglDirectStateAccess() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c maxAnisotropy.
	 *
	 * @return the name of field \c maxAnisotropy.
	 */
	static const std::string getFMaxAnisotropy( void );

	/**
	 * @brief Returns the name of field \c openglDebugOutput.
	 *
	 * @return the name of field \c openglDebugOutput.
	 */
	static const std::string getFOpenglDebugOutput( void );

	/**
	 * @brief Returns the name of field \c openglDirectStateAccess.
	 *
	 * @return the name of field \c openglDirectStateAccess.
	 */
	static const std::string getFOpenglDirectStateAccess( void );

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
	EngineProperties( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , EngineProperties );
private:
	static const vgd::basic::RegisterNode<EngineProperties> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ENGINEPROPERTIES_HPP
