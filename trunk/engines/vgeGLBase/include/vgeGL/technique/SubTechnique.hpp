//// VGSDK - Copyright (C) 2011, 2014, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_TECHNIQUE_SUBTECHNIQUE_HPP
//#define _VGEGLBASE_TECHNIQUE_SUBTECHNIQUE_HPP
//
//#include <glo/IResource.hpp>
//#include <vge/visitor/NodeCollectorExtended.hpp>
//#include "vgeGL/vgeGL.hpp"
//#include "vgeGL/engine/Engine.hpp"
//
//namespace vgeGL
//{ 
//
//namespace technique { struct ForwardRendering; }
//
//}
//
//
//
//namespace vgeGL
//{
//
//namespace technique
//{
//
//
//
///**
// * @brief Element of a technique.
// */
//struct VGEGLBASE_API SubTechnique
//{
//	/**
//	 * @name Constructors
//	 */
//	//@{
//
//	/**
//	 * @brief Constructor
//	 *
//	 * Equivalent to reset()
//	 */
//	SubTechnique();
//
//	/**
//	 * @brief Initializes this object.
//	 *
//	 * Called during stage 1 by meta-technique
//	 *
//	 * @post !isEnabled()
//	 * @post getNode() == 0
//	 */
//	void reset();
//
//	//@}
//
//
//	/**
//	 * @name Enable/disable
//	 */
//	//@{
//
//	/**
//	 * @brief Determines whether this technique is enabled.
//	 *
//	 * @return true if this technique is enabled, false otherwise
//	 */
//	const bool isEnabled() const;
//
//	/**
//	 * @brief Enables or disables this technique depending on the value of the parameter isEnabled.
//	 *
//	 * @param isEnabled		true when this technique must be enabled, false otherwise
//	 *
//	 * @return this technique state before calling this method
//	 */
//	const bool setEnabled( const bool enabled = true );
//
//	//@}
//
//
//
//	// Visitor interface
//
//	/**
//	 * @name Stage 1 : Extract informations
//	 * Invoked on the first stage of rendering to collect informations used by this technique.
//	 */
//	//@{
//
//	virtual void stageCollectInformationsBegin( vgeGL::engine::Engine * engine )
//	{}
//
//	virtual const bool collectInformationsCallback( vge::visitor::TraverseElementVector::const_iterator iterator )
//	{ return false; }
//
//	virtual void stageCollectInformationsEnd( vgeGL::engine::Engine * engine )
//	{}
//	//@}
//
//
//	/**
//	 * @name Stage 2 : Initializes RC
//	 */
//	//@{
//
//	/**
//	 * @brief Helper method to retrieve rc associated to getNode() in OpenGL manager of engine.
//	 *
//	 * @return the desired resource
//	 */
//	template< class rcType >
//	vgd::Shp< rcType > getRC( vgeGL::engine::Engine * engine )
//	{
//		vgd::Shp< vgeGL::engine::Engine::GLManagerType > rcManager = engine->getGLManager();
//
//		vgd::Shp< rcType > rc = rcManager->getShp< rcType >( getNode() );
//
//		return rc;
//	}
//
//
//	/**
//	 * @brief Helper method
//	 */
//	template< class rcType >
//	void templateStageInitializeRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
//	{
//		if ( isEnabled() )
//		{
//			// Tests if rc must be created and/or updated ?
//			bool callUpdateRC;
//
//			vgd::Shp< glo::IResource > rc = getRC< glo::IResource >( engine );
//
//			if ( !rc )
//			{
//				// Creates resource
//				rc.reset( new rcType );
//
//				// Register node and its resource into manager
//				vgd::Shp< vgeGL::engine::Engine::GLManagerType > rcManager = engine->getGLManager();
//				rcManager->add( getNode(), rc );
//
//				// RC must be initialized
//				callUpdateRC = true;
//			}
//			else
//			{
//				// Tests if rc is up to date ?
//				const bool isUpdated = isRCUpdated( technique, engine, rc );
//				callUpdateRC = !isUpdated;
//			}
//
//			// Updates RC ?
//			if ( callUpdateRC )
//			{
//				updateRC( technique, engine, rc );
//			}
//			// else nothing to do
//		}
//		// else nothing to do
//	}
//
//
//	/**
//	 * @brief This method should call stageInitializeRC<rcType>() if it needs resource, thus method isRCUpdated() and updateRC() must be defined.
//	 */
//	virtual void stageInitializeRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )=0;
//
//	/**
//	 * @brief Returns true if rc must be update be calling updateRC(), false otherwise.
//	 *
//	 * Returns always true, if this technique is disabled.
//	 * Otherwise returns the validity of dirty flag for the node of this technique (see getNode()).
//	 */
//	virtual const bool isRCUpdated( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< glo::IResource > rc );
//
//	/**
//	 * @brief
//	 */
//	virtual void updateRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< glo::IResource > rc )=0;
//
//	//@}
//
//
//	/**
//	 * @name Stage 3 : Pre-paint pass
//	 */
//	//@{
//
//	virtual void stagePrePaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
//	{}
//
//	//@}
//
//
//	/**
//	 * @name Stage 4 : Paint pass
//	 */
//	//@{
//
//	// @todo think about opaque and transparent pass
//	// called after beginPass() of paint pass
//	// useful to initialize uniform(s)
//	virtual void stageBeginPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
//	{}
//
//	virtual void stagePaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
//	{}
//
//	virtual void stageEndPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
//	{}
//
//	//@}
//
//
//	/**
//	 * @name Stage 5 : Post-paint pass
//	 */
//	//@{
//
//	virtual void stagePostPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
//	{}
//
//	//@}
//
//
//
//	/**
//	 * @name Node accessors
//	 */
//	//@{
//
//	/**
//	 * @brief Returns a stored node pointer.
//	 *
//	 * @return a node pointer
//	 */
//	vgd::node::Node * getNode() const;
//
//	/**
//	 * @brief Sets a node pointer to store.
//	 *
//	 * @param node	a node pointer to store
//	 */
//	void setNode( vgd::node::Node * node );
//
//	//@}
//
//
//private:
//	bool				m_isEnabled;	///< Determines whether this technique is enabled.
//	vgd::node::Node *	m_node;			///< Stored a node pointer. Typical usage is storing a pointer on the node configuring this technique.
//};
//
//
//
//} // namespace technique
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_TECHNIQUE_SUBTECHNIQUE_HPP
//