// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_TECHNIQUE_TECHNIQUE_H
#define _VGE_TECHNIQUE_TECHNIQUE_H

#include <vge/vge.hpp>
#include <vge/visitor/NodeCollectorExtended.hpp>



namespace vge
{

namespace engine
{
	struct Engine;
}

/** 
 * @namespace vge::technique
 * 
 * @brief Provide a framework to describe evaluation strategy used by Engine.
 */
namespace technique
{
	


/**
 * @brief Technique describes the strategy to evaluate collected nodes in engine for single or multi-pass evaluation 
 * algorithm.
 * 
 * @code // Example to compute all bounding boxes in a scene graph.
 * #include <vge/engine/Engine.hpp>
 * #include <vge/technique/ComputeBoundingBox.hpp>
 * #include <vge/visitor/NodeCollectorExtended.hpp>
 * 
 * void apply( vge::engine::Engine *pEngine )
 * {
 * 	// Step 1 : Collect nodes.
 * 	vge::visitor::NodeCollectorExtended<> collector;
 * 	getRoot()->traverse( collector );
 * 
 * 	// Step 2 : Compute bounding box for the scene graph
 * 	vge::technique::ComputeBoundingBox computeBB;
 * 	computeBB.apply( pEngine, collector.getTraverseElements() );
 * 
 * 	// Step 3 : Use accessors of the technique to retrive additionnal informations (if any).
 * 	...
 * }
 * @endcode
 * 
 * @todo more documentation...
 * @todo virtual void forEach( const vgd::Shp< vge::service::Service > service );
 * @todo collectNodes();
 */
struct VGE_API Technique
{
	/**
	 * @brief Constructor.
	 */
	Technique();

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Technique();
	
	/**
	 * @brief Resets completely the state stack and all stacks for each matrix type.
	 */
	//virtual void resetEngine();

	/**
	 * @brief ???
	 * 
	 * @pre Must be called before starting nodes evaluation.
	 */
	virtual void prepareEval();
	
	/**
	 * @brief ???
	 * 
	 * @post Must be called after nodes evaluations.
	 */
	virtual void finishEval();

	/**
	 * @brief
	 */
	virtual void beginPass();
	
	/**
	 * @brief
	 */
	virtual void endPass();

	/**
	 * @brief Returns the current pass (1 for the first, 2 for the second and so on).
	 * 
	 * @return the current pass.
	 */
	uint32 currentPass() const;
	
	//virtual void push();
	//virtual void pop();

	virtual void apply( vge::engine::Engine *pEngine, vge::visitor::TraverseElementVector* pTraverseElements );



private:
	uint32															m_currentPass;
	bool																m_inPass;
};



} // namespace technique

} // namespace vge

#endif //#ifndef _VGE_TECHNIQUE_TECHNIQUE_H
