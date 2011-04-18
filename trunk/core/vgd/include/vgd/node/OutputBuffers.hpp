// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_OUTPUTBUFFERS_HPP
#define _VGD_NODE_OUTPUTBUFFERS_HPP

#include "vgd/field/Int.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Select which buffers to use for drawing
 *
 * This node affect subsequent shapes in the scene graph. But if this node is under a separator, it does not affect any objects outside that separator. 
 *
 * New fields defined by this node :
 * - MFInt \c current = empty<br>
 *   Specifies the buffers used for rendering. The selection is done using multi-attribute index of OutputBufferProperty nodes.\n @remark The same index may not appear more then once.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_frameBufferNodes
 * @ingroup g_postProcessing
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
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< OutputBuffers > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< OutputBuffers > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field current
	 *
	 * @todo getCurrent( const bool rw = false ) ?
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c current.
	 */
	typedef int CurrentValueType;

	/**
	 * @brief Type definition of the field named \c current
	 */
	typedef vgd::field::TMultiField< CurrentValueType > FCurrentType;


	/**
	 * @brief Gets a read-only editor on the multi field named \c current.
	 */
	vgd::field::EditorRO< FCurrentType > getCurrentRO() const;

	/**
	 * @brief Gets a read-write editor on the multi field named \c current.
	 */
	vgd::field::EditorRW< FCurrentType > getCurrentRW();

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c current.
	 *
	 * @return the name of field \c current.
	 */
	static const std::string getFCurrent( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}
	/**
	 * @name High-level methods
	 */
	//@{

	/**
	 * @brief Specifies which buffer must be used for rendering.
	 *
	 * @param which		index of output buffer. Default value -1 means no buffer.
	 */
	void setCurrent( const int which = -1 );
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
