// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LAYERS_H
#define _VGD_NODE_LAYERS_H

#include "vgd/vgd.hpp"

#include "vgd/field/Image.hpp"
#include "vgd/field/TSingleField.hpp"
#include "vgd/node/Kit.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Layers definition node.
 * 
 * This node is used to compose any number of images on a quadrilateral object. This is a simplified version of layout 
 * management that you can founded in Gimp, but the quadrilateral is drawn in a three dimension space.
 * Images are indexed from 0 to the number of image minus one and are drawn in this order. The first image is blended 
 * with the framebuffer using a function specifing the pixel arithmetic between the two. The result is send to 
 * the framebuffer. The same process occurs the second and the following images. More informations about image 
 * composition are given below.
 * 
 * To simulate 2D layout management, move the quadrilateral in front of the rendering window and align it to axis \c x 
 * and \axis \c y.
 * 
 * @par Compose functions.
 * 
 * Used notations :
 * - C for RGB triple color.
 * - A for alpha value.
 * - C or A could be followed by an \c s or \c d to specify respectively the source (images from layers) or the 
 *		destination (the framebuffer) of the color.
 *
 * The image composition is controlled by an operator that can have one of values among :
 *
 * - COMPOSE_FUNCTION_NONE\n
 * 	The source image is not drawn. The compositing formulas are Cd = Cd and Ad = Ad.
 * 
 * - REPLACE\n
 * 	Each pixels from the source image is drawn in the framebuffer. The compositing formulas are Cd = Cs and Ad = As.
 * 
 * - INTERPOLATE\n
 * 	An interpolation is done between the source image and the framebuffer. An additionnal value, named \c alpha is 
 * 	used to control this interpolation given by formulas Cd = alpha * Cs  +  (1-alpha) * Cd and 
 * 	As = alpha * As  +  (1-alpha) * Ad
 * 
 * - SCISSOR\n
 * 	Use it to simulate a mask. Each pixel from the source image with a value equal to (0,0,0) is considered in the 
 * 	mask (i.e. not drawn), all others are outside the mask (i.e. drawn).
 * 	This operator draw nothing, but following images are drawn with an additionnal restriction given by formulas
 * 	Cd = func(Cs) and Ad = func(As) only if pixel does not lie inside the mask,
 * 	otherwise Cd = Cd and Ad = Ad
 * 	with func() the function used to compose two images.
 * 
 *	- MODULATE\n
 * 	Multiplies the source image with the framebuffer with the following formulas Cd = Cs*Cd and Ad = As*Ad
 *
 * When you compose two images, each components (R,G,B and A) of the resulting pixels values are clamped to the 
 * range [0,255].
 * 
 * 
 * 
 * @par Masking.
 * 
 * SCISSOR is useful to simulate a mask that is applied to more than one image (use it for that).
 * But a mask could also be applyed on a single image. Simply set the \c mask field in ComposeOperator to true. After 
 * that each pixel from the source image with a value equal to (0,0,0) is considered in the mask (i.e. not drawn), 
 * all others are outside the mask (i.e. drawn).
 * Masking functionnalities are available at two levels : with a scissor image and with the alpha channel of each image.
 * When both are used at the same time, the rule is simple. Scissor image can only add pixels to the mask.
 * If a pixel belongs to the mask at the scissor image, it's is never drawn whetever the alpha channel value in the 
 * source image.
 *
 * New field added by this node :
 * 
 * - IImage \c iimage* = empty\n
 * 	Sets the image for a specific layer.
 * 
 * - ComposeOperator \c composeOperator* = empty\n
 * 	- function = COMPOSE_FUNCTION_NONE\n
 * 		Choose one value among COMPOSE_FUNCTION_NONE, REPLACE, INTERPOLATE, SCISSOR and MODULATE.
 * 		COMPOSE_FUNCTION_NONE is the default value.
 * 	- mask = false\n
 * 		true if a mask is activate during compositing, false if not.
 * 	- alpha = 0.5f\n
 * 		Alpha value used only by INTERPOLATE.
 * 
 * @bug	when a scissor composite operator is changed to another one. All following images must be invalidate.
 * @todo [MUST BE DONE] Palette texture (very useful for “fênetrage” and decrease the memory requirements).
 * @todo BOTTLENECK: SCISSOR is partially done in software !!!
 * @todo Hints about usage on image (STATIC and DYNAMIC).
 * @todo Mipmapping (useful only for STATIC images).
 * @todo [MUST BE DONE] Allow transformation to be applied to each layer.
 * @todo Texture compression.
 * @todo Use multitexturing and more... (rendering speed).
 * @todo Computing the resulting image (useful in 3D mode to not recompute Layers for each new frame).
 * @todo Add support for grayscale and boolean image (RGBA is very memory hungry).
 * @todo Support image that are not stored contiguously in memory (this is the case for inrimage).
 * @todo Allow dynamic modification for the number of layer in a vgd::node::Layers.
 * @todo Support images with differents sizes.
 * @todo Polish the current implementation
 * @todo Add an UNSCISSOR composite operator to disable scissor.
 * @todo “Fênetrage” is not done by the Layers node.
 * @todo think of smarter bounding box computation for nodekit (see computeBoundingBox() and vge::handler::cbb::Layers).
 * @todo Destruction of field (removeLayers())
 * 
 * @ingroup g_nodes
 * @ingroup g_nodekits
 */
struct VGD_API Layers : public vgd::node::Kit
{
	META_NODE_HPP( Layers );



	/**
	 * @name Dynamic creation/destruction of layer.
	 */
	//@{
	
	/**
	 * @brief Create dynamically the specified number of layers.
	 * 
	 * Call this method to create dynamically one or more \c iimage and \c composeOperator fields.
	 * 
	 * @param num			number of layers.
	 * @param width		width of the quad.
	 * @param height		height of the quad.
	 * 
	 * @remarks Call this method before any access to layers.
	 */
	void createLayers( const int32 num = 1, const float width = 1.f, const float height = 1.f );
	
	/**
	 * @brief Returns the number of layers actually used by this node.
	 * 
	 * @return The number of texture layers.
	 * 
	 * @remarks This method is relatively slow.
	 */
	const int32	getNumLayers() const;
	//@}



	/**
	 * @name Accessors to field iimage*.
	 */
	//@{

	/**
	 * @brief Typedef for the \c iimage* field.
	 */	
	typedef vgd::field::SFIImage				FIImageType;

	/**
	 * @brief Typedef for the \c iimage* value.
	 */
	typedef vgd::Shp< vgd::basic::IImage >	IImageValueType;
	
	/**
	 * @brief Accessor to \c iimage* field.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the \c iimage* field.
	 */
	vgd::field::EditorRO< FIImageType > getFIImageRO( const int32 index = 0 ) const;

	/**
	 * @brief Accessor to \c iimage* field.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the \c iimage* field.
	 */
	vgd::field::EditorRW< FIImageType > getFIImageRW( const int32 index = 0 );

	//@}
	
	

	/**
	 * @name Accessors to field composeOperator*.
	 */
	//@{

	/**
	 * @brief Typedef for the \c compose \c function.
	 */
	typedef enum {
		
		COMPOSE_FUNCTION_NONE = 0,
		REPLACE,
		INTERPOLATE,
		SCISSOR,
		MODULATE,
		
		COMPOSE_FUNCTION_DEFAULT = COMPOSE_FUNCTION_NONE

	} ComposeFunctionType;

	/**
	 * @brief Typedef for the \c composeOperator* value.
	 */
	struct ComposeOperator
	{
		ComposeOperator(	const ComposeFunctionType function = COMPOSE_FUNCTION_DEFAULT, 
								bool mask = false, float alpha = 0.5f ) :
			m_function	( function ),
			m_mask		( mask ),
			m_alpha		( alpha )
		{
		}
		
		ComposeFunctionType	getFunction() const	{ return ( m_function ); }
		void						setFunction( const ComposeFunctionType value ) { m_function = value; }
		
		bool						hasMask() const					{ return ( m_mask ); } 
		void						setMask( const bool mask )		{ m_mask = mask; }

		float						getAlpha() const		{ return ( m_alpha ); }
		void						setAlpha( const float value ) { m_alpha = value; } 

		private:
			ComposeFunctionType		m_function;
			bool							m_mask;
			float 						m_alpha;
	};

	typedef ComposeOperator ComposeOperatorValueType;
	
	/**
	 * @brief Typedef for the \c composeOperator* field.
	 */
	typedef vgd::field::TSingleField< ComposeOperator >	FComposeOperatorType;
	
	/**
	 * @brief Accessor to \c composeOperator* field.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the \c composeOperator* field.
	 */
	vgd::field::EditorRO< FComposeOperatorType > getFComposeOperatorRO( const int32 index = 0 ) const;

	/**
	 * @brief Accessor to \c composeOperator* field.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the \c composeOperator* field.
	 */
	vgd::field::EditorRW< FComposeOperatorType > getFComposeOperatorRW( const int32 index = 0 );

	//@}






	/**
	 * @name High level accessors to fields of this node.
	 */
	//@{

	/**
	 * @brief Sets the image used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param	index			zero-base index for the layer.
	 * @param	iimage		the image.
	 */
	void sethIImage( const int32 index, vgd::Shp< vgd::basic::IImage > iimage );
	
	/**
	 * @brief Returns the image used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the layer.
	 * @return 				the image used by the specified layer.
	 * 
	 * @remark A read/write access occurs when calling this method (like getFIImageRW()). You can use the returned
	 * reference to change the image.
	 */
	vgd::Shp< vgd::basic::IImage >	gethIImage( const int32 index );

	/**
	 * @brief Sets the compose operator used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index				zero-base index for the layer.
	 * @param composeOperator	the compose operator.
	 */	
	void sethComposeOperator( const int32 index, const ComposeOperatorValueType& composeOperator );

	/**
	 * @brief Gets the compose operator used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the layer.
	 * @return				the compose operator value.
	 */
	const ComposeOperatorValueType	gethComposeOperator( const int32 index );
	//@}



	/**
	 * @name Useful scanning image methods.
	 */
	//@{
	
	/**
	 * @brief Scan the whole image and set alpha value of each pixel to \c alpha.
	 * 
	 * @pre image.format() == RGBA
	 * @pre image.type() == UINT8
	 * @pre 0 <= alpha <= 1
	 * 
	 * @param image		image to scan.
	 * @param alpha		alpha value to assign.
	 */
	void	setAlpha( vgd::Shp< vgd::basic::IImage > image, const float alpha = 1.f );

	/**
	 * @brief Scan the whole image and modify alpha value of each pixel.
	 * 
	 * Sets alpha value of each pixel to \c alpha only if pixel color is != (0,0,0), otherwise sets alpha value to zero.
	 * 
	 * @pre image.format() == RGBA
	 * @pre image.type() == UINT8
	 * @pre 0 <= alpha <= 1
	 * 
	 * @param image		image to scan.
	 * @param alpha		alpha value to assign.
	 */
	void	setAlphaIfNotBlack( vgd::Shp< vgd::basic::IImage > image, const float alpha = 1.f );
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c iimage*.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index					zero-base index for the field.
	 * 
	 * @return the name of field \c iimage*.
	 */
	static const std::string getFIImage( const int32 index );

	/**
	 * @brief Returns the name of field \c composeOperator*.
	 * 
	 * @param index					zero-base index for the field.
	 * 
	 * @return the name of field \c composeOperator*.
	 */
	static const std::string getFComposeOperator( const int32 index );

	//@}

	

	/**
	 * @name Dirty flags enumeration.
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when an image changed.
	 * 
	 * @param index					zero-base index for the field.
	 */
	static const std::string getDFIImage( const int32 index );

	//@}	
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Layers( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_LAYERS_H
