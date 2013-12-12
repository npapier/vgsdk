// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TESSELLATIONLEVEL_HPP
#define _VGD_NODE_TESSELLATIONLEVEL_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/String.hpp"
#include "vgd/field/Vec4f.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Control the tessellation level computation
 *
 * Specify the function used to compute the tessellation level in tessellation control shader. To combine several methods computing the tessellation level, you have to compute tessellation level with each method separately and mixes them as you like using a CUSTOM function (see customDeclarations and customMethod). CUSTOM method has to compute two variables, named tessLevelOuter (a vec4) and tessLevelInner (a vec2) that are similar to gl_TessLevelOuter[] and gl_TessLevelInner[] except their types (vector versus array). 
 *
 * New fields defined by this node :
 * - OFVec4f \c [parameter4f1] = vgm::Vec4f(0.f, 0.f, 0.f, 0.f)<br>
 *<br>
 * - SFString \c customCode = std::string()<br>
 *   Have to compute tessellation level in tessLevelOuter and tessLevelInner (resp. a vec4 and a vec2).<br>
 *<br>
 * - SFString \c customDeclarations = std::string()<br>
 *   Append this field to the tessellation control shader declarations section. Use case: to define function used by customCode field<br>
 *<br>
 * - SFEnum \c method = (UNIFORM)<br>
 *   Specify the method used to compute the tessellation level<br>
 *<br>
 * - OFVec4f \c [parameter4f0] = vgm::Vec4f(0.f, 0.f, 0.f, 0.f)<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 * @ingroup g_shapeModifierNodes
 * @ingroup g_tessellationNodes
 */
struct VGD_API TessellationLevel : public vgd::node::SingleAttribute
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
	static vgd::Shp< TessellationLevel > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< TessellationLevel > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< TessellationLevel > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field parameter4f1
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c parameter4f1.
	 */
	typedef vgm::Vec4f Parameter4f1ValueType;

	/**
	 * @brief The default value of field named \c parameter4f1.
	 */
	static const Parameter4f1ValueType DEFAULT_PARAMETER4F1;

	/**
	 * @brief Type definition of the field named \c parameter4f1
	 */
	typedef vgd::field::TOptionalField< Parameter4f1ValueType > FParameter4f1Type;


	/**
	 * @brief Gets the value of field named \c parameter4f1.
	 */
	const bool getParameter4f1( Parameter4f1ValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c parameter4f1.
 	 */
	void setParameter4f1( const Parameter4f1ValueType& value );

	/**
	 * @brief Erases the field named \c parameter4f1.
	 */
	void eraseParameter4f1();

	/**
	 * @brief Tests if the value of field named \c parameter4f1 has been initialized.
	 */
	const bool hasParameter4f1() const;
	//@}



	/**
	 * @name Accessors to field customCode
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c customCode.
	 */
	typedef std::string CustomCodeValueType;

	/**
	 * @brief The default value of field named \c customCode.
	 */
	static const CustomCodeValueType DEFAULT_CUSTOMCODE;

	/**
	 * @brief Type definition of the field named \c customCode
	 */
	typedef vgd::field::TSingleField< CustomCodeValueType > FCustomCodeType;


	/**
	 * @brief Gets the value of field named \c customCode.
	 */
	const CustomCodeValueType getCustomCode() const;

	/**
	 * @brief Sets the value of field named \c customCode.
	 */
	void setCustomCode( const CustomCodeValueType value );

	//@}



	/**
	 * @name Accessors to field customDeclarations
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c customDeclarations.
	 */
	typedef std::string CustomDeclarationsValueType;

	/**
	 * @brief The default value of field named \c customDeclarations.
	 */
	static const CustomDeclarationsValueType DEFAULT_CUSTOMDECLARATIONS;

	/**
	 * @brief Type definition of the field named \c customDeclarations
	 */
	typedef vgd::field::TSingleField< CustomDeclarationsValueType > FCustomDeclarationsType;


	/**
	 * @brief Gets the value of field named \c customDeclarations.
	 */
	const CustomDeclarationsValueType getCustomDeclarations() const;

	/**
	 * @brief Sets the value of field named \c customDeclarations.
	 */
	void setCustomDeclarations( const CustomDeclarationsValueType value );

	//@}



	/**
	 * @name Accessors to field method
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		CUSTOM = 425,	///< Use custom function to compute the tessellation level. The function is defined by field customDeclarations and customCode
		PIXELS_PER_EDGE = 424,	///< Adaptive tessellation using the number of pixels per edge desired as criterion. Tessellation level range is given by tessellationRange[].
		UNIFORM = 423,	///< Use the same tessellation level given by the field tessellationRange[1]
		DEFAULT_METHOD = UNIFORM	///< Use the same tessellation level given by the field tessellationRange[1]
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct MethodValueType : public vgd::field::Enum
	{
		MethodValueType()
		{}

		MethodValueType( const int v )
		: vgd::field::Enum(v)
		{}

		MethodValueType( const MethodValueType& o )
		: vgd::field::Enum(o)
		{}

		MethodValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 423 );
			retVal.push_back( 424 );
			retVal.push_back( 425 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "UNIFORM" );
			retVal.push_back( "PIXELS_PER_EDGE" );
			retVal.push_back( "CUSTOM" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c method
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FMethodType;


	/**
	 * @brief Gets the value of field named \c method.
	 */
	const MethodValueType getMethod() const;

	/**
	 * @brief Sets the value of field named \c method.
	 */
	void setMethod( const MethodValueType value );

	//@}



	/**
	 * @name Accessors to field parameter4f0
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c parameter4f0.
	 */
	typedef vgm::Vec4f Parameter4f0ValueType;

	/**
	 * @brief The default value of field named \c parameter4f0.
	 */
	static const Parameter4f0ValueType DEFAULT_PARAMETER4F0;

	/**
	 * @brief Type definition of the field named \c parameter4f0
	 */
	typedef vgd::field::TOptionalField< Parameter4f0ValueType > FParameter4f0Type;


	/**
	 * @brief Gets the value of field named \c parameter4f0.
	 */
	const bool getParameter4f0( Parameter4f0ValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c parameter4f0.
 	 */
	void setParameter4f0( const Parameter4f0ValueType& value );

	/**
	 * @brief Erases the field named \c parameter4f0.
	 */
	void eraseParameter4f0();

	/**
	 * @brief Tests if the value of field named \c parameter4f0 has been initialized.
	 */
	const bool hasParameter4f0() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c parameter4f1.
	 *
	 * @return the name of field \c parameter4f1.
	 */
	static const std::string getFParameter4f1( void );

	/**
	 * @brief Returns the name of field \c customCode.
	 *
	 * @return the name of field \c customCode.
	 */
	static const std::string getFCustomCode( void );

	/**
	 * @brief Returns the name of field \c customDeclarations.
	 *
	 * @return the name of field \c customDeclarations.
	 */
	static const std::string getFCustomDeclarations( void );

	/**
	 * @brief Returns the name of field \c method.
	 *
	 * @return the name of field \c method.
	 */
	static const std::string getFMethod( void );

	/**
	 * @brief Returns the name of field \c parameter4f0.
	 *
	 * @return the name of field \c parameter4f0.
	 */
	static const std::string getFParameter4f0( void );

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
	TessellationLevel( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , TessellationLevel );
private:
	static const vgd::basic::RegisterNode<TessellationLevel> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TESSELLATIONLEVEL_HPP
