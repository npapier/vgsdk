// VGSDK - Copyright (C) 2008, 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/MultiMain.hpp"

#include <vgd/node/Camera.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/LayerPlan.hpp>

#include <vge/pass/ForEach.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/pass/Opaque.hpp"
#include "vgeGL/pass/Transparent.hpp"
#include "vgeGL/technique/ForwardRendering.hpp"



namespace vgeGL
{

namespace technique
{



MultiMain::MultiMain()
:	m_paintTechnique( vgd::makeShp( new vgeGL::technique::ForwardRendering() ) )
{
}



vgd::Shp< MultiMain::Window > MultiMain::addWindow( const std::string name,
	const int zOrder, const bool hasBorder, const vgm::Vec4f borderColor, const float borderWidth )
{
	WindowContainer::value_type value( name, vgd::makeShp(new Window( name, zOrder, true/*isVisible*/, WindowBorder(hasBorder, borderColor, borderWidth) ) ) );

	std::pair< WindowContainer::iterator, bool> retVal = m_windows.insert( value );

	return retVal.first->second;
}



vgd::Shp< MultiMain::Window > MultiMain::addWindow( const std::string name,
	const int zOrder, const WindowBorder borderState )
{
	WindowContainer::value_type value( name, vgd::makeShp(new Window( name, zOrder, true/*isVisible*/, borderState ) ) );

	std::pair< WindowContainer::iterator, bool> retVal = m_windows.insert( value );

	return retVal.first->second;
}



const bool MultiMain::removeWindow( const std::string name )
{
	const WindowContainer::size_type retVal = m_windows.erase( name );

	assert( (retVal == 0) || (retVal == 1) && "Unexpected return value." );
	return retVal == 1;
}



const bool MultiMain::removeAllWindows()
{
	const WindowContainer::size_type retVal = m_windows.size();

	m_windows.clear();

	return retVal >= 1;
}



vgd::Shp< MultiMain::Window > MultiMain::getWindow( const std::string name )
{
	WindowContainer::iterator iter = m_windows.find( name );

	if ( iter != m_windows.end() )
	{
		// Window found
		return iter->second;
	}
	else
	{
		// Window not found
		return vgd::makeShp< MultiMain::Window >(0);
	}
}



const vgd::Shp< MultiMain::Window > MultiMain::getWindow( const std::string name ) const
{
	WindowContainer::const_iterator iter = m_windows.find( name );

	if ( iter != m_windows.end() )
	{
		// Window found
		return iter->second;
	}
	else
	{
		// Window not found
		return vgd::makeShp< MultiMain::Window >(0);
	}
}



void MultiMain::setUnderlay( vgd::Shp< vgd::node::LayerPlan > underlay )
{
	m_underlay = underlay;
}



vgd::Shp< vgd::node::LayerPlan > MultiMain::getUnderlay()
{
	return m_underlay;
}



void MultiMain::apply( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector * traverseElements )
{
	// Searches clear framebuffer and camera node
	vgd::node::Camera *				camera				= 0;
	vgd::node::ClearFrameBuffer *	clearFrameBuffer	= 0;

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isAKindOf< vgd::node::Camera >() )
		{
			//camera = dynamic_cast< vgd::node::Camera * >(i->first);
			break;
		}
		
	}

	while ( i != iEnd )
	{
		if ( (i->first)->isAKindOf< vgd::node::ClearFrameBuffer >() )
		{
			clearFrameBuffer = dynamic_cast< vgd::node::ClearFrameBuffer * >(i->first);
			break;
		}
		++i;
	}

	if ( clearFrameBuffer == 0 )
	{
		// No clearFrameBuffer node in scene graph, do nothing
		vgLogDebug( "MultiMain::apply(): No ClearFrameBuffer in scene graph." );
		return;
	}

	// Retrieves camera properties and stores them.
	vgm::Rectangle2i cameraViewport;
	vgm::Rectangle2i cameraScissor;
	bool isCameraViewportDefined;
	bool isCameraScissorDefined;

	/*vgm::Rectangle2i cameraViewport;
	const bool isCameraViewportDefined = camera->getViewport( cameraViewport );
	const vgm::Rectangle2f cameraViewport2f(cameraViewport);*/
	const vgm::Rectangle2f drawingSurface(	0.f, 0.f,
											static_cast<float>(engine->getDrawingSurfaceSize()[0]), static_cast<float>(engine->getDrawingSurfaceSize()[1]) );

	/*vgm::Rectangle2i cameraScissor;
	const bool isCameraScissorDefined = camera->getScissor( cameraScissor );*/

	// Computes the window z-order (for visible windows only)
	typedef std::multimap< int, vgd::Shp< Window > > ZOrderedWindowContainer;
	ZOrderedWindowContainer zOrderedWindows;
	for( WindowContainer::const_iterator	i		= m_windows.begin(),
											iEnd	= m_windows.end();
		i != iEnd;
		++i )
	{
		WindowContainer::mapped_type window = i->second;

		if ( window->isVisible() )
		{
			// The window is visible
			const int zOrder = window->getZOrder();

			ZOrderedWindowContainer::value_type value( zOrder, window );
			/*const ZOrderedWindowContainer::iterator retVal = */zOrderedWindows.insert( value );
		}
		//else nothing to do, the window is hidden
	}

	// Clears the frame buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Renders underlay
	if ( getUnderlay() )
	{
		// Renders underlay
		engine->evaluate( paintService(), getUnderlay().get(), true, false );
	}

	// Renders each window from back to front (i.e. in z-order from 0 to n with n > 0 ).
	for( ZOrderedWindowContainer::const_iterator	i	= zOrderedWindows.begin(),
													iEnd= zOrderedWindows.end();
		i != iEnd;
		++i )
	{
		// Retrieves the window
		const vgd::Shp< MultiMain::Window > window = i->second;

		// Computes the new viewport from window geometry and original camera viewport
		const vgm::Rectangle2f windowGeometry = window->getGeometry();

		vgm::Rectangle2f newViewport;
		newViewport.set(
			drawingSurface.x() + windowGeometry.x() *	drawingSurface.width(),
			drawingSurface.y() + windowGeometry.y() *	drawingSurface.height(),
			windowGeometry.width() * drawingSurface.width(),
			windowGeometry.height() * drawingSurface.height() );
/*		newViewport.set(
			cameraViewport2f.x() + windowGeometry.x() *	cameraViewport2f.width(),
			cameraViewport2f.y() + windowGeometry.y() *	cameraViewport2f.height(),
			windowGeometry.width() * cameraViewport2f.width(),
			windowGeometry.height() * cameraViewport2f.height() );*/

		// Configures the scene graph
		const vgd::Shp< SceneGraphConfigurator > configurator = window->getConfigurator();

		vge::visitor::TraverseElementVector * currentTraverseElements;

		if ( configurator )
		{
			// Applies the configurator
			const bool sceneGraphTopologyUpdated = configurator->apply( traverseElements );

			if ( sceneGraphTopologyUpdated )
			{
				m_collectorExt.reset();
				vgd::node::Group * root = traverseElements->getRootPtr();
				root->traverse( m_collectorExt );
				currentTraverseElements = m_collectorExt.getTraverseElements();
			}
			else
			{
				currentTraverseElements = traverseElements;
			}
		}
		else
		{
			currentTraverseElements = traverseElements;
		}

		//
		camera = 0;
		vge::visitor::TraverseElementVector::const_iterator traverseElement, traverseElementEnd;
		for(	traverseElement = currentTraverseElements->begin(), traverseElementEnd = currentTraverseElements->end();
				traverseElement != traverseElementEnd;
				++traverseElement )
		{
			if ( (traverseElement->first)->isAKindOf< vgd::node::Camera >() )
			{
				camera = dynamic_cast< vgd::node::Camera * >(traverseElement->first);
				break;
			}
		}

		if ( camera == 0 )
		{
			// No camera node in scene graph, do nothing
			vgLogDebug( "MultiMain::apply(): No camera in scene graph." );
			return;
		}
		// Modifies the camera node
		cameraViewport = camera->getViewport();
		isCameraScissorDefined = camera->getScissor( cameraScissor );
		
		const vgm::Rectangle2i newViewport2i(newViewport);
		camera->setViewport( newViewport2i );
		camera->setScissor( newViewport2i );		

		// Paints the window
		vgd::Shp< vgeGL::technique::Technique > paintTechnique = getPaintTechnique();
		paintTechnique->setParameters( this->engine(), currentTraverseElements, sceneManager() );
		paintTechnique->apply( engine, currentTraverseElements );

		// Draws the window decoration
		if ( window->hasBorder() )
		{
			drawBorder( engine, window, newViewport2i );
		}

		// Undo the scene graph configuration
		if ( configurator )
		{
			configurator->unapply( currentTraverseElements );
		}

		// Restores camera node

		// scissor
		if ( isCameraScissorDefined )
		{
			camera->setScissor( cameraScissor );
		}
		else
		{
			camera->eraseScissor();
			glDisable(GL_SCISSOR_TEST);
		}

		// viewport
		camera->setViewport( cameraViewport );
	}



	// Validates the camera node
	camera->getDirtyFlag( camera->getDFNode() )->validate();
}



vgd::Shp< vgeGL::technique::Technique > MultiMain::getPaintTechnique() const
{
	return m_paintTechnique;
}



void MultiMain::setPaintTechnique( vgd::Shp< vgeGL::technique::Technique > technique )
{
	m_paintTechnique = technique;
}



void MultiMain::drawBorder( vgeGL::engine::Engine * engine, const vgd::Shp< MultiMain::Window > window, const vgm::Rectangle2i newViewport2i )
{
	// Makes a backup of GLSL activation state
	using vgeGL::engine::Engine;
	vgd::Shp< Engine::GLSLActivationState > glslActivationState = engine->getGLSLActivationState();

	//
	engine->sethCurrentProgram();

	vgeGL::engine::Engine::begin2DRendering( &newViewport2i, true );

	//glEnable(GL_LINE_SMOOTH);
	glColor4fv( window->getBorderColor().getValue() );
	glLineWidth( window->getBorderWidth() );

	glBegin(GL_LINE_LOOP);
	glVertex2f( 0.f, 0.f );
	glVertex2f( 1.f, 0.f );
	glVertex2f( 1.f, 1.f );
	glVertex2f( 0.f, 1.f );
	glEnd();

	vgeGL::engine::Engine::end2DRendering( true );

	// Restores GLSL activation state
	engine->setGLSLActivationState( glslActivationState );
}



} // namespace technique

} // namespace vgeGL
