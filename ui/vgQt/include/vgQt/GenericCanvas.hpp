// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_GENERICCANVAS_HPP_
#define _VGQT_GENERICCANVAS_HPP_

#include <glc/glc.hpp>
#include <glc_qt/glc_qt.hpp>

#include <vgd/Shp.hpp>
#include "vgQt/node/ActionsMenu.hpp"

#include <QWidget>

namespace vgQt
{

/**
 * @brief	Implements a generic rendering canvas based on QWidget with its own openGL context.
 *
 * It is meant to specialize vgQt::Canvas, vgQt::BasicViewer or vgQt::BasicManipulator.
 *
 */
template< typename CanvasT >
struct GenericCanvas : public QWidget, public CanvasT
{

public:

    explicit GenericCanvas(QWidget *parent = 0)
    : QWidget(parent),
      m_glc( 0 ),
      m_actionsMenu( new vgQt::node::ActionsMenu( this, vgQt::node::CANVAS))
    {
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_NoSystemBackground);
        setAutoFillBackground(true); // for compatibility

        setContextMenuPolicy(Qt::CustomContextMenu);
    }

    ~GenericCanvas()
    {
        CanvasT::shutdownVGSDK ();
    }

    const bool setCurrent()
    {
        const bool retVal = (m_glc != 0) ? glc_set_current( m_glc ) : false;
        if ( retVal == false )
        {
            vgLogDebug("glc_set_current returns false");
        }

        // gle must be made current
        if ( retVal )
        {
            // glc context has been made current. gle must be current too.
            if ( gleGetCurrent() != &CanvasT::getGleContext() )
            {
                gleSetCurrent( &CanvasT::getGleContext() );
            }
            //else nothing to do (already current)
        }
        else
        {
            // gle must be not current.
            gleSetCurrent( 0 );
        }
        return retVal;
    }

    const bool unsetCurrent()
    {
        const bool retVal = (m_glc != 0) ? glc_unset_current( m_glc ) : false;
        gleSetCurrent( 0 );
        return retVal;
    }

    const bool isCurrent() const
    {
        return (m_glc != 0) ? glc_is_current( m_glc ) : false;
    }

    void swapBuffer()
    {
        if ( m_glc != 0 )
        {
            glc_swap( m_glc );
        }
        else
        {
            vgLogDebug("vgQt::Canvas::swapBuffer called without a glc context.");
        }
    }


    const bool setFullscreen( const bool wantFullscreen = true )
    {
        if ( wantFullscreen == isFullscreen() )
        {
            // Nothing to do
            return true;
        }

        // Updates the current state.
        if ( m_glc )
        {
            return glc_drawable_set_fullscreen( m_glc, wantFullscreen, false /*no action on compositing window manager*/) != 0;
        }
        else
        {
            return false;
        }
    }

    const bool isFullscreen()
    {
        if ( m_glc )
        {
            return glc_drawable_is_fullscreen( m_glc ) != 0;
        }
        else
        {
            return false;
        }
    }

    void doRefresh()
    {
        if ( CanvasT::startVGSDK() )
        {
            const vgm::Vec2i v2iSize( width(), height() );
            CanvasT::paint( v2iSize, CanvasT::getBoundingBoxUpdate() );
            unsetCurrent();
        }
    }

    void sendRefresh()
    {
        if ( CanvasT::startVGSDK() )
        {
            const vgm::Vec2i v2iSize( width(), height() );
            CanvasT::paint( v2iSize, CanvasT::getBoundingBoxUpdate() );
            unsetCurrent();
        }
    }

    const bool startOpenGLContext()
    {
        // Tests if glc context is already created
        if ( m_glc == 0 )
        {
            // glc context is not already created, creates a new one

            // First creates the drawable from the canvas
            glc_drawable_t * drawable	= glc_qt_drawable_create( this );
            if ( drawable == 0 )
            {
                vgLogWarning("Unable to create the drawable.");
                return false;
            }

            // Sets the desired property for the context
            const vgeGL::engine::GLContextProperties& requestedProperties = m_requestedGLContextProperties;
            drawable->stereo = requestedProperties.enableQuadBufferStereo();

            // Next, creates the glc context (shared or not)
            m_glc = glc_create_shared( drawable, m_sharedCanvas ? dynamic_cast< const GenericCanvas * >(m_sharedCanvas)->m_glc : 0 );

            if ( m_glc == 0 )
            {
                glc_qt_drawable_destroy( drawable );
                vgLogWarning("Unable to create the glc context.");
                return false;
            }
            vgLogMessage("glc context successfully created.");

            // Next, mades the glc context current
            const bool isGLCCurrent = glc_set_current( m_glc );
            assert( isGLCCurrent && "Unable to set glc context current. This is not expected !!!" );

            vgLogMessage("glc context made current.");

            // Analyses current OpenGL context
            GLboolean glbool;
            glGetBooleanv( GL_STEREO, &glbool );
            if ( glbool )
            {
                vgLogMessage("OpenGL context with stereo support");
                m_currentGLContextProperties = vgeGL::engine::GLContextProperties(true);
            }
            else
            {
                m_currentGLContextProperties = vgeGL::engine::GLContextProperties(false);
                vgLogMessage("OpenGL context without stereo support");
            }
            m_hasCurrentGLContextProperties = true;

            // Finally, initializes gle and sets it current
            vgLogMessage("Start gle initialization...");
            CanvasT::getGleContext().clear();
            CanvasT::getGleContext().initialize();
            vgLogMessage("gle initialization successfully completed.");

            gleSetCurrent( &CanvasT::getGleContext() );

            assert( isCurrent() && "Internal error." );

            return true;
        }
        else
        {
            // glc context is already created
            const bool retVal = setCurrent();

            return retVal;
        }
    }

    const bool shutdownOpenGLContext()
    {
        if ( m_glc != 0 )
        {
            // Cleans gle context
            CanvasT::getGleContext().clear();
            gleSetCurrent(0);
            vgLogMessage("gle context cleaned.");

            // Deletes glc context
            glc_destroy( m_glc );
            m_glc = 0;
            vgLogMessage("glc context deleted.");

            return true;
        }
        else
        {
            return false;
        }
    }

    QPaintEngine * paintEngine () const
    {
        return 0;
    }
    void paintEvent(QPaintEvent* event)
    {
        Q_UNUSED(event);
        const vgm::Vec2i v2iSize( width(), height() );

        if ( CanvasT::startVGSDK() )
        {
            CanvasT::paint( v2iSize, CanvasT::getBoundingBoxUpdate() );
            unsetCurrent();
        }
    }
    void resizeEvent(QResizeEvent* event)
    {
        Q_UNUSED(event);
        const vgm::Vec2i v2iSize( width(), height() );

        if ( CanvasT::startVGSDK() )
        {
            CanvasT::resize( v2iSize );
            unsetCurrent();
        }
    }

private:
    glc_t			*m_glc;

protected:
    vgd::Shp< vgQt::node::ActionsMenu > 	m_actionsMenu;

};

} // namespace vgQt

#endif // _VGQT_GENERICCANVAS_HPP_
