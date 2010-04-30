// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_POSTPROCESSING_HPP
#define _VGD_NODE_POSTPROCESSING_HPP

#include "vgd/field/Enum.hpp"
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
 * - SFEnum \c filter = NO_FILTER<br>
 *   Specifies the filter to apply to the input buffers.<br>
 *<br>
 * - SFEnum \c input0 = PREVIOUS_COLOR<br>
 *   Specifies the first input buffer used by the filter.<br>
 *<br>
 * - SFEnum \c input1 = INPUT1_NONE<br>
 *   Specifies the second input buffer used by the filter.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_texturingNodes
 * @ingroup g_frameBufferNodes
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
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< PostProcessing > createWhole( const std::string nodeName = "DefaultWhole" );

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
		COLOR_INVERSE = 286,	///< Inverts the colored value
		BLUR_VERT = 288,	///< Blurs an image vertically using weights that follow a Gaussian distribution
		BLOOM_HORIZ = 289,	///< Amplifies and blurs an image horizontally using weights that follow a gaussian distribution
		COLOR_TO_MONOCHROME = 285,	///< Converts colored value to black and white
		NO_FILTER = 295,	///< No filter is applied
		DOWN_FILTER4 = 292,	///< Scales images down 4 times with a high-pass filter
		COMBINE = 294,	///< Combines two images (ADD)
		UP_FILTER4 = 293,	///< Scales images up 4 times
		BLOOM_VERT = 290,	///< Amplifies and blurs an image vertically using weights that follow a gaussian distribution
		COLOR_EDGE_DETECT = 291,	///< Detects edges and highlights them
		BLUR_HORIZ = 287,	///< Blurs an image horizontally using weights that follow a Gaussian distribution
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

			retVal.push_back( 285 );
			retVal.push_back( 286 );
			retVal.push_back( 287 );
			retVal.push_back( 288 );
			retVal.push_back( 289 );
			retVal.push_back( 290 );
			retVal.push_back( 291 );
			retVal.push_back( 292 );
			retVal.push_back( 293 );
			retVal.push_back( 294 );
			retVal.push_back( 295 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "COLOR_TO_MONOCHROME" );
			retVal.push_back( "COLOR_INVERSE" );
			retVal.push_back( "BLUR_HORIZ" );
			retVal.push_back( "BLUR_VERT" );
			retVal.push_back( "BLOOM_HORIZ" );
			retVal.push_back( "BLOOM_VERT" );
			retVal.push_back( "COLOR_EDGE_DETECT" );
			retVal.push_back( "DOWN_FILTER4" );
			retVal.push_back( "UP_FILTER4" );
			retVal.push_back( "COMBINE" );
			retVal.push_back( "NO_FILTER" );

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
	 * @name Accessors to field input0
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		NONE = 299,	///< 
		ORIGINAL_COLOR = 296,	///< 
		PREVIOUS_COLOR = 298,	///< 
		ORIGINAL_NORMAL = 297,	///< 
		DEFAULT_INPUT0 = PREVIOUS_COLOR	///< 
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

			retVal.push_back( 296 );
			retVal.push_back( 297 );
			retVal.push_back( 298 );
			retVal.push_back( 299 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "ORIGINAL_COLOR" );
			retVal.push_back( "ORIGINAL_NORMAL" );
			retVal.push_back( "PREVIOUS_COLOR" );
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
		INPUT1_ORIGINAL_COLOR = 300,	///< 
		INPUT1_NONE = 301,	///< 
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

			retVal.push_back( 300 );
			retVal.push_back( 301 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "INPUT1_ORIGINAL_COLOR" );
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
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c filter.
	 *
	 * @return the name of field \c filter.
	 */
	static const std::string getFFilter( void );

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
