// VGSDK - Copyright (C) 2014, Nicolas Papier.
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
	addField( new FOpacityType(getFOpacity()) );
	addField( new FEmittersOrDrainersType(getFEmittersOrDrainers()) );
	addField( new FHeightMapSizeType(getFHeightMapSize()) );
	addField( new FSceneType(getFScene()) );
	addField( new FRequestFeedbackType(getFRequestFeedback()) );
	addField( new FGravityType(getFGravity()) );
	addField( new FSimulationPass1Type(getFSimulationPass1()) );
	addField( new FSimulationPass0Type(getFSimulationPass0()) );
	addField( new FCellSizeType(getFCellSize()) );
	addField( new FFeedbackInformationsBisType(getFFeedbackInformationsBis()) );
	addField( new FDampingType(getFDamping()) );
	addField( new FTimeStepType(getFTimeStep()) );
	addField( new FThicknessType(getFThickness()) );
	addField( new FFeedbackInformationsType(getFFeedbackInformations()) );
	addField( new FCssType(getFCss()) );
	addField( new FFluidPositionFeedbackType(getFFluidPositionFeedback()) );

	// Sets link(s)

	link( getDFNode() );
}



void Fluid::setToDefaults( void )
{
	Shape::setToDefaults();
	setOpacity( (0.6) );
	setHeightMapSize( vgm::Vec2i(256, 256) );
	setScene( vgd::node::NodeWkp() );
	setRequestFeedback( (false) );
	setGravity( vgm::Vec4f(0.f, -1.f, 0.f, 9.8f) );
	setSimulationPass1( std::string() );
	setSimulationPass0( std::string() );
	setCellSize( (1.0) );
	setFeedbackInformationsBis( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
	setDamping( (0.8) );
	setTimeStep( (0.1) );
	setThickness( (1.0) );
	setFeedbackInformations( vgm::Vec5f(0.f, 0.f, 0.f, 0.f, 0.f) );
	setCss( (1.0) );
	setFluidPositionFeedback( vgd::basic::IImageShp() );
}



void Fluid::setOptionalsToDefaults()
{
	Shape::setOptionalsToDefaults();
}



// Opacity

const Fluid::OpacityValueType Fluid::DEFAULT_OPACITY = (0.6);



const Fluid::OpacityValueType Fluid::getOpacity() const
{
	return getFieldRO<FOpacityType>(getFOpacity())->getValue();
}



void Fluid::setOpacity( const OpacityValueType value )
{
	getFieldRW<FOpacityType>(getFOpacity())->setValue( value );
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

const Fluid::HeightMapSizeValueType Fluid::DEFAULT_HEIGHTMAPSIZE = vgm::Vec2i(256, 256);



const Fluid::HeightMapSizeValueType Fluid::getHeightMapSize() const
{
	return getFieldRO<FHeightMapSizeType>(getFHeightMapSize())->getValue();
}



void Fluid::setHeightMapSize( const HeightMapSizeValueType value )
{
	getFieldRW<FHeightMapSizeType>(getFHeightMapSize())->setValue( value );
}



// Scene

const Fluid::SceneValueType Fluid::DEFAULT_SCENE = vgd::node::NodeWkp();



const Fluid::SceneValueType Fluid::getScene() const
{
	return getFieldRO<FSceneType>(getFScene())->getValue();
}



void Fluid::setScene( const SceneValueType value )
{
	getFieldRW<FSceneType>(getFScene())->setValue( value );
}



// RequestFeedback

const Fluid::RequestFeedbackValueType Fluid::DEFAULT_REQUESTFEEDBACK = (false);



const Fluid::RequestFeedbackValueType Fluid::getRequestFeedback() const
{
	return getFieldRO<FRequestFeedbackType>(getFRequestFeedback())->getValue();
}



void Fluid::setRequestFeedback( const RequestFeedbackValueType value )
{
	getFieldRW<FRequestFeedbackType>(getFRequestFeedback())->setValue( value );
}



// Gravity

const Fluid::GravityValueType Fluid::DEFAULT_GRAVITY = vgm::Vec4f(0.f, -1.f, 0.f, 9.8f);



const Fluid::GravityValueType Fluid::getGravity() const
{
	return getFieldRO<FGravityType>(getFGravity())->getValue();
}



void Fluid::setGravity( const GravityValueType value )
{
	getFieldRW<FGravityType>(getFGravity())->setValue( value );
}



// SimulationPass1

const Fluid::SimulationPass1ValueType Fluid::DEFAULT_SIMULATIONPASS1 = std::string();



const Fluid::SimulationPass1ValueType Fluid::getSimulationPass1() const
{
	return getFieldRO<FSimulationPass1Type>(getFSimulationPass1())->getValue();
}



void Fluid::setSimulationPass1( const SimulationPass1ValueType value )
{
	getFieldRW<FSimulationPass1Type>(getFSimulationPass1())->setValue( value );
}



// SimulationPass0

const Fluid::SimulationPass0ValueType Fluid::DEFAULT_SIMULATIONPASS0 = std::string();



const Fluid::SimulationPass0ValueType Fluid::getSimulationPass0() const
{
	return getFieldRO<FSimulationPass0Type>(getFSimulationPass0())->getValue();
}



void Fluid::setSimulationPass0( const SimulationPass0ValueType value )
{
	getFieldRW<FSimulationPass0Type>(getFSimulationPass0())->setValue( value );
}



// CellSize

const Fluid::CellSizeValueType Fluid::DEFAULT_CELLSIZE = (1.0);



const Fluid::CellSizeValueType Fluid::getCellSize() const
{
	return getFieldRO<FCellSizeType>(getFCellSize())->getValue();
}



void Fluid::setCellSize( const CellSizeValueType value )
{
	getFieldRW<FCellSizeType>(getFCellSize())->setValue( value );
}



// FeedbackInformationsBis

const Fluid::FeedbackInformationsBisValueType Fluid::DEFAULT_FEEDBACKINFORMATIONSBIS = vgm::MatrixR(vgm::MatrixR::getIdentity());



const Fluid::FeedbackInformationsBisValueType Fluid::getFeedbackInformationsBis() const
{
	return getFieldRO<FFeedbackInformationsBisType>(getFFeedbackInformationsBis())->getValue();
}



void Fluid::setFeedbackInformationsBis( const FeedbackInformationsBisValueType value )
{
	getFieldRW<FFeedbackInformationsBisType>(getFFeedbackInformationsBis())->setValue( value );
}



// Damping

const Fluid::DampingValueType Fluid::DEFAULT_DAMPING = (0.8);



const Fluid::DampingValueType Fluid::getDamping() const
{
	return getFieldRO<FDampingType>(getFDamping())->getValue();
}



void Fluid::setDamping( const DampingValueType value )
{
	getFieldRW<FDampingType>(getFDamping())->setValue( value );
}



// TimeStep

const Fluid::TimeStepValueType Fluid::DEFAULT_TIMESTEP = (0.1);



const Fluid::TimeStepValueType Fluid::getTimeStep() const
{
	return getFieldRO<FTimeStepType>(getFTimeStep())->getValue();
}



void Fluid::setTimeStep( const TimeStepValueType value )
{
	getFieldRW<FTimeStepType>(getFTimeStep())->setValue( value );
}



// Thickness

const Fluid::ThicknessValueType Fluid::DEFAULT_THICKNESS = (1.0);



const Fluid::ThicknessValueType Fluid::getThickness() const
{
	return getFieldRO<FThicknessType>(getFThickness())->getValue();
}



void Fluid::setThickness( const ThicknessValueType value )
{
	getFieldRW<FThicknessType>(getFThickness())->setValue( value );
}



// FeedbackInformations

const Fluid::FeedbackInformationsValueType Fluid::DEFAULT_FEEDBACKINFORMATIONS = vgm::Vec5f(0.f, 0.f, 0.f, 0.f, 0.f);



const Fluid::FeedbackInformationsValueType Fluid::getFeedbackInformations() const
{
	return getFieldRO<FFeedbackInformationsType>(getFFeedbackInformations())->getValue();
}



void Fluid::setFeedbackInformations( const FeedbackInformationsValueType value )
{
	getFieldRW<FFeedbackInformationsType>(getFFeedbackInformations())->setValue( value );
}



// Css

const Fluid::CssValueType Fluid::DEFAULT_CSS = (1.0);



const Fluid::CssValueType Fluid::getCss() const
{
	return getFieldRO<FCssType>(getFCss())->getValue();
}



void Fluid::setCss( const CssValueType value )
{
	getFieldRW<FCssType>(getFCss())->setValue( value );
}



// FluidPositionFeedback

const Fluid::FluidPositionFeedbackValueType Fluid::DEFAULT_FLUIDPOSITIONFEEDBACK = vgd::basic::IImageShp();



const Fluid::FluidPositionFeedbackValueType Fluid::getFluidPositionFeedback() const
{
	return getFieldRO<FFluidPositionFeedbackType>(getFFluidPositionFeedback())->getValue();
}



void Fluid::setFluidPositionFeedback( const FluidPositionFeedbackValueType value )
{
	getFieldRW<FFluidPositionFeedbackType>(getFFluidPositionFeedback())->setValue( value );
}



// Field name accessor(s)
const std::string Fluid::getFOpacity( void )
{
	return "f_opacity";
}



const std::string Fluid::getFEmittersOrDrainers( void )
{
	return "f_emittersOrDrainers";
}



const std::string Fluid::getFHeightMapSize( void )
{
	return "f_heightMapSize";
}



const std::string Fluid::getFScene( void )
{
	return "f_scene";
}



const std::string Fluid::getFRequestFeedback( void )
{
	return "f_requestFeedback";
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



const std::string Fluid::getFCellSize( void )
{
	return "f_cellSize";
}



const std::string Fluid::getFFeedbackInformationsBis( void )
{
	return "f_feedbackInformationsBis";
}



const std::string Fluid::getFDamping( void )
{
	return "f_damping";
}



const std::string Fluid::getFTimeStep( void )
{
	return "f_timeStep";
}



const std::string Fluid::getFThickness( void )
{
	return "f_thickness";
}



const std::string Fluid::getFFeedbackInformations( void )
{
	return "f_feedbackInformations";
}



const std::string Fluid::getFCss( void )
{
	return "f_css";
}



const std::string Fluid::getFFluidPositionFeedback( void )
{
	return "f_fluidPositionFeedback";
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
			"	float css		= param0.y;\n"
			"	float gravity	= param0.z;\n"
			"	float timeStep	= param0.w;\n"
			"\n"
			"	vec2 left	= vec2(-1.0, 0.0);\n"
			"	vec2 right	= vec2(1.0, 0.0);\n"
			"	vec2 top	= vec2(0.0, 1.0);\n"
			"	vec2 bottom	= vec2(0.0, -1.0);\n"
			"\n"
			"	vec2 scenePositionMapSize = textureSize( scenePositionMap, 0 );\n"

			"	float scenePositionC	= texture( scenePositionMap, texCoord ).z;\n"
			"	if ( scenePositionC == 0.0 )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	float scenePositionL	= texture( scenePositionMap, texCoord + left/scenePositionMapSize ).z;\n"
			"	if ( scenePositionL == 0.0 )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	float scenePositionR	= texture( scenePositionMap, texCoord + right/scenePositionMapSize ).z;\n"
			"	if ( scenePositionR == 0.0 )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	float scenePositionT	= texture( scenePositionMap, texCoord + top/scenePositionMapSize ).z;\n"
			"	if ( scenePositionT == 0.0 )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	float scenePositionB	= texture( scenePositionMap, texCoord + bottom/scenePositionMapSize ).z;\n"
			"	if ( scenePositionB == 0.0 )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"

			// "	vec4 scenePositionC	= texture( scenePositionMap, texCoord );\n"
			// "	if ( /*(scenePositionC.x == 0.0) && (scenePositionC.y == 0.0) && */(scenePositionC.z == 0.0) )\n"
			// "	{\n"
			// "		return vec4(0.0);\n"
			// "	}\n"
			// "	vec4 scenePositionL	= texture( scenePositionMap, texCoord + left/scenePositionMapSize );\n"
			// "	if ( /*(scenePositionL.x == 0.0) && (scenePositionL.y == 0.0) && */(scenePositionL.z == 0.0) )\n"
			// "	{\n"
			// "		return vec4(0.0);\n"
			// "	}\n"
			// "	vec4 scenePositionR	= texture( scenePositionMap, texCoord + right/scenePositionMapSize );\n"
			// "	if ( /*(scenePositionR.x == 0.0) && (scenePositionR.y == 0.0) && */(scenePositionR.z == 0.0) )\n"
			// "	{\n"
			// "		return vec4(0.0);\n"
			// "	}\n"
			// "	vec4 scenePositionT	= texture( scenePositionMap, texCoord + top/scenePositionMapSize );\n"
			// "	if ( /*(scenePositionT.x == 0.0) && (scenePositionT.y == 0.0) && */(scenePositionT.z == 0.0) )\n"
			// "	{\n"
			// "		return vec4(0.0);\n"
			// "	}\n"
			// "	vec4 scenePositionB	= texture( scenePositionMap, texCoord + bottom/scenePositionMapSize );\n"
			// "	if ( /*(scenePositionB.x == 0.0) && (scenePositionB.y == 0.0) && */(scenePositionB.z == 0.0) )\n"
			// "	{\n"
			// "		return vec4(0.0);\n"
			// "	}\n"

//			"	vec4 scenePosition	= vec4( scenePositionL.z, scenePositionR.z, scenePositionT.z, scenePositionB.z );\n"
			"	vec4 scenePosition	= vec4( scenePositionL, scenePositionR, scenePositionT, scenePositionB );\n"
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
//			"	float	totalHC = scenePositionC.z + fluidHeightC;\n"
			"	float	totalHC = scenePositionC + fluidHeightC;\n"
			"	vec4	totalH	= scenePosition + fluidHeight;\n"
			"	vec4	heightDiff	= vec4(totalHC) - totalH;\n"
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
			"}\n"
			"\n\n\n" );

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
//			"	if ( fluidEmitterOrDrainerIntensity == 0 )\n"
//			"	{\n"
//			"		return 0.0;\n"
//			"	}\n"
			"\n"
			"	vec3	emitterOrDrainerPosition	= fluidEmitterOrDrainer.xyz;\n"
			"	float	emitterOrDrainerRadius		= fluidEmitterOrDrainer.w;\n"
			"\n"
			"	if ( distance( scenePosition, emitterOrDrainerPosition ) < emitterOrDrainerRadius )\n"
			"	{\n"
			"		return fluidEmitterOrDrainerIntensity;\n" // @todo better function
			"	}\n"
			"	return 0.0;\n"
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

			/*"	vec4 outputFlowL	= texture( outputFlowMap, texCoord + left/outputFlowMapSize );\n"
			"	vec4 outputFlowR	= texture( outputFlowMap, texCoord + right/outputFlowMapSize );\n"
			"	vec4 outputFlowT	= texture( outputFlowMap, texCoord + top/outputFlowMapSize );\n"
			"	vec4 outputFlowB	= texture( outputFlowMap, texCoord + bottom/outputFlowMapSize );\n"*/

			"	float outputFlowL	= texture( outputFlowMap, texCoord + left/outputFlowMapSize ).y;\n"
			"	float outputFlowR	= texture( outputFlowMap, texCoord + right/outputFlowMapSize ).x;\n"
			"	float outputFlowT	= texture( outputFlowMap, texCoord + top/outputFlowMapSize ).w;\n"
			"	float outputFlowB	= texture( outputFlowMap, texCoord + bottom/outputFlowMapSize ).z;\n"

			"\n"
//			"	float inflows	= outputFlowL.y + outputFlowR.x + outputFlowT.w + outputFlowB.z;\n"
			"	float inflows	= outputFlowL + outputFlowR + outputFlowT + outputFlowB;\n"
			"	float outflows	= outputFlowC.x + outputFlowC.y + outputFlowC.z + outputFlowC.w;\n"
			"\n"
			"	vec3 scenePositionC = texture( scenePositionMap, texCoord ).xyz;\n"
			"	// FLUID EMITTER or DRAINER\n"
			"	float emitOrDrainFluid = 0.0;\n"
			"\n"

			/*"	for( int i = 0; i < 4; ++i )\n"
			"	{\n"
			"		if ( emitterOrDrainerIntensity[i] == 0.0 )\n"
			"		{\n"
			"			break;\n"
			"		}\n"
			"		emitOrDrainFluid += computeFluidEmitterOrDrainer( scenePositionC, emitterOrDrainer[i], emitterOrDrainerIntensity[i] );\n"
			"	}\n"*/

			"	for( int i = 0; i < 4; ++i )\n"
			"	{\n"
			"		if ( emitterOrDrainerIntensity[i] != 0.0 )\n"
			"		{\n"
			"			emitOrDrainFluid += computeFluidEmitterOrDrainer( scenePositionC, emitterOrDrainer[i], emitterOrDrainerIntensity[i] );\n"
			"		}\n"
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

