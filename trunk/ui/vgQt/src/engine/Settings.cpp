// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/engine/Settings.hpp"

#include <vgUI/Canvas.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vector>
#include <vgd/visitor/helpers.hpp>
#include <vgd/visitor/predicate/True.hpp>
#include <vgUI/event/CaptureEventProcessor.hpp>

namespace vgQt
{

namespace engine
{

namespace
{


void dirtyAllNodes( vgUI::Canvas * canvas )
{
    vgd::Shp< vgd::node::NodeList > nodeList;
    nodeList = vgd::visitor::find( canvas->getRoot(), vgd::visitor::predicate::True() );

    using vgd::node::NodeList;

    for( NodeList::const_iterator	i		= nodeList->begin(),
                                    iEnd	= nodeList->end();
        i != iEnd;
        ++i )
    {
        vgd::Shp< vgd::node::Node > node = *i;
        node->getDirtyFlag( node->getDFNode() )->dirty();
    }
}


}

Settings::Settings()
{
    m_glslButton = new QCheckBox("Use GLSL pipeline");
    m_disableLighting = new QCheckBox("Disable lighting");
    m_disableTexture = new QCheckBox("Disable texture");
    m_disableShadow = new QCheckBox("Disable shadow");
    m_disableDisplayList = new QCheckBox("Disable display list");
    m_disableVBO = new QCheckBox("Disable VBO");
    m_disableDepthPrePass = new QCheckBox("Disable Depth pre-pass");
    m_showFPS = new QCheckBox("Show counters (fps and frame)");
    m_debugEvents = new QCheckBox("Log events");
    m_captureButton = new QCheckBox("Enable capture HotKeys");
    m_benchButton = new QPushButton("Bench");
    m_clearGLResourcesButton = new QPushButton("Clear OpenGL Resources");

    addWidget(m_glslButton);
    addWidget(m_disableLighting);
    addWidget(m_disableTexture);
    addWidget(m_disableShadow);
    addWidget(m_disableDisplayList);
    addWidget(m_disableVBO);
    addWidget(m_disableDepthPrePass);
    addWidget(m_showFPS);
    addWidget(m_debugEvents);

    addWidget(m_benchButton);
    addWidget(m_clearGLResourcesButton);

    addWidget(m_captureButton);
    addStretch();

    connect(m_glslButton, SIGNAL(clicked()), (Settings*) this, SLOT(onGLSL()));
    connect(m_disableLighting, SIGNAL(clicked()), (Settings*) this, SLOT(onDisableLighting()));
    connect(m_disableTexture, SIGNAL(clicked()), (Settings*) this, SLOT(onDisableTexture()));
    connect(m_disableShadow, SIGNAL(clicked()), (Settings*) this, SLOT(onDisableShadow()));
    connect(m_disableDisplayList, SIGNAL(clicked()), (Settings*) this, SLOT(onDisableDisplayList()));
    connect(m_disableVBO, SIGNAL(clicked()), (Settings*) this, SLOT(onDisableVBO()));
    connect(m_disableDepthPrePass, SIGNAL(clicked()), (Settings*) this, SLOT(onDisableDepthPrePass()));
    connect(m_showFPS, SIGNAL(clicked()), (Settings*) this, SLOT(onShowFPS()));
    connect(m_debugEvents, SIGNAL(clicked()), (Settings*) this, SLOT(onDebugEvents()));
    connect(m_captureButton, SIGNAL(clicked()), (Settings*) this, SLOT(onDebugEvents()));
    connect(m_benchButton, SIGNAL(clicked()), (Settings*) this, SLOT(onBench()));
    connect(m_clearGLResourcesButton, SIGNAL(clicked()), (Settings*) this, SLOT(onClearGLResources()));
}

void Settings::setCanvas( vgUI::Canvas * canvas )
{
    m_canvas = canvas;

    // Initializes button
    if( m_canvas != 0 )
    {
        m_glslButton->setChecked( m_canvas->getGLEngine()->isGLSLEnabled() );

        m_disableLighting->setChecked( !m_canvas->getGLEngine()->isLightingEnabled() );
        m_disableTexture->setChecked( !m_canvas->getGLEngine()->isTextureMappingEnabled() );
        m_disableShadow->setChecked( !m_canvas->getGLEngine()->isShadowEnabled() );
        m_disableDisplayList->setChecked( !m_canvas->getGLEngine()->isDisplayListEnabled() );
        m_disableVBO->setChecked( !m_canvas->getGLEngine()->isVertexBufferObjectEnabled() );
        m_disableDepthPrePass->setChecked( !m_canvas->getGLEngine()->isDepthPrePassEnabled() );

        m_showFPS->setChecked( m_canvas->isDebugOverlay() );
    }
}
void Settings::onGLSL()
{
    assert( m_canvas != 0 );

    m_canvas->getGLEngine()->setGLSLEnabled( m_glslButton->isChecked() );
    m_canvas->refreshForced();
}

void Settings::onDisableLighting()
{
    assert( m_canvas != 0 );
    m_canvas->getGLEngine()->setLightingEnabled( !m_disableLighting->isChecked() );

    dirtyAllNodes( m_canvas );

    m_canvas->refreshForced();
}
void Settings::onDisableTexture()
{
    assert( m_canvas != 0 );
    m_canvas->getGLEngine()->setTextureMappingEnabled( !m_disableTexture->isChecked() );

    dirtyAllNodes( m_canvas );

    m_canvas->refreshForced();
}
void Settings::onDisableShadow()
{
    assert( m_canvas != 0 );
    m_canvas->getGLEngine()->setShadowEnabled( !m_disableShadow->isChecked() );

    dirtyAllNodes( m_canvas );

    m_canvas->refreshForced();
}
void Settings::onDisableDisplayList()
{
    assert( m_canvas != 0 );

    m_canvas->getGLEngine()->setDisplayListEnabled( !m_disableDisplayList->isChecked() );

    dirtyAllNodes( m_canvas );

    m_canvas->refreshForced();
}
void Settings::onDisableVBO()
{
    assert( m_canvas != 0 );

    m_canvas->getGLEngine()->setVertexBufferObjectEnabled( !m_disableVBO->isChecked() );

    dirtyAllNodes( m_canvas );

    m_canvas->refreshForced();
}
void Settings::onDisableDepthPrePass()
{
    assert( m_canvas != 0 );

    m_canvas->getGLEngine()->setDepthPrePassEnabled( !m_disableDepthPrePass->isChecked() );

    dirtyAllNodes( m_canvas );

    m_canvas->refreshForced();
}

void Settings::onBench()
{
    assert( m_canvas != 0 );

    const int fps = m_canvas->getFPS();

    if ( fps >= 0 )
    {
        m_canvas->refreshForced();
        m_canvas->refreshForced();
        const int paintCount = 5 * 1000 / m_canvas->getFrameTime();
        m_canvas->bench( paintCount );
        m_canvas->refreshForced();
    }
}

void Settings::onShowFPS()
{
    assert( m_canvas != 0 );

    const bool isDebugOverlay = m_showFPS->isChecked();
    m_canvas->setDebugOverlay( isDebugOverlay );

    m_canvas->refreshForced();
}

void Settings::onDebugEvents()
{
    assert( m_canvas != 0 );

    const bool isDebugEvents = m_debugEvents->isChecked();

    m_canvas->setDebugEvents( isDebugEvents );
}

void Settings::onClearGLResources()
{
    assert( m_canvas != 0 );

    // @todo
}

void Settings::onCaptureButton()
{
    assert( m_canvas != 0 );

    const bool enableCapture = m_captureButton->isChecked();

    using vgUI::event::CaptureEventProcessor;

    if ( enableCapture )
    {
        // Inserts capture event processor
        vgd::Shp< CaptureEventProcessor > captureEventProcessor( new CaptureEventProcessor(m_canvas) );
        m_canvas->insertEventProcessor( captureEventProcessor );
    }
    else
    {
        // Removes capture event processor
        const int index = m_canvas->findEventProcessor< CaptureEventProcessor >();
        if ( index != m_canvas->getNumEventProcessors() )
        {
            // Capture event processor found
            m_canvas->removeEventProcessor( index );
        }
        // else nothing to do
    }
}

} // namespace engine

} // namespace vgQt
