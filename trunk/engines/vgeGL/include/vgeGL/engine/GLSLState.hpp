// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_GLSLSTATE_HPP
#define _VGEGL_ENGINE_GLSLSTATE_HPP

#include <bitset>
#include <vector>
#include <vgd/Shp.hpp>
#include <vgd/node/TessellationProperties.hpp>
#include <vgd/node/LightModel.hpp>
#include <vge/basic/TUnitContainer.hpp>
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
		struct Decal;
		struct Light;
		struct OutputBufferProperty;
		struct Overlay;
		struct Program;
		struct PostProcessing;
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
	const bool isDisabled( const uint index ) const;
	void setEnabled( const uint index, const bool enabled = true );
	void setDisabled( const uint index );

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
const bool TBitSet<size>::isDisabled( const uint index ) const
{
	assert( index >= 0 && "Out of range index." );
	assert( index < size && "Out of range index." );

	return !m_bitset[ index ];
}


template< uint size >
void TBitSet<size>::setEnabled( const uint index, const bool enabled )
{
	assert( index >= 0 && "Out of range index." );
	assert( index < size && "Out of range index." );

	m_bitset[ index ] = enabled;
}


template< uint size >
void TBitSet<size>::setDisabled( const uint index )
{
	setEnabled( index, false );
}


template< uint size >
void TBitSet<size>::reset()
{
	m_bitset.reset();
}


/**
 * @brief Index for GLSLState bitset
 */
enum GLSLStateIndex
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
	CLIPPING_PLANE,				///< True when at least one ClipPlane node has been traversed

	// DrawStyle node
	FLAT_SHADING,				///< True when DrawStyle.shape implies a flat shading (instead of smooth shading)

	// PointStyle node
	POINT_STYLE,				///< True when at least one PointStyle node has been traversed

	// Program node
	PROGRAM,					///< True when at least one Program node has been traversed

	// VertexShape node
	COLOR4_BIND_PER_VERTEX,

	// PostProcessing
	IGNORE_POST_PROCESSING,		///< see LightModel.ignorePostProcessing

	//
	BUMP_MAPPING,				///< see LightModel.bumpMapping

	TESSELLATION,				///< tessellation is enabled. Tessellation method ? see GLSLState::get/setTessellation()
	TESSELLATION_LEVEL,			///< a tessellation level node has been encountered (useful to add only once uniform variables. See handler).

	DISPLACEMENT,

	GEOMORPH,					///< enable (during down traversing of scene graph)/disable (during up traversing) by GeoMorph node handler

	//
	MAX_BITSETINDEXTYPE
};


/**
 * @brief Light unit state
 */
struct LightState
{
	/**
	 * @brief Constructor
	 *
	 * @todo default value from Node @todo improves Node api
	 */
	LightState( const int type )
	:	//m_modelViewMatrix,

		m_on(false),
		m_castShadow(false),

		//m_position

		m_cutOffAngle(90.f),
		//m_direction

		m_type(type)
	{
		assert( m_type == DIRECTIONAL_LIGHT || m_type == POINT_LIGHT || m_type == SPOT_LIGHT );

		m_modelViewMatrix.setInvalid();
		m_position.setInvalid();
		m_direction.setInvalid();
	}

	//
	void setModelViewMatrix( const vgm::MatrixR& matrix ) 	{ m_modelViewMatrix = matrix; }
	const vgm::MatrixR& getModelViewMatrix() const			{ return m_modelViewMatrix; }


	// Light
	void setOn( const bool on )								{ m_on = on; }
	const bool getOn() const								{ return m_on; }

	void setCastShadow( const bool castShadow )				{ m_castShadow = castShadow; }
	const bool getCastShadow() const						{ return m_castShadow; }

	// vgm::Vec4f	ambient;
	// vgm::Vec4f	diffuse;
	// vgm::Vec4f	specular;

	// // PointLight
	void setPosition( const vgm::Vec3f& position )			{ m_position = position; }
	const vgm::Vec3f& getPosition() const					{ return m_position; }

	// // SpotLight
	void setCutOffAngle( const float cutOffAngle )			{ m_cutOffAngle = cutOffAngle; }
	const float getCutOffAngle() const						{ return m_cutOffAngle; }

	// float		dropOffRate;

	// // SpotLight-DirectionalLight
	void setDirection( const vgm::Vec3f& direction )		{ m_direction = direction; }
	const vgm::Vec3f& getDirection() const					{ return m_direction; }

	/**
	 * @brief Returns the light type
	 */
	const int getLightType() const							{ return m_type; }
	void setLightType( const int lightType )				{ m_type = lightType; }


private:
	vgm::MatrixR		m_modelViewMatrix;

	bool				m_on;
	bool				m_castShadow;

	vgm::Vec3f			m_position;
	
	float				m_cutOffAngle;
	vgm::Vec3f			m_direction;

	int					m_type;
};


/**
 * @brief GLSL rendering state
 *
 * This class is a specialized container for GLSL rendering state used by program/shader generators 
 * to take care of the rendering state given by the scene graph.
 */
struct GLSLState : public TBitSet< MAX_BITSETINDEXTYPE >
{
	/**
	 * @brief Returns the string representation of the given BitSetIndexType value.
	 *
	 * @pre bitSetIndexType >= 0 and bitSetIndexType < MAX_BITSETINDEXTYPE
	 */
	static const std::string& toString( const GLSLStateIndex bitSetIndexType );



	/**
	 * @brief Default constructor
	 *
	 * @param maxTexUnits					the maximum number of texture units
	 */
	GLSLState( const uint maxTexUnits = 0 );

	/**
	 * @brief Copy constructor
	 */
	GLSLState( const GLSLState& src );

	/**
	 * @brief Assign operator
	 */
	GLSLState& operator = ( const GLSLState& src );

	/**
	 * @brief Resets to the default state.
	 */
	void resetToDefault();


	/**
	 * @name TBitSet
	 */
	//{@
	void setEnabled( const uint index, const bool enabled = true );
	void reset();
	//@}


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
	 * @name Dirty flag accessors
	 */
	//@{

	/**
	 * @brief Test this flag.
	 *
	 * @return true if this flag is dirty, false otherwise.
	 */
	const bool	isDirty() const;

	/**
	 * @brief Test this flag.
	 *
	 * @return true if this flag is valid, false otherwise.
	 */
	const bool	isValid() const;

	/**
	 * @brief Set this flag to valid or dirty.
	 * 
	 * @param setToValid	true if this flag must be set to valid, false for invalidating(dirty) it.
	 */
	void		validate( const bool setToValid = true );

	//@}



	/**
	 * @name Light unit state
	 */
	//@{
	typedef vge::basic::TUnitContainer< LightState > LightStateContainer;	///< definition of light state container
	LightStateContainer lights;												///< array of light state. The zero-based index selects the light unit.
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

	typedef vge::basic::TUnitContainer< TexUnitState > TextureStateContainer;	///< definition of texture state container
	TextureStateContainer textures;												///< array of texture state. The zero-based index selects the texture unit.

	//@}



	/**
	 * @name Private texture unit accessors
	 */
	//@{
	 
	/**
	 * @brief Retrieves index of private texture unit.
	 *
	 * @param index		zero-based index to select private texture unit
	 *
	 * @return The index of the desired texture unit
	 *
	 * @remarks Private texture units are used internally by vgSDK and should not be used directly by user.
	 * @remarks Substract one to the first index to compute the index of the second private texture unit. And so on.
	 */
	const uint getPrivateTexUnitIndex( const uint index = 0 ) const;

	/**
	 * @brief Retrieves index of private texture unit.
	 *
	 * @param index		zero-based index to select private texture unit
	 *
	 * @return a string containing the index of the desired texture unit
	 */
	const std::string getPrivateTexUnit( const uint index = 0 ) const;

	/**
	 * @brief Inverse function of getPrivateTexUnitIndex()
	 *
	 * @param privateTexUnitIndex	index of a private texture unit
	 *
	 * @return the zero-based index.
	 */
	const uint getPrivateIndex( const uint privateTexUnitIndex = 0 );

	/**
	 * @brief Inverse function of getPrivateTexUnitIndex()
	 *
	 * @param privateTexUnitIndex	index of a private texture unit
	 *
	 * @return a string containing zero-based index.
	 */
	const std::string getPrivate( const uint privateTexUnitIndex = 0 );

	//@}



	/**
	 * @name Decal units
	 */
	//@{

	/**
	 * @brief Basic unit state structure containing a reference on a node
	 * @todo use everywhere this template class
	 */
	template< typename NodeType >
	struct TNodeState
	{
		/**
		 * @brief Default constructor
		 */
		TNodeState( NodeType * node )
		: m_node(node)
		{}

		const NodeType * getNode() const { return m_node; }
		NodeType * getNode() { return m_node; }
	private:
		NodeType * m_node;
	};

	struct DecalState : public TNodeState< vgd::node::Decal >
	{
		DecalState( vgd::node::Decal * node, const vgm::MatrixR& matrix )
		:	TNodeState(node),
			m_matrix( matrix )
		{}

		const vgm::MatrixR& getGeometricalMatrix() const		{ return m_matrix; }

	private:
		const vgm::MatrixR m_matrix;
	};

	/**
	 * @brief Post-processing unit container
	 */
	typedef vge::basic::TUnitContainer< DecalState > DecalStateContainer;
	DecalStateContainer decals;												///< array of decal state. The zero-based index selects the post-processing unit.

	//@}


	/**
	 * @name Post-processing units
	 */
	//@{

	/**
	 * @brief Post-processing unit state structure
	 */
	struct PostProcessingState
	{
		/**
		 * @brief Default constructor
		 */
		PostProcessingState( vgd::node::PostProcessing * node )
		: m_node(node)
		{}

		vgd::node::PostProcessing * getNode() const { return m_node; }

	private:
		vgd::node::PostProcessing * m_node;
	};

	/**
	 * @brief Post-processing unit container
	 */
	typedef vge::basic::TUnitContainer< PostProcessingState > PostProcessingStateContainer;
	PostProcessingStateContainer postProcessing;												///< array of post-processing state. The zero-based index selects the post-processing unit.

	//@}



	/**
	 * @name OutputBufferProperty units
	 */
	//@{
	 
	/**
	 * @brief OutputBufferProperty unit state structure
	 */
	struct OutputBufferPropertyState : public TNodeState< vgd::node::OutputBufferProperty >
	{
		/**
		 * @brief Default constructor
		 */
		OutputBufferPropertyState( vgd::node::OutputBufferProperty * node )
		:	TNodeState(node)
		{}
	};

	/**
	 * @brief OutputBufferProperty unit container
	 */
	typedef vge::basic::TUnitContainer< OutputBufferPropertyState > OutputBufferPropertyStateContainer;
	OutputBufferPropertyStateContainer outputBufferProperties;				///< array of output buffer state. The zero-based index selects the output buffer property unit.

	//@}


	/**
	 * @name Overlay units
	 */
	//@{
	 
	/**
	 * @brief Overlay unit state structure
	 */
	struct OverlayState
	{
		/**
		 * @brief Default constructor
		 */
		OverlayState( vgd::node::Overlay * node )
		: m_node(node)
		{}

		vgd::node::Overlay * getNode() const { return m_node; }

	private:
		vgd::node::Overlay * m_node;
	};

	/**
	 * @brief Overlay unit container
	 */
	typedef vge::basic::TUnitContainer< OverlayState > OverlayStateContainer;
	OverlayStateContainer overlays;												///< array of overlay state. The zero-based index selects the overlay unit.

	//@}


	/**
	 * @brief Returns the last encountered Program node
	 */
	vgd::node::Program * getProgram() const;

	/**
	 * @brief Sets the last encountered Program node
	 *
	 * @param node		reference on the Program node
	 */
	void setProgram( vgd::node::Program * program );



	/**
	 * @name Shader generation accessors
	 */
	//@{

// @todo rename VERTEX_ => VS_, TESSELLATIONCONTROL_ => TCS_ ...
	enum ShaderStage
	{
		UNIFORM_DECLARATIONS = 0,
		USER_DEFINED_UNIFORM_DECLARATIONS,

		// VERTEX SHADER
		VERTEX_DECLARATIONS,

		VERTEX_POSITION_DISPLACEMENT,
		VERTEX_POSITION_COMPUTATION,		///< vertex displacement (using a texture a procedurally)
		VERTEX_GL_POSITION_COMPUTATION,
		VERTEX_ECPOSITION_COMPUTATION,

		VERTEX_NORMAL_COMPUTATION,
		VERTEX_ECNORMAL_COMPUTATION,


		// TESSELLATION CONTROL SHADER
		TCS_DECLARATIONS,
// @todo TCS_MAIN_COMPUTATION
		TCS_TESSLEVEL_COMPUTATION,


		// TESSELLATION EVALUATION SHADER
		TES_DECLARATIONS,
// @todo TES_MAIN_COMPUTATION
		TES_POSITION_DISPLACEMENT,


		// FRAGMENT SHADER
		FRAGMENT_DECLARATIONS,

		FRAGMENT_OUTPUT_DECLARATION,		///< Declarations needed by FRAGMENT_OUTPUT
		FRAGMENT_OUTPUT,					///< Fragment Shader Outputs stage (example: gl_FragData[1] = ...)

		MAX_SHADERSTAGE
	};

	/**
	 * @brief Sets the glsl code for a specific stage.
	 *
	 * @param shaderStage	selector of the stage
	 * @param glslCode		code to insert in the desired shader
	 */
	void setShaderStage( const ShaderStage shaderStage, const std::string& glslCode );

	/**
	 * @brief Prepends the given glsl code for a specific stage.
	 *
	 * @param shaderStage	selector of the stage
	 * @param glslCode		code to prepend in the desired shader
	 */
	void prependShaderStage( const ShaderStage shaderStage, const std::string& glslCode );

	/**
	 * @brief Appends the given glsl code for a specific stage.
	 *
	 * @param shaderStage	selector of the stage
	 * @param glslCode		code to append in the desired shader
	 */
	void appendShaderStage( const ShaderStage shaderStage, const std::string& glslCode );

	/**
	 * @brief Sets the default glsl code for a specific stage.
	 *
	 * @param shaderStage	selector of the stage
	 */
	void resetShaderStage( const ShaderStage shaderStage );

	/**
	 * @brief Sets the default glsl code for all shader stages.
	 */
	void resetShaderStages();

	/**
	 * @brief Returns the glsl code for a specific stage.
	 *
	 * @param shaderStage	selector of the stage
	 * @param withMarker	true to add marker around the shader stage code, false to retrieve only the glsl code for the specified stage
	 *
	 * @return code to insert in the desired shader or an empty string.
	 */
#ifdef _DEBUG
	const std::string getShaderStage( const ShaderStage shaderStage, const bool withMarker = true ) const;
#else
	const std::string getShaderStage( const ShaderStage shaderStage, const bool withMarker = false ) const;
#endif

	//@}


	/**
	 * @name Bump mapping accessors
	 */
	//@{
	const bool isBumpMappingEnabled() const;
	void setBumpMappingEnabled( const bool enabled = true );
	//@}

	/**
	 * @name Tessellation accessors
	 */
	//@{
	const bool isTessellationEnabled() const;
	void setTessellationEnabled( const bool enabled = true );


	typedef vgd::node::TessellationProperties::TessellationValueType TessellationValueType;
	const TessellationValueType getTessellation() const;
	void setTessellation( const TessellationValueType value );
	//@}


	/**
	 * @name Shadow accessors
	 */
	//@{
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

	// @todo not here, because don't change generated shaders
	const vgd::node::LightModel::ShadowMapTypeValueType getShadowMapType() const		{ return m_shadowMapType; }
	void setShadowMapType( const vgd::node::LightModel::ShadowMapTypeValueType type )	{ m_shadowMapType = type; }
	//@}


private:
	void copy( const GLSLState& src );
	void release();

	vgd::field::DirtyFlag								m_dirtyFlag;			///< internal dirty flag to catch any modification

	void init();
	vgd::node::Program *								m_program;					///< the last encountered Program node
	// @todo TUnitContainer m_shaderStage;
	std::vector< std::string >							m_shaderStage;				///< container of glsl code for custom shader stage

	TessellationValueType								m_tessellation;				///< EngineProperties.tessellation
	vgd::node::LightModel::ShadowValueType				m_lightModelShadow;			///< Last encountered value of LightModel.shadow field
	vgd::node::LightModel::ShadowMapTypeValueType		m_shadowMapType;			///< @todo doc
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_GLSLSTATE_HPP
