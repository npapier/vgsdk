def init(context):
	print "Transparency demo"
	canvas = context.getBasicManipulator()
	
	# *** transparent object ***
	#material
	material = vgd.Material.create("Transparent")
	material.setDiffuse( vgm.Vec3f(1., 0., 0.) )
	material.setOpacity(0.4)

	# sphere
	sphere = vgd.Sphere.create("SphereTransparent")
	sphere.initializeGeometry(5)

	canvas.getScene().addChild( material )
	canvas.getScene().addChild( sphere )

	# *** opaque object ***
	# material
	material2 = vgd.Material.create("Opaque")
	material2.setDiffuse( vgm.Vec3f(0., 1., 0.) )

	# // sphere
	sphere2 = vgd.Sphere.create("Sphere")
	sphere2.initializeGeometry(2)
	transformation = vgm.MatrixR()
	transformation.setTranslate( vgm.Vec3f(0., -1.2, -2.) )
	transformation.scale(0.5)
	sphere2.transform(transformation)

	canvas.getScene().addChild( material2 )
	canvas.getScene().addChild( sphere2 )


	# // @todo base->run() do a viewAll()
	canvas.viewAll()
	print "done"
	
	
def refresh( context ):
	# Called 25 times per second.
	return