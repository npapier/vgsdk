// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_OUTPUTBUFFERS_HPP
#define _VGD_NODE_OUTPUTBUFFERS_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Select which buffers to use for drawing
 *
 * This node affect subsequent shapes in the scene graph. But if this node is under a separator, it does not affect any objects outside that separator. @todo Adds support for more than 2 different output buffers 
 *
 * New fields defined by this node :
 * - SFEnum \c output = BUFFERS0<br>
 *   Specifies the buffers used for rendering.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_frameBufferNodes
 */
struct VGD_API OutputBuffers : public vgd::node::SingleAttribute
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
	static vgd::Shp< OutputBuffers > create( const std::string nodeName = "NoName" );

	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< OutputBuffers > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field output
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		BUFFERS2 = 287,	///< Selects color buffer 2 and a depth buffer 2
		BUFFERS1 = 286,	///< Selects color buffer 1 and a depth buffer 1
		BUFFERS0 = 285,	///< Selects color buffer 0 and a depth buffer 0
		DEFAULT_OUTPUT = BUFFERS0	///< Selects color buffer 0 and a depth buffer 0
	};

	/**
	 * @brief Type definition of the value contained by field named \c output.
	 */
	struct OutputValueType : public vgd::field::Enum
	{
		OutputValueType()
		{}

		OutputValueType( const int v )
		: vgd::field::Enum(v)
		{}

		OutputValueType( const OutputValueType& o )
		: vgd::field::Enum(o)
		{}

		OutputValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 285 );
			retVal.push_back( 286 );
			retVal.push_back( 287 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "BUFFERS0" );
			retVal.push_back( "BUFFERS1" );
			retVal.push_back( "BUFFERS2" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c output
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FOutputType;


	/**
	 * @brief Gets the value of field named \c output.
	 */
	const OutputValueType getOutput() const;

	/**
	 * @brief Sets the value of field named \c output.
	 */
	void setOutput( const OutputValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c output.
	 *
	 * @return the name of field \c output.
	 */
	static const std::string getFOutput( void );

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
	OutputBuffers( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , OutputBuffers );
private:
	static const vgd::basic::RegisterNode<OutputBuffers> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_OUTPUTBUFFERS_HPP
