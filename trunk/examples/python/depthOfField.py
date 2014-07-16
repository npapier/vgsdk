import math

counter = 0
dof = None

def init( context ):
	global dof
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

	# Material
	material2 = vgd.Material.create("GreenMaterial")
	material2.setDiffuse( vgm.Vec3f(0., 1., 0.) )
	canvas.getScene().addChild( material2 )

	# Array of boxes
	for i in range(10):
		box = vgd.Box.create("box" + str(i))
		box.initializeGeometry()
		transformation = vgm.MatrixR()
		transformation.setRotate( vgm.Rotation( vgm.Vec3f(-1, 1, 0.5), vgm.deg2rad(-25.) ) )
		box.transform(transformation)
		transformation = vgm.MatrixR()
		transformation.setTranslate( vgm.Vec3f(-1 + 0.6 * i, -1 + 0.5 * i, -i * 1.5) )
		transformation.scale(0.5)
		box.transform(transformation)
		canvas.getScene().addChild( box )

	# Material for back wall
	material3 = vgd.Material.create("GreyMaterial")
	material3.setDiffuse( vgm.Vec3f(0.3, 0.3, 0.3) )
	canvas.getScene().addChild( material3 )

	# Back wall
	wall = vgd.Quad.create("Wall")
	wall.initializeGeometry( 15., 15. )
	transformation = vgm.MatrixR()
	transformation.setRotate( vgm.Rotation( vgm.Vec3f(1., 0., 0.), vgm.deg2rad(-90.) ) )
	transformation.setTranslate( vgm.Vec3f(0, 0, -15) )
	wall.transform(transformation)
	canvas.getScene().addChild( wall )

	# Depth of field node
	dof = vgd.DepthOfField.create("DOF")
	dof.setFocusToNear( 2.0 )
	dof.setFocusToFar( 3.0 )
	dof.setFocus( 10.0 )
	dof.setNearMaximumBlurriness( 0.8 )
	dof.setFarMaximumBlurriness( 0.8 )
	canvas.getScene().addChild( dof )

	# Camera
	canvas.viewAll()	

def refresh( context ):	
	global counter
	global dof
	counter += 1
	dof.setFocus( math.cos( counter / 40.0) * 5 + 25 )
	context.getCanvas().refresh()
