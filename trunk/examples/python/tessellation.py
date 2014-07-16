def init(context):
	print "Tessellation demo"
	import vge
	canvas = context.getBasicManipulator()
	tessellationLevel	= vgd.TessellationLevel.create("Tessellation level node")

	method 				= vgd.MethodValueType(vgd.TessellationLevel.CUSTOM)
	mode				= vgd.ComposeModeValueType(vgd.TessellationLevel.APPEND)
	tessellationLevel.setMethod( method )
	tessellationLevel.setComposeMode( mode )

	# load tessellation declaration
	declaration = """
	void tessellationLevelMethodSPHERE( out vec4 tessLevelOuter, out vec2 tessLevelInner)
	{                                                                                    
		vec3 c0 = vec3(gl_in[0].gl_Position);                                            
	   vec3 c1 = vec3(gl_in[1].gl_Position);                                             
	   vec3 c2 = vec3(gl_in[2].gl_Position);                                             
																						 
	   vec3 dispCenter = vec3(2,30,34);                                        			 
	   float radius =  10;                                                				 
																						 
	   float d0 = distance((c0+c1)*0.5, dispCenter );                                    
	   float d1 = distance((c1+c2)*0.5, dispCenter );                                    
	   float d2 = distance((c2+c0)*0.5, dispCenter );                                    
																						 
	   float d0p = 1 - clamp( d0, 0, radius ) / radius;                                  
	   float d1p = 1 - clamp( d1, 0, radius ) / radius;                                  
	   float d2p = 1 - clamp( d2, 0, radius ) / radius;                                  
																						 
	   tessLevelOuter[0] = d1p*TESS_RANGE_MAX*4 + 1;                      				 
	   tessLevelOuter[1] = d2p*TESS_RANGE_MAX*4 + 1;                      				 
	   tessLevelOuter[2] = d0p*TESS_RANGE_MAX*4 + 1;                      				 
	   tessLevelOuter[3] = 0;                                                            
	   tessLevelInner[0] = d0p*TESS_RANGE_MAX*4 + 1;                      				 
	   tessLevelInner[1] = 0;                                                            
	}
	"""                                                                                    
	tessellationLevel.setCustomDeclarations(declaration);

	# load custom code
	code ="""
	// CUSTOM METHOD
	tessellationLevelMethodPIXELS_PER_EDGE( tessLevelOuter, tessLevelInner );
	vec4 tessLevelOuter2;                                                    
	vec2 tessLevelInner2;                                                    
	tessellationLevelMethodSPHERE( tessLevelOuter2, tessLevelInner2 );       
	tessLevelOuter += tessLevelOuter2;                                       
	tessLevelInner += tessLevelInner2;                                       """
	tessellationLevel.setCustomCode(code)                                                                

	canvas.getSetup().addChild( tessellationLevel )


	# Clear 
	clear = vgd.ClearFrameBuffer.create('Frame Buffer Node')
	clear.setClearColor(vgm.Vec4f(0.2, 0.4, 0.4, 0.0))
	canvas.getSetup().addChild( clear )

	# Model load
	import os
	canvas.load(os.getcwd() + r"\mesh\cat.dae")

	# high level detail settings
	#settings = vge.UserSettings(canvas)
	#settings.setMaxLevel()
	#settings.apply(canvas)
	canvas.viewAll()
	print "Done"
	
def refresh( context ):
	# Called 25 times per second.
	return