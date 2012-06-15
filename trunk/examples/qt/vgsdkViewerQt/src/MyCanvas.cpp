// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgsdkViewerQt/MyCanvas.hpp"

#include <vgeGL/technique/MultiMain.hpp>

#include <vgd/node/LightModel.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>

namespace vgsdkViewerQt
{

MyCanvas::MyCanvas()
    : m_renderSettingsDialog( 0 )
{
    // Scene graph initialization.
    createOptionalNode( LIGHTS );
    createOptionalNode( DRAW_STYLE );

    using vgd::node::LightModel;
    vgd::Shp< LightModel > lightModel = vgd::dynamic_pointer_cast< LightModel >( createOptionalNode( LIGHT_MODEL ) );
    lightModel->setModel( LightModel::STANDARD_PER_PIXEL );
    lightModel->setViewer( LightModel::AT_EYE );

    using vgd::node::ClearFrameBuffer;
    vgd::Shp< ClearFrameBuffer > clear = createOptionalNodeAs< ClearFrameBuffer >( CLEAR_FRAME_BUFFER );

    // Get the reference of the default technique
    m_viewModeTechniques.resize( VIEW_MODE_COUNT );
    m_viewModeTechniques[ SINGLE_VIEW ]			= getPaintTechnique();
    m_viewModeTechniques[ LEFT_SIDED_VIEWS ]	= createMultiViewSidedTechnique();
    m_viewModeTechniques[ SQUARED_VIEWS ]		= createMultiViewSquaredTechnique();

    // setViewMode( SINGLE_VIEW );

    // Default light configuration
    using vgd::node::Switch;
    vgd::Shp< Switch > lightSwitcher = vgd::dynamic_pointer_cast<Switch>( getOptionalNode(LIGHTS) );

    if ( lightSwitcher )
    {
        lightSwitcher->setWhichChild( 0 );
    }
}

void MyCanvas::keyPressEvent(QKeyEvent * event)
{
    using vgd::node::Switch;
    // L : switch to next light(s) configuration
    vgd::Shp< Switch > lightSwitcher = vgd::dynamic_pointer_cast<Switch>( getOptionalNode(LIGHTS) );
    if ( lightSwitcher != 0 && event->key() == Qt::Key_L )
    {
        int whichChild = lightSwitcher->getWhichChild();
        if ( whichChild == lightSwitcher->getNumChildren() - 1 )
        {
            whichChild = 0;
        }
        else
        {
            ++whichChild;
        }
        lightSwitcher->setWhichChild( whichChild );
        doRefresh();
    }

    // F : fps
    if ( event->key() == Qt::Key_F )
    {
        setDebugOverlay( !isDebugOverlay() );
        doRefresh();
    }
}

vgQt::engine::UserSettingsDialog* MyCanvas::getRenderSettingsDialog( QWidget* parent )
{
    if ( !m_renderSettingsDialog )
    {
        m_renderSettingsDialog = new vgQt::engine::UserSettingsDialog(parent);
    }

    return m_renderSettingsDialog;
}

const bool MyCanvas::appendToScene( const QString filename, const bool viewAllAfterLoading)
{
    const bool retVal = load(filename.toStdString());
    if(retVal)
    {
        if (viewAllAfterLoading) viewAll();

        refresh( REFRESH_FORCE, SYNCHRONOUS );
        m_filenames.append(filename);
    }
    return retVal;
}

const bool MyCanvas::appendToScene( const QList<QString> filenames, const bool viewAllAfterLoading)
{
    bool retVal = true;
    Q_FOREACH(QString filename, filenames)
    {
        const bool lRetVal = load(filename.toStdString());
        if(lRetVal)
        {
            m_filenames.append(filename);
            if(viewAllAfterLoading)
                viewAll();
            refresh( REFRESH_FORCE, SYNCHRONOUS );
        }
        else
        {
            retVal = false;
        }
    }
    return retVal;
}

const bool MyCanvas::isEmpty() const
{
    return getScene()->getNumChildren() == 0;
}

const bool MyCanvas::reloadScene()
{
    QList<QString> filenames = m_filenames;
    clearScene();
    const bool retVal = appendToScene( filenames, false );
    return retVal;
}

void MyCanvas::setViewMode( const ViewMode mode )
{
    if( mode < VIEW_MODE_COUNT && m_viewModeTechniques[mode] )
    {
        setPaintTechnique( m_viewModeTechniques[mode] );
        refreshForced( ASYNCHRONOUS );
    }
    else
    {
        vgLogDebug( "Error while setting view mode technique." );
    }
}

vgd::Shp< vgeGL::technique::Technique > MyCanvas::createMultiViewSingleTechnique()
{
    // Multi-view rendering technique initialization.
    using vgeGL::technique::MultiMain;

    vgd::Shp< MultiMain >	technique( new MultiMain() );

    vgd::Shp< MultiMain::Window > mainView = technique->addWindow( "main", 0, MultiMain::WindowBorder(false) );
    mainView->setGeometry( vgm::Rectangle2f(0.f, 0.f, 1.f, 1.f) );

    return technique;
}

vgd::Shp< vgeGL::technique::Technique > MyCanvas::createMultiViewSidedTechnique()
{
    // Multi-view rendering technique initialization.
    using vgeGL::technique::MultiMain;

    const float				oneTier		= 1.f / 3.f;
    const float				padding		= 0.011f;
    const float				subWidth	= oneTier - padding - padding;
    const float				subHeight	= oneTier - padding - padding;

    vgd::Shp< MultiMain >	technique( new MultiMain() );

    vgd::Shp< MultiMain::Window > mainView = technique->addWindow( "main", 0, MultiMain::WindowBorder(false) );
    mainView->setGeometry( vgm::Rectangle2f(0.f, 0.f, 1.f, 1.f) );

    vgd::Shp< MultiMain::Window > topView = technique->addWindow( "top", 1,
        MultiMain::WindowBorder(true, vgm::Vec4f(1.f,0.f,0.f,1.f)) );
    const vgm::Rotation rotateTop(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,1.f,0.f));
    topView->setGeometry( vgm::Rectangle2f(padding, 0*oneTier+padding, subWidth, subHeight) );
    topView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateTop)) );

    vgd::Shp< MultiMain::Window > bottomView = technique->addWindow( "bottom", 1,
        MultiMain::WindowBorder(true, vgm::Vec4f(0.f,1.f,0.f,1.f)) );
    const vgm::Rotation rotateBottom(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,-1.f,0.f));
    bottomView->setGeometry( vgm::Rectangle2f(padding, 1*oneTier+padding, subWidth, subHeight) );
    bottomView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateBottom)) );

    vgd::Shp< MultiMain::Window > oppositeView = technique->addWindow( "opposite", 1,
        MultiMain::WindowBorder(true, vgm::Vec4f(0.f,0.f,1.f,1.f)) );
    const vgm::Rotation rotateOpposite(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,0.f,1.f));
    oppositeView->setGeometry( vgm::Rectangle2f(padding, 2*oneTier+padding, subWidth, subHeight) );
    oppositeView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateOpposite)) );

    return technique;
}

vgd::Shp< vgeGL::technique::Technique > MyCanvas::createMultiViewSquaredTechnique()
{
    // Multi-view rendering technique initialization.
    using vgeGL::technique::MultiMain;

    vgd::Shp< MultiMain >	technique( new MultiMain() );

    vgd::Shp< MultiMain::Window > mainView = technique->addWindow( "main", 0,
        MultiMain::WindowBorder(true, vgm::Vec4f(1.f,1.f,1.f,1.f)) );
    mainView->setGeometry( vgm::Rectangle2f(0.5f, 0.5f, 0.5f, 0.5f) );

    vgd::Shp< MultiMain::Window > topView = technique->addWindow( "top", 1,
        MultiMain::WindowBorder(true, vgm::Vec4f(1.f,0.f,0.f,1.f)) );
    const vgm::Rotation rotateTop(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,1.f,0.f));
    topView->setGeometry( vgm::Rectangle2f(0.f, 0.f, 0.5f, 0.5f) );
    topView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateTop)) );

    vgd::Shp< MultiMain::Window > bottomView = technique->addWindow( "bottom", 1,
        MultiMain::WindowBorder(true, vgm::Vec4f(0.f,1.f,0.f,1.f)) );
    const vgm::Rotation rotateBottom(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,-1.f,0.f));
    bottomView->setGeometry( vgm::Rectangle2f(0.f, 0.5f, 0.5f, 0.5f) );
    bottomView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateBottom)) );

    vgd::Shp< MultiMain::Window > oppositeView = technique->addWindow( "opposite", 1,
        MultiMain::WindowBorder(true, vgm::Vec4f(0.f,0.f,1.f,1.f)) );
    const vgm::Rotation rotateOpposite(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,0.f,1.f));
    oppositeView->setGeometry( vgm::Rectangle2f(0.5, 0.f, 0.5f, 0.5f) );
    oppositeView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateOpposite)) );

    return technique;
}

void MyCanvas::clearScene()
{
    m_filenames.clear();
    getScene()->removeAllChildren();
}

} // namespace vgsdkViewerQt
