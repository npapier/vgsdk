// VGSDK - Copyright (C) 2004, 2006, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_TECHNIQUE_TECHNIQUE_HPP
#define _VGE_TECHNIQUE_TECHNIQUE_HPP

#include "vge/vge.hpp"
#include "vge/visitor/NodeCollectorExtended.hpp"

namespace vgd { template<class T> struct Shp; }

namespace vge
{
	namespace engine { struct Engine; }
	
	namespace pass { struct Pass; }
	
	namespace service { struct Service;	}
}



namespace vge
{

/** 
 * @namespace vge::technique
 * 
 * @brief Provide a framework to describe evaluation strategy used by engine.
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
 * 	// Step 3 : Use accessors of the technique to retrieve additionnal informations (if any).
 * 	...
 * }
 * @endcode
 * 
 * @todo more documentation...
 * @todo collectNodes();
 * @todo virtual void push(); and virtual void pop();
 */
struct VGE_API Technique
{
	/**
	 * @name Constructor/destructor
	 */
	//@{

	/**
	 * @brief Constructor.
	 */
	Technique();

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Technique();
	//@}



	/**
	 * @brief Must be overridden to implements the technique.
	 * 
	 * @param engine			engine used during evaluation
	 * @param traverseElements	elements to evaluate
	 */
	virtual void apply(	vge::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements ) = 0;



protected:
	/**
	 * brief Resets completely the state stack and all stacks for each matrix type.
	 * @todo
	 */
	//virtual void resetEngine();

	/**
	 * @brief Initializes the technique to prepare evaluation.
	 * 
	 * @remark Must be called before starting nodes evaluation.
	 * 
	 * @pre engine != 0 and valid
	 * @pre traverseElements != 0 and valid
	 * @pre isInsideAPass() == false
	 * 
	 * @param engine			engine used during evaluation
	 * @param traverseElements	elements to evaluate
	 * 
	 * @post getCurrentPass() == 0
	 * @post isInsideAPass() == false
	 */
	virtual void prepareEval( vge::engine::Engine *engine, vge::visitor::TraverseElementVector* traverseElements );
	
	/**
	 * @brief Initializes the technique to finish evaluation.
	 * 
	 * @remark Must be called after nodes evaluations
	 * 
	 * @pre isInsideAPass() == false
	 * @pre getCurrentPass() > 0
	 * 
	 * @post m_engine = m_traverseElements = 0
	 */
	virtual void finishEval();

	/**
	 * @brief Must be called at the beginning of each new pass.
	 * 
	 * @pre isInsideAPass() == false
	 * @post currentPass() = currentPass() + 1
	 */
	virtual void beginPass();
	
	/**
	 * @brief Muse be called at the end of each new pass
	 */
	virtual void endPass();

	/**
	 * @brief Returns the current pass (1 for the first, 2 for the second and so on).
	 * 
	 * @return the current pass number
	 */
	const uint32 getCurrentPass() const;

	/**
	 * @brief Tests if the technique is inside a pass.
	 * 
	 * A technique is inside a pass if and only if beginPass() has been called and endPass() has not yet been called.
	 * 
	 * @return true if this technique is inside a pass, false otherwisE.
	 */
	const bool isInsideAPass() const;
	
	/**
	 * @brief Evaluates a single pass
	 * 
	 * @param pass		the pass to evaluate
	 * @param service	the service to evaluate
	 */
	void evaluatePass( vgd::Shp< vge::pass::Pass > pass, vgd::Shp< vge::service::Service > service );



protected:

	vge::visitor::TraverseElementVector	*getTraverseElements() const;

private:
	/**
	 * @name Internal data
	 */
	//@{
	uint32									m_currentPass;
	bool									m_inPass;
	
	vge::engine::Engine	*					m_engine;
	vge::visitor::TraverseElementVector	*	m_traverseElements;
	//@}
};



} // namespace technique

} // namespace vge

#endif //#ifndef _VGE_TECHNIQUE_TECHNIQUE_HPP
