// VGSDK - Copyright (C) 2004, 2006, 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/engine/SceneManager.hpp"

#include <vgd/visitor/predicate/ByRegexName.hpp>
#include "vge/technique/ComputeBoundingBox.hpp"



namespace vge
{

namespace engine
{


SceneManager::SceneManager( vgd::Shp< vge::engine::Engine > engine )
:	m_hasVGSDK				( boost::logic::indeterminate		),

	m_root					( vgd::node::Group::create("ROOT")	),
	m_engine				( engine							),
	//m_collectorExt
	m_updateBoundingBox		( true	),
	m_numberOfFrames		( 1		),
	m_frameCount			( 0		)
{}



SceneManager::~SceneManager()
{}



vgd::Shp< vgd::node::Group > SceneManager::getRoot()
{
	return m_root;
}



vgd::Shp< vgd::node::Group > SceneManager::setRoot( vgd::Shp< vgd::node::Group > newRoot )
{
	vgd::Shp< vgd::node::Group > oldRoot;

	oldRoot = m_root;
	m_root = newRoot;

	return m_root;
}



vgd::Shp< vgd::node::Node > SceneManager::findFirstByName( const std::string name ) const
{
	return vgd::visitor::findFirstByName< vgd::node::Node >( m_root, name );
}



vgd::Shp< vgd::node::Node > SceneManager::findFirstByRegex( const std::string regexName ) const
{
	return vgd::visitor::findFirst< vgd::node::Node >(
		m_root,
		vgd::visitor::predicate::ByRegexName(regexName)
		);
}



void SceneManager::setBoundingBoxUpdate( const bool bEachRedraw )
{
	m_updateBoundingBox = bEachRedraw;
}



bool SceneManager::getBoundingBoxUpdate() const
{
	return m_updateBoundingBox;
}



void SceneManager::computeBoundingBox( vge::visitor::NodeCollectorExtended<> * pCollectorExt )
{
	vge::technique::ComputeBoundingBox computeBB;
	//computeBB.setRoot( getRoot() );

	if ( pCollectorExt == 0 )
	{
		updateNodeCollector();
		m_engine->resetMatrices(); //  @todo should call vge::engine::Engine::resetMatrices(); but virtual method
		//m_engine->resetEval();
		computeBB.apply( m_engine.get(), getNodeCollector().getTraverseElements() );
	}
	else
	{
		computeBB.apply( m_engine.get(), pCollectorExt->getTraverseElements() );
	}
}



void SceneManager::writeGraphviz( bool bGeneratePNG, std::ofstream *pofstream )
{
	// Write graphwiz.
	if ( pofstream == 0 )
	{
		std::string str("sceneGraph.dot");
		std::ofstream stream(str.c_str());
		
		getRoot()->writeGraphviz( stream );
	}
	else
	{
		getRoot()->writeGraphviz( *pofstream );
	}

	if ( bGeneratePNG )
	{
		system("dot -Tpng -osceneGraph.png sceneGraph.dot");
	}
}



void SceneManager::bench( const uint frame )
{
	m_numberOfFrames = frame;
}



void SceneManager::paint( const vgm::Vec2i size, const bool bUpdateBoundingBox )
{
	// Updates engine with size of window
	getEngine()->setDrawingSurfaceSize( size );

	// Computes bounding box.
	if ( bUpdateBoundingBox )
	{
		computeBoundingBox();
	}

	// Updates the frame count
	increaseFrameCount();
}



// @todo computeBoundingBox() see paint() method
void SceneManager::resize( const vgm::Vec2i size )
{
	// Updates engine with size of window
	getEngine()->setDrawingSurfaceSize( size );

	// Updates the frame count
	increaseFrameCount();
}



vgd::Shp< vge::engine::Engine > SceneManager::getEngine()
{
	return m_engine;
}



vge::visitor::NodeCollectorExtended<>& SceneManager::getNodeCollector()
{
	return m_collectorExt;
}



void SceneManager::updateNodeCollector()
{
	m_collectorExt.reset();
	m_root->traverse( m_collectorExt );
}



uint SceneManager::getNumberOfFrames() const
{
	return m_numberOfFrames;
}



void SceneManager::setNumberOfFrames( const uint numberOfFrames )
{
	m_numberOfFrames = numberOfFrames;
}



const uint SceneManager::getFrameCount() const
{
	return m_frameCount;
}



const uint SceneManager::increaseFrameCount()
{
	++m_frameCount;

	return m_frameCount;
}



const boost::logic::tribool SceneManager::hasVGSDK() const
{
	return m_hasVGSDK;
}



} // namespace engine

} // namespace vge
