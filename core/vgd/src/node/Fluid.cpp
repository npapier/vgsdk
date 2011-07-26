// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Fluid.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Fluid > Fluid::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Fluid > node( new Fluid(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Fluid > Fluid::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Fluid > node = Fluid::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Fluid > Fluid::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Fluid > node = Fluid::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Fluid::Fluid( const std::string nodeName ) :
	vgd::node::Shape( nodeName )
{
	// Adds field(s)
	addField( new FEmittersOrDrainersType(getFEmittersOrDrainers()) );
	addField( new FHeightMapSizeType(getFHeightMapSize()) );
	addField( new FGravityType(getFGravity()) );
	addField( new FSimulationPass1Type(getFSimulationPass1()) );
	addField( new FSimulationPass0Type(getFSimulationPass0()) );
	addField( new FSceneType(getFScene()) );

	// Sets link(s)

	link( getDFNode() );
}



void Fluid::setToDefaults( void )
{
	Shape::setToDefaults();
	setHeightMapSize( vgm::Vec2i(256, 256) );
	setGravity( vgm::Vec4f(0.f, -1.f, 0.f, 9.8f) );



}



void Fluid::setOptionalsToDefaults()
{
	Shape::setOptionalsToDefaults();
}



// EmittersOrDrainers
vgd::field::EditorRO< Fluid::FEmittersOrDrainersType > Fluid::getEmittersOrDrainersRO() const
{
	return getFieldRO<FEmittersOrDrainersType>( getFEmittersOrDrainers() );
}



vgd::field::EditorRW< Fluid::FEmittersOrDrainersType > Fluid::getEmittersOrDrainersRW()
{
	return getFieldRW<FEmittersOrDrainersType>( getFEmittersOrDrainers() );
}



// HeightMapSize
const Fluid::HeightMapSizeValueType Fluid::getHeightMapSize() const
{
	return getFieldRO<FHeightMapSizeType>(getFHeightMapSize())->getValue();
}



void Fluid::setHeightMapSize( const HeightMapSizeValueType value )
{
	getFieldRW<FHeightMapSizeType>(getFHeightMapSize())->setValue( value );
}



// Gravity
const Fluid::GravityValueType Fluid::getGravity() const
{
	return getFieldRO<FGravityType>(getFGravity())->getValue();
}



void Fluid::setGravity( const GravityValueType value )
{
	getFieldRW<FGravityType>(getFGravity())->setValue( value );
}



// SimulationPass1
const Fluid::SimulationPass1ValueType Fluid::getSimulationPass1() const
{
	return getFieldRO<FSimulationPass1Type>(getFSimulationPass1())->getValue();
}



void Fluid::setSimulationPass1( const SimulationPass1ValueType value )
{
	getFieldRW<FSimulationPass1Type>(getFSimulationPass1())->setValue( value );
}



// SimulationPass0
const Fluid::SimulationPass0ValueType Fluid::getSimulationPass0() const
{
	return getFieldRO<FSimulationPass0Type>(getFSimulationPass0())->getValue();
}



void Fluid::setSimulationPass0( const SimulationPass0ValueType value )
{
	getFieldRW<FSimulationPass0Type>(getFSimulationPass0())->setValue( value );
}



// Scene
const Fluid::SceneValueType Fluid::getScene() const
{
	return getFieldRO<FSceneType>(getFScene())->getValue();
}



void Fluid::setScene( const SceneValueType value )
{
	getFieldRW<FSceneType>(getFScene())->setValue( value );
}



// Field name accessor(s)
const std::string Fluid::getFEmittersOrDrainers( void )
{
	return "f_emittersOrDrainers";
}



const std::string Fluid::getFHeightMapSize( void )
{
	return "f_heightMapSize";
}



const std::string Fluid::getFGravity( void )
{
	return "f_gravity";
}



const std::string Fluid::getFSimulationPass1( void )
{
	return "f_simulationPass1";
}



const std::string Fluid::getFSimulationPass0( void )
{
	return "f_simulationPass0";
}



const std::string Fluid::getFScene( void )
{
	return "f_scene";
}



bool Fluid::computeBoundingBox( const vgm::MatrixR& transformation )
{
	return true;
}



bool Fluid::isBoundingBoxValid() const
{
	return true;
}



void Fluid::invalidateBoundingBox( bool /*bInvalidate*/ )
{
}



void Fluid::sethSimulationPassToDefault()
{
	setSimulationPass0(
			"// OUTPUT BUFFER 0 : scene position map\n"
			"// OUTPUT BUFFER 1 : fluid height map\n"
			"// OUTPUT BUFFER 2 : output flow texture\n"
			"// OUTPUT BUFFER 3 : new fluid height map\n"
			"// OUTPUT BUFFER 4 : fluid position map (scene position map + fluid HM)\n"
			"// OUTPUT BUFFER 5 : fluid normal map\n"
			"// OUTPUT BUFFER 6 : previous output flow texture\n"
			"\n"
			"// PASS0 : compute output flow texture(2) from (0) & (1) & (6)\n"
			"vec4 apply(	sampler2D scenePositionMap, sampler2D fluidHM, sampler2D previousOutflow, vec2 texCoord,\n"
			"				vec4 param0, float damping )\n"
			"{\n"
			"	float cellSize	= param0.x;\n"
			//"	const float cellSize	= 1.0;\n"
			"	float css			= param0.y;\n"
			//"	const float css			= 1.0;\n"
			"	float gravity		= param0.z;\n"
			//"	const float gravity		= 10.0;\n"
			"	float timeStep	= param0.w;\n"
			//"	const float timeStep	= 0.1;\n"
			//"	const float damping		= 0.999;\n"
			//"	const float damping		= 0.4;\n"
			"\n"
			"	vec2 left	= vec2(-1.0, 0.0);\n"
			"	vec2 right	= vec2(1.0, 0.0);\n"
			"	vec2 top	= vec2(0.0, 1.0);\n"
			"	vec2 bottom	= vec2(0.0, -1.0);\n"
			"\n"
			"	vec2 scenePositionMapSize = textureSize( scenePositionMap, 0 );\n"
			"	vec4 scenePositionC	= texture( scenePositionMap, texCoord );\n"
			"	if ( (scenePositionC.x == 0.0) && (scenePositionC.y == 0.0) && (scenePositionC.z == 0.0) )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	vec4 scenePositionL	= texture( scenePositionMap, texCoord + left/scenePositionMapSize );\n"
			"	if ( (scenePositionL.x == 0.0) && (scenePositionL.y == 0.0) && (scenePositionL.z == 0.0) )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	vec4 scenePositionR	= texture( scenePositionMap, texCoord + right/scenePositionMapSize );\n"
			"	if ( (scenePositionR.x == 0.0) && (scenePositionR.y == 0.0) && (scenePositionR.z == 0.0) )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	vec4 scenePositionT	= texture( scenePositionMap, texCoord + top/scenePositionMapSize );\n"
			"	if ( (scenePositionT.x == 0.0) && (scenePositionT.y == 0.0) && (scenePositionT.z == 0.0) )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	vec4 scenePositionB	= texture( scenePositionMap, texCoord + bottom/scenePositionMapSize );\n"
			"	if ( (scenePositionB.x == 0.0) && (scenePositionB.y == 0.0) && (scenePositionB.z == 0.0) )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	vec4 scenePosition	= vec4( scenePositionL.z, scenePositionR.z, scenePositionT.z, scenePositionB.z );\n"
			"\n"
			"	vec2	fluidHMSize = textureSize( fluidHM, 0 );\n"
			"	float	fluidHeightC	= texture( fluidHM, texCoord ).x;\n"
			"//	if ( fluidHeightC == 0.0 )\n"
			"//	{"
			"//		return vec4(0.0);\n"
			"//	}\n"
			"	float	fluidHeightL	= texture( fluidHM, texCoord + left/fluidHMSize ).x;\n"
			"	float	fluidHeightR	= texture( fluidHM, texCoord + right/fluidHMSize ).x;\n"
			"	float	fluidHeightT	= texture( fluidHM, texCoord + top/fluidHMSize ).x;\n"
			"	float	fluidHeightB	= texture( fluidHM, texCoord + bottom/fluidHMSize ).x;\n"
			"	vec4	fluidHeight		= vec4( fluidHeightL, fluidHeightR, fluidHeightT, fluidHeightB );\n"
			"\n"
			"	float	totalHC = scenePositionC.z + fluidHeightC;\n"
			"	vec4	totalH	= scenePosition + fluidHeight;\n"
			"	vec4	heightDiff	= vec4(totalHC) - totalH;\n"
			"\n"
			"//	vec4	stepHD = step(1.0/256.0, heightDiff);\n"
			"//	heightDiff *= stepHD;\n"
			"\n"
			"	vec4	oldOutflow = texture( previousOutflow, texCoord );\n"
			"	vec4	accel		= gravity * heightDiff / cellSize;\n"
			"	vec4	outflow		= damping * oldOutflow + timeStep * css * accel;\n"
			"	outflow = max( vec4(0.0), outflow );\n"
			"\n"
			"	float maxFluid = cellSize*cellSize * fluidHeightC;\n"
			"	float fluidOut = (outflow.x + outflow.y + outflow.z + outflow.w ) * timeStep;\n"
			"	if ( fluidOut == 0.0 )\n"
			"	{\n"
			"		outflow = vec4(0);\n"
			"	}\n"
			"	else\n"
			"	{\n"
			"		float fluidScaleFactor = maxFluid / fluidOut;\n"
			"		if ( fluidScaleFactor < 1.0 )\n"
			"		{\n"
			"			outflow *= fluidScaleFactor;\n"
			"		}\n"
			"	}\n"
			"	return outflow;\n"



			"\n"
			"	//vec4	oldOutflow = texture( previousOutflow, texCoord );\n"
			"\n"
			"//	vec4 param = min(abs(heightDiff), (vec4(fluidHeightC) + fluidHeight)/2.0);\n"
			"//	vec4	outflow = damping * oldOutflow + clamp(0.1 * heightDiff * param, vec4(0), vec4(0.1) );\n"
			"//	outflow = max( vec4(0.0), outflow );\n"
			//"	vec4	outflow = damping * oldOutflow + min( heightDiff, vec4(16.0/256.0) );\n"
			"//	return clamp(heightDiff/8.0,vec4(0),vec4(2.));\n"
			//"	return clamp(heightDiff/8.0,vec4(0),vec4(1.));\n"
			//"	return outflow;\n"
			"\n"
			"}\n"
			"\n\n\n" );
/*	vec4	accel		= gravity * heightDiff / cellSize;

	vec4	oldOutflow = texture( previousOutflow, texCoord );
	vec4 outflow = damping * oldOutflow + accel;
	outflow = max( vec4(0.0), outflow );
	float maxFluid = 1*1*fluidHeightC;
	float fluidOut = (outflow.x + outflow.y + outflow.z + outflow.w ) * 1.0;
	if ( fluidOut == 0.0 )
	{
		outflow = vec4(0);
	}
	else
	{
		float fluidScaleFactor = maxFluid / fluidOut;
		if ( fluidScaleFactor < 1.0 )
		{
			outflow *= fluidScaleFactor;
		}
	}
	return clamp( outflow, vec4(0), vec4(2) );
//	vec4 param = min(abs(heightDiff), (vec4(fluidHeightC) + fluidHeight)/2.0);
	//vec4	outflow = damping * oldOutflow + clamp(0.1 * heightDiff * param, vec4(0), vec4(0.1) );

	//return clamp(heightDiff/8.0,vec4(0),vec4(1.));*/

	/*vec4 param = min( abs(heightDiff), (vec4(fluidHeightC) + fluidHeight)/3.0);
	vec4	oldOutflow = texture( previousOutflow, texCoord );
	vec4	outflow = damping * oldOutflow + clamp(0.1 * heightDiff * param, vec4(0), vec4(0.1) );
	outflow = max( vec4(0.0), outflow );
	return outflow;*/

	setSimulationPass1(
			"// OUTPUT BUFFER 0 : scene position map\n"
			"// OUTPUT BUFFER 1 : fluid height map\n"
			"// OUTPUT BUFFER 2 : output flow texture\n"
			"// OUTPUT BUFFER 3 : new fluid height map\n"
			"// OUTPUT BUFFER 4 : fluid position map (scene position map + fluid HM)\n"
			"// OUTPUT BUFFER 5 : fluid normal map\n"
			"// OUTPUT BUFFER 6 : previous output flow texture\n"
			"\n"
			"float computeFluidEmitterOrDrainer( vec3 scenePosition, vec4 fluidEmitterOrDrainer, float fluidEmitterOrDrainerIntensity )\n"
			"{\n"
			"	if ( fluidEmitterOrDrainerIntensity == 0 )\n"
			"	{\n"
			"		return 0;\n"
			"	}\n"
			"\n"
			"	vec3	emitterOrDrainerPosition	= fluidEmitterOrDrainer.xyz;\n"
			"	float	emitterOrDrainerRadius		= fluidEmitterOrDrainer.w;\n"
			"\n"
			"	if ( distance( scenePosition, emitterOrDrainerPosition ) < emitterOrDrainerRadius )\n"
			"	{\n"
			"		return fluidEmitterOrDrainerIntensity;\n" // @todo better function
			"	}\n"
			"	return 0;\n"
			"}\n"
			"\n"
			"// PASS1 : compute new fluid height texture(3) from (1) & (2)\n"
			"vec4 apply(	sampler2D scenePositionMap, sampler2D fluidHM, sampler2D outputFlowMap, vec2 texCoord,\n"
			"				mat4 emitterOrDrainer, vec4 emitterOrDrainerIntensity )\n"
			"{\n"
			"	const float timeStep	= 0.1;\n"
			"\n"
			"	vec2 left	= vec2(-1.0, 0.0);\n"
			"	vec2 right	= vec2(1.0, 0.0);\n"
			"	vec2 top	= vec2(0.0, 1.0);\n"
			"	vec2 bottom	= vec2(0.0, -1.0);\n"
			"\n"
			//"	vec2	fluidHMSize = textureSize( fluidHM, 0 );\n"
			"	float	fluidHeightC	= texture( fluidHM, texCoord ).x;\n"
			//"	float	fluidHeightL	= texture( fluidHM, texCoord + left/fluidHMSize ).x;\n"
			//"	float	fluidHeightR	= texture( fluidHM, texCoord + right/fluidHMSize ).x;\n"
			//"	float	fluidHeightT	= texture( fluidHM, texCoord + top/fluidHMSize ).x;\n"
			//"	float	fluidHeightB	= texture( fluidHM, texCoord + bottom/fluidHMSize ).x;\n"
			//"	vec4	fluidHeight		= vec4( fluidHeightL, fluidHeightR, fluidHeightT, fluidHeightB );\n"
			"\n"
			"	vec2 outputFlowMapSize = textureSize( outputFlowMap, 0 );\n"
			"	vec4 outputFlowC	= texture( outputFlowMap, texCoord );\n"
			"	vec4 outputFlowL	= texture( outputFlowMap, texCoord + left/outputFlowMapSize );\n"
			"	vec4 outputFlowR	= texture( outputFlowMap, texCoord + right/outputFlowMapSize );\n"
			"	vec4 outputFlowT	= texture( outputFlowMap, texCoord + top/outputFlowMapSize );\n"
			"	vec4 outputFlowB	= texture( outputFlowMap, texCoord + bottom/outputFlowMapSize );\n"
			"\n"
			"	float inflows	= outputFlowL.y + outputFlowR.x + outputFlowT.w + outputFlowB.z;\n"
			"	float outflows	= outputFlowC.x + outputFlowC.y + outputFlowC.z + outputFlowC.w;\n"
			"\n"
			"	vec4 scenePositionC = texture( scenePositionMap, texCoord );\n"
			"	// FLUID EMITTER or DRAINER\n"
			"	float emitOrDrainFluid = 0.0;\n"
			"\n"
			"	for( int i = 0; i < 4; ++i )\n"
			"	{\n"
			"		emitOrDrainFluid += computeFluidEmitterOrDrainer( scenePositionC.xyz, emitterOrDrainer[i], emitterOrDrainerIntensity[i] );\n"
			"	}\n"
			"\n"
			"	return vec4(fluidHeightC + (timeStep *(inflows - outflows + emitOrDrainFluid )) );\n"
			"}\n"
			"\n\n\n" );
}

IMPLEMENT_INDEXABLE_CLASS_CPP( , Fluid );



const vgd::basic::RegisterNode<Fluid> Fluid::m_registrationInstance;



} // namespace node

} // namespace vgd

