// VGSDK - Copyright (C) 2006, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CALLBACK_H
#define _VGD_NODE_CALLBACK_H

#include <boost/function.hpp>

#include "vgd/vgd.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{

/**
 * @brief A node allowing to insert directly openGL code through a
 * callback
 * 
 * The callback is registered using the setCallback function. It must
 * be of the form void callback(vgd::node::Callback*)
 * There are two different ways to send extra information to the callback.
 * - The Callback node can be inherited and extra information can be
     put on the new class.
 * - A new field can be added to the node.
 * \code
 *  vgd::field::TSingleField<float>* transparency = new vgd::field::TSingleField<float>("transparency");
 * transparency->setValue(0.5);
 * callbackNode->addField(transparency);
 * \endcode 
 * The data is accessed the following way inside the callback:
 * \code
 * if(node->isField("transparency"){
 *   vgd::field::EditorRO<TSingleField<float> > ed = node->getField<TSingleField<float> ("transparency");
 *   float transparency = *ed;
 * ...
 * }
 * \endcode
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * 
 */
struct VGD_API Callback : public vgd::node::SingleAttribute
{
	META_NODE_HPP( Callback );
	
	/**
	 * @name Accessors to field function.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c callback parameter.
	 */
	typedef enum
	{
	  CALLBACKFUNCTION = 1
	} FunctionParameterType;

	/**
	 * @brief Typedef for the \c function parameter value.
	 */
	typedef boost::function<void (Callback*)> CallbackType;

	/**
	 * @brief Typedef for the \c function field.
	 */	
	typedef vgd::field::TPairAssociativeField< FunctionParameterType, CallbackType > FFunctionType;

	/**
	 * @brief Sets the \c function value.
	 */
	void 			setCallback( CallbackType value );
	
	/**
	 * @brief Erase the \c function value.
	 */
	void 			eraseCallback();
	//@}
	/**
	 * @brief Gets the \c function value.
	 */
	bool			getCallback( CallbackType& value ) const;


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

	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Callback( const std::string nodeName );

	void	setToDefaults();

	void	setOptionalsToDefaults();

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_CALLBACK_H
