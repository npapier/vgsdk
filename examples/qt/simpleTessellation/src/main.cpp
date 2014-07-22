#include <QApplication>
#include <QMainWindow>

#include <vgd/node/Camera.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/TessellationLevel.hpp>
#include <vgd/node/TessellationProperties.hpp>
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
	mainWindow.setWindowTitle("Simple tessellation example (move the scene by pressing SHIFT and your mouse up and down)");


	// Set up the default scene graph.
	canvas.createOptionalNodes();

	// Wireframe rendering without lighting
	using vgd::node::LightModel;
	vgd::Shp< LightModel > lightModel = canvas.getOptionalNodeAs< LightModel >( vgUI::BasicViewer::LIGHT_MODEL );
	lightModel->setModel( LightModel::LIGHTING_OFF );

	using vgd::node::DrawStyle;
	vgd::Shp< DrawStyle > drawStyle = canvas.getOptionalNodeAs< DrawStyle >( vgUI::BasicViewer::DRAW_STYLE );
	drawStyle->setShape( DrawStyle::FLAT_HIDDEN_LINE );

	// Enables adaptive phong tessellation
	using vgd::node::Group;
	using vgd::node::TessellationLevel;
	using vgd::node::TessellationProperties;

	vgd::Shp< Group > group = canvas.getOptionalNodeAs< Group >( vgUI::BasicViewer::TESSELLATION );
	vgd::Shp< TessellationProperties >	tessProp	= group->getChild< TessellationProperties >(0);
	vgd::Shp< TessellationLevel >		tessLevel	= group->getChild< TessellationLevel >(1);

	//		Enables phong tessellation
	tessProp->setTessellation( TessellationProperties::PHONG );
	//		Specifies the minimum (1) and maximum (32) tessellation level used by the tessellation control shaders to tessellate the incoming primitive.
	tessProp->setRange( vgm::Vec2f(1.f, 32.f) );
	//		When tessellation method is set to PHONG and TessellationLevel.method==PIXELS_PER_EDGE, then this field specifies the desired number of pixels per edge
	tessProp->setPixelsPerEdge( 15.f );

	//		Chooses adaptive tessellation using the number of pixels per edge desired as criterion
	tessLevel->setMethod( TessellationLevel::PIXELS_PER_EDGE ); // TessellationLevel::UNIFORM to use an uniform criterion


	// Adds a simple sphere (20 triangles)
	vgd::Shp< vgd::node::Sphere > sphere = vgd::node::Sphere::create("sphere");
	sphere->scale( vgm::Vec3f(2.f, 1.f, 1.f) );
	canvas.getScene()->addChild( sphere );

	// Initializes the camera, shows the main window and runs the application loop.
	canvas.viewAll();
	vgd::Shp< vgd::node::Camera > camera = canvas.getCamera();
	vgm::MatrixR lookAtMatrix = vgm::MatrixR();
	lookAtMatrix.setLookAt(vgm::Vec3f(3, 3, 15), vgm::Vec3f(0, 0, 0), vgm::Vec3f(0, 0, 1));
	camera->setLookAt(lookAtMatrix);

	mainWindow.show();
	return application.exec();
}