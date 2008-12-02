// VGSDK - Copyright (C) 2006, 2008, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_NODE_CALLBACK_HPP
#define _VGD_NODE_CALLBACK_HPP

#include <boost/function.hpp>

#include "vgd/vgd.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/IBoundingBox.hpp"
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
struct VGD_API Callback : public vgd::node::SingleAttribute, public vgd::node::IBoundingBox
{
	META_NODE_HPP( Callback );
	
	/**
	 * @brief Enumeration of the \c callback parameter.
	 */
	typedef enum
	{
	  PAINT_FUNCTION = 1,
	  CBB_FUNCTION
	} FunctionParameterType;

	/**
	 * @brief Typedef for the paint function.
	 */
	typedef boost::function<void (Callback*)> PaintFunctionType;
	
	/**
	 * @brief	Typedef for the bounding box computation function.
	 */
	typedef boost::function<void (Callback*)> CbbFunctionType;

	/**
	 * @brief Typedef for the paint function field.
	 */	
	typedef vgd::field::TPairAssociativeField< FunctionParameterType, PaintFunctionType > FPaintFunctionType;
	
	/**
	 * @brief Typedef for the bounding box computation function field.
	 */	
	typedef vgd::field::TPairAssociativeField< FunctionParameterType, CbbFunctionType > FCbbFunctionType;
	
		
	/**
	 * @name	Paint Function Access
	 */
	//@{
	/**
	 * @brief Sets the point function .
	 */
	void setPaintFunction( PaintFunctionType value );
	
	/**
	 * @brief Erases the paint function.
	 */
	void erasePaintFunction();
	
	/**
	 * @brief Gets the paint function.
	 */
	bool getPaintFunction( PaintFunctionType & value ) const;
	//@}


	/**
	 * @name	Bounding Box Computation Function Access
	 */
	//@{
	/**
	 * @brief Sets the bounding box computation function .
	 */
	void setCbbFunction( CbbFunctionType value );
	
	/**
	 * @brief Erases the bounding box computation function.
	 */
	void eraseCbbFunction();
	
	/**
	 * @brief Gets the bounding box computation function.
	 */
	bool getCbbFunction( CbbFunctionType & value ) const;
	//@}


	/**
	 * @name Fields names enumeration.
	 */
	//@{
	/**
	 * @brief Returns the name of paint function field.
	 * 
	 * @return the name of paint function field.
	 */
	static const std::string getFPaintFunction();

	/**
	 * @brief Returns the name of bounding box computation function field.
	 * 
	 * @return the name of bounding box computation function field.
	 */
	static const std::string getFCbbFunction();
	//@}
	
	
	/**
	 * @name	IBoundingBox Implementation
	 */
	//@{
	bool computeBoundingBox( const vgm::MatrixR& transformation );
	bool isBoundingBoxValid() const;
	void invalidateBoundingBox( bool bInvalidate = true );
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

#endif //#ifndef _VGD_NODE_CALLBACK_HPP
