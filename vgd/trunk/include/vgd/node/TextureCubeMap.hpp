// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXTURECUBEMAP_H
#define _VGD_NODE_TEXTURECUBEMAP_H

#include "vgd/vgd.hpp"

#include "vgd/basic/IImage.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/Texture.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Cube map texture definition node
 * 
 * This node specifies a cube map texture.
 * 
 * New field added by this node :
 * 
 * - PAFImage \c images
 * 	- [POS_X]\n
 * 		Sets the positive x face cube map texture image.
 * 
 * 	- [NEG_X]\n
 * 		Sets the negative x face cube map texture image.
 * 	
 * 	- [POS_Y]\n
 * 		Sets the positive y face cube map texture image.
 * 
 * 	- [NEG_Y]\n
 * 		Sets the negative y face cube map texture image.
 * 
 * 	- [POS_Z]\n
 * 		Sets the positive z face cube map texture image.
 * 
 * 	- [NEG_Z]\n
 * 		Sets the negative z face cube map texture image.
 * 
 * @remarks assert( width == height && "Width and height must be the same." );
 * 
 * @todo Add comments about fields (from texture) that have no or different effects with cube map texturing.
 * 
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_texturingNodes
 */
struct VGD_API TextureCubeMap : public vgd::node::Texture
{
	META_NODE_HPP( TextureCubeMap );



	/**
	 * @name Accessors to field iimages.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c iimages parameters.
	 */
	typedef enum
	{
		POS_X		= 0,
		NEG_X,
		POS_Y,
		NEG_Y,
		POS_Z,
		NEG_Z
		
	} IImagesParameterType;

	/**
	 * @brief Typedef for the \c iimages value.
	 */
	typedef vgd::Shp< vgd::basic::IImage > IImagesValueType;

	/**
	 * @brief Typedef for the \c iimages field.
	 */	
	typedef vgd::field::TPairAssociativeField< IImagesParameterType, IImagesValueType > FIImagesType;

	/**
	 * @brief Gets the iimages value.
	 */
	bool			getIImages( const IImagesParameterType param, IImagesValueType& value ) const;

	/**
	 * @brief Sets the iimages value.
	 */
	void 			setIImages( const IImagesParameterType param, IImagesValueType value );
	
	/**
	 * @brief Erase the iimages value.
	 */
	void 			eraseIImages( const IImagesParameterType param );
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c iimages.
	 * 
	 * @return the name of field \c iimages.
	 */
	static const std::string getFIImages( void );
	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 * 
	 * @internal Add field, dirty flags and link in the constructor.
	 */
	TextureCubeMap( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXTURECUBEMAP_H
