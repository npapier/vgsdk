// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_POSTPROCESSING_HPP
#define _VGD_NODE_POSTPROCESSING_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/String.hpp"
#include "vgd/field/Vec4f.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief A single stage of a post-processing stage.
 *
 * This node defines a single stage of a post-processing stage. Post-processing effect is applied to the previously rendered scene using COLOR and/or NORMAL buffer(s) 
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
 * - SFString \c customFilterApply = empty<br>
 *   Specifies the code calling the filter defined by customFilterDefinition.<br>
 *<br>
 * - OFFloat \c [param1f0] = 0.0<br>
 *   Specifies the first 1f parameter used by the filter.<br>
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
		INPUT2_PREVIOUS0 = 347,	///< 
		INPUT2_OUTPUT_BUFFER0 = 339,	///< 
		INPUT2_OUTPUT_BUFFER1 = 340,	///< 
		INPUT2_OUTPUT_BUFFER2 = 341,	///< 
		INPUT2_OUTPUT_BUFFER3 = 342,	///< 
		INPUT2_OUTPUT_BUFFER4 = 343,	///< 
		INPUT2_OUTPUT_BUFFER5 = 344,	///< 
		INPUT2_OUTPUT_BUFFER6 = 345,	///< 
		INPUT2_OUTPUT_BUFFER7 = 346,	///< 
		INPUT2_NONE = 348,	///< 
		DEFAULT_INPUT2 = INPUT2_NONE	///< 
	};

	/**
	 * @brief Type definition of the value contained by field named \c input2.
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

			retVal.push_back( 339 );
			retVal.push_back( 340 );
			retVal.push_back( 341 );
			retVal.push_back( 342 );
			retVal.push_back( 343 );
			retVal.push_back( 344 );
			retVal.push_back( 345 );
			retVal.push_back( 346 );
			retVal.push_back( 347 );
			retVal.push_back( 348 );

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
		NONE = 328,	///< 
		PREVIOUS0 = 327,	///< 
		OUTPUT_BUFFER6 = 325,	///< 
		OUTPUT_BUFFER7 = 326,	///< 
		OUTPUT_BUFFER4 = 323,	///< 
		OUTPUT_BUFFER5 = 324,	///< 
		OUTPUT_BUFFER2 = 321,	///< 
		OUTPUT_BUFFER3 = 322,	///< 
		OUTPUT_BUFFER0 = 319,	///< 
		OUTPUT_BUFFER1 = 320,	///< 
		DEFAULT_INPUT0 = PREVIOUS0	///< 
	};

	/**
	 * @brief Type definition of the value contained by field named \c input0.
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
		INPUT1_OUTPUT_BUFFER5 = 334,	///< 
		INPUT1_OUTPUT_BUFFER4 = 333,	///< 
		INPUT1_OUTPUT_BUFFER7 = 336,	///< 
		INPUT1_OUTPUT_BUFFER6 = 335,	///< 
		INPUT1_OUTPUT_BUFFER1 = 330,	///< 
		INPUT1_OUTPUT_BUFFER0 = 329,	///< 
		INPUT1_OUTPUT_BUFFER3 = 332,	///< 
		INPUT1_OUTPUT_BUFFER2 = 331,	///< 
		INPUT1_NONE = 338,	///< 
		INPUT1_PREVIOUS0 = 337,	///< 
		DEFAULT_INPUT1 = INPUT1_NONE	///< 
	};

	/**
	 * @brief Type definition of the value contained by field named \c input1.
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
		COLOR_INVERSE = 300,	///< Inverts the colored value
		OVER = 309,	///< Composes two images using an over filter. The input0 source is composited over the input1 source. @todo uses alpha instead black to decide composition
		SUB = 311,	///< Combines two images into one using the following formula : image1 - image2
		BLUR_VERT = 303,	///< Blurs an image vertically using weights that follow a Gaussian distribution. Bloom scale could be specify using param1f0
		CUSTOM_FILTER = 318,	///< The filter defined by field customFilterDefinition is applied using field customFilterApply.
		BLOOM_HORIZ = 304,	///< Amplifies and blurs an image horizontally using weights that follow a gaussian distribution
		COLOR_TO_MONOCHROME = 298,	///< Converts colored value to black and white
		DOF = 316,	///< @todo
		MIX_AND_SCALE = 312,	///< Combines two images into one by blending them linearly using the following formula : image1 * (1-a) + image2 * a with a = param4f0[0].\nThen the resulting image is multiplied by a scale factor : previousComputation *=scale with scale = param4f0[1]
		NO_FILTER = 317,	///< No filter is applied
		COMBINE2_AND_SCALE = 314,	///< Combines two images into one by blending them linearly using the following formula : image1 * a + image2 * b with a = param4f0[0] and b = param4f0[1].\nThen the resulting image is multiplied by a scale factor : previousComputation *=scale with scale = param4f0[2]
		ADD = 310,	///< Combines two images into one using the following formula : image1 + image2
		DOWN_FILTER4 = 307,	///< Scales images down 4 times with a high-pass filter
		UP_FILTER4 = 308,	///< Scales images up 4 times
		BLOOM_VERT = 305,	///< Amplifies and blurs an image vertically using weights that follow a gaussian distribution
		ALPHAMIX_AND_SCALE = 313,	///< Combines two images into one by blending them linearly using the following formula : image1 * (1-a) + image2 * a with a = image2.a\nThen the resulting image is multiplied by a scale factor : previousComputation *=scale with scale = param1f0. The alpha channel of the output is image2.a
		SCALE_AND_BIAS = 301,	///< Each of the color components is multiplied by a scale factor, then added to a bias factor using the following formula : output = input0 * param4f0 + param4f1.
		COMBINE3_AND_SCALE = 315,	///< Combines three images into one by blending them linearly using the following formula : image1 * a + image2 * b + image3 * c with a = param4f0[0], b = param4f0[1] and c = param4f0[2].\nThen the resulting image is multiplied by a scale factor : previousComputation *=scale with scale = param4f0[3]
		COLOR_TO_SEPIA = 299,	///< Converts colored value to sepia.\nSets desaturate parameter(default 0.5f, min 0.0f, max 1.0f) into param4f0[0]. Sets toning parameter ( default 1.f, min 0.0f, max 1.0f) into param4f0[1].
		BLUR_HORIZ = 302,	///< Blurs an image horizontally using weights that follow a Gaussian distribution. Bloom scale could be specify using param1f0.
		COLOR_EDGE_DETECT = 306,	///< Detects edges and highlights them
		DEFAULT_FILTER = NO_FILTER	///< No filter is applied
	};

	/**
	 * @brief Type definition of the value contained by field named \c filter.
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

			retVal.push_back( 298 );
			retVal.push_back( 299 );
			retVal.push_back( 300 );
			retVal.push_back( 301 );
			retVal.push_back( 302 );
			retVal.push_back( 303 );
			retVal.push_back( 304 );
			retVal.push_back( 305 );
			retVal.push_back( 306 );
			retVal.push_back( 307 );
			retVal.push_back( 308 );
			retVal.push_back( 309 );
			retVal.push_back( 310 );
			retVal.push_back( 311 );
			retVal.push_back( 312 );
			retVal.push_back( 313 );
			retVal.push_back( 314 );
			retVal.push_back( 315 );
			retVal.push_back( 316 );
			retVal.push_back( 317 );
			retVal.push_back( 318 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

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
	 * @brief Returns the name of field \c customFilterApply.
	 *
	 * @return the name of field \c customFilterApply.
	 */
	static const std::string getFCustomFilterApply( void );

	/**
	 * @brief Returns the name of field \c param1f0.
	 *
	 * @return the name of field \c param1f0.
	 */
	static const std::string getFParam1f0( void );

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
