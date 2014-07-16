def init(context):
	print "Post process demo : Noise"
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

	# Noise
	noise = vgd.Noise.create("Noise")
	noise.setFactors( vgm.Vec4f(0.025, 0.1, 4, 1) )
	root.addChild( noise )

	# Clear 
	clear = vgd.ClearFrameBuffer.create('Frame Buffer Node')
	clear.setClearColor(vgm.Vec4f(0.2, 0.4, 0.4, 0.0))
	canvas.getSetup().addChild( clear )

	# Model load
	import os
	canvas.load(os.getcwd() + r"\mesh\cat.dae")
	canvas.viewAll()
	canvas.refresh()
	
	
def refresh( context ):
	# Called 25 times per second.
	return