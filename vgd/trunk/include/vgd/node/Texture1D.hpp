// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXTURE1D_HPP
#define _VGD_NODE_TEXTURE1D_HPP

#include "vgd/vgd.hpp"

#include "vgd/node/Texture.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Texture mapping node
 * 
 * This property node defines a texture map and parameters for that map. This map is used to apply texture to subsequent 
 * shapes as they are rendered.
 * 
 * New field added by this node :
 * 
 * - SFIImage \c [iimage]\n
 * 		Determines the source of data used to created the texture. Must be a 1d image
 * 		(iimage.height() == iimage.depth() == 0).
 * 		You can set multiple times this field, but only if all successive images have the same format.
 * 		The data and size of the image can changed, but that's all.
 * 
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_texturingNodes
 */
struct VGD_API Texture1D : public vgd::node::Texture
{
	META_NODE_HPP( Texture1D );



	/**
	 * @name Accessors to field iimage.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c iimage parameter.
	 */
	typedef IImagesParameterType IImageParameterType;

	/**
	 * @brief Typedef for the \c iimage parameter value.
	 */
	typedef vgd::Shp< vgd::basic::IImage > IImageValueType;

	/**
	 * @brief Typedef for the \c iimage field.
	 */	
	typedef vgd::field::TPairAssociativeField< IImageParameterType, IImageValueType > FIImageType;

	/**
	 * @brief Gets the \c iimage value.
	 */
	bool			getIImage( vgd::Shp< vgd::basic::IImage >& value ) const;

	/**
	 * @brief Sets the \c iimage value.
	 *
	 * Create a texture from the iimage interface to an image stored in memory (with ImageInfo) or from a 
	 * file (with Image).
	 * 
	 * @param image		reference to a 1d image.
	 *
	 * @remarks Be carefull, data referenced by image informations must be available when texture is update.
	 */	 
	void 			setIImage( vgd::Shp< vgd::basic::IImage > image );
	
	/**
	 * @brief Erase the \c iimage value.
	 */
	void 			eraseIImage();
	//@}



	// overridden method
	const uint32 gethTextureDimension() const;



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Texture1D( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();
	
	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXTURE1D_HPP
