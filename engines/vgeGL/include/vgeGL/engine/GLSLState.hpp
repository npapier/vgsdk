// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_GLSLSTATE_HPP
#define _VGEGL_ENGINE_GLSLSTATE_HPP

#include <bitset>
#include <vgd/Shp.hpp>
#include "vgeGL/vgeGL.hpp"

namespace glo { struct Texture; }
namespace vgd
{ 
	namespace node
	{
		struct Light;
	}
}
namespace vgeGL { namespace engine { struct Engine; } }



namespace vgeGL
{

namespace engine
{



template< uint size >
struct TBitSet
{
	const bool isEnabled( const uint index ) const;
	void setEnabled( const uint index, const bool enabled = true );

	void reset();
protected:
	std::bitset<size>	m_bitset;	///< Container of a fixed number of bits that provide a compact way of keeping flags.
};

template< uint size >
const bool TBitSet<size>::isEnabled( const uint index ) const
{
	assert( index >= 0 && "Out of range index." );
	assert( index < size && "Out of range index." );

	return m_bitset[ index ];
}


template< uint size >
void TBitSet<size>::setEnabled( const uint index, const bool enabled )
{
	assert( index >= 0 && "Out of range index." );
	assert( index < size && "Out of range index." );

	m_bitset[ index ] = enabled;
}


template< uint size >
void TBitSet<size>::reset()
{
	m_bitset.reset();
}



/**
 * @brief GLSL rendering state
 *
 * This class is a specialized container for GLSL rendering state used by program/shader generators 
 * to take care of the rendering state given by the scene graph.
 */
struct GLSLState : public TBitSet< 8 >
{
	enum
	{
		// LightModel node
		LIGHTING = 0,
		PER_PIXEL_LIGHTING,
		LOCAL_VIEWER,
		TWO_SIDED_LIGHTING,			///< Lighting must operate in two-sided mode

		// Light node
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,

		// ClipPlane node
		CLIPPING_PLANE				///< True when at least on ClipPlane node has been traversed
	} BitSetIndexType;

	static const std::string indexString[];


	/**
	 * @brief Default constructor
	 *
	 * @param maxLightUnits		the maximum number of light units
	 * @param maxTexUnits		the maximum number of texture units
	 */
	GLSLState( const uint maxLightUnits = 0, const uint maxTexUnits = 0 );

	/**
	 * @brief Resets to the default state.
	 *
	 * @param maxLightUnits		the maximum number of light units
	 * @param maxTexUnits		the maximum number of texture units
	 */
	void reset( const uint maxLightUnits, const uint maxTexUnits );


	/**
	 * @name Lighting state
	 */
	//@{
	const bool isLightingEnabled() const;
	void setLightingEnabled( const bool enabled = true );

	const bool isTwoSidedLightingEnabled() const;
	void setTwoSidedLightingEnabled( const bool enabled = true );

	const bool isPerPixelLightingEnabled() const;
	const bool isPerVertexLightingEnabled() const;
	void setPerPixelLightingEnabled( const bool enabled = true );
	//@}


	/**
	 * @name Light unit state
	 */
	//@{

	// @todo completes and documents
	struct LightState
	{
		LightState( vgd::node::Light * light, const int type )
		:	m_light(light),
			m_type(type)
		{
			assert( m_light != 0 );
			assert( m_type == DIRECTIONAL_LIGHT || m_type == POINT_LIGHT || m_type == SPOT_LIGHT );
		}

		const vgd::node::Light *getLightNode() const	{ return m_light; }
		vgd::node::Light *getLightNode()				{ return m_light; }

		const int getLightType() const					{ return m_type; }

	private:
		vgd::node::Light *	m_light;
		int					m_type;
	};

	/**
	 * @brief Retrieves light state for the desired light unit.
	 *
	 * @param indexLightUnit		the index of the light unit
	 *
	 * @return The light state for the given light unit or an empty shared pointer.
	 */
	const vgd::Shp< LightState > getLight( const uint indexLightUnit = 0 ) const;

	/**
	 * @brief Retrieves light state for the desired light unit.
	 *
	 * @param indexLightUnit		the index of the light unit
	 *
	 * @return The light state for the given light unit or an empty shared pointer.
	 */
	vgd::Shp< LightState > getLight( const uint indexLightUnit = 0 );

	/**
	 * @brief Sets light state for the given light unit.
	 *
	 * @param indexLightUnit		the index of the light unit
	 * @param lightState			the light state
	 *
	 * @return The previous light state for the given light unit.
	 */
	vgd::Shp< LightState > setLight( const uint indexLightUnit, vgd::Shp< LightState > lightState = vgd::Shp< LightState >() );

	/**
	 * @brief Retrieves the number of light state in all light units.
	 *
	 * @return The number of light state in all light units.
	 */
	const uint getNumLight() const;

	/**
	 * @brief Retrieves the number of light units.
	 *
	 * @return The number of light units.
	 */
	const uint getMaxLight() const;
	//@}



	/**
	 * @name Texture unit state
	 */
	//@{

	/**
	 * @brief Retrieves texture object for the desired texture unit.
	 *
	 * @param indexTexUnit		the index of the texture unit
	 *
	 * @return The texture object for the given texture unit or a null pointer.
	*/
	const glo::Texture *getTexture( const uint indexTexUnit = 0 ) const;

	/**
	 * @brief Retrieves texture object for the desired texture unit.
	 *
	 * @param indexTexUnit		the index of the texture unit
	 *
	 * @return The texture object for the given texture unit or a null pointer.
	*/
	glo::Texture *getTexture( const uint indexTexUnit = 0 );

	/**
	 * @brief Sets texture object for the given texture unit.
	 *
	 * @param indexTexUnit		the index of the texture unit
	 * @param texture			the texture object
	 *
	 * @return The previous texture object for the given texture unit.
	*/
	glo::Texture *setTexture( const uint indexTexUnit, glo::Texture * texture );

	/**
	 * @brief Retrieves the number of texture object in all texture units.
	 *
	 * @return The number of texture object in all texture units.
	 */
	const uint getNumTexture() const;

	/**
	 * @brief Retrieves the number of texture units.
	 *
	 * @return The number of texture units
	 */
	const uint getMaxTexture() const;
	//@}



	void update( vgeGL::engine::Engine * engine );

private:
	std::vector< vgd::Shp< LightState > >	m_light;		///< array of light state. The zero-based index selects the light unit.
	uint									m_numLight;		///< number of light state in all light units.

	std::vector< ::glo::Texture * >	m_texture;		///< array of texture object. The zero-based index selects the texture unit.
	uint							m_numTexture;	///< number of texture object in all texture units.
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_GLSLSTATE_HPP
