def init(context):
	print "Post process demo : FXAA1"
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

	# FXAA
	root.addChild( vgd.Antialiasing.create("FXAA1") )

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
