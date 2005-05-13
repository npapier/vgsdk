// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "basicViewer/myCanvas.hpp"

#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgTrian/Loader.hpp>



namespace basicViewer
{



BEGIN_EVENT_TABLE( myCanvas, vgWX::BasicManipulator )
END_EVENT_TABLE()



myCanvas::myCanvas(
					wxWindow *parent,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id ) :

	vgWX::BasicManipulator( parent, name, pos, size, style, gl_attrib, id )
{
}



void myCanvas::initialize()
{
	// STEP 1: OpenGL buffers must be initialized.
	// clears the color and depth buffer
	vgd::Shp< vgd::node::ClearFrameBuffer > clearFrameBuffer = vgd::node::ClearFrameBuffer::create("clearFrameBuffer");
	// specifies clear values for the color buffer. black is the default color.
	//clearFrameBuffer->setClear( vgd::node::ClearFrameBuffer::COLOR, vgm::Vec4f( 1.f, 0.f, 0.f, 0.f) );
	
	// STEP 2: adding a light.
	// create and swith on a directional light.
	vgd::Shp< vgd::node::DirectionalLight > light1 = vgd::node::DirectionalLight::create("light1");
	light1->setOn( true );
	// Sets its direction.
	light1->setDirection( vgm::Vec3f(0.f, 0.f, -1.f) );

	// STEP 3: adding a shape/mesh.

	// load file liver.trian
	vgTrian::Loader loader;
	std::pair< bool, vgd::Shp< vgd::node::VertexShape > > retVal;

	retVal = loader.loadTrian( "liver.trian" );
	
	if ( !retVal.first )
	{
		throw "Error during loading .trian";
		return;
	}

	// trian file does not contain normal table, so they must be computed.
	vgd::Shp< vgd::node::VertexShape > vertexShape( retVal.second );
	vertexShape->computeNormals();

	// STEP 4: adding nodes to the scene graph.
	
	// The scene graph is divided in two parts :
	// - The SETUP part, that contains some useful nodes to initialize the scene.
	// - The SCENE part, that must contains the real scene like the mesh.
	
	// add clearFrameBuffer and light to the setup node.
	getSetup()->addChild( clearFrameBuffer );
	getSetup()->addChild( light1 );

	// add the mesh to the scene
	getScene()->addChild( vertexShape );
	
	// STEP 5: Adjust the camera position and frustum to be able to view the entire scene 
	viewAll();
	
	// STEP 6: generate a file (sceneGraph.dot) with a graphical representation of the scene graph (in graphviz format).
	writeGraphviz();
}



} // namespace basicViewer
