// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXTURE_HPP
#define _VGD_NODE_TEXTURE_HPP

#include "vgd/vgd.hpp"

#include <vgm/Vector.hpp>
#include "vgd/basic/IImage.hpp"
#include "vgd/field/TPairAssociativeField.hpp"

#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract texture mapping node
 * 
 * This node defines texture parameters (wrapping, filters, mipmapping, border, environnement color and 
 * function/combine).
 * 
 * @remarks You MUST define at least the \c wrap, \c filter and \c function fields.
 * 
 * New field added by this node :
 * 
 * - PAFInt32 \c wrap
 *  - [WRAP_S]\n
 * 		Choose one value among :
 * 			- REPEAT (default)
 * 			- CLAMP
 * 			- CLAMP_TO_EDGE
 * 			- CLAMP_TO_BORDER
 * 			- MIRRORED_REPEAT
 * 			- ONCE ( don't set texture coordinates outside the interval [0.f, 1.f] ).

 * 	- [WRAP_T]\n
 * 		Choose one value among REPEAT (default), CLAMP, CLAMP_TO_EDGE, CLAMP_TO_BORDER, MIRRORED_REPEAT or ONCE.
 * 
 * 	- [WRAP_R]\n
 * 		Choose one value among REPEAT (default), CLAMP, CLAMP_TO_EDGE, CLAMP_TO_BORDER, MIRRORED_REPEAT or ONCE.
 * 
 * - PAFInt32 \c filter
 * 
 * 	- [MIN_FILTER]\n
 * 		Choose one value among NEAREST, LINEAR (default), NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR,
 * 			LINEAR_MIPMAP_LINEAR.
 * 
 * 	- [MAG_FILTER]\n
 * 		Choose one value among NEAREST or LINEAR (default).
 * 
 * - PAFBool \c [mipmap] = true\n
 * 
 * - PAFVec4f \c [border] = (0,0,0,0)\n
 * 
 * - PAFVec4f \c [envColor] = (0,0,0,0)\n
 * 
 * - PAFInt32 \c [function] = FUN_MODULATE\n
 * 	Choose a value among FUN_REPLACE, FUN_MODULATE, FUN_DECAL, FUN_BLEND, FUN_ADD and FUN_COMBINE.
 * 
 * - PAFInt32 combine
 * 	- [RGB]\n
 * 		Choose a value among REPLACE, MODULATE, ADD, ADD_SIGNED, INTERPOLATE, SUBTRACT, DOT3_RGB or DOT3_RGBA.
 * 	- [ALPHA]\n
 * 		Choose a value among REPLACE, MODULATE, ADD, ADD_SIGNED, INTERPOLATE, or SUBTRACT.
 * 
 * - PAFInt32 source
 * 	- [RGB0]\n
 * 		Choose a value among CONSTANT, PRIMARY_COLOR, PREVIOUS, TEXTURE or TEXTUREn.
 * 	- [RGB1]\n
 * 		Choose a value among CONSTANT, PRIMARY_COLOR, PREVIOUS, TEXTURE or TEXTUREn.
 * 	- [RGB2]\n
 * 		Choose a value among CONSTANT, PRIMARY_COLOR, PREVIOUS, TEXTURE or TEXTUREn.
 * 	- [ALPHA0]\n
 * 		Choose a value among CONSTANT, PRIMARY_COLOR, PREVIOUS, TEXTURE or TEXTUREn.
 * 	- [ALPHA1]\n
 * 		Choose a value among CONSTANT, PRIMARY_COLOR, PREVIOUS, TEXTURE or TEXTUREn.
 * 	- [ALPHA2]\n
 * 		Choose a value among CONSTANT, PRIMARY_COLOR, PREVIOUS, TEXTURE or TEXTUREn.
 * 
 * - PAFInt32 operand
 * 	- [RGB0]\n
 * 		Choose a value among SRC_COLOR, ONE_MINUS_SRC_COLOR, SRC_ALPHA or ONE_MINUS_SRC_ALPHA.
 *	- [RGB1]\n
 * 		Choose a value among SRC_COLOR, ONE_MINUS_SRC_COLOR, SRC_ALPHA or ONE_MINUS_SRC_ALPHA.
 * 	- [RGB2]\n
 * 		Choose a value among SRC_COLOR, ONE_MINUS_SRC_COLOR, SRC_ALPHA or ONE_MINUS_SRC_ALPHA.
 * 	- [ALPHA0]\n
 *			Choose a value among SRC_ALPHA or ONE_MINUS_SRC_ALPHA.
 * 	- [ALPHA1]\n
 *			Choose a value among SRC_ALPHA or ONE_MINUS_SRC_ALPHA.
 * 	- [ALPHA2]\n
 *			Choose a value among SRC_ALPHA or ONE_MINUS_SRC_ALPHA.
 *
 * - PAFFloat scale
 * 	- [RGB_SCALE]\n
 *			Choose a value among 1.0, 2.0 or 4.0.
 * 	- [ALPHA_SCALE]\n
 *			Choose a value among 1.0, 2.0 or 4.0.
 * 
 * - PAFImage \c [images]
 * 		Generic repository of images used to specify texture images. Don't use this field unless knowing exactly what
 * 		you do.
 *
 * @remarks When you evaluate scene graph with vgeGL, there are two constraints that you should keep in mind :
 * 	- When the image exceed the maximum allowable size for the texture, a temporary resized copy of the \c iimage(to 
 * 		the maximum of the texture size) is used for defining texture. This is not very fast. Be carefull. 
 * 		For example :
 * 		- Radeon 8500 could do 2048 x 2048 for 2D texturing, 512 x 512 x 512 for 3D texturing and 2048 for cube mapping. 
 * 		- GeForce 2 could do 2048 x 2048 for 2D texturing, 64 x 64 x 64 for 3D texturing and 512 for cube mapping. 
 * 		- GeForce 3 could do 4096 x 4096 for 2D texturing, 512 x 512 x 512 for 3D texturing and 4096 for cube mapping.
 * 		- GeForce FX could do 4096 x 4096 for 2D texturing, 512 x 512 x 512 for 3D texturing and 4096 for cube mapping.
 * 	- If your OpenGL implementation does'nt support advanced texturing not limited to images with power-of-two 
 * 		dimensions, a temporary resized copy of the \c iimage is used for all wrapping modes except \c ONCE.
 * 
 * @todo Add documentation about used OpenGL extensions (like GL_ARB_texture_env_combine, GL_texture_env_crossbar).
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API Texture : public vgd::node::MultiAttribute
{
	//META_NODE_HPP( Texture );



	/**
	 * @name Accessors to field iimages.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c iimages parameters.
	 */
	typedef enum
	{
		IIMAGE_1 = 1,
		IIMAGE_2,
		IIMAGE_3,
		IIMAGE_4,
		IIMAGE_5,
		IIMAGE_6,
		DEFAULT_IIMAGES = IIMAGE_1
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
	 * @name Accessors to field wrap.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c wrap parameters.
	 */
	typedef enum
	{
		WRAP_S = 0,
		WRAP_T,
		WRAP_R			/*!< GL 1.2 */
	} WrapParameterType;

	/**
	 * @brief Typedef for the \c wrap value.
	 */
	typedef enum {

		REPEAT	= 0,
		CLAMP,
		CLAMP_TO_EDGE,			/*!< GL 1.2 */
		CLAMP_TO_BORDER,		/*!< GL 1.3 */
		MIRRORED_REPEAT,		/*!< GL 1.4 */
		
		ONCE,

		DEFAULT_WRAP		= REPEAT
	} WrapValueType;

	/**
	 * @brief Typedef for the \c wrap field.
	 */	
	typedef vgd::field::TPairAssociativeField< WrapParameterType, WrapValueType > FWrapType;

	/**
	 * @brief Gets the wrap value.
	 */
	bool			getWrap( const WrapParameterType param, WrapValueType& value ) const;

	/**
	 * @brief Sets the wrap value.
	 */
	void 			setWrap( const WrapParameterType param, WrapValueType value );
	
	/**
	 * @brief Erase the wrap value.
	 */
	void 			eraseWrap( const WrapParameterType param );
	//@}



	/**
	 * @name Accessors to field filter.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c filter parameters.
	 */
	typedef enum {
		
		MIN_FILTER = 0,
		MAG_FILTER
		
	} FilterParameterType;

	/**
	 * @brief Typedef for the \c filter value.
	 */
	typedef enum {

		NEAREST	= 0,
		LINEAR,

		NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR,

		DEFAULT_FILTER					= LINEAR
		
	} FilterValueType;

	/**
	 * @brief Typedef for the \c filter field.
	 */	
	typedef vgd::field::TPairAssociativeField< FilterParameterType, FilterValueType > FFilterType;

	/**
	 * @brief Gets the filter value.
	 */
	bool			getFilter( const FilterParameterType param, FilterValueType& value ) const;

	/**
	 * @brief Sets the filter value.
	 */
	void 			setFilter( const FilterParameterType param, FilterValueType value );
	
	/**
	 * @brief Erase the filter value.
	 */
	void 			eraseFilter( const FilterParameterType param );
	//@}



	/**
	 * @name Accessors to field mipmap.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c mipmap parameter.
	 */
	typedef enum
	{
		MIPMAP = 0
	} MipmapParameterType;

	/**
	 * @brief Typedef for the \c mipmap parameter value.
	 */
	typedef bool MipmapValueType;

	/**
	 * @brief Typedef for the \c mipmap field.
	 */	
	typedef vgd::field::TPairAssociativeField< MipmapParameterType, MipmapValueType > FMipmapType;

	/**
	 * @brief Gets the \c mipmap value.
	 */
	bool			getMipmap( MipmapValueType& value ) const;

	/**
	 * @brief Sets the \c mipmap value.
	 */
	void 			setMipmap( MipmapValueType value );
	
	/**
	 * @brief Erase the \c mipmap value.
	 */
	void 			eraseMipmap();
	//@}



	/**
	 * @name Accessors to field border.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c border parameter.
	 */
	typedef enum
	{
		BORDER = 0
	} BorderParameterType;

	/**
	 * @brief Typedef for the \c border parameter value.
	 */
	typedef vgm::Vec4f BorderValueType;

	/**
	 * @brief Typedef for the \c border field.
	 */	
	typedef vgd::field::TPairAssociativeField< BorderParameterType, BorderValueType > FBorderType;

	/**
	 * @brief Gets the \c border value.
	 */
	bool			getBorder( BorderValueType& value ) const;

	/**
	 * @brief Sets the \c border value.
	 */
	void 			setBorder( BorderValueType value );
	
	/**
	 * @brief Erase the \c border value.
	 */
	void 			eraseBorder();
	//@}

	
	
	/**
	 * @name Accessors to field envColor.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c envColor parameter.
	 */
	typedef enum
	{
		ENV_COLOR = 0
	} EnvColorParameterType;

	/**
	 * @brief Typedef for the \c envColor parameter value.
	 */
	typedef vgm::Vec4f EnvColorValueType;

	/**
	 * @brief Typedef for the \c envColor field.
	 */	
	typedef vgd::field::TPairAssociativeField< EnvColorParameterType, EnvColorValueType > FEnvColorType;

	/**
	 * @brief Gets the \c envColor value.
	 */
	bool			getEnvColor( EnvColorValueType& value ) const;

	/**
	 * @brief Sets the \c envColor value.
	 */
	void 			setEnvColor( EnvColorValueType value );
	
	/**
	 * @brief Erase the \c envColor value.
	 */
	void 			eraseEnvColor();
	//@}



	/**
	 * @name Accessors to field function.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c function parameters.
	 */
	typedef enum {
		FUNCTION
	} FunctionParameterType;

	/**
	 * @brief Typedef for the \c function value.
	 */
	typedef enum
	{
		FUN_REPLACE = 0,
		FUN_MODULATE, 
		FUN_DECAL, 
		FUN_BLEND, 
		
		FUN_ADD,
		FUN_COMBINE,
		
		DEFAULT_FUN = FUN_MODULATE
	} FunctionValueType;

	/**
	 * @brief Typedef for the \c function field.
	 */	
	typedef vgd::field::TPairAssociativeField< FunctionParameterType, FunctionValueType > FFunctionType;

	/**
	 * @brief Gets the function value.
	 */
	bool			getFunction( FunctionValueType& value ) const;

	/**
	 * @brief Sets the function value.
	 */
	void 			setFunction( FunctionValueType value );
	
	/**
	 * @brief Erase the function value.
	 */
	void 			eraseFunction();
	//@}



	/**
	 * @name Accessors to field combine.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c combine parameters.
	 */
	typedef enum
	{
		RGB = 0,
		ALPHA
	} CombineParameterType;

	/**
	 * @brief Typedef for the \c combine value.
	 */
	typedef enum {
		REPLACE = 0,
		MODULATE, 
		ADD, 
		ADD_SIGNED, 
		INTERPOLATE,
		SUBTRACT,
		DOT3_RBG,
		DOT3_RGBA
	} CombineValueType;

	/**
	 * @brief Typedef for the \c combine field.
	 */	
	typedef vgd::field::TPairAssociativeField< CombineParameterType, CombineValueType > FCombineType;

	/**
	 * @brief Gets the combine value.
	 */
	bool			getCombine( const CombineParameterType param, CombineValueType& value ) const;

	/**
	 * @brief Sets the combine value.
	 */
	void 			setCombine( const CombineParameterType param, CombineValueType value );
	
	/**
	 * @brief Erase the combine value.
	 */
	void 			eraseCombine( const CombineParameterType param );
	//@}




	/**
	 * @name Accessors to field source.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c source parameters.
	 */
	typedef enum
	{
		RGB0 = 0,
		RGB1,
		RGB2,
		
		ALPHA0,
		ALPHA1,
		ALPHA2

	} SourceParameterType;
 
	/**
	 * @brief Typedef for the \c source value.
	 */
	typedef enum {
		
		CONSTANT = 0,
		PRIMARY_COLOR,
		PREVIOUS,
		TEXTURE,
		TEXTURE0=TEXTURE,
		TEXTURE1,
		TEXTURE2,
		TEXTURE3,
		TEXTURE4,
		TEXTURE5,
		TEXTURE6,
		TEXTURE7,
		TEXTURE8,
		TEXTURE9,
		TEXTURE10,
		TEXTURE11,
		TEXTURE12,
		TEXTURE13,
		TEXTURE14,
		TEXTURE15,
		TEXTURE16,
		TEXTURE17,
		TEXTURE18,
		TEXTURE19,
		TEXTURE20,
		TEXTURE21,
		TEXTURE22,
		TEXTURE23,
		TEXTURE24,
		TEXTURE25,
		TEXTURE26,
		TEXTURE27,
		TEXTURE28,
		TEXTURE29,
		TEXTURE30,
		TEXTURE31

	} SourceValueType;

	/**
	 * @brief Typedef for the \c source field.
	 */	
	typedef vgd::field::TPairAssociativeField< SourceParameterType, SourceValueType > FSourceType;

	/**
	 * @brief Gets the source value.
	 */
	bool			getSource( const SourceParameterType param, SourceValueType& value ) const;

	/**
	 * @brief Sets the source value.
	 */
	void 			setSource( const SourceParameterType param, SourceValueType value );
	
	/**
	 * @brief Erase the source value.
	 */
	void 			eraseSource( const SourceParameterType param );
	//@}



	/**
	 * @name Accessors to field operand.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c operand parameters.
	 */
	typedef SourceParameterType /*enum
	{
		RGB0 = 0,
		RGB1,
		RGB2,
		
		ALPHA0,
		ALPHA1,
		ALPHA2
		
	} */OperandParameterType;
 
	/**
	 * @brief Typedef for the \c operand value.
	 */
	typedef enum {

		SRC_COLOR = 0,
		ONE_MINUS_SRC_COLOR,
		SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA
	} OperandValueType;

	/**
	 * @brief Typedef for the \c operand field.
	 */	
	typedef vgd::field::TPairAssociativeField< OperandParameterType, OperandValueType > FOperandType;

	/**
	 * @brief Gets the operand value.
	 */
	bool			getOperand( const OperandParameterType param, OperandValueType& value ) const;

	/**
	 * @brief Sets the operand value.
	 */
	void 			setOperand( const OperandParameterType param, OperandValueType value );
	
	/**
	 * @brief Erase the operand value.
	 */
	void 			eraseOperand( const OperandParameterType param );
	//@}



	/**
	 * @name Accessors to field scale.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c scale parameters.
	 */
	typedef CombineParameterType /*enum
	{
		RGB = 0,
		ALPHA
	} */ScaleParameterType;
 
	/**
	 * @brief Typedef for the \c scale value.
	 */
	typedef float ScaleValueType;

	/**
	 * @brief Typedef for the \c scale field.
	 */	
	typedef vgd::field::TPairAssociativeField< ScaleParameterType, ScaleValueType > FScaleType;

	/**
	 * @brief Gets the scale value.
	 */
	bool			getScale( const ScaleParameterType param, ScaleValueType& value ) const;

	/**
	 * @brief Sets the scale value.
	 */
	void 			setScale( const ScaleParameterType param, ScaleValueType value );
	
	/**
	 * @brief Erase the scale value.
	 */
	void 			eraseScale( const ScaleParameterType param );
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

	/**
	 * @brief Returns the name of field \c wrap.
	 * 
	 * @return the name of field \c wrap.
	 */
	static const std::string getFWrap( void );
	
	/**
	 * @brief Returns the name of field \c filter.
	 * 
	 * @return the name of field \c filter.
	 */
	static const std::string getFFilter( void );
	
	/**
	 * @brief Returns the name of field \c mipmap.
	 * 
	 * @return the name of field \c mipmap.
	 */
	static const std::string getFMipmap( void );	

	/**
	 * @brief Returns the name of field \c border.
	 * 
	 * @return the name of field \c border.
	 */
	static const std::string getFBorder( void );	
	
	/**
	 * @brief Returns the name of field \c envColor.
	 * 
	 * @return the name of field \c envColor.
	 */
	static const std::string getFEnvColor( void );
	
	/**
	 * @brief Returns the name of field \c function.
	 * 
	 * @return the name of field \c function.
	 */
	static const std::string getFFunction( void );
	
	/**
	 * @brief Returns the name of field \c combine.
	 * 
	 * @return the name of field \c combine.
	 */
	static const std::string getFCombine( void );
	
	/**
	 * @brief Returns the name of field \c source.
	 * 
	 * @return the name of field \c source.
	 */
	static const std::string getFSource( void );

	/**
	 * @brief Returns the name of field \c operand.
	 * 
	 * @return the name of field \c operand.
	 */
	static const std::string getFOperand( void );

	/**
	 * @brief Returns the name of field \c scale.
	 * 
	 * @return the name of field \c scale.
	 */
	static const std::string getFScale( void );

	//@}



	/**
	 * @name Dirty flags enumeration.
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when at least one image has changed.
	 */
	static const std::string getDFIImages();

	/**
	 * @brief Returns name of dirty flag that is invalidate when texture parameters changed.
	 */
	static const std::string getDFParameters();

	//@}		



	/**
	 * @name High-level accessors
	 */
	//@{
	
	/**
	 * @brief Returns the dimension of this texture node.
	 * 
	 * @return dimension of this texture node
	 */
	virtual const uint32 gethTextureDimension() const=0;
	
	//@}


protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Texture( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXTURE_HPP
