// VGSDK - Copyright (C) 2004, 2006, 2007, Nicolas Papier, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier, Guillaume Brocker

#ifndef _VGD_NODE_ILAYERS_HPP
#define _VGD_NODE_ILAYERS_HPP

#include "vgd/basic/ImageUtilities.hpp"
#include "vgd/basic/ITransferFunction.hpp"
#include "vgd/field/IImageShp.hpp"
#include "vgd/field/TSingleField.hpp"
#include "vgd/field/Vector.hpp"
#include "vgd/node/Kit.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Common interface for node with layer functionnalities.
 * 
 * This node is used to compose any number of images. This is a simplified version of layout management that you can 
 * founded in Gimp.
 * Images are indexed from 0 to the number of image minus one and are drawn in this order. The first image is blended 
 * with the framebuffer using a function specifing the pixel arithmetic between the two. The result is send to 
 * the framebuffer. The same process occurs the second and the following images. More informations about image 
 * composition are given below.
 * 
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
 *  Currently not available.
 *
 * When you compose two images, each components (R,G,B and A) of the resulting pixels values are clamped to the 
 * range [0,255].
 * 
 * 
 * 
 * @par Masking.
 * 
 * SCISSOR is useful to simulate a mask that is applied to more than one image (use it for that).
 * But a mask could also be applied on a single image. Simply set the \c mask field in ComposeOperator to true. 
 * After that each pixel from the source image (not in COLOR_INDEX mode) with a value equal to (0,0,0) is considered in 
 * the mask (i.e. not drawn), all others are outside the mask (i.e. drawn). 
 * This rule is slightly different for images in COLOR_INDEX mode. After that each pixel from the source image 
 * (in COLOR_INDEX mode) with an alpha value equal to zero is considered in the mask (i.e. not drawn), all others are 
 * outside the mask (i.e. drawn).
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
 * 		Alpha value used only by INTERPOLATE and only for images not in COLOR_INDEX mode.
 * 
 * - TransferFunction \c transferFunction* = empty\n
 *		Sets the transfer function for a specific layer.
 * 
 * - SFVec3f	\c translation		= (0 0 0)\n
 * 		Sets the translation applied to all layers.
 * - SFVec3f	\c scaleFactor 		= (1 1 1)\n
 * 		Sets the scale factors applied to all layers.
 * 
 * @todo addLayers(), clearLayers()...
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API ILayers : public vgd::node::Kit
{
	/**
	 * @name Dynamic creation/destruction of layer
	 */
	//@{
	
	/**
	 * @brief Create dynamically the specified number of layers.
	 * 
	 * Call this method to create dynamically one or more \c iimage, \c composeOperator 
	 * and \c transferFunction fields.
	 * 
	 * @param num			number of layers.
	 * 
	 * @remarks Call this method before any access to layers.
	 */
	void createLayers( const int32 num );
	
	/**
	 * @brief Returns the number of layers actually used by this node.
	 * 
	 * @return The number of texture layers.
	 */
	const int32	getNumLayers() const;
	//@}



	/**
	 * @name Accessors to field iimage*
	 */
	//@{

	/**
	 * @brief Typedef for the \c iimage* field.
	 */
	typedef vgd::field::SFIImageShp			FIImageType;

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
	 * @name Accessors to field composeOperator*
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
		//MODULATE,					@todo no more supported.
		
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

		float						getAlpha() const				{ return ( m_alpha ); }
		void						setAlpha( const float value )	{ m_alpha = value; } 

		private:
		
		ComposeFunctionType		m_function;
		bool					m_mask;
		float 					m_alpha;
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
	 * @name Accessors to field transferFunction*
	 */
	//@{

	/**
	 * @brief Typedef for the \c transferFunction* field.
	 */	
	typedef vgd::field::TSingleField< vgd::Shp< vgd::basic::ITransferFunction > >	FTransferFunctionType;

	/**
	 * @brief Typedef for the \c transferFunction* value.
	 */
	typedef vgd::Shp< vgd::basic::ITransferFunction >	TransferFunctionValueType;
	
	/**
	 * @brief Accessor to \c transferFunction* field.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the \c transferFunction* field.
	 */
	vgd::field::EditorRO< FTransferFunctionType > getFTransferFunctionRO( const int32 index = 0 ) const;

	/**
	 * @brief Accessor to \c transferFunction* field.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the \c transferFunction* field.
	 */
	vgd::field::EditorRW< FTransferFunctionType > getFTransferFunctionRW( const int32 index = 0 );

	//@}



	/**
	 * @name Accessors to field translation
	 */
	//@{

	/**
	 * @brief Typedef for the \c translation field.
	 */	
	typedef vgd::field::SFVec3f	FTranslationType;
		
	/**
	 * @brief Typedef for the \c translation value.
	 */
	typedef vgm::Vec3f			TranslationValueType;

	/**
	 * @brief Gets the translation vector.
	 */
	const vgm::Vec3f		getTranslation( void ) const;

	/**
	 * @brief Sets the translation vector.
	 */
	void					setTranslation( const vgm::Vec3f translation );

	//@}



	/**
	 * @name Accessors to field scaleFactor
	 */
	//@{

	/**
	 * @brief Typedef for the \c scaleFactor field.
	 */	
	typedef vgd::field::SFVec3f	FScaleFactorType;
		
	/**
	 * @brief Typedef for the \c scaleFactor value.
	 */
	typedef vgm::Vec3f			ScaleFactorValueType;
	
	/**
	 * @brief Gets the scale factors.
	 */
	const vgm::Vec3f		getScaleFactor( void ) const;

	/**
	 * @brief Sets the scale factors.
	 */
	void					setScaleFactor( const vgm::Vec3f scaleFactor );
	
	//@}



	/**
	 * @name High level accessors to fields of this node
	 */
	//@{

	/**
	 * @brief Sets the image used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param	index		zero-base index for the layer.
	 * @param	iimage		the image.
	 */
	void sethIImage( const int32 index, vgd::Shp< vgd::basic::IImage > iimage );
	
	/**
	 * @brief Returns the image used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the layer.
	 * @return 			the image used by the specified layer.
	 * 
	 * @remark A read/write access occurs when calling this method (like getFIImageRW()). You can use the returned
	 * reference to change the image.
	 */
	vgd::Shp< vgd::basic::IImage >	gethIImage( const int32 index );

	/**
	 * @brief Returns the image used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the layer.
	 * @return 			the image used by the specified layer.
	 */
	const vgd::Shp< vgd::basic::IImage > gethIImage( const int32 index ) const;

	/**
	 * @brief	Retrives the index of the first non empty layer.
	 * 
	 * @return Returns index of the first non empty layer, otherwise -1 is returned.
	 */
	const int32 gethFirstIImage() const;
	
	/**
	 * @brief	Tests if all layers are empty.
	 * 
	 * @return true if all layers are empty, false if otherwise.
	 */
	const bool isEmpty() const;

	/**
	 * @brief Returns the image size used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the layer.
	 * @return 			the image size used by the specified layer.
	 */
	const vgm::Vec3i gethIImageSize3i( const int32 index ) const;
	
	/**
	 * @brief Returns the image size used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the layer.
	 * @return 			the image size used by the specified layer.
	 */
	const vgm::Vec3f gethIImageSize3f( const int32 index ) const;

	/**
	 * @brief	Retrieves the number of slices for the given slice type
	 * 
	 * @param	sliceType	a type of slices
	 * 
	 * @return	the number of slices
	 */
	const uint32 gethSliceCount( const ::vgd::basic::SliceType sliceType ) const;	
	
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
	 * @return			the compose operator value.
	 */
	const ComposeOperatorValueType	gethComposeOperator( const int32 index ) const;
	
	/**
	 * @brief Sets the transfer function used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index				zero-base index for the layer.
	 * @param transferFunction	the transfer function.
	 */	
	void sethTransferFunction( const int32 index, const TransferFunctionValueType& transferFunction );

	/**
	 * @brief Gets the transfer function used by the specified layer.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the layer.
	 * @return			the transfer function value.
	 */
	const TransferFunctionValueType	gethTransferFunction( const int32 index ) const;

	//@}



	/**
	 * @name Fields names enumeration
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c iimage*.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the field.
	 * 
	 * @return the name of field \c iimage*.
	 */
	static const std::string getFIImage( const int32 index );

	/**
	 * @brief Returns the name of field \c composeOperator*.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the field.
	 * 
	 * @return the name of field \c composeOperator*.
	 */
	static const std::string getFComposeOperator( const int32 index );

	/**
	 * @brief Returns the name of field \c transferFunction*.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the field.
	 * 
	 * @return the name of field \c transferFunction*.
	 */
	static const std::string getFTransferFunction( const int32 index );

	/**
	 * @brief Returns the name of field \c scaleFactor.
	 * 
	 * @return the name of field \c scaleFactor.
	 */
	static const std::string getFScaleFactor( void );

	/**
	 * @brief Returns the name of field \c translation.
	 * 
	 * @return the name of field \c translation.
	 */
	static const std::string getFTranslation( void );

	//@}

	

	/**
	 * @name Dirty flags enumeration
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when an image changed.
	 * 
	 * @pre		0 <= index < getNumLayers()
	 * 
	 * @param index		zero-base index for the field.
	 */
	static const std::string getDFIImage( const int32 index );

	/**
	 * @brief Returns name of dirty flag that is invalidate when transformation changed.
	 */
	static const std::string getDFTransformation();

	//@}

	
	
protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	ILayers( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}
	
	
	/**
	 * @brief	Extract a given slice.
	 * 
	 * Additionnaly, the method checks if there is an image for the given layer
	 * and if there is a composition operator for this layer.
	 * 
	 * @param	layer		the layer for which a slice must be extracted
	 * @param	type		the type of the slice to extract
	 * @param	position	the position of the slice to extract
	 * 
	 * @return	the extracted slice,
	 * 			or an empty shared pointer if there is no image
	 * 			or no composition operator
	 * 
	 * @pre	0 <=layer < getNumLayers()
	 */
	vgd::Shp< vgd::basic::IImage > extractSlice( const int32 layer, const vgd::basic::SliceType type, const uint32 position );
	
private:

	/**
	 * @brief Number of layers
	 */
	int32			m_numLayers;
	
	/**
	 * @brief	Index of the first image
	 */
	mutable int32	m_firstImageIndex;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ILAYERS_HPP
