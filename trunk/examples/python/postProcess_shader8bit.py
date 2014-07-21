def init(context):
	print "Post process demo : 8 bit shader"
	canvas = context.getBasicManipulator()
	# OutputBufferProperty
	obufProperty 	= vgd.OutputBufferProperty.create("BUF0", 0)
	format 			= vgd.FormatValueType(vgd.OutputBufferProperty.RGBA)
	type 			= vgd.TypeValueType(vgd.OutputBufferProperty.INTEGER)
	command			= vgd.CommandValueType(vgd.OutputBufferProperty.COLOR)
	obufProperty.setFormat( format )
	obufProperty.setType( type )
	obufProperty.setCommand( command )
	canvas.getSetup().addChild( obufProperty )

	# Switch
	root = vgd.Switch.create("PostProcessing root")
	canvas.getSetup().addChild( root )
	root.setWhichChild( 0 )

	# Shader
	group = vgd.Group.create("shader filter")
	root.addChild( group )
	p = vgd.PostProcessing.create("p0")
	input0 = vgd.Input0ValueType(vgd.PostProcessing.OUTPUT_BUFFER0)
	filter = vgd.FilterValueTypePostProcessing(vgd.PostProcessing.CUSTOM_FILTER)
	p.setInput0( input0 )
	p.setFilter( filter )
	p.setParam1f0( 8. )
	p.setCustomFilterDefinition(
		"vec4 apply( sampler2D texMap0, vec2 texCoord, float size )"
		"{\n"
		"	vec2 lowResolutionPixelSize = vec2(size, size);\n"
		"	vec2 texMap0Size = textureSize( texMap0, 0 );\n"
		"	float dx = lowResolutionPixelSize.x/texMap0Size.x;\n"
		"	float dy = lowResolutionPixelSize.y/texMap0Size.y;\n"
		"	vec2 newTexCoord = vec2( dx*floor(texCoord.x/dx), dy*floor(texCoord.y/dy) );\n"
		"	return texture( texMap0, newTexCoord );\n"
		"}\n"
		"\n\n\n" );
	p.setCustomFilterApply(
	"	color = apply( texMap2D[0], mgl_TexCoord[0].xy, param1f0 );\n"
	)
	group.addChild( p )

	# Installs PostProcessing by default
	canvas.getScene().addChild( group )

	# Clear 
	clear = vgd.ClearFrameBuffer.create('Frame Buffer Node')
	clear.setClearColor(vgm.Vec4f(0.2, 0.4, 0.4, 0.0))
	canvas.getSetup().addChild( clear )

	# Model load
	canvas.load('mesh/cat.dae')
	canvas.viewAll()
	
	
def refresh( context ):
	# Called 25 times per second.
	return
