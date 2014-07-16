#include <QApplication>
#include <QMainWindow>

#include <vgd/node/Box.hpp>
#include <vgd/node/Camera.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgQt/BasicManipulator.hpp>

// Defines the window size.
static const int windowWidth = 640;
static const int windowHeight = 480;


int main( int argc, char ** argv )
{
	QApplication			application(argc, argv);
	QMainWindow				mainWindow;
	vgQt::BasicManipulator	canvas;


	// Initializes the main window.
	mainWindow.setCentralWidget( &canvas );
	mainWindow.setFixedSize( windowWidth, windowHeight );
	mainWindow.setWindowTitle("Simple cube");


	// Set up the default scene graph.
	canvas.createOptionalNodes();
	

	// Configures the ambiant color.
	vgd::Shp< vgd::node::LightModel > lightModel = canvas.getOptionalNodeAs< vgd::node::LightModel >( vgUI::BasicViewer::LIGHT_MODEL );
	lightModel->setAmbient( vgm::Vec4f(0.6f, 0.5f, 0.8f, 0.f) );


	// Adds a light.
	vgd::Shp< vgd::node::DirectionalLight > light =vgd::node:: DirectionalLight::create("light");
	light->setOn( true );
	light->setDirection( vgm::Vec3f(0, -1, -0.5) );
	canvas.getSetup()->addChild( light );

	
	// Adds a simple mesh.
	vgd::Shp< vgd::node::Box > box = vgd::node::Box::createWhole("box");
	box->transform( vgm::Rotation( vgm::Vec3f(1, 1, 1), vgm::PI / 4) ); // Rotate the cube using axis + angle
	canvas.getScene()->addChild( box );

	// Initializes the camera, shows the main window and runs the application loop.
	canvas.viewAll();
	vgd::Shp< vgd::node::Camera > camera = canvas.getCamera();
	vgm::MatrixR lookAtMatrix = vgm::MatrixR();
	lookAtMatrix.setLookAt(vgm::Vec3f(3, 3, 3), vgm::Vec3f(0, 0, 0), vgm::Vec3f(0, 0, 1));
	camera->setLookAt(lookAtMatrix);

	mainWindow.show();
	return application.exec();
}