// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXTURE1D_HPP
#define _VGD_NODE_TEXTURE1D_HPP

#include "vgd/node/Texture.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Texture mapping node
 *
 * This property node defines a texture map and parameters for that map. This map is used to apply texture to subsequent shapes as they are rendered. @remarks Must be a 1d image (iimage.height() == iimage.depth() == 0). 
 *
 * No new field defined by this node.
 *
 * Inherited fields from Texture:
 * - OFString \c [fragmentFunction] = empty<br>
 *   Fragment texturing function.<br>
 *<br>
 * - PAFEnum \c wrap = REPEAT<br>
 *   Sets the wrap parameter for texture coordinate S, T or R to either REPEAT, CLAMP, CLAMP_TO_EDGE, CLAMP_TO_BORDER, MIRRORED_REPEAT or ONCE. Initially, this field is set to REPEAT for S, T and R.<br>
 *<br>
 * - OFIImageShp \c [image] = empty<br>
 *   Determines the source of data used to created the texture. You can set multiple times this field, but only if all successive images have the same format. The data and size of the image can changed, but that's all.<br>
 *<br>
 * - OFBool \c [mipmap] = false<br>
 *   Specifies if all levels of a mipmap array should be automatically updated when any modification to the image field (the base level of mipmap) is done.<br>
 *<br>
 * - PAFEnum \c filter = LINEAR<br>
 *   The texture minifying function (MIN_FILTER) is used whenever the pixel being textured maps to an area greater than one texture element. The texture magnification function (MAG_FILTER) is used when the pixel being textured maps to an area less than or equal to one texture element.<br>
 *<br>
 * - OFString \c [vertexFunction] = empty<br>
 *   Vertex texturing function.<br>
 *<br>
 * - SFEnum \c internalFormat = AUTOMATIC<br>
 *   Specifies the desired internal format used by the GPU.<br>
 *<br>
 * - SFEnum \c usage = IMAGE<br>
 *   Indicating the expected usage pattern of the texture.<br>
 *<br>
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_texturingNodes
 */
struct VGD_API Texture1D : public vgd::node::Texture
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
	static vgd::Shp< Texture1D > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Texture1D > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Texture1D > createWhole( const std::string nodeName = "DefaultWhole" );

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
	Texture1D( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Texture1D );
private:
	static const vgd::basic::RegisterNode<Texture1D> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXTURE1D_HPP
