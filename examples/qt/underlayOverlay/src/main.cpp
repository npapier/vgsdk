#include <QApplication>
#include <QMainWindow>

#include <vgCairo/ImageSurface.hpp>
#include <vgd/node/Box.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/LayerPlan.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgQt/BasicManipulator.hpp>


// Defines the window size.
static const int windowWidth = 640;
static const int windowHeight = 480;


vgd::Shp< vgd::basic::IImage > createUnderlayImage()
{
	vgd::Shp< vgCairo::ImageSurface >	image = vgd::makeShp( new vgCairo::ImageSurface(windowWidth, windowHeight) );
	cairo_t *							cr = image->getContext();
	
	cairo_pattern_t * pattern = cairo_pattern_create_linear( 0, 0, 0, windowHeight );
	cairo_pattern_add_color_stop_rgb( pattern, 0, 0.6, 0.5, 0.8 );
	cairo_pattern_add_color_stop_rgb( pattern, 1, 0.1, 0.05, 0.2 );	
	cairo_set_source( cr, pattern );
	cairo_paint( cr );
	cairo_pattern_destroy( pattern );

	cairo_set_source_rgba( cr, 1.0, 1.0, 1.0, 0.5 );
	cairo_select_font_face( cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD );
	cairo_set_font_size( cr, 50.0 );
	cairo_move_to( cr, 50, windowHeight - 50 );
	cairo_show_text( cr, "Cairo underlay" );
	
	return image;
}


vgd::Shp< vgd::basic::IImage > createOverlayImage()
{
	vgd::Shp< vgCairo::ImageSurface >	image = vgd::makeShp( new vgCairo::ImageSurface(windowWidth, windowHeight) );
	cairo_t *							cr = image->getContext();

	cairo_set_source_rgba( cr, 1.0, 0.0, 1.0, 0.5 );
	cairo_select_font_face( cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD );
	cairo_set_font_size( cr, 50.0 );
	cairo_move_to( cr, 50, 75 );
	cairo_show_text( cr, "Cairo overlay" );
	
	return image;
}


int main( int argc, char ** argv )
{
	QApplication			application(argc, argv);
	QMainWindow				mainWindow;
	vgQt::BasicManipulator	canvas;


	// Initializes the main window.
	mainWindow.setCentralWidget( &canvas );
	mainWindow.setFixedSize( windowWidth, windowHeight );
	mainWindow.setWindowTitle("underlay, overlay and cairo text demo using vgSDK");


	// Set up the default scene graph.
	canvas.createOptionalNodes();
	

	// Configures the ambiant color.
	vgd::Shp< vgd::node::LightModel > lightModel = canvas.getOptionalNodeAs< vgd::node::LightModel >( vgUI::BasicViewer::LIGHT_MODEL );
	lightModel->setAmbient( vgm::Vec4f(0.6f, 0.5f, 0.8f, 0.f) );


	// Adds a light.
	vgd::Shp< vgd::node::DirectionalLight > light =vgd::node:: DirectionalLight::create("light");
	light->setOn( true );
	light->setDirection( vgm::Vec3f(0, -1, -1) );
	canvas.getSetup()->addChild( light );


	// Adds the underlay.
	vgd::Shp< vgd::node::LayerPlan > underlay = vgd::node::LayerPlan::createWhole( "underlay" );
	underlay->setImage( createUnderlayImage() );
	underlay->setPosition( vgm::Vec2f(0, 0) );
	underlay->setSize( vgm::Vec2f(1, 1) );
	canvas.getScene()->addChild( underlay );

	
	// Adds a simple mesh.
	canvas.getScene()->addChild( vgd::node::Box::createWhole("box") );


	// Adds the overlay.
	vgd::Shp< vgd::node::LayerPlan > overlay = vgd::node::LayerPlan::createWhole( "overlay" );
	overlay->setImage( createOverlayImage() );
	overlay->setPosition( vgm::Vec2f(0, 0) );
	overlay->setSize( vgm::Vec2f(1, 1) );
	canvas.getScene()->addChild( overlay );


	// Initializes the camera, shows the main window and runs the application loop.
	canvas.viewAll();
	mainWindow.show();
	return application.exec();
}