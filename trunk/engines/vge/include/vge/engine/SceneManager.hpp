// VGSDK - Copyright (C) 2004, 2006, 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_ENGINE_SCENEMANAGER_HPP
#define _VGE_ENGINE_SCENEMANAGER_HPP

#include <boost/logic/tribool.hpp>
#include <fstream>
#include <vgd/node/Group.hpp>
#include <vgd/visitor/helpers.hpp>
#include <vgd/visitor/predicate/ByKindOfType.hpp>
#include <vgd/visitor/predicate/ByType.hpp>
#include "vge/engine/Engine.hpp"
#include "vge/visitor/NodeCollectorExtended.hpp"



namespace vge
{

namespace engine
{

/**
 * @brief Provide a scene graph and some associated services.
 * 
 * This class provides some methods to :
 *
 * - Manage a scene graph :
 * - Set/get root node.
 * - Search nodes in the scene graph with some predicates.
 * - Compute/update all bounding box in the scene graph.
 * - Write the graphviz graph of the scene graph with writeGraphviz(). This is very useful to show the scene graph
 *   topology, the name and the type of each node in the scene graph.
 * - paint()/resize() methods for doing rendering from the GUI (see vgUI and specialization like vgGTK) and the method bench() for doing benchmarks.
 * 
 * @remarks \c Paint service is only available in vgeGL. So paint/resize/bench don't do the whole work.
 * Theses methods are specialized to be completed in vgeGL::engine::SceneManager.
 * 
 * @todo method find<>( root ) that take the root of the search.
 */
struct VGE_API SceneManager
{
	/**
	 * @name Constructors/Destructor
	 */
	//@{
	
	/**
	 * @brief Constructor
	 * 
	 * @param pEngine		reference on the engine that must be used by the scene manager.
	 * 
	 * By default the root node of the scene graph, a vgd::node::Group, is created with no children and is name is \c ROOT.
	 */
	SceneManager( vgd::Shp< vge::engine::Engine > pEngine );

	/**
	 * @brief Destructor
	 */
	virtual ~SceneManager();
	//@}



	/**
	 * @name Accessors to scene graph
	 *
	 * @todo Updates doc of findFirst*() methods (see vgd/visitor/helpers.hpp)
	 */
	//@{

	/**
	 * @brief Returns the root node.
	 *
	 * @return the root node.
	 */
	vgd::Shp< vgd::node::Group > getRoot();

	/**
	 * @brief Set the root node.
	 * 
	 * @param newRoot		the new root node.
	 *
	 * @return the previous root node.
	 */
	vgd::Shp< vgd::node::Group > setRoot( vgd::Shp< vgd::node::Group > newRoot );

	/**
	 * @brief Search the first node of type \c nodeType.
	 * 
	 * @return The desired node or a smart pointer to null.
	 */
	template< typename nodeType >
	vgd::Shp< nodeType > findFirstByType() const
	{
		return vgd::visitor::findFirst< nodeType >( m_root, vgd::visitor::predicate::ByType< nodeType >() );
	}

	/**
	 * @brief Search the first node of type \c nodeType.
	 * 
	 * @return The desired node or a smart pointer to null.
	 */
	template< typename nodeType >
	vgd::Shp< nodeType > findFirstByKindOfType() const
	{
		return vgd::visitor::findFirst< nodeType >( m_root, vgd::visitor::predicate::ByKindOfType< nodeType >() );
	}

	/**
	 * @brief Search the first node with name that match a string.
	 * 
	 * @param name		string to search in node names.
	 * 
	 * @return The desired node or a smart pointer to null.
	 */
	vgd::Shp< vgd::node::Node > findFirstByName( const std::string name ) const;
	
	/**
	 * @brief Search the first node with name that match a regular expression.
	 * 
	 * @param regexName		regular expression to search in node names.
	 * 
	 * @return The desired node or a smart pointer to null.
	 */
	vgd::Shp< vgd::node::Node > findFirstByRegex( const std::string regexName ) const;

	//@}



	/**
	 * @name Accessors to bounding box computation and to the paint() behavior about bounding box computation
	 * 
	 * @remark By default the bounding boxes in the scene graph are update before each redraw in the paint() method.
	 */
	//@{
	
	/**
	 * @brief Sets the policies for updating bounding box in the scene graph.
	 * 
	 * @param bEachRedraw	true to update bounding box at each redraw(OnPaint()), false to update it yourself.
	 */
	void setBoundingBoxUpdate( const bool bEachRedraw );
	
	/**
	 * @brief Gets the policies for updating bounding box in the scene graph.
	 * 
	 * @return true if update bounding box occurs at each redraw(OnPaint()), false if not.
	 */
	bool getBoundingBoxUpdate() const;
	
	/**
	 * @brief Compute/update bounding boxes.
	 * 
	 * If pCollectorExt equals zero, then the internal node collector is update with all nodes from scene graph.
	 * Otherwise nodes founded in node collector passed in parameter are used to update/compute bounding boxes.
	 * 
	 * @param pCollectorExt		the node collector to used or 0 if internal node collector should be used.
	 */
	void computeBoundingBox( vge::visitor::NodeCollectorExtended<> * pCollectorExt = 0 );
	
	//@}



	/**
	 * @name Debug service
	 */
	//@{
	
	/**
	 * @brief Write the graph into a output stream in graphviz dot format.
	 * 
	 * @param bGeneratePNG	true if you want to use \c dot program to generate the picture of the scene graph
	 * @param pofstream		if null, an ofstream("sceneGraph.dot") is used, otherwise use the passed output stream.
	 * 
	 * @remark To generate png, Graphviz must be in your path.
	 * 
	 * @sa vgd::node::Group::writeGraphviz
	 *
	 * @deprecated At least for gtk user interface.
	 */
	 void writeGraphviz( bool bGeneratePNG = false, std::ofstream *pofstream = 0 );

	//@}



	/**
	 * @name Rendering methods
	 */
	//@{
	
	/**
	 * @brief Use it to indicate that paint() must be called multiples times during the next refresh (OnPaint).
	 * 
	 * This method is very useful to do benchmarks.
	 * 
	 * @param frame		number of frame to render.
	 */
	virtual void bench( const uint frame );
	
	/**
	 * @brief Called to update the bounding box.
	 * 
	 * @param size					the size of the window.
	 * @param bUpdateBoundingBox		true to update bounding box in the scene graph, false to do nothing.
	 */
	virtual void paint( const vgm::Vec2i size, const bool bUpdateBoundingBox );

	 /**
	  * @brief Called when the window is resized.
	  *
	  * @param size		the size of the window.
	  */
	virtual void resize( const vgm::Vec2i size );

	//@}



	/**
	 * @name Accessors to some vgsdk objects
	 */
	//@{

	/**
	 * @brief Returns the main evaluation engine.
	 * 
	 * @return the vge engine.
	 */
	vgd::Shp< vge::engine::Engine >			getEngine();

	/**
	 * @brief Returns the collector of node.
	 *
	 * @return the node collector.
	 */
	vge::visitor::NodeCollectorExtended<>&	getNodeCollector();
	
	/**
	 * @brief Updates the node collector.
	 * 
	 * Traverses the scene graph and updates collected nodes.
	 */
	void updateNodeCollector();

	/**
	 * @brief Returns the number of frames that must be render.
	 */
	uint	getNumberOfFrames() const;
	
	/**
	 * @brief Sets the number of frames that must be render.
	 * 
	 * Number of frames to render during the next paint(). This value is automatically reseted to 1 inside paint().
	 */
	void	setNumberOfFrames( const uint numberOfFrames );


	/**
	 * @brief Returns the number of frames displayed by paint() method.
	 *
	 * @return the number of frames displayed by paint() method
	 */
	const uint getFrameCount() const;
	//@}


	/**
	 * @name vgsdk startup/shutdown
	 */
	//@{

	/**
	 * @brief Calls this method before using vgsdk.
	 *
	 * @return true if vgsdk could be used, false otherwise.
	 */
	virtual const bool startVGSDK()=0;

	/**
	 * @brief Calls this method when you no longer need vgsdk.
	 *
	 * @return true if vgsdk shutdown has been completed successfuly, false otherwise.
	 */
	virtual const bool shutdownVGSDK()=0;

	/**
	 * @brief Tests vgsdk initialization state.
	 *
	 * @return true if vgsdk has been successfully initialized, false if vgsdk has not been successfully initialized,
	 * indeterminate if vgsdk is not initialized.
	 */
	virtual const boost::logic::tribool hasVGSDK() const;
	//@}


protected:

	/**
	 * @brief Increases the frame count by one.
	 *
	 * @return the new frame count, i.e. getFrameCount()
	 */
	virtual const uint increaseFrameCount();

	boost::logic::tribool m_hasVGSDK;			///< see hasVGSDK()
private:

	/**
	 * @name Datas
	 */
	//@{
	/**
	 * @brief Root node of scene graph.
	 */
	vgd::Shp< vgd::node::Group >			m_root;
	
	/**
	 * @brief Main evaluation engine.
	 */
	vgd::Shp< vge::engine::Engine >			m_engine;
	
	/**
	 * @brief Collector of nodes.
	 */
	vge::visitor::NodeCollectorExtended<>	m_collectorExt;
	
	/**
	 * @brief true to update bounding box at each redraw, false if not.
	 */
	bool 									m_updateBoundingBox;
	
	/**
	 * @brief Number of frames to render during the next OnPaint().
	 */
	uint									m_numberOfFrames;

	uint m_frameCount;	///< the number of frames displayed by paint() method
	//@}
};



} // namespace engine

} // namespace vge

#endif //#ifndef _VGE_SCENEMANAGER_HPP
