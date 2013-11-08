// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_SHADOWMAPPING_HPP
#define _VGEGL_TECHNIQUE_SHADOWMAPPING_HPP

#include <vgd/basic/Image.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Texture2D.hpp>
#include "vgeGL/engine/GLSLState.hpp"

namespace vgd { namespace node { struct FrameBuffer; struct TexGenEyeLinear; struct Texture2D; } }
namespace vgeGL { namespace rc { struct Texture2D; } }


namespace vgeGL
{

namespace technique
{



/**
 * @brief Input informations for shadow mapping
 *
 * @todo Light* and MatrixR are the informations needed to compute all shadow mapping input for a light. BoundingBox of root to adjust projection
 */
struct ShadowMappingInput
{
	struct LightInfo
	{
		typedef vgeGL::engine::LightState LightState;

		LightInfo( const vgd::Shp< LightState > lightState, const vgm::MatrixR projection )
		:	m_lightState(lightState),
			m_lightProjectionMatrix( projection)
		{}

		vgd::Shp< LightState > m_lightState;

		vgm::MatrixR m_lightProjectionMatrix;
	};




	ShadowMappingInput()
	{}

	/**
	 * @brief "Default" constructor
	 *
	 * @param engine		the engine where informations on the current state would be extracted.
	 * @param shadowType	
	 */
	void reset( const vgeGL::engine::Engine * engine, const vgd::node::LightModel::ShadowValueType shadowType );

	/**
	 * @name Accessors
	 */
	//@{
	const LightInfo& getLight( const uint index ) const;

	/**
	 * @brief Returns number of lights casting shadow.
	 */
	const uint getNumLight() const;


	const vgm::MatrixR& getLightProjectionMatrix( const uint index ) const;

	vgd::Shp< vgd::node::Texture2D > getLightDepthMap( const uint index );
	vgd::Shp< vgeGL::rc::Texture2D > getLightDepthMap( const uint index, vgeGL::engine::Engine * engine );

	/*vgd::Shp< vgd::node::Texture2D > getLightAlphaMap( const uint index );
	vgd::Shp< vgeGL::rc::Texture2D > getLightAlphaMap( const uint index, vgeGL::engine::Engine * engine );*/

	vgd::Shp< vgd::node::TexGenEyeLinear > getTexGen( const uint index );

	// @todo != size for shadow map per light casting shadow
	const vgm::Vec2i getShadowMapSize() const;

	//@}


	std::vector< vgd::Shp< vgd::node::FrameBuffer > >		m_fbo;
	std::vector< vgd::Shp< vgd::node::FrameBuffer > >		m_recycleFbo;

	//std::vector< vgd::Shp< vgeGL::rc::FrameBuffer > >		m_fbo;
private:
	//std::vector< vgd::Shp< vgeGL::rc::FrameBuffer > >		m_recycleFbo;
	vgm::Vec2i												m_shadowMapSize;
// @todo only one vector
	std::vector< LightInfo >								m_lights;

	std::vector< vgd::Shp< vgd::node::Texture2D > >			m_recycleLightDepthMap;
	std::vector< vgd::Shp< vgd::node::Texture2D > >			m_lightDepthMap;
	//std::vector< vgd::Shp< vgd::node::Texture2D > >			m_recycleLightAlphaMap;
	//std::vector< vgd::Shp< vgd::node::Texture2D > >			m_lightAlphaMap;
	std::vector< vgd::Shp< vgd::node::TexGenEyeLinear > >	m_recycleTexGen;
	std::vector< vgd::Shp< vgd::node::TexGenEyeLinear > >	m_texGen;
};



std::pair< vgd::basic::IImage::Type, vgd::node::Texture::InternalFormatValueType > convertShadowMapType2IImageType( const vgd::node::LightModel::ShadowMapTypeValueType shadowMapType );



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_SHADOWMAPPING_HPP
