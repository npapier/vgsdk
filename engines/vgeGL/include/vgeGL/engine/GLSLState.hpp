// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_GLSLSTATE_HPP
#define _VGEGL_ENGINE_GLSLSTATE_HPP

#include <bitset>
#include <vector>
#include <vgd/Shp.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgm/Matrix.hpp>
#include "vgeGL/vgeGL.hpp"

namespace glo
{
	struct Texture;
}

namespace vgd
{ 
	namespace node
	{
		struct Light;
		struct SpotLight;
		struct TexGen;
		struct Texture;
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
struct GLSLState : public TBitSet< 11 >
{
	enum BitSetIndexType
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
		SPOT_LIGHT_CASTING_SHADOW,

		// ClipPlane node
		CLIPPING_PLANE,				///< True when at least on ClipPlane node has been traversed

		// DrawStyle node
		FLAT_SHADING,				///< True when DrawStyle.shape implies a flat shading (instead of smooth shading)

		// VertexShape node
		COLOR4_BIND_PER_VERTEX,

		//
		MAX_BITSETINDEXTYPE
	};

	/**
	 * @brief Returns the string representation of the given BitSetIndexType value.
	 *
	 * @pre bitSetIndexType >= 0 and bitSetIndexType < MAX_BITSETINDEXTYPE
	 */
	static const std::string& toString( const BitSetIndexType bitSetIndexType );



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

/*	vgDEPRECATED( const bool isLightingEnabled() const );
	vgDEPRECATED( void setLightingEnabled( const bool enabled = true ) );

	vgDEPRECATED( const bool isTwoSidedLightingEnabled() const );
	vgDEPRECATED( void setTwoSidedLightingEnabled( const bool enabled = true ) );

	vgDEPRECATED( const bool isPerPixelLightingEnabled() const );
	vgDEPRECATED( const bool isPerVertexLightingEnabled() const );
	vgDEPRECATED( void setPerPixelLightingEnabled( const bool enabled = true ) );*/
	//@}


	/**
	 * @name Light unit state
	 */
	//@{

	/**
	 * @brief Light unit state
	 */
	struct LightState
	{
		/**
		 * @brief Constructor
		 */
		LightState( vgd::node::Light * light, const int type )
		:	m_light(light),
			m_type(type)
		{
			assert( m_light != 0 );
			assert( m_type == DIRECTIONAL_LIGHT || m_type == POINT_LIGHT || m_type == SPOT_LIGHT );
		}

		/**
		 * @brief Returns light node
		 */
		const vgd::node::Light *getLightNode() const	{ return m_light; }

		/**
		 * @brief Returns light node
		 */
		vgd::node::Light *getLightNode()				{ return m_light; }


		/**
		 * @brief Returns light node
		 */
		const vgd::node::SpotLight *getSpotLightNode() const;

		/**
		 * @brief Returns the light type
		 */
		const int getLightType() const					{ return m_type; }

		// @todo api
		vgm::MatrixR lightMODELVIEWMatrix;
		vgm::MatrixR lightViewMatrix;
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
	 * @brief Texture unit state structure
	 */
	struct TexUnitState
	{
		TexUnitState(	vgd::node::Texture * textureNode	= 0,
						glo::Texture * texture				= 0,
						const uint8 texCoordDim				= 0,
						vgd::node::TexGen * texGenNode		= 0)
		:	m_textureNode	( textureNode	),
			m_texture		( texture		),
			m_texCoordDim	( texCoordDim	),
			m_texGenNode	( texGenNode	)
		{}

		const vgd::node::Texture * getTextureNode() const		{ return m_textureNode; }
		vgd::node::Texture * getTextureNode()					{ return m_textureNode; }
		void setTextureNode( vgd::node::Texture * textureNode ) { m_textureNode = textureNode; }

		const glo::Texture * getTexture() const		{ return m_texture; }
		glo::Texture * getTexture()					{ return m_texture; }
		void setTexture( glo::Texture * texture )	{ m_texture = texture; }

		const uint8 getTexCoordDim() const		{ return m_texCoordDim; }
		uint8 getTexCoordDim()					{ return m_texCoordDim; }
		void setTexCoordDim( const uint8 texCoordDim ) { m_texCoordDim = texCoordDim; }

		const vgd::node::TexGen * getTexGenNode() const			{ return m_texGenNode; }
		vgd::node::TexGen * getTexGenNode()						{ return m_texGenNode; }
		void setTexGenNode( vgd::node::TexGen * texGenNode )	{ m_texGenNode = texGenNode; }

		/**
		 * @brief Tests completeness of the texture unit
		 *
		 * A texture unit is said to be complete if it contains a texture node and the dimension of texture coordinates is not zero.
		 *
		 * @return true the texture unit is complete, false otherwise
		 */
		const bool isComplete() const
		{
			const bool retVal = getTextureNode() && getTexCoordDim() != 0;
			return retVal;
		}

	private:
		vgd::node::Texture *	m_textureNode;
		glo::Texture *			m_texture;
		uint8					m_texCoordDim;
		vgd::node::TexGen *		m_texGenNode;
	};

	/**
	 * @brief Retrieves state for the desired texture unit.
	 *
	 * @param indexTexUnit		the index of the texture unit
	 *
	 * @return The state for the given texture unit or an empty shared pointer.
	*/
	const vgd::Shp< TexUnitState > getTexture( const uint indexTexUnit = 0 ) const;

	/**
	 * @brief Retrieves state for the desired texture unit.
	 *
	 * @param indexTexUnit		the index of the texture unit
	 *
	 * @return The state for the given texture unit or an empty shared pointer.
	*/
	vgd::Shp< TexUnitState > getTexture( const uint indexTexUnit = 0 );

	/**
	 * @brief Sets state for the given texture unit.
	 *
	 * @param indexTexUnit		the index of the texture unit
	 * @param texture			the texture state
	 *
	 * @return The previous texture state for the given texture unit.
	*/
	vgd::Shp< TexUnitState > setTexture( const uint indexTexUnit, vgd::Shp< TexUnitState > textureState = vgd::Shp< TexUnitState >() );

	/**
	 * @brief Retrieves the number of texture state in all texture units.
	 *
	 * @return The number of texture state in all texture units.
	 */
	const uint getNumTexture() const;

	/**
	 * @brief Retrieves the number of texture units.
	 *
	 * @return The number of texture units
	 */
	const uint getMaxTexture() const;

	//@}


	/**
	 * @brief Returns the last encountered value of LightModel.shadow
	 */
	const vgd::node::LightModel::ShadowValueType getShadowType() const { return m_lightModelShadow; }

	/**
	 * @brief Sets the last encountered value of LightModel.shadow.
	 *
	 * @param shadowType	the value of LightModel.shadow
	 */
	void setShadowType( const vgd::node::LightModel::ShadowValueType shadowType ) { m_lightModelShadow = shadowType; }


private:
	vgd::node::LightModel::ShadowValueType		m_lightModelShadow;	///< Last encountered value of LightModel.shadow field

	std::vector< vgd::Shp< LightState > >		m_light;		///< array of light state. The zero-based index selects the light unit.
	uint										m_numLight;		///< number of light state in all light units.

	std::vector< vgd::Shp< TexUnitState > >		m_texture;		///< array of texture state. The zero-based index selects the texture unit.
	uint										m_numTexture;	///< number of texture state in all light units.

	static const std::string m_indexString[];	///< array containing the string representation for BitSetIndexType.
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_GLSLSTATE_HPP
