// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_POSTPROCESSING_HPP
#define _VGD_NODE_POSTPROCESSING_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/MatrixR.hpp"
#include "vgd/field/String.hpp"
#include "vgd/field/Vec4f.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief A single stage of a post-processing pipeline.
 *
 * This node defines a single stage of a post-processing pipeline, i.e. a \c filter function applied on each pixel of the drawing surface with up to 3 input buffers, several parameters and one output buffer. Typical use-case of post-processing pipeline is to apply effect to the the previously rendered scene like depth of field, bloom and so on. 
 *
 * New fields defined by this node :
 * - SFEnum \c input2 = INPUT2_NONE<br>
 *   Specifies the third input buffer used by the filter.<br>
 *<br>
 * - SFEnum \c input0 = PREVIOUS0<br>
 *   Specifies the first input buffer used by the filter.<br>
 *<br>
 * - SFEnum \c input1 = INPUT1_NONE<br>
 *   Specifies the second input buffer used by the filter.<br>
 *<br>
 * - SFString \c customFilterDefinition = empty<br>
 *   Specifies the code implementing the filter.<br>
 *<br>
 * - SFEnum \c filter = NO_FILTER<br>
 *   Specifies the filter to apply to the input buffers.<br>
 *<br>
 * - OFVec4f \c [param4f1] = vgm::Vec4f(0.0, 0.0, 0.0, 0.0)<br>
 *   Specifies the second 4f parameter used by the filter.<br>
 *<br>
 * - OFVec4f \c [param4f0] = vgm::Vec4f(0.0, 0.0, 0.0, 0.0)<br>
 *   Specifies the first 4f parameter used by the filter.<br>
 *<br>
 * - OFMatrixR \c [param4x4f0] = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Specifies the first 4x4f parameter used by the filter.<br>
 *<br>
 * - SFString \c customFilterApply = empty<br>
 *   Specifies the code calling the filter defined by customFilterDefinition.<br>
 *<br>
 * - SFEnum \c output = OUTPUT_TMP0<br>
 *   Specifices the output buffer used by the filter.<br>
 *<br>
 * - OFFloat \c [param1f0] = 0.0<br>
 *   Specifies the first 1f parameter used by the filter.<br>
 *<br>
 * - OFFloat \c [param1f1] = 0.0<br>
 *   Specifies the second 1f parameter used by the filter.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_autoMultiAttributeNodes
 * @ingroup g_texturingNodes
 * @ingroup g_frameBufferNodes
 * @ingroup g_postProcessing
 */
struct VGD_API PostProcessing : public vgd::node::MultiAttribute
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
	static vgd::Shp< PostProcessing > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< PostProcessing > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< PostProcessing > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field input2
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		INPUT2_PREVIOUS0 = 369,	///< 
		INPUT2_OUTPUT_BUFFER0 = 361,	///< 
		INPUT2_OUTPUT_BUFFER1 = 362,	///< 
		INPUT2_OUTPUT_BUFFER2 = 363,	///< 
		INPUT2_OUTPUT_BUFFER3 = 364,	///< 
		INPUT2_OUTPUT_BUFFER4 = 365,	///< 
		INPUT2_OUTPUT_BUFFER5 = 366,	///< 
		INPUT2_OUTPUT_BUFFER6 = 367,	///< 
		INPUT2_OUTPUT_BUFFER7 = 368,	///< 
		INPUT2_NONE = 370,	///< 
		DEFAULT_INPUT2 = INPUT2_NONE	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct Input2ValueType : public vgd::field::Enum
	{
		Input2ValueType()
		{}

		Input2ValueType( const int v )
		: vgd::field::Enum(v)
		{}

		Input2ValueType( const Input2ValueType& o )
		: vgd::field::Enum(o)
		{}

		Input2ValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 361 );
			retVal.push_back( 362 );
			retVal.push_back( 363 );
			retVal.push_back( 364 );
			retVal.push_back( 365 );
			retVal.push_back( 366 );
			retVal.push_back( 367 );
			retVal.push_back( 368 );
			retVal.push_back( 369 );
			retVal.push_back( 370 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "INPUT2_OUTPUT_BUFFER0" );
			retVal.push_back( "INPUT2_OUTPUT_BUFFER1" );
			retVal.push_back( "INPUT2_OUTPUT_BUFFER2" );
			retVal.push_back( "INPUT2_OUTPUT_BUFFER3" );
			retVal.push_back( "INPUT2_OUTPUT_BUFFER4" );
			retVal.push_back( "INPUT2_OUTPUT_BUFFER5" );
			retVal.push_back( "INPUT2_OUTPUT_BUFFER6" );
			retVal.push_back( "INPUT2_OUTPUT_BUFFER7" );
			retVal.push_back( "INPUT2_PREVIOUS0" );
			retVal.push_back( "INPUT2_NONE" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c input2
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FInput2Type;


	/**
	 * @brief Gets the value of field named \c input2.
	 */
	const Input2ValueType getInput2() const;

	/**
	 * @brief Sets the value of field named \c input2.
	 */
	void setInput2( const Input2ValueType value );

	//@}



	/**
	 * @name Accessors to field input0
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		NONE = 350,	///< 
		PREVIOUS0 = 349,	///< 
		OUTPUT_BUFFER6 = 347,	///< 
		OUTPUT_BUFFER7 = 348,	///< 
		OUTPUT_BUFFER4 = 345,	///< 
		OUTPUT_BUFFER5 = 346,	///< 
		OUTPUT_BUFFER2 = 343,	///< 
		OUTPUT_BUFFER3 = 344,	///< 
		OUTPUT_BUFFER0 = 341,	///< 
		OUTPUT_BUFFER1 = 342,	///< 
		DEFAULT_INPUT0 = PREVIOUS0	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct Input0ValueType : public vgd::field::Enum
	{
		Input0ValueType()
		{}

		Input0ValueType( const int v )
		: vgd::field::Enum(v)
		{}

		Input0ValueType( const Input0ValueType& o )
		: vgd::field::Enum(o)
		{}

		Input0ValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 341 );
			retVal.push_back( 342 );
			retVal.push_back( 343 );
			retVal.push_back( 344 );
			retVal.push_back( 345 );
			retVal.push_back( 346 );
			retVal.push_back( 347 );
			retVal.push_back( 348 );
			retVal.push_back( 349 );
			retVal.push_back( 350 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "OUTPUT_BUFFER0" );
			retVal.push_back( "OUTPUT_BUFFER1" );
			retVal.push_back( "OUTPUT_BUFFER2" );
			retVal.push_back( "OUTPUT_BUFFER3" );
			retVal.push_back( "OUTPUT_BUFFER4" );
			retVal.push_back( "OUTPUT_BUFFER5" );
			retVal.push_back( "OUTPUT_BUFFER6" );
			retVal.push_back( "OUTPUT_BUFFER7" );
			retVal.push_back( "PREVIOUS0" );
			retVal.push_back( "NONE" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c input0
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FInput0Type;


	/**
	 * @brief Gets the value of field named \c input0.
	 */
	const Input0ValueType getInput0() const;

	/**
	 * @brief Sets the value of field named \c input0.
	 */
	void setInput0( const Input0ValueType value );

	//@}



	/**
	 * @name Accessors to field input1
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		INPUT1_OUTPUT_BUFFER5 = 356,	///< 
		INPUT1_OUTPUT_BUFFER4 = 355,	///< 
		INPUT1_OUTPUT_BUFFER7 = 358,	///< 
		INPUT1_OUTPUT_BUFFER6 = 357,	///< 
		INPUT1_OUTPUT_BUFFER1 = 352,	///< 
		INPUT1_OUTPUT_BUFFER0 = 351,	///< 
		INPUT1_OUTPUT_BUFFER3 = 354,	///< 
		INPUT1_OUTPUT_BUFFER2 = 353,	///< 
		INPUT1_NONE = 360,	///< 
		INPUT1_PREVIOUS0 = 359,	///< 
		DEFAULT_INPUT1 = INPUT1_NONE	///< 
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct Input1ValueType : public vgd::field::Enum
	{
		Input1ValueType()
		{}

		Input1ValueType( const int v )
		: vgd::field::Enum(v)
		{}

		Input1ValueType( const Input1ValueType& o )
		: vgd::field::Enum(o)
		{}

		Input1ValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 351 );
			retVal.push_back( 352 );
			retVal.push_back( 353 );
			retVal.push_back( 354 );
			retVal.push_back( 355 );
			retVal.push_back( 356 );
			retVal.push_back( 357 );
			retVal.push_back( 358 );
			retVal.push_back( 359 );
			retVal.push_back( 360 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "INPUT1_OUTPUT_BUFFER0" );
			retVal.push_back( "INPUT1_OUTPUT_BUFFER1" );
			retVal.push_back( "INPUT1_OUTPUT_BUFFER2" );
			retVal.push_back( "INPUT1_OUTPUT_BUFFER3" );
			retVal.push_back( "INPUT1_OUTPUT_BUFFER4" );
			retVal.push_back( "INPUT1_OUTPUT_BUFFER5" );
			retVal.push_back( "INPUT1_OUTPUT_BUFFER6" );
			retVal.push_back( "INPUT1_OUTPUT_BUFFER7" );
			retVal.push_back( "INPUT1_PREVIOUS0" );
			retVal.push_back( "INPUT1_NONE" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c input1
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FInput1Type;


	/**
	 * @brief Gets the value of field named \c input1.
	 */
	const Input1ValueType getInput1() const;

	/**
	 * @brief Sets the value of field named \c input1.
	 */
	void setInput1( const Input1ValueType value );

	//@}



	/**
	 * @name Accessors to field customFilterDefinition
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c customFilterDefinition.
	 */
	typedef std::string CustomFilterDefinitionValueType;

	/**
	 * @brief Type definition of the field named \c customFilterDefinition
	 */
	typedef vgd::field::TSingleField< CustomFilterDefinitionValueType > FCustomFilterDefinitionType;


	/**
	 * @brief Gets the value of field named \c customFilterDefinition.
	 */
	const CustomFilterDefinitionValueType getCustomFilterDefinition() const;

	/**
	 * @brief Sets the value of field named \c customFilterDefinition.
	 */
	void setCustomFilterDefinition( const CustomFilterDefinitionValueType value );

	//@}



	/**
	 * @name Accessors to field filter
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		SUB = 333,	///< Combines two images into one using the following formula : image1 - image2
		OVER = 331,	///< Composes two images using an over filter. The input0 source is composited over the input1 source. @todo uses alpha instead black to decide composition
		DOF = 338,	///< @todo
		COMBINE2_AND_SCALE = 336,	///< Combines two images into one by blending them linearly using the following formula : image1 * a + image2 * b with a = param4f0[0] and b = param4f0[1].\n Then the resulting image is multiplied by a scale factor : previousComputation *=scale with scale = param4f0[2]
		DOWN_FILTER4 = 329,	///< Scales images down 4 times with a high-pass filter
		COLOR_INVERSE = 322,	///< Inverts the colored value
		MIX_AND_SCALE = 334,	///< Combines two images into one by blending them linearly using the following formula : image1 * (1-a) + image2 * a with a = param4f0[0].\n Then the resulting image is multiplied by a scale factor : previousComputation *=scale with scale = param4f0[1]
		BLOOM_HORIZ = 326,	///< Amplifies and blurs an image horizontally using weights that follow a gaussian distribution. Bloom scale could be specify using param1f0.
		SCALE_AND_BIAS = 323,	///< Each of the color components is multiplied by a scale factor, then added to a bias factor using the following formula : output = input0 * param4f0 + param4f1.
		COMBINE3_AND_SCALE = 337,	///< Combines three images into one by blending them linearly using the following formula : image1 * a + image2 * b + image3 * c with a = param4f0[0], b = param4f0[1] and c = param4f0[2].\n Then the resulting image is multiplied by a scale factor : previousComputation *=scale with scale = param4f0[3]
		BLUR_VERT = 325,	///< Blurs an image vertically using weights that follow a gaussian distribution.
		CUSTOM_FILTER = 340,	///< The filter defined by field customFilterDefinition is applied using field customFilterApply.
		COLOR_TO_MONOCHROME = 320,	///< Converts colored value to black and white
		ADD = 332,	///< Combines two images into one using the following formula : image1 + image2
		BLOOM_VERT = 327,	///< Amplifies and blurs an image vertically using weights that follow a gaussian distribution. Bloom scale could be specify using param1f0.
		ALPHAMIX_AND_SCALE = 335,	///< Combines two images into one by blending them linearly using the following formula : image1 * (1-a) + image2 * a with a = image2.a\n Then the resulting image is multiplied by a scale factor : previousComputation *=scale with scale = param1f0. The alpha channel of the output is image2.a
		COLOR_TO_SEPIA = 321,	///< Converts colored value to sepia.\n Sets desaturate parameter(default 0.5f, min 0.0f, max 1.0f) into param4f0[0]. Sets toning parameter ( default 1.f, min 0.0f, max 1.0f) into param4f0[1].
		IDENTITY = 319,	///< Identity filter, so the resulting image is the input image.
		COLOR_EDGE_DETECT = 328,	///< Detects edges and highlights them
		NO_FILTER = 339,	///< No filter is applied
		BLUR_HORIZ = 324,	///< Blurs an image horizontally using weights that follow a gaussian distribution.
		UP_FILTER4 = 330,	///< Scales images up 4 times
		DEFAULT_FILTER = NO_FILTER	///< No filter is applied
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct FilterValueType : public vgd::field::Enum
	{
		FilterValueType()
		{}

		FilterValueType( const int v )
		: vgd::field::Enum(v)
		{}

		FilterValueType( const FilterValueType& o )
		: vgd::field::Enum(o)
		{}

		FilterValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 319 );
			retVal.push_back( 320 );
			retVal.push_back( 321 );
			retVal.push_back( 322 );
			retVal.push_back( 323 );
			retVal.push_back( 324 );
			retVal.push_back( 325 );
			retVal.push_back( 326 );
			retVal.push_back( 327 );
			retVal.push_back( 328 );
			retVal.push_back( 329 );
			retVal.push_back( 330 );
			retVal.push_back( 331 );
			retVal.push_back( 332 );
			retVal.push_back( 333 );
			retVal.push_back( 334 );
			retVal.push_back( 335 );
			retVal.push_back( 336 );
			retVal.push_back( 337 );
			retVal.push_back( 338 );
			retVal.push_back( 339 );
			retVal.push_back( 340 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "IDENTITY" );
			retVal.push_back( "COLOR_TO_MONOCHROME" );
			retVal.push_back( "COLOR_TO_SEPIA" );
			retVal.push_back( "COLOR_INVERSE" );
			retVal.push_back( "SCALE_AND_BIAS" );
			retVal.push_back( "BLUR_HORIZ" );
			retVal.push_back( "BLUR_VERT" );
			retVal.push_back( "BLOOM_HORIZ" );
			retVal.push_back( "BLOOM_VERT" );
			retVal.push_back( "COLOR_EDGE_DETECT" );
			retVal.push_back( "DOWN_FILTER4" );
			retVal.push_back( "UP_FILTER4" );
			retVal.push_back( "OVER" );
			retVal.push_back( "ADD" );
			retVal.push_back( "SUB" );
			retVal.push_back( "MIX_AND_SCALE" );
			retVal.push_back( "ALPHAMIX_AND_SCALE" );
			retVal.push_back( "COMBINE2_AND_SCALE" );
			retVal.push_back( "COMBINE3_AND_SCALE" );
			retVal.push_back( "DOF" );
			retVal.push_back( "NO_FILTER" );
			retVal.push_back( "CUSTOM_FILTER" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c filter
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FFilterType;


	/**
	 * @brief Gets the value of field named \c filter.
	 */
	const FilterValueType getFilter() const;

	/**
	 * @brief Sets the value of field named \c filter.
	 */
	void setFilter( const FilterValueType value );

	//@}



	/**
	 * @name Accessors to field param4f1
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c param4f1.
	 */
	typedef vgm::Vec4f Param4f1ValueType;

	/**
	 * @brief Type definition of the field named \c param4f1
	 */
	typedef vgd::field::TOptionalField< Param4f1ValueType > FParam4f1Type;


	/**
	 * @brief Gets the value of field named \c param4f1.
	 */
	const bool getParam4f1( Param4f1ValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c param4f1.
 	 */
	void setParam4f1( const Param4f1ValueType& value );

	/**
	 * @brief Erases the field named \c param4f1.
	 */
	void eraseParam4f1();

	/**
	 * @brief Tests if the value of field named \c param4f1 has been initialized.
	 */
	const bool hasParam4f1() const;
	//@}



	/**
	 * @name Accessors to field param4f0
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c param4f0.
	 */
	typedef vgm::Vec4f Param4f0ValueType;

	/**
	 * @brief Type definition of the field named \c param4f0
	 */
	typedef vgd::field::TOptionalField< Param4f0ValueType > FParam4f0Type;


	/**
	 * @brief Gets the value of field named \c param4f0.
	 */
	const bool getParam4f0( Param4f0ValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c param4f0.
 	 */
	void setParam4f0( const Param4f0ValueType& value );

	/**
	 * @brief Erases the field named \c param4f0.
	 */
	void eraseParam4f0();

	/**
	 * @brief Tests if the value of field named \c param4f0 has been initialized.
	 */
	const bool hasParam4f0() const;
	//@}



	/**
	 * @name Accessors to field param4x4f0
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c param4x4f0.
	 */
	typedef vgm::MatrixR Param4x4f0ValueType;

	/**
	 * @brief Type definition of the field named \c param4x4f0
	 */
	typedef vgd::field::TOptionalField< Param4x4f0ValueType > FParam4x4f0Type;


	/**
	 * @brief Gets the value of field named \c param4x4f0.
	 */
	const bool getParam4x4f0( Param4x4f0ValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c param4x4f0.
 	 */
	void setParam4x4f0( const Param4x4f0ValueType& value );

	/**
	 * @brief Erases the field named \c param4x4f0.
	 */
	void eraseParam4x4f0();

	/**
	 * @brief Tests if the value of field named \c param4x4f0 has been initialized.
	 */
	const bool hasParam4x4f0() const;
	//@}



	/**
	 * @name Accessors to field customFilterApply
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c customFilterApply.
	 */
	typedef std::string CustomFilterApplyValueType;

	/**
	 * @brief Type definition of the field named \c customFilterApply
	 */
	typedef vgd::field::TSingleField< CustomFilterApplyValueType > FCustomFilterApplyType;


	/**
	 * @brief Gets the value of field named \c customFilterApply.
	 */
	const CustomFilterApplyValueType getCustomFilterApply() const;

	/**
	 * @brief Sets the value of field named \c customFilterApply.
	 */
	void setCustomFilterApply( const CustomFilterApplyValueType value );

	//@}



	/**
	 * @name Accessors to field output
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		OUTPUT_OUTPUT_BUFFER7 = 379,	///< 
		OUTPUT_OUTPUT_BUFFER6 = 378,	///< 
		OUTPUT_OUTPUT_BUFFER5 = 377,	///< 
		OUTPUT_OUTPUT_BUFFER4 = 376,	///< 
		OUTPUT_OUTPUT_BUFFER3 = 375,	///< 
		OUTPUT_OUTPUT_BUFFER2 = 374,	///< 
		OUTPUT_OUTPUT_BUFFER1 = 373,	///< 
		OUTPUT_OUTPUT_BUFFER0 = 372,	///< 
		OUTPUT_TMP0 = 371,	///< Post-processing internal buffer.
		DEFAULT_OUTPUT = OUTPUT_TMP0	///< Post-processing internal buffer.
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct OutputValueType : public vgd::field::Enum
	{
		OutputValueType()
		{}

		OutputValueType( const int v )
		: vgd::field::Enum(v)
		{}

		OutputValueType( const OutputValueType& o )
		: vgd::field::Enum(o)
		{}

		OutputValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 371 );
			retVal.push_back( 372 );
			retVal.push_back( 373 );
			retVal.push_back( 374 );
			retVal.push_back( 375 );
			retVal.push_back( 376 );
			retVal.push_back( 377 );
			retVal.push_back( 378 );
			retVal.push_back( 379 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "OUTPUT_TMP0" );
			retVal.push_back( "OUTPUT_OUTPUT_BUFFER0" );
			retVal.push_back( "OUTPUT_OUTPUT_BUFFER1" );
			retVal.push_back( "OUTPUT_OUTPUT_BUFFER2" );
			retVal.push_back( "OUTPUT_OUTPUT_BUFFER3" );
			retVal.push_back( "OUTPUT_OUTPUT_BUFFER4" );
			retVal.push_back( "OUTPUT_OUTPUT_BUFFER5" );
			retVal.push_back( "OUTPUT_OUTPUT_BUFFER6" );
			retVal.push_back( "OUTPUT_OUTPUT_BUFFER7" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c output
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FOutputType;


	/**
	 * @brief Gets the value of field named \c output.
	 */
	const OutputValueType getOutput() const;

	/**
	 * @brief Sets the value of field named \c output.
	 */
	void setOutput( const OutputValueType value );

	//@}



	/**
	 * @name Accessors to field param1f0
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c param1f0.
	 */
	typedef float Param1f0ValueType;

	/**
	 * @brief Type definition of the field named \c param1f0
	 */
	typedef vgd::field::TOptionalField< Param1f0ValueType > FParam1f0Type;


	/**
	 * @brief Gets the value of field named \c param1f0.
	 */
	const bool getParam1f0( Param1f0ValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c param1f0.
 	 */
	void setParam1f0( const Param1f0ValueType& value );

	/**
	 * @brief Erases the field named \c param1f0.
	 */
	void eraseParam1f0();

	/**
	 * @brief Tests if the value of field named \c param1f0 has been initialized.
	 */
	const bool hasParam1f0() const;
	//@}



	/**
	 * @name Accessors to field param1f1
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c param1f1.
	 */
	typedef float Param1f1ValueType;

	/**
	 * @brief Type definition of the field named \c param1f1
	 */
	typedef vgd::field::TOptionalField< Param1f1ValueType > FParam1f1Type;


	/**
	 * @brief Gets the value of field named \c param1f1.
	 */
	const bool getParam1f1( Param1f1ValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c param1f1.
 	 */
	void setParam1f1( const Param1f1ValueType& value );

	/**
	 * @brief Erases the field named \c param1f1.
	 */
	void eraseParam1f1();

	/**
	 * @brief Tests if the value of field named \c param1f1 has been initialized.
	 */
	const bool hasParam1f1() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c input2.
	 *
	 * @return the name of field \c input2.
	 */
	static const std::string getFInput2( void );

	/**
	 * @brief Returns the name of field \c input0.
	 *
	 * @return the name of field \c input0.
	 */
	static const std::string getFInput0( void );

	/**
	 * @brief Returns the name of field \c input1.
	 *
	 * @return the name of field \c input1.
	 */
	static const std::string getFInput1( void );

	/**
	 * @brief Returns the name of field \c customFilterDefinition.
	 *
	 * @return the name of field \c customFilterDefinition.
	 */
	static const std::string getFCustomFilterDefinition( void );

	/**
	 * @brief Returns the name of field \c filter.
	 *
	 * @return the name of field \c filter.
	 */
	static const std::string getFFilter( void );

	/**
	 * @brief Returns the name of field \c param4f1.
	 *
	 * @return the name of field \c param4f1.
	 */
	static const std::string getFParam4f1( void );

	/**
	 * @brief Returns the name of field \c param4f0.
	 *
	 * @return the name of field \c param4f0.
	 */
	static const std::string getFParam4f0( void );

	/**
	 * @brief Returns the name of field \c param4x4f0.
	 *
	 * @return the name of field \c param4x4f0.
	 */
	static const std::string getFParam4x4f0( void );

	/**
	 * @brief Returns the name of field \c customFilterApply.
	 *
	 * @return the name of field \c customFilterApply.
	 */
	static const std::string getFCustomFilterApply( void );

	/**
	 * @brief Returns the name of field \c output.
	 *
	 * @return the name of field \c output.
	 */
	static const std::string getFOutput( void );

	/**
	 * @brief Returns the name of field \c param1f0.
	 *
	 * @return the name of field \c param1f0.
	 */
	static const std::string getFParam1f0( void );

	/**
	 * @brief Returns the name of field \c param1f1.
	 *
	 * @return the name of field \c param1f1.
	 */
	static const std::string getFParam1f1( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



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
	PostProcessing( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , PostProcessing );
private:
	static const vgd::basic::RegisterNode<PostProcessing> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_POSTPROCESSING_HPP
