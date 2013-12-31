// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_UNIFORMS_HPP
#define _VGD_NODE_UNIFORMS_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/node/SingleAttribute.hpp"
#include "vgd/field/Uniform.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Defines uniform variable(s) available in all shaders
 *
 * An uniform variable is a global variable used by shaders in read-only mode. To add a new uniform variable, just call setUniform("uMyVariable", vgm::Vec3f(1.f, 2.f, 3.f)) To change the value of an uniform variable, just call setUniform("uMyVariable", vgm::Vec3f(1.f, 2.f, 3.f)) exactly as done to create the variable. To change the type of a variable, the variable has to be removed using removeUniform() and add again using setUniform(). See Uniforms accessors section in the documentation for the whole interface to manage uniform variables. 
 *
 * New fields defined by this node :
 * - SFEnum \c composeMode = (REPLACE)<br>
 *   Specifies if uniforms defined by this node are added or are replacing the current uniforms<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API Uniforms : public vgd::node::SingleAttribute
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
	static vgd::Shp< Uniforms > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Uniforms > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Uniforms > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field composeMode
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		APPEND = 461,	///< Uniforms defined by this node are added to the current uniforms
		REPLACE = 460,	///< Uniforms defined by this node are replacing the current uniforms. So all previous uniform variables are removed.
		DEFAULT_COMPOSEMODE = REPLACE	///< Uniforms defined by this node are replacing the current uniforms. So all previous uniform variables are removed.
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct ComposeModeValueType : public vgd::field::Enum
	{
		ComposeModeValueType()
		{}

		ComposeModeValueType( const int v )
		: vgd::field::Enum(v)
		{}

		ComposeModeValueType( const ComposeModeValueType& o )
		: vgd::field::Enum(o)
		{}

		ComposeModeValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 460 );
			retVal.push_back( 461 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "REPLACE" );
			retVal.push_back( "APPEND" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c composeMode
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FComposeModeType;


	/**
	 * @brief Gets the value of field named \c composeMode.
	 */
	const ComposeModeValueType getComposeMode() const;

	/**
	 * @brief Sets the value of field named \c composeMode.
	 */
	void setComposeMode( const ComposeModeValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c composeMode.
	 *
	 * @return the name of field \c composeMode.
	 */
	static const std::string getFComposeMode( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}
	/**
	 * @name Uniforms accessors
	 */
	//@{

	/**
	 * @brief Removes all uniform variables
	 */
	void clearUniforms();


	/**
	 * @brief Sets the value of an uniform variable
	 *
	 * If isUniform(name) is false, then it creates a new single field containing the given value. Otherwise it modifies the value of the variable.
	 *
	 * @param name		name of the uniform variable. Have to start with 'u' and followed by an upper case letter (ex. uPosition).
	 * @param value		value of the uniform variable. See vgd::field::UniformValue for an exhaustive list of supported type.
	 *
	 * @todo Test if T is a supported type
	 */
	template< typename T >
	void setUniform( const std::string& name, const T& value )
	{
		vgAssertN( name[0] == 'u', "The given name '%s' have to start with 'u'", name.c_str() );
		vgAssertN( name.size()>=2, "The size of the given name '%s' have to be at least 2.", name.c_str() );
		vgAssertN( (name[1] >= 'A') && (name[1] <= 'Z'), "The second character of the given name '%s' have to be an upper case letter", name.c_str() );

		if ( !isUniform(name) )
		{
			// Non existing uniform variable
			addField( new vgd::field::TSingleField< T >(name) );

			addDirtyFlag( name );

			link( name, name );
			link( name, getDFNode() );
		}

		// Changes the value of the uniform variable
		vgAssertN( getFieldType(name) == typeid(vgd::field::TSingleField<T>), "Try to set the uniform named '%s' with a new type '%s' instead of '%s'.", name.c_str(), typeid(vgd::field::TSingleField<T>).name(), getFieldType(name).name() );
		vgd::field::EditorRW< vgd::field::TSingleField<T> > uniform = getFieldRW< vgd::field::TSingleField<T> >( name );
		uniform->setValue( value );
	}


	/**
	 * @brief Returns the value of an uniform variable.
	 *
	 * @pre isUniform(name)
	 * @param name		name of the uniform variable.
	 *
	 * @return the value of the desired uniform variable.
	 */
	template< typename T >
	const T& getUniform( const std::string& name ) const
	{
		vgAssertN( getFieldType(name) == typeid(vgd::field::TSingleField<T>), "Try to get the uniform named '%s' with the wrong type '%s' instead of '%s'.", name.c_str(), typeid(vgd::field::TSingleField<T>).name(), getFieldType(name).name() );
		vgd::field::EditorRO< vgd::field::TSingleField<T> > uniform = getFieldRO< vgd::field::TSingleField<T> >( name );
		const T& value = uniform->getValue();
		return value;
	}


	/**
	 * @brief Remove an uniform variable
	 *
	 * @pre isAnUniformName(name)
	 *
	 * @param name		name of the variable to remove
	 * @return true if successfully removed, false otherwise
	 */
	const bool removeUniform( const std::string& name );


	/**
	 * @brief Tests if an uniform variable exists
	 *
	 * Tests if a field with the given name contains an uniform variable.
	 *
	 * @param name		name of the uniform variable
	 *
	 * @return true if the variable exists, false otherwise
	 */
	const bool isUniform( const std::string& name ) const;
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
	Uniforms( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Uniforms );
private:
	static const vgd::basic::RegisterNode<Uniforms> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_UNIFORMS_HPP
