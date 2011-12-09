// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_NOISE_HPP
#define _VGD_NODE_NOISE_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/Vec2f.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Built-in post-processing effect adding noise
 *
 * Most digital cameras acquired images with noise. This built-in post-processing effect simulates dominant source of noise, i.e. the photon noise. 
 *
 * New fields defined by this node :
 * - SFVec2f \c factors = vgm::Vec2f(0.025, 0.025)<br>
 *   Sets the linear and constant factor used to generate noise.<br>
 *<br>
 * - SFEnum \c noiseModel = PHOTON<br>
 *   Sets the noise model.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_frameBufferNodes
 */
struct VGD_API Noise : public vgd::node::SingleAttribute
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
	static vgd::Shp< Noise > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Noise > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Noise > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field factors
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c factors.
	 */
	typedef vgm::Vec2f FactorsValueType;

	/**
	 * @brief Type definition of the field named \c factors
	 */
	typedef vgd::field::TSingleField< FactorsValueType > FFactorsType;


	/**
	 * @brief Gets the value of field named \c factors.
	 */
	const FactorsValueType getFactors() const;

	/**
	 * @brief Sets the value of field named \c factors.
	 */
	void setFactors( const FactorsValueType value );

	//@}



	/**
	 * @name Accessors to field noiseModel
	 */
	//@{

	/**
	 * @brief Definition of symbolic values
	 */
	enum  
	{
		PHOTON = 304,	///< Photon noise simulation
		NO = 303,	///< No noise simulation
		DEFAULT_NOISEMODEL = PHOTON	///< Photon noise simulation
	};

	/**
	 * @brief Type definition of a container for the previous symbolic values
	 */
	struct NoiseModelValueType : public vgd::field::Enum
	{
		NoiseModelValueType()
		{}

		NoiseModelValueType( const int v )
		: vgd::field::Enum(v)
		{}

		NoiseModelValueType( const NoiseModelValueType& o )
		: vgd::field::Enum(o)
		{}

		NoiseModelValueType( const vgd::field::Enum& o )
		: vgd::field::Enum(o)
		{}

		const std::vector< int > values() const
		{
			std::vector< int > retVal;

			retVal.push_back( 303 );
			retVal.push_back( 304 );

			return retVal;
		}

		const std::vector< std::string > strings() const
		{
			std::vector< std::string > retVal;

			retVal.push_back( "NO" );
			retVal.push_back( "PHOTON" );

			return retVal;
		}
	};

	/**
	 * @brief Type definition of the field named \c noiseModel
	 */
	typedef vgd::field::TSingleField< vgd::field::Enum > FNoiseModelType;


	/**
	 * @brief Gets the value of field named \c noiseModel.
	 */
	const NoiseModelValueType getNoiseModel() const;

	/**
	 * @brief Sets the value of field named \c noiseModel.
	 */
	void setNoiseModel( const NoiseModelValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c factors.
	 *
	 * @return the name of field \c factors.
	 */
	static const std::string getFFactors( void );

	/**
	 * @brief Returns the name of field \c noiseModel.
	 *
	 * @return the name of field \c noiseModel.
	 */
	static const std::string getFNoiseModel( void );

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
	Noise( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Noise );
private:
	static const vgd::basic::RegisterNode<Noise> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_NOISE_HPP
