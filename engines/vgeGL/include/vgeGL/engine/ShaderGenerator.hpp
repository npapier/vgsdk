// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_SHADERGENERATOR_HPP
#define _VGEGL_ENGINE_SHADERGENERATOR_HPP

#include <boost/lexical_cast.hpp>
#include <glo/GLSLProgram.hpp>
#include <vgd/Shp.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Light.hpp>

#include "vgeGL/engine/GLSLState.hpp"



namespace vgeGL { namespace engine { struct Engine; } }



namespace vgeGL
{

namespace engine
{



/*lazy generation of shaders => call run() on VertexShape node
invalid generator from handlers
count generation during a pass
cache generated shaders at least for a single rendering */

// @todo move GLSLGHelpers
struct GLSLHelpers
{
	// @todo Flags class in vgd::basic



	// LIGHTING
	static const std::string& generate_lightAccumulators()
	{
		static const std::string retVal = 
		"vec4 Ambient;\n"
		"vec4 Diffuse;\n"
		"vec4 Specular;\n"
		"\n";

		return retVal;
	}



	static const std::string generate_lights( const GLSLState& state )
	{
		std::string retVal;

		// DIRECTIONAL_LIGHT
		if ( state.isEnabled( GLSLState::DIRECTIONAL_LIGHT) )
		{
			const std::string& directionalLight = GLSLHelpers::generateFunction_directionalLight( state );
			retVal += directionalLight;
		}

		// POINT_LIGHT
		if ( state.isEnabled( GLSLState::POINT_LIGHT) )
		{
			const std::string& pointLight = GLSLHelpers::generateFunction_pointLight( state );
			retVal += pointLight;
		}

		// SPOT_LIGHT
		if ( state.isEnabled( GLSLState::SPOT_LIGHT) )
		{
			const std::string& spotLight = GLSLHelpers::generateFunction_spotLight( state );
			retVal += spotLight;
		}

		return retVal;
	}



	static const std::string& generateFunction_directionalLight( const GLSLState& state )
	{
		static const std::string retVal = 
		"void directionalLight( in int i, in vec3 normal )\n"
		"{\n"
		"	float nDotVP;			// normal . light direction\n"
		"	float nDotHV;			// normal . light half vector\n"
		"	float pf;				// power factor\n"
		"\n"
		"	nDotVP = max(0.0, dot(normal, normalize(vec3(gl_LightSource[i].position))));\n"
		"	nDotHV = max(0.0, dot(normal, vec3(gl_LightSource[i].halfVector)));\n\n"
		"	if ( nDotVP == 0.0 || nDotHV == 0.0 )\n"
		"	{\n"
		"		pf = 0.0;\n"
		"	}\n"
		"	else\n"
		"	{\n"
		"		pf = pow( nDotHV, gl_FrontMaterial.shininess);\n\n"
		"	}\n"
		"\n"
		"	Ambient		+= gl_LightSource[i].ambient;\n"
		"	Diffuse		+= gl_LightSource[i].diffuse * nDotVP;\n"
		"	Specular	+= gl_LightSource[i].specular * pf;\n"
		"}\n";

		return retVal;
	}



	static const std::string& generateFunction_pointLight( const GLSLState& state )
	{
		static const std::string retVal =
		"void pointLight( in int i, in vec3 ecPosition3, in vec3 normal, in vec3 eye )\n"
		"{\n"
		"	float nDotVP;			// normal . light direction\n"
		"	float nDotHV;			// normal . light half vector\n"
		"	float pf;				// power factor\n"
		"	float attenuation;		// computed attenuation factor\n"
		"	float d;				// distance from surface to light source\n"
		"	vec3  VP;				// direction from surface to light position\n"
		"	vec3  halfVector;		// direction of maximum highlights\n"
		"\n"
		"	// Compute vector from surface to light position\n"
		"	VP = vec3(gl_LightSource[i].position) - ecPosition3;\n"
		"\n"
		"	// Compute distance between surface and light position\n"
		"	d = length(VP);\n"
		"\n"
		"	// Normalize the vector from surface to light position\n"
		"	VP = normalize(VP);\n"
		"\n"
		"	// Compute attenuation\n"
		"	attenuation =	1.0 / (gl_LightSource[i].constantAttenuation +\n"
		"					gl_LightSource[i].linearAttenuation * d +\n"
		"					gl_LightSource[i].quadraticAttenuation * d * d);\n"
		"\n"
		"	halfVector = normalize(VP + eye);\n"
		"\n"
		"	nDotVP = max(0.0, dot(normal, VP));\n"
		"	nDotHV = max(0.0, dot(normal, halfVector));\n"
		"\n"
		"	if ( nDotVP == 0.0 || nDotHV == 0.0 )\n"
		"	{\n"
		"		pf = 0.0;\n"
		"	}\n"
		"	else\n"
		"	{\n"
		"		pf = pow(nDotHV, gl_FrontMaterial.shininess);\n"
		"	}\n"
		"\n"
		"	Ambient		+= gl_LightSource[i].ambient * attenuation;\n"
		"	Diffuse		+= gl_LightSource[i].diffuse * nDotVP * attenuation;\n"
		"	Specular	+= gl_LightSource[i].specular * pf * attenuation;\n"
		"}\n";

		return retVal;
	}



	static const std::string& generateFunction_spotLight( const GLSLState& state )
	{
		static const std::string retVal =
		"void spotLight( in int i, in vec3 ecPosition3, in vec3 normal, in vec3 eye )\n"
		"{\n"
		"	float nDotVP;			// normal . light direction\n"
		"	float nDotHV;			// normal . light half vector\n"
		"	float pf;				// power factor\n"
		"	float spotDot;			// cosine of angle between spotlight\n"
		"	float spotAttenuation;	// spotlight attenuation factor\n"
		"	float attenuation;		// computed attenuation factor\n"
		"	float d;				// distance from surface to light source\n"
		"	vec3  VP;				// direction from surface to light position\n"
		"	vec3  halfVector;		// direction of maximum highlights\n"
		"\n"
		"	// Compute vector from surface to light position\n"
		"	VP = vec3(gl_LightSource[i].position) - ecPosition3;\n"
		"\n"
		"	// Compute distance between surface and light position\n"
		"	d = length(VP);\n"
		"\n"
		"	// Normalize the vector from surface to light position\n"
		"	VP = normalize(VP);\n"
		"\n"
		"	// Compute attenuation\n"
		"	attenuation =	1.0 / (gl_LightSource[i].constantAttenuation +\n"
		"					gl_LightSource[i].linearAttenuation * d +\n"
		"					gl_LightSource[i].quadraticAttenuation * d * d);\n"
		"\n"
		"	// See if point on surface is inside cone of illumination\n"
		"	spotDot = dot(-VP, normalize(gl_LightSource[i].spotDirection));\n"
		"\n"
		"	if ( spotDot < gl_LightSource[i].spotCosCutoff || spotDot == 0.0 )\n"
		"	{\n"
		"		spotAttenuation = 0.0; // light adds no contribution\n"
		"	}\n"
		"	else\n"
		"	{\n"
		"		spotAttenuation = pow(spotDot, gl_LightSource[i].spotExponent);\n"
		"	}\n"
		"\n"
		"	// Combine the spotlight and distance attenuation.\n"
		"	attenuation *= spotAttenuation;\n"
		"\n"
		//"	halfVector = gl_LightSource[i].halfVector;\n"
		"	halfVector = normalize(VP + eye);\n"
		"\n"
		"	nDotVP = max( 0.0, dot(normal, VP) );\n"
		"	nDotHV = max( 0.0, dot(normal, halfVector) );\n"
		"\n"
//		"	if ( nDotVP <= 0.0 )\n"
		"	if ( nDotVP == 0.0 || nDotHV == 0.0 )\n"
		"	{\n"
		"		pf = 0.0;\n"
		"	}\n"
		"	else\n"
		"	{\n"
		"		pf = pow( nDotHV, gl_FrontMaterial.shininess );\n"				// @todo gl_Back ?
		"	}\n"
		"\n"
		"	Ambient		+= gl_LightSource[i].ambient * attenuation;\n"
		"	Diffuse		+= gl_LightSource[i].diffuse * nDotVP * attenuation;\n"
		"	Specular	+= gl_LightSource[i].specular * pf * attenuation;\n"
		"}\n";

		return retVal;
	}


	static const std::string generateFunction_flight( const GLSLState& state )
	{
		std::string retVal;

		if ( state.isLightingEnabled() )
		{
			retVal +=
			"\n"
			"void flight( in vec4 ecPosition, in vec3 normal )\n"
			"{\n"
			"	vec3 ecPosition3;\n"
			"	vec3 eye;\n"
			"\n"
			"	ecPosition3 = (vec3(ecPosition)) / ecPosition.w;\n";

			if ( state.isEnabled(GLSLState::LOCAL_VIEWER) )
			{
				retVal +=
				"	eye = -normalize(ecPosition3);\n"
				"\n";
			}
			else
			{
				retVal +=
				"	eye = vec3(0.0, 0.0, 1.0);\n"
				"\n";
			}

			retVal += 
			"	// Clear the light intensity accumulators\n"
			"	Ambient		= vec4(0.0);\n"
			"	Diffuse		= vec4(0.0);\n"
			"	Specular	= vec4(0.0);\n"
			"\n";

			std::string currentLightFront;
			std::string currentLightBack;

			uint		i		= 0;
			const uint	iEnd	= state.getMaxLight();

			for( uint foundLight = 0; i != iEnd; ++i )
			{
				const vgd::Shp< GLSLState::LightState > currentLightState = state.getLight(i);

				if ( currentLightState )
				{
					const vgd::node::Light * currentLight = currentLightState->getLightNode();
					assert( currentLight != 0 );

					bool isDefined;
					bool onValue;

					isDefined = currentLight->getOn( onValue );

					if ( isDefined && onValue )
					{
						const std::string iStr = boost::lexical_cast< std::string >( i ); // @todo optme

						const int lightType = currentLightState->getLightType();

						switch ( lightType )
						{
							case GLSLState::DIRECTIONAL_LIGHT:
								currentLightFront	+= "	directionalLight( " + iStr + ", normal );\n";
								currentLightBack	+= "	directionalLight( " + iStr + ", -normal );\n";
								break;

							case GLSLState::POINT_LIGHT:
								currentLightFront	+= "	pointLight( " + iStr + ", ecPosition3, normal, eye );\n";
								currentLightBack	+= "	pointLight( " + iStr + ", ecPosition3, -normal, eye );\n";
								break;

							case GLSLState::SPOT_LIGHT:
								currentLightFront	+= "	spotLight( " + iStr + ", ecPosition3, normal, eye );\n";
								currentLightBack	+= "	spotLight( " + iStr + ", ecPosition3, -normal, eye );\n";
								break;

							default:
								assert( false && "Unknown light type !" );
						}

						retVal += currentLightFront;

						// Takes care of two sided lighting
						if ( state.isTwoSidedLightingEnabled() )
						{
							retVal += currentLightBack;
						}
					}
					// else light off, nothing to do

					//
					++foundLight;
					if ( foundLight == state.getNumLight() )
					{
						break;
					}
				}
				// else no light, nothing to do
			}

			/*retVal +=
			"\n"
			"	color =	gl_FrontLightModelProduct.sceneColor +\n"
			"			Ambient * gl_FrontMaterial.ambient +\n"
			"			Diffuse * gl_FrontMaterial.diffuse;\n";

			// GL_SEPARATE_SPECULAR_COLOR
			retVal += "	gl_FrontSecondaryColor = Specular * gl_FrontMaterial.specular;\n";
			// GL_SEPARATE_SPECULAR_COLOR == false => "	 color += Specular * gl_FrontMaterial.specular;\n"

			retVal += 
			"	color = clamp( color, 0.0, 1.0 );\n"
			"	gl_FrontColor = color;\n";*/

			// @todo
			// if(lightModelTwoSidedInt)
	        // {
	            // str +=  wxT("    // Invert the normal for these lighting calculations\n"
	                    // "    normal = -normal;\n"
	                    // "    //Clear the light intensity accumulators\n"
	                    // "    Ambient  = vec4 (0.0);\n"
	                    // "    Diffuse  = vec4 (0.0);\n"
	                    // "    Specular = vec4 (0.0);\n\n");

	            // for (int i = 0; i < 8; i++)
	            // {
	                // if(glIsEnabled(GL_LIGHT0 + i))
	                // {
	                    // glGetLightfv( GL_LIGHT0 + i, GL_POSITION, v);

	                    // if(v[3] == 0.0)
	                    // {
	                        // str += wxString::Format(wxT("    directionalLight(%d, normal);\n\n"), i);
	                        // fLightDir = true;
	                    // }
	                    // else
	                    // {
	                        // glGetLightfv( GL_LIGHT0 + i, GL_SPOT_CUTOFF, &spotCut);
	                        // if( spotCut == 180.0)
	                        // {
	                            // str += wxString::Format(wxT("    pointLight(%d, normal, eye, ecPosition3);\n\n"), i);
	                            // fLightPoint = true;
	                        // }
	                        // else
	                        // {
	                            // str += wxString::Format(wxT("    spotLight(%d, normal, eye, ecPosition3);\n\n"), i);
	                            // fLightSpot = true;
	                        // }
	                    // }
	                // }
	            // }

	            // str +=  "\n"
	                // "    color = gl_BackLightModelProduct.sceneColor +\n"
	                // "        Ambient * gl_BackMaterial.ambient +\n"
	                // "        Diffuse * gl_BackMaterial.diffuse;\n";

	            // if(separateSpecInt == GL_SEPARATE_SPECULAR_COLOR)
	                // str += "    gl_BackSecondaryColor = Specular * gl_BackMaterial.specular;\n";
	            // else
	                // str += "    color += Specular * gl_BackMaterial.specular;\n";

	            // str += "    gl_BackColor = color;\n";
	        // }

			/*retVal += 
			"\n"
			"	gl_FrontColor *= alphaFade;\n"; // @todo*/
			//"	gl_FrontColor.a *= alphaFade;\n"; // @todo
	        // if(lightModelTwoSidedInt)
	        // {     
	            // str += "    gl_FrontSecondaryColor.a *= alphaFade;\n"
	                // "    gl_BackColor.a *= alphaFade;\n"
	                // "    gl_BackSecondaryColor.a *= alphaFade;\n";
	        // }
			retVal += 
			"}\n";
		}
		//else no lighting => then nothing to do

		return retVal;
	}



	//
	static const std::string& generateFunction_fnormal( const bool isLightingEnabled )
	{
		if ( isLightingEnabled )
		{
			static const std::string retVal =
			"\n"
			"vec3 fnormal(void)\n"
			"{\n"
			"	//Compute the normal\n"
			"	vec3 normal = gl_NormalMatrix * gl_Normal;\n"
			"	normal = normalize(normal);\n"	// glIsEnabled(GL_NORMALIZE)	//@todo not if PerPixelLighting
//			"	normal = normal * gl_NormalScale;\n"		// glIsEnabled(GL_RESCALE_NORMAL)
			"	return normal;\n"
			"}\n"
			"\n";

			return retVal;
		}
		else
		{
			static const std::string retVal("");
			return retVal;
		}
	}



	// TEXTURE
	static const std::string generateFunction_ftexgen( const vgeGL::engine::GLSLState& state )
	{
		std::string retVal;

		retVal = 
		"void ftexgen( in vec4 ecPosition, in vec3 normal )\n"
		"{\n";

		uint		i		= 0;
		const uint	iEnd	= state.getMaxTexture();

		for( uint foundTexture = 0; i != iEnd; ++i )
		{
			const glo::Texture * current = state.getTexture( i );

			if ( current ) // @todo Texturing is enabled if vertex shape contains tex coord and NOT when a texture is defined.
			{
				const std::string strUnit = boost::lexical_cast< std::string >( i );
				retVal +=
				"	gl_TexCoord[" + strUnit + "] = gl_MultiTexCoord" + strUnit + ";\n";

				//
				++foundTexture;
				if ( foundTexture == state.getNumTexture() )
				{
					break;
				}
			}
			// else no texture, nothing to do
		}

		retVal += 
		"}\n";

		return retVal;
	}


	static const std::string generate_samplers( const vgeGL::engine::GLSLState& state )
	{
		std::string retVal;

		uint		i		= 0;
		const uint	iEnd	= state.getMaxTexture();

		for( uint foundTexture = 0; i != iEnd; ++i )
		{
			const glo::Texture * current = state.getTexture( i );

			if ( current ) // @todo Texturing is enabled if vertex shape contains tex coord and NOT when a texture is defined.
			{
				const std::string strUnit = boost::lexical_cast< std::string >( i );

				retVal +=
				"uniform sampler2D texUnit" + strUnit + ";\n";

				//
				++foundTexture;
				if ( foundTexture == state.getNumTexture() )
				{
					break;
				}
			}
			// else no texture, nothing to do
		}

		return retVal;
	}


	static const std::string generate_texLookups( const vgeGL::engine::GLSLState& state )
	{
		std::string retVal;

		uint		i		= 0;
		const uint	iEnd	= state.getMaxTexture();

		for( uint foundTexture = 0; i != iEnd; ++i )
		{
			const glo::Texture * current = state.getTexture( i );

			if ( current ) // @todo Texturing is enabled if vertex shape contains tex coord and NOT when a texture is defined.
			{
				const std::string strUnit = boost::lexical_cast< std::string >( i );

				retVal +=
				"	color *= texture2D(texUnit" + strUnit + ", gl_TexCoord[" + strUnit + "].xy);\n";

				//
				++foundTexture;
				if ( foundTexture == state.getNumTexture() )
				{
					break;
				}
			}
			// else no texture, nothing to do
		}

		return retVal;
	}
};



/**
 * @brief Abstract base class for code generator
 *
 * This is the abstract base class for all GLSL shader generator.
 *
 * @todo NVidia/CG generator ?
 */
struct VGEGL_API ShaderGenerator
{
	/**
	 * @brief Default constructor
	 */
	ShaderGenerator( const glo::GLSLProgram::ShaderType shaderType );


	/**
	 * @param engine	used to lookup the rendering state (light(s) , texture(s) and so on).
	 */
	virtual const bool generate( vgeGL::engine::Engine * engine ) = 0;


	/**
	 * @brief Returns the type of the shader generated by this class.
	 *
	 * @return the type of the shader generated by this class
	 */
	const glo::GLSLProgram::ShaderType getShaderType() const;


	// @todo hides getMainDF() and adds isValid() and invalidate()
	/**
	 * @brief Retrieves the main dirty flag of the generator
	 *
	 * This dirty flag is used to store the validation/invalidation state of the generator.
	 * An invalid state means that method run() must be called before retrieving the generated code.
	 * A valid state means that generaed code could be retrieve directly.
	 *
	 * @return the main dirty flag
	 */
	vgd::field::DirtyFlag& getMainDirtyFlag();


	/**
	 * @brief Enables or disables the code generation depending on the value of the parameter b.
	 *
	 * @param isEnabled		true when code generation must be enabled, false otherwise
	 */
	void setEnabled( const bool isEnabled = true );

	/**
	 * @brief Determines whether the code generation is enabled.
	 *
	 * @return true if the code generation is enabled, false otherwise
	 */
	const bool isEnabled() const;


	/**
	 * @brief Retrieves the generated code
	 *
	 * @return the string containing the generated code
	 */
	const std::string& getCode() const;


private:
	glo::GLSLProgram::ShaderType	m_shaderType;		///< the type of the generated shader
	vgd::field::DirtyFlag			m_mainDirtyFlag;	///< the main dirty flag
	bool							m_isEnabled;		///< true when code generation is enabled, false otherwise
protected:
	std::string						m_code;				///< the string containing the generated code
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_SHADERGENERATOR_HPP
