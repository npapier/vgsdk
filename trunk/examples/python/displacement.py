def init(context):
	print "Displacement demo"
	canvas = context.getBasicManipulator()
	
	# Light
	spot = vgd.SpotLight.create("spot")
	spot.setOn( True )
	spot.setPosition( vgm.Vec3f(0., 20., 5.) )
	spot.setDirection( vgm.Vec3f(0., -1., -0.2) )
	spot.setCutOffAngle( 45. )
	lightModel = canvas.createOptionalNodeAsLightModel( vgUI.BasicViewer.LIGHT_MODEL )
	lightModelIndex = canvas.getSetup().findChild( lightModel )
	canvas.getSetup().insertChild( spot, lightModelIndex )
		
	# Wireframe display
	drawStyle = canvas.getOptionalNodeAsDrawStyle( vgUI.BasicViewer.DRAW_STYLE )
	shape = vgd.ShapeValueType(vgd.DrawStyle.WIREFRAME)
	drawStyle.setShape(shape)
	
	# Grid setting       
	grid = vgd.Grid.create()
	grid.initializeGeometry(1,1,10,10)
	canvas.getScene().addChild( grid )
	
	displacement = vgd.Displacement.create("Displacement node")
	
	# Load displacement shader code

	shader = """
	vec3 dispCenter= vec3(0, 0, 0);
	float radius = 1.0;
	float 	d = distance(vec3(position), dispCenter);
	//d = clamp(d, 0, radius) /radius;  // 0-1
	//d = 1 - d;                        // 1-0
	d = cos(d);
	position += d*vec4(0, 0, 1.0, 0);
	normal = vec3(position);
	"""

	# Only the one in use will be used, vertex shader or tessellation evaluation shader
	displacement.setDisplacementVS( "#ifndef TESSELLATION\n" + shader + "\n#endif\n" );
	displacement.setDisplacementTES( shader )
	canvas.getScene().insertChild( displacement )  	
	functionCustom = vgd.PredefinedDisplacementValueType( vgd.Displacement.CUSTOM )
	displacement.setDisplacementFunctionVS( functionCustom )
	displacement.setDisplacementFunctionTES( functionCustom )
	
	# Clear 
	clear = vgd.ClearFrameBuffer.create('Frame Buffer Node')
	clear.setClearColor(vgm.Vec4f(0.2, 0.4, 0.4, 0.0))
	canvas.getSetup().addChild( clear )

	canvas.viewAll()
	
	# Camera
	camera = canvas.getCamera()
	projection = camera.getProjection()
	drawingSize	= canvas.getEngine().getDrawingSurfaceSize()
	aspect = drawingSize[0]/drawingSize[1]
	projection.setPerspective(45, aspect, 0.001, 20)
	camera.setProjection(projection)
	lookAtMatrix = vgm.MatrixR()
	lookAtMatrix.setLookAt(vgm.Vec3f(2, 2, 3), vgm.Vec3f(0, 0, 0), vgm.Vec3f(0, 0, 1))
	camera.setLookAt(lookAtMatrix)
	
	print "Done"
	
def refresh( context ):
	# Called 25 times per second.
	return
