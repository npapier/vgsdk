// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_GLSLSTATE_HPP
#define _VGEGL_ENGINE_GLSLSTATE_HPP

#include <bitset>
#include "vgeGL/vgeGL.hpp"

namespace glo { struct Texture; }
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
struct GLSLState : public TBitSet< 3 >
{
	enum
	{
		LIGHTING = 0,
		TWO_SIDED_LIGHTING,			///< Lighting must operate in two-sided mode
		PER_PIXEL_LIGHTING
	} BitSetIndexType;

	static const std::string indexString[];


	/**
	 * @brief Default constructor
	 *
	 * @param maxTexUnits		the maximum number of texture units
	 */
	GLSLState( const uint maxTexUnits );

	/**
	 * @brief Resets to the default state.
	 */
	void reset( const uint maxTexUnits );


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
	glo::Texture *setTexture( const uint uindexTexUnit, glo::Texture * texture );

	/**
	 * @brief Retrieves the number of texture object in all texture units.
	 *
	 * @return the number of texture object in all texture units.
	 */
	const uint getNumTexture() const;

	/**
	 * @brief Retrieves the number of texture units.
	 *
	 * @return the number of texture units
	 */
	const uint getMaxTexture() const;
	//@}



	void update( vgeGL::engine::Engine * engine );

private:
	std::vector< ::glo::Texture * >	m_texture;		///< array of texture objects. The zero-based index selects the texture unit.
	uint							m_numTexture;	///< number of texture object in all texture units.
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_GLSLSTATE_HPP
