// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/EnumRegistry.hpp"

#include <vgDebug/helpers.hpp>
#include <vgd/Shp.hpp>
#include <vgd/field/Enum.hpp>
#include <vgd/node/Antialiasing.hpp>
#include <vgd/node/Camera.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/DepthOfField.hpp>
#include <vgd/node/Displacement.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/FrontFace.hpp>
#include <vgd/node/GeoMorph.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Noise.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/TessellationLevel.hpp>
#include <vgd/node/TessellationProperties.hpp>
#include <vgd/node/Texture.hpp>
#include <vgd/node/Uniforms.hpp>
#include <vgd/node/VertexShape.hpp>



namespace vgd
{

namespace node
{



const std::string EnumRegistry::toString( const int enumValue )
{
	if ( m_toString.empty() )
	{
		// Initializes the registry (only once).
		initialize();
	}

	ToStringType::const_iterator iter = m_toString.find( enumValue );

	if ( iter != m_toString.end() )
	{
		return iter->second;
	}
	else
	{
		return std::string("");
	}
}



const vgd::Shp< vgd::field::Enum > EnumRegistry::toEnum( const int enumValue )
{
	if ( m_toEnum.empty() )
	{
		// Initializes the registry (only once).
		initialize();
	}

	ToEnumType::const_iterator iter = m_toEnum.find( enumValue );

	if ( iter != m_toEnum.end() )
	{
		return iter->second;
	}
	else
	{
		return vgd::makeShp( new vgd::field::Enum() );
	}
}



EnumRegistry::ToStringType EnumRegistry::m_toString;



EnumRegistry::ToEnumType EnumRegistry::m_toEnum;



void EnumRegistry::initialize()
{
	// Initializes m_toString map

	//
	#ifdef _DEBUG
	if ( m_toString.find( 290 ) != m_toString.end() )
	{
		vgLogDebug("(290, NORMALIZED) already in m_toString enum registry");
		assert( false && "(290, NORMALIZED) already in registry" );
	}
	#endif

	m_toString[ 290 ] = std::string("NORMALIZED");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 300 ) != m_toString.end() )
	{
		vgLogDebug("(300, CHOICE3) already in m_toString enum registry");
		assert( false && "(300, CHOICE3) already in registry" );
	}
	#endif

	m_toString[ 300 ] = std::string("CHOICE3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 299 ) != m_toString.end() )
	{
		vgLogDebug("(299, CHOICE2) already in m_toString enum registry");
		assert( false && "(299, CHOICE2) already in registry" );
	}
	#endif

	m_toString[ 299 ] = std::string("CHOICE2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 298 ) != m_toString.end() )
	{
		vgLogDebug("(298, CHOICE1) already in m_toString enum registry");
		assert( false && "(298, CHOICE1) already in registry" );
	}
	#endif

	m_toString[ 298 ] = std::string("CHOICE1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 297 ) != m_toString.end() )
	{
		vgLogDebug("(297, CHOICE0) already in m_toString enum registry");
		assert( false && "(297, CHOICE0) already in registry" );
	}
	#endif

	m_toString[ 297 ] = std::string("CHOICE0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 367 ) != m_toString.end() )
	{
		vgLogDebug("(367, ADD) already in m_toString enum registry");
		assert( false && "(367, ADD) already in registry" );
	}
	#endif

	m_toString[ 367 ] = std::string("ADD");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 346 ) != m_toString.end() )
	{
		vgLogDebug("(346, COLOR) already in m_toString enum registry");
		assert( false && "(346, COLOR) already in registry" );
	}
	#endif

	m_toString[ 346 ] = std::string("COLOR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 444 ) != m_toString.end() )
	{
		vgLogDebug("(444, LINEAR_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(444, LINEAR_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 444 ] = std::string("LINEAR_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 261 ) != m_toString.end() )
	{
		vgLogDebug("(261, EYE_RIGHT) already in m_toString enum registry");
		assert( false && "(261, EYE_RIGHT) already in registry" );
	}
	#endif

	m_toString[ 261 ] = std::string("EYE_RIGHT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 274 ) != m_toString.end() )
	{
		vgLogDebug("(274, CUSTOM) already in m_toString enum registry");
		assert( false && "(274, CUSTOM) already in registry" );
	}
	#endif

	m_toString[ 274 ] = std::string("CUSTOM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 286 ) != m_toString.end() )
	{
		vgLogDebug("(286, AA_OBJECT_SPACE) already in m_toString enum registry");
		assert( false && "(286, AA_OBJECT_SPACE) already in registry" );
	}
	#endif

	m_toString[ 286 ] = std::string("AA_OBJECT_SPACE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 328 ) != m_toString.end() )
	{
		vgLogDebug("(328, LOW) already in m_toString enum registry");
		assert( false && "(328, LOW) already in registry" );
	}
	#endif

	m_toString[ 328 ] = std::string("LOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 360 ) != m_toString.end() )
	{
		vgLogDebug("(360, BLOOM_VERT) already in m_toString enum registry");
		assert( false && "(360, BLOOM_VERT) already in registry" );
	}
	#endif

	m_toString[ 360 ] = std::string("BLOOM_VERT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 258 ) != m_toString.end() )
	{
		vgLogDebug("(258, NONE) already in m_toString enum registry");
		assert( false && "(258, NONE) already in registry" );
	}
	#endif

	m_toString[ 258 ] = std::string("NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 329 ) != m_toString.end() )
	{
		vgLogDebug("(329, MEDIUM) already in m_toString enum registry");
		assert( false && "(329, MEDIUM) already in registry" );
	}
	#endif

	m_toString[ 329 ] = std::string("MEDIUM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 292 ) != m_toString.end() )
	{
		vgLogDebug("(292, CW) already in m_toString enum registry");
		assert( false && "(292, CW) already in registry" );
	}
	#endif

	m_toString[ 292 ] = std::string("CW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 312 ) != m_toString.end() )
	{
		vgLogDebug("(312, SHADOW_MAPPING_9U) already in m_toString enum registry");
		assert( false && "(312, SHADOW_MAPPING_9U) already in registry" );
	}
	#endif

	m_toString[ 312 ] = std::string("SHADOW_MAPPING_9U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 342 ) != m_toString.end() )
	{
		vgLogDebug("(342, LUMINANCE_FOR_DEPTH) already in m_toString enum registry");
		assert( false && "(342, LUMINANCE_FOR_DEPTH) already in registry" );
	}
	#endif

	m_toString[ 342 ] = std::string("LUMINANCE_FOR_DEPTH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 283 ) != m_toString.end() )
	{
		vgLogDebug("(283, NEIGHBOUR) already in m_toString enum registry");
		assert( false && "(283, NEIGHBOUR) already in registry" );
	}
	#endif

	m_toString[ 283 ] = std::string("NEIGHBOUR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 441 ) != m_toString.end() )
	{
		vgLogDebug("(441, NEAREST_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(441, NEAREST_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 441 ] = std::string("NEAREST_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 351 ) != m_toString.end() )
	{
		vgLogDebug("(351, CUSTOM) already in m_toString enum registry");
		assert( false && "(351, CUSTOM) already in registry" );
	}
	#endif

	m_toString[ 351 ] = std::string("CUSTOM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 308 ) != m_toString.end() )
	{
		vgLogDebug("(308, SHADOW_MAPPING) already in m_toString enum registry");
		assert( false && "(308, SHADOW_MAPPING) already in registry" );
	}
	#endif

	m_toString[ 308 ] = std::string("SHADOW_MAPPING");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 437 ) != m_toString.end() )
	{
		vgLogDebug("(437, MIN_FILTER) already in m_toString enum registry");
		assert( false && "(437, MIN_FILTER) already in registry" );
	}
	#endif

	m_toString[ 437 ] = std::string("MIN_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 386 ) != m_toString.end() )
	{
		vgLogDebug("(386, INPUT0SAMPLING_NONE) already in m_toString enum registry");
		assert( false && "(386, INPUT0SAMPLING_NONE) already in registry" );
	}
	#endif

	m_toString[ 386 ] = std::string("INPUT0SAMPLING_NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 450 ) != m_toString.end() )
	{
		vgLogDebug("(450, DEPTH_COMPONENT_32) already in m_toString enum registry");
		assert( false && "(450, DEPTH_COMPONENT_32) already in registry" );
	}
	#endif

	m_toString[ 450 ] = std::string("DEPTH_COMPONENT_32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 291 ) != m_toString.end() )
	{
		vgLogDebug("(291, CCW) already in m_toString enum registry");
		assert( false && "(291, CCW) already in registry" );
	}
	#endif

	m_toString[ 291 ] = std::string("CCW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 423 ) != m_toString.end() )
	{
		vgLogDebug("(423, UNIFORM) already in m_toString enum registry");
		assert( false && "(423, UNIFORM) already in registry" );
	}
	#endif

	m_toString[ 423 ] = std::string("UNIFORM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 456 ) != m_toString.end() )
	{
		vgLogDebug("(456, LUMINANCE_16F) already in m_toString enum registry");
		assert( false && "(456, LUMINANCE_16F) already in registry" );
	}
	#endif

	m_toString[ 456 ] = std::string("LUMINANCE_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 411 ) != m_toString.end() )
	{
		vgLogDebug("(411, INPUT2_TEXTURE0) already in m_toString enum registry");
		assert( false && "(411, INPUT2_TEXTURE0) already in registry" );
	}
	#endif

	m_toString[ 411 ] = std::string("INPUT2_TEXTURE0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 368 ) != m_toString.end() )
	{
		vgLogDebug("(368, SUB) already in m_toString enum registry");
		assert( false && "(368, SUB) already in registry" );
	}
	#endif

	m_toString[ 368 ] = std::string("SUB");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 371 ) != m_toString.end() )
	{
		vgLogDebug("(371, COMBINE2_AND_SCALE) already in m_toString enum registry");
		assert( false && "(371, COMBINE2_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 371 ] = std::string("COMBINE2_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 358 ) != m_toString.end() )
	{
		vgLogDebug("(358, BLUR_VERT) already in m_toString enum registry");
		assert( false && "(358, BLUR_VERT) already in registry" );
	}
	#endif

	m_toString[ 358 ] = std::string("BLUR_VERT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 395 ) != m_toString.end() )
	{
		vgLogDebug("(395, INPUT1_OUTPUT_BUFFER3) already in m_toString enum registry");
		assert( false && "(395, INPUT1_OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toString[ 395 ] = std::string("INPUT1_OUTPUT_BUFFER3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 270 ) != m_toString.end() )
	{
		vgLogDebug("(270, PINHOLE) already in m_toString enum registry");
		assert( false && "(270, PINHOLE) already in registry" );
	}
	#endif

	m_toString[ 270 ] = std::string("PINHOLE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 445 ) != m_toString.end() )
	{
		vgLogDebug("(445, IMAGE) already in m_toString enum registry");
		assert( false && "(445, IMAGE) already in registry" );
	}
	#endif

	m_toString[ 445 ] = std::string("IMAGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 434 ) != m_toString.end() )
	{
		vgLogDebug("(434, CLAMP_TO_BORDER) already in m_toString enum registry");
		assert( false && "(434, CLAMP_TO_BORDER) already in registry" );
	}
	#endif

	m_toString[ 434 ] = std::string("CLAMP_TO_BORDER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 435 ) != m_toString.end() )
	{
		vgLogDebug("(435, MIRRORED_REPEAT) already in m_toString enum registry");
		assert( false && "(435, MIRRORED_REPEAT) already in registry" );
	}
	#endif

	m_toString[ 435 ] = std::string("MIRRORED_REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 332 ) != m_toString.end() )
	{
		vgLogDebug("(332, NEAREST) already in m_toString enum registry");
		assert( false && "(332, NEAREST) already in registry" );
	}
	#endif

	m_toString[ 332 ] = std::string("NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 343 ) != m_toString.end() )
	{
		vgLogDebug("(343, INTEGER) already in m_toString enum registry");
		assert( false && "(343, INTEGER) already in registry" );
	}
	#endif

	m_toString[ 343 ] = std::string("INTEGER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 372 ) != m_toString.end() )
	{
		vgLogDebug("(372, COMBINE3_AND_SCALE) already in m_toString enum registry");
		assert( false && "(372, COMBINE3_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 372 ] = std::string("COMBINE3_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 257 ) != m_toString.end() )
	{
		vgLogDebug("(257, BIND_PER_VERTEX) already in m_toString enum registry");
		assert( false && "(257, BIND_PER_VERTEX) already in registry" );
	}
	#endif

	m_toString[ 257 ] = std::string("BIND_PER_VERTEX");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 305 ) != m_toString.end() )
	{
		vgLogDebug("(305, AT_INFINITY) already in m_toString enum registry");
		assert( false && "(305, AT_INFINITY) already in registry" );
	}
	#endif

	m_toString[ 305 ] = std::string("AT_INFINITY");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 416 ) != m_toString.end() )
	{
		vgLogDebug("(416, OUTPUT_OUTPUT_BUFFER1) already in m_toString enum registry");
		assert( false && "(416, OUTPUT_OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toString[ 416 ] = std::string("OUTPUT_OUTPUT_BUFFER1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 415 ) != m_toString.end() )
	{
		vgLogDebug("(415, OUTPUT_OUTPUT_BUFFER0) already in m_toString enum registry");
		assert( false && "(415, OUTPUT_OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toString[ 415 ] = std::string("OUTPUT_OUTPUT_BUFFER0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 449 ) != m_toString.end() )
	{
		vgLogDebug("(449, DEPTH_COMPONENT_24) already in m_toString enum registry");
		assert( false && "(449, DEPTH_COMPONENT_24) already in registry" );
	}
	#endif

	m_toString[ 449 ] = std::string("DEPTH_COMPONENT_24");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 337 ) != m_toString.end() )
	{
		vgLogDebug("(337, PIXEL_SIZE) already in m_toString enum registry");
		assert( false && "(337, PIXEL_SIZE) already in registry" );
	}
	#endif

	m_toString[ 337 ] = std::string("PIXEL_SIZE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 446 ) != m_toString.end() )
	{
		vgLogDebug("(446, SHADOW) already in m_toString enum registry");
		assert( false && "(446, SHADOW) already in registry" );
	}
	#endif

	m_toString[ 446 ] = std::string("SHADOW");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 365 ) != m_toString.end() )
	{
		vgLogDebug("(365, UP_FILTER4_LINEAR) already in m_toString enum registry");
		assert( false && "(365, UP_FILTER4_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 365 ] = std::string("UP_FILTER4_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 452 ) != m_toString.end() )
	{
		vgLogDebug("(452, RGB_16F) already in m_toString enum registry");
		assert( false && "(452, RGB_16F) already in registry" );
	}
	#endif

	m_toString[ 452 ] = std::string("RGB_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 341 ) != m_toString.end() )
	{
		vgLogDebug("(341, LUMINANCE_ALPHA) already in m_toString enum registry");
		assert( false && "(341, LUMINANCE_ALPHA) already in registry" );
	}
	#endif

	m_toString[ 341 ] = std::string("LUMINANCE_ALPHA");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 347 ) != m_toString.end() )
	{
		vgLogDebug("(347, NORMAL) already in m_toString enum registry");
		assert( false && "(347, NORMAL) already in registry" );
	}
	#endif

	m_toString[ 347 ] = std::string("NORMAL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 391 ) != m_toString.end() )
	{
		vgLogDebug("(391, LINEAR_MAXANISOTROPY16) already in m_toString enum registry");
		assert( false && "(391, LINEAR_MAXANISOTROPY16) already in registry" );
	}
	#endif

	m_toString[ 391 ] = std::string("LINEAR_MAXANISOTROPY16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 281 ) != m_toString.end() )
	{
		vgLogDebug("(281, FLAT_HIDDEN_LINE) already in m_toString enum registry");
		assert( false && "(281, FLAT_HIDDEN_LINE) already in registry" );
	}
	#endif

	m_toString[ 281 ] = std::string("FLAT_HIDDEN_LINE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 349 ) != m_toString.end() )
	{
		vgLogDebug("(349, DEPTH) already in m_toString enum registry");
		assert( false && "(349, DEPTH) already in registry" );
	}
	#endif

	m_toString[ 349 ] = std::string("DEPTH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 350 ) != m_toString.end() )
	{
		vgLogDebug("(350, LINEAR_DEPTH) already in m_toString enum registry");
		assert( false && "(350, LINEAR_DEPTH) already in registry" );
	}
	#endif

	m_toString[ 350 ] = std::string("LINEAR_DEPTH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 414 ) != m_toString.end() )
	{
		vgLogDebug("(414, OUTPUT_TMP0) already in m_toString enum registry");
		assert( false && "(414, OUTPUT_TMP0) already in registry" );
	}
	#endif

	m_toString[ 414 ] = std::string("OUTPUT_TMP0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 454 ) != m_toString.end() )
	{
		vgLogDebug("(454, RGBA_16F) already in m_toString enum registry");
		assert( false && "(454, RGBA_16F) already in registry" );
	}
	#endif

	m_toString[ 454 ] = std::string("RGBA_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 384 ) != m_toString.end() )
	{
		vgLogDebug("(384, PREVIOUS0) already in m_toString enum registry");
		assert( false && "(384, PREVIOUS0) already in registry" );
	}
	#endif

	m_toString[ 384 ] = std::string("PREVIOUS0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 271 ) != m_toString.end() )
	{
		vgLogDebug("(271, THIN_LENS) already in m_toString enum registry");
		assert( false && "(271, THIN_LENS) already in registry" );
	}
	#endif

	m_toString[ 271 ] = std::string("THIN_LENS");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 276 ) != m_toString.end() )
	{
		vgLogDebug("(276, POINT) already in m_toString enum registry");
		assert( false && "(276, POINT) already in registry" );
	}
	#endif

	m_toString[ 276 ] = std::string("POINT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 369 ) != m_toString.end() )
	{
		vgLogDebug("(369, MIX_AND_SCALE) already in m_toString enum registry");
		assert( false && "(369, MIX_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 369 ] = std::string("MIX_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 439 ) != m_toString.end() )
	{
		vgLogDebug("(439, NEAREST) already in m_toString enum registry");
		assert( false && "(439, NEAREST) already in registry" );
	}
	#endif

	m_toString[ 439 ] = std::string("NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 330 ) != m_toString.end() )
	{
		vgLogDebug("(330, HIGH) already in m_toString enum registry");
		assert( false && "(330, HIGH) already in registry" );
	}
	#endif

	m_toString[ 330 ] = std::string("HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 301 ) != m_toString.end() )
	{
		vgLogDebug("(301, CHOICE4) already in m_toString enum registry");
		assert( false && "(301, CHOICE4) already in registry" );
	}
	#endif

	m_toString[ 301 ] = std::string("CHOICE4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 448 ) != m_toString.end() )
	{
		vgLogDebug("(448, DEPTH_COMPONENT_16) already in m_toString enum registry");
		assert( false && "(448, DEPTH_COMPONENT_16) already in registry" );
	}
	#endif

	m_toString[ 448 ] = std::string("DEPTH_COMPONENT_16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 317 ) != m_toString.end() )
	{
		vgLogDebug("(317, SHADOW_MAPPING_25UM) already in m_toString enum registry");
		assert( false && "(317, SHADOW_MAPPING_25UM) already in registry" );
	}
	#endif

	m_toString[ 317 ] = std::string("SHADOW_MAPPING_25UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 458 ) != m_toString.end() )
	{
		vgLogDebug("(458, LUMINANCE_ALPHA_16F) already in m_toString enum registry");
		assert( false && "(458, LUMINANCE_ALPHA_16F) already in registry" );
	}
	#endif

	m_toString[ 458 ] = std::string("LUMINANCE_ALPHA_16F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 338 ) != m_toString.end() )
	{
		vgLogDebug("(338, RGB) already in m_toString enum registry");
		assert( false && "(338, RGB) already in registry" );
	}
	#endif

	m_toString[ 338 ] = std::string("RGB");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 433 ) != m_toString.end() )
	{
		vgLogDebug("(433, CLAMP_TO_EDGE) already in m_toString enum registry");
		assert( false && "(433, CLAMP_TO_EDGE) already in registry" );
	}
	#endif

	m_toString[ 433 ] = std::string("CLAMP_TO_EDGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 370 ) != m_toString.end() )
	{
		vgLogDebug("(370, ALPHAMIX_AND_SCALE) already in m_toString enum registry");
		assert( false && "(370, ALPHAMIX_AND_SCALE) already in registry" );
	}
	#endif

	m_toString[ 370 ] = std::string("ALPHAMIX_AND_SCALE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 427 ) != m_toString.end() )
	{
		vgLogDebug("(427, PHONG) already in m_toString enum registry");
		assert( false && "(427, PHONG) already in registry" );
	}
	#endif

	m_toString[ 427 ] = std::string("PHONG");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 340 ) != m_toString.end() )
	{
		vgLogDebug("(340, LUMINANCE) already in m_toString enum registry");
		assert( false && "(340, LUMINANCE) already in registry" );
	}
	#endif

	m_toString[ 340 ] = std::string("LUMINANCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 377 ) != m_toString.end() )
	{
		vgLogDebug("(377, OUTPUT_BUFFER2) already in m_toString enum registry");
		assert( false && "(377, OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toString[ 377 ] = std::string("OUTPUT_BUFFER2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 376 ) != m_toString.end() )
	{
		vgLogDebug("(376, OUTPUT_BUFFER1) already in m_toString enum registry");
		assert( false && "(376, OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toString[ 376 ] = std::string("OUTPUT_BUFFER1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 375 ) != m_toString.end() )
	{
		vgLogDebug("(375, OUTPUT_BUFFER0) already in m_toString enum registry");
		assert( false && "(375, OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toString[ 375 ] = std::string("OUTPUT_BUFFER0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 382 ) != m_toString.end() )
	{
		vgLogDebug("(382, OUTPUT_BUFFER7) already in m_toString enum registry");
		assert( false && "(382, OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toString[ 382 ] = std::string("OUTPUT_BUFFER7");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 381 ) != m_toString.end() )
	{
		vgLogDebug("(381, OUTPUT_BUFFER6) already in m_toString enum registry");
		assert( false && "(381, OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toString[ 381 ] = std::string("OUTPUT_BUFFER6");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 380 ) != m_toString.end() )
	{
		vgLogDebug("(380, OUTPUT_BUFFER5) already in m_toString enum registry");
		assert( false && "(380, OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toString[ 380 ] = std::string("OUTPUT_BUFFER5");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 379 ) != m_toString.end() )
	{
		vgLogDebug("(379, OUTPUT_BUFFER4) already in m_toString enum registry");
		assert( false && "(379, OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toString[ 379 ] = std::string("OUTPUT_BUFFER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 344 ) != m_toString.end() )
	{
		vgLogDebug("(344, FLOAT16) already in m_toString enum registry");
		assert( false && "(344, FLOAT16) already in registry" );
	}
	#endif

	m_toString[ 344 ] = std::string("FLOAT16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 302 ) != m_toString.end() )
	{
		vgLogDebug("(302, LIGHTING_OFF) already in m_toString enum registry");
		assert( false && "(302, LIGHTING_OFF) already in registry" );
	}
	#endif

	m_toString[ 302 ] = std::string("LIGHTING_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 461 ) != m_toString.end() )
	{
		vgLogDebug("(461, APPEND) already in m_toString enum registry");
		assert( false && "(461, APPEND) already in registry" );
	}
	#endif

	m_toString[ 461 ] = std::string("APPEND");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 447 ) != m_toString.end() )
	{
		vgLogDebug("(447, AUTOMATIC) already in m_toString enum registry");
		assert( false && "(447, AUTOMATIC) already in registry" );
	}
	#endif

	m_toString[ 447 ] = std::string("AUTOMATIC");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 378 ) != m_toString.end() )
	{
		vgLogDebug("(378, OUTPUT_BUFFER3) already in m_toString enum registry");
		assert( false && "(378, OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toString[ 378 ] = std::string("OUTPUT_BUFFER3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 294 ) != m_toString.end() )
	{
		vgLogDebug("(294, INT24) already in m_toString enum registry");
		assert( false && "(294, INT24) already in registry" );
	}
	#endif

	m_toString[ 294 ] = std::string("INT24");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 466 ) != m_toString.end() )
	{
		vgLogDebug("(466, STREAM) already in m_toString enum registry");
		assert( false && "(466, STREAM) already in registry" );
	}
	#endif

	m_toString[ 466 ] = std::string("STREAM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 256 ) != m_toString.end() )
	{
		vgLogDebug("(256, BIND_OFF) already in m_toString enum registry");
		assert( false && "(256, BIND_OFF) already in registry" );
	}
	#endif

	m_toString[ 256 ] = std::string("BIND_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 400 ) != m_toString.end() )
	{
		vgLogDebug("(400, INPUT1_TEXTURE0) already in m_toString enum registry");
		assert( false && "(400, INPUT1_TEXTURE0) already in registry" );
	}
	#endif

	m_toString[ 400 ] = std::string("INPUT1_TEXTURE0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 273 ) != m_toString.end() )
	{
		vgLogDebug("(273, ALONG_NORMAL) already in m_toString enum registry");
		assert( false && "(273, ALONG_NORMAL) already in registry" );
	}
	#endif

	m_toString[ 273 ] = std::string("ALONG_NORMAL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 277 ) != m_toString.end() )
	{
		vgLogDebug("(277, FLAT) already in m_toString enum registry");
		assert( false && "(277, FLAT) already in registry" );
	}
	#endif

	m_toString[ 277 ] = std::string("FLAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 265 ) != m_toString.end() )
	{
		vgLogDebug("(265, ANAGLYPH) already in m_toString enum registry");
		assert( false && "(265, ANAGLYPH) already in registry" );
	}
	#endif

	m_toString[ 265 ] = std::string("ANAGLYPH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 260 ) != m_toString.end() )
	{
		vgLogDebug("(260, EYE_LEFT) already in m_toString enum registry");
		assert( false && "(260, EYE_LEFT) already in registry" );
	}
	#endif

	m_toString[ 260 ] = std::string("EYE_LEFT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 432 ) != m_toString.end() )
	{
		vgLogDebug("(432, CLAMP) already in m_toString enum registry");
		assert( false && "(432, CLAMP) already in registry" );
	}
	#endif

	m_toString[ 432 ] = std::string("CLAMP");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 465 ) != m_toString.end() )
	{
		vgLogDebug("(465, DYNAMIC) already in m_toString enum registry");
		assert( false && "(465, DYNAMIC) already in registry" );
	}
	#endif

	m_toString[ 465 ] = std::string("DYNAMIC");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 263 ) != m_toString.end() )
	{
		vgLogDebug("(263, MONOSCOPIC) already in m_toString enum registry");
		assert( false && "(263, MONOSCOPIC) already in registry" );
	}
	#endif

	m_toString[ 263 ] = std::string("MONOSCOPIC");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 355 ) != m_toString.end() )
	{
		vgLogDebug("(355, COLOR_INVERSE) already in m_toString enum registry");
		assert( false && "(355, COLOR_INVERSE) already in registry" );
	}
	#endif

	m_toString[ 355 ] = std::string("COLOR_INVERSE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 387 ) != m_toString.end() )
	{
		vgLogDebug("(387, NEAREST_MAXANISOTROPY1) already in m_toString enum registry");
		assert( false && "(387, NEAREST_MAXANISOTROPY1) already in registry" );
	}
	#endif

	m_toString[ 387 ] = std::string("NEAREST_MAXANISOTROPY1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 402 ) != m_toString.end() )
	{
		vgLogDebug("(402, INPUT1_NONE) already in m_toString enum registry");
		assert( false && "(402, INPUT1_NONE) already in registry" );
	}
	#endif

	m_toString[ 402 ] = std::string("INPUT1_NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 296 ) != m_toString.end() )
	{
		vgLogDebug("(296, FLOAT32) already in m_toString enum registry");
		assert( false && "(296, FLOAT32) already in registry" );
	}
	#endif

	m_toString[ 296 ] = std::string("FLOAT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 412 ) != m_toString.end() )
	{
		vgLogDebug("(412, INPUT2_PREVIOUS0) already in m_toString enum registry");
		assert( false && "(412, INPUT2_PREVIOUS0) already in registry" );
	}
	#endif

	m_toString[ 412 ] = std::string("INPUT2_PREVIOUS0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 262 ) != m_toString.end() )
	{
		vgLogDebug("(262, EYE_BOTH) already in m_toString enum registry");
		assert( false && "(262, EYE_BOTH) already in registry" );
	}
	#endif

	m_toString[ 262 ] = std::string("EYE_BOTH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 320 ) != m_toString.end() )
	{
		vgLogDebug("(320, SHADOW_MAPPING_64U) already in m_toString enum registry");
		assert( false && "(320, SHADOW_MAPPING_64U) already in registry" );
	}
	#endif

	m_toString[ 320 ] = std::string("SHADOW_MAPPING_64U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 353 ) != m_toString.end() )
	{
		vgLogDebug("(353, COLOR_TO_MONOCHROME) already in m_toString enum registry");
		assert( false && "(353, COLOR_TO_MONOCHROME) already in registry" );
	}
	#endif

	m_toString[ 353 ] = std::string("COLOR_TO_MONOCHROME");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 311 ) != m_toString.end() )
	{
		vgLogDebug("(311, SHADOW_MAPPING_4DM) already in m_toString enum registry");
		assert( false && "(311, SHADOW_MAPPING_4DM) already in registry" );
	}
	#endif

	m_toString[ 311 ] = std::string("SHADOW_MAPPING_4DM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 394 ) != m_toString.end() )
	{
		vgLogDebug("(394, INPUT1_OUTPUT_BUFFER2) already in m_toString enum registry");
		assert( false && "(394, INPUT1_OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toString[ 394 ] = std::string("INPUT1_OUTPUT_BUFFER2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 393 ) != m_toString.end() )
	{
		vgLogDebug("(393, INPUT1_OUTPUT_BUFFER1) already in m_toString enum registry");
		assert( false && "(393, INPUT1_OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toString[ 393 ] = std::string("INPUT1_OUTPUT_BUFFER1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 392 ) != m_toString.end() )
	{
		vgLogDebug("(392, INPUT1_OUTPUT_BUFFER0) already in m_toString enum registry");
		assert( false && "(392, INPUT1_OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toString[ 392 ] = std::string("INPUT1_OUTPUT_BUFFER0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 399 ) != m_toString.end() )
	{
		vgLogDebug("(399, INPUT1_OUTPUT_BUFFER7) already in m_toString enum registry");
		assert( false && "(399, INPUT1_OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toString[ 399 ] = std::string("INPUT1_OUTPUT_BUFFER7");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 398 ) != m_toString.end() )
	{
		vgLogDebug("(398, INPUT1_OUTPUT_BUFFER6) already in m_toString enum registry");
		assert( false && "(398, INPUT1_OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toString[ 398 ] = std::string("INPUT1_OUTPUT_BUFFER6");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 397 ) != m_toString.end() )
	{
		vgLogDebug("(397, INPUT1_OUTPUT_BUFFER5) already in m_toString enum registry");
		assert( false && "(397, INPUT1_OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toString[ 397 ] = std::string("INPUT1_OUTPUT_BUFFER5");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 396 ) != m_toString.end() )
	{
		vgLogDebug("(396, INPUT1_OUTPUT_BUFFER4) already in m_toString enum registry");
		assert( false && "(396, INPUT1_OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toString[ 396 ] = std::string("INPUT1_OUTPUT_BUFFER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 287 ) != m_toString.end() )
	{
		vgLogDebug("(287, OBJECT_AND_AA_OBJECT_SPACE) already in m_toString enum registry");
		assert( false && "(287, OBJECT_AND_AA_OBJECT_SPACE) already in registry" );
	}
	#endif

	m_toString[ 287 ] = std::string("OBJECT_AND_AA_OBJECT_SPACE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 352 ) != m_toString.end() )
	{
		vgLogDebug("(352, IDENTITY) already in m_toString enum registry");
		assert( false && "(352, IDENTITY) already in registry" );
	}
	#endif

	m_toString[ 352 ] = std::string("IDENTITY");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 278 ) != m_toString.end() )
	{
		vgLogDebug("(278, SMOOTH) already in m_toString enum registry");
		assert( false && "(278, SMOOTH) already in registry" );
	}
	#endif

	m_toString[ 278 ] = std::string("SMOOTH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 307 ) != m_toString.end() )
	{
		vgLogDebug("(307, SHADOW_OFF) already in m_toString enum registry");
		assert( false && "(307, SHADOW_OFF) already in registry" );
	}
	#endif

	m_toString[ 307 ] = std::string("SHADOW_OFF");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 425 ) != m_toString.end() )
	{
		vgLogDebug("(425, CUSTOM) already in m_toString enum registry");
		assert( false && "(425, CUSTOM) already in registry" );
	}
	#endif

	m_toString[ 425 ] = std::string("CUSTOM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 464 ) != m_toString.end() )
	{
		vgLogDebug("(464, STATIC) already in m_toString enum registry");
		assert( false && "(464, STATIC) already in registry" );
	}
	#endif

	m_toString[ 464 ] = std::string("STATIC");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 295 ) != m_toString.end() )
	{
		vgLogDebug("(295, INT32) already in m_toString enum registry");
		assert( false && "(295, INT32) already in registry" );
	}
	#endif

	m_toString[ 295 ] = std::string("INT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 361 ) != m_toString.end() )
	{
		vgLogDebug("(361, COLOR_EDGE_DETECT) already in m_toString enum registry");
		assert( false && "(361, COLOR_EDGE_DETECT) already in registry" );
	}
	#endif

	m_toString[ 361 ] = std::string("COLOR_EDGE_DETECT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 443 ) != m_toString.end() )
	{
		vgLogDebug("(443, NEAREST_MIPMAP_LINEAR) already in m_toString enum registry");
		assert( false && "(443, NEAREST_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toString[ 443 ] = std::string("NEAREST_MIPMAP_LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 356 ) != m_toString.end() )
	{
		vgLogDebug("(356, SCALE_AND_BIAS) already in m_toString enum registry");
		assert( false && "(356, SCALE_AND_BIAS) already in registry" );
	}
	#endif

	m_toString[ 356 ] = std::string("SCALE_AND_BIAS");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 455 ) != m_toString.end() )
	{
		vgLogDebug("(455, RGBA_32F) already in m_toString enum registry");
		assert( false && "(455, RGBA_32F) already in registry" );
	}
	#endif

	m_toString[ 455 ] = std::string("RGBA_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 268 ) != m_toString.end() )
	{
		vgLogDebug("(268, FRONT) already in m_toString enum registry");
		assert( false && "(268, FRONT) already in registry" );
	}
	#endif

	m_toString[ 268 ] = std::string("FRONT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 419 ) != m_toString.end() )
	{
		vgLogDebug("(419, OUTPUT_OUTPUT_BUFFER4) already in m_toString enum registry");
		assert( false && "(419, OUTPUT_OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toString[ 419 ] = std::string("OUTPUT_OUTPUT_BUFFER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 335 ) != m_toString.end() )
	{
		vgLogDebug("(335, PHOTON) already in m_toString enum registry");
		assert( false && "(335, PHOTON) already in registry" );
	}
	#endif

	m_toString[ 335 ] = std::string("PHOTON");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 428 ) != m_toString.end() )
	{
		vgLogDebug("(428, WRAP_S) already in m_toString enum registry");
		assert( false && "(428, WRAP_S) already in registry" );
	}
	#endif

	m_toString[ 428 ] = std::string("WRAP_S");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 442 ) != m_toString.end() )
	{
		vgLogDebug("(442, LINEAR_MIPMAP_NEAREST) already in m_toString enum registry");
		assert( false && "(442, LINEAR_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toString[ 442 ] = std::string("LINEAR_MIPMAP_NEAREST");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 429 ) != m_toString.end() )
	{
		vgLogDebug("(429, WRAP_T) already in m_toString enum registry");
		assert( false && "(429, WRAP_T) already in registry" );
	}
	#endif

	m_toString[ 429 ] = std::string("WRAP_T");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 264 ) != m_toString.end() )
	{
		vgLogDebug("(264, QUAD_BUFFER) already in m_toString enum registry");
		assert( false && "(264, QUAD_BUFFER) already in registry" );
	}
	#endif

	m_toString[ 264 ] = std::string("QUAD_BUFFER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 366 ) != m_toString.end() )
	{
		vgLogDebug("(366, OVER) already in m_toString enum registry");
		assert( false && "(366, OVER) already in registry" );
	}
	#endif

	m_toString[ 366 ] = std::string("OVER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 288 ) != m_toString.end() )
	{
		vgLogDebug("(288, DISABLED) already in m_toString enum registry");
		assert( false && "(288, DISABLED) already in registry" );
	}
	#endif

	m_toString[ 288 ] = std::string("DISABLED");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 362 ) != m_toString.end() )
	{
		vgLogDebug("(362, MEDIAN3x3) already in m_toString enum registry");
		assert( false && "(362, MEDIAN3x3) already in registry" );
	}
	#endif

	m_toString[ 362 ] = std::string("MEDIAN3x3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 345 ) != m_toString.end() )
	{
		vgLogDebug("(345, FLOAT32) already in m_toString enum registry");
		assert( false && "(345, FLOAT32) already in registry" );
	}
	#endif

	m_toString[ 345 ] = std::string("FLOAT32");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 279 ) != m_toString.end() )
	{
		vgLogDebug("(279, WIREFRAME) already in m_toString enum registry");
		assert( false && "(279, WIREFRAME) already in registry" );
	}
	#endif

	m_toString[ 279 ] = std::string("WIREFRAME");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 436 ) != m_toString.end() )
	{
		vgLogDebug("(436, ONCE) already in m_toString enum registry");
		assert( false && "(436, ONCE) already in registry" );
	}
	#endif

	m_toString[ 436 ] = std::string("ONCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 280 ) != m_toString.end() )
	{
		vgLogDebug("(280, HIDDEN_LINE) already in m_toString enum registry");
		assert( false && "(280, HIDDEN_LINE) already in registry" );
	}
	#endif

	m_toString[ 280 ] = std::string("HIDDEN_LINE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 430 ) != m_toString.end() )
	{
		vgLogDebug("(430, WRAP_R) already in m_toString enum registry");
		assert( false && "(430, WRAP_R) already in registry" );
	}
	#endif

	m_toString[ 430 ] = std::string("WRAP_R");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 385 ) != m_toString.end() )
	{
		vgLogDebug("(385, NONE) already in m_toString enum registry");
		assert( false && "(385, NONE) already in registry" );
	}
	#endif

	m_toString[ 385 ] = std::string("NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 323 ) != m_toString.end() )
	{
		vgLogDebug("(323, SHADOW_MAPPING_144UM) already in m_toString enum registry");
		assert( false && "(323, SHADOW_MAPPING_144UM) already in registry" );
	}
	#endif

	m_toString[ 323 ] = std::string("SHADOW_MAPPING_144UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 339 ) != m_toString.end() )
	{
		vgLogDebug("(339, RGBA) already in m_toString enum registry");
		assert( false && "(339, RGBA) already in registry" );
	}
	#endif

	m_toString[ 339 ] = std::string("RGBA");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 316 ) != m_toString.end() )
	{
		vgLogDebug("(316, SHADOW_MAPPING_25U) already in m_toString enum registry");
		assert( false && "(316, SHADOW_MAPPING_25U) already in registry" );
	}
	#endif

	m_toString[ 316 ] = std::string("SHADOW_MAPPING_25U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 319 ) != m_toString.end() )
	{
		vgLogDebug("(319, SHADOW_MAPPING_36UM) already in m_toString enum registry");
		assert( false && "(319, SHADOW_MAPPING_36UM) already in registry" );
	}
	#endif

	m_toString[ 319 ] = std::string("SHADOW_MAPPING_36UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 321 ) != m_toString.end() )
	{
		vgLogDebug("(321, SHADOW_MAPPING_64UM) already in m_toString enum registry");
		assert( false && "(321, SHADOW_MAPPING_64UM) already in registry" );
	}
	#endif

	m_toString[ 321 ] = std::string("SHADOW_MAPPING_64UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 359 ) != m_toString.end() )
	{
		vgLogDebug("(359, BLOOM_HORIZ) already in m_toString enum registry");
		assert( false && "(359, BLOOM_HORIZ) already in registry" );
	}
	#endif

	m_toString[ 359 ] = std::string("BLOOM_HORIZ");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 333 ) != m_toString.end() )
	{
		vgLogDebug("(333, LINEAR) already in m_toString enum registry");
		assert( false && "(333, LINEAR) already in registry" );
	}
	#endif

	m_toString[ 333 ] = std::string("LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 418 ) != m_toString.end() )
	{
		vgLogDebug("(418, OUTPUT_OUTPUT_BUFFER3) already in m_toString enum registry");
		assert( false && "(418, OUTPUT_OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toString[ 418 ] = std::string("OUTPUT_OUTPUT_BUFFER3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 417 ) != m_toString.end() )
	{
		vgLogDebug("(417, OUTPUT_OUTPUT_BUFFER2) already in m_toString enum registry");
		assert( false && "(417, OUTPUT_OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toString[ 417 ] = std::string("OUTPUT_OUTPUT_BUFFER2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 383 ) != m_toString.end() )
	{
		vgLogDebug("(383, TEXTURE0) already in m_toString enum registry");
		assert( false && "(383, TEXTURE0) already in registry" );
	}
	#endif

	m_toString[ 383 ] = std::string("TEXTURE0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 289 ) != m_toString.end() )
	{
		vgLogDebug("(289, SKIP) already in m_toString enum registry");
		assert( false && "(289, SKIP) already in registry" );
	}
	#endif

	m_toString[ 289 ] = std::string("SKIP");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 422 ) != m_toString.end() )
	{
		vgLogDebug("(422, OUTPUT_OUTPUT_BUFFER7) already in m_toString enum registry");
		assert( false && "(422, OUTPUT_OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toString[ 422 ] = std::string("OUTPUT_OUTPUT_BUFFER7");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 421 ) != m_toString.end() )
	{
		vgLogDebug("(421, OUTPUT_OUTPUT_BUFFER6) already in m_toString enum registry");
		assert( false && "(421, OUTPUT_OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toString[ 421 ] = std::string("OUTPUT_OUTPUT_BUFFER6");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 420 ) != m_toString.end() )
	{
		vgLogDebug("(420, OUTPUT_OUTPUT_BUFFER5) already in m_toString enum registry");
		assert( false && "(420, OUTPUT_OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toString[ 420 ] = std::string("OUTPUT_OUTPUT_BUFFER5");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 310 ) != m_toString.end() )
	{
		vgLogDebug("(310, SHADOW_MAPPING_4UM) already in m_toString enum registry");
		assert( false && "(310, SHADOW_MAPPING_4UM) already in registry" );
	}
	#endif

	m_toString[ 310 ] = std::string("SHADOW_MAPPING_4UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 322 ) != m_toString.end() )
	{
		vgLogDebug("(322, SHADOW_MAPPING_144U) already in m_toString enum registry");
		assert( false && "(322, SHADOW_MAPPING_144U) already in registry" );
	}
	#endif

	m_toString[ 322 ] = std::string("SHADOW_MAPPING_144U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 404 ) != m_toString.end() )
	{
		vgLogDebug("(404, INPUT2_OUTPUT_BUFFER1) already in m_toString enum registry");
		assert( false && "(404, INPUT2_OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toString[ 404 ] = std::string("INPUT2_OUTPUT_BUFFER1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 403 ) != m_toString.end() )
	{
		vgLogDebug("(403, INPUT2_OUTPUT_BUFFER0) already in m_toString enum registry");
		assert( false && "(403, INPUT2_OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toString[ 403 ] = std::string("INPUT2_OUTPUT_BUFFER0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 440 ) != m_toString.end() )
	{
		vgLogDebug("(440, LINEAR) already in m_toString enum registry");
		assert( false && "(440, LINEAR) already in registry" );
	}
	#endif

	m_toString[ 440 ] = std::string("LINEAR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 457 ) != m_toString.end() )
	{
		vgLogDebug("(457, LUMINANCE_32F) already in m_toString enum registry");
		assert( false && "(457, LUMINANCE_32F) already in registry" );
	}
	#endif

	m_toString[ 457 ] = std::string("LUMINANCE_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 285 ) != m_toString.end() )
	{
		vgLogDebug("(285, OBJECT_SPACE) already in m_toString enum registry");
		assert( false && "(285, OBJECT_SPACE) already in registry" );
	}
	#endif

	m_toString[ 285 ] = std::string("OBJECT_SPACE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 424 ) != m_toString.end() )
	{
		vgLogDebug("(424, PIXELS_PER_EDGE) already in m_toString enum registry");
		assert( false && "(424, PIXELS_PER_EDGE) already in registry" );
	}
	#endif

	m_toString[ 424 ] = std::string("PIXELS_PER_EDGE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 405 ) != m_toString.end() )
	{
		vgLogDebug("(405, INPUT2_OUTPUT_BUFFER2) already in m_toString enum registry");
		assert( false && "(405, INPUT2_OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toString[ 405 ] = std::string("INPUT2_OUTPUT_BUFFER2");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 334 ) != m_toString.end() )
	{
		vgLogDebug("(334, NO) already in m_toString enum registry");
		assert( false && "(334, NO) already in registry" );
	}
	#endif

	m_toString[ 334 ] = std::string("NO");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 275 ) != m_toString.end() )
	{
		vgLogDebug("(275, NO_SHAPE) already in m_toString enum registry");
		assert( false && "(275, NO_SHAPE) already in registry" );
	}
	#endif

	m_toString[ 275 ] = std::string("NO_SHAPE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 426 ) != m_toString.end() )
	{
		vgLogDebug("(426, DISABLED) already in m_toString enum registry");
		assert( false && "(426, DISABLED) already in registry" );
	}
	#endif

	m_toString[ 426 ] = std::string("DISABLED");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 357 ) != m_toString.end() )
	{
		vgLogDebug("(357, BLUR_HORIZ) already in m_toString enum registry");
		assert( false && "(357, BLUR_HORIZ) already in registry" );
	}
	#endif

	m_toString[ 357 ] = std::string("BLUR_HORIZ");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 438 ) != m_toString.end() )
	{
		vgLogDebug("(438, MAG_FILTER) already in m_toString enum registry");
		assert( false && "(438, MAG_FILTER) already in registry" );
	}
	#endif

	m_toString[ 438 ] = std::string("MAG_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 284 ) != m_toString.end() )
	{
		vgLogDebug("(284, NO_BOUNDING_BOX) already in m_toString enum registry");
		assert( false && "(284, NO_BOUNDING_BOX) already in registry" );
	}
	#endif

	m_toString[ 284 ] = std::string("NO_BOUNDING_BOX");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 354 ) != m_toString.end() )
	{
		vgLogDebug("(354, COLOR_TO_SEPIA) already in m_toString enum registry");
		assert( false && "(354, COLOR_TO_SEPIA) already in registry" );
	}
	#endif

	m_toString[ 354 ] = std::string("COLOR_TO_SEPIA");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 309 ) != m_toString.end() )
	{
		vgLogDebug("(309, SHADOW_MAPPING_4U) already in m_toString enum registry");
		assert( false && "(309, SHADOW_MAPPING_4U) already in registry" );
	}
	#endif

	m_toString[ 309 ] = std::string("SHADOW_MAPPING_4U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 460 ) != m_toString.end() )
	{
		vgLogDebug("(460, REPLACE) already in m_toString enum registry");
		assert( false && "(460, REPLACE) already in registry" );
	}
	#endif

	m_toString[ 460 ] = std::string("REPLACE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 266 ) != m_toString.end() )
	{
		vgLogDebug("(266, DISABLED) already in m_toString enum registry");
		assert( false && "(266, DISABLED) already in registry" );
	}
	#endif

	m_toString[ 266 ] = std::string("DISABLED");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 259 ) != m_toString.end() )
	{
		vgLogDebug("(259, FXAA1) already in m_toString enum registry");
		assert( false && "(259, FXAA1) already in registry" );
	}
	#endif

	m_toString[ 259 ] = std::string("FXAA1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 431 ) != m_toString.end() )
	{
		vgLogDebug("(431, REPEAT) already in m_toString enum registry");
		assert( false && "(431, REPEAT) already in registry" );
	}
	#endif

	m_toString[ 431 ] = std::string("REPEAT");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 293 ) != m_toString.end() )
	{
		vgLogDebug("(293, INT16) already in m_toString enum registry");
		assert( false && "(293, INT16) already in registry" );
	}
	#endif

	m_toString[ 293 ] = std::string("INT16");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 326 ) != m_toString.end() )
	{
		vgLogDebug("(326, SHADOW_MAPPING_256U) already in m_toString enum registry");
		assert( false && "(326, SHADOW_MAPPING_256U) already in registry" );
	}
	#endif

	m_toString[ 326 ] = std::string("SHADOW_MAPPING_256U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 388 ) != m_toString.end() )
	{
		vgLogDebug("(388, LINEAR_MAXANISOTROPY1) already in m_toString enum registry");
		assert( false && "(388, LINEAR_MAXANISOTROPY1) already in registry" );
	}
	#endif

	m_toString[ 388 ] = std::string("LINEAR_MAXANISOTROPY1");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 459 ) != m_toString.end() )
	{
		vgLogDebug("(459, LUMINANCE_ALPHA_32F) already in m_toString enum registry");
		assert( false && "(459, LUMINANCE_ALPHA_32F) already in registry" );
	}
	#endif

	m_toString[ 459 ] = std::string("LUMINANCE_ALPHA_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 267 ) != m_toString.end() )
	{
		vgLogDebug("(267, BACK) already in m_toString enum registry");
		assert( false && "(267, BACK) already in registry" );
	}
	#endif

	m_toString[ 267 ] = std::string("BACK");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 389 ) != m_toString.end() )
	{
		vgLogDebug("(389, LINEAR_MAXANISOTROPY4) already in m_toString enum registry");
		assert( false && "(389, LINEAR_MAXANISOTROPY4) already in registry" );
	}
	#endif

	m_toString[ 389 ] = std::string("LINEAR_MAXANISOTROPY4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 313 ) != m_toString.end() )
	{
		vgLogDebug("(313, SHADOW_MAPPING_9UM) already in m_toString enum registry");
		assert( false && "(313, SHADOW_MAPPING_9UM) already in registry" );
	}
	#endif

	m_toString[ 313 ] = std::string("SHADOW_MAPPING_9UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 390 ) != m_toString.end() )
	{
		vgLogDebug("(390, LINEAR_MAXANISOTROPY8) already in m_toString enum registry");
		assert( false && "(390, LINEAR_MAXANISOTROPY8) already in registry" );
	}
	#endif

	m_toString[ 390 ] = std::string("LINEAR_MAXANISOTROPY8");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 314 ) != m_toString.end() )
	{
		vgLogDebug("(314, SHADOW_MAPPING_16U) already in m_toString enum registry");
		assert( false && "(314, SHADOW_MAPPING_16U) already in registry" );
	}
	#endif

	m_toString[ 314 ] = std::string("SHADOW_MAPPING_16U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 306 ) != m_toString.end() )
	{
		vgLogDebug("(306, AT_EYE) already in m_toString enum registry");
		assert( false && "(306, AT_EYE) already in registry" );
	}
	#endif

	m_toString[ 306 ] = std::string("AT_EYE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 364 ) != m_toString.end() )
	{
		vgLogDebug("(364, UP_FILTER4) already in m_toString enum registry");
		assert( false && "(364, UP_FILTER4) already in registry" );
	}
	#endif

	m_toString[ 364 ] = std::string("UP_FILTER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 451 ) != m_toString.end() )
	{
		vgLogDebug("(451, DEPTH_COMPONENT_32F) already in m_toString enum registry");
		assert( false && "(451, DEPTH_COMPONENT_32F) already in registry" );
	}
	#endif

	m_toString[ 451 ] = std::string("DEPTH_COMPONENT_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 331 ) != m_toString.end() )
	{
		vgLogDebug("(331, VERY_HIGH) already in m_toString enum registry");
		assert( false && "(331, VERY_HIGH) already in registry" );
	}
	#endif

	m_toString[ 331 ] = std::string("VERY_HIGH");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 363 ) != m_toString.end() )
	{
		vgLogDebug("(363, DOWN_FILTER4) already in m_toString enum registry");
		assert( false && "(363, DOWN_FILTER4) already in registry" );
	}
	#endif

	m_toString[ 363 ] = std::string("DOWN_FILTER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 374 ) != m_toString.end() )
	{
		vgLogDebug("(374, CUSTOM_FILTER) already in m_toString enum registry");
		assert( false && "(374, CUSTOM_FILTER) already in registry" );
	}
	#endif

	m_toString[ 374 ] = std::string("CUSTOM_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 348 ) != m_toString.end() )
	{
		vgLogDebug("(348, POSITION) already in m_toString enum registry");
		assert( false && "(348, POSITION) already in registry" );
	}
	#endif

	m_toString[ 348 ] = std::string("POSITION");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 453 ) != m_toString.end() )
	{
		vgLogDebug("(453, RGB_32F) already in m_toString enum registry");
		assert( false && "(453, RGB_32F) already in registry" );
	}
	#endif

	m_toString[ 453 ] = std::string("RGB_32F");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 318 ) != m_toString.end() )
	{
		vgLogDebug("(318, SHADOW_MAPPING_36U) already in m_toString enum registry");
		assert( false && "(318, SHADOW_MAPPING_36U) already in registry" );
	}
	#endif

	m_toString[ 318 ] = std::string("SHADOW_MAPPING_36U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 463 ) != m_toString.end() )
	{
		vgLogDebug("(463, ONCE) already in m_toString enum registry");
		assert( false && "(463, ONCE) already in registry" );
	}
	#endif

	m_toString[ 463 ] = std::string("ONCE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 282 ) != m_toString.end() )
	{
		vgLogDebug("(282, SMOOTH_HIDDEN_LINE) already in m_toString enum registry");
		assert( false && "(282, SMOOTH_HIDDEN_LINE) already in registry" );
	}
	#endif

	m_toString[ 282 ] = std::string("SMOOTH_HIDDEN_LINE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 324 ) != m_toString.end() )
	{
		vgLogDebug("(324, SHADOW_MAPPING_225U) already in m_toString enum registry");
		assert( false && "(324, SHADOW_MAPPING_225U) already in registry" );
	}
	#endif

	m_toString[ 324 ] = std::string("SHADOW_MAPPING_225U");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 315 ) != m_toString.end() )
	{
		vgLogDebug("(315, SHADOW_MAPPING_16UM) already in m_toString enum registry");
		assert( false && "(315, SHADOW_MAPPING_16UM) already in registry" );
	}
	#endif

	m_toString[ 315 ] = std::string("SHADOW_MAPPING_16UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 269 ) != m_toString.end() )
	{
		vgLogDebug("(269, FRONT_AND_BACK) already in m_toString enum registry");
		assert( false && "(269, FRONT_AND_BACK) already in registry" );
	}
	#endif

	m_toString[ 269 ] = std::string("FRONT_AND_BACK");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 325 ) != m_toString.end() )
	{
		vgLogDebug("(325, SHADOW_MAPPING_225UM) already in m_toString enum registry");
		assert( false && "(325, SHADOW_MAPPING_225UM) already in registry" );
	}
	#endif

	m_toString[ 325 ] = std::string("SHADOW_MAPPING_225UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 304 ) != m_toString.end() )
	{
		vgLogDebug("(304, STANDARD_PER_PIXEL) already in m_toString enum registry");
		assert( false && "(304, STANDARD_PER_PIXEL) already in registry" );
	}
	#endif

	m_toString[ 304 ] = std::string("STANDARD_PER_PIXEL");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 406 ) != m_toString.end() )
	{
		vgLogDebug("(406, INPUT2_OUTPUT_BUFFER3) already in m_toString enum registry");
		assert( false && "(406, INPUT2_OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toString[ 406 ] = std::string("INPUT2_OUTPUT_BUFFER3");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 401 ) != m_toString.end() )
	{
		vgLogDebug("(401, INPUT1_PREVIOUS0) already in m_toString enum registry");
		assert( false && "(401, INPUT1_PREVIOUS0) already in registry" );
	}
	#endif

	m_toString[ 401 ] = std::string("INPUT1_PREVIOUS0");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 408 ) != m_toString.end() )
	{
		vgLogDebug("(408, INPUT2_OUTPUT_BUFFER5) already in m_toString enum registry");
		assert( false && "(408, INPUT2_OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toString[ 408 ] = std::string("INPUT2_OUTPUT_BUFFER5");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 407 ) != m_toString.end() )
	{
		vgLogDebug("(407, INPUT2_OUTPUT_BUFFER4) already in m_toString enum registry");
		assert( false && "(407, INPUT2_OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toString[ 407 ] = std::string("INPUT2_OUTPUT_BUFFER4");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 410 ) != m_toString.end() )
	{
		vgLogDebug("(410, INPUT2_OUTPUT_BUFFER7) already in m_toString enum registry");
		assert( false && "(410, INPUT2_OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toString[ 410 ] = std::string("INPUT2_OUTPUT_BUFFER7");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 409 ) != m_toString.end() )
	{
		vgLogDebug("(409, INPUT2_OUTPUT_BUFFER6) already in m_toString enum registry");
		assert( false && "(409, INPUT2_OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toString[ 409 ] = std::string("INPUT2_OUTPUT_BUFFER6");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 462 ) != m_toString.end() )
	{
		vgLogDebug("(462, AUTOMATIC) already in m_toString enum registry");
		assert( false && "(462, AUTOMATIC) already in registry" );
	}
	#endif

	m_toString[ 462 ] = std::string("AUTOMATIC");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 373 ) != m_toString.end() )
	{
		vgLogDebug("(373, NO_FILTER) already in m_toString enum registry");
		assert( false && "(373, NO_FILTER) already in registry" );
	}
	#endif

	m_toString[ 373 ] = std::string("NO_FILTER");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 336 ) != m_toString.end() )
	{
		vgLogDebug("(336, SCALE_FACTOR) already in m_toString enum registry");
		assert( false && "(336, SCALE_FACTOR) already in registry" );
	}
	#endif

	m_toString[ 336 ] = std::string("SCALE_FACTOR");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 327 ) != m_toString.end() )
	{
		vgLogDebug("(327, SHADOW_MAPPING_256UM) already in m_toString enum registry");
		assert( false && "(327, SHADOW_MAPPING_256UM) already in registry" );
	}
	#endif

	m_toString[ 327 ] = std::string("SHADOW_MAPPING_256UM");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 303 ) != m_toString.end() )
	{
		vgLogDebug("(303, STANDARD_PER_VERTEX) already in m_toString enum registry");
		assert( false && "(303, STANDARD_PER_VERTEX) already in registry" );
	}
	#endif

	m_toString[ 303 ] = std::string("STANDARD_PER_VERTEX");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 413 ) != m_toString.end() )
	{
		vgLogDebug("(413, INPUT2_NONE) already in m_toString enum registry");
		assert( false && "(413, INPUT2_NONE) already in registry" );
	}
	#endif

	m_toString[ 413 ] = std::string("INPUT2_NONE");

	//
	#ifdef _DEBUG
	if ( m_toString.find( 272 ) != m_toString.end() )
	{
		vgLogDebug("(272, NONE) already in m_toString enum registry");
		assert( false && "(272, NONE) already in registry" );
	}
	#endif

	m_toString[ 272 ] = std::string("NONE");

	// Initializes m_toEnum map

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 290 ) != m_toEnum.end() )
	{
		vgLogDebug("(290, NORMALIZED) already in m_toEnum enum registry");
		assert( false && "(290, NORMALIZED) already in registry" );
	}
	#endif

	m_toEnum[ 290 ] = vgd::makeShp( new vgd::node::GeoMorph::MethodValueType(290) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 300 ) != m_toEnum.end() )
	{
		vgLogDebug("(300, CHOICE3) already in m_toEnum enum registry");
		assert( false && "(300, CHOICE3) already in registry" );
	}
	#endif

	m_toEnum[ 300 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(300) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 299 ) != m_toEnum.end() )
	{
		vgLogDebug("(299, CHOICE2) already in m_toEnum enum registry");
		assert( false && "(299, CHOICE2) already in registry" );
	}
	#endif

	m_toEnum[ 299 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(299) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 298 ) != m_toEnum.end() )
	{
		vgLogDebug("(298, CHOICE1) already in m_toEnum enum registry");
		assert( false && "(298, CHOICE1) already in registry" );
	}
	#endif

	m_toEnum[ 298 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(298) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 297 ) != m_toEnum.end() )
	{
		vgLogDebug("(297, CHOICE0) already in m_toEnum enum registry");
		assert( false && "(297, CHOICE0) already in registry" );
	}
	#endif

	m_toEnum[ 297 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(297) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 367 ) != m_toEnum.end() )
	{
		vgLogDebug("(367, ADD) already in m_toEnum enum registry");
		assert( false && "(367, ADD) already in registry" );
	}
	#endif

	m_toEnum[ 367 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(367) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 346 ) != m_toEnum.end() )
	{
		vgLogDebug("(346, COLOR) already in m_toEnum enum registry");
		assert( false && "(346, COLOR) already in registry" );
	}
	#endif

	m_toEnum[ 346 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(346) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 444 ) != m_toEnum.end() )
	{
		vgLogDebug("(444, LINEAR_MIPMAP_LINEAR) already in m_toEnum enum registry");
		assert( false && "(444, LINEAR_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toEnum[ 444 ] = vgd::makeShp( new vgd::node::Texture::FilteringValueType(444) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 261 ) != m_toEnum.end() )
	{
		vgLogDebug("(261, EYE_RIGHT) already in m_toEnum enum registry");
		assert( false && "(261, EYE_RIGHT) already in registry" );
	}
	#endif

	m_toEnum[ 261 ] = vgd::makeShp( new vgd::node::Camera::EyeUsagePolicyValueType(261) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 274 ) != m_toEnum.end() )
	{
		vgLogDebug("(274, CUSTOM) already in m_toEnum enum registry");
		assert( false && "(274, CUSTOM) already in registry" );
	}
	#endif

	m_toEnum[ 274 ] = vgd::makeShp( new vgd::node::Displacement::PredefinedDisplacementValueType(274) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 286 ) != m_toEnum.end() )
	{
		vgLogDebug("(286, AA_OBJECT_SPACE) already in m_toEnum enum registry");
		assert( false && "(286, AA_OBJECT_SPACE) already in registry" );
	}
	#endif

	m_toEnum[ 286 ] = vgd::makeShp( new vgd::node::DrawStyle::BoundingBoxValueType(286) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 328 ) != m_toEnum.end() )
	{
		vgLogDebug("(328, LOW) already in m_toEnum enum registry");
		assert( false && "(328, LOW) already in registry" );
	}
	#endif

	m_toEnum[ 328 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapSizeValueType(328) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 360 ) != m_toEnum.end() )
	{
		vgLogDebug("(360, BLOOM_VERT) already in m_toEnum enum registry");
		assert( false && "(360, BLOOM_VERT) already in registry" );
	}
	#endif

	m_toEnum[ 360 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(360) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 258 ) != m_toEnum.end() )
	{
		vgLogDebug("(258, NONE) already in m_toEnum enum registry");
		assert( false && "(258, NONE) already in registry" );
	}
	#endif

	m_toEnum[ 258 ] = vgd::makeShp( new vgd::node::Antialiasing::TechniqueValueType(258) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 329 ) != m_toEnum.end() )
	{
		vgLogDebug("(329, MEDIUM) already in m_toEnum enum registry");
		assert( false && "(329, MEDIUM) already in registry" );
	}
	#endif

	m_toEnum[ 329 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapSizeValueType(329) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 292 ) != m_toEnum.end() )
	{
		vgLogDebug("(292, CW) already in m_toEnum enum registry");
		assert( false && "(292, CW) already in registry" );
	}
	#endif

	m_toEnum[ 292 ] = vgd::makeShp( new vgd::node::FrontFace::OrientationValueType(292) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 312 ) != m_toEnum.end() )
	{
		vgLogDebug("(312, SHADOW_MAPPING_9U) already in m_toEnum enum registry");
		assert( false && "(312, SHADOW_MAPPING_9U) already in registry" );
	}
	#endif

	m_toEnum[ 312 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(312) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 342 ) != m_toEnum.end() )
	{
		vgLogDebug("(342, LUMINANCE_FOR_DEPTH) already in m_toEnum enum registry");
		assert( false && "(342, LUMINANCE_FOR_DEPTH) already in registry" );
	}
	#endif

	m_toEnum[ 342 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(342) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 283 ) != m_toEnum.end() )
	{
		vgLogDebug("(283, NEIGHBOUR) already in m_toEnum enum registry");
		assert( false && "(283, NEIGHBOUR) already in registry" );
	}
	#endif

	m_toEnum[ 283 ] = vgd::makeShp( new vgd::node::DrawStyle::ShapeValueType(283) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 441 ) != m_toEnum.end() )
	{
		vgLogDebug("(441, NEAREST_MIPMAP_NEAREST) already in m_toEnum enum registry");
		assert( false && "(441, NEAREST_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toEnum[ 441 ] = vgd::makeShp( new vgd::node::Texture::FilteringValueType(441) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 351 ) != m_toEnum.end() )
	{
		vgLogDebug("(351, CUSTOM) already in m_toEnum enum registry");
		assert( false && "(351, CUSTOM) already in registry" );
	}
	#endif

	m_toEnum[ 351 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(351) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 308 ) != m_toEnum.end() )
	{
		vgLogDebug("(308, SHADOW_MAPPING) already in m_toEnum enum registry");
		assert( false && "(308, SHADOW_MAPPING) already in registry" );
	}
	#endif

	m_toEnum[ 308 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(308) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 437 ) != m_toEnum.end() )
	{
		vgLogDebug("(437, MIN_FILTER) already in m_toEnum enum registry");
		assert( false && "(437, MIN_FILTER) already in registry" );
	}
	#endif

	m_toEnum[ 437 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(437) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 386 ) != m_toEnum.end() )
	{
		vgLogDebug("(386, INPUT0SAMPLING_NONE) already in m_toEnum enum registry");
		assert( false && "(386, INPUT0SAMPLING_NONE) already in registry" );
	}
	#endif

	m_toEnum[ 386 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0SamplingValueType(386) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 450 ) != m_toEnum.end() )
	{
		vgLogDebug("(450, DEPTH_COMPONENT_32) already in m_toEnum enum registry");
		assert( false && "(450, DEPTH_COMPONENT_32) already in registry" );
	}
	#endif

	m_toEnum[ 450 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(450) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 291 ) != m_toEnum.end() )
	{
		vgLogDebug("(291, CCW) already in m_toEnum enum registry");
		assert( false && "(291, CCW) already in registry" );
	}
	#endif

	m_toEnum[ 291 ] = vgd::makeShp( new vgd::node::FrontFace::OrientationValueType(291) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 423 ) != m_toEnum.end() )
	{
		vgLogDebug("(423, UNIFORM) already in m_toEnum enum registry");
		assert( false && "(423, UNIFORM) already in registry" );
	}
	#endif

	m_toEnum[ 423 ] = vgd::makeShp( new vgd::node::TessellationLevel::MethodValueType(423) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 456 ) != m_toEnum.end() )
	{
		vgLogDebug("(456, LUMINANCE_16F) already in m_toEnum enum registry");
		assert( false && "(456, LUMINANCE_16F) already in registry" );
	}
	#endif

	m_toEnum[ 456 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(456) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 411 ) != m_toEnum.end() )
	{
		vgLogDebug("(411, INPUT2_TEXTURE0) already in m_toEnum enum registry");
		assert( false && "(411, INPUT2_TEXTURE0) already in registry" );
	}
	#endif

	m_toEnum[ 411 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(411) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 368 ) != m_toEnum.end() )
	{
		vgLogDebug("(368, SUB) already in m_toEnum enum registry");
		assert( false && "(368, SUB) already in registry" );
	}
	#endif

	m_toEnum[ 368 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(368) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 371 ) != m_toEnum.end() )
	{
		vgLogDebug("(371, COMBINE2_AND_SCALE) already in m_toEnum enum registry");
		assert( false && "(371, COMBINE2_AND_SCALE) already in registry" );
	}
	#endif

	m_toEnum[ 371 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(371) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 358 ) != m_toEnum.end() )
	{
		vgLogDebug("(358, BLUR_VERT) already in m_toEnum enum registry");
		assert( false && "(358, BLUR_VERT) already in registry" );
	}
	#endif

	m_toEnum[ 358 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(358) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 395 ) != m_toEnum.end() )
	{
		vgLogDebug("(395, INPUT1_OUTPUT_BUFFER3) already in m_toEnum enum registry");
		assert( false && "(395, INPUT1_OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toEnum[ 395 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(395) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 270 ) != m_toEnum.end() )
	{
		vgLogDebug("(270, PINHOLE) already in m_toEnum enum registry");
		assert( false && "(270, PINHOLE) already in registry" );
	}
	#endif

	m_toEnum[ 270 ] = vgd::makeShp( new vgd::node::DepthOfField::CameraModelValueType(270) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 445 ) != m_toEnum.end() )
	{
		vgLogDebug("(445, IMAGE) already in m_toEnum enum registry");
		assert( false && "(445, IMAGE) already in registry" );
	}
	#endif

	m_toEnum[ 445 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(445) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 434 ) != m_toEnum.end() )
	{
		vgLogDebug("(434, CLAMP_TO_BORDER) already in m_toEnum enum registry");
		assert( false && "(434, CLAMP_TO_BORDER) already in registry" );
	}
	#endif

	m_toEnum[ 434 ] = vgd::makeShp( new vgd::node::Texture::WrappingValueType(434) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 435 ) != m_toEnum.end() )
	{
		vgLogDebug("(435, MIRRORED_REPEAT) already in m_toEnum enum registry");
		assert( false && "(435, MIRRORED_REPEAT) already in registry" );
	}
	#endif

	m_toEnum[ 435 ] = vgd::makeShp( new vgd::node::Texture::WrappingValueType(435) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 332 ) != m_toEnum.end() )
	{
		vgLogDebug("(332, NEAREST) already in m_toEnum enum registry");
		assert( false && "(332, NEAREST) already in registry" );
	}
	#endif

	m_toEnum[ 332 ] = vgd::makeShp( new vgd::node::LightModel::ShadowFilteringValueType(332) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 343 ) != m_toEnum.end() )
	{
		vgLogDebug("(343, INTEGER) already in m_toEnum enum registry");
		assert( false && "(343, INTEGER) already in registry" );
	}
	#endif

	m_toEnum[ 343 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::TypeValueType(343) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 372 ) != m_toEnum.end() )
	{
		vgLogDebug("(372, COMBINE3_AND_SCALE) already in m_toEnum enum registry");
		assert( false && "(372, COMBINE3_AND_SCALE) already in registry" );
	}
	#endif

	m_toEnum[ 372 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(372) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 257 ) != m_toEnum.end() )
	{
		vgLogDebug("(257, vgd.node.BIND_PER_VERTEX) already in m_toEnum enum registry");
		assert( false && "(257, vgd.node.BIND_PER_VERTEX) already in registry" );
	}
	#endif

	m_toEnum[ 257 ] = vgd::makeShp( new vgd::node::Binding(257) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 305 ) != m_toEnum.end() )
	{
		vgLogDebug("(305, AT_INFINITY) already in m_toEnum enum registry");
		assert( false && "(305, AT_INFINITY) already in registry" );
	}
	#endif

	m_toEnum[ 305 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(305) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 416 ) != m_toEnum.end() )
	{
		vgLogDebug("(416, OUTPUT_OUTPUT_BUFFER1) already in m_toEnum enum registry");
		assert( false && "(416, OUTPUT_OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toEnum[ 416 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(416) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 415 ) != m_toEnum.end() )
	{
		vgLogDebug("(415, OUTPUT_OUTPUT_BUFFER0) already in m_toEnum enum registry");
		assert( false && "(415, OUTPUT_OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toEnum[ 415 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(415) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 449 ) != m_toEnum.end() )
	{
		vgLogDebug("(449, DEPTH_COMPONENT_24) already in m_toEnum enum registry");
		assert( false && "(449, DEPTH_COMPONENT_24) already in registry" );
	}
	#endif

	m_toEnum[ 449 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(449) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 337 ) != m_toEnum.end() )
	{
		vgLogDebug("(337, PIXEL_SIZE) already in m_toEnum enum registry");
		assert( false && "(337, PIXEL_SIZE) already in registry" );
	}
	#endif

	m_toEnum[ 337 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::SizeSemanticValueType(337) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 446 ) != m_toEnum.end() )
	{
		vgLogDebug("(446, SHADOW) already in m_toEnum enum registry");
		assert( false && "(446, SHADOW) already in registry" );
	}
	#endif

	m_toEnum[ 446 ] = vgd::makeShp( new vgd::node::Texture::UsageValueType(446) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 365 ) != m_toEnum.end() )
	{
		vgLogDebug("(365, UP_FILTER4_LINEAR) already in m_toEnum enum registry");
		assert( false && "(365, UP_FILTER4_LINEAR) already in registry" );
	}
	#endif

	m_toEnum[ 365 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(365) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 452 ) != m_toEnum.end() )
	{
		vgLogDebug("(452, RGB_16F) already in m_toEnum enum registry");
		assert( false && "(452, RGB_16F) already in registry" );
	}
	#endif

	m_toEnum[ 452 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(452) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 341 ) != m_toEnum.end() )
	{
		vgLogDebug("(341, LUMINANCE_ALPHA) already in m_toEnum enum registry");
		assert( false && "(341, LUMINANCE_ALPHA) already in registry" );
	}
	#endif

	m_toEnum[ 341 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(341) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 347 ) != m_toEnum.end() )
	{
		vgLogDebug("(347, NORMAL) already in m_toEnum enum registry");
		assert( false && "(347, NORMAL) already in registry" );
	}
	#endif

	m_toEnum[ 347 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(347) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 391 ) != m_toEnum.end() )
	{
		vgLogDebug("(391, LINEAR_MAXANISOTROPY16) already in m_toEnum enum registry");
		assert( false && "(391, LINEAR_MAXANISOTROPY16) already in registry" );
	}
	#endif

	m_toEnum[ 391 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0SamplingValueType(391) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 281 ) != m_toEnum.end() )
	{
		vgLogDebug("(281, FLAT_HIDDEN_LINE) already in m_toEnum enum registry");
		assert( false && "(281, FLAT_HIDDEN_LINE) already in registry" );
	}
	#endif

	m_toEnum[ 281 ] = vgd::makeShp( new vgd::node::DrawStyle::ShapeValueType(281) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 349 ) != m_toEnum.end() )
	{
		vgLogDebug("(349, DEPTH) already in m_toEnum enum registry");
		assert( false && "(349, DEPTH) already in registry" );
	}
	#endif

	m_toEnum[ 349 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(349) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 350 ) != m_toEnum.end() )
	{
		vgLogDebug("(350, LINEAR_DEPTH) already in m_toEnum enum registry");
		assert( false && "(350, LINEAR_DEPTH) already in registry" );
	}
	#endif

	m_toEnum[ 350 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(350) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 414 ) != m_toEnum.end() )
	{
		vgLogDebug("(414, OUTPUT_TMP0) already in m_toEnum enum registry");
		assert( false && "(414, OUTPUT_TMP0) already in registry" );
	}
	#endif

	m_toEnum[ 414 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(414) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 454 ) != m_toEnum.end() )
	{
		vgLogDebug("(454, RGBA_16F) already in m_toEnum enum registry");
		assert( false && "(454, RGBA_16F) already in registry" );
	}
	#endif

	m_toEnum[ 454 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(454) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 384 ) != m_toEnum.end() )
	{
		vgLogDebug("(384, PREVIOUS0) already in m_toEnum enum registry");
		assert( false && "(384, PREVIOUS0) already in registry" );
	}
	#endif

	m_toEnum[ 384 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(384) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 271 ) != m_toEnum.end() )
	{
		vgLogDebug("(271, THIN_LENS) already in m_toEnum enum registry");
		assert( false && "(271, THIN_LENS) already in registry" );
	}
	#endif

	m_toEnum[ 271 ] = vgd::makeShp( new vgd::node::DepthOfField::CameraModelValueType(271) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 276 ) != m_toEnum.end() )
	{
		vgLogDebug("(276, POINT) already in m_toEnum enum registry");
		assert( false && "(276, POINT) already in registry" );
	}
	#endif

	m_toEnum[ 276 ] = vgd::makeShp( new vgd::node::DrawStyle::ShapeValueType(276) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 369 ) != m_toEnum.end() )
	{
		vgLogDebug("(369, MIX_AND_SCALE) already in m_toEnum enum registry");
		assert( false && "(369, MIX_AND_SCALE) already in registry" );
	}
	#endif

	m_toEnum[ 369 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(369) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 439 ) != m_toEnum.end() )
	{
		vgLogDebug("(439, NEAREST) already in m_toEnum enum registry");
		assert( false && "(439, NEAREST) already in registry" );
	}
	#endif

	m_toEnum[ 439 ] = vgd::makeShp( new vgd::node::Texture::FilteringValueType(439) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 330 ) != m_toEnum.end() )
	{
		vgLogDebug("(330, HIGH) already in m_toEnum enum registry");
		assert( false && "(330, HIGH) already in registry" );
	}
	#endif

	m_toEnum[ 330 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapSizeValueType(330) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 301 ) != m_toEnum.end() )
	{
		vgLogDebug("(301, CHOICE4) already in m_toEnum enum registry");
		assert( false && "(301, CHOICE4) already in registry" );
	}
	#endif

	m_toEnum[ 301 ] = vgd::makeShp( new vgd::node::LightModel::Option0ValueType(301) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 448 ) != m_toEnum.end() )
	{
		vgLogDebug("(448, DEPTH_COMPONENT_16) already in m_toEnum enum registry");
		assert( false && "(448, DEPTH_COMPONENT_16) already in registry" );
	}
	#endif

	m_toEnum[ 448 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(448) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 317 ) != m_toEnum.end() )
	{
		vgLogDebug("(317, SHADOW_MAPPING_25UM) already in m_toEnum enum registry");
		assert( false && "(317, SHADOW_MAPPING_25UM) already in registry" );
	}
	#endif

	m_toEnum[ 317 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(317) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 458 ) != m_toEnum.end() )
	{
		vgLogDebug("(458, LUMINANCE_ALPHA_16F) already in m_toEnum enum registry");
		assert( false && "(458, LUMINANCE_ALPHA_16F) already in registry" );
	}
	#endif

	m_toEnum[ 458 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(458) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 338 ) != m_toEnum.end() )
	{
		vgLogDebug("(338, RGB) already in m_toEnum enum registry");
		assert( false && "(338, RGB) already in registry" );
	}
	#endif

	m_toEnum[ 338 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(338) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 433 ) != m_toEnum.end() )
	{
		vgLogDebug("(433, CLAMP_TO_EDGE) already in m_toEnum enum registry");
		assert( false && "(433, CLAMP_TO_EDGE) already in registry" );
	}
	#endif

	m_toEnum[ 433 ] = vgd::makeShp( new vgd::node::Texture::WrappingValueType(433) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 370 ) != m_toEnum.end() )
	{
		vgLogDebug("(370, ALPHAMIX_AND_SCALE) already in m_toEnum enum registry");
		assert( false && "(370, ALPHAMIX_AND_SCALE) already in registry" );
	}
	#endif

	m_toEnum[ 370 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(370) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 427 ) != m_toEnum.end() )
	{
		vgLogDebug("(427, PHONG) already in m_toEnum enum registry");
		assert( false && "(427, PHONG) already in registry" );
	}
	#endif

	m_toEnum[ 427 ] = vgd::makeShp( new vgd::node::TessellationProperties::TessellationValueType(427) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 340 ) != m_toEnum.end() )
	{
		vgLogDebug("(340, LUMINANCE) already in m_toEnum enum registry");
		assert( false && "(340, LUMINANCE) already in registry" );
	}
	#endif

	m_toEnum[ 340 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(340) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 377 ) != m_toEnum.end() )
	{
		vgLogDebug("(377, OUTPUT_BUFFER2) already in m_toEnum enum registry");
		assert( false && "(377, OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toEnum[ 377 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(377) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 376 ) != m_toEnum.end() )
	{
		vgLogDebug("(376, OUTPUT_BUFFER1) already in m_toEnum enum registry");
		assert( false && "(376, OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toEnum[ 376 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(376) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 375 ) != m_toEnum.end() )
	{
		vgLogDebug("(375, OUTPUT_BUFFER0) already in m_toEnum enum registry");
		assert( false && "(375, OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toEnum[ 375 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(375) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 382 ) != m_toEnum.end() )
	{
		vgLogDebug("(382, OUTPUT_BUFFER7) already in m_toEnum enum registry");
		assert( false && "(382, OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toEnum[ 382 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(382) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 381 ) != m_toEnum.end() )
	{
		vgLogDebug("(381, OUTPUT_BUFFER6) already in m_toEnum enum registry");
		assert( false && "(381, OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toEnum[ 381 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(381) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 380 ) != m_toEnum.end() )
	{
		vgLogDebug("(380, OUTPUT_BUFFER5) already in m_toEnum enum registry");
		assert( false && "(380, OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toEnum[ 380 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(380) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 379 ) != m_toEnum.end() )
	{
		vgLogDebug("(379, OUTPUT_BUFFER4) already in m_toEnum enum registry");
		assert( false && "(379, OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toEnum[ 379 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(379) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 344 ) != m_toEnum.end() )
	{
		vgLogDebug("(344, FLOAT16) already in m_toEnum enum registry");
		assert( false && "(344, FLOAT16) already in registry" );
	}
	#endif

	m_toEnum[ 344 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::TypeValueType(344) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 302 ) != m_toEnum.end() )
	{
		vgLogDebug("(302, LIGHTING_OFF) already in m_toEnum enum registry");
		assert( false && "(302, LIGHTING_OFF) already in registry" );
	}
	#endif

	m_toEnum[ 302 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(302) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 461 ) != m_toEnum.end() )
	{
		vgLogDebug("(461, APPEND) already in m_toEnum enum registry");
		assert( false && "(461, APPEND) already in registry" );
	}
	#endif

	m_toEnum[ 461 ] = vgd::makeShp( new vgd::node::Uniforms::ComposeModeValueType(461) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 447 ) != m_toEnum.end() )
	{
		vgLogDebug("(447, AUTOMATIC) already in m_toEnum enum registry");
		assert( false && "(447, AUTOMATIC) already in registry" );
	}
	#endif

	m_toEnum[ 447 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(447) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 378 ) != m_toEnum.end() )
	{
		vgLogDebug("(378, OUTPUT_BUFFER3) already in m_toEnum enum registry");
		assert( false && "(378, OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toEnum[ 378 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(378) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 294 ) != m_toEnum.end() )
	{
		vgLogDebug("(294, INT24) already in m_toEnum enum registry");
		assert( false && "(294, INT24) already in registry" );
	}
	#endif

	m_toEnum[ 294 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(294) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 466 ) != m_toEnum.end() )
	{
		vgLogDebug("(466, STREAM) already in m_toEnum enum registry");
		assert( false && "(466, STREAM) already in registry" );
	}
	#endif

	m_toEnum[ 466 ] = vgd::makeShp( new vgd::node::VertexShape::DeformableHintValueType(466) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 256 ) != m_toEnum.end() )
	{
		vgLogDebug("(256, vgd.node.BIND_OFF) already in m_toEnum enum registry");
		assert( false && "(256, vgd.node.BIND_OFF) already in registry" );
	}
	#endif

	m_toEnum[ 256 ] = vgd::makeShp( new vgd::node::Binding(256) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 400 ) != m_toEnum.end() )
	{
		vgLogDebug("(400, INPUT1_TEXTURE0) already in m_toEnum enum registry");
		assert( false && "(400, INPUT1_TEXTURE0) already in registry" );
	}
	#endif

	m_toEnum[ 400 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(400) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 273 ) != m_toEnum.end() )
	{
		vgLogDebug("(273, ALONG_NORMAL) already in m_toEnum enum registry");
		assert( false && "(273, ALONG_NORMAL) already in registry" );
	}
	#endif

	m_toEnum[ 273 ] = vgd::makeShp( new vgd::node::Displacement::PredefinedDisplacementValueType(273) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 277 ) != m_toEnum.end() )
	{
		vgLogDebug("(277, FLAT) already in m_toEnum enum registry");
		assert( false && "(277, FLAT) already in registry" );
	}
	#endif

	m_toEnum[ 277 ] = vgd::makeShp( new vgd::node::DrawStyle::ShapeValueType(277) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 265 ) != m_toEnum.end() )
	{
		vgLogDebug("(265, ANAGLYPH) already in m_toEnum enum registry");
		assert( false && "(265, ANAGLYPH) already in registry" );
	}
	#endif

	m_toEnum[ 265 ] = vgd::makeShp( new vgd::node::Camera::ModeValueType(265) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 260 ) != m_toEnum.end() )
	{
		vgLogDebug("(260, EYE_LEFT) already in m_toEnum enum registry");
		assert( false && "(260, EYE_LEFT) already in registry" );
	}
	#endif

	m_toEnum[ 260 ] = vgd::makeShp( new vgd::node::Camera::EyeUsagePolicyValueType(260) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 432 ) != m_toEnum.end() )
	{
		vgLogDebug("(432, CLAMP) already in m_toEnum enum registry");
		assert( false && "(432, CLAMP) already in registry" );
	}
	#endif

	m_toEnum[ 432 ] = vgd::makeShp( new vgd::node::Texture::WrappingValueType(432) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 465 ) != m_toEnum.end() )
	{
		vgLogDebug("(465, DYNAMIC) already in m_toEnum enum registry");
		assert( false && "(465, DYNAMIC) already in registry" );
	}
	#endif

	m_toEnum[ 465 ] = vgd::makeShp( new vgd::node::VertexShape::DeformableHintValueType(465) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 263 ) != m_toEnum.end() )
	{
		vgLogDebug("(263, MONOSCOPIC) already in m_toEnum enum registry");
		assert( false && "(263, MONOSCOPIC) already in registry" );
	}
	#endif

	m_toEnum[ 263 ] = vgd::makeShp( new vgd::node::Camera::ModeValueType(263) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 355 ) != m_toEnum.end() )
	{
		vgLogDebug("(355, COLOR_INVERSE) already in m_toEnum enum registry");
		assert( false && "(355, COLOR_INVERSE) already in registry" );
	}
	#endif

	m_toEnum[ 355 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(355) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 387 ) != m_toEnum.end() )
	{
		vgLogDebug("(387, NEAREST_MAXANISOTROPY1) already in m_toEnum enum registry");
		assert( false && "(387, NEAREST_MAXANISOTROPY1) already in registry" );
	}
	#endif

	m_toEnum[ 387 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0SamplingValueType(387) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 402 ) != m_toEnum.end() )
	{
		vgLogDebug("(402, INPUT1_NONE) already in m_toEnum enum registry");
		assert( false && "(402, INPUT1_NONE) already in registry" );
	}
	#endif

	m_toEnum[ 402 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(402) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 296 ) != m_toEnum.end() )
	{
		vgLogDebug("(296, FLOAT32) already in m_toEnum enum registry");
		assert( false && "(296, FLOAT32) already in registry" );
	}
	#endif

	m_toEnum[ 296 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(296) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 412 ) != m_toEnum.end() )
	{
		vgLogDebug("(412, INPUT2_PREVIOUS0) already in m_toEnum enum registry");
		assert( false && "(412, INPUT2_PREVIOUS0) already in registry" );
	}
	#endif

	m_toEnum[ 412 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(412) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 262 ) != m_toEnum.end() )
	{
		vgLogDebug("(262, EYE_BOTH) already in m_toEnum enum registry");
		assert( false && "(262, EYE_BOTH) already in registry" );
	}
	#endif

	m_toEnum[ 262 ] = vgd::makeShp( new vgd::node::Camera::EyeUsagePolicyValueType(262) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 320 ) != m_toEnum.end() )
	{
		vgLogDebug("(320, SHADOW_MAPPING_64U) already in m_toEnum enum registry");
		assert( false && "(320, SHADOW_MAPPING_64U) already in registry" );
	}
	#endif

	m_toEnum[ 320 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(320) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 353 ) != m_toEnum.end() )
	{
		vgLogDebug("(353, COLOR_TO_MONOCHROME) already in m_toEnum enum registry");
		assert( false && "(353, COLOR_TO_MONOCHROME) already in registry" );
	}
	#endif

	m_toEnum[ 353 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(353) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 311 ) != m_toEnum.end() )
	{
		vgLogDebug("(311, SHADOW_MAPPING_4DM) already in m_toEnum enum registry");
		assert( false && "(311, SHADOW_MAPPING_4DM) already in registry" );
	}
	#endif

	m_toEnum[ 311 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(311) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 394 ) != m_toEnum.end() )
	{
		vgLogDebug("(394, INPUT1_OUTPUT_BUFFER2) already in m_toEnum enum registry");
		assert( false && "(394, INPUT1_OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toEnum[ 394 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(394) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 393 ) != m_toEnum.end() )
	{
		vgLogDebug("(393, INPUT1_OUTPUT_BUFFER1) already in m_toEnum enum registry");
		assert( false && "(393, INPUT1_OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toEnum[ 393 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(393) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 392 ) != m_toEnum.end() )
	{
		vgLogDebug("(392, INPUT1_OUTPUT_BUFFER0) already in m_toEnum enum registry");
		assert( false && "(392, INPUT1_OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toEnum[ 392 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(392) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 399 ) != m_toEnum.end() )
	{
		vgLogDebug("(399, INPUT1_OUTPUT_BUFFER7) already in m_toEnum enum registry");
		assert( false && "(399, INPUT1_OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toEnum[ 399 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(399) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 398 ) != m_toEnum.end() )
	{
		vgLogDebug("(398, INPUT1_OUTPUT_BUFFER6) already in m_toEnum enum registry");
		assert( false && "(398, INPUT1_OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toEnum[ 398 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(398) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 397 ) != m_toEnum.end() )
	{
		vgLogDebug("(397, INPUT1_OUTPUT_BUFFER5) already in m_toEnum enum registry");
		assert( false && "(397, INPUT1_OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toEnum[ 397 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(397) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 396 ) != m_toEnum.end() )
	{
		vgLogDebug("(396, INPUT1_OUTPUT_BUFFER4) already in m_toEnum enum registry");
		assert( false && "(396, INPUT1_OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toEnum[ 396 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(396) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 287 ) != m_toEnum.end() )
	{
		vgLogDebug("(287, OBJECT_AND_AA_OBJECT_SPACE) already in m_toEnum enum registry");
		assert( false && "(287, OBJECT_AND_AA_OBJECT_SPACE) already in registry" );
	}
	#endif

	m_toEnum[ 287 ] = vgd::makeShp( new vgd::node::DrawStyle::BoundingBoxValueType(287) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 352 ) != m_toEnum.end() )
	{
		vgLogDebug("(352, IDENTITY) already in m_toEnum enum registry");
		assert( false && "(352, IDENTITY) already in registry" );
	}
	#endif

	m_toEnum[ 352 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(352) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 278 ) != m_toEnum.end() )
	{
		vgLogDebug("(278, SMOOTH) already in m_toEnum enum registry");
		assert( false && "(278, SMOOTH) already in registry" );
	}
	#endif

	m_toEnum[ 278 ] = vgd::makeShp( new vgd::node::DrawStyle::ShapeValueType(278) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 307 ) != m_toEnum.end() )
	{
		vgLogDebug("(307, SHADOW_OFF) already in m_toEnum enum registry");
		assert( false && "(307, SHADOW_OFF) already in registry" );
	}
	#endif

	m_toEnum[ 307 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(307) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 425 ) != m_toEnum.end() )
	{
		vgLogDebug("(425, CUSTOM) already in m_toEnum enum registry");
		assert( false && "(425, CUSTOM) already in registry" );
	}
	#endif

	m_toEnum[ 425 ] = vgd::makeShp( new vgd::node::TessellationLevel::MethodValueType(425) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 464 ) != m_toEnum.end() )
	{
		vgLogDebug("(464, STATIC) already in m_toEnum enum registry");
		assert( false && "(464, STATIC) already in registry" );
	}
	#endif

	m_toEnum[ 464 ] = vgd::makeShp( new vgd::node::VertexShape::DeformableHintValueType(464) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 295 ) != m_toEnum.end() )
	{
		vgLogDebug("(295, INT32) already in m_toEnum enum registry");
		assert( false && "(295, INT32) already in registry" );
	}
	#endif

	m_toEnum[ 295 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(295) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 361 ) != m_toEnum.end() )
	{
		vgLogDebug("(361, COLOR_EDGE_DETECT) already in m_toEnum enum registry");
		assert( false && "(361, COLOR_EDGE_DETECT) already in registry" );
	}
	#endif

	m_toEnum[ 361 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(361) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 443 ) != m_toEnum.end() )
	{
		vgLogDebug("(443, NEAREST_MIPMAP_LINEAR) already in m_toEnum enum registry");
		assert( false && "(443, NEAREST_MIPMAP_LINEAR) already in registry" );
	}
	#endif

	m_toEnum[ 443 ] = vgd::makeShp( new vgd::node::Texture::FilteringValueType(443) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 356 ) != m_toEnum.end() )
	{
		vgLogDebug("(356, SCALE_AND_BIAS) already in m_toEnum enum registry");
		assert( false && "(356, SCALE_AND_BIAS) already in registry" );
	}
	#endif

	m_toEnum[ 356 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(356) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 455 ) != m_toEnum.end() )
	{
		vgLogDebug("(455, RGBA_32F) already in m_toEnum enum registry");
		assert( false && "(455, RGBA_32F) already in registry" );
	}
	#endif

	m_toEnum[ 455 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(455) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 268 ) != m_toEnum.end() )
	{
		vgLogDebug("(268, FRONT) already in m_toEnum enum registry");
		assert( false && "(268, FRONT) already in registry" );
	}
	#endif

	m_toEnum[ 268 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(268) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 419 ) != m_toEnum.end() )
	{
		vgLogDebug("(419, OUTPUT_OUTPUT_BUFFER4) already in m_toEnum enum registry");
		assert( false && "(419, OUTPUT_OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toEnum[ 419 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(419) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 335 ) != m_toEnum.end() )
	{
		vgLogDebug("(335, PHOTON) already in m_toEnum enum registry");
		assert( false && "(335, PHOTON) already in registry" );
	}
	#endif

	m_toEnum[ 335 ] = vgd::makeShp( new vgd::node::Noise::NoiseModelValueType(335) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 428 ) != m_toEnum.end() )
	{
		vgLogDebug("(428, WRAP_S) already in m_toEnum enum registry");
		assert( false && "(428, WRAP_S) already in registry" );
	}
	#endif

	m_toEnum[ 428 ] = vgd::makeShp( new vgd::node::Texture::WrapSelectorValueType(428) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 442 ) != m_toEnum.end() )
	{
		vgLogDebug("(442, LINEAR_MIPMAP_NEAREST) already in m_toEnum enum registry");
		assert( false && "(442, LINEAR_MIPMAP_NEAREST) already in registry" );
	}
	#endif

	m_toEnum[ 442 ] = vgd::makeShp( new vgd::node::Texture::FilteringValueType(442) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 429 ) != m_toEnum.end() )
	{
		vgLogDebug("(429, WRAP_T) already in m_toEnum enum registry");
		assert( false && "(429, WRAP_T) already in registry" );
	}
	#endif

	m_toEnum[ 429 ] = vgd::makeShp( new vgd::node::Texture::WrapSelectorValueType(429) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 264 ) != m_toEnum.end() )
	{
		vgLogDebug("(264, QUAD_BUFFER) already in m_toEnum enum registry");
		assert( false && "(264, QUAD_BUFFER) already in registry" );
	}
	#endif

	m_toEnum[ 264 ] = vgd::makeShp( new vgd::node::Camera::ModeValueType(264) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 366 ) != m_toEnum.end() )
	{
		vgLogDebug("(366, OVER) already in m_toEnum enum registry");
		assert( false && "(366, OVER) already in registry" );
	}
	#endif

	m_toEnum[ 366 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(366) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 288 ) != m_toEnum.end() )
	{
		vgLogDebug("(288, DISABLED) already in m_toEnum enum registry");
		assert( false && "(288, DISABLED) already in registry" );
	}
	#endif

	m_toEnum[ 288 ] = vgd::makeShp( new vgd::node::GeoMorph::MethodValueType(288) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 362 ) != m_toEnum.end() )
	{
		vgLogDebug("(362, MEDIAN3x3) already in m_toEnum enum registry");
		assert( false && "(362, MEDIAN3x3) already in registry" );
	}
	#endif

	m_toEnum[ 362 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(362) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 345 ) != m_toEnum.end() )
	{
		vgLogDebug("(345, FLOAT32) already in m_toEnum enum registry");
		assert( false && "(345, FLOAT32) already in registry" );
	}
	#endif

	m_toEnum[ 345 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::TypeValueType(345) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 279 ) != m_toEnum.end() )
	{
		vgLogDebug("(279, WIREFRAME) already in m_toEnum enum registry");
		assert( false && "(279, WIREFRAME) already in registry" );
	}
	#endif

	m_toEnum[ 279 ] = vgd::makeShp( new vgd::node::DrawStyle::ShapeValueType(279) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 436 ) != m_toEnum.end() )
	{
		vgLogDebug("(436, ONCE) already in m_toEnum enum registry");
		assert( false && "(436, ONCE) already in registry" );
	}
	#endif

	m_toEnum[ 436 ] = vgd::makeShp( new vgd::node::Texture::WrappingValueType(436) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 280 ) != m_toEnum.end() )
	{
		vgLogDebug("(280, HIDDEN_LINE) already in m_toEnum enum registry");
		assert( false && "(280, HIDDEN_LINE) already in registry" );
	}
	#endif

	m_toEnum[ 280 ] = vgd::makeShp( new vgd::node::DrawStyle::ShapeValueType(280) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 430 ) != m_toEnum.end() )
	{
		vgLogDebug("(430, WRAP_R) already in m_toEnum enum registry");
		assert( false && "(430, WRAP_R) already in registry" );
	}
	#endif

	m_toEnum[ 430 ] = vgd::makeShp( new vgd::node::Texture::WrapSelectorValueType(430) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 385 ) != m_toEnum.end() )
	{
		vgLogDebug("(385, NONE) already in m_toEnum enum registry");
		assert( false && "(385, NONE) already in registry" );
	}
	#endif

	m_toEnum[ 385 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(385) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 323 ) != m_toEnum.end() )
	{
		vgLogDebug("(323, SHADOW_MAPPING_144UM) already in m_toEnum enum registry");
		assert( false && "(323, SHADOW_MAPPING_144UM) already in registry" );
	}
	#endif

	m_toEnum[ 323 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(323) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 339 ) != m_toEnum.end() )
	{
		vgLogDebug("(339, RGBA) already in m_toEnum enum registry");
		assert( false && "(339, RGBA) already in registry" );
	}
	#endif

	m_toEnum[ 339 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::FormatValueType(339) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 316 ) != m_toEnum.end() )
	{
		vgLogDebug("(316, SHADOW_MAPPING_25U) already in m_toEnum enum registry");
		assert( false && "(316, SHADOW_MAPPING_25U) already in registry" );
	}
	#endif

	m_toEnum[ 316 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(316) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 319 ) != m_toEnum.end() )
	{
		vgLogDebug("(319, SHADOW_MAPPING_36UM) already in m_toEnum enum registry");
		assert( false && "(319, SHADOW_MAPPING_36UM) already in registry" );
	}
	#endif

	m_toEnum[ 319 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(319) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 321 ) != m_toEnum.end() )
	{
		vgLogDebug("(321, SHADOW_MAPPING_64UM) already in m_toEnum enum registry");
		assert( false && "(321, SHADOW_MAPPING_64UM) already in registry" );
	}
	#endif

	m_toEnum[ 321 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(321) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 359 ) != m_toEnum.end() )
	{
		vgLogDebug("(359, BLOOM_HORIZ) already in m_toEnum enum registry");
		assert( false && "(359, BLOOM_HORIZ) already in registry" );
	}
	#endif

	m_toEnum[ 359 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(359) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 333 ) != m_toEnum.end() )
	{
		vgLogDebug("(333, LINEAR) already in m_toEnum enum registry");
		assert( false && "(333, LINEAR) already in registry" );
	}
	#endif

	m_toEnum[ 333 ] = vgd::makeShp( new vgd::node::LightModel::ShadowFilteringValueType(333) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 418 ) != m_toEnum.end() )
	{
		vgLogDebug("(418, OUTPUT_OUTPUT_BUFFER3) already in m_toEnum enum registry");
		assert( false && "(418, OUTPUT_OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toEnum[ 418 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(418) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 417 ) != m_toEnum.end() )
	{
		vgLogDebug("(417, OUTPUT_OUTPUT_BUFFER2) already in m_toEnum enum registry");
		assert( false && "(417, OUTPUT_OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toEnum[ 417 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(417) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 383 ) != m_toEnum.end() )
	{
		vgLogDebug("(383, TEXTURE0) already in m_toEnum enum registry");
		assert( false && "(383, TEXTURE0) already in registry" );
	}
	#endif

	m_toEnum[ 383 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0ValueType(383) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 289 ) != m_toEnum.end() )
	{
		vgLogDebug("(289, SKIP) already in m_toEnum enum registry");
		assert( false && "(289, SKIP) already in registry" );
	}
	#endif

	m_toEnum[ 289 ] = vgd::makeShp( new vgd::node::GeoMorph::MethodValueType(289) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 422 ) != m_toEnum.end() )
	{
		vgLogDebug("(422, OUTPUT_OUTPUT_BUFFER7) already in m_toEnum enum registry");
		assert( false && "(422, OUTPUT_OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toEnum[ 422 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(422) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 421 ) != m_toEnum.end() )
	{
		vgLogDebug("(421, OUTPUT_OUTPUT_BUFFER6) already in m_toEnum enum registry");
		assert( false && "(421, OUTPUT_OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toEnum[ 421 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(421) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 420 ) != m_toEnum.end() )
	{
		vgLogDebug("(420, OUTPUT_OUTPUT_BUFFER5) already in m_toEnum enum registry");
		assert( false && "(420, OUTPUT_OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toEnum[ 420 ] = vgd::makeShp( new vgd::node::PostProcessing::OutputValueType(420) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 310 ) != m_toEnum.end() )
	{
		vgLogDebug("(310, SHADOW_MAPPING_4UM) already in m_toEnum enum registry");
		assert( false && "(310, SHADOW_MAPPING_4UM) already in registry" );
	}
	#endif

	m_toEnum[ 310 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(310) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 322 ) != m_toEnum.end() )
	{
		vgLogDebug("(322, SHADOW_MAPPING_144U) already in m_toEnum enum registry");
		assert( false && "(322, SHADOW_MAPPING_144U) already in registry" );
	}
	#endif

	m_toEnum[ 322 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(322) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 404 ) != m_toEnum.end() )
	{
		vgLogDebug("(404, INPUT2_OUTPUT_BUFFER1) already in m_toEnum enum registry");
		assert( false && "(404, INPUT2_OUTPUT_BUFFER1) already in registry" );
	}
	#endif

	m_toEnum[ 404 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(404) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 403 ) != m_toEnum.end() )
	{
		vgLogDebug("(403, INPUT2_OUTPUT_BUFFER0) already in m_toEnum enum registry");
		assert( false && "(403, INPUT2_OUTPUT_BUFFER0) already in registry" );
	}
	#endif

	m_toEnum[ 403 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(403) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 440 ) != m_toEnum.end() )
	{
		vgLogDebug("(440, LINEAR) already in m_toEnum enum registry");
		assert( false && "(440, LINEAR) already in registry" );
	}
	#endif

	m_toEnum[ 440 ] = vgd::makeShp( new vgd::node::Texture::FilteringValueType(440) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 457 ) != m_toEnum.end() )
	{
		vgLogDebug("(457, LUMINANCE_32F) already in m_toEnum enum registry");
		assert( false && "(457, LUMINANCE_32F) already in registry" );
	}
	#endif

	m_toEnum[ 457 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(457) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 285 ) != m_toEnum.end() )
	{
		vgLogDebug("(285, OBJECT_SPACE) already in m_toEnum enum registry");
		assert( false && "(285, OBJECT_SPACE) already in registry" );
	}
	#endif

	m_toEnum[ 285 ] = vgd::makeShp( new vgd::node::DrawStyle::BoundingBoxValueType(285) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 424 ) != m_toEnum.end() )
	{
		vgLogDebug("(424, PIXELS_PER_EDGE) already in m_toEnum enum registry");
		assert( false && "(424, PIXELS_PER_EDGE) already in registry" );
	}
	#endif

	m_toEnum[ 424 ] = vgd::makeShp( new vgd::node::TessellationLevel::MethodValueType(424) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 405 ) != m_toEnum.end() )
	{
		vgLogDebug("(405, INPUT2_OUTPUT_BUFFER2) already in m_toEnum enum registry");
		assert( false && "(405, INPUT2_OUTPUT_BUFFER2) already in registry" );
	}
	#endif

	m_toEnum[ 405 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(405) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 334 ) != m_toEnum.end() )
	{
		vgLogDebug("(334, NO) already in m_toEnum enum registry");
		assert( false && "(334, NO) already in registry" );
	}
	#endif

	m_toEnum[ 334 ] = vgd::makeShp( new vgd::node::Noise::NoiseModelValueType(334) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 275 ) != m_toEnum.end() )
	{
		vgLogDebug("(275, NO_SHAPE) already in m_toEnum enum registry");
		assert( false && "(275, NO_SHAPE) already in registry" );
	}
	#endif

	m_toEnum[ 275 ] = vgd::makeShp( new vgd::node::DrawStyle::ShapeValueType(275) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 426 ) != m_toEnum.end() )
	{
		vgLogDebug("(426, DISABLED) already in m_toEnum enum registry");
		assert( false && "(426, DISABLED) already in registry" );
	}
	#endif

	m_toEnum[ 426 ] = vgd::makeShp( new vgd::node::TessellationProperties::TessellationValueType(426) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 357 ) != m_toEnum.end() )
	{
		vgLogDebug("(357, BLUR_HORIZ) already in m_toEnum enum registry");
		assert( false && "(357, BLUR_HORIZ) already in registry" );
	}
	#endif

	m_toEnum[ 357 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(357) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 438 ) != m_toEnum.end() )
	{
		vgLogDebug("(438, MAG_FILTER) already in m_toEnum enum registry");
		assert( false && "(438, MAG_FILTER) already in registry" );
	}
	#endif

	m_toEnum[ 438 ] = vgd::makeShp( new vgd::node::Texture::FilterValueType(438) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 284 ) != m_toEnum.end() )
	{
		vgLogDebug("(284, NO_BOUNDING_BOX) already in m_toEnum enum registry");
		assert( false && "(284, NO_BOUNDING_BOX) already in registry" );
	}
	#endif

	m_toEnum[ 284 ] = vgd::makeShp( new vgd::node::DrawStyle::BoundingBoxValueType(284) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 354 ) != m_toEnum.end() )
	{
		vgLogDebug("(354, COLOR_TO_SEPIA) already in m_toEnum enum registry");
		assert( false && "(354, COLOR_TO_SEPIA) already in registry" );
	}
	#endif

	m_toEnum[ 354 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(354) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 309 ) != m_toEnum.end() )
	{
		vgLogDebug("(309, SHADOW_MAPPING_4U) already in m_toEnum enum registry");
		assert( false && "(309, SHADOW_MAPPING_4U) already in registry" );
	}
	#endif

	m_toEnum[ 309 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(309) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 460 ) != m_toEnum.end() )
	{
		vgLogDebug("(460, REPLACE) already in m_toEnum enum registry");
		assert( false && "(460, REPLACE) already in registry" );
	}
	#endif

	m_toEnum[ 460 ] = vgd::makeShp( new vgd::node::Uniforms::ComposeModeValueType(460) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 266 ) != m_toEnum.end() )
	{
		vgLogDebug("(266, DISABLED) already in m_toEnum enum registry");
		assert( false && "(266, DISABLED) already in registry" );
	}
	#endif

	m_toEnum[ 266 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(266) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 259 ) != m_toEnum.end() )
	{
		vgLogDebug("(259, FXAA1) already in m_toEnum enum registry");
		assert( false && "(259, FXAA1) already in registry" );
	}
	#endif

	m_toEnum[ 259 ] = vgd::makeShp( new vgd::node::Antialiasing::TechniqueValueType(259) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 431 ) != m_toEnum.end() )
	{
		vgLogDebug("(431, REPEAT) already in m_toEnum enum registry");
		assert( false && "(431, REPEAT) already in registry" );
	}
	#endif

	m_toEnum[ 431 ] = vgd::makeShp( new vgd::node::Texture::WrappingValueType(431) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 293 ) != m_toEnum.end() )
	{
		vgLogDebug("(293, INT16) already in m_toEnum enum registry");
		assert( false && "(293, INT16) already in registry" );
	}
	#endif

	m_toEnum[ 293 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapTypeValueType(293) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 326 ) != m_toEnum.end() )
	{
		vgLogDebug("(326, SHADOW_MAPPING_256U) already in m_toEnum enum registry");
		assert( false && "(326, SHADOW_MAPPING_256U) already in registry" );
	}
	#endif

	m_toEnum[ 326 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(326) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 388 ) != m_toEnum.end() )
	{
		vgLogDebug("(388, LINEAR_MAXANISOTROPY1) already in m_toEnum enum registry");
		assert( false && "(388, LINEAR_MAXANISOTROPY1) already in registry" );
	}
	#endif

	m_toEnum[ 388 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0SamplingValueType(388) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 459 ) != m_toEnum.end() )
	{
		vgLogDebug("(459, LUMINANCE_ALPHA_32F) already in m_toEnum enum registry");
		assert( false && "(459, LUMINANCE_ALPHA_32F) already in registry" );
	}
	#endif

	m_toEnum[ 459 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(459) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 267 ) != m_toEnum.end() )
	{
		vgLogDebug("(267, BACK) already in m_toEnum enum registry");
		assert( false && "(267, BACK) already in registry" );
	}
	#endif

	m_toEnum[ 267 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(267) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 389 ) != m_toEnum.end() )
	{
		vgLogDebug("(389, LINEAR_MAXANISOTROPY4) already in m_toEnum enum registry");
		assert( false && "(389, LINEAR_MAXANISOTROPY4) already in registry" );
	}
	#endif

	m_toEnum[ 389 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0SamplingValueType(389) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 313 ) != m_toEnum.end() )
	{
		vgLogDebug("(313, SHADOW_MAPPING_9UM) already in m_toEnum enum registry");
		assert( false && "(313, SHADOW_MAPPING_9UM) already in registry" );
	}
	#endif

	m_toEnum[ 313 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(313) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 390 ) != m_toEnum.end() )
	{
		vgLogDebug("(390, LINEAR_MAXANISOTROPY8) already in m_toEnum enum registry");
		assert( false && "(390, LINEAR_MAXANISOTROPY8) already in registry" );
	}
	#endif

	m_toEnum[ 390 ] = vgd::makeShp( new vgd::node::PostProcessing::Input0SamplingValueType(390) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 314 ) != m_toEnum.end() )
	{
		vgLogDebug("(314, SHADOW_MAPPING_16U) already in m_toEnum enum registry");
		assert( false && "(314, SHADOW_MAPPING_16U) already in registry" );
	}
	#endif

	m_toEnum[ 314 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(314) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 306 ) != m_toEnum.end() )
	{
		vgLogDebug("(306, AT_EYE) already in m_toEnum enum registry");
		assert( false && "(306, AT_EYE) already in registry" );
	}
	#endif

	m_toEnum[ 306 ] = vgd::makeShp( new vgd::node::LightModel::ViewerValueType(306) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 364 ) != m_toEnum.end() )
	{
		vgLogDebug("(364, UP_FILTER4) already in m_toEnum enum registry");
		assert( false && "(364, UP_FILTER4) already in registry" );
	}
	#endif

	m_toEnum[ 364 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(364) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 451 ) != m_toEnum.end() )
	{
		vgLogDebug("(451, DEPTH_COMPONENT_32F) already in m_toEnum enum registry");
		assert( false && "(451, DEPTH_COMPONENT_32F) already in registry" );
	}
	#endif

	m_toEnum[ 451 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(451) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 331 ) != m_toEnum.end() )
	{
		vgLogDebug("(331, VERY_HIGH) already in m_toEnum enum registry");
		assert( false && "(331, VERY_HIGH) already in registry" );
	}
	#endif

	m_toEnum[ 331 ] = vgd::makeShp( new vgd::node::LightModel::ShadowMapSizeValueType(331) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 363 ) != m_toEnum.end() )
	{
		vgLogDebug("(363, DOWN_FILTER4) already in m_toEnum enum registry");
		assert( false && "(363, DOWN_FILTER4) already in registry" );
	}
	#endif

	m_toEnum[ 363 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(363) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 374 ) != m_toEnum.end() )
	{
		vgLogDebug("(374, CUSTOM_FILTER) already in m_toEnum enum registry");
		assert( false && "(374, CUSTOM_FILTER) already in registry" );
	}
	#endif

	m_toEnum[ 374 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(374) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 348 ) != m_toEnum.end() )
	{
		vgLogDebug("(348, POSITION) already in m_toEnum enum registry");
		assert( false && "(348, POSITION) already in registry" );
	}
	#endif

	m_toEnum[ 348 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::CommandValueType(348) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 453 ) != m_toEnum.end() )
	{
		vgLogDebug("(453, RGB_32F) already in m_toEnum enum registry");
		assert( false && "(453, RGB_32F) already in registry" );
	}
	#endif

	m_toEnum[ 453 ] = vgd::makeShp( new vgd::node::Texture::InternalFormatValueType(453) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 318 ) != m_toEnum.end() )
	{
		vgLogDebug("(318, SHADOW_MAPPING_36U) already in m_toEnum enum registry");
		assert( false && "(318, SHADOW_MAPPING_36U) already in registry" );
	}
	#endif

	m_toEnum[ 318 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(318) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 463 ) != m_toEnum.end() )
	{
		vgLogDebug("(463, ONCE) already in m_toEnum enum registry");
		assert( false && "(463, ONCE) already in registry" );
	}
	#endif

	m_toEnum[ 463 ] = vgd::makeShp( new vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType(463) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 282 ) != m_toEnum.end() )
	{
		vgLogDebug("(282, SMOOTH_HIDDEN_LINE) already in m_toEnum enum registry");
		assert( false && "(282, SMOOTH_HIDDEN_LINE) already in registry" );
	}
	#endif

	m_toEnum[ 282 ] = vgd::makeShp( new vgd::node::DrawStyle::ShapeValueType(282) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 324 ) != m_toEnum.end() )
	{
		vgLogDebug("(324, SHADOW_MAPPING_225U) already in m_toEnum enum registry");
		assert( false && "(324, SHADOW_MAPPING_225U) already in registry" );
	}
	#endif

	m_toEnum[ 324 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(324) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 315 ) != m_toEnum.end() )
	{
		vgLogDebug("(315, SHADOW_MAPPING_16UM) already in m_toEnum enum registry");
		assert( false && "(315, SHADOW_MAPPING_16UM) already in registry" );
	}
	#endif

	m_toEnum[ 315 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(315) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 269 ) != m_toEnum.end() )
	{
		vgLogDebug("(269, FRONT_AND_BACK) already in m_toEnum enum registry");
		assert( false && "(269, FRONT_AND_BACK) already in registry" );
	}
	#endif

	m_toEnum[ 269 ] = vgd::makeShp( new vgd::node::CullFace::ModeValueType(269) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 325 ) != m_toEnum.end() )
	{
		vgLogDebug("(325, SHADOW_MAPPING_225UM) already in m_toEnum enum registry");
		assert( false && "(325, SHADOW_MAPPING_225UM) already in registry" );
	}
	#endif

	m_toEnum[ 325 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(325) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 304 ) != m_toEnum.end() )
	{
		vgLogDebug("(304, STANDARD_PER_PIXEL) already in m_toEnum enum registry");
		assert( false && "(304, STANDARD_PER_PIXEL) already in registry" );
	}
	#endif

	m_toEnum[ 304 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(304) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 406 ) != m_toEnum.end() )
	{
		vgLogDebug("(406, INPUT2_OUTPUT_BUFFER3) already in m_toEnum enum registry");
		assert( false && "(406, INPUT2_OUTPUT_BUFFER3) already in registry" );
	}
	#endif

	m_toEnum[ 406 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(406) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 401 ) != m_toEnum.end() )
	{
		vgLogDebug("(401, INPUT1_PREVIOUS0) already in m_toEnum enum registry");
		assert( false && "(401, INPUT1_PREVIOUS0) already in registry" );
	}
	#endif

	m_toEnum[ 401 ] = vgd::makeShp( new vgd::node::PostProcessing::Input1ValueType(401) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 408 ) != m_toEnum.end() )
	{
		vgLogDebug("(408, INPUT2_OUTPUT_BUFFER5) already in m_toEnum enum registry");
		assert( false && "(408, INPUT2_OUTPUT_BUFFER5) already in registry" );
	}
	#endif

	m_toEnum[ 408 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(408) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 407 ) != m_toEnum.end() )
	{
		vgLogDebug("(407, INPUT2_OUTPUT_BUFFER4) already in m_toEnum enum registry");
		assert( false && "(407, INPUT2_OUTPUT_BUFFER4) already in registry" );
	}
	#endif

	m_toEnum[ 407 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(407) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 410 ) != m_toEnum.end() )
	{
		vgLogDebug("(410, INPUT2_OUTPUT_BUFFER7) already in m_toEnum enum registry");
		assert( false && "(410, INPUT2_OUTPUT_BUFFER7) already in registry" );
	}
	#endif

	m_toEnum[ 410 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(410) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 409 ) != m_toEnum.end() )
	{
		vgLogDebug("(409, INPUT2_OUTPUT_BUFFER6) already in m_toEnum enum registry");
		assert( false && "(409, INPUT2_OUTPUT_BUFFER6) already in registry" );
	}
	#endif

	m_toEnum[ 409 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(409) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 462 ) != m_toEnum.end() )
	{
		vgLogDebug("(462, AUTOMATIC) already in m_toEnum enum registry");
		assert( false && "(462, AUTOMATIC) already in registry" );
	}
	#endif

	m_toEnum[ 462 ] = vgd::makeShp( new vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType(462) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 373 ) != m_toEnum.end() )
	{
		vgLogDebug("(373, NO_FILTER) already in m_toEnum enum registry");
		assert( false && "(373, NO_FILTER) already in registry" );
	}
	#endif

	m_toEnum[ 373 ] = vgd::makeShp( new vgd::node::PostProcessing::FilterValueType(373) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 336 ) != m_toEnum.end() )
	{
		vgLogDebug("(336, SCALE_FACTOR) already in m_toEnum enum registry");
		assert( false && "(336, SCALE_FACTOR) already in registry" );
	}
	#endif

	m_toEnum[ 336 ] = vgd::makeShp( new vgd::node::OutputBufferProperty::SizeSemanticValueType(336) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 327 ) != m_toEnum.end() )
	{
		vgLogDebug("(327, SHADOW_MAPPING_256UM) already in m_toEnum enum registry");
		assert( false && "(327, SHADOW_MAPPING_256UM) already in registry" );
	}
	#endif

	m_toEnum[ 327 ] = vgd::makeShp( new vgd::node::LightModel::ShadowValueType(327) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 303 ) != m_toEnum.end() )
	{
		vgLogDebug("(303, STANDARD_PER_VERTEX) already in m_toEnum enum registry");
		assert( false && "(303, STANDARD_PER_VERTEX) already in registry" );
	}
	#endif

	m_toEnum[ 303 ] = vgd::makeShp( new vgd::node::LightModel::ModelValueType(303) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 413 ) != m_toEnum.end() )
	{
		vgLogDebug("(413, INPUT2_NONE) already in m_toEnum enum registry");
		assert( false && "(413, INPUT2_NONE) already in registry" );
	}
	#endif

	m_toEnum[ 413 ] = vgd::makeShp( new vgd::node::PostProcessing::Input2ValueType(413) );

	//
	#ifdef _DEBUG
	if ( m_toEnum.find( 272 ) != m_toEnum.end() )
	{
		vgLogDebug("(272, NONE) already in m_toEnum enum registry");
		assert( false && "(272, NONE) already in registry" );
	}
	#endif

	m_toEnum[ 272 ] = vgd::makeShp( new vgd::node::Displacement::PredefinedDisplacementValueType(272) );

}



} // namespace node

} // namespace vgd
