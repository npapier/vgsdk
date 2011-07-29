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

