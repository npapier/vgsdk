// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DEPTH_HPP
#define _VGD_NODE_DEPTH_HPP

#include "vgd/vgd.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{

/**
 * @brief Properties and usage definition of the depth buffer
 * 
 * The Depth node specifies the current depth function and enable/disable the writing into the depth buffer.
 * 
 * New field added by this node :
 * 
 * - PAFInt32 \c [function] = (LESS)\n
 * 		Specifies the function used for depth-buffer comparisons. The following symbolic constants are accepted :
 * 			- NEVER
 * 				Never passes
 * 			- LESS
 * 				Passes if the incoming z value is less than the stored z value. This is the default value.
 * 			- LEQUAL
 * 				Passes if the incoming z value is less than or equal to the stored z value.
 * 			- EQUAL
 * 				Passes if the incoming z value is equal to the stored z value.
 * 			- GREATER
 * 				Passes if the incoming z value is greater than the stored z value.
 * 			- NOTEQUAL
 * 				Passes if the incoming z value is not equal to the stored z value.
 * 			- GEQUAL
 * 				Passes if the incoming z value is greater than or equal to the stored z value.
 * 			- ALWAYS
 * 				Always passes.
 * 
 * - PAFBool \c [mask] = (RW)\n
 * 		Specifies the type of access to the depth buffer. The following symbolic constant are accepted :
 * 			- RW
 * 				Specifies that the depth buffer is enabled for writing. This is the default.
 * 			- RO
 * 				Specifies that the depth buffer access is read-only.
 * 
 * @ingroup g_nodes
 * @ingroup g_frameBufferNodes
 * @ingroup g_singleAttributeNodes
 * 
 * @todo glDepthRange, glPolygonOffset
 */
struct VGD_API Depth : public vgd::node::SingleAttribute
{
	META_NODE_HPP( Depth );
	


	/**
	 * @name Accessors to field function.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c function parameter.
	 */
	typedef enum
	{
		FUNCTION = 1
	} FunctionParameterType;

	/**
	 * @brief Typedef for the \c function parameter value.
	 */
	typedef enum {
		NEVER = 0,
		LESS,
		LEQUAL,
		EQUAL,
		GREATER,
		NOTEQUAL,
		GEQUAL,
		ALWAYS,
		FUNCTION_DEFAULT = LESS
	} FunctionValueType;

	/**
	 * @brief Typedef for the \c function field.
	 */	
	typedef vgd::field::TPairAssociativeField< FunctionParameterType, FunctionValueType > FFunctionType;

	/**
	 * @brief Gets the \c function value.
	 */
	bool			getFunction( FunctionValueType& value ) const;

	/**
	 * @brief Sets the \c function value.
	 */
	void 			setFunction( FunctionValueType value );
	
	/**
	 * @brief Erase the \c function value.
	 */
	void 			eraseFunction();
	//@}

	
	
	/**
	 * @name Accessors to field mask.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c mask parameter.
	 */
	typedef enum
	{
		MASK = 1
	} MaskParameterType;

	/**
	 * @brief Typedef for the \c mask parameter value.
	 */
	typedef enum {
		RW = 0,
		RO,
		MASK_DEFAULT = RW
	} MaskValueType;

	/**
	 * @brief Typedef for the \c mask field.
	 */	
	typedef vgd::field::TPairAssociativeField< MaskParameterType, MaskValueType > FMaskType;

	/**
	 * @brief Gets the \c mask value.
	 */
	bool			getMask( MaskValueType& value ) const;

	/**
	 * @brief Sets the \c mask value.
	 */
	void 			setMask( MaskValueType value );
	
	/**
	 * @brief Erase the \c mask value.
	 */
	void 			eraseMask();

	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c function.
	 * 
	 * @return the name of field \c function.
	 */
	static const std::string getFFunction();

	/**
	 * @brief Returns the name of field \c mask.
	 * 
	 * @return the name of field \c mask.
	 */
	static const std::string getFMask();

	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Depth( const std::string nodeName );

	void	setToDefaults();

	void	setOptionalsToDefaults();

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_DEPTH_HPP
