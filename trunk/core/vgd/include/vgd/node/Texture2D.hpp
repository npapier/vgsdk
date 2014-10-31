// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXTURE2D_HPP
#define _VGD_NODE_TEXTURE2D_HPP

#include "vgd/node/Texture.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Texture mapping node
 *
 * This property node defines a texture map and parameters for that map. This map is used to apply texture to subsequent shapes as they are rendered. 
 *
 * No new field defined by this node.
 *
 * Inherited fields from Texture:
 * - SFEnum \c usage = (IMAGE)<br>
 *   Indicating the expected usage pattern of the texture.<br>
 *<br>
 * - SFEnum \c internalFormat = (AUTOMATIC)<br>
 *   Specifies the desired internal format used by the GPU.<br>
 *<br>
 * - OFIImageShp \c [image] = vgd::basic::IImageShp()<br>
 *   Determines the source of data used to created the texture. You can set multiple times this field, but only if all successive images have the same format. The data and size of the image can changed, but that's all.<br>
 *<br>
 * - OFWrappingValueType \c [wrapS] = (REPEAT)<br>
 *   Set the wrap parameter for texture coordinate s<br>
 *<br>
 * - OFWrappingValueType \c [wrapT] = (REPEAT)<br>
 *   Set the wrap parameter for texture coordinate t<br>
 *<br>
 * - OFWrappingValueType \c [wrapR] = (REPEAT)<br>
 *   Set the wrap parameter for texture coordinate r<br>
 *<br>
 * - OFFilteringValueType \c [minFilter] = (LINEAR)<br>
 *   The texture minifying function is used whenever the pixel being textured maps to an area greater than one texture element.<br>
 *<br>
 * - OFFilteringValueType \c [magFilter] = (LINEAR)<br>
 *   The texture magnification function is used when the pixel being textured maps to an area less than or equal to one texture element.<br>
 *<br>
 * - OFBool \c [mipmap] = (false)<br>
 *   Specifies if all levels of a mipmap array should be automatically updated when any modification to the image field (the base level of mipmap) is done.<br>
 *<br>
 * - OFFloat \c [maxAnisotropy] = (1.f)<br>
 *   Specifies the maximum degree of anisotropy. If not defined the value returned by Engine::getDefaultMaxAnisotropy() is used.<br>
 *<br>
 * - OFString \c [vertexFunction] = std::string()<br>
 *   Vertex texturing function.<br>
 *<br>
 * - OFString \c [fragmentFunction] = std::string()<br>
 *   Fragment texturing function.<br>
 *<br>
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_texturingNodes
 */
struct VGD_API Texture2D : public vgd::node::Texture
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
	static vgd::Shp< Texture2D > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Texture2D > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Texture2D > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{


	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}
	const uint32 gethTextureDimension() const; ///< overridden method
	void sethDefaults(); ///< overridden method


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
	Texture2D( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( Texture2D );
private:
	static const vgd::basic::RegisterNode<Texture2D> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXTURE2D_HPP
