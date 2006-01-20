// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CLEARFRAMEBUFFER_H
#define _VGD_NODE_CLEARFRAMEBUFFER_H

#include "vgd/vgd.hpp"

#include <vgm/Vector.hpp>

#include "vgd/field/Integer.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Node to clear framebuffer.
 *
 * New fields added by this node :
 *
 * - SFInt8 clearMask		= (COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT)\n
 * 		Buffers to be cleared.
 * 
 * - PAFVec4f \c [clear]
 * 	- COLOR	= (0 0 0 0 )\n
 * 		The clear color.
 * 	- ACCUM	= (0 0 0 0 )\n
 * 		The clear accumulation color.
 * 
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_frameBufferNodes
 * 
 * @todo clear values for the stencil, depth.
 */
struct VGD_API ClearFrameBuffer : public vgd::node::SingleAttribute
{
	META_NODE_HPP( ClearFrameBuffer );



	/**
	 * @name Accessors to field clearMask.
	 */
	//@{
	
	/**
	 * @brief Enumeration of masks values.
	 */
	enum
	{
		COLOR_BUFFER_BIT		= 1<<0,			/*!< The buffers currently enabled for color writing. */
		DEPTH_BUFFER_BIT		= 1<<1,			/*!< The depth buffer. */
		ACCUM_BUFFER_BIT		= 1<<2,			/*!< The accumulation buffer. */
		STENCIL_BUFFER_BIT	= 1<<3			/*!< The stencil buffer. */
	};
	
	/**
	 * @brief Typedef for the \c clearMask field.
	 */	
	typedef vgd::field::SFInt8	FClearMaskType;
		
	/**
	 * @brief Typedef for the \c clearMask value.
	 */
	typedef int8					ClearMaskValueType;	
	
	/**
	 * @brief Gets the masks that indicate the buffers to be cleared.
	 */
	int8	getClearMask() const;
	
	/**
	 * @brief Sets the masks that indicate the buffers to be cleared.
	 * 
	 * @param mask		Bitwise OR operators of masks that indicate the buffers to be cleared.
	 */
	void	setClearMask( const int8 mask );
	//@}

	
	
	/**
	 * @name Accessors to field clear.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c clear parameters.
	 */
	typedef enum
	{
		COLOR		= 1,
		ACCUM
	} ClearParameterType;

	/**
	 * @brief Typedef for the \c clear value.
	 */
	typedef vgm::Vec4f ClearValueType;

	/**
	 * @brief Typedef for the \c clear field.
	 */	
	typedef vgd::field::TPairAssociativeField< ClearParameterType, ClearValueType > FClearType;

	/**
	 * @brief Gets the clear value for the color or accumulation buffers.
	 */
	bool			getClear( const ClearParameterType param, ClearValueType& value ) const;

	/**
	 * @brief Sets the clear value for the color or accumulation buffers.
	 */
	void 			setClear( const ClearParameterType param, ClearValueType value );
	
	/**
	 * @brief Erase the clear value for the color or accumulation buffers.
	 */
	void 			eraseClear( const ClearParameterType param );
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c clearMask.
	 * 
	 * @return the name of field \c clearMask.
	 */
	static const std::string getFClearMask( void );

	/**
	 * @brief Returns the name of field \c clear.
	 * 
	 * @return the name of field \c clear.
	 */
	static const std::string getFClear( void );
	//@}
	
	

protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	ClearFrameBuffer( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_CLEARFRAMEBUFFER_H
